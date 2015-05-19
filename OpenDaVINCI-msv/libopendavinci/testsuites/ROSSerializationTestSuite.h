/*
 * OpenDaVINCI.
 *
 * This software is open source. Please see COPYING and AUTHORS for further information.
 */

#ifndef CORE_PROTOSERIALIZATIONTESTSUITE_H_
#define CORE_PROTOSERIALIZATIONTESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include <cstdlib>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/concept_check.hpp>

#include "core/base/Hash.h"
#include "core/base/Serializable.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "core/base/Deserializer.h"
#include "core/base/ROSDeserializer.h"
#include "core/base/ROSSerializer.h"
#include "core/base/Thread.h"
#include "core/data/Container.h"
#include "core/data/TimeStamp.h"
#include "core/data/control/VehicleControl.h"

#include </home/cadogan/Git/thesisWork/OpenDaVINCI-msv/apps/2015/msv-data/include/SensorBoardData.h>
// #include "core/platform.h"

using namespace std;
using namespace core::base;
using namespace core::data;
using namespace core::data::control;
using namespace msv;

class SerializationTestNestedData : public core::base::Serializable {
    public:
        SerializationTestNestedData() :
                m_int(0),
                m_double(0),
                m_string(""){}

       uint32_t m_int;
       double m_double;
       string m_string;

        ostream& operator<<(ostream &out) const {
            SerializationFactory sf;

            Serializer &s = sf.getSerializer(out);

            s.write(1,m_int);
            s.write(2,m_double);
            s.write(3,m_string);

            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory sf;

            Deserializer &d = sf.getDeserializer(in);

            d.read(2, m_int);
            d.read(3,m_double);
            d.read(4,m_string);

            return in;
        }
};

class SerializationTestSampleData : public core::base::Serializable {
    public:
        SerializationTestSampleData() :
                m_bool(false),
                m_int(0),
                m_string(""),
                m_double(),
                m_float(),
                m_nestedData() 
                {}

        bool m_bool;
        int32_t m_int;
        string m_string;
        double  m_double;
        float m_float;
        SerializationTestNestedData m_nestedData;

        ostream& operator<<(ostream &out) const {
            SerializationFactory sf;

            Serializer &s = sf.getSerializer(out);
            
            s.write(1,m_float);
            s.write(2,m_double);
            s.write(3, m_bool);
   s.write(4, m_nestedData);
        
            s.write(5, m_int);
           
            s.write(6, m_string);
    
          
            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory sf;

            Deserializer &d = sf.getDeserializer(in);
            
             d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('m', '_', 'b', '3', 'o', 'l') >::RESULT,m_float);
            d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('m', '_', 'b', '2', 'o', 'l') >::RESULT,m_double);
            d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('m', '_', 'b', 'o', 'o', 'l') >::RESULT,
                   m_bool);
            
//            
                  d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('m', '_', 'n', 'e', 's', 't', 'e', 'd') >::RESULT,
                    m_nestedData);
             d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('m', '_', 'i', 'n', 't') >::RESULT,
                   m_int);
            d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('m', '_', 's', 't', 'r') >::RESULT,
                   m_string);
       

// 
            

            return in;
        }
};


class SerializationTest : public CxxTest::TestSuite {
    public:
        void testSerializationNested() {
            std::cout << " --- testing nested data --- " << endl; 
           SerializationTestSampleData sd;
           sd.m_bool = true;
           sd.m_int = 42;
           sd.m_nestedData.m_double = 1234.32;
           sd.m_nestedData.m_int = 1234;
           sd.m_string = "This is an example.";
           sd.m_float = 123.32;
           sd.m_double = 1999.354;
           sd.m_nestedData.m_string = "Nested one.";
            stringstream inout;
            inout << sd;
            inout.flush();

            // Read from the previously created data sink.
//             cout << " STARTING DECODING " <<endl;
            SerializationTestSampleData sd2;
            inout >> sd2;

            TS_ASSERT(sd2.m_bool);
            TS_ASSERT(sd2.m_int == 42);
            TS_ASSERT(sd2.m_string == "This is an example.");
            TS_ASSERT_DELTA(sd2.m_float, 123.32, 1e-5);
            TS_ASSERT_DELTA(sd2.m_double, 1999.354, 1e-5);
            TS_ASSERT_DELTA(sd2.m_nestedData.m_double,1234.32, 1e-5);
            TS_ASSERT(sd2.m_nestedData.m_int == 1234);
              TS_ASSERT(sd2.m_nestedData.m_string == "Nested one.");
// 
//             cout << "m_bool : "  << sd2.m_bool << " expected : " <<sd.m_bool << endl;
//              cout << " m_string " << sd2.m_string<< " Expected : " << sd.m_string << endl;;
//             cout << "m_int : " << sd2.m_int << "expected : " << sd.m_int <<endl;
              cout << "m_nestedData : " << sd2.m_nestedData.m_string<< " expected : " <<sd.m_nestedData.m_string <<endl;;
            cout << " --- end testing nested data --- " << endl; 

           
        }
        
          void testSerializationContainer() {
            cout << " --- Test serializing  container --- " << endl;
            // Create some data.
        
              
            VehicleControl vc;
            vc.setSpeed(2.0);
            vc.setAcceleration(1.6);
            vc.setSteeringWheelAngle(32);
            vc.setBrakeLights(true);
            vc.setLeftFlashingLights(false);
            vc.setRightFlashingLights(true);
//             cout << vc.toString() <<endl;
              
            Container c(Container::VEHICLECONTROL,vc);
          

            stringstream inout;

            SerializationFactory sf;
            ROSSerializer &protos = sf.getROSSerializer(inout);
            protos.write(c);
            inout.flush();
            
            Container c2;
            ROSDeserializer &protod = sf.getROSDeserializer(inout);
            protod.read(inout, c2);

            VehicleControl vc2 = c2.getData<VehicleControl>();
//             cout << vc2.toString()<<endl;

            TS_ASSERT(vc.toString() == vc2.toString());

            cout << " --- end test of container ---" << endl;
        }
        
          void testSerializationPayload() {
            cout << " --- Test payload --- " << endl;
            
            VehicleControl vc;
            vc.setSpeed(2.0);
            vc.setAcceleration(1.6);
            vc.setSteeringWheelAngle(32);
            vc.setBrakeLights(true);
            vc.setLeftFlashingLights(false);
            vc.setRightFlashingLights(true);
            
//             cout << vc.toString() <<endl;
              
            
            stringstream inout2;
            inout2 << vc;
            
            VehicleControl vc3 ;
            inout2 >> vc3;
//             cout << vc3.toString()<<endl;

             TS_ASSERT(vc.toString() == vc3.toString());

            cout << " --- end  Test payload --- " << endl;
       }
       
       
       void xtestSBD(){
           cout << " -- SensorBoardData serializing test -- " <<endl;
           
//            SensorBoardData sdb;
           //void update(const uint32_t &sensorID, const double &distance);
//            sdb.update(1, 12.2);
//            sdb.update(2, 12.2);
//            sdb.update(3, 12.2);
//            sdb.update(4, 12.2);
//            sdb.update(5, 12.2);
//            sdb.update(6, 12.2);
//            
           
       }
        
        void xtestProtoSerialisation() {
          cout << " --- Proto serialisation test --- " << endl;
          
          stringstream rawData ;
             
           VehicleControl vc;
           vc.setSpeed(2.0);
           vc.setAcceleration(1.6);
           vc.setSteeringWheelAngle(32);
           vc.setBrakeLights(true);
           vc.setLeftFlashingLights(false);
           vc.setRightFlashingLights(true);
           
           stringstream inout;
          
           Container c(Container::VEHICLECONTROL,vc);
           
           SerializationFactory sf;
           PROTOSerializer &protos = sf.getPROTOSerializer(inout);
           
           protos.write(c);
           
           TS_ASSERT(rawData.str() == inout.str());
          
           cout << " --- End of the proto serialisation test ---" << endl;
        
        }
        
        void xtestProtoDeserialisation() {
            
           cout << " --- Proto Deserialisation test ---" << endl;
           stringstream rawData;
             
           VehicleControl vc;
           vc.setSpeed(2.0);
           vc.setAcceleration(1.6);
           vc.setSteeringWheelAngle(32);
           vc.setBrakeLights(true);
           vc.setLeftFlashingLights(false);
           vc.setRightFlashingLights(true);
           
           cout << vc.toString() << endl;
           
           SerializationFactory sf;
           PROTODeserializer &protod = sf.getPROTODeserializer(rawData);
           Container c;
           protod.read(rawData,c);
           
           VehicleControl vc2 = c.getData<VehicleControl>();
           cout << vc2.toString()<<endl;

           TS_ASSERT(vc.toString() == vc2.toString());
          
           cout << " --- End of proto Deserialisation test ---" <<endl;
        }
        
        void xtestContainerNestedDataSerialisation() {
                 cout << " --- Test serializing  container --- " << endl;
            // Create some data.
        
            SerializationTestNestedData sd;
            VehicleControl vc;
            vc.setSpeed(10);
            vc.setAcceleration(1.6);
            vc.setSteeringWheelAngle(32);
            vc.setBrakeLights(true);
            vc.setLeftFlashingLights(false);
            vc.setRightFlashingLights(true);
//             cout << vc.toString() <<endl;
              sd.m_int = 10;
            Container c(Container::VEHICLECONTROL,vc);
          

            stringstream inout;

            SerializationFactory sf;
            PROTOSerializer &protos = sf.getPROTOSerializer(inout);
            protos.write(c);
            inout.flush();
            
            Container c2;
            PROTODeserializer &protod = sf.getPROTODeserializer(inout);
            protod.read(inout, c2);

            VehicleControl vc2 = c2.getData<VehicleControl>();
            cout << vc.toString() <<endl;
            cout << vc2.toString()<<endl;

            TS_ASSERT(vc.toString() == vc2.toString());

            cout << " --- end test of container --- 123" << endl;
            
            
        }
};

#endif /*CORE_PROTOSERIALIZATIONTESTSUITE_H_*/