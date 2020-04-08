
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.Text;
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
            CollectionViewSource.GetDefaultView(pc).Filter = obj =>
            {
                return (obj as Palindrome).Palindrom.Contains(txtSearch.Text);
            };
            int count = dataPalindromes.Items.Count;
            lblCount.Content = $"{count} palindromes shown";
        }

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            string header = (sender as MenuItem).Header as string;
            int depth = int.Parse(header);
            this.Title = $"Generating palindromes (depth={depth})";

            var proc = new Process
            {
                StartInfo = new ProcessStartInfo
                {
                    FileName = "TranslatorCpp.exe",
                    Arguments = $"-palindrome:SR {depth}",
                    UseShellExecute = false,
                    RedirectStandardOutput = true,
                    CreateNoWindow = true
                }
            };

            proc.StartInfo.StandardOutputEncoding = Encoding.Unicode;
            proc.Start();
            proc.StandardOutput.ReadLine();
            
            pc.Clear();
            while (!proc.StandardOutput.EndOfStream)
            {
                string line = proc.StandardOutput.ReadLine();
                
                if (char.IsDigit(line[0]))
                    continue;

                Palindrome pal = new Palindrome(line);
                pc.Add(pal);
            }
            dataPalindromes.ItemsSource = pc;
            this.Title = $"{pc.Count} palindromes loaded (depth={depth})";
            proc.WaitForExit();
        }

        ObservableCollection<Palindrome> pc = new ObservableCollection<Palindrome>();
    }

    public class Palindrome : INotifyPropertyChanged
    {
        public Palindrome(string line)
        {
            int pos = line.IndexOf(',');
            Palindrom = line.Substring(0, pos);
            Chars = GetInt(line, ref pos);
            Letters = GetInt(line, ref pos);
            Words = GetInt(line, ref pos);
            AvgWord = GetFloat(line, ref pos);
            StdWord = GetFloat(line, ref pos);
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

        public event PropertyChangedEventHandler PropertyChanged;
    }
}