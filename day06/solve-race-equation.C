#include <algorithm> 
#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>


using namespace std;


/* (t-x)      *   x   > d
  (time left) * speed > distance to beat

  --> x^2 - tx + d < 0 , solutions t/2 -+ sqrt ( (t/2)^2 - d ) 
      ceil(smaller one / -), floor(larger one / +)
 */



std::vector<long> parseline(std::string line, bool part2);

long getWinOptions(long time, long dist);

int main(){

  
  std::ifstream infile("input");
  //std::ifstream infile("example");
  std::vector<long> times;
  std::vector<long> distances;
  
  std::string line; 

  bool isPart2=true;
  // the first line contains the times
  std::getline(infile, line);
  times = parseline(line, isPart2);

  // the next line contains the distances
  std::getline(infile, line);
  distances = parseline(line, isPart2);

  int nraces = times.size();
  long product = 1;
  for(int irace =0; irace <nraces; irace++){
    long options = getWinOptions(times.at(irace), distances.at(irace));
    // std::cout << "time " <<times.at(irace) << " for distance " << distances.at(irace)
    // 	      << " - win options " << options << std::endl;
    product*=options;
  }

  std::cout << "product of win options: " << product << std::endl;

  return 0;
}



long getWinOptions(long time, long dist)
{
    // larger than dist, not >= dist
    long minCharge = ceil(0.5*time - sqrt(0.25*time*time - dist -1));
    long maxCharge = floor(0.5*time + sqrt(0.25*time*time - dist -1));
    //    std::cout << "minCharge " << minCharge << " maxCharge " << maxCharge << std::endl;
    return maxCharge-minCharge+1;
}
  

std::vector<long> parseline(std::string line, bool part2=false)
{
    // clean up extra spaces
    std::regex space_re(R"(\s+)");
    if (!part2){
      line=std::regex_replace(line, space_re, " ");
    }else{
      line=std::regex_replace(line, space_re, "");
    }
    size_t thecolon=line.find(':');
    if(!part2){
      thecolon--; // there's a space after the colon
    }
    // everything after the colon is useful numbers
    std::string numlist = line.substr(thecolon+1);
    std::cout << numlist << endl;
    // stringstream to parse this list with getline
    std::istringstream ss(numlist);
    std::string sNumber;
    std::vector<long> values;
    while (std::getline(ss, sNumber, ' ')) {
      std::istringstream partStream(sNumber);
      long value;
      while (partStream >> value) {
	values.push_back(value);
      }
    }
    return values;
}
  


