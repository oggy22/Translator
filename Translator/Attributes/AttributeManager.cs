using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Translator.Attributes
{
    public class AttributeManager
    {
        HashSet<AttributeCategory> categories;

        public AttributeManager()
        {
        }

        public void AddCategory(string name)
        {
            //categories.Add(new AttributeCategory(name));
        }

        public void AddAttribute(string name)
        {
            Attribute.getAttribute(name);
        }
    }
}