#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


// return power of the game (=maxRed*maxGreen*maxBlue)
int parsecolors(std::string game);



int main(){
  std::ifstream infile("input");
  //std::ifstream infile("example");
  std::vector<std::string> games;

  std::string line;

  // Get the input and evaluate line by line
  long sum=0;
  while (std::getline(infile, line)){
    if (!line.empty()){
      sum+=parsecolors(line);
    }
  }

  std::cout << sum << std::endl;
  return 0;
}


// return power of the game
int parsecolors(std::string game){

  // the lines all start with "game", then ID, then ":"
  size_t thecolon=game.find(':');
  // int gameID;  
  // gameID = stoi(game.substr(5, thecolon-5));
  // std::cout << gameID << std::endl;
  
  // everything after the colon is color lists, separated by ;
  std::string colorlist = game.substr(thecolon+1);
  // stringstream to parse this colorlist with getline
  std::istringstream ss(colorlist);
  std::string sPart, sSubpart;
  
  // Variables to store the maximum values for each color
  int nRed = 0, nGreen = 0, nBlue = 0;
  bool possiblegame;
  
  while (std::getline(ss, sPart, ';')) {
    std::string color;
    int value;
    std::istringstream sss(sPart);

    // the color-value pairs are separated by ,
    // --> read in, match color, compare with max
    while (std::getline(sss, sSubpart, ',')) {
      std::istringstream partStream(sSubpart);
      while (partStream >> value >> color) {
	//std::cout << value << " " << color << std::endl;
	if (color == "red" && value > nRed) {
	  nRed = value;
	} else if (color == "green" && value > nGreen) {
	  nGreen = value;
	} else if (color == "blue" && value > nBlue) {
	  nBlue = value;
	}
      }
    }
  }

  //  std::cout << game << " " << nBlue << " " << nRed << " " << nGreen << std::endl;
  // take the maximum of each color, and multiply
  return nBlue*nRed*nGreen;
}
