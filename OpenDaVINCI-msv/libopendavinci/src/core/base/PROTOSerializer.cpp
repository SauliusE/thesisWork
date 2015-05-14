/*
 * OpenDaVINCI.
 *
 * This software is open source. Please see COPYING and AUTHORS for further information.
 */

#include "core/base/PROTOSerializer.h"
#include "core/base/Serializable.h"
#include "endian.h"
#include "core/data/Container.h"
#include <typeinfo>
#include <boost/graph/graph_concepts.hpp>






namespace core {
    namespace base {
        
        using namespace std;
        
        PROTOSerializer::PROTOSerializer(ostream& out) :
                m_out(out),
                m_buffer(),
                m_size(0){
                }
        
        PROTOSerializer::~PROTOSerializer(){
            // Here suppose to be finalized message based on PROTO approach, as far i know it is
            // It is : 
            // - > size of message
            // - > payload
            // Writing size of message
            
            //if m_size != 0 so we wrote something 
            // else it was write container
           
             stringstream asd ;
            if(m_size !=0 ){
//                 m_out.write(reinterpret_cast<const char *>(&m_size),sizeof(uint32_t));
//                 cout << "encoding m_size : " << m_size <<endl;
//                 uint64_t test = static_cast<uint64_t>(m_size);
//                 cout << "test " << test << endl;
//                 uint32_t encodesize = getVarSize(m_size);
                
//                 cout << " encode size " << encodesize << endl;
                stringstream ss ;
              encode(ss,m_size);
//               ss.clear();
//             cout << "decoding m_size " << endl;
//             uint64_t value;
           
            
//              m_buffer.clear();
//             m_out.seekg(0,ios_base::beg);
//            uint32_t decodesize = decodeVar(ss,value);
//            cout << " decode size " << decodesize << endl;
//            cout << " decode value " << value << endl;
//             m_size = static_cast<uint32_t>(value);
//             cout << " decoded value m_buffer " << m_size         << endl;
                m_out << ss.str();
//                 cout << " payload lenght lenght " << ss.str().length()<<endl;
                m_out << m_buffer.str();
//                  cout << "m_buffer lenght " << m_buffer.str().length()<<endl;
//                  cout << " message size in proto serializer when m_size != 0" <<m_size<< endl;
            }  
       
//               cout << " message size in proto serializer" <<m_size<< endl;
       
        } // end of ~constructor

        void PROTOSerializer::write ( const uint32_t id, const Serializable& s ) {
             // writing serializable
            (void)id;
            stringstream buffer;
            buffer << s;
            uint64_t size = 0;
            decodeVar(buffer,size);
//             buffer.read(reinterpret_cast<char*>(&size),sizeof(uint32_t));
            m_size += static_cast<uint32_t>(size);
            char c = 0;
            buffer.get(c);
            uint32_t counter = 0;
            while(buffer.good() && counter<size){
                m_buffer.put(c);
                buffer.get(c);
                counter++;
            }
            
            
        }
    
    
        void PROTOSerializer::write ( const uint32_t id, const bool& b ) {
                uint32_t sizeOFB = getVarSize(b);
//                 cout << " m_size in begining of bool " << m_size<< endl;
                m_size += sizeOFB;
                (void)id;
                PROTO_TYPE protoType = ( PROTO_TYPE )6;
                WIRE_TYPE wireType = getWireType( protoType) ;
                
                uint32_t key = getKey ( id, wireType );
                m_size += getVarSize(key);
  
                 encode(m_buffer,key);
                encode(m_buffer, b );
//                 cout << " m_size in bool " << m_size <<endl;
        }
        
        void PROTOSerializer::write ( const uint32_t id, const char& c ) {
               
                m_size += getVarSize(c);
                
                PROTO_TYPE protoType = ( PROTO_TYPE )6;
                WIRE_TYPE wireType = getWireType ( protoType) ;
                
                uint32_t key = getKey ( id, wireType );           
                m_size += getVarSize(key);
                
                encode(m_buffer,key);
                encode(m_buffer,c );
        }
        
        void PROTOSerializer::write ( const uint32_t id, const unsigned char& uc ) {
               
                m_size += getVarSize(uc);
                
                PROTO_TYPE protoType = ( PROTO_TYPE )6;
                WIRE_TYPE wireType = getWireType ( protoType) ;
                
                uint32_t key = getKey ( id, wireType );
                m_size += getVarSize(key);
                
                encode(m_buffer,key);
                encode(m_buffer, uc );
        }

        void PROTOSerializer::write ( const uint32_t id, const int32_t& i ) {
              
                m_size += getVarSize(i);
                
                PROTO_TYPE protoType = ( PROTO_TYPE )0;
                WIRE_TYPE wireType = getWireType ( protoType) ;
               
                uint32_t key = getKey ( id, wireType );
                m_size += getVarSize(key);
                
                encode(m_buffer,key);
                encode(m_buffer, i );
        }
        
        void PROTOSerializer::write ( const uint32_t id, const uint32_t& ui ) {
//                 cout << " Writing uint32_t " << ui <<endl;
//                 cout << " m_size in begning " << m_size <<endl;
                m_size += getVarSize(ui);
//                 cout << " m_size after UI " << m_size << endl;
                PROTO_TYPE protoType = ( PROTO_TYPE )2;
                WIRE_TYPE wireType = getWireType ( protoType) ;
               
                uint32_t key = getKey ( id, wireType );
//                 cout << " key is : " << key << endl;
                m_size += getVarSize(key);
//                 cout << " size after key << " <<m_size <<endl;
                encode(m_buffer,key);
                encode(m_buffer, ui );


        }
        
        void PROTOSerializer::write ( const uint32_t id, const float& f ) {
       
                float _f = f;
                m_size += 4;
//                 cout << " funcin float 2" <<endl;
                PROTO_TYPE protoType = ( PROTO_TYPE )4;
                WIRE_TYPE wireType = getWireType ( protoType) ;
                
                uint32_t key = getKey ( id, wireType );
                m_size += getVarSize(key);
                
                encode(m_buffer,key);
                m_buffer.write(reinterpret_cast<const char *>(&_f), 4);
       }

        void PROTOSerializer::write ( const uint32_t id, const double& d ) {
                double _d = d;
//               (void)id;
                m_size += 8;
                PROTO_TYPE protoType = ( PROTO_TYPE )5;
                WIRE_TYPE wireType = getWireType ( protoType) ;
//                  cout << "Double - protoType " << protoType << " WIRE_TYPE "<< wireType << "field id " << id<<endl;
                uint32_t key = getKey ( id, wireType );
//                 cout <<"message size "  << m_size<<endl;
                m_size += static_cast<uint32_t>(getVarSize(key));
//                 cout << " key size serializable ; " << static_cast<uint32_t>(getVarSize(key))<<endl; 
//                cout << " key  serializer" << key<< endl;
//                 cout << " Double  key " << key << endl;
                encode(m_buffer,key);
//                 cout << "double valuue "<< _d<<endl;
                m_buffer.write(reinterpret_cast<const char *>(&_d), 8);
//         cout << " m_size in double " << m_size<<endl;
//                 cout << " M_buffer lenght after double stuff " << m_size << " m_buffer.lenght : " <<m_buffer.str().length() <<endl;

        }
        void PROTOSerializer::write ( const uint32_t id, const string& s ) {

                PROTO_TYPE protoType = ( PROTO_TYPE )8;
                WIRE_TYPE wireType = getWireType ( protoType) ;
            
                uint32_t key = getKey ( id, wireType );
//               cout << " String key " << key << endl;
                encode(m_buffer,key);
                m_size += getVarSize(key);
              
                uint32_t stringSize = 0;
                stringSize = s.length() ;
                m_size += stringSize;
//                cout << " string size " << stringSize << endl;
                encode( m_buffer,stringSize );
//                  cout << " string " << s.c_str() <<endl;
                m_buffer.write ( reinterpret_cast<const char *>(s.c_str()), stringSize );  


        }

        void PROTOSerializer::write ( const uint32_t id, const void* data, const uint32_t& size ) {
            cout<< "Writing id: " << id << "of user data " << data << " size of it " << size << endl;
        }
    

    void PROTOSerializer::write (core::data::Container &container){
   
                uint16_t magicNumber = 0xAABB;
//                 cout << " magic number " <<magicNumber<<endl;
                uint32_t dataType = container.getDataType(); 
//                 cout << " data type " << dataType << endl;
                encode(m_out, magicNumber);
                encode(m_out, dataType); 
            
//                 uint32_t msgSize;
//                 stringstream ss;
//                 ss<< container.getSerializedData();
//                 ss.read(reinterpret_cast<char *>(&msgSize),sizeof(uint32_t));
//                 uint64_t value = 0;
//                 decodeVar(ss,value);
//                 msgSize = static_cast<uint32_t>
//                 cout << "encoding msg size " <<  msgSize <<endl;
//                 encode(m_out,msgSize);
//                 char c = 0;
//                 ss.get(c);
//                 int cs = 0;
//                 while(ss.good()){
//                     m_out.put(c);
//                     ss.get(c);
//                     cs++;
//                 }
//                 cout <<"lol"<< cs<<endl;
           m_out << container.getSerializedData();
                m_size = 0;
//                 cout << " END OF WRITING CONTAINER " <<endl;
//                 Serializing container
//                 -- write Message size -- uint32_t
//                 -- write Payload
//                 ----encode Key -- uint32_t
//                 ----encode value 
    }
    


    
    void PROTOSerializer::encode( ostream &out, uint64_t value){
  
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


    uint8_t PROTOSerializer::getVarSize( uint64_t value){
                uint8_t size = 0;
                value = htole64(value);
                
                    do {
                        
                        char byte = value & (uint8_t) 0x7F;
                        value >>=7;

                        if(value){
                            byte |= (uint8_t) 0x80;
                        }
                        ++size;
                
                    } while (value);

                    return size;
                }


    } 
    
    
uint32_t base::PROTOSerializer::decodeVar(std::istream& in, uint64_t& value)
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

        
base::PROTOSerializer::WIRE_TYPE base::PROTOSerializer::getWireType ( base::PROTOSerializer::PROTO_TYPE type )
{
switch ( type ) {
     case INT32:
          return VARINT;
     case INT64:
          return VARINT;
     case UINT32:
          return VARINT;
     case UINT64:
          return VARINT;
     case FLOAT:
          return BIT_32;
     case DOUBLE:
          return BIT_64;
     case BOOL:
          return VARINT;
     case STRING:
     case BYTES:
          return LENGTH_DELIMITED;
     default:
          return OTHER;
     }

}
} // core:base

  
