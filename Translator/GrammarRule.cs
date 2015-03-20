using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Translator.Node;

namespace Translator
{
    class GrammarRule
    {
        TokenNode left;

        List<TokenNode> right;

        public GrammarRule(TokenNode left, List<TokenNode> right)
        {
            this.left = left;
            this.right = right;
        }
    }
}