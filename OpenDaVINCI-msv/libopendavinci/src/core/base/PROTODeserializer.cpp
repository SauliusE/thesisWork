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
                position(0){
            // Initialize the stringstream for getting valid positions when calling tellp().
            // This MUST be a blank (Win32 has a *special* implementation...)!
 
                  //Decoding magic number
                m_buffer.str("");
                uint64_t value = 0;
                decodeVar(in,value);
                //casting value to uint16
                uint16_t magicNumber = static_cast<uint16_t>(value);
    //             cout << " magic number " << magicNumber <<endl;
                in.clear();
                in.seekg(0,ios_base::beg);
                if(magicNumber == 0xAABB){
    //                 cout << " found magic number " << endl;
                    return;
                
            }
//             cout << " once " << endl;
            decodeVar(in,value);
//             uint32_t msize;
//             in.read(reinterpret_cast<char*>(&msize),sizeof(uint32_t));
            uint32_t msgSize =static_cast<uint32_t>(value);
//             cout<<"msg size " <<msgSize<<endl;
            char c = 0;
            in.get(c);
//       in.get(c);
//       in.get(c);
//       in.get(c);
      // check size encoding
            uint32_t readSize = 0;
            while(in.good() && readSize <= msgSize){
                m_buffer.put(c);
                in.get(c);
                readSize++;
            }
            m_size = msgSize;
//             cout << " readSize : " << readSize << endl;
//             m_buffer.clear();
//             m_buffer.seekg(0,ios_base::beg);
//             cout << "next thing will be 1 " <<endl;

        }

        PROTODeserializer::~PROTODeserializer() { 
        }
       

        void PROTODeserializer::read(const uint32_t id, Serializable &s) {
          (void) id; //to be removed in the future
//           cout << " i am here " <<endl;
                stringstream ss;
                encode(ss,m_size);
                ss << m_buffer;
                ss >> s;
            }

        

        
        void PROTODeserializer::read(const uint32_t id, bool &b) {
                (void)id;
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
                b = v;
        }

        void PROTODeserializer::read(const uint32_t id, char &c) {
                (void)id;
                
                    
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
      }

        void PROTODeserializer::read(const uint32_t id, unsigned char &uc) {          (void)id;

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

        }

        void PROTODeserializer::read(const uint32_t id, int32_t &i) {
                (void)id;
                uint32_t size ;
                uint64_t key;
                size = decodeVar(m_buffer,key);
                m_size -=size;
                WIRE_TYPE wireType = getWireType(key);
                uint32_t fieldId = getFieldNumber(key);
                (void) wireType;
                (void) fieldId;
                uint64_t v;
                 
                size  = decodeVar(m_buffer,v);
                m_size -= size;
                i = (int32_t) v;

        }

        void PROTODeserializer::read(const uint32_t id, uint32_t &ui) {
                (void)id;
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
                ui = (uint32_t) v;
        }

        void PROTODeserializer::read(const uint32_t id, float &f) {
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
              
        }

        void PROTODeserializer::read(const uint32_t id, double &d) {
                (void) id;
                uint64_t key;
//                                 cout << " next will be 3 " << endl;

                 decodeVar(m_buffer,key);
//                 cout << " decode key size " << test_size<<endl;
                WIRE_TYPE wireType = getWireType(key);
                uint32_t fieldId = getFieldNumber(key);
//                 cout << " WIRE_TYPE "  << wireType << " fieldId " << fieldId << endl;
                (void) wireType;
                (void) fieldId;                
//                 cout << " key  Deserializer" << key<< endl;
//                 double _d =0;    
              m_size -=8;
                m_buffer.read(reinterpret_cast<char *>(&d),8); 

//                 cout << " dd " <<_d<<endl;
            //    d = _d;
        }

        void PROTODeserializer::read(const uint32_t id, string &s) {
                (void) id;
                uint64_t key;
                decodeVar(m_buffer,key);
                cout << "decoded string key " << key <<endl;
                WIRE_TYPE wireType = getWireType(key);
                uint32_t fieldId = getFieldNumber(key);
                (void) wireType;
                (void) fieldId;
                uint64_t size;
                uint32_t siz =  decodeVar(m_buffer, size );
                uint32_t length = (uint32_t) size ;
//                 length++;
                cout << "string length " <<  length << endl;
                char *str = new char[length+1];
                m_size -= length;
                m_size -= siz;
                m_buffer.read(reinterpret_cast<char *>(str), length);
                str[length] = '\0';
                cout << " raw string " << str <<endl;
                s = string(str, length);
                cout << " string string " << s << endl;
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
                if (magicNumber != 0xAABB){
                   if (in.good()) {
                    // Stream is good but still no magic number?
                    clog << "Stream corrupt: magic number not found. proto" << endl;
                    }
                return;                   
                }
                
                value  = 0 ;    
                decodeVar(in,value);
                
                uint16_t dataType = (uint16_t) value;
//                 cout << "datatype in container " << dataType <<endl;
                container.setDataType(static_cast<core::data::Container::DATATYPE>(dataType));
//                 uint64_t size;
//                 
//                 decodeVar(in, size);
                uint64_t readSize = 0;
//                 cout << "size decoded containe:" << size <<endl;
                char c = 0;
                in.get(c);
//                  in.get(c);
// //               
//                 in.get(c);
                while(in.good()){
                    m_buffer.put(c);
                    in.get(c);
                    readSize++;
                }
//                 cout <<"read size: "<<readSize<<endl;
       /* */        cout << "m_buffer size " << m_buffer.str().length()<<endl;
                container.setSerializedData(m_buffer.str());

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
