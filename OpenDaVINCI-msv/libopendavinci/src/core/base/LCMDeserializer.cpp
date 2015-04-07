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
			
			cout << "I AM INSIDE LCM DESERIALIZER " << endl;
			cout << " I got this istream data : "  << in << endl;
			
			uint8_t buf[4];
			
			in.read(reinterpret_cast<char*>(&buf), sizeof(uint32_t));
			cout << "buf[0]: " << buf[0] << endl;
			//in.read(reinterpret_cast<char*>(buf[1]), sizeof(uint8_t));
			cout << "buf[1]: " << buf[1] << endl;
			//in.read(reinterpret_cast<char*>(buf[2]), sizeof(uint8_t));
			cout << "buf[2]: " << buf[2] << endl;
			//in.read(reinterpret_cast<char*>(buf[3]), sizeof(uint8_t));
			cout << "buf[3]: " << buf[3] << endl;
			
			cout << "buf: " << buf << endl;
			
			int32_t p = 0;
			
			p = (((int32_t)buf[0])<<24) + (((int32_t)buf[1])<<16) + (((int32_t)buf[2])<<8) + ((int32_t)buf[3]);
			
			cout << "p: " << p << endl;
			
			
			uint8_t buf2[4];
			
			in.read(reinterpret_cast<char*>(&buf2), sizeof(uint32_t));
			cout << "buf2[0]: " << buf2[0] << endl;
			//in.read(reinterpret_cast<char*>(buf[1]), sizeof(uint8_t));
			cout << "buf2[1]: " << buf2[1] << endl;
			//in.read(reinterpret_cast<char*>(buf[2]), sizeof(uint8_t));
			cout << "buf2[2]: " << buf2[2] << endl;
			//in.read(reinterpret_cast<char*>(buf[3]), sizeof(uint8_t));
			cout << "buf2[3]: " << buf2[3] << endl;
			
			cout << "buf2: " << buf2 << endl;
			
			p = (((int32_t)buf2[0])<<24) + (((int32_t)buf2[1])<<16) + (((int32_t)buf2[2])<<8) + ((int32_t)buf2[3]);
			
			cout << "p: " << p << endl;
            
        }

        LCMDeserializer::~LCMDeserializer() {}

        void LCMDeserializer::read(const uint32_t id, Serializable &s) {
                cout << "Read Serializable Deserializer" << "- ID value: " << id <<" | Serializable value" << s << endl;
        }

        void LCMDeserializer::read(const uint32_t id, bool &b) {
              cout << "Read Bool Deserializer" << "- ID value: " << id <<" | Bool value" << b << endl ;
        }

        void LCMDeserializer::read(const uint32_t id, char &c) {
              cout << "Read char Deserializer" << "- ID value: " << id <<" | char  value: " << c << endl;
        }

        void LCMDeserializer::read(const uint32_t id, unsigned char &uc) {
             cout << "Read unsgined char Deserializer" << "- ID value: " << id <<"  | unsigned char  value: " << uc << endl;

        }

        void LCMDeserializer::read(const uint32_t id, int32_t &i) {
             cout << "Read int32_t Deserializer" << "- ID value: " << id <<" | int32_t  value: " << i << endl;

        }

        void LCMDeserializer::read(const uint32_t id, uint32_t &ui) {
            cout << "Read uint32_t Deserializer" << "- ID value: " << id <<" | uint32_t  value: " << ui << endl;

        }

        void LCMDeserializer::read(const uint32_t id, float &f) {
             cout << "Read float Deserializer" << "- ID value: " << id <<" < | float   value: " << f << endl;

        }

        void LCMDeserializer::read(const uint32_t id, double &d) {
              cout << "Read double Deserializer" << "- ID value: " << id <<" | double  value: " << d << endl;

        }

        void LCMDeserializer::read(const uint32_t id, string &s) {
              cout << "Read char Deserializer" << "- ID value: " << id <<" | string  value: " << s << endl;
        }

        void LCMDeserializer::read(const uint32_t id, void *data, uint32_t size) {
              cout << "Read data Deserializer" << "- ID value: " << id <<" |  data  value: " << data << " | size of data : "<< size << endl;

        }

    }
} // core::base
