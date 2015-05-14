/*
 * OpenDaVINCI.
 *
 * This software is open source. Please see COPYING and AUTHORS for further information.
 */

#ifndef OPENDAVINCI_DATA_ENVIRONMENT_SAMPLEDATA_H_
#define OPENDAVINCI_DATA_ENVIRONMENT_SAMPLEDATA_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/data/SerializableData.h"


namespace core {
    namespace data {
        namespace environment {

            using namespace std;
            
            
            class OPENDAVINCI_API SampleNestedData : public core::data::SerializableData {
            public:
                SampleNestedData();
                SampleNestedData(const SampleNestedData &obj);
                virtual ~SampleNestedData();
                
                // TODO; write set and get methods for variables
//                 void setNestedBool(const bool &b);                
//                 void setNestedInt32(const int32_t &i);                
//                 void setNestedUint32(const uint32_t &ui);                
//                 void setNestedString(const string &s);                
//                 void setNestedDouble(const double &d);                
//                 void setNestedFloat(const float &f);                
//                 bool getNestedBool() const;                
//                 int32_t getNestedInt32() const;                
//                 uint32_t getNestedUint32() const;                
//                 string getNestedString() const;                
//                 float getNestedFloat() const;
//                 
                
                 virtual ostream& operator<<(ostream &out) const;
                 virtual istream& operator>>(istream &in);

                 virtual const string toString() const;
                
          
                bool m_bool;
                int32_t m_int;
                uint32_t m_uint;
                string m_string;
                double  m_double;
                float m_float;
            };
            
            
            /**
             * This class contains all relevant data for the own car.
             */
            class OPENDAVINCI_API SampleData : public core::data::SerializableData {
                public:
                    SampleData();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                     SampleData(const  SampleData &obj);

                    virtual ~ SampleData();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                     SampleData& operator=(const  SampleData &obj);

                     // TODO: set and get methods for all variables
                    
//                 void setBool(const bool &b);                
//                 void setInt32(const int32_t &i);                
//                 void setUint32(const uint32_t &ui);               
//                 void setString(const string &s);                
//                 void setDouble(const double &d);                
//                 void setFloat(const float &f);                
//                 bool getBool() const;                
//                 int32_t getInt32() const;                
//                 uint32_t getUint32() const;                
//                 string getString() const;                
//                 float getFloat() const;
                
                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

               
                    bool m_bool;
                    int32_t m_int;
                    uint32_t m_uint;
                    string m_string;
                    double  m_double;
                    float m_float;
                    SampleNestedData m_nestedData;
                    
            };

        }
    }

} // core::data::environment

#endif /*OPENDAVINCI_DATA_ENVIRONMENT_SAMPLEDATA_H_*/
