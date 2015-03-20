using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Translator.Attributes
{
    public class Attribute
    {
        public readonly AttributeCategory category;
        
        public readonly string Name;

        private static HashSet<Attribute> attributes = new HashSet<Attribute>();

        private Attribute(string name, string category = null)
        {
            Name = name;
            if (attributes.Contains(this))
                throw new Exception("The attribute " + Name + " already exists");
            attributes.Add(this);
        }

        static public Attribute getAttribute(string name)
        {
            foreach (Attribute attr in attributes)
                if (attr.Name == name)
                    return attr;
            throw new Exception("The attribute " + name + " does not exist");
        }
    }
}
