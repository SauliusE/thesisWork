/*
* OpenDaVINCI.
*
* This software is open source. Please see COPYING and AUTHORS for further information.
*/

#include "core/base/LCMSerializer.h"
//#include "core/base/Serializable.h"
//#include "core/data/Container.h"

#include <typeinfo>


namespace core {
	namespace base {
		
		using namespace std;
	//	using namespace core::data;
		
		LCMSerializer::LCMSerializer(ostream& out) :
				m_out(out),
				m_buffer(),
				m_hash(0x12345678)
				{}
		
		LCMSerializer::~LCMSerializer() {
		//	cout << "hash " << getHash()<< endl
			m_out << m_buffer.str();
		} // end of deconstructor

		//Set and get method for hash
		void LCMSerializer::setHash(const int64_t hash){
			payload_hash = hash;
		}

		int64_t LCMSerializer::getHash(){
			return this->m_hash;
		}

		void LCMSerializer::write ( const uint32_t id, const Serializable& s ) {

			(void) id;
		//	uint32_t _id = id;
		//	m_hash = hash_string(m_hash, reinterpret_cast<char*>(&_id));
		//	m_hash = hash_string(m_hash, typeid(s).name());

			stringstream buffer;
			buffer << s;
			cout << "i am here !!!!"<<endl;
			
			m_buffer << buffer.str();
			cout << "end of here" <<endl;
			
		}
	
	
		void LCMSerializer::write ( const uint32_t id, const bool& b ) {

			uint32_t _id = id;
			m_hash = hash_string(m_hash, reinterpret_cast<char*>(&_id));
			m_hash = hash_string(m_hash, typeid(b).name());
			
			m_buffer.write(reinterpret_cast<const char *>(&b), sizeof(const bool));

		}
		
		void LCMSerializer::write ( const uint32_t id, const char& c ) {

			uint32_t _id = id;
			m_hash = hash_string(m_hash, reinterpret_cast<char*>(&_id));
			m_hash = hash_string(m_hash, typeid(c).name());
			
			m_buffer.write(&c, sizeof(const char));


		}
		
		void LCMSerializer::write ( const uint32_t id, const unsigned char& uc ) {
			uint32_t _id = id;
			m_hash = hash_string(m_hash, reinterpret_cast<char*>(&_id));
			m_hash = hash_string(m_hash, typeid(uc).name());
			
			m_buffer.write(reinterpret_cast<const char *>(&uc), sizeof(const unsigned char));



		}
		
		void LCMSerializer::write ( const uint32_t id, const int32_t& i ) {
			uint32_t _id = id;
			m_hash = hash_string(m_hash, reinterpret_cast<char*>(&_id));
			m_hash = hash_string(m_hash, typeid(i).name());
			
			uint8_t buf[4];
			int32_t v = i;
			
			buf[0] = (v>>24)&0xff;
			buf[1] = (v>>16)&0xff;
			buf[2] = (v>>8)&0xff;
			buf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(&buf[0]), sizeof(const uint8_t));
			m_buffer.write(reinterpret_cast<const char *>(&buf[1]), sizeof(const uint8_t));
			m_buffer.write(reinterpret_cast<const char *>(&buf[2]), sizeof(const uint8_t));
			m_buffer.write(reinterpret_cast<const char *>(&buf[3]), sizeof(const uint8_t));



		}
		
		void LCMSerializer::write ( const uint32_t id, const uint32_t& ui ) {

			uint32_t _id = id;
			m_hash = hash_string(m_hash, reinterpret_cast<char*>(&_id));
			m_hash = hash_string(m_hash, typeid(ui).name());
			
			uint8_t buf[4];
			int32_t v = ui;
			
			buf[0] = (v>>24)&0xff;
			buf[1] = (v>>16)&0xff;
			buf[2] = (v>>8)&0xff;
			buf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(&buf[0]), sizeof(const uint8_t));
			m_buffer.write(reinterpret_cast<const char *>(&buf[1]), sizeof(const uint8_t));
			m_buffer.write(reinterpret_cast<const char *>(&buf[2]), sizeof(const uint8_t));
			m_buffer.write(reinterpret_cast<const char *>(&buf[3]), sizeof(const uint8_t));



		}
		
		void LCMSerializer::write ( const uint32_t id, const float& f ) {
			uint32_t _id = id;
			m_hash = hash_string(m_hash, reinterpret_cast<char*>(&_id));
			m_hash = hash_string(m_hash, typeid(f).name());
			
			uint8_t buf[4];
			int32_t v = f;
			
			buf[0] = (v>>24)&0xff;
			buf[1] = (v>>16)&0xff;
			buf[2] = (v>>8)&0xff;
			buf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(&buf[0]), sizeof(const uint8_t));
			m_buffer.write(reinterpret_cast<const char *>(&buf[1]), sizeof(const uint8_t));
			m_buffer.write(reinterpret_cast<const char *>(&buf[2]), sizeof(const uint8_t));
			m_buffer.write(reinterpret_cast<const char *>(&buf[3]), sizeof(const uint8_t));



		}

		void LCMSerializer::write ( const uint32_t id, const double& d ) {

			uint32_t _id = id;
			m_hash = hash_string(m_hash, reinterpret_cast<char*>(&_id));
			m_hash = hash_string(m_hash, typeid(d).name());
			
			uint8_t buf[8];
			uint64_t v = d;
			
			buf[0] = (v>>56)&0xff;
			buf[1] = (v>>48)&0xff;
			buf[2] = (v>>40)&0xff;
			buf[3] = (v>>32)&0xff;
			buf[4] = (v>>24)&0xff;
			buf[5] = (v>>16)&0xff;
			buf[6] = (v>>8)&0xff;
			buf[7] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(&buf[0]), sizeof(const uint8_t));
			m_buffer.write(reinterpret_cast<const char *>(&buf[1]), sizeof(const uint8_t));
			m_buffer.write(reinterpret_cast<const char *>(&buf[2]), sizeof(const uint8_t));
			m_buffer.write(reinterpret_cast<const char *>(&buf[3]), sizeof(const uint8_t));
			m_buffer.write(reinterpret_cast<const char *>(&buf[4]), sizeof(const uint8_t));
			m_buffer.write(reinterpret_cast<const char *>(&buf[5]), sizeof(const uint8_t));
			m_buffer.write(reinterpret_cast<const char *>(&buf[6]), sizeof(const uint8_t));
			m_buffer.write(reinterpret_cast<const char *>(&buf[7]), sizeof(const uint8_t));



		}
		void LCMSerializer::write ( const uint32_t id, const string& s ) {

			uint32_t _id = id;
			m_hash = hash_string(m_hash, reinterpret_cast<char*>(&_id));
			m_hash = hash_string(m_hash, typeid(s).name());

			char* cstr = (char*) s.c_str();
			int32_t length1 = strlen(cstr) + 1;
			
			uint8_t lengthBuf[4];
			int32_t v = length1;
				cout << "string lenght in the write function " << length1 << endl;
			lengthBuf[0] = (v>>24)&0xff;
			lengthBuf[1] = (v>>16)&0xff;
			lengthBuf[2] = (v>>8)&0xff;
			lengthBuf[3] = (v & 0xff);
			m_buffer.write(reinterpret_cast<const char *>(&lengthBuf), sizeof(const int32_t));
			
			m_buffer.write(reinterpret_cast<const char *>(&cstr), length1);


		}

		void LCMSerializer::write ( const uint32_t id, const void* data, const uint32_t& size ) {
			
			uint32_t _id = id;
			m_hash = hash_string(m_hash, reinterpret_cast<char*>(&_id));
			m_hash = hash_string(m_hash, typeid(data).name());
			
			m_buffer.write(reinterpret_cast<const char*>(&data), size);

		}

		void LCMSerializer::write(core::data::Container &container){

			cout << "serializing container" <<endl;

			cout <<"write magic number"<<endl;
			  uint32_t magicNumber = 0x4c433032;
			  uint8_t mnbuf[4];
			  mnbuf[0] = (magicNumber>>24)&0xff;
			  mnbuf[1] = (magicNumber>>16)&0xff;
			  mnbuf[2] = (magicNumber>>8)&0xff;
			  mnbuf[3] = (magicNumber & 0xff);

			  m_out.write(reinterpret_cast<const char *>(&mnbuf[0]), sizeof(const uint8_t));
			  m_out.write(reinterpret_cast<const char *>(&mnbuf[1]), sizeof(const uint8_t));
			  m_out.write(reinterpret_cast<const char *>(&mnbuf[2]), sizeof(const uint8_t));
			  m_out.write(reinterpret_cast<const char *>(&mnbuf[3]), sizeof(const uint8_t));

			  cout << "write sequence "<< endl;
			  //sequence
			  uint32_t sequence = 0;

			  uint8_t seqbuf[4];
			  seqbuf[0] = (sequence>>24)&0xff;
			  seqbuf[1] = (sequence>>16)&0xff;
			  seqbuf[2] = (sequence>>8)&0xff;
			  seqbuf[3] = (sequence & 0xff);

			  m_out.write(reinterpret_cast<const char *>(&seqbuf[0]), sizeof(const uint8_t));
			  m_out.write(reinterpret_cast<const char *>(&seqbuf[1]), sizeof(const uint8_t));
			  m_out.write(reinterpret_cast<const char *>(&seqbuf[2]), sizeof(const uint8_t));
			  m_out.write(reinterpret_cast<const char *>(&seqbuf[3]), sizeof(const uint8_t));

			  cout << "channel name" <<endl;
			   //Channel name
			   string channel;
			   stringstream ss;
			   int chan = container.getDataType();
			    ss << chan;
			    channel = ss.str();
			   char* cstr = (char*)  channel.c_str();
			   int32_t length = strlen(cstr) + 1;
				m_out.write(cstr, length);
				cout << "channel name" << channel <<endl;
				std::cout << "NULL terminator \0" <<endl;
				// '0'
				//const char* nullValue = '\0';
				m_out.write("0", sizeof(const uint8_t));

				cout << " writing hash" <<endl;
				// hash
				uint8_t hashbuf[8];
				m_hash = container.m_payloadHash;
				cout << "m_hash" <<  m_hash<<endl;
				hashbuf[0] = (m_hash>>56)&0xff;
				hashbuf[1] = (m_hash>>48)&0xff;
				hashbuf[2] = (m_hash>>40)&0xff;
				hashbuf[3] = (m_hash>>32)&0xff;
				hashbuf[4] = (m_hash>>24)&0xff;
				hashbuf[5] = (m_hash>>16)&0xff;
				hashbuf[6] = (m_hash>>8)&0xff;
				hashbuf[7] = (m_hash & 0xff);

				m_out.write(reinterpret_cast<const char *>(&hashbuf), sizeof(const uint64_t));

				cout << "writing payload"<<endl;
				// payload

				m_out << container.m_serializedData.str();
				cout << "end of  serializing container" <<endl;
		}
		
		int64_t calculate_hash(int64_t v, char c) {
			v = ((v<<8) ^ (v>>55)) + c;
			
			return v;
		}
		
		int64_t hash_string(int64_t v, const char *s) {
			v = calculate_hash(v, strlen(s));
			
			for(; *s != 0; s++)
				v = calculate_hash(v, *s);
			
			return v;
		}

	} 
} // core:base

