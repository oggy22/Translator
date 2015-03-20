using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Translator;

namespace TestTranslator.Languages
{
    class Serbian : Language
    {
        public Serbian()
        {
            // Word Types
            addWordType("имен");
            addWordType("глаг");
            addWordType("замн");

            // Categories and Attributes
            addCategory("лиц", "1лиц", "2лиц", "3лиц");
            addCategory("род", "муш", "жен", "сре");
            addCategory("број", "једн", "множ");
            addCategory("пад", "ном", "ген", "дат", "акуз", "инстр", "лок");

            addLexicalRules();

            addDictionaryWords();

            // Grammar rules
            addGrammarRule("<ГС>", "ићи() у имен<акуз>");
            addGrammarRule("<РЕЧЕН>", "замен<лиц,број> ГС<лиц,број>");
        }

        private void addLexicalRules()
        {
            #region Pronouns
            // Add nominative case
            addLexicalRule("%", "замен", "%", "ном");

            // ja
            addLexicalRule("ја", "замен", "мене", "ген");
            addLexicalRule("ја", "замен", "мени", "дат");
            addLexicalRule("ја", "замен", "ми", "дат", "скр");
            addLexicalRule("ја", "замен", "мене", "акуз");
            addLexicalRule("ја", "замен", "ме", "акуз", "скр");
            addLexicalRule("ја", "замен", "мном", "инстр");
            addLexicalRule("ја", "замен", "мене", "лок");

            // ti
            addLexicalRule("ти", "замен", "тебе", "ген");
            addLexicalRule("ти", "замен", "теби", "дат");
            addLexicalRule("ти", "замен", "ти", "дат", "скр");
            addLexicalRule("ти", "замен", "тебе", "акуз");
            addLexicalRule("ти", "замен", "те", "акуз", "скр");
            addLexicalRule("ти", "замен", "тобом", "инстр");
            addLexicalRule("ти", "замен", "тебе", "лок");

            // mi
            addLexicalRule("ми", "замен", "нас", "ген");
            addLexicalRule("ми", "замен", "нама", "дат");
            addLexicalRule("ми", "замен", "нам", "дат", "скр");
            addLexicalRule("ми", "замен", "нас", "акуз");
            addLexicalRule("ми", "замен", "нама", "инстр");
            addLexicalRule("ми", "замен", "нама", "лок");

            // vi
            addLexicalRule("ви", "замен", "вас", "ген");
            addLexicalRule("ви", "замен", "вама", "дат");
            addLexicalRule("ви", "замен", "вам", "дат", "скр");
            addLexicalRule("ви", "замен", "вас", "акуз");
            addLexicalRule("ви", "замен", "вама", "инстр");
            addLexicalRule("ви", "замен", "вама", "лок");

            #endregion Pronouns

            #region Prisvojni pridevi
            this.attributesStack.Push("једн");

                this.attributesStack.Push("муш");
                addLexicalRule("%ој", "прзам", "%ој", "ном");
                addLexicalRule("%ој", "прзам", "%ог", "ген");
                addLexicalRule("%ој", "прзам", "%ом", "дат");
                addLexicalRule("%ој", "прзам", "%ој", "акуз");
                addLexicalRule("%ој", "прзам", "%ојим", "инстр");
                addLexicalRule("%ој", "прзам", "%ом", "лок");
                this.attributesStack.Pop();

                this.attributesStack.Push("жен");
                addLexicalRule("%ој", "прзам", "%оја", "ном");
                addLexicalRule("%ој", "прзам", "%оје", "ген");
                addLexicalRule("%ој", "прзам", "%ојој", "дат");
                addLexicalRule("%ој", "прзам", "%оју", "акуз");
                addLexicalRule("%ој", "прзам", "%ојом", "инстр");
                addLexicalRule("%ој", "прзам", "%ојој", "лок");
                this.attributesStack.Pop();

                this.attributesStack.Push("сре");
                addLexicalRule("%ој", "прзам", "%оје", "ном");
                addLexicalRule("%ој", "прзам", "%ог", "ген");
                addLexicalRule("%ој", "прзам", "%ом", "дат");
                addLexicalRule("%ој", "прзам", "%оје", "акуз");
                addLexicalRule("%ој", "прзам", "%ојим", "инстр");
                addLexicalRule("%ој", "прзам", "%ом", "лок");
                this.attributesStack.Pop();

            this.attributesStack.Pop(); //једн

            this.attributesStack.Push("множ");

                this.attributesStack.Push("муш");
                addLexicalRule("%ој", "прзам", "%оји", "ном");
                addLexicalRule("%ој", "прзам", "%ојих", "ген");
                addLexicalRule("%ој", "прзам", "%ојим", "дат");
                addLexicalRule("%ој", "прзам", "%оје", "акуз");
                addLexicalRule("%ој", "прзам", "%ојим", "инстр");
                addLexicalRule("%ој", "прзам", "%ојим", "лок");
                this.attributesStack.Pop();

                this.attributesStack.Push("жен");
                addLexicalRule("%ој", "прзам", "%оје", "ном");
                addLexicalRule("%ој", "прзам", "%ојих", "ген");
                addLexicalRule("%ој", "прзам", "%ојим", "дат");
                addLexicalRule("%ој", "прзам", "%оје", "акуз");
                addLexicalRule("%ој", "прзам", "%ојим", "инстр");
                addLexicalRule("%ој", "прзам", "%ојим", "лок");
                this.attributesStack.Pop();

                this.attributesStack.Push("сре");
                addLexicalRule("%ој", "прзам", "%оје", "ном");
                addLexicalRule("%ој", "прзам", "%ог", "ген");
                addLexicalRule("%ој", "прзам", "%ом", "дат");
                addLexicalRule("%ој", "прзам", "%оје", "акуз");
                addLexicalRule("%ој", "прзам", "%ојим", "инстр");
                addLexicalRule("%ој", "прзам", "%ом", "лок");
                this.attributesStack.Pop();

            this.attributesStack.Pop(); //множ


            #endregion

            #region Nouns

            // Singular
            attributesStack.Push("једн");
                addLexicalRule("%а", "имен", "%а", "ном");
                addLexicalRule("%а", "имен", "%е", "ген");
                addLexicalRule("%а", "имен", "%и", "дат");
                addLexicalRule("%а", "имен", "%у", "акуз");
                addLexicalRule("%а", "имен", "%ом", "инстр");
                addLexicalRule("%а", "имен", "%и", "лок");
            attributesStack.Pop();

            // Plural
            attributesStack.Push("множ");
                addLexicalRule("%а", "имен", "%е", "ном");
                addLexicalRule("%а", "имен", "%а", "ген");
                addLexicalRule("%а", "имен", "%ама", "дат");
                addLexicalRule("%а", "имен", "%е", "акуз");
                addLexicalRule("%а", "имен", "%ама", "инстр");
                addLexicalRule("%а", "имен", "%ама", "лок");
            attributesStack.Pop();
            
            #endregion


            #region Adjectives

            attributesStack.Push("жен");

            // Singular
            attributesStack.Push("једн");
            addLexicalRule("%", "имен", "%а", "ном");
            addLexicalRule("%", "имен", "%е", "ген");
            addLexicalRule("%", "имен", "%ој", "дат");
            addLexicalRule("%", "имен", "%у", "акуз");
            addLexicalRule("%", "имен", "%ом", "инстр");
            addLexicalRule("%", "имен", "%ој", "лок");
            attributesStack.Pop();

            // Plural
            attributesStack.Push("множ");
            addLexicalRule("%", "имен", "%е", "ном");
            addLexicalRule("%", "имен", "%их", "ген");
            addLexicalRule("%", "имен", "%им", "дат");
            addLexicalRule("%", "имен", "%е", "акуз");
            addLexicalRule("%", "имен", "%им", "инстр");
            addLexicalRule("%", "имен", "%им", "лок");
            attributesStack.Pop();
            
            attributesStack.Pop();
            #endregion

            #region Verbs

            attributesStack.Push("през");
                // Verbs -ci
                addLexicalRule("%ћи", "глаг", "%дем", "1лиц", "једн");
                addLexicalRule("%ћи", "глаг", "%деш", "2лиц", "једн");
                addLexicalRule("%ћи", "глаг", "%де", "3лиц", "једн");
                addLexicalRule("%ћи", "глаг", "%демо", "1лиц", "множ");
                addLexicalRule("%ћи", "глаг", "%дете", "2лиц", "множ");
                addLexicalRule("%ћи", "глаг", "%ду", "3лиц", "множ");

                // Verbs -ti
                addLexicalRule("%ти", "глаг", "%ам", "1лиц", "једн");
                addLexicalRule("%ти", "глаг", "%аш", "2лиц", "једн");
                addLexicalRule("%ти", "глаг", "%а", "3лиц", "једн");
                addLexicalRule("%ти", "глаг", "%амо", "1лиц", "множ");
                addLexicalRule("%ти", "глаг", "%ате", "2лиц", "множ");
                addLexicalRule("%ти", "глаг", "%аују", "3лиц", "множ");
            attributesStack.Pop();

            #endregion
        }

        void addGrammarRules()
        {
            #region NP
            addGrammarRule("<ИС>(род,број,пад,*)", "<прид>(род,број,пад) <имен>(род,број,пад,*)");
            #endregion

            #region VP
            addGrammarRule("<ГС>()", "<глаг>(мод,лиц,број) да <ГС>(лиц,број)");
            addGrammarRule("<ГС>()", "<глаг>(мод,лиц,број) да <ГС>(лиц,број)");
            #endregion

            #region Prepositions

            //place
            addGrammarRule("<ПО>(локац)", "у <ИС>(лок)");
            addGrammarRule("<ПО>(локац)", "на <ИС>(лок)");
            addGrammarRule("<ПО>", "са <ИС>(инстр)");

            //time
            addGrammarRule("<ПО>(врем)", "јуче");
            addGrammarRule("<ПО>(врем)", "сада");
            addGrammarRule("<ПО>(врем)", "данас");
            addGrammarRule("<ПО>(врем)", "сутра");
            #endregion

            #region Sentence
            addGrammarRule("<РЕЧЕН>", "<ИС>(лиц,број) <ГС>(лиц,број)");
            addGrammarRule("<РЕЧЕН>", "<Sent> <Prep>");
            #endregion
        }

        private void addDictionaryWordRule(string rule, string wordType)
        {

        }

        private void addDictionaryWords()
        {
            addDictionaryWordRule("%ти", "глаг");
            addDictionaryWordRule("%ћи", "глаг");

            #region Pronouns
            addDictionaryWord("ја<замен>(1лиц,једн)");
            addDictionaryWord("ти<замен>(2лиц,једн)");
            addDictionaryWord("он<замен>(3лиц,једн,муш)");
            addDictionaryWord("она<замен>(3лиц,једн,жен)");
            addDictionaryWord("оно<замен>(3лиц,једн,сре)");
            addDictionaryWord("ми<замен>(1лиц,множ)");
            addDictionaryWord("ви<замен>(2лиц,множ)");
            addDictionaryWord("они<замен>(3лиц,множ,муш)");
            addDictionaryWord("оне<замен>(3лиц,множ,жен)");
            addDictionaryWord("она<замен>(3лиц,множ,сре)");
            #endregion

            #region Nouns
            addDictionaryWord("жена<имен>(жен)");
            addDictionaryWord("књига<имен>(жен)");
            addDictionaryWord("мајка<имен>(жен)");
            addDictionaryWord("отац<имен>(муш)");
            addDictionaryWord("школа<имен>(жен)");
            #endregion

            addDictionaryWord("ићи<глаг>");
        }

        public void tests()
        {
            base.test("са лепом женом"); base.test("");
            base.test("ја хоћу да идем");
        }
    }
}
