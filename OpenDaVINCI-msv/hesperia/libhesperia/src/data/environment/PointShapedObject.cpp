/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"

#include "hesperia/data/environment/PointShapedObject.h"

namespace hesperia {
    namespace data {
        namespace environment {

            using namespace std;
            using namespace core::base;
            using namespace core::data::environment;

            PointShapedObject::PointShapedObject() :
                    Position(Point3(0, 0, 0), Point3(0, 0, 0)),
                    m_velocity(Point3(0, 0, 0)),
                    m_acceleration(Point3(0, 0, 0)) {}

            PointShapedObject::PointShapedObject(const Point3 &position, const Point3 &rotation,
                                                 const Point3 &velocity, const Point3 &acceleration) :
                    Position(position, rotation),
                    m_velocity(velocity),
                    m_acceleration(acceleration) {}

            PointShapedObject::PointShapedObject(const PointShapedObject &obj) :
                    Position(obj),
                    m_velocity(obj.getVelocity()),
                    m_acceleration(obj.getAcceleration()) {}

            PointShapedObject::~PointShapedObject() {}

            PointShapedObject& PointShapedObject::operator=(const PointShapedObject &obj) {
                Position::operator=(obj);
                setVelocity(obj.getVelocity());
                setAcceleration(obj.getAcceleration());

                return (*this);
            }

            const Point3 PointShapedObject::getVelocity() const {
                return m_velocity;
            }

            void PointShapedObject::setVelocity(const Point3 &velocity) {
                m_velocity = velocity;
            }

            const Point3 PointShapedObject::getAcceleration() const {
                return m_acceleration;
            }

            void PointShapedObject::setAcceleration(const Point3 &acceleration) {
                m_acceleration = acceleration;
            }

            const string PointShapedObject::toString() const {
                stringstream s;
                s << Position::toString() << "@" << getVelocity().toString() << " with " << getAcceleration().toString();
                return s.str();
            }

            ostream& PointShapedObject::operator<<(ostream &out) const {
                // Serializer super class.
                Position::operator<<(out);

                // Serialize this class.
                SerializationFactory sf;

                Serializer &s = sf.getSerializer(out);

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('v', 'e', 'l', 'o', 'c', 'i', 't', 'y') >::RESULT,
                        m_velocity);

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('a', 'c', 'c', 'e', 'l') >::RESULT,
                        m_acceleration);

                return out;
            }

            istream& PointShapedObject::operator>>(istream &in) {
                // Deserializer super class.
                Position::operator>>(in);

                // Deserialize this class.
                SerializationFactory sf;

                Deserializer &d = sf.getDeserializer(in);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('v', 'e', 'l', 'o', 'c', 'i', 't', 'y') >::RESULT,
                       m_velocity);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('a', 'c', 'c', 'e', 'l') >::RESULT,
                       m_acceleration);

                return in;
            }

        }
    }
} // hesperia::data::environment
