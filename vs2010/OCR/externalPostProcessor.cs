using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NOCR
{
    public class externalPostProcessor
    {

        System.String inputFileName, outputFileName;

        System.String outputString;
        public externalPostProcessor(System.String applicationPath, System.String PostProcessorApplicationFileName) //,System.String *inputFileName,System.String *outputFileName)
        {
            // String *applicationPath = Application.StartupPath.ToString();

            applicationPath += string.Concat(applicationPath, "\\");
            System.String applicationName = string.Concat(applicationPath, PostProcessorApplicationFileName);
            this.outputFileName = System.String.Concat(applicationPath, "rawOutput.txt");


            try
            {
                System.Diagnostics.Process shellProcess = new System.Diagnostics.Process();
                shellProcess.StartInfo.FileName = applicationName;

                shellProcess.StartInfo.CreateNoWindow = true;
                shellProcess.StartInfo.RedirectStandardError = true;
                shellProcess.StartInfo.UseShellExecute = false;
                shellProcess.StartInfo.WorkingDirectory = applicationPath;

                //System.Windows.Forms.MessageBox.Show(shellProcess.StartInfo.get_WorkingDirectory().ToString());
                shellProcess.Start();
                shellProcess.WaitForExit();
                // System.Windows.Forms.MessageBox.Show(applicationName,"running");
                shellProcess.Close();
                /* if(shellProcess_Exited){
                     System.Windows.Forms.MessageBox.Show("exitted");
                 }*/
            }
            catch (System.Exception ex)
            {
                System.Windows.Forms.MessageBox.Show(ex.ToString(), "Error running PostProcessor", System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Error);
            }


        }


        System.String getText()
        {
            return this.outputFileName;
        }

        public void tryNewProcesor()
        {
            // Start the child process.
            System.Diagnostics.Process p1 = new System.Diagnostics.Process();
            // Redirect the output stream of the child process.
            p1.StartInfo.UseShellExecute = false;
            p1.StartInfo.RedirectStandardOutput = true;
            p1.StartInfo.FileName = "ocrTextProcessor.exe";
            p1.Start();
            // Do not wait for the child process to exit before
            // reading to the end of its redirected stream.
            // p.WaitForExit();
            // Read the output stream first and then wait.
            System.String output = p1.StandardOutput.ReadToEnd();
            p1.WaitForExit();

        }

        /// <summary>
        /// Processes Text -- Remove postprocessor 
        /// </summary>
        /// <returns></returns>
        public string PostProcess()
        {

            System.String inputText= "";
            System.String processedText="";
            String arg0, inputFileName, outputFileName;
            inputFileName = "rawInput.txt";
            outputFileName = "rawOutput.txt";
            System.IO.StreamWriter swLog = new System.IO.StreamWriter("PostProcessr.log");

            try
            {
                //inputFileName = argument 0
                //Reading input file from argument 0
                System.String tempStr;
                System.IO.StreamReader sr = new System.IO.StreamReader(inputFileName);
                while (!System.String.IsNullOrEmpty(tempStr = sr.ReadLine()))
                {
                    inputText += string.Concat(inputText, tempStr, "\n");

                }
                sr.Close();
                System.Console.Write(inputText);

                PostProcessor pr = new PostProcessor(inputText);
                swLog.WriteLine("\n---------Input -----------\n");
                swLog.Write(inputText);
                swLog.WriteLine("\n---------Output -----------\n");

                processedText = pr.TextPostProcessor();
                //outputFileName = argument 1
                //Reading input file from argument 1
                swLog.WriteLine("\n--------- Logs -----------\n");
                swLog.WriteLine("Program Exitted successfully");
                swLog.Close();
                
            }
            catch (System.Exception ioException1)
            {


                swLog.Write("An Error Has Occured");
                //swLog.WriteLine(ioException1.ToString());
                swLog.Close();

            }
            return processedText;
        }
    }
}
