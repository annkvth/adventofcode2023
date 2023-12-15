#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int makehash(string step);

int main(){
  ifstream infile("input");
  //ifstream infile("example");
  string step;

  // // teststring HASH should result in 52
  // string teststring="HASH";
  // cout << makehash(teststring) << endl;
  
  // Get the input and evaluate line by line
  int ihash;
  int hsum=0;
  while (getline(infile, step,',')){
    if (!step.empty()){
      // remove the newline at the end
      step.erase(std::remove(step.begin(), step.end(), '\n'), step.end());
      ihash=makehash(step);
      hsum=hsum+ihash; 
      //      cout << step << " " << ihash << " hash sum " << hsum << endl;
    }
  }

  cout << hsum << endl;
  return 0;
}


// Hash instructions:
// - Determine the ASCII code for the current character of the string.
// - Increase the current value by the ASCII code you just determined.
// - Set the current value to itself multiplied by 17.
// - Set the current value to the remainder of dividing itself by 256.

int makehash(string step){
  // cout << returnvalue << endl;

  // ascii value of a char: int cast it
  int returnvalue = 0;
  for (auto achar : step){
    returnvalue+=(int)achar;
    returnvalue*=17;
    returnvalue%=256;
  }

  return returnvalue;
}
