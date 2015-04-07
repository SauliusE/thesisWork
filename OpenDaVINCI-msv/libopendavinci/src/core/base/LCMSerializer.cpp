/*
* OpenDaVINCI.
*
* This software is open source. Please see COPYING and AUTHORS for further information.
*/

#include "core/base/LCMSerializer.h"
#include "core/base/Serializable.h"


namespace core {
	namespace base {
		
		using namespace std;
		
		LCMSerializer::LCMSerializer(ostream& out) :
				m_out(out),
				m_buffer() {}
		
		LCMSerializer::~LCMSerializer(){
			// Here suppose to be finnalized message based on LCM approach, as far i know it is
			// It is : 
			cout << "created LCM serializer" << endl;
			uint32_t magicHeader = 0x4c433032;
			uint32_t id = 6575338; // sequence_number
			cout << "magic: "<< magicHeader << "\nid: " << id << endl;
			
			uint8_t buf[4];
			
			int32_t v = magicHeader;
			buf[0] = (v>>24)&0xff;
			buf[1] = (v>>16)&0xff;
			buf[2] = (v>>8)&0xff;
			buf[3] = (v & 0xff);
			
			cout << "buf: " << buf << endl;
			
			m_out.write(reinterpret_cast<const char *>(&buf), sizeof(uint32_t));
			
			
			uint8_t buf2[4];
			
			v = id;
			buf2[0] = (v>>24)&0xff;
			buf2[1] = (v>>16)&0xff;
			buf2[2] = (v>>8)&0xff;
			buf2[3] = (v & 0xff);
			
			m_out.write(reinterpret_cast<const char *>(&buf2), sizeof(uint32_t));
			
			
			m_out << m_buffer;
			
			m_out << ",";
			
			
/*                                   === Small messages ===
*
*               A small message is defined as one where the LCM small message header, channel name, and the payload can fit into a single UDP datagram.  While this can technically be up to 64 kb, in practice the current LCM implementations limit this to 1400 bytes (to stay under the Ethernet MTU).
*
*               The header for a small message is 8 bytes long and has the following form:
*
*               {{{
*               0      7 8     15 16    23 24    31 
*                +--------+--------+--------+--------+
*                | short_header_magic                |
*                +--------+--------+--------+--------+
*                | sequence_number                   |
*                +--------+--------+--------+--------+
*                }}}
*
*               {{{short_header_magic}}} is an unsigned 32-bit integer with value  {{{0x4c433032}}}.
*
*              {{{sequence_number}}} is a monotonically increasing (subject to integer wraparound) unsigned 32-bit number identifying the message.
*
*               Both values are encoded in network byte order (Big-Endian).
*
*               The header is followed by the null-terminated UTF-8 encoding of the channel name.
*
*                The channel name is followed by the payload.
*/
			
		} // end of deconstructor
		
		void LCMSerializer::write ( const uint32_t id, const Serializable& s ) {
			uint8_t idbuf[4];
			int32_t v = id;
			
			idbuf[0] = (v>>24)&0xff;
			idbuf[1] = (v>>16)&0xff;
			idbuf[2] = (v>>8)&0xff;
			idbuf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(&idbuf), sizeof(uint32_t));
			
			stringstream buffer;
			buffer << s;
			
			uint32_t size = static_cast<uint32_t>(buffer.str().length());
			size = htonl(size);
			m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));
			
			m_buffer << buffer.str();

		}
	
	
		void LCMSerializer::write ( const uint32_t id, const bool& b ) {
			uint8_t idbuf[4];
			int32_t v = id;
			
			idbuf[0] = (v>>24)&0xff;
			idbuf[1] = (v>>16)&0xff;
			idbuf[2] = (v>>8)&0xff;
			idbuf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(&idbuf), sizeof(uint32_t));
			
			m_buffer.write(reinterpret_cast<const char *>(&b), sizeof(const bool));
		}
		
		void LCMSerializer::write ( const uint32_t id, const char& c ) {
			uint8_t idbuf[4];
			int32_t v = id;
			
			idbuf[0] = (v>>24)&0xff;
			idbuf[1] = (v>>16)&0xff;
			idbuf[2] = (v>>8)&0xff;
			idbuf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(&idbuf), sizeof(uint32_t));
			
			m_buffer.write(&c, sizeof(const char));
		}
		
		void LCMSerializer::write ( const uint32_t id, const unsigned char& uc ) {
			uint8_t idbuf[4];
			int32_t v = id;
			
			idbuf[0] = (v>>24)&0xff;
			idbuf[1] = (v>>16)&0xff;
			idbuf[2] = (v>>8)&0xff;
			idbuf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(&idbuf), sizeof(uint32_t));
			
			m_buffer.write(reinterpret_cast<const char *>(&uc), sizeof(const unsigned char));

		}
		void LCMSerializer::write ( const uint32_t id, const int32_t& i ) {
			uint8_t idbuf[4];
			int32_t v = id;
			
			idbuf[0] = (v>>24)&0xff;
			idbuf[1] = (v>>16)&0xff;
			idbuf[2] = (v>>8)&0xff;
			idbuf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(&idbuf), sizeof(uint32_t));

			uint8_t buf[4];
			v = i;
			
			buf[0] = (v>>24)&0xff;
			buf[1] = (v>>16)&0xff;
			buf[2] = (v>>8)&0xff;
			buf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(&buf), sizeof(uint32_t));
		}
		
		void LCMSerializer::write ( const uint32_t id, const uint32_t& ui ) {
			uint8_t idbuf[4];
			int32_t v = id;
			
			idbuf[0] = (v>>24)&0xff;
			idbuf[1] = (v>>16)&0xff;
			idbuf[2] = (v>>8)&0xff;
			idbuf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(&idbuf), sizeof(uint32_t));
			
			uint8_t buf[4];
			v = ui;
			
			buf[0] = (v>>24)&0xff;
			buf[1] = (v>>16)&0xff;
			buf[2] = (v>>8)&0xff;
			buf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(&buf), sizeof(uint32_t));
		}
		
		void LCMSerializer::write ( const uint32_t id, const float& f ) {
			uint8_t idbuf[4];
			int32_t v = id;
			
			idbuf[0] = (v>>24)&0xff;
			idbuf[1] = (v>>16)&0xff;
			idbuf[2] = (v>>8)&0xff;
			idbuf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(&idbuf), sizeof(uint32_t));

			uint8_t buf[4];
			v = f;
			
			buf[0] = (v>>24)&0xff;
			buf[1] = (v>>16)&0xff;
			buf[2] = (v>>8)&0xff;
			buf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(&buf), sizeof(uint32_t));
		}

		void LCMSerializer::write ( const uint32_t id, const double& d ) {
			uint8_t idbuf[4];
			int64_t v = id;
			
			idbuf[0] = (v>>24)&0xff;
			idbuf[1] = (v>>16)&0xff;
			idbuf[2] = (v>>8)&0xff;
			idbuf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(&idbuf), sizeof(uint32_t));

			uint8_t buf[8];
			v = d;
			
			buf[0] = (v>>56)&0xff;
			buf[1] = (v>>48)&0xff;
			buf[2] = (v>>40)&0xff;
			buf[3] = (v>>32)&0xff;
			buf[4] = (v>>24)&0xff;
			buf[5] = (v>>16)&0xff;
			buf[6] = (v>>8)&0xff;
			buf[7] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(&buf), sizeof(uint64_t));
		}
		void LCMSerializer::write ( const uint32_t id, const string& s ) {
			uint8_t idbuf[4];
			int32_t v = id;
			
			idbuf[0] = (v>>24)&0xff;
			idbuf[1] = (v>>16)&0xff;
			idbuf[2] = (v>>8)&0xff;
			idbuf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(&idbuf), sizeof(uint32_t));

			int32_t length = s.length() + 1; // length includes \0
			
			uint8_t buf[4];
			v = length;
			
			buf[0] = (v>>24)&0xff;
			buf[1] = (v>>16)&0xff;
			buf[2] = (v>>8)&0xff;
			buf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(&buf), sizeof(uint32_t));
			m_buffer.write(reinterpret_cast<const char *>(&s), sizeof(uint8_t));
		}

		void LCMSerializer::write ( const uint32_t id, const void* data, const uint32_t& size ) {
			uint8_t idbuf[4];
			int32_t v = id;
			
			idbuf[0] = (v>>24)&0xff;
			idbuf[1] = (v>>16)&0xff;
			idbuf[2] = (v>>8)&0xff;
			idbuf[3] = (v & 0xff);
			
			m_buffer.write(reinterpret_cast<const char *>(&idbuf), sizeof(uint32_t));

			uint32_t realSize = size;
			realSize = htonl(realSize);
			m_buffer.write(reinterpret_cast<const char*>(&realSize), sizeof(uint32_t));
			m_buffer.write(reinterpret_cast<const char*>(data), size);
			}

		} 
} // core:base

	