/*
 * OpenDaVINCI.
 *
 * This software is open source. Please see COPYING and AUTHORS for further information.
 */

#include "core/base/PROTOSerializer.h"
#include "core/base/Serializable.h"


namespace core {
    namespace base {
        
        using namespace std;
        
        PROTOSerializer::PROTOSerializer(ostream& out) :
                m_out(out),
                m_buffer() {}
        
        PROTOSerializer::~PROTOSerializer(){
            // Here suppose to be finnalized message based on LCM approach, as far i know it is
            // It is : 
            cout << "created PROTOserializer" << endl;

        } // end of deconstructor

        void PROTOSerializer::write ( const uint32_t id, const Serializable& s ) {
             cout << "Writing id " << id << " and serialize " << s << endl;

        }
    
    
        void PROTOSerializer::write ( const uint32_t id, const bool& b ) {
			cout << "Writing id " << id  << " of boolean " << b << endl;
        }
        
        void PROTOSerializer::write ( const uint32_t id, const char& c ) {
			cout << "Writing id : " << id << " of char " << c << endl;
		}
        
        void PROTOSerializer::write ( const uint32_t id, const unsigned char& uc ) {
            cout << "Writing id : " << id << " of unsigned char : " << uc << endl;
        }
        void PROTOSerializer::write ( const uint32_t id, const int32_t& i ) {
			cout << "Writing id : " << id << " of int32 " <<  i << endl;
        }
        
        void PROTOSerializer::write ( const uint32_t id, const uint32_t& ui ) {
			cout << "Writing id : " << id << " of uint32_t : "  << ui << endl;
		}
        
        void PROTOSerializer::write ( const uint32_t id, const float& f ) {
			cout << "Writing id: " << id <<  " of float " << f <<endl;
	   }

        void PROTOSerializer::write ( const uint32_t id, const double& d ) {
			cout << " Writing id: " << id << " of double " << d<<endl;
        }
        void PROTOSerializer::write ( const uint32_t id, const string& s ) {
			cout << "Writing id: " << id << "of string " << s << endl;
		}

        void PROTOSerializer::write ( const uint32_t id, const void* data, const uint32_t& size ) {
			cout << "Writing id: " << id << "of user data " << data << " size of it " << size << endl;
		}

        } 
} // core:base

  
