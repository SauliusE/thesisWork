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

        PROTODeserializer::PROTODeserializer(istream &in) :
                m_buffer(),
                m_values() {
            // Initialize the stringstream for getting valid positions when calling tellp().
            // This MUST be a blank (Win32 has a *special* implementation...)!
                
                cout << "I AM INSIDE LCM DESERIALIZER " << endl;
                cout << " I got this istream data : "  << in << endl;
            
        }

        PROTODeserializer::~PROTODeserializer() {}

        void PROTODeserializer::read(const uint32_t id, Serializable &s) {
                cout << "Read Serializable Deserializer" << "- ID value: " << id <<" | Serializable value" << s <<endl ;
        }

        void PROTODeserializer::read(const uint32_t id, bool &b) {
              cout << "Read Bool Deserializer" << "- ID value: " << id <<" | Bool value" << b <<endl ;
        }

        void PROTODeserializer::read(const uint32_t id, char &c) {
              cout << "Read char Deserializer" << "- ID value: " << id <<" | char  value: " << c <<endl;
        }

        void PROTODeserializer::read(const uint32_t id, unsigned char &uc) {
             cout << "Read unsgined char Deserializer" << "- ID value: " << id <<"  | unsigned char  value: " << uc <<endl;

        }

        void PROTODeserializer::read(const uint32_t id, int32_t &i) {
             cout << "Read int32_t Deserializer" << "- ID value: " << id <<" | int32_t  value: " << i <<endl;

        }

        void PROTODeserializer::read(const uint32_t id, uint32_t &ui) {
            cout << "Read uint32_t Deserializer" << "- ID value: " << id <<" | uint32_t  value: " << ui <<endl;

        }

        void PROTODeserializer::read(const uint32_t id, float &f) {
             cout << "Read float Deserializer" << "- ID value: " << id <<" < | float   value: " << f <<endl;

        }

        void PROTODeserializer::read(const uint32_t id, double &d) {
              cout << "Read double Deserializer" << "- ID value: " << id <<" | double  value: " << d <<endl;

        }

        void PROTODeserializer::read(const uint32_t id, string &s) {
              cout << "Read char Deserializer" << "- ID value: " << id <<" | string  value: " << s <<endl;
        }

        void PROTODeserializer::read(const uint32_t id, void *data, uint32_t size) {
              cout << "Read data Deserializer" << "- ID value: " << id <<" |  data  value: " << data << " | size of data : "<< size <<endl;

        }

    }
} // core::base
