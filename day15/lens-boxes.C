#include <algorithm>
#include <deque> // similar to vector, but double-ended
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// new in part 2: only letters count for hash
int makehashletters(string step);

bool removalstep(string step);

pair<string, int> labellens(string step);

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
  map<int, deque<pair<string,int>>> theboxes;
  while (getline(infile, step,',')){
    if (!step.empty()){
      // remove the newline at the end
      step.erase(std::remove(step.begin(), step.end(), '\n'), step.end());

      // new in part 2: only letters count for hash
      // this is the number of the box I'm interested in
      ihash=makehashletters(step);

      // is there an entry for this box yet?
      if(theboxes.find(ihash) == theboxes.end()){
	// nothing to do if it's a removal step if the box does not exist
	// otherwise insert the lens
	if (!removalstep(step)){
	  deque<pair<string, int>> lenslist;
	  auto thelabel=labellens(step);
	  lenslist.push_back(thelabel);
	  theboxes.insert({ihash, lenslist});
	  // cout << "create new box "  << ihash << "and add lens " << thelabel.first << endl;
	}
	// else{
	//   cout << "nothing to remove." << endl;
	// }
      }
      else{
	// is there an entry with this label yet?
	// cout << "found existing box "  << ihash << endl;
	deque<pair<string,int>> lenslist = theboxes[ihash];	
	bool exists;
	auto steplabel=labellens(step);
	cout << steplabel.first << " " << steplabel.second << endl;
	auto it = std::find_if( lenslist.begin(), lenslist.end(),
				[&steplabel](const std::pair<std::string, int>& element){ return element.first == steplabel.first;} );
	if( it != lenslist.end())
	  {
	    // if it exists, replace or remove it
	    exists=true;
	    // removalsteps are -1 in focus
	    if (steplabel.second >= 0){
	      // cout << "label " << (*it).first  << " found and will be replaced with "  << steplabel.first << endl;
	    *it = steplabel;
	    }
	    else{
	      // cout << "label " << (*it).first  << " found and will be removed " << endl;
	      lenslist.erase(it);
	    }
	  }
	else{ 
	  exists=false;
	  // it this is not a removal step, insert the element to the end
	  if(steplabel.second >= 0){
	    lenslist.push_back(steplabel);
	    // cout << "label " << steplabel.first  << " inserted into box." << endl;
	  }
	  // else{
	  //   	  cout << "nothing to remove." << endl;
	  // }
	  
	}
	theboxes[ihash]=lenslist;
      }
      
      //      cout << step << " " << ihash << " hash sum " << hsum << endl;
    }
  }


  // The focusing power of a single lens is the result of multiplying together:
  // - One plus the box number of the lens in question.
  // - The slot number of the lens within the box: 1 for the first lens, 2 for the second lens, and so on.
  // - The focal length of the lens.
  long sumF=0;
  for ( auto it = theboxes.begin(); it != theboxes.end(); ++it  ){
    auto lenslist = it->second;
    if (lenslist.size() !=0){
      int ibox=it->first;
      // cout << ibox <<  " box: ";
      ibox++;
      int islot=1;
      for (auto lens : lenslist){
	auto lensF = lens.second;
	// cout << lens.first << " " << lensF << ", " ;
	sumF+=ibox*lensF*islot;
	islot++;
      }
    }
  }
  
  cout << sumF << endl;

  
  return 0;
}




// Hash instructions:
// - Determine the ASCII code for the current character of the string.
// - Increase the current value by the ASCII code you just determined.
// - Set the current value to itself multiplied by 17.
// - Set the current value to the remainder of dividing itself by 256.

int makehashletters(string step){
  // cout << returnvalue << endl;

  // ascii value of a char: int cast it
  // a-z are in the range from 97-122
  int returnvalue = 0;
  for (auto achar : step){
    if( (int)achar >= 97 && (int)achar <=122){
      returnvalue+=(int)achar;
      returnvalue*=17;
      returnvalue%=256;
    }
  }

  return returnvalue;
}


pair<string, int> labellens(string step){
  // the bit before the = is the label, the bit after the focussing power
  string label;
  int focus;
  int pos;
  if(removalstep(step)){
    pos = step.find('-');
    focus=-1;
  }
  else{
    pos = step.find('=');
    focus=stoi(step.substr(pos+1));
  }
  label=step.substr(0,pos);
  //  cout << step << " " << step.substr(pos+1) << endl;
  pair<string, int> labellens(label,focus);
  return labellens;
}


bool removalstep(string step){
  auto pos = step.find("=");
  if (pos!=std::string::npos){
    return false;
  }
  return true;  
}

