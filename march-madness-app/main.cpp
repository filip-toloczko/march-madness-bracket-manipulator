/*--------------------------------------------
Program 5: March Madness Frenzy
Course: CS 141, Spring 2022, Tuesday 9 am lab
System: Windows using CLion
Author: Filip Toloczko
 ---------------------------------------------*/

#include <iostream>
#include <iomanip>
#include <cctype>
#include <vector>
#include <string>
#include <cassert>
#include <fstream>
#include <algorithm>
using namespace std;

//Creation of Class that will store data members of basketball games
class MarchMadnessData{
//creating the private data members
private:
    string region;
    string team1;
    string team2;
    string winningTeam;
    int rank1;
    int score1;
    int rank2;
    int score2;
    int roundNumber;
    int gameNumber;
//getter and setter functions for data members
public:
    void setRegion(string region){
        this->region = region;
    }
    string getRegion(){
        return region;
    }
    void setTeam1(string team1){
        this->team1 = team1;
    }
    string getTeam1(){
        return team1;
    }
    void setTeam2(string team2){
        this->team2 = team2;
    }
    string getTeam2(){
        return team2;
    }
    void setWinningTeam(string winningTeam){
        this->winningTeam = winningTeam;
    }
    string getWinningTeam(){
        return winningTeam;
    }
    void setRank1(int rank1){
        this->rank1 = rank1;
    }
    int getRank1(){
        return rank1;
    }
    void setRank2(int rank2){
        this->rank2 = rank2;
    }
    int getRank2(){
        return rank2;
    }
    void setScore1(int score1){
        this->score1 = score1;
    }
    int getScore1(){
        return score1;
    }
    void setScore2(int score2){
        this->score2 = score2;
    }
    int getScore2(){
        return score2;
    }
    void setRoundNumber(int roundNumber){
        this->roundNumber = roundNumber;
    }
    int getRoundNumber(){
        return roundNumber;
    }
    void setGameNumber(int gameNumber){
        this->gameNumber = gameNumber;
    }
    int getGameNumber(){
        return gameNumber;
    }

};

//function to read in data from csv files into vector
void readInMarchMadnessData(string filename, vector<MarchMadnessData>& marchMadnessGames) {
  ifstream inStream;
  inStream.open(filename);
  assert(inStream.fail() == false);
  string gameLine;
  getline(inStream, gameLine);
  while (getline(inStream, gameLine )){
    stringstream s_stream(gameLine);
    MarchMadnessData oneGame;
    int columnNumber = 0;
    while (s_stream.good()) {
      string columnValue;
      getline(s_stream, columnValue, ',');
      switch(columnNumber){
        //set region value
        case 0:{
          oneGame.setRegion(columnValue);
          break;
        }
        //set rank of first team, convert to number
        case 1:
          oneGame.setRank1(stoi(columnValue));
          break;
        //set name of first team
        case 2:
          oneGame.setTeam1(columnValue);
          break;
        //set score of first team
        case 3:
          //check if the score value is empty. If so set score to 0
          if (columnValue==""){
            oneGame.setScore1(0);
          }
          //convert string to number  
          else {
            oneGame.setScore1(stoi(columnValue));
            break;
          }
          break;
        //set rank of second team, convert to number
        case 4:
          oneGame.setRank2(stoi(columnValue));
          break;
        //set name of second team
        case 5:
          oneGame.setTeam2(columnValue);
          break;
        //set score of second team
        case 6:                
          //check if the score value is empty. If so set score to 0
          if (columnValue == ""){
            oneGame.setScore2(0);
          }
          //convert string to number
          else {
            oneGame.setScore2(stoi(columnValue));
            break;
          }
        //set value for winning team
        case 7:
          oneGame.setWinningTeam(columnValue);
          break;
        //set value for round number
        case 8:
          oneGame.setRoundNumber(stoi(columnValue));
          break;
        //set value for game number
        case 9:
          oneGame.setGameNumber(stoi(columnValue));
          break;
      }
      //Iterate column number
      columnNumber++;
    }
    //append game to vector of games
    marchMadnessGames.push_back(oneGame);
  }
}

//function to display bracket information (menu option 1)
void displayBracketInformation(vector<MarchMadnessData>& marchMadnessGames){
  //variable declaration
  int setSpace;

  //display number of games played in tournament
  cout << "Total number of games played in tournament: " << marchMadnessGames.size()<< endl;
  cout << "The Final Four contestants are: " << endl;

  //for loop that iterates through vector of games
  for (int i =0; i<marchMadnessGames.size(); i++){
    //if statement checks if the games round number is 4
    if(marchMadnessGames.at(i).getRoundNumber() == 4){
      //display the teams participating in the final 4
      setSpace = (8 - (marchMadnessGames.at(i).getRegion()).size());
      cout <<"        "<< marchMadnessGames.at(i).getRegion() 
           <<" region:"<<setw(setSpace)<< "" << marchMadnessGames.at(i).getWinningTeam() << endl;
    }
    else{
      continue;
    }
  }
}

//function to display the winning team's path to victory (menu option 2)
void displayWinningTeamPath(vector<MarchMadnessData>& marchMadnessGames){
  //variable declaration
  string tournamentWinner;
  
  //for loop iterates through vector of games
  for (int i =0; i<marchMadnessGames.size(); i++){
    
    //if statement checks if the round is six
    if(marchMadnessGames.at(i).getRoundNumber() == 6){
      //set tournamentWinner to the winner of round 6
      tournamentWinner = marchMadnessGames.at(i).getWinningTeam();
    }
    else{
      continue;
    }
  }
  //reverse the vector in order to get the games in order played
  reverse(marchMadnessGames.begin(), marchMadnessGames.end());
  
  //for loop iterates throufh vector of games
  for (int i =0; i<marchMadnessGames.size(); i++){
    //if statement checks if a games winner is the tournament winner
    if(marchMadnessGames.at(i).getWinningTeam() == tournamentWinner){
      //display the information of the game
      cout << "Round " << marchMadnessGames.at(i).getRoundNumber() << ", "
           << "Game " << marchMadnessGames.at(i).getGameNumber() << ": "
           << marchMadnessGames.at(i).getTeam1() << " vs "
           << marchMadnessGames.at(i).getTeam2() << ". " 
           << "Winner: " << marchMadnessGames.at(i).getWinningTeam() << endl;
    }
  }
  
  //reverse the vector to its original order
  reverse(marchMadnessGames.begin(), marchMadnessGames.end());
}

//function to determine the region most likely to win (menu option 3)
void determineBestRegion(vector<MarchMadnessData> marchMadnessGames, int roundNumber){
  //varianle declararions
  int eastSpokane=0, westGreensboro=0, midwestBridgeport=0, southWichita=0;
  string bestRegion;
  vector<int> regions;
  
  //for loop iterates through the vector
  for (int i =0; i<marchMadnessGames.size(); i++){
    //if statement checks that the round number is equal to roundNumber
    if(marchMadnessGames.at(i).getRoundNumber() == roundNumber){
      //if statement checks if the winner of the game is team 1 
      if (marchMadnessGames.at(i).getWinningTeam() == marchMadnessGames.at(i).getTeam1()){
        //if statements check what region team 1 is from and adds rank 1 to the respective strings
        if((marchMadnessGames.at(i).getRegion() == "West") || (marchMadnessGames.at(i).getRegion() == "Greensboro")){
          westGreensboro +=marchMadnessGames.at(i).getRank1();
        }
        else if((marchMadnessGames.at(i).getRegion() == "South") || (marchMadnessGames.at(i).getRegion() == "Wichita")){
          southWichita +=marchMadnessGames.at(i).getRank1();
        }
        else if((marchMadnessGames.at(i).getRegion() == "East") || (marchMadnessGames.at(i).getRegion() == "Spokane")){
          eastSpokane += marchMadnessGames.at(i).getRank1();
        }
        else if((marchMadnessGames.at(i).getRegion() == "Midwest") || (marchMadnessGames.at(i).getRegion() == "Bridgeport")){
          midwestBridgeport +=marchMadnessGames.at(i).getRank1();
        }
      }

      //if statement checks if the winner of the game is team 2
      else if (marchMadnessGames.at(i).getWinningTeam() == marchMadnessGames.at(i).getTeam2()){
        //if statements check what region team 2 is from and adds rank 2 to the respective strings
        if((marchMadnessGames.at(i).getRegion() == "West") || (marchMadnessGames.at(i).getRegion() == "Greensboro")){
          westGreensboro +=marchMadnessGames.at(i).getRank2();
        }
        else if((marchMadnessGames.at(i).getRegion() == "South") || (marchMadnessGames.at(i).getRegion() == "Wichita")){
          southWichita +=marchMadnessGames.at(i).getRank2();
        }
        else if((marchMadnessGames.at(i).getRegion() == "East") || (marchMadnessGames.at(i).getRegion() == "Spokane")){
          eastSpokane += marchMadnessGames.at(i).getRank2();
        }
        else if((marchMadnessGames.at(i).getRegion() == "Midwest") || (marchMadnessGames.at(i).getRegion() == "Bridgeport")){
          midwestBridgeport +=marchMadnessGames.at(i).getRank2();
        }
        
      }
    }
  }
  //add the regions to the vector regions
  regions.push_back(eastSpokane);
  regions.push_back(westGreensboro);
  regions.push_back(midwestBridgeport);
  regions.push_back(southWichita);
  
  //sort the vector to get the regions in order
  sort(regions.begin(), regions.end());
  
  //if statements check what the first element of vector regions is and sets bestRegion to that element
  if((regions[0]==westGreensboro)&&(marchMadnessGames.at(32).getRegion()=="South")){
    bestRegion = "West";
  }
  else if((regions[0]==westGreensboro)&&(marchMadnessGames.at(32).getRegion()=="Wichita")){
    bestRegion = "Greensboro";
  }
  else if((regions[0]==southWichita)&&(marchMadnessGames.at(32).getRegion()=="South")){
    bestRegion = "South";
  }
  else if((regions[0]==southWichita)&&(marchMadnessGames.at(32).getRegion()=="Wichita")){
    bestRegion = "Wichita";
  }
  else if((regions[0]==eastSpokane)&&(marchMadnessGames.at(32).getRegion()=="South")){
    bestRegion = "East";
  }
  else if((regions[0]==eastSpokane)&&(marchMadnessGames.at(32).getRegion()=="Wichita")){
    bestRegion = "Spokane";
  }
  else if((regions[0]==midwestBridgeport)&&(marchMadnessGames.at(32).getRegion()=="South")){
    bestRegion = "Midwest";
  }
  else if((regions[0]==midwestBridgeport)&&(marchMadnessGames.at(32).getRegion()=="Wichita")){
    bestRegion = "Bridgeport";
  }
  
  //display the region with the lowest combined rank
  cout << "\nThe region expected to win is: " << bestRegion << endl;
  
  //clear the vector regions
  regions.clear();
}

//function to find the best underdog (menu option 4)
void getBestUnderdog(vector<MarchMadnessData>& marchMadnessGames, int roundNumber){
  //variable declarations
  int teamRank=0;
  string worstTeam;
  
  //for loop iterates through the vector 
  for (int i =0; i<marchMadnessGames.size(); i++){
    //if statement checks if the round number is equal to roundNumber
    if(marchMadnessGames.at(i).getRoundNumber() == roundNumber){
      //create variables to store ranks of both team for games
      int rank1 = marchMadnessGames.at(i).getRank1();
      int rank2 = marchMadnessGames.at(i).getRank2();
      
      //if statements check if the teams ranks are greater than teamRank
      if (rank1>teamRank){
        teamRank = rank1;
        worstTeam = marchMadnessGames.at(i).getTeam1();
      }
      if (rank2>teamRank){
        teamRank = rank2;
        worstTeam = marchMadnessGames.at(i).getTeam2();
      }
    }
  }
  //display the best underdog
  cout << "The best underdog team is " << worstTeam << " which has rank " << teamRank << "." << endl;
}

//function to get the closest game (menu option 5)
void getCloseGames(vector<MarchMadnessData>& marchMadnessGames, int roundNumber){
  //variable declarations
  int pointDifference=0;
  int round, game;
  string team1, team2, winningTeam;
  
  //for loop iterates through the vector
  for (int i =0; i<marchMadnessGames.size(); i++){
    //if statement checks if the round number isn't 7
    if (roundNumber != 7){
      //if statement checks if the round number is equal to roundNumber
      if(marchMadnessGames.at(i).getRoundNumber() == roundNumber){
        int score1 = marchMadnessGames.at(i).getScore1();
        int score2 = marchMadnessGames.at(i).getScore2();
        int difference = score1-score2;
        int absoluteDifference = abs(difference);
        
        //if statement checks if the current point difference is greater than the max difference
        if (absoluteDifference>pointDifference){
          pointDifference = absoluteDifference;
          round = marchMadnessGames.at(i).getRoundNumber();
          game = marchMadnessGames.at(i).getGameNumber();
          team1 = marchMadnessGames.at(i).getTeam1();
          team2 = marchMadnessGames.at(i).getTeam2();
          winningTeam = marchMadnessGames.at(i).getWinningTeam();
        }
      }
    }
    //if statement checks if roundNumber is 7
    else if (roundNumber == 7){
      int score1 = marchMadnessGames.at(i).getScore1();
      int score2 = marchMadnessGames.at(i).getScore2();
      int difference = score1-score2;
      int absoluteDifference = abs(difference);

      //if statement checks if the current point difference is greater than the max difference
      if (absoluteDifference>pointDifference){
        pointDifference = absoluteDifference;
        round = marchMadnessGames.at(i).getRoundNumber();
        game = marchMadnessGames.at(i).getGameNumber();
        team1 = marchMadnessGames.at(i).getTeam1();
        team2 = marchMadnessGames.at(i).getTeam2();
        winningTeam = marchMadnessGames.at(i).getWinningTeam();
      }
    }
  }
  //display the shoo-in game
  cout << "\nThe shoo-in game was: " << endl;
  cout << "Round " << round << ", Game " << game << ": " << team1 << " vs " << team2 
       << ". Winner: " << winningTeam << endl;
  cout << "The difference was " << pointDifference << " points." << endl;
}

//function to get the blowout game (menu option 5)
void getBlowout(vector<MarchMadnessData>& marchMadnessGames, int roundNumber){
  //variable declarations
  int pointDifference=100;
  int round, game;
  string team1, team2, winningTeam;

  //for loop iterates through vector
  for (int i =0; i<marchMadnessGames.size(); i++){
    //if statement checks if roundNumber isn't 7
    if (roundNumber != 7){
      //if statement checks that round number is equal to roundNumber
      if(marchMadnessGames.at(i).getRoundNumber() == roundNumber){
        int score1 = marchMadnessGames.at(i).getScore1();
        int score2 = marchMadnessGames.at(i).getScore2();
        int difference = score1-score2;
        int absoluteDifference = abs(difference);
        //if statement checks if the current point difference is greater than the max difference
        if (absoluteDifference<pointDifference){
          pointDifference = absoluteDifference;
          round = marchMadnessGames.at(i).getRoundNumber();
          game = marchMadnessGames.at(i).getGameNumber();
          team1 = marchMadnessGames.at(i).getTeam1();
          team2 = marchMadnessGames.at(i).getTeam2();
          winningTeam = marchMadnessGames.at(i).getWinningTeam();
        }
      }
    }
    //if statement checks if roundNumber is equal to 7
    else if (roundNumber == 7){
      int score1 = marchMadnessGames.at(i).getScore1();
      int score2 = marchMadnessGames.at(i).getScore2();
      int difference = score1-score2;
      int absoluteDifference = abs(difference);
      //if statement checks if the current point difference is greater than the max difference
      if (absoluteDifference<pointDifference){
          pointDifference = absoluteDifference;
          round = marchMadnessGames.at(i).getRoundNumber();
          game = marchMadnessGames.at(i).getGameNumber();
          team1 = marchMadnessGames.at(i).getTeam1();
          team2 = marchMadnessGames.at(i).getTeam2();
          winningTeam = marchMadnessGames.at(i).getWinningTeam();
        }
    }
  }

  //displays nail biter game
  cout << "\nThe nail-biting game was: " << endl;
  cout << "Round " << round << ", Game " << game << ": " << team1 << " vs " << team2 
       << ". Winner: " << winningTeam << endl;
  cout << "The difference was " << pointDifference << " points." << endl;
}

//function to compare brackets (menu option 6)
void compareBrackets(vector<MarchMadnessData>& marchMadnessGames, vector<MarchMadnessData>& marchMadnessPredictions){
  //variable declarations
  int points = 0;
  int gamesPredicted = 0;

  //for loop iterates through vector
  for (int i = 0; i < marchMadnessGames.size(); i++){
    //if statements check for round numbers
    if (marchMadnessGames.at(i).getRoundNumber() == 1){
      if (marchMadnessGames.at(i).getWinningTeam() == marchMadnessPredictions.at(i).getWinningTeam()){
        points += 5;
        gamesPredicted += 1;
      }
    }
    if (marchMadnessGames.at(i).getRoundNumber() == 2){
      if (marchMadnessGames.at(i).getWinningTeam() == marchMadnessPredictions.at(i).getWinningTeam()){
        points += 10;
        gamesPredicted += 1;
      }
    }
    if (marchMadnessGames.at(i).getRoundNumber() == 3){
      if (marchMadnessGames.at(i).getWinningTeam() == marchMadnessPredictions.at(i).getWinningTeam()){
        points += 15;
        gamesPredicted += 1;
      }
    }
    if (marchMadnessGames.at(i).getRoundNumber() == 4){
      if (marchMadnessGames.at(i).getWinningTeam() == marchMadnessPredictions.at(i).getWinningTeam()){
        points += 20;
        gamesPredicted += 1;
      }
    }
    if (marchMadnessGames.at(i).getRoundNumber() == 5){
      if (marchMadnessGames.at(i).getWinningTeam() == marchMadnessPredictions.at(i).getWinningTeam()){
        points += 25;
        gamesPredicted += 1;
      }
    }
    if (marchMadnessGames.at(i).getRoundNumber() == 6){
      if (marchMadnessGames.at(i).getWinningTeam() == marchMadnessPredictions.at(i).getWinningTeam()){
        points += 30;
        gamesPredicted += 1;
      }
    }
  }

  //display brakcet comparison 
  cout << "You correctly predicted the winner for " << gamesPredicted << " games. " << endl;
  cout << "This means that you have a score of " << points << "." << endl;
  if (points >= 250){
    cout << "Great job! You could consider entering your predictions to win money!" << endl;
  }
  else{
    cout << "You may want to learn more about basketball to improve your predictions next year." << endl;
  }
}

//function to display welcome message
void displayWelcomeMessage(){
  cout<< "Program 5: March Madness Frenzy" << endl;
  cout<< "CS 141, Spring 2022, UIC\n" << endl;
  cout << "This program reads in data from NCAA Basketball Tournaments"
       <<"(aka March Madness). It provides overall information regarding" 
       <<"the data, allows you to see the path taken to the championship,"
       <<"uses rankings of teams to determine which region is expected to win"
       <<"at a given round and to find the best underdog team, and calculates"
       <<"point differences within the games. You can also compare the actual"
       <<"brackets to your own predictions!" << endl
       <<"\nEnter the name of the file with the data for the NCAA tournament: "<<endl;
}

//function to display menu options
void displayMenu(){
  cout<<"\nSelect a menu option: "<<endl;
  cout<<"   1. Display overall information about the data"<<endl;
  cout<<"   2. Display the path of the winning team to the championship"<<endl;
  cout<<"   3. Determine which region is expected to win the championship based on a given round"<<endl;
  cout<<"   4. Identify the best underdog within a given round"<<endl;
  cout<<"   5. Find the shoo-in and nail-biting games within a given round, or overall"<<endl;
  cout<<"   6. Compare the actual brackets to your predicted brackets"<<endl;
  cout<<"   7. Exit"<<endl;
  cout<<"Your choice --> ";
}

//alternative menu options
void displayRoundOptions(){
  cout << "Enter a round to be evaluated: " << endl;
  cout << "   Select 2 for round 2" << endl;
  cout << "   Select 3 for round 3 'Sweet 16'" << endl;
  cout << "   Select 4 for round 4 'Elite 8'" << endl;
  cout << "   Select 5 for round 5 'Final 4'" << endl;
  cout << "Your choice --> ";
}

//alternative menu options
void displayRoundOptions2(){
  cout << "   Select 2 for round 2" << endl;
  cout << "   Select 3 for round 3 'Sweet 16'" << endl;
  cout << "   Select 4 for round 4 'Elite 8'" << endl;
  cout << "   Select 5 for round 5 'Final 4'" << endl;
  cout << "   Select 6 for round 6 'Championship'" << endl;
  cout << "Your choice --> ";
}

//alternative menu options
void displayRoundOptions3(){
  cout << "   Select 1 for round 1" << endl;
  cout << "   Select 2 for round 2" << endl;
  cout << "   Select 3 for round 3 'Sweet 16'" << endl;
  cout << "   Select 4 for round 4 'Elite 8'" << endl;
  cout << "   Select 5 for round 5 'Final 4'" << endl;
  cout << "   Select 6 for round 6 'Championship'" << endl;
  cout << "   Select 7 for the overall tournament" << endl;
  cout << "Your choice --> ";
}

//main function
int main(){
  //variable declatations
  string fileName,predictionFilename;
  cin >> fileName;
  vector<MarchMadnessData> marchMadnessGames;
  vector<MarchMadnessData> marchMadnessPredictions;
  int roundNumber;
  int menuOption;

  //read in data from chosen csv file
  readInMarchMadnessData(fileName, marchMadnessGames);
  //display welcome message
  displayWelcomeMessage();
  
  //while loop that runs to program
  while(true){
    displayMenu();
    cin >> menuOption;
    
    //menu option 1
    if(menuOption == 1){
      displayBracketInformation(marchMadnessGames);
    }
    //menu option 2  
    else if(menuOption == 2){
      cout << "Path to the championship: " << endl;
      displayWinningTeamPath(marchMadnessGames);
    }
    //menu option 3  
    else if(menuOption == 3){
      displayRoundOptions();
      cin >> roundNumber;
      cout << "Analyzing round " << roundNumber << "..." << endl;
      //if statement checks if roundNumber == 5
      if (roundNumber != 5){
        determineBestRegion(marchMadnessGames, roundNumber);
      }
      else if ( roundNumber == 5){
        roundNumber = 4;
        determineBestRegion(marchMadnessGames, roundNumber);
      }
    }
    //menu option 4  
    else if (menuOption == 4){
      cout << "Enter a round to be evaluated: " << endl;
      displayRoundOptions2();
      cin >> roundNumber;
      getBestUnderdog(marchMadnessGames,roundNumber);
    }
    //menu option 5  
    else if (menuOption == 5){
      cout << "Enter a round to be evaluated: " << endl;
      displayRoundOptions3();
      cin >> roundNumber;
      //if statement checks if roundNumber == 7
      if (roundNumber != 7){
        cout << "Analyzing round " << roundNumber << "..." << endl;
      }
      else if (roundNumber == 7){
        cout << "Analyzing the overall tournament..." << endl;
      }
      getCloseGames(marchMadnessGames, roundNumber);
      getBlowout(marchMadnessGames, roundNumber);
    }
    //menu option 6  
    else if (menuOption == 6){
      cout << "Enter the name of the file with your predicted brackets: " << endl;
      cin >> predictionFilename;
      readInMarchMadnessData(predictionFilename, marchMadnessPredictions);
      compareBrackets(marchMadnessGames, marchMadnessPredictions);
      marchMadnessPredictions.clear();
    }
    //menu option 7
    else if(menuOption == 7){
      cout << "Exiting program...";
      break;
    }
    //invalid menu option
    else{
      cout << "Invalid value.  Please re-enter a value from the menu options below." << endl;
    }
  }
}
