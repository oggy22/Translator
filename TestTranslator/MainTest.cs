using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using TestTranslator.Languages;

namespace TestTranslator
{
    [TestClass]
    public class MainTest
    {
        //todo: tests()
        [TestMethod]
        public void TestSerbian()
        {
            Serbian serbian = new Serbian();
            //serbian.tests();
        }

        [TestMethod]
        public void TestEnglish()
        {
            English english = new English();
            //english.tests();
        }
    }
}
