using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Translator
{
    class StringWrapper
    {
        public string source { get; private set; }
        StringWrapper connection;
        public StringWrapper(string source)
        {
            this.source = source;
        }

        void ConnectTo(StringWrapper connection)
        { this.connection = connection; }

        public bool Propagate()
        {
            if (connection == null)
                return false;

            if (connection.source == null)
            {
                connection.source = source;
                return false;
            }

            return connection.source != source;
        }
    }
}