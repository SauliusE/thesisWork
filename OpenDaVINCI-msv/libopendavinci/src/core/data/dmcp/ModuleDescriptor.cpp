/*
 * OpenDaVINCI.
 *
 * This software is open source. Please see COPYING and AUTHORS for further information.
 */

#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"

#include "core/data/dmcp/ModuleDescriptor.h"

namespace core {
    namespace data {
        namespace dmcp {

            using namespace core::base;

            ModuleDescriptor::ModuleDescriptor() :
        		SerializableData(),
                m_name(""),
                m_identifier(""),
                m_version(""),
                m_frequency(1)           
            {}

            ModuleDescriptor::ModuleDescriptor(const string& name,
                                               const string& identifier,
                                               const string& version,
                                               const float& frequency) :
                SerializableData(),
                m_name(name),
                m_identifier(identifier),
                m_version(version),
                m_frequency(frequency)
            {}

            ModuleDescriptor::ModuleDescriptor(const ModuleDescriptor &obj) :
                SerializableData(),
                m_name(obj.getName()),
                m_identifier(obj.getIdentifier()),
                m_version(obj.getVersion()),
                m_frequency(obj.getFrequency())
            {}

            ModuleDescriptor::~ModuleDescriptor() {}

            ModuleDescriptor& ModuleDescriptor::operator=(const ModuleDescriptor &obj) {
                m_name = obj.getName();
                m_identifier = obj.getIdentifier();
                m_version = obj.getVersion();
                m_frequency = obj.getFrequency();

                return (*this);
            }

            const string ModuleDescriptor::getName() const {
                return m_name;
            }

            const string ModuleDescriptor::getIdentifier() const {
                return m_identifier;
            }

            const string ModuleDescriptor::getVersion() const {
                return m_version;
            }

            float ModuleDescriptor::getFrequency() const {
                return m_frequency;
            }

            const string ModuleDescriptor::toString() const {
                stringstream ss;
                ss << m_name << "[" << m_identifier << "]" << m_version << "@" << m_frequency;

                return ss.str();
            }

            ostream& ModuleDescriptor::operator<<(ostream &out) const {
                SerializationFactory sf;

                Serializer &s = sf.getSerializer(out);

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('n', 'a', 'm', 'e') >::RESULT,
                        m_name);

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                        m_identifier);

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('v', 'e', 'r', 's', 'i', 'o', 'n') >::RESULT,
                        m_version);

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('f', 'r', 'e', 'q') >::RESULT,
                        m_frequency);

                return out;
            }

            istream& ModuleDescriptor::operator>>(istream &in) {
                SerializationFactory sf;

                Deserializer &d = sf.getDeserializer(in);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('n', 'a', 'm', 'e') >::RESULT,
                       m_name);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                       m_identifier);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('v', 'e', 'r', 's', 'i', 'o', 'n') >::RESULT,
                       m_version);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('f', 'r', 'e', 'q') >::RESULT,
                       m_frequency);

                return in;
            }

        }
    }
} // core::data::dmcp
