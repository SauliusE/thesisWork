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
            m_hash(0x12345678),
            m_hashn(0),
            m_first(false) {}
        
        LCMSerializer::~LCMSerializer() {
            /* 
             * Calculates and writes the hash number and the payload to the ostream which will then get written to the container stream.
             * If this is the Serializer from the container (m_first is true), the hash will be serialized and written along with the payload.
             * Otherwise, if it is not the serializer where the write(container) function is called, the hash will be written along with the payload without serialization.
             * This is to be able to get the hash from the serializer that is created in "buffer << s" in write(Serializable).
             */
            
            int64_t hash;
            if (m_hash != 0x12345678) {
                hash = m_hash + ((m_hashn<<1) + ((m_hashn>>63)&1));
                hash = (hash<<1) + ((hash>>63)&1);
            } else if (!m_first) {
                hash = (m_hashn<<1) + ((m_hashn>>63)&1);
            }
            
            if (!m_first) {
                //hash = 0xbd6168d5cdb9b155;
                //hash = (hash<<1) + ((hash>>63)&1);
                uint8_t hashbuf[8];
                hashbuf[0] = (hash>>56)&0xff;
                hashbuf[1] = (hash>>48)&0xff;
                hashbuf[2] = (hash>>40)&0xff;
                hashbuf[3] = (hash>>32)&0xff;
                hashbuf[4] = (hash>>24)&0xff;
                hashbuf[5] = (hash>>16)&0xff;
                hashbuf[6] = (hash>>8)&0xff;
                hashbuf[7] = (hash & 0xff);
                m_out.write(reinterpret_cast<const char *>(&hashbuf), sizeof(const uint64_t));
            }
            
            
//             cout << "m_buffer length: " << m_buffer.str().length() << endl;
            m_out << m_buffer.str();
        }
        
        // Set and get methods
        int64_t LCMSerializer::getHash() {
            return m_hash;
        }
        
        void LCMSerializer::setHash(int64_t hash) {
            m_hash = hash;
        }
        
        bool LCMSerializer::getFirst() {
            return m_first;
        }
        
        void LCMSerializer::setFirst(bool f) {
            m_first = f;
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
        
        
        // This is for nested data, that is, data which has its own data fields.
        void LCMSerializer::write ( const uint32_t id, const Serializable& s ) {
            uint32_t _id = id;
            char cid[4];
            cid[0] = (_id>>24) & 0xff;
            cid[1] = (_id>>16) & 0xff;
            cid[2] = (_id>>8) & 0xff;
            cid[3] = _id & 0xff;
            m_hash = hash_string(m_hash, reinterpret_cast<const char *>(cid));
            m_hash = calculate_hash(m_hash, 0);
            
            stringstream buffer;
            buffer << s;
            
            uint8_t hashbuf[8];
            buffer.read(reinterpret_cast<char*>(&hashbuf), sizeof(int64_t));
            int64_t a = (((int32_t)hashbuf[0])<<24) + (((int32_t)hashbuf[1])<<16) + ((int32_t)hashbuf[2]<<8) + (int32_t)hashbuf[3];
            int64_t b = (((int32_t)hashbuf[4])<<24) + (((int32_t)hashbuf[5])<<16) + ((int32_t)hashbuf[6]<<8) + (int32_t)hashbuf[7];
            int64_t hash = (a<<32) + (b&0xffffffff);
            m_hashn = hash;
            
            buffer.str(buffer.str().substr(sizeof(int64_t), buffer.str().length())); 
            m_buffer << buffer.str();
        }
        
        // Bool
        void LCMSerializer::write ( const uint32_t id, const bool& b ) {
            uint32_t _id = id;
            char cid[4];
            cid[0] = (_id>>24) & 0xff;
            cid[1] = (_id>>16) & 0xff;
            cid[2] = (_id>>8) & 0xff;
            cid[3] = _id & 0xff;
            m_hash = hash_string(m_hash, reinterpret_cast<const char *>(cid));
            m_hash = hash_string(m_hash, "boolean");
            m_hash = calculate_hash(m_hash, 0);
            
            m_buffer.write(reinterpret_cast<const char *>(&b), sizeof(const bool));
        }
        
        /*
         * Char
         * 
         * Not supported by LCM. Used by OpenDaVINCI.
         */
        void LCMSerializer::write ( const uint32_t id, const char& c ) {
            uint32_t _id = id;
            char cid[4];
            cid[0] = (_id>>24) & 0xff;
            cid[1] = (_id>>16) & 0xff;
            cid[2] = (_id>>8) & 0xff;
            cid[3] = _id & 0xff;
            m_hash = hash_string(m_hash, reinterpret_cast<const char *>(cid));
            m_hash = hash_string(m_hash, "char");
            m_hash = calculate_hash(m_hash, 0);
            
            m_buffer.write(&c, sizeof(const char));
        }
        
        /*
         * Unsigned Char
         * 
         * Not supported by LCM. Used by OpenDaVINCI.
         */
        void LCMSerializer::write ( const uint32_t id, const unsigned char& uc ) {
            uint32_t _id = id;
            char cid[4];
            cid[0] = (_id>>24) & 0xff;
            cid[1] = (_id>>16) & 0xff;
            cid[2] = (_id>>8) & 0xff;
            cid[3] = _id & 0xff;
            m_hash = hash_string(m_hash, reinterpret_cast<const char *>(cid));
            m_hash = hash_string(m_hash, "unsigned char");
            m_hash = calculate_hash(m_hash, 0);
            
            m_buffer.write(reinterpret_cast<const char *>(&uc), sizeof(const unsigned char));
        }
        
        // int32_t
        void LCMSerializer::write ( const uint32_t id, const int32_t& i ) {
            uint32_t _id = id;
            char cid[4];
            cid[0] = (_id>>24) & 0xff;
            cid[1] = (_id>>16) & 0xff;
            cid[2] = (_id>>8) & 0xff;
            cid[3] = _id & 0xff;
            m_hash = hash_string(m_hash, reinterpret_cast<const char *>(cid));
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
         * Not supported by LCM. Used by OpenDaVINCI.
         */
        
        void LCMSerializer::write ( const uint32_t id, const uint32_t& ui ) {
            uint32_t _id = id;
            char cid[4];
            cid[0] = (_id>>24) & 0xff;
            cid[1] = (_id>>16) & 0xff;
            cid[2] = (_id>>8) & 0xff;
            cid[3] = _id & 0xff;
            m_hash = hash_string(m_hash, reinterpret_cast<const char *>(cid));
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
        
        // int64_t
        void LCMSerializer::write ( const uint32_t id, const int64_t& i ) {
            uint32_t _id = id;
            char cid[4];
            cid[0] = (_id>>24) & 0xff;
            cid[1] = (_id>>16) & 0xff;
            cid[2] = (_id>>8) & 0xff;
            cid[3] = _id & 0xff;
            m_hash = hash_string(m_hash, reinterpret_cast<const char *>(cid));
            m_hash = hash_string(m_hash, "int64_t");
            m_hash = calculate_hash(m_hash, 0);
            
            
            uint8_t buf[8];
            int64_t v = i;
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
        
        // Float
        void LCMSerializer::write ( const uint32_t id, const float& f ) {
            uint32_t _id = id;
            char cid[4];
            cid[0] = (_id>>24) & 0xff;
            cid[1] = (_id>>16) & 0xff;
            cid[2] = (_id>>8) & 0xff;
            cid[3] = _id & 0xff;
            m_hash = hash_string(m_hash, reinterpret_cast<const char *>(cid));
            m_hash = hash_string(m_hash, "float");
            m_hash = calculate_hash(m_hash, 0);
            
            
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
        void LCMSerializer::write ( const uint32_t id, const double& d ) {
            uint32_t _id = id;
            char cid[4];
            cid[0] = (_id>>24) & 0xff;
            cid[1] = (_id>>16) & 0xff;
            cid[2] = (_id>>8) & 0xff;
            cid[3] = _id & 0xff;
            m_hash = hash_string(m_hash, reinterpret_cast<const char *>(cid));
            m_hash = hash_string(m_hash, "double");
            m_hash = calculate_hash(m_hash, 0);
            
            
            // This way of encoding is taken straight from LCM.
            // Don't even know how and why it works myself.
            double _d = d;
            double *dd = &_d;
            int64_t *p = (int64_t*) dd;
            
//             cout << "m_buffer write pos: " << m_buffer.tellp() << endl;
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
            
            
            //double _d = d;
            //m_buffer.write(reinterpret_cast<const char *>(&_d), sizeof(const uint64_t));
        }
        
        /*
         * A string is encoded by first converting the string to a char*.
         * The length of the string, including the '\0', is encoded and written to the buffer
         * and then the char* is written to the buffer.
         */
        
        // String
        void LCMSerializer::write ( const uint32_t id, const string& s ) {
            uint32_t _id = id;
            char cid[4];
            cid[0] = (_id>>24) & 0xff;
            cid[1] = (_id>>16) & 0xff;
            cid[2] = (_id>>8) & 0xff;
            cid[3] = _id & 0xff;
            m_hash = hash_string(m_hash, reinterpret_cast<const char *>(cid));
            m_hash = hash_string(m_hash, "string");
            m_hash = calculate_hash(m_hash, 0);
            
            
            //char* cstr = (char *) s.c_str();
            uint32_t length = s.length() + 1;
            
            uint8_t lengthBuf[4];
            int32_t v = length;
            lengthBuf[0] = (v>>24)&0xff;
            lengthBuf[1] = (v>>16)&0xff;
            lengthBuf[2] = (v>>8)&0xff;
            lengthBuf[3] = (v & 0xff);
            m_buffer.write(reinterpret_cast<const char *>(&lengthBuf), sizeof(const uint32_t));
            m_buffer.write(reinterpret_cast<const char *>(s.c_str()), length);
        }
        
        // This is for data with no appropriate write function. You need to specify the size of the data.
        void LCMSerializer::write ( const uint32_t id, const void* data, const uint32_t& size ) {
            uint32_t _id = id;
            char cid[4];
            cid[0] = (_id>>24) & 0xff;
            cid[1] = (_id>>16) & 0xff;
            cid[2] = (_id>>8) & 0xff;
            cid[3] = _id & 0xff;
            m_hash = hash_string(m_hash, reinterpret_cast<const char *>(cid));
            m_hash = hash_string(m_hash, "void");
            m_hash = calculate_hash(m_hash, 0);
            
            m_buffer.write(reinterpret_cast<const char*>(data), size);
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
            /*
            // Writing the hash
            int64_t hash = container.getHash();
            uint8_t hashbuf[8];
            hashbuf[0] = (hash>>56)&0xff;
            hashbuf[1] = (hash>>48)&0xff;
            hashbuf[2] = (hash>>40)&0xff;
            hashbuf[3] = (hash>>32)&0xff;
            hashbuf[4] = (hash>>24)&0xff;
            hashbuf[5] = (hash>>16)&0xff;
            hashbuf[6] = (hash>>8)&0xff;
            hashbuf[7] = (hash & 0xff);
            m_out.write(reinterpret_cast<const char *>(&hashbuf), sizeof(const uint64_t));
            */
            
            // Writing the payload
            //string payload = container.getSerializedData();
            //string s1 = payload.substr(0, sizeof(int64_t));
            //string s2 = payload.substr(sizeof(int64_t), payload.length());
            
            m_out << container.getSerializedData();
            
            //Preventing any hash from being written
            m_first = true;
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


