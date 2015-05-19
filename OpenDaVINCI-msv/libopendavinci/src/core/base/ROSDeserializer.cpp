/*
 * OpenDaVINCI.
 *
 * This software is open source. Please see COPYING and AUTHORS for further information.
 */

#include "core/base/ROSDeserializer.h"
#include "core/base/Serializable.h"

namespace core {
    namespace base {

        using namespace std;
uint32_t decodeVar ( istream &in, uint64_t &value );
        ROSDeserializer::ROSDeserializer(istream &in) :
                m_buffer(),
                m_values(),
                m_size(0),
                position(0){
            // Initialize the stringstream for getting valid positions when calling tellp().
            // This MUST be a blank (Win32 has a *special* implementation...)!
  char c = 0;
            in.get(c);
        
            while(in.good() ){
                m_buffer.put(c);
                in.get(c);
                
            }
            
            in.clear();
            in.seekg(0,ios_base::beg);

        }

        ROSDeserializer::~ROSDeserializer() { 
        }
       

        void ROSDeserializer::read(const uint32_t id, Serializable &s) {
          (void) id; //to be removed in the future
                m_buffer >> s;
            }

        

        
        void ROSDeserializer::read(const uint32_t id, bool &b) {
               
                (void)id;           
                m_buffer.read(reinterpret_cast<char *>(&b), sizeof(bool));
        }

        void ROSDeserializer::read(const uint32_t id, char &c) {
            
                (void)id;           
                m_buffer.read(reinterpret_cast<char *>(&c), sizeof(char));
      }

void ROSDeserializer::read(const uint32_t id, unsigned char& uc)
{
 (void) id;
 (void)uc;
}

        void ROSDeserializer::read(const uint32_t id, int32_t &i) {
            
                (void)id;           
                m_buffer.read(reinterpret_cast<char *>(&i), sizeof(int32_t));

        }

        void ROSDeserializer::read(const uint32_t id, uint32_t &ui) {
            
                (void)id;           
                m_buffer.read(reinterpret_cast<char *>(&ui), sizeof(uint32_t));
        }

        void ROSDeserializer::read(const uint32_t id, float &f) {
            
                (void)id;           
                m_buffer.read(reinterpret_cast<char *>(&f), sizeof(float));
              
        }

        void ROSDeserializer::read(const uint32_t id, double &d) {
            
                (void)id;           
                m_buffer.read(reinterpret_cast<char *>(&d), sizeof(double));
        }

        void ROSDeserializer::read(const uint32_t id, string &s) {
            
                (void)id;           
                uint32_t stringLength = 0;
                m_buffer.read(reinterpret_cast<char *>(&stringLength), sizeof(uint32_t));
                stringLength = ntohl(stringLength);
                char *str = new char[stringLength+1];
                m_buffer.read(reinterpret_cast<char *>(str), static_cast<uint32_t>(stringLength));
                str[stringLength] = '\0';
                // It is absolutely necessary to specify the size of the serialized string, otherwise, s contains only data until the first '\0' is read.
                s = string(str, stringLength);
                OPENDAVINCI_CORE_DELETE_ARRAY(str);
        }

        void ROSDeserializer::read(const uint32_t id, void *data, uint32_t size) {
              cout << "Read data Deserializer" << "- ID value: " << id <<" |  data  value: " << data << " | size of data : "<< size <<endl;

        }
        void ROSDeserializer::read(istream &in, core::data::Container &container) {
                
                uint32_t connectionID;
                uint8_t opcode;
                uint8_t messageID;
                uint16_t blockNr;

                in.read(reinterpret_cast<char *>(&connectionID), sizeof(const uint32_t));
                in.read(reinterpret_cast<char *>(&opcode), sizeof(const uint8_t));
                in.read(reinterpret_cast<char *>(&messageID), sizeof(const uint8_t));
                in.read(reinterpret_cast<char *>(&blockNr), sizeof(const uint16_t));
                
                char c = 0;
                in.get(c);
                
                while(in.good()){
                    m_buffer.put(c);
                    in.get(c);
                }
                
                container.setSerializedData(m_buffer.str());

    }
     


    }
} // core::base
