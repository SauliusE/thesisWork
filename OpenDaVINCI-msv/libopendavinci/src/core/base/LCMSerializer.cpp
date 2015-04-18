/*
* OpenDaVINCI.
*
* This software is open source. Please see COPYING and AUTHORS for further information.
*/

#include "core/base/LCMSerializer.h"
#include "core/base/Serializable.h"
//#include "core/data/Container.h"


namespace core {
	namespace base {
		
		using namespace std;
		using namespace core::data;
		
		LCMSerializer::LCMSerializer(ostream& out) :
				m_out(out),
				m_buffer() {}
		
		LCMSerializer::~LCMSerializer() {
			uint16_t magicNumber = 0xAACF;
			uint32_t v;
			
			// Write Magic Number
			uint8_t *magic = new uint8_t[2];
			v = magicNumber;
			magic[0] = (v>>8)&0xff;
			magic[1] = (v & 0xff);
			m_out.write(reinterpret_cast<const char *>(magic), sizeof(uint16_t));
			
			// Write Length
			uint8_t *length = new uint8_t[4];
			v = static_cast<uint32_t>(m_buffer.str().length());
			length[0] = (v>>24)&0xff;
			length[1] = (v>>16)&0xff;
			length[2] = (v>>8)&0xff;
			length[3] = (v & 0xff);
			m_out.write(reinterpret_cast<const char *>(length), sizeof(uint32_t));

			
			m_out << m_buffer.str();
			
			
			m_out << ",";
			
		} // end of deconstructor
		
		void LCMSerializer::write ( const uint32_t id, const Serializable& s ) {
			uint8_t *idbuf = new uint8_t[4];
			int32_t v = id;
			
			idbuf[0] = (v>>24)&0xff;
			idbuf[1] = (v>>16)&0xff;
			idbuf[2] = (v>>8)&0xff;
			idbuf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(idbuf), sizeof(uint32_t));
			
			stringstream buffer;
			buffer << s;
			
			uint8_t *sizebuf = new uint8_t[4];
			v = static_cast<uint32_t>(buffer.str().length());;
			
			sizebuf[0] = (v>>24)&0xff;
			sizebuf[1] = (v>>16)&0xff;
			sizebuf[2] = (v>>8)&0xff;
			sizebuf[3] = (v & 0xff);
			
            m_buffer.write(reinterpret_cast<const char*>(sizebuf), sizeof(uint32_t));
			
			m_buffer << buffer.str();

		}
	
	
		void LCMSerializer::write ( const uint32_t id, const bool& b ) {
			uint8_t *idbuf = new uint8_t[4];
			int32_t v = id;
			
			idbuf[0] = (v>>24)&0xff;
			idbuf[1] = (v>>16)&0xff;
			idbuf[2] = (v>>8)&0xff;
			idbuf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(idbuf), sizeof(uint32_t));
			
			uint8_t *sizebuf = new uint8_t[4];
			v = static_cast<uint32_t>(sizeof(b));;
			
			sizebuf[0] = (v>>24)&0xff;
			sizebuf[1] = (v>>16)&0xff;
			sizebuf[2] = (v>>8)&0xff;
			sizebuf[3] = (v & 0xff);
			
            m_buffer.write(reinterpret_cast<const char*>(sizebuf), sizeof(uint32_t));
			
			m_buffer.write(reinterpret_cast<const char *>(&b), sizeof(const bool));
		}
		
		void LCMSerializer::write ( const uint32_t id, const char& c ) {
			uint8_t *idbuf = new uint8_t[4];
			int32_t v = id;
			
			idbuf[0] = (v>>24)&0xff;
			idbuf[1] = (v>>16)&0xff;
			idbuf[2] = (v>>8)&0xff;
			idbuf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(idbuf), sizeof(uint32_t));
			
			uint8_t *sizebuf = new uint8_t[4];
			v = static_cast<uint32_t>(sizeof(c));
			
			sizebuf[0] = (v>>24)&0xff;
			sizebuf[1] = (v>>16)&0xff;
			sizebuf[2] = (v>>8)&0xff;
			sizebuf[3] = (v & 0xff);
			
            m_buffer.write(reinterpret_cast<const char*>(sizebuf), sizeof(uint32_t));
			
			m_buffer.write(&c, sizeof(const char));
		}
		
		void LCMSerializer::write ( const uint32_t id, const unsigned char& uc ) {
			uint8_t *idbuf = new uint8_t[4];
			int32_t v = id;
			
			idbuf[0] = (v>>24)&0xff;
			idbuf[1] = (v>>16)&0xff;
			idbuf[2] = (v>>8)&0xff;
			idbuf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(idbuf), sizeof(uint32_t));
			
			uint8_t *sizebuf = new uint8_t[4];
			v = static_cast<uint32_t>(sizeof(uc));
			
			sizebuf[0] = (v>>24)&0xff;
			sizebuf[1] = (v>>16)&0xff;
			sizebuf[2] = (v>>8)&0xff;
			sizebuf[3] = (v & 0xff);
			
            m_buffer.write(reinterpret_cast<const char*>(sizebuf), sizeof(uint32_t));
			
			m_buffer.write(reinterpret_cast<const char *>(&uc), sizeof(const unsigned char));

		}
		void LCMSerializer::write ( const uint32_t id, const int32_t& i ) {
			// calculate hash for ID = membername , typeof(i) = typename;
			hash = calculate_hash(hash,id);


			uint8_t *idbuf = new uint8_t[4];
			int32_t v = id;
			
			idbuf[0] = (v>>24)&0xff;
			idbuf[1] = (v>>16)&0xff;
			idbuf[2] = (v>>8)&0xff;
			idbuf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(idbuf), sizeof(uint32_t));
			
			uint8_t *sizebuf = new uint8_t[4];
			v = static_cast<uint32_t>(sizeof(i));
			
			sizebuf[0] = (v>>24)&0xff;
			sizebuf[1] = (v>>16)&0xff;
			sizebuf[2] = (v>>8)&0xff;
			sizebuf[3] = (v & 0xff);
			
            m_buffer.write(reinterpret_cast<const char*>(sizebuf), sizeof(uint32_t));
			
			uint8_t *buf = new uint8_t[4];
			v = i;
			
			buf[0] = (v>>24)&0xff;
			buf[1] = (v>>16)&0xff;
			buf[2] = (v>>8)&0xff;
			buf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(buf), sizeof(const uint32_t));
		}
		
		void LCMSerializer::write ( const uint32_t id, const uint32_t& ui ) {
			uint8_t *idbuf = new uint8_t[4];
			int32_t v = id;
			
			idbuf[0] = (v>>24)&0xff;
			idbuf[1] = (v>>16)&0xff;
			idbuf[2] = (v>>8)&0xff;
			idbuf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(idbuf), sizeof(uint32_t));
			
			uint8_t *sizebuf = new uint8_t[4];
			v = static_cast<uint32_t>(sizeof(ui));
			
			sizebuf[0] = (v>>24)&0xff;
			sizebuf[1] = (v>>16)&0xff;
			sizebuf[2] = (v>>8)&0xff;
			sizebuf[3] = (v & 0xff);
			
            m_buffer.write(reinterpret_cast<const char*>(sizebuf), sizeof(uint32_t));
			
			uint8_t *buf = new uint8_t[4];
			v = ui;
			
			buf[0] = (v>>24)&0xff;
			buf[1] = (v>>16)&0xff;
			buf[2] = (v>>8)&0xff;
			buf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(buf), sizeof(const uint32_t));
		}
		
		void LCMSerializer::write ( const uint32_t id, const float& f ) {
			uint8_t *idbuf = new uint8_t[4];
			int32_t v = id;
			
			idbuf[0] = (v>>24)&0xff;
			idbuf[1] = (v>>16)&0xff;
			idbuf[2] = (v>>8)&0xff;
			idbuf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(idbuf), sizeof(uint32_t));
			
			uint8_t *sizebuf = new uint8_t[4];
			v = static_cast<uint32_t>(sizeof(f));
			
			sizebuf[0] = (v>>24)&0xff;
			sizebuf[1] = (v>>16)&0xff;
			sizebuf[2] = (v>>8)&0xff;
			sizebuf[3] = (v & 0xff);
			
            m_buffer.write(reinterpret_cast<const char*>(sizebuf), sizeof(uint32_t));
			
			uint8_t *buf = new uint8_t[4];
			v = f;
			
			buf[0] = (v>>24)&0xff;
			buf[1] = (v>>16)&0xff;
			buf[2] = (v>>8)&0xff;
			buf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(buf), sizeof(const float));
		}

		void LCMSerializer::write ( const uint32_t id, const double& d ) {
			uint8_t *idbuf = new uint8_t[4];
			int64_t v = id;
			
			idbuf[0] = (v>>24)&0xff;
			idbuf[1] = (v>>16)&0xff;
			idbuf[2] = (v>>8)&0xff;
			idbuf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(idbuf), sizeof(uint32_t));
			
			uint8_t *sizebuf = new uint8_t[4];
			v = static_cast<uint32_t>(sizeof(d));
			
			sizebuf[0] = (v>>24)&0xff;
			sizebuf[1] = (v>>16)&0xff;
			sizebuf[2] = (v>>8)&0xff;
			sizebuf[3] = (v & 0xff);
			
            m_buffer.write(reinterpret_cast<const char*>(sizebuf), sizeof(uint32_t));
			
			uint8_t *buf = new uint8_t[8];
			v = d;
			
			buf[0] = (v>>56)&0xff;
			buf[1] = (v>>48)&0xff;
			buf[2] = (v>>40)&0xff;
			buf[3] = (v>>32)&0xff;
			buf[4] = (v>>24)&0xff;
			buf[5] = (v>>16)&0xff;
			buf[6] = (v>>8)&0xff;
			buf[7] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(buf), sizeof(const double));
		}
		void LCMSerializer::write ( const uint32_t id, const string& s ) {
			uint8_t *idbuf = new uint8_t[4];
			int32_t v = id;
			
			idbuf[0] = (v>>24)&0xff;
			idbuf[1] = (v>>16)&0xff;
			idbuf[2] = (v>>8)&0xff;
			idbuf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(idbuf), sizeof(uint32_t));
			
			uint32_t length = s.length();
			uint8_t *sizebuf = new uint8_t[4];
			v = static_cast<uint32_t>(length + sizeof(uint32_t));
			
			sizebuf[0] = (v>>24)&0xff;
			sizebuf[1] = (v>>16)&0xff;
			sizebuf[2] = (v>>8)&0xff;
			sizebuf[3] = (v & 0xff);
			
            m_buffer.write(reinterpret_cast<const char*>(sizebuf), sizeof(uint32_t));
			
			
			uint8_t *buf = new uint8_t[4];
			v = length;
			
			buf[0] = (v>>24)&0xff;
			buf[1] = (v>>16)&0xff;
			buf[2] = (v>>8)&0xff;
			buf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(buf), sizeof(uint32_t));
			m_buffer.write(reinterpret_cast<const char *>(s.c_str()), length);
		}

		void LCMSerializer::write ( const uint32_t id, const void* data, const uint32_t& size ) {
			uint8_t *idbuf = new uint8_t[4];
			int32_t v = id;
			
			idbuf[0] = (v>>24)&0xff;
			idbuf[1] = (v>>16)&0xff;
			idbuf[2] = (v>>8)&0xff;
			idbuf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(idbuf), sizeof(uint32_t));

			uint32_t realSize = size;
			uint8_t *sizebuf = new uint8_t[4];
			v = static_cast<uint32_t>(sizeof(realSize));
			
			sizebuf[0] = (v>>24)&0xff;
			sizebuf[1] = (v>>16)&0xff;
			sizebuf[2] = (v>>8)&0xff;
			sizebuf[3] = (v & 0xff);
			
            m_buffer.write(reinterpret_cast<const char*>(sizebuf), sizeof(uint32_t));
			m_buffer.write(reinterpret_cast<const char*>(data), size);
		}

		void write( const uint32_t id, Container &con){
			(void) id;
			(void) con;
			cout << "deserializing container" <<endl;

			//write magic number
			//sequence
			//channel name
			// '\0'
			// hash
			// payload


























		}

	} 
} // core:base

