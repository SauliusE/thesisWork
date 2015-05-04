/*
 * OpenDaVINCI.
 *
 * This software is open source. Please see COPYING and AUTHORS for further information.
 */

#include "core/base/ROSSerializer.h"
#include "core/base/Serializable.h"
#include "endian.h"
#include "core/data/Container.h"
#include <typeinfo>



namespace core {
    namespace base {
        
        using namespace std;
        
        ROSSerializer::ROSSerializer(ostream& out) :
                m_out(out),
                m_buffer(),
                m_size(0){}
        
        ROSSerializer::~ROSSerializer(){
            // Here suppose to be finalized message based on ROS approach, as far i know it is
            // It is : 
            // - > size of message
            // - > payload
            // Writing size of message
            m_out << m_buffer.str();
       
        } // end of ~constructor

        void ROSSerializer::write ( const uint32_t id, const Serializable& s ) {
             // writing serializable
            (void)id;
            stringstream buffer;
            buffer << s;
            m_buffer << buffer.str();
        }
    
    
        void ROSSerializer::write ( const uint32_t id, const bool& b ) {
                uint32_t sizeOFB = getVarSize(b);
                m_size += sizeOFB;
                
                ROS_TYPE protoType = ( ROS_TYPE )6;
                WIRE_TYPE wireType = getWireType ( protoType) ;
                
                uint32_t key = getKey ( id, wireType );
                m_size += getVarSize(key);
  
                encode(m_buffer,key);
                encode(m_buffer, b );
        }
        
        void ROSSerializer::write ( const uint32_t id, const char& c ) {
               
                m_size += getVarSize(c);
                
                ROS_TYPE protoType = ( ROS_TYPE )6;
                WIRE_TYPE wireType = getWireType ( protoType) ;
                
                uint32_t key = getKey ( id, wireType );           
                m_size += getVarSize(key);
                
                encode(m_buffer,key);
                encode(m_buffer,c );
        }
        
        void ROSSerializer::write ( const uint32_t id, const unsigned char& uc ) {
               
                m_size += getVarSize(uc);
                
                ROS_TYPE protoType = ( ROS_TYPE )6;
                WIRE_TYPE wireType = getWireType ( protoType) ;
                
                uint32_t key = getKey ( id, wireType );
                m_size += getVarSize(key);
                
                encode(m_buffer,key);
                encode(m_buffer, uc );
        }

        void ROSSerializer::write ( const uint32_t id, const int32_t& i ) {
              
                m_size += getVarSize(i);
                
                ROS_TYPE protoType = ( ROS_TYPE )0;
                WIRE_TYPE wireType = getWireType ( protoType) ;
               
                uint32_t key = getKey ( id, wireType );
                m_size += getVarSize(key);
                
                encode(m_buffer,key);
                encode(m_buffer, i );
        }
        
        void ROSSerializer::write ( const uint32_t id, const uint32_t& ui ) {

                m_size += getVarSize(ui);
                
                ROS_TYPE protoType = ( ROS_TYPE )2;
                WIRE_TYPE wireType = getWireType ( protoType) ;
               
                uint32_t key = getKey ( id, wireType );
                m_size += getVarSize(key);

                encode(m_buffer,key);
                encode(m_buffer, ui );


        }
        
        void ROSSerializer::write ( const uint32_t id, const float& f ) {
       
                float _f = f;
                m_size += 4;
                
                ROS_TYPE protoType = ( ROS_TYPE )4;
                WIRE_TYPE wireType = getWireType ( protoType) ;
                
                uint32_t key = getKey ( id, wireType );
                m_size += getVarSize(key);
                
                encode(m_buffer,key);
                m_buffer.write(reinterpret_cast<const char *>(&_f), 4);
       }

        void ROSSerializer::write ( const uint32_t id, const double& d ) {

                double _d = d;
              
                m_size += 8;
                ROS_TYPE protoType = ( ROS_TYPE )5;
                WIRE_TYPE wireType = getWireType ( protoType) ;
               
                uint32_t key = getKey ( id, wireType );
                m_size += getVarSize(key);
               
                encode(m_buffer,key);
                m_buffer.write(reinterpret_cast<const char *>(&_d), 8);


        }
        void ROSSerializer::write ( const uint32_t id, const string& s ) {

                ROS_TYPE protoType = ( ROS_TYPE )8;
                WIRE_TYPE wireType = getWireType ( protoType) ;
            
                uint32_t key = getKey ( id, wireType );
                encode(m_buffer,key);
              
                uint32_t stringSize = 0;
                stringSize = (s.size() + 1) ;
                m_size += stringSize;
              
                encode( m_buffer,stringSize );
                m_buffer.write ( s.c_str(), stringSize );  


        }

        void ROSSerializer::write ( const uint32_t id, const void* data, const uint32_t& size ) {
            cout<< "Writing id: " << id << "of user data " << data << " size of it " << size << endl;
        }
    

    void ROSSerializer::write (core::data::Container &container){
   
                uint16_t magicNumber = 0xAABB;
                uint16_t dataType = container.getDataType();  
                encode(m_out, magicNumber);
                encode(m_out, dataType); 
            
                uint32_t msgSize = container.m_message_size;
                m_out << msgSize;
                m_out << container.m_serializedData.str();
//                 Serializing container
//                 -- write Message size -- uint32_t
//                 -- write Payload
//                 ----encode Key -- uint32_t
//                 ----encode value 
    }
    


    
    void ROSSerializer::encode( ostream &out, uint64_t value){
  
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


    uint8_t ROSSerializer::getVarSize( uint64_t value){
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
        
base::ROSSerializer::WIRE_TYPE base::ROSSerializer::getWireType ( base::ROSSerializer::ROS_TYPE type )
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

  
