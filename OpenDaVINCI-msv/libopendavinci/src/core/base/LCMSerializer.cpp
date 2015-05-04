/*
* OpenDaVINCI.
*
* This software is open source. Please see COPYING and AUTHORS for further information.
*/

#include "core/base/LCMSerializer.h"
//#include "core/base/Serializable.h"
//#include "core/data/Container.h"

#include <inttypes.h>
#include <string>


namespace core {
    namespace base {
        
        using namespace std;
        
        LCMSerializer::LCMSerializer(ostream& out) :
            m_out(out),
            m_buffer(),
            m_hash(0x12345678) {}
        
        LCMSerializer::~LCMSerializer() {
            // Writes the hash number and the payload to the ostream which will then get written to the container stream
            if (m_hash != 0x12345678) {
                m_hash = (m_hash<<1) + ((m_hash>>63)&1);
                
                uint8_t hashbuf[8];
                hashbuf[0] = (m_hash>>56)&0xff;
                hashbuf[1] = (m_hash>>48)&0xff;
                hashbuf[2] = (m_hash>>40)&0xff;
                hashbuf[3] = (m_hash>>32)&0xff;
                hashbuf[4] = (m_hash>>24)&0xff;
                hashbuf[5] = (m_hash>>16)&0xff;
                hashbuf[6] = (m_hash>>8)&0xff;
                hashbuf[7] = (m_hash & 0xff);
                m_out.write(reinterpret_cast<const char *>(&hashbuf), sizeof(const int64_t));   
            }
            
            m_out << m_buffer.str();
        }

        // Set and get method for hash
        void LCMSerializer::setHash(const int64_t hash){
            m_hash = hash;
        }

        int64_t LCMSerializer::getHash(){
            return m_hash;
        }
        
        /*
         * The write functions below are called to encode and write variables to a stringstream buffer.
         * The variables will be written to the buffer in the order the write functions are called.
         * 
         * A hash number is also generated based on the names and the types of the variables that are being written.
         * This hash number is not used in OpenDaVINCI. It is only used by LCM.
         * 
         * For single byte variables, they are just written to the buffer without any encoding.
         * For others, the bytes of a variable are stored into a uint8_t buffer and the buffer is then written to the stream.
         */
        
        
        // This is for nested data, that is, data which is also part of "serializableData"
        void LCMSerializer::write ( const uint32_t id, const Serializable& s ) {
            (void) id;
            stringstream buffer;
            buffer << s;
            m_buffer << buffer.str();
        }
        
        
        // TO QUIET WARNINGS
        
        void LCMSerializer::write( const uint32_t id, const bool &b ) {
            (void) id;
            (void) b;
        }

        void LCMSerializer::write( const uint32_t id, const char &c ) {
            (void) id;
            (void) c;
        }

        void LCMSerializer::write( const uint32_t id, const unsigned char &uc ) {
            (void) id;
            (void) uc;
        }

        void LCMSerializer::write( const uint32_t id, const int32_t &i ) {
            (void) id;
            (void) i;
        }

        void LCMSerializer::write( const uint32_t id, const uint32_t &ui ) {
            (void) id;
            (void) ui;
        }

        void LCMSerializer::write( const uint32_t id, const float &f ) {
            (void) id;
            (void) f;
        }

        void LCMSerializer::write( const uint32_t id, const double &d ) {
            (void) id;
            (void) d;
        }

        void LCMSerializer::write( const uint32_t id, const string &s ) {
            (void) id;
            (void) s;
        }

        void LCMSerializer::write( const uint32_t id, const void *data, const uint32_t &size ) {
            (void) id;
            (void) data;
            (void) size;
        }
        
        
        
        // REAL WRITE FUNCTIONS
        
        
        // Bool
        void LCMSerializer::write ( const string id, const bool& b ) {
            char* _id = (char *) id.c_str();
            m_hash = hash_string(m_hash, reinterpret_cast<const char *>(_id));
            m_hash = hash_string(m_hash, "boolean");
            m_hash = calculate_hash(m_hash, 0);
            
            m_buffer.write(reinterpret_cast<const char *>(&b), sizeof(const bool));
        }
        
        /*
         * Char
         * 
         * Not supported by LCM, but just keeping it here just incase.
         */
        void LCMSerializer::write ( const string id, const char& c ) {
            char* _id = (char *) id.c_str();
            m_hash = hash_string(m_hash, reinterpret_cast<const char *>(_id));
            m_hash = hash_string(m_hash, "char");
            m_hash = calculate_hash(m_hash, 0);
            
            m_buffer.write(&c, sizeof(const char));
        }
        
        /*
         * Unsigned Char
         * 
         * Not supported by LCM, but just keeping it here just incase.
         */
        void LCMSerializer::write ( const string id, const unsigned char& uc ) {
            char* _id = (char *) id.c_str();
            m_hash = hash_string(m_hash, reinterpret_cast<const char *>(_id));
            m_hash = hash_string(m_hash, "unsigned char");
            m_hash = calculate_hash(m_hash, 0);
            
            m_buffer.write(reinterpret_cast<const char *>(&uc), sizeof(const unsigned char));
        }
        
        // int32_t
        void LCMSerializer::write ( const string id, const int32_t& i ) {
            char* _id = (char *) id.c_str();
            m_hash = hash_string(m_hash, reinterpret_cast<const char *>(_id));
            m_hash = hash_string(m_hash, "int32_t");
            m_hash = calculate_hash(m_hash, 0);
            
            uint8_t buf[4];
            int32_t v = i;
            buf[0] = (v>>24)&0xff;
            buf[1] = (v>>16)&0xff;
            buf[2] = (v>>8)&0xff;
            buf[3] = (v & 0xff);
            m_buffer.write(reinterpret_cast<const char *>(&buf), sizeof(const uint32_t));
        }
        
        /*
         * uint32_t
         * 
         * Not supported by LCM, but just keeping it here just incase.
         */
        
        void LCMSerializer::write ( const string id, const uint32_t& ui ) {
            char* _id = (char *) id.c_str();
            m_hash = hash_string(m_hash, reinterpret_cast<const char *>(_id));
            m_hash = hash_string(m_hash, "uint32_t");
            m_hash = calculate_hash(m_hash, 0);
            
            uint8_t buf[4];
            int32_t v = ui;
            buf[0] = (v>>24)&0xff;
            buf[1] = (v>>16)&0xff;
            buf[2] = (v>>8)&0xff;
            buf[3] = (v & 0xff);
            m_buffer.write(reinterpret_cast<const char *>(&buf), sizeof(const uint32_t));
        }
        
        // Float
        void LCMSerializer::write ( const string id, const float& f ) {
            char* _id = (char *) id.c_str();
            m_hash = hash_string(m_hash, reinterpret_cast<const char *>(_id));
            m_hash = hash_string(m_hash, "float");
            m_hash = calculate_hash(m_hash, 0);
            
            // This way of encoding is taken straight from LCM.
            // Don't even know how and why it works myself.
            float _f = f;
            float *ff = &_f;
            int64_t *p = (int64_t*) ff;
            
            uint8_t buf[4];
            int32_t v = p[0];
            buf[0] = (v>>24)&0xff;
            buf[1] = (v>>16)&0xff;
            buf[2] = (v>>8)&0xff;
            buf[3] = (v & 0xff);
            m_buffer.write(reinterpret_cast<const char *>(&buf), sizeof(const uint32_t));
        }
        
        // Double
        void LCMSerializer::write ( const string id, const double& d ) {
            char* _id = (char *) id.c_str();
            m_hash = hash_string(m_hash, reinterpret_cast<const char *>(_id));
            m_hash = hash_string(m_hash, "double");
            m_hash = calculate_hash(m_hash, 0);
            
            // This way of encoding is taken straight from LCM.
            // Don't even know how and why it works myself.
            double _d = d;
            double *dd = &_d;
            int64_t *p = (int64_t*) dd;
            
            uint8_t buf[8];
            int64_t v = p[0];
            buf[0] = (v>>56)&0xff;
            buf[1] = (v>>48)&0xff;
            buf[2] = (v>>40)&0xff;
            buf[3] = (v>>32)&0xff;
            buf[4] = (v>>24)&0xff;
            buf[5] = (v>>16)&0xff;
            buf[6] = (v>>8)&0xff;
            buf[7] = (v & 0xff);
            m_buffer.write(reinterpret_cast<const char *>(&buf), sizeof(const uint64_t));
        }
        
        /*
         * A string is encoded by first converting the string to a char*.
         * The length of the string, including the '\0', is encoded and written to the buffer
         * and then the char* is written to the buffer.
         */
        
        // String
        void LCMSerializer::write ( const string id, const string& s ) {
            char* _id = (char *) id.c_str();
            m_hash = hash_string(m_hash, reinterpret_cast<const char *>(_id));
            m_hash = hash_string(m_hash, "string");
            m_hash = calculate_hash(m_hash, 0);
            
            char* cstr = (char *) s.c_str();
            int32_t length = s.length() + 1;
            
            uint8_t lengthBuf[4];
            int32_t v = length;
            lengthBuf[0] = (v>>24)&0xff;
            lengthBuf[1] = (v>>16)&0xff;
            lengthBuf[2] = (v>>8)&0xff;
            lengthBuf[3] = (v & 0xff);
            m_buffer.write(reinterpret_cast<const char *>(&lengthBuf), sizeof(const int32_t));
            m_buffer.write(reinterpret_cast<const char *>(cstr), length);
        }
        
        // This is for data types with no appropriate write function
        void LCMSerializer::write ( const string id, const void* data, const uint32_t& size ) {
            char* _id = (char *) id.c_str();
            m_hash = hash_string(m_hash, reinterpret_cast<const char *>(_id));
            m_hash = hash_string(m_hash, "void");
            m_hash = calculate_hash(m_hash, 0);
            
            m_buffer.write(reinterpret_cast<const char*>(&data), size);
        }

        void LCMSerializer::write(core::data::Container &container){
            /* 
             * This is the writing of the message to the outstream that is going to be sent using LCM message structure.
             * This function will be called when all the necessary data has been encoded and written for the container.
             * An LCM message has the following structure:
             * 
             * MagicNumber|SequenceNumber|ChannelName|0|Hash|Payload
             * 
             * MagicNumber is used to check if the message is an LCM message. It is 4 bytes big.
             * SequenceNumber is not used since we only have non-fragmented messages. It is 4 bytes big.
             * ChannelName is the channel which the message will appear in. In our case it is the container data type. It can be up to 256 bytes big.
             * The 0 is used to know when the ChannelName ends. It is 1 byte big.
             * Hash shows which variables have been encoded and in which order. It is only for LCM and is not used in OpenDaVINCI. It is 8 bytes big.
             * Payload is where the encoded data will be.
             */
            
            // Encoding and writing the magic number
            uint32_t magicNumber = 0x4c433032;
            uint8_t mnbuf[4];
            mnbuf[0] = (magicNumber>>24)&0xff;
            mnbuf[1] = (magicNumber>>16)&0xff;
            mnbuf[2] = (magicNumber>>8)&0xff;
            mnbuf[3] = (magicNumber & 0xff);
            m_out.write(reinterpret_cast<const char *>(&mnbuf), sizeof(const uint32_t));
            
            // Sequence Number
            uint32_t sequence = 0;
            uint8_t seqbuf[4];
            seqbuf[0] = (sequence>>24)&0xff;
            seqbuf[1] = (sequence>>16)&0xff;
            seqbuf[2] = (sequence>>8)&0xff;
            seqbuf[3] = (sequence & 0xff);
            m_out.write(reinterpret_cast<const char *>(&seqbuf), sizeof(const uint32_t));
            
            // Channel name
            string channel;
            stringstream ss;
            
            uint32_t chan = container.getDataType();
            ss << chan;
            channel = ss.str();
            m_out << channel;
            
            // 0
            uint8_t zero = 0;
            m_out.write(reinterpret_cast<const char *>(&zero), sizeof(const uint8_t));
            
            // Writing the hash and the payload
            m_out << container.getSerializedData();
        }
        
        // Functions taken from LCM for calculating hash
        int64_t calculate_hash(int64_t v, char c) {
            v = ((v<<8) ^ (v>>55)) + c;
            
            return v;
        }
        
        int64_t hash_string(int64_t v, const char *s) {
            v = calculate_hash(v, ((string)s).length());
            
            for(; *s != 0; s++)
                v = calculate_hash(v, *s);
            
            return v;
        }

    } 
} // core:base

