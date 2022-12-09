/*
 * Anthony Redamonti
 * Professor Gregory Wagner
 * CSE 681 Software Modeling
 * Project 3
 * 9/2/2022
 * 
 * The following file defines the behavior of the GUI in "MainWindow.xaml."
 * When the user presses the collect data button, the MainWindow class will
 * start a thread that will call the collect data method on its instance 
 * of the TestFunctionality class. After the thread returns, the MainWindow
 * class will start the display data thread, which will display the JSON 
 * object data to the GUI.
 * 
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.ComponentModel;
using System.Threading;

namespace Project3
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public TextBox[] teamTextBoxesArray = new TextBox[32];
        public string[] teamNamesArray = new string[32];
        TestFunctionality testFunctionalityObj = new TestFunctionality();
        private BackgroundWorker backgroundWorkerObj;

        /// <summary>
        /// Constructor for the MainWindow class. Populates the team name array with 
        /// the appropriate string and the textbox array with the appropriate team
        /// textbox.
        /// </summary>
        public MainWindow()
        {
            InitializeComponent();
            teamTextBoxesArray[0] = CardinalsTextBox; teamNamesArray[0] = "Cardinals";
            teamTextBoxesArray[1] = FalconsTextBox; teamNamesArray[1] = "Falcons";
            teamTextBoxesArray[2] = RavensTextBox; teamNamesArray[2] = "Ravens";
            teamTextBoxesArray[3] = BillsTextBox; teamNamesArray[3] = "Bills";
            teamTextBoxesArray[4] = PanthersTextBox; teamNamesArray[4] = "Panthers";
            teamTextBoxesArray[5] = BearsTextBox; teamNamesArray[5] = "Bears";
            teamTextBoxesArray[6] = BrownsTextBox; teamNamesArray[6] = "Browns";
            teamTextBoxesArray[7] = CowboysTextBox; teamNamesArray[7] = "Cowboys";
            teamTextBoxesArray[8] = BroncosTextBox; teamNamesArray[8] = "Broncos";
            teamTextBoxesArray[9] = LionsTextBox; teamNamesArray[9] = "Lions";
            teamTextBoxesArray[10] = PackersTextBox; teamNamesArray[10] = "Packers";
            teamTextBoxesArray[11] = GiantsTextBox; teamNamesArray[11] = "Giants";
            teamTextBoxesArray[12] = ColtsTextBox; teamNamesArray[12] = "Colts";
            teamTextBoxesArray[13] = JaguarsTextBox; teamNamesArray[13] = "Jaguars";
            teamTextBoxesArray[14] = ChiefsTextBox; teamNamesArray[14] = "Chiefs";
            teamTextBoxesArray[15] = DolphinsTextBox; teamNamesArray[15] = "Dolphins";
            teamTextBoxesArray[16] = VikingsTextBox; teamNamesArray[16] = "Vikings";
            teamTextBoxesArray[17] = PatriotsTextBox; teamNamesArray[17] = "Patriots";
            teamTextBoxesArray[18] = SaintsTextBox; teamNamesArray[18] = "Saints";
            teamTextBoxesArray[19] = JetsTextBox; teamNamesArray[19] = "Jets";
            teamTextBoxesArray[20] = RaidersTextBox; teamNamesArray[20] = "Raiders";
            teamTextBoxesArray[21] = EaglesTextBox; teamNamesArray[21] = "Eagles";
            teamTextBoxesArray[22] = SteelersTextBox; teamNamesArray[22] = "Steelers";
            teamTextBoxesArray[23] = ChargersTextBox; teamNamesArray[23] = "Chargers";
            teamTextBoxesArray[24] = SeahawksTextBox; teamNamesArray[24] = "Seahawks";
            teamTextBoxesArray[25] = FortyNinersTextBox; teamNamesArray[25] = "49ers";
            teamTextBoxesArray[26] = RamsTextBox; teamNamesArray[26] = "Rams";
            teamTextBoxesArray[27] = BuccaneersTextBox; teamNamesArray[27] = "Buccaneers";
            teamTextBoxesArray[28] = TitansTextBox; teamNamesArray[28] = "Titans";
            teamTextBoxesArray[29] = CommandersTextBox; teamNamesArray[29] = "Washington";
            teamTextBoxesArray[30] = BengalsTextBox; teamNamesArray[30] = "Bengals";
            teamTextBoxesArray[31] = TexansTextBox; teamNamesArray[31] = "Texans";

            backgroundWorkerObj = new BackgroundWorker();
            backgroundWorkerObj.DoWork += CollectData;
            backgroundWorkerObj.ProgressChanged += UpdateProgressBar;
            backgroundWorkerObj.RunWorkerCompleted += DataCollected;
            backgroundWorkerObj.WorkerReportsProgress = true;
        }

        /// <summary>
        /// Handles the event when the user presses the collect data button in the GUI.
        /// </summary>
        void CollectDataButton_Click(Object sender, EventArgs e)
        {
            try
            {
                MonitorButton.Background = Brushes.Red;
                MonitorButton.Foreground = Brushes.Red;
                ProgressLabel.Content = "0";
                PercentProgressBar.Value = 0;
                CollectDataButton.IsEnabled = false;
                clearTextBoxes();

                if (backgroundWorkerObj.IsBusy == false)
                {
                    backgroundWorkerObj.RunWorkerAsync();
                }

                CollectDataButton.IsEnabled = true;
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception thrown in CollectDataButton_Click: " + ex.Message);
                throw;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public void UpdateProgressBar(object sender, ProgressChangedEventArgs e)
        {
            try
            {
                double percentPerTeam = 1.0 / Convert.ToDouble(testFunctionalityObj.numberOfTeams);
                percentPerTeam = percentPerTeam * 100;
                double percentComplete = 0.0;
                double rounded = 0.0;

                percentComplete = e.ProgressPercentage * percentPerTeam;
                rounded = Math.Round(percentComplete);
                updateProgressBar(rounded);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception thrown in report work thread: " + ex.Message);
                throw;
            }
        }

        /// <summary>
        /// Method to update the progress bar with the passed double value.
        /// </summary>
        private void updateProgressBar(double value)
        {
            try
            {
                this.Dispatcher.BeginInvoke(new Action(() =>
                {
                    PercentProgressBar.Value = Convert.ToInt32(value);
                    ProgressLabel.Content = Convert.ToString(Convert.ToInt32(value));
                }));
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception thrown in monitor data thread: " + ex.Message);
                throw;
            }
        }

        /// <summary>
        /// The data has been collected. 
        /// </summary>
        private void DataCollected(object sender, RunWorkerCompletedEventArgs e)
        {
            try
            {
                // update the textbox for each team with its record.
                for (int i = 0; i < testFunctionalityObj.seasonInfoList.Count(); i++)
                {
                    updateTextBox(testFunctionalityObj.seasonInfoList[i]);
                }

                this.Dispatcher.BeginInvoke(new Action(() =>
                {
                    MonitorButton.Background = Brushes.Green;
                    MonitorButton.Foreground = Brushes.Green;
                }));
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception thrown in UpdateUI thread: " + ex.Message);
                throw;
            }
        }

        /// <summary>
        /// Collect the data from the server using a background worker.
        /// </summary>
        private void CollectData(object sender, DoWorkEventArgs e)
        {
            try
            {
                testFunctionalityObj.collectData(backgroundWorkerObj);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception thrown in collect data thread: " + ex.Message);
                throw;
            }
        }

        /// <summary>
        /// Method called by the main thread to clear the textboxes in the GUI
        /// </summary>
        private void clearTextBoxes()
        {
            try
            {
                // start the thread to collect the data from the online server.
                Thread clearTextBoxesThread;
                clearTextBoxesThread = new Thread(clearTextBoxesMethod);
                clearTextBoxesThread.IsBackground = true;
                clearTextBoxesThread.Name = "Clear Textboxes Thread";
                clearTextBoxesThread.Start();
                clearTextBoxesThread.Join();
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception thrown in clear textboxes method: " + ex.Message);
                throw;
            }
        }

        /// <summary>
        /// Method called by the clear textboxes thread.
        /// </summary>
        private void clearTextBoxesMethod()
        {
            try
            {
                this.Dispatcher.BeginInvoke(new Action(() =>
                {
                    for (int i = 0; i < teamTextBoxesArray.Length; i++)
                    {
                        teamTextBoxesArray[i].Text = " ";
                    }
                }));
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception thrown in clear textboxes thread: " + ex.Message);
                throw;
            }
        }

        /// <summary>
        /// Update the textbox of the team name passed to the field.
        /// </summary>
        private void updateTextBox(SeasonInfo inputSeasonInfoObj)
        {
            try
            {
                // if the team name matches an entry in the team name array, update the corresponding textbox in the GUI.
                for(int i = 0; i < teamNamesArray.Length; i++)
                {
                    if(teamNamesArray[i] == inputSeasonInfoObj.teamName)
                    {
                        // if accessing the textbox from a different thread than the main thread,
                        // the dispatcher must be invoked to grant access. Check if invoking is 
                        // necessary.
                        if (this.Dispatcher.CheckAccess())
                        {
                            teamTextBoxesArray[i].Text = Convert.ToString(inputSeasonInfoObj.wins) + "-" + Convert.ToString(inputSeasonInfoObj.losses) + "-" + Convert.ToString(inputSeasonInfoObj.ties);
                        }
                        else
                        {
                            this.Dispatcher.BeginInvoke(new Action(() =>
                            {
                                teamTextBoxesArray[i].Text = Convert.ToString(inputSeasonInfoObj.wins) + "-" + Convert.ToString(inputSeasonInfoObj.losses) + "-" + Convert.ToString(inputSeasonInfoObj.ties);
                            }));
                        }
                        return;
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception thrown in update textbox method: " + ex.Message);
                throw;
            }
        }
    }
}
