using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Translator
{
    class Utils
    {
        /// <summary>
        /// Parses a query e.g "ici&leglag&re(prez)"
        /// </summary>
        /// <param name="text"></param>
        /// <param name="word"></param>
        /// <param name="wordType">The portion between &leglag&re or <c>null</c> if the brackets don't exist.</param>
        /// <param name="catsAndAttrs">Array of string separeted by comma The portion between "(" and ")". Set to null if these brackets don't exist.</param>
        static public void parseNode(string text, out string word, out string wordType, out string[] catsAndAttrs)
        {
            // text = "ici<glag>(prez)"

            // Get Word
            word = text.TakeWhile(c => char.IsLetter(c)).Aggregate(string.Empty, (s, c) => s + c);
            text = text.Substring(word.Length);

            // Get word type
            wordType = null;
            if (text.First() == '<')
                wordType = text.Substring(1, text.IndexOf('>') - 1);
            text = text.Substring(wordType == null ? 0 : wordType.Length + 2);

            // Get categories and attributes
            catsAndAttrs = null;
            if (text.First() == '(')
            {
                if (text.Last() != ')')
                    throw new Exception("Expecting attributes and categories in the brackets");
                text = text.Substring(1, text.Length - 2);
                catsAndAttrs = text.Split(',');
            }
        }
    }
}
