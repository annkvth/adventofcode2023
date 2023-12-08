#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <vector>


using namespace std;


int main(){

  std::ifstream infile("input");
  //ifstream infile("example6");
  std::string line;

  // the first line contains the RL instructions
  getline(infile, line);
  // fill into a vector, using 0 for L and 1 for R  
  vector<char> vecLR;
  for (char direction : line){
    vecLR.push_back(direction);
  }
 
  // store the number of card copies in a map
  // Get the rest of the input and evaluate line by line:
  // clean up string, fill map with location pairs
  map<string, pair<string,string>> rl_map;
  regex space_re(R"(\s+)");
  regex notalpha_re(R"([^A-Za-z\d])");
  pair<string,string> dir_set;
  string currLoc;
  while (getline(infile, line)){    
    if (!line.empty()){
      //example line: AAA = (BBB, CCC) -->AAA BBB CCC
      line=regex_replace(line, notalpha_re, " ");
      line=regex_replace(line, space_re, " ");
      istringstream ss(line);       string sLocation;
      getline(ss, sLocation);       istringstream partStream(sLocation);
      partStream >> currLoc >> dir_set.first >> dir_set.second;
      rl_map.insert(pair(currLoc, dir_set));
      //      cout << currLoc << " " << rl_map[currLoc].first << " " << rl_map[currLoc].second << endl;     
    }
  }
  

  int sum=0;
  currLoc = "AAA";
  // now starting at AAA, loop over direction vector
  // and check if this takes us to ZZZ  
  while(!(currLoc=="ZZZ")){
    for (auto nextLR : vecLR){
      dir_set = rl_map[currLoc];
      // new location based on left-right vector
      nextLR=='L' ? currLoc = dir_set.first : currLoc = dir_set.second;
      //      cout << nextLR << " of " << dir_set.first << "," << dir_set.second << " : " << currLoc << endl;
      sum++;
      if (currLoc=="ZZZ") break;
    }
  }
  
  std::cout << sum << std::endl;
  
  return 0;
}
