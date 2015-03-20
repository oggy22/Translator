using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Translator.Attributes
{
    public class AttributeCategory
    {
        HashSet<Attribute> attributes;
        
        static HashSet<AttributeCategory> categories = new HashSet<AttributeCategory>();
        
        public Attribute defaultAttribute { get; private set; }

        public string Name { get; private set; }

        private AttributeCategory(string name)
        {
            Name = name;
        }

        static public AttributeCategory getCategory(string name)
        {
            return categories.FirstOrDefault(cat => cat.Name == name);
        }

        static public AttributeCategory retrieveCategory(string name)
        {
            AttributeCategory category = categories.FirstOrDefault(cat => cat.Name == name);
            if (category == null)
            {
                categories.Add(category = new AttributeCategory(name));
            }
            return category;
        }
    }
}
