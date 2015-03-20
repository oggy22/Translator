using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Translator.Words;

namespace Translator
{
    public class Translator
    {
        Language srcLanguage, dstLanguage;

        List<Tuple<Words.TranslationRoot, Words.TranslationRoot>> translations;

        public Translator(Language srcLanguage, Language dstLanguage)
        {
            this.srcLanguage = srcLanguage;
            this.dstLanguage = dstLanguage;
        }

        IEnumerable<Node.NodeBase> getNodes(string word)
        {
            yield return new Node.LiteralNode(word);


        }

        string translateSentence(string[] words)
        {
            return null;
        }

        public void AddTranslation(string src, string dst)
        {
            translations.Add(new Tuple<TranslationRoot, TranslationRoot>(new TranslationRoot(src,""), new TranslationRoot(dst, "")));
        }

        public void AddTranslation(string srcRoot, string srcExpanded, string dstRoot, string dstExpanded)
        {

        }

        public string translate(string text)
        {
            return text;
        }
        public string translateBack(string text)
        {
            return text;
        }
    }
}