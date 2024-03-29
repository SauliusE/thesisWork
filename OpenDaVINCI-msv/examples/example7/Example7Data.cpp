/*
 * OpenDaVINCI.
 *
 * This software is open source. Please see COPYING and AUTHORS for further information.
 */

#include "core/base/Hash.h"
#include "core/base/LCMDeserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/LCMSerializer.h"

#include "Example7Data.h"
//#include <inttypes.h>

namespace examples {

	using namespace std;
	using namespace core::base;

	Example7Data::Example7Data() :
		m_numericalValue(0),
		m_stringValue(""),
		m_bool(true),
		m_char('S'),
		m_uc('E'),
		m_int32(123123),
		m_float(23.34),
		m_double(23123123213213123){}

	Example7Data::Example7Data(const Example7Data &obj) :
			SerializableData(),
			m_numericalValue(obj.m_numericalValue),
			m_stringValue(obj.m_stringValue) {}

	Example7Data::~Example7Data() {}

	Example7Data& Example7Data::operator=(const Example7Data &obj) {
		m_numericalValue = obj.m_numericalValue;
		m_stringValue = obj.m_stringValue;

		return (*this);
	}

	uint32_t Example7Data::getNumericalValue() const {
		return m_numericalValue;
	}

	void Example7Data::setNumericalValue(const uint32_t &nv) {
		m_numericalValue = nv;
	}

	const string Example7Data::getStringValue() const {
		return m_stringValue;
	}

	void Example7Data::setStringValue(const string &sv) {
		m_stringValue = sv;
	}

	const string Example7Data::toString() const {
		stringstream s;
		s << "int32_t : " ;
		s << m_numericalValue;
		s << " ";
		s << "string: ";
		s << m_stringValue;
		s << " ";
		s << "Bool : ";
		s << m_bool;
		s << " "<<endl;
		//s << "char : ";
		//s << m_char;
		//s << " ";
		//s << "unsigned char : ";
		//s << m_uc;
		//s << " ";
		s << "float " ;
		s << m_float;
		s << " ";
		s << "double " ;
		s << m_double;
		s << " ";

		return s.str();
	}

	ostream& Example7Data::operator<<(ostream &out) const {
        SerializationFactory sf;

        LCMSerializer &s = sf.getLCMSerializer(out);

        s.write(LCM32 < OPENDAVINCI_CORE_STRINGLITERAL4('n', 'u', 'm', 'b') >::RESULT, m_numericalValue);
        s.write(LCM32 < OPENDAVINCI_CORE_STRINGLITERAL4('s', 't', 'r', 'i') >::RESULT, m_stringValue);
        s.write(LCM32 < OPENDAVINCI_CORE_STRINGLITERAL4('b', 'o', 'b', 'o') >::RESULT, m_bool);
        s.write(LCM32 < OPENDAVINCI_CORE_STRINGLITERAL4('f', 'l', 'o', 'a') >::RESULT, m_float);
        s.write(LCM32 < OPENDAVINCI_CORE_STRINGLITERAL4('d', 'o', 'u', 'b') >::RESULT, m_double);
   /*     
        ROSSerializer &s = sf.getROSSerializer(out);
        s.write(1, m_numericalValue);
        s.write(2,m_stringValue);
        s.write(3,m_bool);
        s.write(4, m_float);
        s.write(5, m_double);
*/
        //int64_t hash = s.getHash();
        //printf("HASH17: %016"PRIx64"\n", hash);

        return out;
	}

	istream& Example7Data::operator>>(istream &in) {
		SerializationFactory sf;
	//	LCMDeserializer &d = sf.getLCMDeserializer(in);
                LCMDeserializer &d = sf.getLCMDeserializer(in);
        cout << endl;
		d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('n', 'u', 'm') >::RESULT,
			   m_numericalValue);
		d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('s', 't', 'r') >::RESULT,
			   m_stringValue);
		d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('a', 't', 'r') >::RESULT,
				m_bool);
		d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('z', 't', 'r') >::RESULT,
				m_float);
		d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('b', 't', 'r') >::RESULT,
				m_double);

		return in;
	}


} // examples

