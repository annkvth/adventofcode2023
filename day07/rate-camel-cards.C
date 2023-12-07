#include <algorithm> // for sort
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// return a rating based on the type and the card values of each game hand
tuple<int, int, int, int, int, int, int> ratehands(string hand, int points, bool isPart2);



int main(){
  ifstream infile("input");
  //ifstream infile("example");
  bool isPart2=true;
  
  vector<string> hands;
  string line;
  // Get the input and evaluate line by line
  // the lines all start with the cards, then a space, than the points
  string hand;
  int points;
  vector<tuple<int, int, int, int, int, int, int>> handsvec;
  while (getline(infile, line)){    
    if (!line.empty()){
      istringstream ssline(line);
      ssline >> hand >> points;
      //   cout << hand << " gives points: " << points << endl;
      auto rated = ratehands(hand, points, isPart2);
      handsvec.push_back(rated);
    }
  }

  // now that all hands are rated and in a vector,
  // sort them (using tuple-inbuilt comperator logic)
  sort(handsvec.begin(),handsvec.end());

  // the worst one gets 1*it's points, the next one 2, and so on
  int multiply=1;
  long sum=0;
  // int cvalues[5];
  // int type;
  for (tuple<int, int, int, int, int, int, int> hand: handsvec){
    tie (std::ignore, std::ignore, std::ignore, std::ignore, std::ignore, std::ignore, points) = hand;
    //    tie (type, cvalues[0], cvalues[1], cvalues[2], cvalues[3], cvalues[4], points) = hand;
    // cout << type << " " << cvalues[0] << " " << cvalues[4]
    // 	 << " multiply " << multiply << " " << points << endl;
    sum+=multiply*points;
    multiply++;
  }
  cout << sum << endl;
  return 0;
}



// return a rating based on the type and the card values of each game hand
tuple<int, int, int, int, int, int, int> ratehands(string hand, int points, bool isPart2){

  //  cout << hand << " gives points: " << points << endl;   
  // convert cards to their values:
  //    A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, or 2
  std::map<char, int> cardvalues;
  int startvalue=14;
  cardvalues['A']=startvalue--; cardvalues['K']=startvalue--; cardvalues['Q']=startvalue--;
  if(!isPart2)  cardvalues['J']=startvalue--;
  cardvalues['T']=startvalue--; cardvalues['9']=startvalue--; cardvalues['8']=startvalue--;
  cardvalues['7']=startvalue--;  cardvalues['6']=startvalue--; cardvalues['5']=startvalue--;
  cardvalues['4']=startvalue--; cardvalues['3']=startvalue--; cardvalues['2']=startvalue--;
  // in part2 j's are jokers and are worth the least
  if (isPart2){cardvalues['J']=startvalue--;}
  //cout << "j cards are worth " << cardvalues['J'] << endl;
   
  int countcards[13]={0};
  int cvalues[5];
  int icard=0;
  for(auto card : hand) {
    int value=cardvalues[card];
    countcards[value-2]++;
    cvalues[icard]=value;
    icard++;
  }

  // find out the type of hand:
  // 7  Five of a kind
  // 6  Four of a kind
  // 5  Full house
  // 4  Three of a kind
  // 3  Two pair
  // 2  One pair
  // 1  High card
  int type=0;
  if (!isPart2){
    bool triple=false, pair=false;  
    for(auto count : countcards){
      if (count==5){ type=7; break; }
      else if (count==4){ type=6; break; }
      else if (count==3){ triple=true;}
      else if (count==2){
	if (pair==true){  // already found another pair
	  type=3; break; }
	pair=true;
      }      
    }
    if (type==0){
      if (pair==true && triple ==true){ type = 5; }
      else if (pair==true){type = 2;}
      else if (triple ==true){type = 4;}
      else {type = 1;}
    }
  }
  // in part2, the jokers are in the last element of countcards
  // read them seperately and apply as upgrade
  else{
    bool quad=false, triple=false, pair=false, pair2=false;
    for (int ic=1; ic<13; ic++){
      auto count=countcards[ic];
      if (count==5){ type=7; break; }
      else if (count==4){ quad=true; break; }
      else if (count==3){ triple=true;}
      else if (count==2){
	//	cout << hand << " " << ic << " " << count << endl;
	if (pair==true){  // already found another pair
	  pair2=true; }
	pair=true;
      }      
    }
    if (type==0){
      auto jokers = countcards[0];
      //      cout << "applying " << jokers << " jokers" << endl;
      // 4 or 5 jokers --> five of a kind
      if(jokers>=4){	type = 7; }
      else if(jokers==3){
	if(pair==true){ type=7; }
	else{ type = 6;};	
      }
      else if(jokers==2){
	if(triple==true){ type = 7;}
	else if(pair==true){ type=6; }
	else{ type =4;}
      }
      else if(jokers==1){
	if (quad==true){type = 7;} 
	else if (triple ==true){ type = 6; }
	else if (pair==true && pair2==true){type = 5;}
	else if (pair==true ){type = 4;}
	else {type = 2;}
      }
      else{
	if (quad==true){type = 6;}
	else if (pair==true && triple ==true){ type = 5; }
	else if (triple ==true){type = 4;}
	else if (pair==true && pair2==true){type = 3;}
	else if (pair==true ){type = 2;}
	else {type = 1;}
      }
    }
    //    cout << hand << " " << triple << " " << pair << " " << pair2 << " rating " << type << endl;

  }
  
  // type card card card card card points
  return make_tuple(type, cvalues[0], cvalues[1], cvalues[2], cvalues[3], cvalues[4], points);
}
