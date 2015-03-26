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
            uint32_t id = 1; // sequence_number
           cout << magicHeader << "bla " << id << endl;
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
             uint32_t _id = id;
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            stringstream buffer;
            buffer << s;

            uint32_t size = static_cast<uint32_t>(buffer.str().length());
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            m_buffer << buffer.str();

        }
    
    
        void LCMSerializer::write ( const uint32_t id, const bool& b ) {
uint32_t _id = id;
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(b));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));
            m_buffer.write(reinterpret_cast<const char *>(&b), sizeof(const bool));
        }
        
        void LCMSerializer::write ( const uint32_t id, const char& c ) {
    uint32_t _id = id;
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(c));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));
            m_buffer.write(&c, sizeof(const char));
        }
        
        void LCMSerializer::write ( const uint32_t id, const unsigned char& uc ) {
                 uint32_t _id = id;
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(uc));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));
            m_buffer.write(reinterpret_cast<const char *>(&uc), sizeof(const unsigned char));

        }
        void LCMSerializer::write ( const uint32_t id, const int32_t& i ) {
  uint32_t _id = id;
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(i));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            int32_t _i = i;
            _i = htonl(_i);
            m_buffer.write(reinterpret_cast<const char *>(&_i), sizeof(const uint32_t));
        }
        
        void LCMSerializer::write ( const uint32_t id, const uint32_t& ui ) {
 uint32_t _id = id;
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(ui));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            uint32_t _ui = ui;
            _ui = htonl(_ui);
            m_buffer.write(reinterpret_cast<const char *>(&_ui), sizeof(const uint32_t));
        }
        
        void LCMSerializer::write ( const uint32_t id, const float& f ) {
       uint32_t _id = id;
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(f));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            float _f = f;
            _f = Serializer::htonf(_f);
            m_buffer.write(reinterpret_cast<const char *>(&_f), sizeof(const float));
        }

        void LCMSerializer::write ( const uint32_t id, const double& d ) {
    uint32_t _id = id;
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t size = static_cast<uint32_t>(sizeof(d));
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char*>(&size), sizeof(uint32_t));

            double _d = d;
            _d = Serializer::htond(_d);
            m_buffer.write(reinterpret_cast<const char *>(&_d), sizeof(const double));
            }
        void LCMSerializer::write ( const uint32_t id, const string& s ) {
  uint32_t _id = id;
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t stringLength = s.length();
            uint32_t size = static_cast<uint32_t>(stringLength + sizeof(uint32_t)); // String's length plus the length of the type for (string's length).
            size = htonl(size);
            m_buffer.write(reinterpret_cast<const char *>(&size), sizeof(uint32_t));

            uint32_t _stringLength = stringLength;
            _stringLength = htonl(_stringLength);
            m_buffer.write(reinterpret_cast<const char *>(&_stringLength), sizeof(uint32_t));
            m_buffer.write(reinterpret_cast<const char *>(s.c_str()), stringLength);
            }

        void LCMSerializer::write ( const uint32_t id, const void* data, const uint32_t& size ) {
 uint32_t _id = id;
            _id = htonl(_id);
            m_buffer.write(reinterpret_cast<const char *>(&_id), sizeof(uint32_t));

            uint32_t realSize = size;
            realSize = htonl(realSize);
            m_buffer.write(reinterpret_cast<const char*>(&realSize), sizeof(uint32_t));
            m_buffer.write(reinterpret_cast<const char*>(data), size);
            }

        } 
} // core:base

  