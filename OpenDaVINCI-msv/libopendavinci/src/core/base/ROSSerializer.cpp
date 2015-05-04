/*
 * OpenDaVINCI.
 *
 * This software is open source. Please see COPYING and AUTHORS for further information.
 */

#include "core/base/ROSSerializer.h"
#include "core/base/Serializable.h"
#include "endian.h"
#include "core/data/Container.h"
#include <typeinfo>



namespace core {
    namespace base {
        
        using namespace std;
        
        ROSSerializer::ROSSerializer(ostream& out) :
                m_out(out),
                m_buffer(),
                m_size(0){}
        
        ROSSerializer::~ROSSerializer(){
            // Here suppose to be finalized message based on ROS approach, as far i know it is
            // It is : 
            // - > size of message
            // - > payload
            // Writing size of message
            m_out << m_buffer.str();
       
        } // end of ~constructor

        void ROSSerializer::write ( const uint32_t id, const Serializable& s ) {
             // writing serializable
            (void)id;
            stringstream buffer;
            buffer << s;
            m_buffer << buffer.str();
        }
    
    
        void ROSSerializer::write ( const uint32_t id, const bool& b ) {
            
            (void) id;
            m_size += static_cast<uint32_t>(sizeof(b));
            
            m_buffer.write(reinterpret_cast<const char *>(&b), sizeof(const bool));
        }
        
        void ROSSerializer::write ( const uint32_t id, const char& c ) {
               
            (void) id;
            m_size += static_cast<uint32_t>(sizeof(c));
            
            m_buffer.write(&c, sizeof(const char));
        }
        

        void ROSSerializer::write ( const uint32_t id, const int32_t& i ) {
            
            (void) id;
            m_size += static_cast<uint32_t>(sizeof(i));
            
            int32_t _i = i;
            _i = htonl(_i);
            m_buffer.write(reinterpret_cast<const char *>(&_i), sizeof(const uint32_t));
        }
        
        void ROSSerializer::write ( const uint32_t id, const uint32_t& ui ) {

            (void) id;
            m_size += static_cast<uint32_t>(sizeof(ui));
            
            uint32_t _ui = ui;
            _ui = htonl(_ui);
            m_buffer.write(reinterpret_cast<const char *>(&_ui), sizeof(const uint32_t));

        }
        
        void ROSSerializer::write ( const uint32_t id, const float& f ) {
            
            (void) id;
            m_size += static_cast<uint32_t>(sizeof(f));
            
            float _f = f;
            _f = Serializer::htonf(_f);
            m_buffer.write(reinterpret_cast<const char *>(&_f), sizeof(const float));

       }

        void ROSSerializer::write ( const uint32_t id, const double& d ) {

            (void) id;
            m_size += static_cast<uint32_t>(sizeof(d));
            
            double _d = d;
            _d = Serializer::htond(_d);
            m_buffer.write(reinterpret_cast<const char *>(&_d), sizeof(const double));


        }
        void ROSSerializer::write ( const uint32_t id, const string& s ) {
               
            (void) id;
            m_size += static_cast<uint32_t>(sizeof(s));
            
            uint32_t stringLength = s.length();
            uint32_t size = static_cast<uint32_t>(stringLength + sizeof(uint32_t));             

            uint32_t _stringLength = stringLength;
            _stringLength = htonl(_stringLength);
            m_buffer.write(reinterpret_cast<const char *>(&_stringLength), sizeof(uint32_t));
            m_buffer.write(reinterpret_cast<const char *>(s.c_str()), stringLength);


        }

        void ROSSerializer::write ( const uint32_t id, const void* data, const uint32_t& size ) {
            cout<< "Writing id: " << id << "of user data " << data << " size of it " << size << endl;
        }
    

    void ROSSerializer::write (core::data::Container &container){
   
                uint32_t headerLength = 4;                
                headerLength = htonl(headerLength);
                m_out.write(reinterpret_cast<const char *>(&headerLength), sizeof(const uint32_t));
                
                uint32_t dataType = container.getDataType();
                dataType = htonl(dataType);
                m_out.write(reinterpret_cast<const char *>(&dataType), sizeof(const uint32_t));
            
                uint32_t msgSize = container.getMessageSize();
                msgSize = htonl(msgSize);
                m_out.write(reinterpret_cast<const char *>(&msgSize), sizeof(const uint32_t));
                
                m_out << container.getSerializedData();

        }
    

    } 
        
} // core:base

  
