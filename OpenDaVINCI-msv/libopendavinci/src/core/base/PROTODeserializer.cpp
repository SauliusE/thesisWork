/*
 * OpenDaVINCI.
 *
 * This software is open source. Please see COPYING and AUTHORS for further information.
 */

#include "core/base/PROTODeserializer.h"
#include "core/base/Serializable.h"

namespace core {
    namespace base {

        using namespace std;
// uint32_t decodeVar ( istream &in, uint64_t &value );
        PROTODeserializer::PROTODeserializer(istream &in) :
                m_buffer(),
                m_values(),
                m_size(0),
                position(0),
                m_in(in){
                    
            // Initialize the stringstream for getting valid positions when calling tellp().
            // This MUST be a blank (Win32 has a *special* implementation...)!
 
                  //Decoding magic number
//                 m_buffer.str("");
//                     in.tellg();
//                       cout << "buffer write possition " <<in.tellp();
             
                position = in.tellg();
//                      cout << " buffer read position in CONSTRUCTOR " << position << endl;
                uint64_t value = 0;
                decodeVar(in,value);
                //casting value to uint16
                uint16_t magicNumber = static_cast<uint16_t>(value);
//                  cout << " magic number " << magicNumber <<endl;
                 in.clear();
                in.seekg(0,ios_base::beg);
//                       cout << " after clear buffer read position " << in.tellg() << endl;
                if(magicNumber == 0xAABB){
//                      cout << " found magic number " << endl;
                    return;
                
            }
//             cout << " once " << endl;
value = 0;
            decodeVar(in,value);
             uint16_t msgSize =static_cast<uint16_t>(value);
//               cout<<"msg size " <<msgSize<<endl;
            char c = 0;
            in.get(c);

      // check size encoding
            uint32_t readSize = 0;
            while(in.good() ){
                m_buffer.put(c);            
                in.get(c);
                readSize++;
            }
            m_size = msgSize;
            
//              cout << " MESSSAGE SIZE IN CONSTRUCTOR " <<m_size << endl;
//              cout << " readSize : " << readSize << endl;
            in.clear();
            in.seekg(position,ios_base::beg);
//             cout << "next thing will be 1 " <<endl;

        }

        PROTODeserializer::~PROTODeserializer() {
//             cout << " deconstructor " << endl;;
             int pos = m_buffer.tellg();
            m_in.clear();
            m_in.seekg(pos, ios_base::beg);
        }
       

        void PROTODeserializer::read(const uint32_t id, Serializable &s) {
          (void) id; //to be removed in the future
                stringstream ss;
//                 cout << " SS write and read pointers in the begining " << ss.tellp() << " " << ss.tellg() << endl;
//                cout << " s m_size " <<  m_size << endl;
                uint64_t tempSize = static_cast<uint64_t>(m_size);
//                 cout << " tempSize " << tempSize << endl;
                encode(ss,tempSize);
//                 cout << " m_size takes to encode " <<  <<endl;
//                 ss.clear();
//                 cout << " SS write and read pointers in the begining " << ss.tellp() << " " << ss.tellg() << endl;
              int pos = m_buffer.tellg();
                char c = 0;
                m_buffer.get(c);
                while (m_buffer.good()) {
                ss.put(c);
                m_buffer.get(c);
                }
//                 cout << " SS write and read pointers in the begining " << ss.tellp() << " " << ss.tellg() << endl;
//                 cout << " Going to nested data  " << endl;
//                 cout << " Read position in Serializable " << pos <<endl;
                
//                 cout << " ss read pointer " << ss.tellg() << endl;
//                 (void) s ;
//                 uint64_t value;
//                 uint32_t decodedValue;
//                 decodeVar(ss,value);
//                 cout << " SS write and read pointers in the begining " << ss.tellp() << " " << ss.tellg() << endl;
//                 decodedValue = static_cast<uint32_t>(value);
//                 cout << " directly decoded size " <<decodedValue<< endl;
                ss >> s;
                pos += ss.tellg();
                m_buffer.clear();
                m_buffer.seekg(pos, ios_base::beg);
//                 cout << " End of Serializable " << pos<< endl;
//                  cout << " m_buffer lenght " << m_buffer.str().length() <<endl;
            }

        

        
        void PROTODeserializer::read(const uint32_t id, bool &b) {
                (void)id;
//                    cout << " b m_size " <<  m_size << endl;
//                    cout << " bool " << endl;
//                 cout << " msize begining of boold " << m_size<<endl;
                uint32_t size ;
                uint64_t key;
                size =decodeVar(m_buffer,key);
                m_size -= size ;
//                 cout << " bool key size " << size << endl;
        
                WIRE_TYPE wireType = getWireType(key);
                uint32_t fieldId = getFieldNumber(key);
                (void) wireType;
                (void) fieldId;
                uint64_t v;
                size  = decodeVar(m_buffer,v);
//                 cout << " bool size was " <<size<<endl;
                m_size -= size;
                b = v;
//                 cout << "decoded b " << b <<endl;
//                 cout << "m size after bool " << m_size<<endl;
               
        }

        void PROTODeserializer::read(const uint32_t id, char &c) {
                (void)id;
//                    cout << " c m_size " <<  m_size << endl;
                    
                uint64_t key;
                decodeVar(m_buffer,key);                   
                WIRE_TYPE wireType = getWireType(key);           
                uint32_t fieldId = getFieldNumber(key);                   
                (void) wireType;                  
                (void) fieldId;                  
                uint64_t v;                   
                uint32_t size ;
                size  = decodeVar(m_buffer,v);
                m_size -= size;                  
                c =  v;
//                                 cout << "decoded c " << c <<endl;

      }

        void PROTODeserializer::read(const uint32_t id, unsigned char &uc) {          (void)id;
//    cout << "uc  m_size " <<  m_size << endl;
                uint64_t key;
                decodeVar(m_buffer,key);
                WIRE_TYPE wireType = getWireType(key);
                uint32_t fieldId = getFieldNumber(key);
                (void) wireType;
                (void) fieldId;
                uint64_t v;
                 uint32_t size ;
                size  = decodeVar(m_buffer,v);
                m_size -= size;
                uc =  v;
//                                 cout << "decoded uc " << uc <<endl;

        }

        void PROTODeserializer::read(const uint32_t id, int32_t &i) {
                (void)id;
// //                 
//                    cout << "i m_size " <<  m_size << endl;
//                 cout << " read int " << m_size << endl;
                uint32_t size ;
                uint64_t key;
                size = decodeVar(m_buffer,key);
//                 cout << " int key " << i << endl;
                m_size -=size;
//                 cout << " decoded key  m_size" << m_size <<endl;
                WIRE_TYPE wireType = getWireType(key);
                uint32_t fieldId = getFieldNumber(key);
                (void) wireType;
                (void) fieldId;
                uint64_t v;
                 
                size  = decodeVar(m_buffer,v);
                
                m_size -= size;
//                  cout << " decoded int  m_size" << m_size <<endl;
                i = static_cast<int32_t>(v);
//                                                 cout << "decoded i " << i <<endl;

//                 cout << "decoded int : " << i << endl;

        }

        void PROTODeserializer::read(const uint32_t id, uint32_t &ui) {
                (void)id;
                uint64_t key;
                
//                    cout << "ui m_size " <<  m_size << endl;
                decodeVar(m_buffer,key);
//                 cout << " m_size position begining " << m_size <<endl;
                WIRE_TYPE wireType = getWireType(key);
                uint32_t fieldId = getFieldNumber(key);
//                 cout << " key uint32_t is : " << key<<endl;
                (void) wireType;
                (void) fieldId;
                
                uint64_t v;
                 uint32_t size ;
                size  = decodeVar(m_buffer,v);
//                 cout << " decodede value  of uint32 " << v << endl; 
                m_size -= size;
                ui = static_cast<uint32_t>(v);
//                                                 cout << "decoded ui " << ui <<endl;

        }

        void PROTODeserializer::read(const uint32_t id, float &f) {
//                cout << " flaot m_size " <<  m_size << endl;
                (void) id;  
                uint64_t key;
                decodeVar(m_buffer,key);
                WIRE_TYPE wireType = getWireType(key);
                uint32_t fieldId = getFieldNumber(key);
                (void) wireType;
                (void) fieldId;
                m_size -= 4;
                float _f =0;
                m_buffer.read(reinterpret_cast<char *>(&_f), 4);
                f= _f;
//                    cout << " f end m_size " <<  m_size << endl;
//                                                    cout << "decoded f " <<f <<endl;

              
        }

        void PROTODeserializer::read(const uint32_t id, double &d) {
                (void) id;
                uint64_t key;
                uint32_t size ;   
//                 cout << "d m_size " <<  m_size << endl;
//                                 cout << " next will be 3 " << endl;
//                 cout <<  " m size in double " << m_size <<endl;
                size = decodeVar(m_buffer,key);
                m_size -= size;
//                  cout << " decode key double " << key<<endl;
                WIRE_TYPE wireType = getWireType(key);
                uint32_t fieldId = getFieldNumber(key);
//                  cout << " WIRE_TYPE "  << wireType << " fieldId " << fieldId << endl;
                (void) wireType;
                (void) fieldId;                
//                 cout << " key  Deserializer" << key<< endl;
//                 double _d =0;    
              m_size -=8;
                m_buffer.read(reinterpret_cast<char *>(&d),8); 
// cout <<  " m size in double end " << m_size <<endl;
//                  cout << " dd " <<d<<endl;
            //    d = _d;
        }

        void PROTODeserializer::read(const uint32_t id, string &s) {
                (void) id;
                uint64_t key;
//                    cout << "s m_size " <<  m_size << endl;
                decodeVar(m_buffer,key);
//                 cout << "decoded string key " << key <<endl;
                WIRE_TYPE wireType = getWireType(key);
                uint32_t fieldId = getFieldNumber(key);
                (void) wireType;
                (void) fieldId;
                uint64_t size;
                uint32_t siz =  decodeVar(m_buffer, size );
                uint32_t length = (uint32_t) size ;
//                 length++;
//                 cout << "string length " <<  length << endl;
                char *str = new char[length+1];
                m_size -= length;
                m_size -= siz;
                m_buffer.read(reinterpret_cast<char *>(str), length);
                str[length] = '\0';
//                 cout << " raw string " << str <<endl;
                s = string(str, length);
//                 cout << " string string " << s << endl;
//                    cout << "s end m_size " <<  m_size << endl;
        }

        void PROTODeserializer::read(const uint32_t id, void *data, uint32_t size) {
              cout << "Read data Deserializer" << "- ID value: " << id <<" |  data  value: " << data << " | size of data : "<< size <<endl;

        }
        void PROTODeserializer::read(istream &in, core::data::Container &container) {
                // Getting message size
                // Decoding magic number
                uint64_t value = 0;
                decodeVar(in,value);
//                    cout << " Deserializer container magic number " << value << endl;
                // casting value to uint16
                uint16_t magicNumber = (uint16_t) value;
//                 cout << "magic number des " << magicNumber<< endl;
             //   cout << " magic number " << 0xAABB << " == "<< magicNumber << endl;
                if (magicNumber != 0xAABB){
                   if (in.good()) {
                    // Stream is good but still no magic number?
                    clog << "Stream corrupt: magic number not found. proto" << endl;
                    }
                return;                   
                }
                stringstream buffer;
                char c = 0;
                in.get(c);
                while(in.good()){
                  buffer.put(c);
                  in.get(c);
                }
                buffer >> container;


    }
     
        uint32_t PROTODeserializer::decodeVar ( istream &in, uint64_t &value )
          {
          uint32_t size = 0;
              int shift = 0;
              uint8_t c;
              value = 0;

              do {
                    c = in.get();
                    value |= ( uint64_t ) ( c & 0x7F ) << shift;
                    shift += 7;
                    ++size;
              } while ( in.good() && ( c & 0x80 ) != 0 );

              value = le64toh ( value );

              return size;
          }
          
            void PROTODeserializer::encode( ostream &out, uint64_t value){
  
                value = htole64( value);
                
                    do {

                        char byte = value & (uint8_t) 0x7F;
                        value >>= 7;
            
                        if ( value) {
                            byte |= ( uint8_t ) 0x80;
                        }
                        out.put( byte );
                
                } while (value);
            }

    }
} // core::base
