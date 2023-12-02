#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


// return gameID if valid combination, 0 otherwise
int parsecolors(std::string game);



int main(){
  std::ifstream infile("input");
  //std::ifstream infile("example");
  std::vector<std::string> games;

  std::string line;

  // Get the input and evaluate line by line
  int sum=0;
  while (std::getline(infile, line)){
    if (!line.empty()){
      sum+=parsecolors(line);
    }
  }

  std::cout << sum << std::endl;
  return 0;
}


// return gameID if valid combination, 0 otherwise
int parsecolors(std::string game){
  // valid game conditions: no more than
  // 12 red cubes, 13 green cubes, and 14 blue cubes
  const int maxRed=12, maxGreen=13, maxBlue=14;

  int gameID;  
  // the lines all start with "game", then ID, then ":"
  size_t thecolon=game.find(':');
  gameID = stoi(game.substr(5, thecolon-5));
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
	std::cout << value << " " << color << std::endl;
	if (color == "red" && value > nRed) {
	  nRed = value;
	} else if (color == "green" && value > nGreen) {
	  nGreen = value;
	} else if (color == "blue" && value > nBlue) {
	  nBlue = value;
	}
      }
    }
    //    std::cout << "--- " << nBlue << " " << nRed << " " << nGreen << std::endl;

  }

  //  std::cout << game << " " << nBlue << " " << nRed << " " << nGreen << std::endl;
  // now compare the maxima with he game condisitons
  int returnvalue;
  if ( (nBlue <= maxBlue) &&  (nRed <= maxRed) &&  (nGreen <= maxGreen)){
    returnvalue=gameID;
  }
  else{
    returnvalue=0;
  }

  // std::cout << returnvalue << std::endl;
  return returnvalue;
}
