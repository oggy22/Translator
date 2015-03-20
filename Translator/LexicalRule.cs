using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Translator
{
    public class LexicalRule
    {
        string src, dst;
        int srcJokerPos, dstJokerPos;

        string wordType;
        HashSet<string> attributes;

        public LexicalRule(string src, string dst, string wordType, HashSet<string> attributes)
        {
            int jokerSrcCount = src.Count(c => c == '%');
            int jokerDstCount = dst.Count(c => c=='%');

            Assert.IsTrue(jokerSrcCount <= 1);
            Assert.IsTrue(jokerSrcCount == jokerDstCount);

            srcJokerPos = src.IndexOf('%');
            dstJokerPos = dst.IndexOf('%');
            
            this.src = src;
            this.dst = dst;
            this.wordType = wordType;
            this.attributes = attributes;
        }

        public string CreateWordForm(Words.DictionayrWord word)
        {
            if (word.wordType != wordType)
                return null;

            if (srcJokerPos == -1)
            {
                if (word.word != src)
                    return null;

                return dst;
            }

            string pre = word.word.Substring(0, srcJokerPos);

            // Check the pre-joker part
            if (pre != src.Substring(0, srcJokerPos))
                return null;

            string post = word.word.Substring(srcJokerPos + 1);

            // Check the after-joker part
            if (post != src.Substring(srcJokerPos + 1))
                return null;

            return dst.Replace("%", word.word.Substring(srcJokerPos, word.word.Length - pre.Length - post.Length));
        }

        private bool match(string word)
        {
            return true;
        }
    }
}