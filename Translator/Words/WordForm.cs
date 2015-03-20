using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Translator.Words
{
    class WordForm
    {
        public readonly DictionayrWord dictWord;
        public readonly string word;
        public readonly HashSet<string> attributes;
        public string WordType
        {
            get
            {
                return dictWord.wordType;
            }
        }

        public bool containsAttribute(string attribute)
        {
            return attributes.Contains(attribute);// || dictWord
        }
    }
}
