/*
 * OpenDaVINCI.
 *
 * This software is open source. Please see COPYING and AUTHORS for further information.
 */

#ifndef OPENDAVINCI_CORE_DATA_CONTAINER_H_
#define OPENDAVINCI_CORE_DATA_CONTAINER_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/base/Serializable.h"
#include "core/data/SerializableData.h"
#include "core/data/TimeStamp.h"

namespace core {
    namespace data {

        using namespace std;

        /**
         * Container for all interchangeable data.
         */
        class OPENDAVINCI_API Container : public core::base::Serializable {
            public:
                enum DATATYPE {
                    UNDEFINEDDATA                =  1,
                    CONFIGURATION                =  2,
                    DMCP_DISCOVER                =  3,
                    DMCP_CONNECTION_REQUEST      =  4,
                    DMCP_CONFIGURATION_REQUEST   =  5,
                    DMCP_MODULESTATEMESSAGE      =  6,
                    DMCP_MODULEEXITCODEMESSAGE   =  7,
                    MODULESTATISTICS             =  8,
                    RUNTIMESTATISTIC             =  9,
                    PLAYER_COMMAND               = 10,
                    RECORDER_COMMAND             = 11,
                    TIMESTAMP                    = 12,
                    SHARED_DATA                  = 13,
                    SHARED_IMAGE                 = 14,
                    POSITION                     = 15,

                    CONTOUREDOBJECT              = 30,
                    CONTOUREDOBJECTS             = 31,
                    EGOSTATE                     = 32,
                    FORCECONTROL                 = 33,
                    LMS291MESSAGE                = 34,
                    OBSTACLE                     = 35,
                    OTHERVEHICLESTATE            = 36,
                    POINTSHAPEDOBJECT            = 37,
                    ROUTE                        = 38,
                    VEHICLEDATA                  = 39,
                    DRAW_LINE                    = 40,
                    VEHICLECONTROL               = 41,

                    STRINGDATA                   = 100,

                    DMCP_PULSE_MESSAGE           = 101,

                    USER_BUTTON                  = 999,
                    USER_DATA_0                  = 1000,
                    USER_DATA_1                  = 1001,
                    USER_DATA_2                  = 1002,
                    USER_DATA_3                  = 1003,
                    USER_DATA_4                  = 1004,
                    USER_DATA_5                  = 1005,
                    USER_DATA_6                  = 1006,
                    USER_DATA_7                  = 1007,
                    USER_DATA_8                  = 1008,
                    USER_DATA_9                  = 1009
                };

            public:
                Container();

                /**
                 * Constructor.
                 *
                 * @param dataType Type of data inside this container.
                 * @param serializableData Data to be serialized.
                 */
                Container(const DATATYPE &dataType, const SerializableData &serializableData)	;

                /**
                 * Copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                Container(const Container &obj);

                virtual ~Container();

                /**
                 * Assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                Container& operator=(const Container &obj);
				
				string getSerializedData() const;
				void setSerializedData(const string &s);
				
                /**
                 * This method returns the data type inside this container.
                 *
                 * @return Data type of the data contained in this container.
                 */
                DATATYPE getDataType() const;
                void setDataType(const DATATYPE &dataType);	
                int64_t getHash() const;
                void setHash(const int64_t &hash);
                
                void setMessageSize(uint32_t &size);
                uint32_t getMessageSize();

                virtual ostream& operator<<(ostream &out) const;
                virtual istream& operator>>(istream &in);

                /**
                 * This method returns a usable object:
                 *
                 * @code
                 * Container c;
                 * ...
                 * T t = c.getData<T>();
                 * @endcode
                 *
                 * @return Usable object.
                 */
                template<class T>
                inline T getData() {
                    T containerData;
                    // Read from beginning.
                    m_serializedData.seekg(ios::beg);
                    m_serializedData >> containerData;
                    return containerData;
                };

                /**
                 * This method returns the time stamp when this
                 * container was sent.
                 *
                 * @return Time stamp when this container was sent.
                 */
                const TimeStamp getSentTimeStamp() const;

                /**
                 * This method sets the time stamp when this
                 * container was sent.
                 *
                 * @param sentTimeStamp Time stamp when this container was sent.
                 */
                void setSentTimeStamp(const TimeStamp &sentTimeStamp);

                /**
                 * This method returns the time stamp when this
                 * container was received.
                 *
                 * @return Time stamp when this container was received.
                 */
                const TimeStamp getReceivedTimeStamp() const;

                /**
                 * This method sets the time stamp when this
                 * container was received.
                 *
                 * @param receivedTimeStamp Time stamp when this container was received.
                 */
                void setReceivedTimeStamp(const TimeStamp &receivedTimeStamp);

                /**
                 * This method returns the data type as String.
                 *
                 * @return The data type.
                 */
                const string toString() const;

                
				


            private:
		stringstream m_serializedData;
		DATATYPE m_dataType;
		uint64_t m_payloadHash;
                TimeStamp m_sent;
                TimeStamp m_received;
		uint32_t m_message_size;
        };

    }
} // core::data

#endif /*OPENDAVINCI_CORE_DATA_CONTAINER_H_*/

