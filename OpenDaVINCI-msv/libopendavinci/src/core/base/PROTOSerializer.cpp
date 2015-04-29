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



namespace core {
    namespace base {
        
        using namespace std;
        
        PROTOSerializer::PROTOSerializer(ostream& out) :
                m_out(out),
                m_buffer(),
                m_size(0){}
        
        PROTOSerializer::~PROTOSerializer(){
            // Here suppose to be finalized message based on PROTO approach, as far i know it is
            // It is : 
        	// - > size of message
        	// - > payload
			// Writing size of message
		  //writing buffer to m_out
		  		m_out << m_buffer.str();
				

        } // end of ~constructor

        void PROTOSerializer::write ( const uint32_t id, const Serializable& s ) {
             // writing serializable
		  // ?? PURPOSE OF THIS FUNCTION
		  (void)id;
             stringstream buffer;
             buffer << s;
			 m_buffer << buffer.str();
			  //cout<< "serializable" <<endl;

        }
    
    
        void PROTOSerializer::write ( const uint32_t id, const bool& b ) {
          //cout<< " Serialization of BOOLEAN. "<< endl;
          // writing boolean (bool is being encoded as Varint)
           //     uint64_t _b =  b ;
                uint32_t sizeOFB = getVarSize(b);
                cout << "boolean size " << sizeOFB << endl;
				m_size += sizeOFB;
				PROTO_TYPE protoType = ( PROTO_TYPE )6;
				WIRE_TYPE wireType = getWireType ( protoType) ;
				uint32_t key = getKey ( id, wireType );
				m_size += getVarSize(key);
                          cout << " serializer bool key --------------------------- " << key;

				encode(m_buffer,key);
                cout << "bool before Encoding " << b <<endl;
				encode(m_buffer, b );
				cout << "bool " << b <<endl;


        }
        
        void PROTOSerializer::write ( const uint32_t id, const char& c ) {
                  //cout<< " Serialization  of char. " <<endl;
             //   uint64_t _c =  c ;
				m_size += getVarSize(c);
				PROTO_TYPE protoType = ( PROTO_TYPE )6;
				WIRE_TYPE wireType = getWireType ( protoType) ;
				uint32_t key = getKey ( id, wireType );
				m_size += getVarSize(key);
				encode(m_buffer,key);
				encode(m_buffer,c );
				cout << "char " << c <<endl;
							  //cout<< "char" <<endl;

		}
        
        void PROTOSerializer::write ( const uint32_t id, const unsigned char& uc ) {
            //cout<< " Serialization of  unsigned char : "  << endl;
       //         uint64_t _uc =  uc ;
				m_size += getVarSize(uc);
				PROTO_TYPE protoType = ( PROTO_TYPE )6;
				WIRE_TYPE wireType = getWireType ( protoType) ;
				uint32_t key = getKey ( id, wireType );
				m_size += getVarSize(key);
				encode(m_buffer,key);
				encode(m_buffer, uc );
								//cout << "u char " << _uc <<endl;

					  //cout<< " unsigned char" <<endl;

        }

        void PROTOSerializer::write ( const uint32_t id, const int32_t& i ) {
          //cout<< "Serialization of int32 " <<endl;
                uint64_t _i =  i ;
				m_size += getVarSize(_i);
				PROTO_TYPE protoType = ( PROTO_TYPE )0;
				WIRE_TYPE wireType = getWireType ( protoType) ;
				uint32_t key = getKey ( id, wireType );
				m_size += getVarSize(key);
				encode(m_buffer,key);
				encode(m_buffer, _i );
    			  //cout<< " int " <<endl;
								cout << "int32" << _i <<endl;


        }
        
        void PROTOSerializer::write ( const uint32_t id, const uint32_t& ui ) {
                        cout<< " Serialization of uint32_t : "  << endl;
              //  uint64_t _ui = ui ;
	//			cout << "htole64"<<endl;
				m_size += getVarSize(ui);
	//			cout <<"var size " <<m_size <<endl;
				PROTO_TYPE protoType = ( PROTO_TYPE )2;
	//			cout << "PROTO_type " <<protoType<<endl;
				WIRE_TYPE wireType = getWireType ( protoType) ;
		//		cout <<"WIRE_TYPE"<<endl;
				uint32_t key = getKey ( id, wireType );
		//		cout << "key " << key <<endl;
				m_size += getVarSize(key);
	//			cout <<"var size " <<m_size <<endl;

				encode(m_buffer,key);
		//		cout <<"key encoded " <<endl;
				encode(m_buffer, ui );
			//	cout << "number encoded"<<endl;
				  cout<< " unsigned int" <<ui<< endl;

		}
        
        void PROTOSerializer::write ( const uint32_t id, const float& f ) {
			//cout<< "Writing id: " << id <<  " of float "  <<endl;
                //float asdd = f;
				//void& _f = (uint32_t*) &asdd;
                //cout << "asd value " << asdd << endl;
              //  cout << "_f value " << _f <<endl;
            // Writing id
            float _f = f;
         //     char* _f = reinterpret_cast<void*>(test);
				m_size += 4;
				PROTO_TYPE protoType = ( PROTO_TYPE )4;
				WIRE_TYPE wireType = getWireType ( protoType) ;
				uint32_t key = getKey ( id, wireType );
				m_size += getVarSize(key);
				encode(m_buffer,key);
                
               m_buffer.write(reinterpret_cast<const char *>(&_f), 4);

				//m_buffer.write(f,4);
                // m_buffer << f ;
	//			cout << "float " << _f<<endl;


	   }

        void PROTOSerializer::write ( const uint32_t id, const double& d ) {
			//cout<< " Writing id: " << id << " of double " <<endl;
			// Writing id
            double _d = d;
              
              //converting double to 
				m_size += 8;
				PROTO_TYPE protoType = ( PROTO_TYPE )5;
				WIRE_TYPE wireType = getWireType ( protoType) ;
				uint32_t key = getKey ( id, wireType );
				m_size += getVarSize(key);
				encode(m_buffer,key);
                 m_buffer.write(reinterpret_cast<const char *>(&_d), 8);

			//	m_buffer.write( ( char* ) _d, 8);
				//  cout<< "double " <<_d <<endl;

        }
        void PROTOSerializer::write ( const uint32_t id, const string& s ) {
			//cout<< "Writing id: " << id << "of string "  << endl;
			// Writing id
			     
			  // writing string
			//  void* _s = (string*) &s;
			  PROTO_TYPE protoType = ( PROTO_TYPE )8;
			  WIRE_TYPE wireType = getWireType ( protoType) ;
			  uint32_t key = getKey ( id, wireType );
			  encode(m_buffer,key);
			 uint32_t stringSize = 0;
             stringSize = s.size();
			  m_size += stringSize;
                cout << " Encoding string size . which is : " << stringSize << endl;
			  encode( m_buffer,stringSize );
              m_buffer.write ( s.c_str(), stringSize+1 );			  //cout<< "string" <<endl;
			  cout << "string " << s.c_str()<<endl;



		}

        void PROTOSerializer::write ( const uint32_t id, const void* data, const uint32_t& size ) {
			cout<< "Writing id: " << id << "of user data " << data << " size of it " << size << endl;
		}
	

	void PROTOSerializer::write (core::data::Container &container){
	  cout << "container" <<endl;
          uint16_t magicNumber = 0xAABB;
	  uint16_t dataType = container.getDataType();  
	  encode(m_out, magicNumber);
      cout << " ------------------------------------------encoded magicNumber " << magicNumber<< endl;
	  encode(m_out, dataType); 
      uint32_t msgSize = container.getMessageSize();
	  m_out << msgSize;
	  cout << "Container data type " <<  container.getDataType() << endl;
	  cout << "message size " << msgSize;
	  m_out << container.m_serializedData.str();
		// Serializing container
		// -- write Message size -- uint32_t
		// -- write Payload
		// ----encode Key -- uint32_t
		// ----encode value 
	}
	
	void print_bytes(const void *object, size_t size)
{
  size_t i;

  
  for(i = 0; i < size; i++)
  {
    printf("%02x ", ((const unsigned char *) object)[i] & 0xff);
  }

}


	
	void PROTOSerializer::encode( ostream &out, uint64_t value){
                   cout << " printing byte of value  " << value << endl;

	       value = htole64( value);
           cout << " printing byte of value  " << value << endl;
		do {printf("[ ");

		    char byte = value & (uint8_t) 0x7F;
    		    value >>= 7;
	
	    	if ( value) {
		    byte |= ( uint8_t ) 0x80;
		}
	     print_bytes(&byte, sizeof(byte));
		out.put( byte );
        
		} while (value);
         printf("]\n"); 
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

  
