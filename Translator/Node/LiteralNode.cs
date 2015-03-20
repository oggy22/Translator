using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Translator.Node
{
    public class LiteralNode : NodeBase
    {
        readonly string literal;
        
        public LiteralNode(string word)
        {
            literal = word;
        }
    }
}
