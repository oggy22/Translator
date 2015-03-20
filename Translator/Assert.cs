using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Translator
{
    static public class Assert
    {
        static public void Contains<T>(ICollection<T> set, T value)
        {
            if (!set.Contains(value))
            {
                throw new Exception("" + set + " does not contain " + value);
            }
        }

        static public void DoesNotContain(ICollection<string> set, string value)
        {
            if (set.Contains(value))
            {
                throw new Exception("" + set + " contains " + value);
            }
        }

        static public void IsTrue(bool condition)
        {
            if (!condition)
            {
                throw new Exception("The condition is not satisfied!");
            }
        }
    }
}
