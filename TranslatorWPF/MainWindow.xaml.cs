
using System.Diagnostics;

using System.Windows;
using System.Windows.Controls;


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
            TxtDst.Dispatcher.Invoke(
                () => { TxtDst.Text = e.Data + "\n"; });
        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            processInput.WriteLine(TxtSrc.Text + "\n");
        }
    }
}