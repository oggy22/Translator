using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Translator.Words
{
    class WordQuery : WordBase
    {
        public WordQuery(string query) : base(query)  // e.g. "go(1st,sing)" 
        {

        }

        public bool matches(WordForm word)
        {
            // Check WordType
            if (wordType != null)
                if (wordType != word.WordType)
                    return false;

            // Check Attributes
            foreach (var attr in attributes)
            {
                if (!word.containsAttribute(attr))
                    return false;
            }

            return true;
        }
    }
}
