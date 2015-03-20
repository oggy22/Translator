using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Translator.Words
{
    public abstract class WordBase
    {
        public string literal;
        public string wordType;
        public HashSet<string> attributes = new HashSet<string>();

        public WordBase(string query)
        {
            // Take the literal part if any
            if (char.IsLetter(query[0]))
            {
                int pos;
                for (pos = 1; pos < query.Length && char.IsLetter(query[pos]); pos++) ;
                literal = query.Substring(0, pos);
                query = query.Substring(pos);
            }

            // Take the formal part if any
            if (query[0] == '<')
            {
                int pos;
                for (pos = 1; pos < query.Length && query[pos] != '>'; pos++) ;
                wordType = query.Substring(1, pos - 1);
                query = query.Substring(pos + 1);
            }

            if (query.Length == 0)
                return;

            // Take the arguments
            Assert.IsTrue(query.First() == '(');
            Assert.IsTrue(query.Last() == ')');
            foreach (var attr in query.Substring(1, query.Length - 2).Split(','))
            {
                attributes.Add(attr);
            }
        }

        public WordBase() { }
    }
}
