using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Translator
{
    public class Language
    {
        public Language()
        {
            freeAttributes = new HashSet<Attributes.Attribute>();
            attributeCategories = new HashSet<Attributes.AttributeCategory>();
            dictionaryWords = new List<Words.DictionayrWord>();
            wordTypes = new HashSet<string>();
            tokenTypes = new HashSet<string>();
        }

        public IEnumerable<Node.WordNode> recognizeWord(string literal)
        {
            foreach (var word in dictionaryWords)
            {
                if (word.word == literal) yield break;
                    //yield return new Node.WordNode(word);
            }
        }

        public void addDictionaryWord(string expression)
        {
            new Words.DictionayrWord(expression);
        }

        public void addWordType(string wordType)
        {
            Assert.DoesNotContain(wordTypes, wordType);
            wordTypes.Add(wordType);
        }

        public void addTokenType(string tokenType)
        {
            Assert.DoesNotContain(tokenTypes, tokenType);
            Assert.DoesNotContain(wordTypes, tokenType);
            tokenTypes.Add(tokenType);
        }

        public void addAttributeCategory(string attributeCategory)
        {
            //Assert.DoesNotContain(attributeCategories.Keys, attributeCategory);
            //freeAttributes.Add(attributeCategory);
        }

        public void addAttribute(string attribute)
        {
            //Assert.DoesNotContain(freeAttributes, attribute);
            //freeAttributes.Add(attribute);
        }

        public void addAttributes(params string[] attributes)
        {
            foreach (var attr in attributes)
            {
                addAttribute(attr);
            }
        }

        protected void addCategory(string category, params string[] attributes)
        {

        }

        public void addDictionaryWord(string rule, string wordType, params string[] attributes)
        {
            //todo:
        }

        public Attributes.Attribute getAttribute(string attr)
        {
            return Attributes.Attribute.getAttribute(attr);
        }

        public Attributes.AttributeCategory getCategory(string attr)
        {
            return null;
            //foreach (Attributes.addAttributeCategory category in attr)
        }

        private void addWordAttribute(HashSet<string> attributes, string attribute)
        {
            //Assert.Contains(this.freeAttributes, attribute);
            Assert.DoesNotContain(attributes, attribute);
            attributes.Add(attribute);
        }

        public void addWord(string word, string wordtype, params string[] attrs)
        {
            Assert.Contains(wordTypes, wordtype);

            HashSet<string> attributes = new HashSet<string>();

            foreach (var attr in attrs)
            {
                addWordAttribute(attributes, attr);
            }            
        }

        public void addLexicalRule(string matchSrc, string wordType, string matchDst, params string[] attrs)
        {
            HashSet<string> attributes = new HashSet<string>(attrs);
            foreach (string s in attributesStack)
                attributes.Add(s);
            rules.Add(new LexicalRule(matchSrc, matchDst, wordType, attributes));
        }

        private List<LexicalRule> rules = new List<LexicalRule>();

        protected Stack<string> attributesStack = new Stack<string>();

        private Attributes.AttributeHolder createAttributeHolder(string[] attrAndCats, Dictionary<string, Attributes.AttributeHolder> take)
        {
            Attributes.AttributeHolder attributeHolder = new Attributes.AttributeHolder();
            foreach (string aac in attrAndCats)
            {
                // Check for attribute
                Attributes.Attribute attribute = Attributes.Attribute.getAttribute(aac);
                if (attribute != null)
                {
                    attributeHolder.addAttribute(attribute);
                    continue;
                }

                // Check for category
                string cat = char.IsDigit(aac.Last()) ? aac.Substring(0, aac.Length - 1) : aac;
                Attributes.AttributeCategory category = Attributes.AttributeCategory.getCategory(cat);
                if (category != null)
                {
                    attributeHolder.addCategory(category);
                    take[aac] = attributeHolder;
                    continue;
                }

                throw new Exception(aac + " is not recognized as attribute or category!");
            }
            return new Attributes.AttributeHolder();
        }

        private Node.NodeBase parseNode(string node)
        {
            //if (char.IsLetter(node.Last()))
            //    return new Node.LiteralNode(node);
            
            //if (node.Last() == ')')
            //{
            //    int openBracketIndex = node.IndexOf('(');
            //    Assert.IsTrue(openBracketIndex != -1);

            //    Attributes.AttributeHolder attributeHolder =
            //        createAttributeHolder(node.Substring(openBracketIndex + 1, node.Length - openBracketIndex - 1).Split(','), null);
            //}

            //return new Node.WordNode(wordText)
            ////return new Node.WordNode(dictionaryWords.First(w => w.word == node));
            return null;
        }

        public void addGrammarRule(string left, params string[] right)
        {
            //Node.TokenNode leftNode = Node.TokenNode.parse(left);
        }

        public void addGrammarRule(string left, string right)
        {
            Attributes.AttributeConsolidator consolidator = new Attributes.AttributeConsolidator();
            Node.TokenNode leftNode = Node.TokenNode.parse(left) as Node.TokenNode;
            List<Node.TokenNode> rigthNodes = new List<Node.TokenNode>();
            foreach (string r in right.Split(' '))
            {
                //rigthNodes.Add(Node.TokenNode.parse(r));
            }

            grammarRules.Add(new GrammarRule(leftNode, rigthNodes));
        }

        public void test(string text, bool expectedParse = true)
        {
            string[] words = text.Split(' ');
            int n = words.Count();
            List<Words.WordForm>[,] matrix = new List<Words.WordForm>[n, n];

            // Popoluate one-words
            for (int i=0; i<n; i++)
            {
                matrix[i,i] = new List<Words.WordForm>();
                foreach (var word in allWords())
                    if (word.word == words[i])
                        matrix[i, i].Add(word);
            }

            // Apply grammar rules
            for (int len=1; len<=n; len++)
            {
                for (int i=0; i<=n-len; i++)
                {
                    //todo:
                    //this.parseNode();
                }
            }

            // Check that the entire text is parsed
            if (expectedParse)
            {
                if (matrix[0, n - 1].Count() == 0)
                    throw new Exception("Could not parse the text '" + text + "'");
            }
            else
            {
                if (matrix[0, n - 1].Count() != 0)
                    throw new Exception("The text '" + text + "' is succesfully parsed");
            }
        }

        public HashSet<string> wordTypes { get; private set; }
        public HashSet<string> tokenTypes { get; private set; }
        public HashSet<Attributes.Attribute> freeAttributes { get; private set; }
        public HashSet<Attributes.AttributeCategory> attributeCategories { get; private set; }
        public List<Words.DictionayrWord> dictionaryWords { get; private set; }

        private List<GrammarRule> grammarRules = new List<GrammarRule>();

        private IEnumerable<Words.WordForm> allWords()
        {
            //todo:
            yield break;
        }
    }
}