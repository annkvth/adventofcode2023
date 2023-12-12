#include <fstream>
#include <iostream>
#include <map>
#include <numeric> // for least common multiple
#include <regex>
#include <sstream>
#include <string>
#include <vector>


using namespace std;


long recurse_lcm(long anum, vector<long> avec);


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
  vector<string> allLoc;
  int endsInA = 0; // count how many end in A - that's how many steps we take at the same time
  int endsInZ = 0;
  while (getline(infile, line)){    
    if (!line.empty()){
      //example line: AAA = (BBB, CCC) -->AAA BBB CCC
      line=regex_replace(line, notalpha_re, " ");
      line=regex_replace(line, space_re, " ");
      istringstream ss(line);       string sLocation;
      getline(ss, sLocation);       istringstream partStream(sLocation);
      partStream >> currLoc >> dir_set.first >> dir_set.second;
      rl_map.insert(pair(currLoc, dir_set));
      if(currLoc.back()=='A'){
	endsInA++;
	allLoc.push_back(currLoc);
	cout << "A-end location " << currLoc << " " << rl_map[currLoc].first << " " << rl_map[currLoc].second << endl;     
      }
      else if(currLoc.back()=='Z'){
	endsInZ++;
	cout << "Z-end location " << currLoc << " " << rl_map[currLoc].first << " " << rl_map[currLoc].second << endl;     
      }
      //      cout << currLoc << " " << rl_map[currLoc].first << " " << rl_map[currLoc].second << endl;     
    }
  }
  cout << endsInA << " locations end in A" << endl;  
  cout << endsInZ << " locations end in Z" << endl;  

  long sum=0;
  // first solution didn't work, had to look up a spoiler-hint on reddit:
  // "Hint: Ghosts travel in cycles. "
  vector<long> nsteps;
  bool check = false;
  // for each start location, check how many steps the ghots needs to finish
  for (auto currLoc : allLoc){
    sum=0;
    check=false;
    while(!check){
      for (auto nextLR : vecLR){
	sum++;
	// jump all the steps until Z-ending
	dir_set = rl_map[currLoc];
	// new location based on left-right vector
	nextLR=='L' ? currLoc = dir_set.first : currLoc = dir_set.second;
	// no need to keep counting when one wasn't z   
	if(currLoc.back()=='Z'){
	  nsteps.push_back(sum);
	  std::cout << sum << std::endl;
	  check=true;
	  break;
	}
	// cout << nextLR << " of " << dir_set.first << "," << dir_set.second << " : "
	//      << currLoc << " - " << currLoc.back() << endl;
      }
    }
  }

  // seperate vector into last element and all the rest for function call
  long anum= nsteps.back();
  nsteps.pop_back();
  long sresult = recurse_lcm(anum, nsteps);
  std::cout << sresult << std::endl;
  
  return 0;
}



// avoid hard-coding vector legth - recurvice all off lcs
long recurse_lcm(long anum, vector<long> avec){

  long bnum = avec.back();
  auto asize = avec.size();
  avec.pop_back();
  if (asize > 1){
    bnum = recurse_lcm(bnum, avec);
  }
  
  return lcm(anum, bnum);  
  
}
