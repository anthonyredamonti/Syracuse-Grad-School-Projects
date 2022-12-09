/*
 * Anthony Redamonti
 * Professor Gregory Wagner
 * CSE 681 Software Modeling
 * Project 4
 * 9/9/2022
 * 
 * NflData.cs
 * 
 * The following program sends a series of REST get requests to
 * an online server. The https address of the server is below.
 * https://sports.snoozle.net/search/nfl/searchHandler?fileType=inline&statType=teamStats&season=2020&teamName=1
 * 
 * The request returns a string of JSON data. The data is converted
 * to a JSON object. The data being queried from the address 
 * represents an NFL team's performance during the year 2020. Alter 
 * the last number in the address to query a different NFL team 
 * (numbered 1-32).
 * 
 * The NFL team's records are calculated using the private method
 * "calculateRecord" in the SeasonInfo class. 
 * 
 */

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using System.Text.Json;

namespace Project4
{

    /// <summary>
    /// Below is the public TestFunctionality class. It will create a list of strings
    /// to store the altered https addresses for all 32 NFL teams. It will then
    /// create a Utility object and use it to load the list with the altered addresses.
    /// Each address is queried and JSON data is deserialized into a JSON object.
    /// Each team name, code, and record are displayed to the console. 
    /// </summary>
    public class TestFunctionality
    {
        public Queue<SeasonInfo> seasonInfoQueue = new Queue<SeasonInfo>();

        public int numberOfTeams = 32;

        // the main method will accept the JSON file from the user.
        public void collectData(BackgroundWorker backgrndWrkrObj)
        {
            // clear the list of season info objects.
            if (seasonInfoQueue.Count > 0) { seasonInfoQueue.Clear(); }

            List<string> urlList = new List<string>();
            string url = "https://sports.snoozle.net/search/nfl/searchHandler?fileType=inline&statType=teamStats&season=2020&teamName=1";

            Utility utilityObj = new Utility();
            utilityObj.loadUrlList(ref urlList, url, numberOfTeams);

            // for each of the teams in the list, perform the following operation
            for (int i = 0; i < urlList.Count; i++)
            {
                var webClient = new WebClient();
                var jsonString = webClient.DownloadString(@urlList[i]);

                int error = 1;
                SeasonInfo seasonInfoObj = new SeasonInfo();
                try
                {
                    utilityObj.createSeasonInfoObj(jsonString, ref seasonInfoObj);
                    seasonInfoObj.initialize();
                    seasonInfoQueue.Enqueue(seasonInfoObj);
                    backgrndWrkrObj.ReportProgress(seasonInfoQueue.Count);
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Exception thrown in TestFunctionality::Main method: " + ex.Message);
                    throw;
                }
            }
        }
    }

    /// <summary>
    /// The Utility class's public method "loadUrlList" is used to load altered https 
    /// addresses into the passed list of strings. The public method "createSeasonInfoObj" 
    /// uses the JsonConvert method to deserialize the input Json string into a Json 
    /// object of type SeasonInfo class.
    /// </summary>
    public class Utility
    {
        /// <summary>
        /// Below is the public createSeasonInfoObj method.
        /// The input JSON string will be deserialized and stored inside a SeasonInfo object.
        /// </summary>        
        public void createSeasonInfoObj(string inputJsonString, ref SeasonInfo seasonInfoObj)
        {
            try
            {
                // create a glossary object by deserializing the JSON string using the SeasonInfo Object class structure.
                seasonInfoObj = JsonConvert.DeserializeObject<SeasonInfo>(inputJsonString);
            }
            // catch any exception here.
            catch (Exception ex)
            {
                Console.WriteLine("Exception thrown in Utility::createSeasonInfoObj method: " + ex.Message);
                throw;
            }
        }

        // load the list with the altered URL. Perform the operation for each team.
        public void loadUrlList(ref List<string> urlList, string url, int numberOfTeams)
        {
            try
            {
                urlList.Add(url);

                int urlLength = url.Length;

                // add the rest of the teams to the list.
                for (int i = 2; i < numberOfTeams + 1; i++)
                {
                    // edit the last digit in the URL.
                    string newUrl = url.Substring(0, urlLength - 1) + i;

                    urlList.Add(newUrl);
                }
            }
            // catch any exception here.
            catch (Exception ex)
            {
                Console.WriteLine("Exception thrown in TestFunctionality::loadUrlList method: " + ex.Message);
                throw;
            }
        }
    }

    /// <summary>
    /// Below is the public SeasonInfo class.
    /// Use the JsonConvert.DeserializeObject<List<GameInfo>>(JsonString) method 
    /// to populate the properties of an instance of this class. Then use 
    /// the displayContent method to view the class's content on the console.
    /// </summary>
    public class SeasonInfo
    {
        // List that stores the game information for the season.
        [JsonProperty("matchUpStats")]
        public IList<GameInfo> gameInfoList { get; set; }

        // have the contents been calculated already?
        private bool initialized = false;

        // the team code for this season info object
        public int teamCode;

        // the team code for this season info object
        public string teamName;

        // the record of the team in question.
        public int wins;
        public int losses;
        public int ties;

        // calculate the team code based on the first 3 games.
        private void calculateTeamCode()
        {
            try
            {
                // record the team codes for the first game of the season.
                int id1 = Convert.ToInt16(gameInfoList[0].homeTeamStatsObj.teamCode);
                int id2 = Convert.ToInt16(gameInfoList[0].visTeamStatsObj.teamCode);

                // give each of them a count of 1.
                int id1Count = 1;
                int id2Count = 1;

                int gamesToSearch = 3;

                for (int i = 1; i < gamesToSearch; i++)
                {
                    if (gameInfoList[i].playedInTheGame(id1))
                    {
                        id1Count = id1Count + 1;
                    }
                    else if (gameInfoList[i].playedInTheGame(id2))
                    {
                        id2Count = id2Count + 1;
                    }
                    else
                    {
                        // nothing to do at this time.
                    }
                }

                // update the team code with the team that played in all the games searched.
                if (id1Count == gamesToSearch)
                {
                    teamCode = id1;
                }
                else if (id2Count == gamesToSearch)
                {
                    teamCode = id2;
                }
                else
                {
                    // nothing to do at this time.
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception thrown in Utility::calculateTeamCode method: " + ex.Message);
                throw;
            }
        }

        // calculate the team name based on the team code.
        // Call calculateTeamCode before using this method.
        private void calculateTeamName()
        {
            // use the first game for the comparison.
            teamName = gameInfoList[0].getTeamName(teamCode);
        }

        // calcuate the recond of the team in question.
        private void calculateRecord()
        {
            try
            {
                for (int i = 0; i < gameInfoList.Count; i++)
                {
                    if (gameInfoList[i].didTeamWin(teamCode) == 1)
                    {
                        wins = wins + 1;
                    }
                    else if (gameInfoList[i].didTeamWin(teamCode) == 0)
                    {
                        losses = losses + 1;
                    }
                    else if (gameInfoList[i].didTeamWin(teamCode) == 2)
                    {
                        ties = ties + 1;
                    }
                    else
                    {
                        // There was an error. Nothing to do at this time.
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception thrown in SeasonInfo::calculateRecord method: " + ex.Message);
                throw;
            }
        }

        // display the content of all the games to the user.
        public void initialize()
        {
            if (!initialized)
            {
                calculateTeamCode();
                calculateTeamName();
                calculateRecord();
                initialized = true;
            }

            //Console.WriteLine("Team Name: " + teamName);
            //Console.WriteLine("Team Code: " + teamCode);
            //Console.WriteLine("Record: " + wins + "-" + losses + "-" + ties);
        }
    }

    /// <summary>
    /// Below is the public GameInfo class.
    /// Use the JsonConvert.DeserializeObject<GameInfo>(JsonString) method 
    /// to populate the properties of an instance of this class. Then use 
    /// the displayContent method to view the class's content on the console.
    /// </summary>
    public class GameInfo
    {
        [JsonProperty("visTeamName")]
        public string? visitingTeamName { get; set; }

        [JsonProperty("visStats")]
        public VisTeamStats visTeamStatsObj { get; set; }

        [JsonProperty("homeTeamName")]
        public string? homeTeamName { get; set; }

        [JsonProperty("homeStats")]
        public HomeTeamStats homeTeamStatsObj { get; set; }

        // display the content of the GameInfo object to the user.
        public void displayContent()
        {
            Console.WriteLine("Visiting Team Name: " + visitingTeamName);
            visTeamStatsObj.displayContent();
            Console.WriteLine("Home Team Name: " + homeTeamName);
            homeTeamStatsObj.displayContent();
        }

        // get the team name that matches the team code.
        public string getTeamName(int teamCode)
        {
            try
            {
                if (Convert.ToInt16(homeTeamStatsObj.teamCode) == teamCode)
                {
                    return homeTeamName;
                }
                else if (Convert.ToInt16(visTeamStatsObj.teamCode) == teamCode)
                {
                    return visitingTeamName;
                }
                else
                {
                    // nothing to do at this time.
                    return null;
                }
            }
            // catch any exception here.
            catch (Exception ex)
            {
                Console.WriteLine("Exception thrown in GameInfo::getTeamName method: " + ex.Message);
                throw;
            }
        }

        // did the team matching the team code argument win?
        // return 0 for a loss.
        // return 1 for a win.
        // return 2 for a tie.
        // return -1 if an error occurred.
        public int didTeamWin(int teamCode)
        {
            try
            {
                bool isHomeTeam = false;
                bool isVisitingTeam = false;
                bool homeTeamWon = false;
                bool visitingTeamWon = false;
                bool theGameWasTied = false;

                // find the team code for the season. (Whose team code played in the first 3 games?)
                if (matchTeamCode(ref isHomeTeam, ref isVisitingTeam, teamCode) == -1) { return -1; }

                // calculate the winner of the game. 
                if (findWinner(ref homeTeamWon, ref visitingTeamWon, ref theGameWasTied) == -2) { return -2; }

                // if the game was tied, return 2.
                if (theGameWasTied) { return 2; }

                // return the answer from the winOrLoss method.
                return (winOrLoss(ref isHomeTeam, ref isVisitingTeam, ref homeTeamWon, ref visitingTeamWon));
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception thrown in GameInfo::didTeamWin method: " + ex.Message);
                throw;
            }
        }

        /// <summary>
        /// Did the team (matching team code) win or lose?
        /// </summary>
        /// <param name="isHomeTeam"></param>
        /// <param name="isVisitingTeam"></param>
        /// <param name="homeTeamWon"></param>
        /// <param name="visitingTeamWon"></param>
        /// <returns>1 for win. 0 for loss. -3 for error.</returns>
        private int winOrLoss(ref bool isHomeTeam, ref bool isVisitingTeam, ref bool homeTeamWon, ref bool visitingTeamWon)
        {
            try
            {
                // if the team code entered matches the home team and the home team won, 
                // or if the team code entered matches the away team and the away team won,
                // return 1, signifying a win for the team code entered.
                if ((isHomeTeam && homeTeamWon) || (isVisitingTeam && visitingTeamWon))
                {
                    return 1;
                }
                // the team code entered lost the game.
                else if ((isHomeTeam && !homeTeamWon) || (isVisitingTeam && !visitingTeamWon))
                {
                    return 0;
                }
                // an error occurred in the calculation.
                else
                {
                    return -3;
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception thrown in GameInfo::winOrLoss method: " + ex.Message);
                throw;
            }
        }

        /// <summary>
        /// A private method matching the team code with either the home or visiting team.
        /// </summary>
        /// <param name="isHomeTeam"></param>
        /// <param name="isVisitingTeam"></param>
        /// <param name="teamCode"></param>
        /// <returns>0 for success. -1 for failure.</returns>
        private int matchTeamCode(ref bool isHomeTeam, ref bool isVisitingTeam, int teamCode)
        {
            try
            {
                if (Convert.ToInt16(homeTeamStatsObj.teamCode) == teamCode)
                {
                    isHomeTeam = true;
                }
                else if (Convert.ToInt16(visTeamStatsObj.teamCode) == teamCode)
                {
                    isVisitingTeam = true;
                }
                // the team code entered was not found to be playing in this game.
                else
                {
                    return -1;
                }
                return 0;
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception thrown in GameInfo::FindHomeTeam method: " + ex.Message);
                throw;
            }
        }

        /// <summary>
        /// Private method calculating the winning team.
        /// </summary>
        /// <param name="homeTeamWon"></param>
        /// <param name="visitingTeamWon"></param>
        /// <param name="theGameWasTied"></param>
        /// <returns>0 on success. -2 on error.</returns>
        private int findWinner(ref bool homeTeamWon, ref bool visitingTeamWon, ref bool theGameWasTied)
        {
            try
            {
                // calculate the winner if there was one.
                if (Convert.ToInt16(homeTeamStatsObj.score) > Convert.ToInt16(visTeamStatsObj.score))
                {
                    homeTeamWon = true;
                }
                else if (Convert.ToInt16(homeTeamStatsObj.score) < Convert.ToInt16(visTeamStatsObj.score))
                {
                    visitingTeamWon = true;
                }
                else if (Convert.ToInt16(homeTeamStatsObj.score) == Convert.ToInt16(visTeamStatsObj.score))
                {
                    theGameWasTied = true;
                }
                else
                {
                    return -2;
                }
                return 0;
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception thrown in GameInfo::findWinner method: " + ex.Message);
                throw;
            }
        }

        /// <summary>
        /// A method used to indicate whether the team code entered playing in the game.
        /// </summary>
        /// <param name="teamCode"></param>
        /// <returns></returns>
        public bool playedInTheGame(int teamCode)
        {
            try
            {
                if ((Convert.ToInt16(homeTeamStatsObj.teamCode) == teamCode) || (Convert.ToInt16(visTeamStatsObj.teamCode) == teamCode))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception thrown in GameInfo::playedInTheGame method: " + ex.Message);
                throw;
            }
        }
    }

    /// <summary>
    /// Below is the public VisTeamStats class.
    /// It holds important JsonProperties for the visiting team in the instance of the GameInfo class.
    /// </summary>
    public class VisTeamStats
    {
        [JsonProperty("teamCode")]
        public string? teamCode { get; set; }

        [JsonProperty("score")]
        public string? score { get; set; }

        // display the content of the VisTeamStats object to the user.
        public void displayContent()
        {
            Console.WriteLine("team code: " + teamCode);
            Console.WriteLine("score: " + score);
        }
    }

    /// <summary>
    /// Below is the public HomeTeamStats class.
    /// It holds important JsonProperties for the home team in the instance of the GameInfo class.
    /// </summary>
    public class HomeTeamStats
    {
        [JsonProperty("teamCode")]
        public string? teamCode { get; set; }

        [JsonProperty("score")]
        public string? score { get; set; }

        // display the content of the HomeTeamStats object to the user.
        public void displayContent()
        {
            Console.WriteLine("team code: " + teamCode);
            Console.WriteLine("score: " + score);
        }
    }

}
