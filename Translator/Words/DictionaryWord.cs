using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Translator.Words
{
    public class DictionayrWord : WordBase
    {
        public DictionayrWord(string word, string wordType, HashSet<string> attributes)
        {
            this.word = word;
            this.wordType = wordType;
            this.Attributes = attributes;
        }

        public DictionayrWord(string wordExpression) : base(wordExpression)
        {
            string[] catsAndAttrs;
            //Utils.parseNode(wordExpression, out word, out wordType, out catsAndAttrs);
        }

        public readonly string word;
        public readonly string wordType;
        public readonly HashSet<string> Attributes;
    }
}
