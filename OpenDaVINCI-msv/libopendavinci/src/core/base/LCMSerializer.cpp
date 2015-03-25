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
        
        LCMSerializer::LCMSerializer(std::ostream& out) :
                m_out(out),
                m_buffer() {}
        
        LCMSerializer::~LCMSerializer(){
            // Here suppose to be finnalized message based on LCM approach, as far i know it is
            // It is : 
            uint32_t magicHeader = 0x4c433032;
            uint32_t id; // sequence_number
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

        }
    
    
        void LCMSerializer::write ( const uint32_t id, const bool& b ) {

        }
        
        void LCMSerializer::write ( const uint32_t id, const char& c ) {

        }
        
        void LCMSerializer::write ( const uint32_t id, const unsigned char& uc ) {

        }
        void LCMSerializer::write ( const uint32_t id, const int32_t& i ) {

        }
        
        void LCMSerializer::write ( const uint32_t id, const uint32_t& ui ) {

        }
        
        void LCMSerializer::write ( const uint32_t id, const float& f ) {

        }

        void LCMSerializer::write ( const uint32_t id, const double& d ) {

            }
        void LCMSerializer::write ( const uint32_t id, const string& s ) {

            }

        void LCMSerializer::write ( const uint32_t id, const void* data, const uint32_t& size ) {

            }

        } 
} // core:base

  