/*
 * OpenDaVINCI.
 *
 * This software is open source. Please see COPYING and AUTHORS for further information.
 */

#include "core/base/Hash.h"
#include "core/base/LCMDeserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/LCMSerializer.h"
//#include "core/base/Serializer.h"
#include "core/data/Container.h"
#include "core/base/ROSSerializer.h"
#include "core/base/ROSDeserializer.h"

namespace core {
    namespace data {

        using namespace std;
        using namespace base;

        Container::Container() :
                m_serializedData(),
                m_dataType(UNDEFINEDDATA),
                m_payloadHash(),
                m_sent(TimeStamp(0, 0)),
                m_received(TimeStamp(0, 0)),
                m_message_size(){}

        Container::Container(const DATATYPE &dataType, const SerializableData &serializableData) :
                m_serializedData(),
                m_dataType(dataType),
                m_payloadHash(),
                m_sent(TimeStamp(0, 0)),
                m_received(TimeStamp(0, 0)),
                m_message_size(){
            
//             SerializationFactory sf;
//             LCMSerializer &lcm = sf.getLCMSerializer(m_serializedData);
//             
//             lcm.setFirst(true);
//             lcm.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('s','e','r') >:: RESULT,serializableData);
//             setHash(lcm.getHash());
               
               m_serializedData << serializableData;
                /*
               TimeStamp start;   
                m_serializedData << serializableData;
                TimeStamp end;
                uint32_t data = getDataType();
                ofstream myfile;
                if(data == 1000){
                     myfile.open ("/opt/msv/ContainerWriteSBD.csv",ios::out | ios::app);
                     myfile << (end.toMicroseconds() - start.toMicroseconds());
                     myfile << " : " ;
                     myfile << m_serializedData.str().length();
                     myfile << endl;
                }
                if(data == 41){
                     myfile.open ("/opt/msv/ContainerWriteVC.csv",ios::out | ios::app);
                     myfile << (end.toMicroseconds() - start.toMicroseconds());
                     myfile << " : " ;
                     myfile << m_serializedData.str().length();
                     myfile << endl;
                }
                if(data == 39){
                     myfile.open ("/opt/msv/ContainerWriteVD.csv",ios::out | ios::app);
                     myfile << (end.toMicroseconds() - start.toMicroseconds());
                     myfile << " : " ;
                     myfile << m_serializedData.str().length();
                     myfile << endl;
                }
                myfile.close();
                */
            /*
            SerializationFactory sf;
            LCMSerializer &lcm = sf.getLCMSerializer(m_serializedData);
            
            lcm.setFirst(true);
            lcm.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('s','e','r') >:: RESULT,serializableData);
            setHash(lcm.getHash());
            */
            
            
           // m_payloadHash = lcm.getHash();
         //   m_message_size = lcm.getMessageSize();
        }

        Container::Container(const Container &obj) :
                Serializable(),
                m_serializedData(),
                m_dataType(obj.getDataType()),
                m_payloadHash(),
                m_sent(obj.m_sent),
                m_received(obj.m_received) {
                    
            m_serializedData.str(obj.m_serializedData.str());
        }

        Container& Container::operator=(const Container &obj) {
            m_dataType = obj.getDataType();
            m_serializedData.str(obj.m_serializedData.str());
            setSentTimeStamp(obj.getSentTimeStamp());
            setReceivedTimeStamp(obj.getReceivedTimeStamp());

            return (*this);
        }

        Container::~Container() {}
        
        uint32_t Container::getMessageSize()
        {
            return m_message_size;
        }


        void Container::setMessageSize(uint32_t& size)
        {
            m_message_size = size;
        }

        string Container::getSerializedData() const {
            return m_serializedData.str();
        }
        
        void Container::setSerializedData(const string &s) {
            m_serializedData.str(s);
        }
        
        Container::DATATYPE Container::getDataType() const {
            return m_dataType;
        }
        
        void Container::setDataType(const DATATYPE &dataType) {
            m_dataType = dataType;
        }
        
        int64_t Container::getHash() const {
            return m_payloadHash;
        }
        
        void Container::setHash(const int64_t &hash) {
            m_payloadHash = hash;
        }

        const TimeStamp Container::getSentTimeStamp() const {
            return m_sent;
        }

        void Container::setSentTimeStamp(const TimeStamp &sentTimeStamp) {
            m_sent = sentTimeStamp;
        }

        const TimeStamp Container::getReceivedTimeStamp() const {
            return m_received;
        }

        void Container::setReceivedTimeStamp(const TimeStamp &receivedTimeStamp) {
            m_received = receivedTimeStamp;
        }



        ostream& Container::operator<<(ostream &out) const {
            SerializationFactory sf;

            Serializer &s = sf.getSerializer(out);

            // Write container data type.
            uint32_t dataType = getDataType();
            TimeStamp start;
            s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                    dataType);
            
            // Write container data.
            s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('d', 'a', 't', 'a') >::RESULT,
                    m_serializedData.str());
            
            // Write sent time stamp data.
            s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('s', 'e', 'n', 't') >::RESULT,
                    m_sent);

            // Write received time stamp data.
            s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('r', 'e', 'c', 'v', 'd') >::RESULT,
                    m_received);
            TimeStamp end;
            uint32_t size = 0;
                       size = sizeof(dataType) + m_serializedData.str().length() + sizeof(m_sent) + sizeof(m_received);
                       ofstream myfile;
                       if(dataType == 1000){
                           myfile.open ("/opt/msv/ContainerWriteSBD.csv",ios::out | ios::app);
                           myfile << (end.toMicroseconds() - start.toMicroseconds());
                           myfile << " : " ;
                           myfile << size;
                           myfile << endl;
                        }
                        if(dataType == 41){
                            myfile.open ("/opt/msv/ContainerWriteVC.csv",ios::out | ios::app);
                            myfile << (end.toMicroseconds() - start.toMicroseconds());
                            myfile << " : " ;
                            myfile << size;
                            myfile << endl;
                        }
                        if(dataType == 39){
                            myfile.open ("/opt/msv/ContainerWriteVD.csv",ios::out | ios::app);
                            myfile << (end.toMicroseconds() - start.toMicroseconds());
                            myfile << " : " ;
                            myfile << size;
                            myfile << endl;
                          }
                         myfile.close();
            return out;
        }

        istream& Container::operator>>(istream &in) {
            string rawData = "";

            SerializationFactory sf;
            Deserializer &d = sf.getDeserializer(in);
         //   d.read();
            // Read container data type.
           uint32_t dataType = 0;
           TimeStamp start;
            d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                   dataType);

            // Read container data.
            d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('d', 'a', 't', 'a') >::RESULT,
                   rawData);
            
            // Read sent time stamp data.
            d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('s', 'e', 'n', 't') >::RESULT,
                   m_sent);

            // Read received time stamp data.
            d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('r', 'e', 'c', 'v', 'd') >::RESULT,
                   m_received);
            
            TimeStamp end;

                        uint32_t size = 0;
                        size = sizeof(dataType) + rawData.length() + sizeof(m_sent) + sizeof(m_received);
                        ofstream myfile;
                        if(dataType == 1000){
                            myfile.open ("/opt/msv/ContainerReadSBD.csv",ios::out | ios::app);
                            myfile << (end.toMicroseconds() - start.toMicroseconds());
                            myfile << " : " ;
                            myfile << size;
                            myfile << endl;
                         }
                         if(dataType == 41){
                             myfile.open ("/opt/msv/ContainerReadVC.csv",ios::out | ios::app);
                             myfile << (end.toMicroseconds() - start.toMicroseconds());
                             myfile << " : " ;
                             myfile << size;
                             myfile << endl;
                         }
                         if(dataType == 39){
                             myfile.open ("/opt/msv/ContainerReadVD.csv",ios::out | ios::app);
                             myfile << (end.toMicroseconds() - start.toMicroseconds());
                             myfile << " : " ;
                             myfile << size;
                             myfile << endl;
                           }
                          myfile.close();
            // Set data.
            m_dataType = static_cast<DATATYPE>(dataType);
            m_serializedData.str(rawData);

            return in;
        }

        const string Container::toString() const {
            switch (getDataType()) {
                case UNDEFINEDDATA:
                    return "undefined data";
                case CONFIGURATION:
                    return "Configuration";
                case DMCP_DISCOVER:
                    return "DMCPDiscoverMessage";
                case DMCP_CONNECTION_REQUEST:
                    return "DMCPConnectionRequest";
                case DMCP_CONFIGURATION_REQUEST:
                    return "DMCPConfigurationRequest";
                case DMCP_MODULESTATEMESSAGE:
                    return "DMCP_MODULESTATEMESSAGE";
                case DMCP_MODULEEXITCODEMESSAGE:
                    return "DMCP_MODULEEXITCODEMESSAGE";
                case MODULESTATISTICS:
                    return "ModuleStatistics";
                case RUNTIMESTATISTIC:
                    return "RuntimeStatistic";
                case PLAYER_COMMAND:
                    return "PlayerCommand";
                case RECORDER_COMMAND:
                    return "RecorderCommand";
                case TIMESTAMP:
                    return "TimeStamp";
                case SHARED_DATA:
                    return "SharedData";
                case SHARED_IMAGE:
                    return "SharedImage";
                case POSITION:
                    return "Position";
                case CONTOUREDOBJECT:
                    return "ContouredObject";
                case CONTOUREDOBJECTS:
                    return "ContouredObject";
                case EGOSTATE:
                    return "EgoState";
                case FORCECONTROL:
                    return "ForceControl";
                case LMS291MESSAGE:
                    return "LMS291Message";
                case OBSTACLE:
                    return "Obstacle";
                case OTHERVEHICLESTATE:
                    return "OtherVehicleState";
                case POINTSHAPEDOBJECT:
                    return "PointShapedObject";
                case ROUTE:
                    return "Route";
                case VEHICLEDATA:
                    return "VehicleData";
                case DRAW_LINE:
                    return "Draw line";
                case VEHICLECONTROL:
                    return "VehicleControl";
                case STRINGDATA:
                    return "StringData";
                case USER_BUTTON:
                    return "User Button";
                case DMCP_PULSE_MESSAGE:
                    return "DMCP_PULSE_MESSAGE";
                case USER_DATA_0:
                    return "UserData_0";
                case USER_DATA_1:
                    return "UserData_1";
                case USER_DATA_2:
                    return "UserData_2";
                case USER_DATA_3:
                    return "UserData_3";
                case USER_DATA_4:
                    return "UserData_4";
                case USER_DATA_5:
                    return "UserData_5";
                case USER_DATA_6:
                    return "UserData_6";
                case USER_DATA_7:
                    return "UserData_7";
                case USER_DATA_8:
                    return "UserData_8";
                case USER_DATA_9:
                    return "UserData_9";
            }
            return "";
        }
    }
} // core::data


