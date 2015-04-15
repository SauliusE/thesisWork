/*
 * OpenDaVINCI.
 *
 * This software is open source. Please see COPYING and AUTHORS for further information.
 */

#include "core/base/LCMDeserializer.h"
#include "core/base/Serializable.h"

namespace core {
	namespace base {
		
		using namespace std;
		
		LCMDeserializer::LCMDeserializer(istream &in) :
			m_buffer(),
			m_values() {
			// Initialize the stringstream for getting valid positions when calling tellp().
			// This MUST be a blank (Win32 has a *special* implementation...)!
			m_buffer << " ";
			
			uint16_t magicNumber = 0;
			
			//Magic number
			uint8_t *magic = new uint8_t[2];
			in.read(reinterpret_cast<char*>(magic), sizeof(uint16_t));
			magicNumber = (((int16_t)magic[0])<<8) + ((int16_t)magic[1]);
			if (magicNumber != 0xAACF) {
				if (in.good()) {
					// Stream is good but still no magic number?
					clog << "Stream corrupt: magic number not found." << endl;
				}
				return;
			}
			
			// Decoding length of the payload.
			uint8_t *bufLength = new uint8_t[4];
			in.read(reinterpret_cast<char*>(bufLength), sizeof(uint32_t));
			uint32_t length = (((int32_t)bufLength[0])<<24) + (((int32_t)bufLength[1])<<16) + (((int32_t)bufLength[2])<<8) + ((int32_t)bufLength[3]);
			
			
			char c = 0;
			uint32_t tokenIdentifier = 0;
			uint32_t lengthOfPayload = 0;
			while (in.good() && (length > 0)) {
				// Start of next token by reading ID.
				uint8_t *tokenBuf = new uint8_t[4];;
				in.read(reinterpret_cast<char*>(tokenBuf), sizeof(uint32_t));
				tokenIdentifier = (((int32_t)tokenBuf[0])<<24) + (((int32_t)tokenBuf[1])<<16) + (((int32_t)tokenBuf[2])<<8) + ((int32_t)tokenBuf[3]);
				length -= (sizeof(uint32_t));
				
				// Read length of payload.
				uint8_t *lengthBuf = new uint8_t[4];;
				in.read(reinterpret_cast<char*>(lengthBuf), sizeof(uint32_t));
				lengthOfPayload = (((int32_t)lengthBuf[0])<<24) + (((int32_t)lengthBuf[1])<<16) + (((int32_t)lengthBuf[2])<<8) + ((int32_t)lengthBuf[3]);
				length -= (sizeof(uint32_t));
				
				// Create new (tokenIdentifier, m_buffer) hashmap entry.
				m_values.insert(make_pair(tokenIdentifier, m_buffer.tellp()));
				
				// Decode payload.
					for (uint32_t i = 0; i < lengthOfPayload; i++) {
						in.get(c);
						m_buffer.put(c);
						length--;
					}

			}
			
			// Check for trailing ','
            in.get(c);
            if (c != ',') {
                clog << "Stream corrupt: trailing ',' missing,  found: '" << c << "'" << endl;
            }
        }

        LCMDeserializer::~LCMDeserializer() {}

        void LCMDeserializer::read(const uint32_t id, Serializable &s) {
			map<uint32_t, streampos>::iterator it = m_values.find(id);
			
			if (it != m_values.end()) {
				m_buffer.seekg(it->second);
				m_buffer >> s;
			}
        }

        void LCMDeserializer::read(const uint32_t id, bool &b) {
			map<uint32_t, streampos>::iterator it = m_values.find(id);
			
			if (it != m_values.end()) {
				m_buffer.seekg(it->second);
				m_buffer.read(reinterpret_cast<char *>(&b), sizeof(bool));
			}
        }

        void LCMDeserializer::read(const uint32_t id, char &c) {
			map<uint32_t, streampos>::iterator it = m_values.find(id);
			
			if (it != m_values.end()) {
				m_buffer.seekg(it->second);
				m_buffer.read(&c, sizeof(char));
			}
        }

        void LCMDeserializer::read(const uint32_t id, unsigned char &uc) {
			map<uint32_t, streampos>::iterator it = m_values.find(id);
			
			if (it != m_values.end()) {
				m_buffer.seekg(it->second);
				m_buffer.read(reinterpret_cast<char *>(&uc), sizeof(unsigned char));
			}
        }

        void LCMDeserializer::read(const uint32_t id, int32_t &i) {
			map<uint32_t, streampos>::iterator it = m_values.find(id);
			
			if (it != m_values.end()) {
				uint8_t *buf = new uint8_t[4];
				
				m_buffer.seekg(it->second);
				m_buffer.read(reinterpret_cast<char *>(buf), sizeof(int32_t));
				i = (((int32_t)buf[0])<<24) + (((int32_t)buf[1])<<16) + (((int32_t)buf[2])<<8) + ((int32_t)buf[3]);
			}
			
        }

        void LCMDeserializer::read(const uint32_t id, uint32_t &ui) {
			map<uint32_t, streampos>::iterator it = m_values.find(id);
			
			if (it != m_values.end()) {
				uint8_t *buf = new uint8_t[4];
				
				m_buffer.seekg(it->second);
				m_buffer.read(reinterpret_cast<char *>(buf), sizeof(uint32_t));
				ui = (((int32_t)buf[0])<<24) + (((int32_t)buf[1])<<16) + (((int32_t)buf[2])<<8) + ((int32_t)buf[3]);
			}
        }

        void LCMDeserializer::read(const uint32_t id, float &f) {
			map<uint32_t, streampos>::iterator it = m_values.find(id);
			
			if (it != m_values.end()) {
				uint8_t *buf = new uint8_t[4];
				
				m_buffer.seekg(it->second);
				m_buffer.read(reinterpret_cast<char *>(buf), sizeof(float));
				f = (((int32_t)buf[0])<<24) + (((int32_t)buf[1])<<16) + (((int32_t)buf[2])<<8) + ((int32_t)buf[3]);
			}
        }

        void LCMDeserializer::read(const uint32_t id, double &d) {
			map<uint32_t, streampos>::iterator it = m_values.find(id);
			
			if (it != m_values.end()) {
				uint8_t *buf = new uint8_t[8];
				
				m_buffer.seekg(it->second);
				m_buffer.read(reinterpret_cast<char *>(buf), sizeof(double));
				d = (((int64_t)buf[0])<<56) + (((int64_t)buf[1])<<48) + (((int64_t)buf[2])<<40) + (((int64_t)buf[3])<<32) + (((int64_t)buf[4])<<24) + (((int64_t)buf[5])<<16) + (((int64_t)buf[6])<<8) + ((int64_t)buf[7]);
			}
        }

        void LCMDeserializer::read(const uint32_t id, string &s) {
			//cout << "Read char Deserializer" << "- ID value: " << id <<" | string  value: " << s << endl;
			
			map<uint32_t, streampos>::iterator it = m_values.find(id);
			
			if (it != m_values.end()) {
				m_buffer.seekg(it->second);
				uint8_t *stringLengthBuf = new uint8_t[4];
				m_buffer.read(reinterpret_cast<char *>(stringLengthBuf), sizeof(uint32_t));
				
				uint32_t stringLength = (((int32_t)stringLengthBuf[0])<<24) + (((int32_t)stringLengthBuf[1])<<16) + (((int32_t)stringLengthBuf[2])<<8) + ((int32_t)stringLengthBuf[3]);
				char *str = new char[stringLength+1];
				m_buffer.read(reinterpret_cast<char *>(str), static_cast<uint32_t>(stringLength));
				str[stringLength] = '\0';
				// It is absolutely necessary to specify the size of the serialized string, otherwise, s contains only data until the first '\0' is read.
				s = string(str, stringLength);
				OPENDAVINCI_CORE_DELETE_ARRAY(str);
			}
        }

        void LCMDeserializer::read(const uint32_t id, void *data, uint32_t size) {
			map<uint32_t, streampos>::iterator it = m_values.find(id);
			
			if (it != m_values.end()) {
				m_buffer.seekg(it->second);
				m_buffer.read(reinterpret_cast<char*>(data), size);
			}
        }

    }
} // core::base
