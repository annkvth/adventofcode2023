#include <algorithm> // for std::find
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>


// return number of wins of each game card
int parsecards(std::string card);



int main(){
  std::ifstream infile("input");
  //std::ifstream infile("example");
  std::vector<std::string> cards;
  std::string line;
  // store the number of card copies in a map
  std::map<int, int> card_map;

  // Get the input and evaluate line by line:
  // fill cards vector and initialise map with one copy per card
  int icard=0;
  while (std::getline(infile, line)){
    if (!line.empty()){
      icard++;
      cards.push_back(line);
      card_map.insert(std::pair<int, int>(icard, 1) );
    }
  }

  int ncards=cards.size(); // the amount of cards I start with
  int sum=0;
  // iterate over cards and multiply the nwins following cards
  for (int jcard=0; jcard<ncards; jcard++){
    line = cards.at(jcard);
    // get number of copies from the map and update sum
    int ncopies=card_map[jcard+1]; // +1 since that's how the elves count
    sum+=ncopies;
    // find number of wins of this card
    int nwins=parsecards(line);
    // increment the n following cards once for each card copy
    for (int iwins=1; iwins<=nwins; iwins++){
      card_map[jcard+1+iwins]+=ncopies;
    }
  }
  
  std::cout << sum << std::endl;
  return 0;
}


// return cardID if valid combination, 0 otherwise
int parsecards(std::string card){

  // solve a few formatting issues due to spaces
  std::size_t index = card.find("  ");
  while (index != std::string::npos){
    card.replace(index, 2, " "); // single spaces only
    index = card.find("  ");
  }
  card.replace(card.find(": "), 2, ":");
  card.replace(card.find(" | "), 3, "|");
  //std::cout << card << std::endl;

  
  // the lines all start with "Card", then ID, then ":"
  size_t thecolon=card.find(':');
  //  cardID = stoi(card.substr(5, thecolon-5));
  // std::cout << cardID << std::endl;
  
  // everything after the colon are the two lists of numbers, separated by |
  std::string numberlist = card.substr(thecolon+1);
  // stringstream to parse this numberlist with getline
  std::istringstream ss(numberlist);
  std::string sPart, sSubpart;
  //  std::cout<<numberlist << std::endl;
  
  // read until the | to get the winning numbers
  std::getline(ss, sPart, '|');
  std::vector<int>winning ={};
  std::istringstream sss(sPart);
  // numbers are separated by spaces
  int anumber;
  //std::cout << sPart << std::endl;
  while (std::getline(sss, sSubpart, ' ')) {
    std::istringstream partStream(sSubpart);
    partStream >> anumber;
    //std::cout << "winning number " << anumber << std::endl;
    winning.push_back(anumber);
  }
  // now the rest of the line are the elf's numbers
  std::getline(ss, sPart);
  std::vector<int>elfnumbers={};
  std::istringstream ssself(sPart);
  // numbers are separated by spaces
  while (std::getline(ssself, sSubpart, ' ')) {
    std::istringstream partStream(sSubpart);
    partStream >> anumber;
    //std::cout << "the elf has number " << anumber << std::endl;
    elfnumbers.push_back(anumber);
  }

  int returnvalue=0;
  // for each number in elfnumbers, check if it is contained in the winning numbers
  for (int elfnum : elfnumbers){
    if(std::find(winning.begin(), winning.end(), elfnum) != winning.end()) {
      // if winning contains elfnum, count number of wins
      returnvalue++;
    }
  }
  //std::cout << returnvalue << std::endl;
  
  return returnvalue;
}
