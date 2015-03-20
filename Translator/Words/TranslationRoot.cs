using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Translator.Words
{
    class TranslationRoot : WordQuery
    {
        public TranslationRoot(string root, string children) : base(root)
        {
            foreach (var child in children.Split(' '))
            {
                this.children.Add(new WordQuery(child));
            }
        }

        List<WordQuery> children;
    }
}