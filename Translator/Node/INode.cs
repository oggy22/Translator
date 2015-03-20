using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Translator.Node
{
    public abstract class NodeBase
    {
        public Attributes.AttributeHolder attributeHolder
        {
            get;
            private set;
        }

        static public NodeBase parse(string text)
        {
            // text = "ici<glag>(prez)"

            // Get Word
            string word = text.TakeWhile(c => char.IsLetter(c)).Aggregate(string.Empty, (s, c) => s + c);
            text = text.Substring(word.Length);

            // Get word type
            string wordType = null;
            if (text.First() == '<')
                wordType = text.Substring(1, text.IndexOf('>') - 1);
            text = text.Substring(wordType == null ? 0 : wordType.Length + 2);

            // Get categories and attributes
            string[] catsAndAttrs = null;
            if (text.Length > 0 && text.First() == '(')
            {
                if (text.Last() != ')')
                    throw new Exception("Expecting attributes and categories in the brackets");
                catsAndAttrs = text.Split(',');
            }

            if (word!=string.Empty && wordType == null && catsAndAttrs == null)
                return new LiteralNode(word);

            if (word == string.Empty)
                return new TokenNode(wordType, catsAndAttrs);

            return new WordNode(word, catsAndAttrs);
        }

        //private Tuple<List<Attributes.Attribute>, List<Attributes.AttributeCategory>> getAttributesAndCategories(string catsAndAttrs)
        //{
        //    string[] t = catsAndAttrs.Split(',');
        //    Language language = null;

        //}
    }
}