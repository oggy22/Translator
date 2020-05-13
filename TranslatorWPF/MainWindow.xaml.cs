
using Microsoft.Win32;
using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;

namespace TranslatorWPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        Process proc;
        System.IO.StreamWriter processInput;

        public MainWindow()
        {
            InitializeComponent();
            InitTranslatorProcess();
        }

        private void InitTranslatorProcess()
        {
            proc = new Process();
            proc.StartInfo.FileName = System.IO.Directory.GetCurrentDirectory() + "\\TranslatorCpp.exe";

            // set up output redirection
            proc.StartInfo.RedirectStandardOutput = true;
            proc.StartInfo.RedirectStandardError = true;
            proc.StartInfo.RedirectStandardInput = true;
            proc.EnableRaisingEvents = true;
            proc.StartInfo.CreateNoWindow = true;
            proc.StartInfo.UseShellExecute = false;

            // see below for output handler
            proc.ErrorDataReceived += proc_DataReceived;
            proc.OutputDataReceived += proc_DataReceived;

            proc.Start();

            proc.BeginErrorReadLine();
            proc.BeginOutputReadLine();
            processInput = proc.StandardInput;
        }

        void proc_DataReceived(object sender, DataReceivedEventArgs e)
        {
            //TxtDst.Dispatcher.Invoke(
            //    () => { TxtDst.Text = e.Data + "\n"; });
        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            string key = txtSearch.Text;

            if (tabPalindromes.IsSelected)
            {
                CollectionViewSource.GetDefaultView(pc).Filter = obj =>
                {
                    return (obj as Palindrome).Palindrom.Contains(key);
                };
                int count = dataPalindromes.Items.Count;
                lblCount.Content = $"{count} palindromes shown";
            }
            else if (tabWords.IsSelected)
            {
                if (txtSearch.Text == "")
                {
                    txtWords.Select(txtWords.SelectionStart, 0);
                }
                else
                {
                    int pos = txtWords.Text.IndexOf(key);
                    if (pos >= 0)
                    {
                        txtWords.Focus();
                        txtWords.Select(pos, key.Length);
                        txtWords.ScrollToLine(txtWords.GetLineIndexFromCharacterIndex(pos));
                        txtSearch.Focus();
                    }
                }
            }
        }

        private async void MenuItem_Palindromes(object sender, RoutedEventArgs e)
        {
            string header = (sender as MenuItem).Header as string;
            int depth = int.Parse(header);
            Application.Current.Dispatcher.Invoke(new Action(() =>
            {
                this.Title = $"Generating palindromes (depth={depth})";
            }));
            await GeneratePalindromes(depth, false);
        }

        private async void MenuItem_PalindromesWithParse(object sender, RoutedEventArgs e)
        {
            string header = (sender as MenuItem).Header as string;
            int depth = int.Parse(header);
            Application.Current.Dispatcher.Invoke(new Action(() =>
            {
                this.Title = $"Generating palindromes with parse (depth={depth})";
            }));
            await GeneratePalindromes(depth, true);
        }

        private async Task GeneratePalindromes(int depth, bool parse)
        {
            var proc = RunProcess(parse ? $"-palindromep:SR {depth}" : $"-palindrome:SR {depth}", true);
            DateTime start = DateTime.Now;
            await proc.StandardOutput.ReadLineAsync();

            this.dataPalindromes.ItemsSource = null;
            
            pc.Clear();
            Application.Current.Dispatcher.Invoke(new Action(() =>
            {
                this.Title = $"Parsing palindromes (depth={depth})";
            }));
            int count = 0;
            while (!proc.StandardOutput.EndOfStream)
            {
                string line = proc.StandardOutput.ReadLine();

                // The last line contains the number of palindrome
                if (char.IsDigit(line[0]))
                    continue;

                Palindrome pal = new Palindrome(line, parse);
                pc.Add(pal);

                count++;
                if (count % 1000 == 0)
                    Application.Current.Dispatcher.Invoke(new Action(() =>
                    {
                        this.Title = $"Received {count} palindromes (depth={depth})";
                    }));
            }
            dataPalindromes.ItemsSource = pc;
            TimeSpan time = DateTime.Now - start;
            this.Title = $"{pc.Count} palindromes loaded (depth={depth}) {(int)time.TotalSeconds}sec";
            proc.WaitForExit();
        }

        ObservableCollection<Palindrome> pc = new ObservableCollection<Palindrome>();
        private Process RunProcess(string args, bool unicode)
        {
            var proc = new Process
            {
                StartInfo = new ProcessStartInfo
                {
                    FileName = "TranslatorCpp.exe",
                    Arguments = args,
                    UseShellExecute = false,
                    RedirectStandardOutput = true,
                    CreateNoWindow = true
                }
            };

            if (unicode)
                proc.StartInfo.StandardOutputEncoding = Encoding.Unicode;
            proc.Start();

            return proc;
        }

        private void MenuItem_ListWords(object sender, RoutedEventArgs e)
        {
            string language = (sender as MenuItem).Header as string;
            var proc = RunProcess($"-list:{language}", language == "SR");
            string text = proc.StandardOutput.ReadToEnd();
            txtWords.Text = text;
        }

        private void MenuItem_RandomSentence(object sender, RoutedEventArgs e)
        {
            string language = (sender as MenuItem).Header as string;
            var proc = RunProcess($"-random:{language}", language == "SR");
            string text = proc.StandardOutput.ReadToEnd();
            txtWords.Text = text;
        }

        private void MenuItem_PalindromesLoad(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Coma separated files (*.csv)|*.csv|All files (*.*)|*.*";

            if (openFileDialog.ShowDialog() == true)
            {
                DateTime start = DateTime.Now;
                StreamReader fileStreamRead = new StreamReader(openFileDialog.FileName, Encoding.Unicode);
                fileStreamRead.ReadLine();

                pc.Clear();
                Application.Current.Dispatcher.Invoke(new Action(() =>
                {
                    this.Title = $"Loading palindromes";
                }));
                int count = 0;
                bool parse = false;
                while (!fileStreamRead.EndOfStream)
                {
                    string line = fileStreamRead.ReadLine();

                    // The last line contains the number of palindrome
                    if (char.IsDigit(line[0]))
                        continue;

                    if (count == 0)
                    {
                        int columns = line.Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries).Length;
                        switch (columns)
                        {
                            case 6: parse = false; break;
                            case 7: parse = true; break;
                            default:
                                throw new InvalidDataException($"CSV file has {columns} columns, but 6 or 7 are expected");
                        }
                    }
                    Palindrome pal = new Palindrome(line, parse);
                    pc.Add(pal);

                    count++;
                    if (count % 1000 == 0)
                        Application.Current.Dispatcher.Invoke(new Action(() =>
                        {
                            this.Title = $"Loaded {count} palindromes";
                        }));
                }

                dataPalindromes.ItemsSource = pc;
                TimeSpan time = DateTime.Now - start;
                this.Title = $"{pc.Count} palindromes loaded {(int)time.TotalSeconds}sec";
            }
        }
    }

    public class Palindrome : INotifyPropertyChanged
    {
#pragma warning disable 67
        public event PropertyChangedEventHandler PropertyChanged;
#pragma warning restore 67

        public Palindrome(string line, bool parse)
        {
            int pos = line.IndexOf(',');
            Palindrom = line.Substring(0, pos);
            Chars = GetInt(line, ref pos);
            Letters = GetInt(line, ref pos);
            Words = GetInt(line, ref pos);
            AvgWord = GetFloat(line, ref pos);
            StdWord = GetFloat(line, ref pos);
            if (parse)
                Parse = GetFloat(line, ref pos);
        }

        static int GetInt(string line, ref int pos)
        {
            int result = 0;

            while (!char.IsDigit(line[pos])) pos++;

            for (; pos < line.Length && char.IsDigit(line[pos]); pos++)
            {
                result += (int)(line[pos] - '0') + 10 * result;
            }

            return result;
        }

        static float GetFloat(string line, ref int pos)
        {
            float result = GetInt(line, ref pos);
            if (pos >= line.Length || line[pos] != '.')
                return result;
            pos++;

            float dec = 1.0f;
            for (; pos < line.Length && char.IsDigit(line[pos]); pos++)
            {
                dec *= 0.1f;
                result += dec * (int)(line[pos] - '0');
            }

            return result;
        }

        public string Palindrom { get; set; }

        public int Words { get; set; }

        public int Letters { get; set; }

        public int Chars { get; set; }

        public float AvgWord { get; set; }

        public float StdWord { get; set; }

        public float Parse { get; set; }
    }
}