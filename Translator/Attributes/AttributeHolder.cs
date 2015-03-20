using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Translator.Attributes
{
    public class AttributeHolder
    {
        private Dictionary<AttributeCategory, Attribute> function;

        private HashSet<Attribute> freeAttributes;

        public void addAttribute(Attribute attribute)
        {
            freeAttributes.Add(attribute);
        }

        public void addCategory(AttributeCategory category)
        {
            function[category] = null;
        }

        public Attribute this[string category]
        {
            get
            {
                AttributeCategory attributeCategory = AttributeCategory.getCategory(category);
                return function[attributeCategory];
            }
        }
    }
}
