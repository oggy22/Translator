using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Translator.Node
{
    class TokenNode : NodeBase
    {
        readonly string token;
        readonly string[] catsAndAttrs;

        public TokenNode(string token, string[] catsAndAttrs)
        {
            this.token = token;
            this.catsAndAttrs = catsAndAttrs;
        }
    }
}