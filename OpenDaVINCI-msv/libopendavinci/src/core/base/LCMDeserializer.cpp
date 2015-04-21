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
		
		LCMDeserializer::LCMDeserializer(istream &in):
			m_buffer(),
			m_values() {
			// Initialize the stringstream for getting valid positions when calling tellp().
			// This MUST be a blank (Win32 has a *special* implementation...)!
			
			// Magic number
			cout << "TESST" << endl;
			uint8_t magicBuf[4];
			in.read(reinterpret_cast<char*>(&magicBuf), sizeof(uint32_t));
			int32_t magicNumber = (((int32_t)magicBuf[0])<<24) + (((int32_t)magicBuf[1])<<16) + (((int32_t)magicBuf[2])<<8) + ((int32_t)magicBuf[3]);
			if (magicNumber != 0x4c433032) {
				if (in.good()) {
					// Stream is good but still no magic number?
					clog << "Stream corrupt: magic number not found." << endl;
				}
				cout << "FUKKK" << endl;
				return;
			}
			
			// Decoding the seq_number.
			uint8_t seqBuf[4];
			in.read(reinterpret_cast<char*>(&seqBuf), sizeof(uint32_t));
			int32_t msg_seq = (((int32_t)seqBuf[0])<<24) + (((int32_t)seqBuf[1])<<16) + (((int32_t)seqBuf[2])<<8) + ((int32_t)seqBuf[3]);
			(void) msg_seq;
			
			// Decoding channel
			char channel[256];
			int channel_len = 0;
			char ch = 0;
			in.get(ch);
			cout << "CH_CHAR1: " << ch << endl;
			
			while (ch != '0') {
				channel[channel_len++] = ch;
				in.get(ch);
				cout << "CH_CHAR: " << ch << endl;
			}
			
			channel[channel_len] = 0;
			cout << "channel!!!!: " << channel << endl;
			
			uint8_t hashBuf[8];
			in.read(reinterpret_cast<char*>(&hashBuf), sizeof(uint64_t));
			int64_t hash = (((int64_t)seqBuf[0])<<56) + (((int64_t)seqBuf[1])<<48) + (((int64_t)seqBuf[2])<<40) + (((int64_t)seqBuf[3])<<32) + (((int64_t)seqBuf[4])<<24) + (((int64_t)seqBuf[5])<<16) + (((int64_t)seqBuf[6])<<8) + ((int64_t)seqBuf[7]);
			(void) hash;
			
			cout << "DEHASH: " << hash << endl;
			/*
			if (hash != 0x0e65ec258fc2e665LL) {
				return;
			}
			*/
			
			char c = 0;
			while (in.good()) {
				in.get(c);
				m_buffer.put(c);
			}
        }

        LCMDeserializer::~LCMDeserializer() {}

        void LCMDeserializer::read(const uint32_t id, Serializable &s) {
			(void) id;
			m_buffer >> s;
        }

        void LCMDeserializer::read(const uint32_t id, bool &b) {
			(void) id;
			m_buffer.read(reinterpret_cast<char *>(&b), sizeof(bool));
        }

        void LCMDeserializer::read(const uint32_t id, char &c) {
			(void) id;
			m_buffer.read(&c, sizeof(char));
        }

        void LCMDeserializer::read(const uint32_t id, unsigned char &uc) {
			(void) id;
			m_buffer.read(reinterpret_cast<char *>(&uc), sizeof(unsigned char));
        }

        void LCMDeserializer::read(const uint32_t id, int32_t &i) {
			(void) id;
			uint8_t buf[4];
			m_buffer.read(reinterpret_cast<char *>(&buf), sizeof(int32_t));
			i = (((int32_t)buf[0])<<24) + (((int32_t)buf[1])<<16) + (((int32_t)buf[2])<<8) + ((int32_t)buf[3]);
        }

        void LCMDeserializer::read(const uint32_t id, uint32_t &ui) {
			(void) id;
			uint8_t buf[4];
			m_buffer.read(reinterpret_cast<char *>(&buf), sizeof(uint32_t));
			ui = (((int32_t)buf[0])<<24) + (((int32_t)buf[1])<<16) + (((int32_t)buf[2])<<8) + ((int32_t)buf[3]);
        }

        void LCMDeserializer::read(const uint32_t id, float &f) {
			(void) id;
			uint8_t buf[4];
			m_buffer.read(reinterpret_cast<char *>(&buf), sizeof(float));
			f = (((int32_t)buf[0])<<24) + (((int32_t)buf[1])<<16) + (((int32_t)buf[2])<<8) + ((int32_t)buf[3]);
        }

        void LCMDeserializer::read(const uint32_t id, double &d) {
			(void) id;
			uint8_t buf[4];
			m_buffer.read(reinterpret_cast<char *>(&buf), sizeof(double));
			d = (((int64_t)buf[0])<<56) + (((int64_t)buf[1])<<48) + (((int64_t)buf[2])<<40) + (((int64_t)buf[3])<<32) + (((int64_t)buf[4])<<24) + (((int64_t)buf[5])<<16) + (((int64_t)buf[6])<<8) + ((int64_t)buf[7]);
        }

        void LCMDeserializer::read(const uint32_t id, string &s) {
			(void) id;
			uint8_t lengthBuf[4];
			m_buffer.read(reinterpret_cast<char *>(&lengthBuf), sizeof(int32_t));
			int32_t length = (((int32_t)lengthBuf[0])<<24) + (((int32_t)lengthBuf[1])<<16) + (((int32_t)lengthBuf[2])<<8) + ((int32_t)lengthBuf[3]);
			
			cout << "STRING LENGTH: " << length << endl;
			cout << "STRING1" << endl;
			m_buffer.read(reinterpret_cast<char *>(&s), length);
			cout << "STRING2: " << s << endl;
        }

        void LCMDeserializer::read(const uint32_t id, void *data, uint32_t size) {
			(void) id;
			m_buffer.read(reinterpret_cast<char*>(data), size);
        }

    }
} // core::base
