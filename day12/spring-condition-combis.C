#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// this looks at a line and returns number of valid combinations
int parserecord(std::string recordline);

// check if the observed spring pattern matches the one from the record
bool matchespattern(vector<int> target, vector<int> observed);

// SPROING! aka the recursive matching
int checkpattern(std::string pattern, vector<int> targetvec);

// group springs in a record line
vector<int> countspring(std::string record);


int main(){
  std::ifstream infile("input");
  //std::ifstream infile("example");
  std::string line;
  // Get the input and evaluate line by line
  int sum=0;
  while (std::getline(infile, line)){
    if (!line.empty()){
      sum+=parserecord(line);
    }
    //    std::cout << "--- " << nBlue << " " << nRed << " " << nGreen << std::endl;

  }

  std::cout << "Sum " << sum << std::endl;
  return 0;
}



int parserecord(std::string recordline){

  // the recordlines all start with the "record", then space, then numbers
  size_t thespace=recordline.find(' ');
  string records = recordline.substr(0, thespace);
  
  // everything after the space is numbers lists, separated by ,
  std::string numlist = recordline.substr(thespace+1);
  // stringstream to parse this list with getrecordline
  std::istringstream ss(numlist);      
  std::string sPart, sSubpart;
  
  vector<int> springvec;
  while (std::getline(ss, sPart, ',')) {
    int svalue;
    std::istringstream sss(sPart);
    sss >> svalue;
    springvec.push_back(svalue);
    //	std::cout << svalue << " " << std::endl;	
  }
  //  std::cout << springvec.size() << " " << std::endl;	

  
  int ncombis = checkpattern(records, springvec);
  return ncombis;
}


// recursive replacing to find all possible patterns
int checkpattern(std::string pattern, vector<int> targetvec){
  // keep replacing question marks with possible combis
  int sum=0;
  std::size_t qindex = pattern.find("?");
  //  cout << pattern << " " << qindex << endl;
  string option1;
  if (qindex != std::string::npos){
    option1=pattern;
    option1.replace(qindex, 1, ".");
    pattern.replace(qindex, 1, "#");
    sum+=checkpattern(option1,  targetvec);
    sum+=checkpattern(pattern,  targetvec);      
    qindex = pattern.find("?");
  }
  else{    // no more question marks - compare to targetvec
    auto observed = countspring(pattern);
    auto matchfound = matchespattern(targetvec, observed);
    int combi =  matchfound? 1 : 0;
    //    cout << pattern << " match: " << matchfound << endl;
    return combi;
  }

  return sum;
}


bool matchespattern(vector<int> target, vector<int> observed){
  return (target == observed);
}


vector<int> countspring(std::string record){

  int ispring=0;
  vector<int> groupvec;
  bool groupstarted=false;
  for (char achar : record){
    if(!groupstarted){   
      if(achar == '#'){
	ispring++;
	groupstarted=true;
      }
    }
    else{
      if(achar == '#'){	// the spring group continues
	ispring++;
      }
      else{      // the spring group is over
	groupvec.push_back(ispring);
	//cout << ispring << endl;
	ispring=0;
	groupstarted=false;
      }
    }
  }  
  // finalise the last group if not over
  if(groupstarted){
    groupvec.push_back(ispring);
    //cout << ispring << endl;
  }

  return groupvec;
}
