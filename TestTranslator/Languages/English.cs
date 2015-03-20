using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Translator;

namespace TestTranslator.Languages
{
    class English : Language
    {
        public English()
        {
            // Word Types
            addWordType("noun");
            addWordType("verb");
            addWordType("pron");

            // Tokens
            addTokenType("NP");
            addTokenType("VP");
            addTokenType("PREP");

            // Attributes and attribute Categories
            addCategory("num", "sing", "plur");
            addCategory("per", "1per", "2per", "3per");
            addCategory("gend", "masc", "fem", "neut");

            // Dictionary Words
            addDictionaryWords();

            // Lexical rules
            addLexicalRules();

            // Grammar rules
            addGrammarRules();
        }

        void addDictionaryWords()
        {
            #region Pronouns

            // Nominative
            addDictionaryWord("i<pron>(1per,sing)");
            addDictionaryWord("you<pron>(2per,sing)");
            addDictionaryWord("he<pron>(3per,sing,masc)");
            addDictionaryWord("she<pron>(3per,sing,fem)");
            addDictionaryWord("it<pron>(3per,sing,neut)");
            addDictionaryWord("we<pron>(1per,plur)");
            addDictionaryWord("you<pron>(2per,plur)");
            addDictionaryWord("they<pron>(3per,plur)");

            // Accusative
            addDictionaryWord("me<pron>(1per,sing,accus)");
            addDictionaryWord("you<pron>(2per,sing,accus)");
            addDictionaryWord("him<pron>(3per,sing,masc,accus)");
            addDictionaryWord("her<pron>(3per,sing,fem,accus)");
            addDictionaryWord("it<pron>(3per,sing,neut,accus)");
            addDictionaryWord("us<pron>(1per,plur,accus)");
            addDictionaryWord("you<pron>(2per,plur,accus)");
            addDictionaryWord("them<pron>(3per,plur,accus)");

            // Possesive pronouns
            addDictionaryWord("my<pron>(1per,sing,poss)");
            addDictionaryWord("your<pron>(2per,sing,poss)");
            addDictionaryWord("his<pron>(3per,sing,masc,poss)");
            addDictionaryWord("her<pron>(3per,sing,fem,poss)");
            addDictionaryWord("its<pron>(3per,sing,neut,poss)");
            addDictionaryWord("our<pron>(1per,plur,poss)");
            addDictionaryWord("your<pron>(2per,plur,poss)");
            addDictionaryWord("their<pron>(3per,plur,poss)");

            #endregion

            #region Nouns
            addDictionaryWord("book<noun>");
            addDictionaryWord("mother<noun>(fem)");
            addDictionaryWord("father<noun>(masc)");
            addDictionaryWord("school<noun>");
            #endregion

            #region Verbs
            addDictionaryWord("go<verb>");
            #endregion

            #region Adjective
            addDictionaryWord("bad<adj>");
            addDictionaryWord("good<adj>");
            addDictionaryWord("nice<adj>");
            #endregion
        }

        void addLexicalRules()
        {
            addLexicalRule("%", "noun", "%", "sing");
            addLexicalRule("%", "noun", "%s", "plur");

            #region regular verbs
            // Infinitive
            addLexicalRule("%", "verb", "%", "inf");
            addLexicalRule("%", "verb", "to %", "toinf");
            // Present
            addLexicalRule("%", "verb", "%", "sing", "1per");
            addLexicalRule("%", "verb", "%", "sing", "2per");
            addLexicalRule("%", "verb", "%s", "sing", "3per");
            addLexicalRule("%o", "verb", "%oes", "sing", "3per");   // does, goes
            addLexicalRule("%", "verb", "%", "plur");
            // Past
            addLexicalRule("%", "verb", "%ed", "perf");
            addLexicalRule("%", "verb", "%ed", "part");
            // -ing
            addLexicalRule("%", "verb", "%ing", "cont");
            #endregion

            #region irregular verbs
            addLexicalRule("go", "verb", "went", "perf");
            addLexicalRule("go", "verb", "gone", "part");
            addLexicalRule("send", "verb", "sent", "perf");
            addLexicalRule("send", "verb", "sent", "part");
            #endregion
        }

        void addGrammarRules()
        {
            #region NP
            addGrammarRule("<NP>(3per,*)", "<adj> <noun>(*)");
            addGrammarRule("<NP>(3per,*)", "<adj> <adj> <noun>(*)");
            addGrammarRule("<NP>(3per,*)", "<noun>(*) of <noun>");
            addGrammarRule("<NP>(3per,*)", "the <noun>(*)");
            addGrammarRule("<NP>(3per,*)", "<pron>(poss) <noun>(*)"); // my mother
            addGrammarRule("<NP>(3per,sing)", "a <noun>(sing)");
            #endregion

            #region VP
            addGrammarRule("<VP>(pl,pers,imper,neg)", "do not <verb>(inf)");
            addGrammarRule("<VP>()", "be(*) <adj>");

            // Tenses
            addGrammarRule("<VP>(pres,simple)", "<VP>(pres)");
            addGrammarRule("<VP>(pres,perf)", "have() <VP>(part)");
            addGrammarRule("<VP>(past,simple)", "<VP>(past)");
            addGrammarRule("<VP>(past,perf)", "<VP>(part)");
            addGrammarRule("<VP>(fut)", "will <VP>(inf)");

            // Verb phrases
            addGrammarRule("<VP>(*)", "send(*) <pron>(acus) <NP>");
            addGrammarRule("<VP>(*)", "tell(*) <pron>(acus) about <NP>");
            #endregion

            #region Prepositions
            
            //place
            addGrammarRule("<Prep>(loc)", "at <NP>");
            addGrammarRule("<Prep>(loc)", "in <NP>");
            addGrammarRule("<Prep>(loc)", "on <NP>");

            //time
            addGrammarRule("<Prep>(time)", "yesterday");
            addGrammarRule("<Prep>(time)", "now");
            addGrammarRule("<Prep>(time)", "today");
            addGrammarRule("<Prep>(time)", "tomorrow");
            addGrammarRule("<Prep>(time)", "right now");
            #endregion

            #region Sentence
            addGrammarRule("<Sent>", "<NP>(per,pl) <VP>(per,pl)");
            addGrammarRule("<Sent>", "<Sent> <Prep>");
            #endregion
        }

        public void tests()
        {
            base.test("I am fine");
            base.test("This house is nice");
            base.test("My mother sent me a book");
            base.test("I have seen your father");
            base.test("He will tell you about it");
        }
    }
}