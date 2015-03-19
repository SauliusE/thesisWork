/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#ifndef HESPERIA_SITUATION_SITUATIONFACTORY_H_
#define HESPERIA_SITUATION_SITUATIONFACTORY_H_

#include <string>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"
#include "core/base/Mutex.h"
#include "core/exceptions/Exceptions.h"
#include "core/wrapper/parser/ParserErrorListener.h"
#include "core/wrapper/parser/ParserTokenListener.h"

#include "hesperia/data/situation/Situation.h"

namespace hesperia {
    namespace situation {

        using namespace std;

        /**
         * This class produces the complex core::data::Situation data structure.
         */
        class OPENDAVINCI_API SituationFactory {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                SituationFactory(const SituationFactory &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                SituationFactory& operator=(const SituationFactory &);

            private:
                SituationFactory();

            public:
                virtual ~SituationFactory();

                /**
                 * This method returns a static instance for this factory.
                 *
                 * @return Instance of this factory.
                 */
                static SituationFactory& getInstance();

                /**
                 * This method returns the complex data structure for a situation.
                 *
                 * @param s String to be parsed.
                 * @return Situation data structure.
                 * @throws InvalidArgumentException if the input could be parsed.
                 */
                data::situation::Situation getSituation(const string &s) throw (core::exceptions::InvalidArgumentException);

            private:
                static core::base::Mutex m_singletonMutex;
                static SituationFactory* m_singleton;

                /**
                 * This class is responsible for creating the data structure.
                 */
                class SITGrammarTokenListener : public core::wrapper::parser::ParserTokenListener {
                    private:
                        /**
                         * "Forbidden" copy constructor. Goal: The compiler should warn
                         * already at compile time for unwanted bugs caused by any misuse
                         * of the copy constructor.
                         */
                        SITGrammarTokenListener(const SITGrammarTokenListener &);

                        /**
                         * "Forbidden" assignment operator. Goal: The compiler should warn
                         * already at compile time for unwanted bugs caused by any misuse
                         * of the assignment operator.
                         */
                        SITGrammarTokenListener& operator=(const SITGrammarTokenListener &);

                    public:
                        /**
                         * Constructor.
                         *
                         * @param s Scenario to construct using the incoming tokens.
                         */
                        SITGrammarTokenListener(data::situation::Situation &s);

                        virtual ~SITGrammarTokenListener();

                        virtual void nextToken(const core::wrapper::parser::ParserToken &token);

                    private:
                        data::situation::Situation &m_situation;
                };

                /**
                 * This class is called whenever an error occurs during parsing.
                 */
                class SITGrammarErrorListener : public core::wrapper::parser::ParserErrorListener {
                    private:
                        /**
                         * "Forbidden" copy constructor. Goal: The compiler should warn
                         * already at compile time for unwanted bugs caused by any misuse
                         * of the copy constructor.
                         */
                        SITGrammarErrorListener(const SITGrammarErrorListener &);

                        /**
                         * "Forbidden" assignment operator. Goal: The compiler should warn
                         * already at compile time for unwanted bugs caused by any misuse
                         * of the assignment operator.
                         */
                        SITGrammarErrorListener& operator=(const SITGrammarErrorListener &);

                    public:
                        SITGrammarErrorListener();

                        virtual ~SITGrammarErrorListener();

                        void errorToken(core::wrapper::parser::ParserError &error);

                        /**
                         * This method returns the occurred error.
                         *
                         * @return Occurred error.
                         */
                        const string getLastError() const;

                    private:
                        string m_lastError;
                };
        };

    }
} // hesperia::situation

#endif /*HESPERIA_CORE_SITUATION_SITUATIONFACTORY_H_*/
