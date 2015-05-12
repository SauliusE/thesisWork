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

#include "core/base/Hash.h"
#include "core/base/Serializable.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "core/base/Deserializer.h"
#include "core/base/PROTODeserializer.h"
#include "core/base/PROTOSerializer.h"
#include "core/base/Thread.h"
#include "core/data/Container.h"
#include "core/data/TimeStamp.h"
#include "core/data/control/VehicleControl.h"
using namespace std;
using namespace core::base;
using namespace core::data;
using namespace core::data::control;

class SerializationTestNestedData : public Serializable {
    public:
        SerializationTestNestedData() :
                m_double(0) {}

        double m_double;

        ostream& operator<<(ostream &out) const {
            SerializationFactory sf;

            PROTOSerializer &s = sf.getPROTOSerializer(out);

            s.write(1, m_double);
            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory sf;

            PROTODeserializer &d = sf.getPROTODeserializer(in);

            d.read(1, m_double);
            return in;
        }
};

class SerializationTestSampleData : public Serializable {
    public:
        int64_t m_hash;
        bool m_bool;
        int32_t m_int;
        string m_string;
        float m_float;
        double m_double;
        
        SerializationTestSampleData() :
                m_hash(),
                m_bool(false),
                m_int(0),
                m_string(""),
                m_float(),
                m_double() {}
                
       SerializationTestSampleData(const SerializationTestSampleData& o):
          m_hash(o.m_hash),
                m_bool(o.m_bool),
                m_int(o.m_int),
                m_string(o.m_string),
                m_float(o.m_float),
                m_double(o.m_double){}
       
     
        ostream& operator<<(ostream &out) const {
            SerializationFactory sf;

            PROTOSerializer &s = sf.getPROTOSerializer(out);

            s.write(1, m_bool);
            
            s.write(2, m_int);

            s.write(3, m_string);
            
            s.write(4, m_float);

            s.write(5, m_double);

            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory sf;

            PROTODeserializer &d = sf.getPROTODeserializer(in);
            
            d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('m', '_', 'h', 'a', 's', 'h') >::RESULT,
                   m_hash);
            
            d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('m', '_', 'b', 'o', 'o', 'l') >::RESULT,
                   m_bool);
            
            d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('m', '_', 'i', 'n', 't') >::RESULT,
                   m_int);

            d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('m', '_', 's', 't', 'r') >::RESULT,
                   m_string);
            
            d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('m', '_', 'f', 'l', 'o', 'a', 't') >::RESULT,
                   m_float);
            
            d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('m', '_', 'n', 'e', 's', 't', 'e', 'd') >::RESULT,
                   m_double);

            return in;
        }
};


class SerializationTest : public CxxTest::TestSuite {
    public:
        void testSerializationPayload() {
            // Data to be serialized
            VehicleControl vc;
            vc.setSpeed(2.0);
            vc.setAcceleration(1.6);
            vc.setSteeringWheelAngle(32);
            vc.setBrakeLights(true);
            vc.setLeftFlashingLights(false);
            vc.setRightFlashingLights(true);
            
            cout << " Test for serializing payload " <<endl;
            // Create a data sink.
            stringstream inout;
            cout << vc.toString()<<endl;
            inout << vc;
            inout.flush();
            
            // Read from the previously created data sink.
            VehicleControl vc2;
            inout >> vc2;
            cout << vc2.toString()<< endl;

            TS_ASSERT(vc.toString() == vc2.toString());
            
            cout << " End of test for the serializing payload. " <<endl;
           
        }
        
          void testSerializationContainer() {
              cout << "Testing Container " << endl;
            // Create some data.
//             SerializationTestSampleData sd;
//             sd.m_bool = true;
//             sd.m_int = 42;
//             sd.m_string = "This is an example.";
//             sd.m_float = -321.456;
//             sd.m_double = -42.42;
//             TimeStamp ts;
              
              VehicleControl vc;
              vc.setSpeed(2.0);
              vc.setAcceleration(5.0);
              vc.setSteeringWheelAngle(23.0);
              vc.setBrakeLights(true);
            cout << vc.toString() <<endl;
              
            Container c(Container::VEHICLECONTROL,vc);
            
            stringstream inout2;
            inout2 << vc;
            
            VehicleControl vc3 ;
            inout2 >> vc3;
            cout << vc3.toString()<<endl;
            // Create a data sink.
       
           
            stringstream inout;

                SerializationFactory sf;
                LCMSerializer &lcm = sf.getLCMSerializer(inout);
            lcm.write(c);
             inout.flush();
            
              Container c2;
              LCMDeserializer &lcmd = sf.getLCMDeserializer(inout);
              lcmd.read(inout, c2);
            
              VehicleControl vc2 = c2.getData<VehicleControl>();
              cout << vc2.toString()<<endl;
//               inout >> c2;
              TS_ASSERT(vc2.getBrakeLights());
              cout << " brake lights are : " << vc2.getBrakeLights() << " Should " << vc.getBrakeLights()<<endl;
              TS_ASSERT_DELTA(vc2.getSpeed(),2.0,1e-5);
              cout << "speed is : " << vc2.getSpeed() << " Should : " << vc.getSpeed() << endl;
//             // Read from the previously created data sink.
//             SerializationTestSampleData sd2 = c2.getData<SerializationTestSampleData>();
// //             inout >> sd2;
//             
//             cout << "m_hash Is: " << sd2.m_hash << ", Should: " << "dunno" << endl;
//             cout << "m_bool Is: " << sd2.m_bool << ", Should: " << false << endl;
//             TS_ASSERT(sd2.m_bool);
//             cout << "m_int Is: " << sd2.m_int << ", Should: " << 42 << endl;
//             TS_ASSERT(sd2.m_int == 42);
//             cout << "m_string Is: " << sd2.m_string << ", Should: " << "This is an example." << endl;
//             TS_ASSERT(sd2.m_string == "This is an example.");
//             cout << "m_float Is: " << sd2.m_float << ", Should: " << -321.456 << endl;
//             TS_ASSERT_DELTA(sd2.m_float, -321.456, 1e-5);
//             cout << "m_double Is: " << sd2.m_double << ", Should: " << -42.42 << endl;
//             TS_ASSERT_DELTA(sd2.m_double, -42.42, 1e-5);
        }
        
          void testPayload() {
              cout << " Test payload " << endl;
              VehicleControl vc;
              vc.setSpeed(2.0);
              vc.setAcceleration(5.0);
              vc.setSteeringWheelAngle(23.0);
              vc.setBrakeLights(true);
            cout << vc.toString() <<endl;
              
            
            stringstream inout2;
            inout2 << vc;
            
            VehicleControl vc3 ;
            inout2 >> vc3;
            cout << vc3.toString()<<endl;
            // Create a data sink.
            TS_ASSERT(vc.toString() == vc3.toString());
             cout << " end  Test payload " << endl;
       }
        
        void xtestArraySerialisation() {
            /*
            stringstream stream;
            uint32_t array[10];
            for (uint32_t i=0; i<10; ++i) {
                array[i] = i;
            }

            SerializationFactory sf;
            LCMSerializer& s = sf.getLCMSerializer(stream);
            s.write(550, &array, 10);
            
            stream.clear();
            stream.seekg(0, ios_base::beg);
            
            LCMDeserializer& d = sf.getLCMDeserializer(stream);
            //int64_t hash;
            //d.read(0, hash);
            uint32_t deserializedArray[10];
            d.read(1, &deserializedArray, 10);

            for (uint32_t i=0; i<10; ++i) {
                TS_WARN(deserializedArray[i] == i);
                cout << "Is: " << deserializedArray[i] << ", Should: " << i << endl;
            }
            */
        }
        
};

#endif /*CORE_PROTOSERIALIZATIONTESTSUITE_H_*/