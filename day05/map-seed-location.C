#include <algorithm> // for std::find
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>




int main(){
  
  // store the different mappings in vectors of tuples
  // tuple style: source destination rangeend
  std::vector<std::tuple<long,long,long>> seed_soil_tvec;
  std::vector<std::tuple<long,long,long>> soil_fertilizer_tvec;
  std::vector<std::tuple<long,long,long>> fertilizer_water_tvec;
  std::vector<std::tuple<long,long,long>> water_light_tvec;
  std::vector<std::tuple<long,long,long>> light_temperature_tvec;
  std::vector<std::tuple<long,long,long>> temperature_humidity_tvec;
  std::vector<std::tuple<long,long,long>> humidity_location_tvec; 
  // to loop over them, make a vector of the tuple vectors
  std::vector< std::vector<std::tuple<long,long,long> >> tvecvec;
  tvecvec.push_back(seed_soil_tvec);
  tvecvec.push_back(soil_fertilizer_tvec);
  tvecvec.push_back(fertilizer_water_tvec);
  tvecvec.push_back(water_light_tvec);
  tvecvec.push_back(light_temperature_tvec);
  tvecvec.push_back(temperature_humidity_tvec);
  tvecvec.push_back(humidity_location_tvec); 

  
  std::ifstream infile("input");
  //std::ifstream infile("example");
  std::vector<long> seeds;
  std::string line; 
  
  // the first line contains the seeds (seed: numbers separated by spaces)
  std::getline(infile, line);
  size_t thecolon=line.find(':');
  // everything after the colon is seed numbers (+2 to skip the leading space)
  std::string seedlist = line.substr(thecolon+2);
  // stringstream to parse this seedlist with getline
  std::istringstream ss(seedlist);
  std::string sPart, sSubpart;
  while (std::getline(ss, sPart, ' ')) {
    std::istringstream partStream(sPart);
    long value;
    while (partStream >> value) {
      seeds.push_back(value);
    }
  }
  // new read secton by section and fill the maps
  size_t pos;
  bool newsection=false;
  int isection=-1;
  long source, dest, range, rangeend;
  while (std::getline(infile, line)){
    pos = line.find(" map:"); // see if this line starts a new section
    if (pos!=std::string::npos){ 
      newsection=true;
      isection++;
      //      std::cout << isection << " new section " << line << std::endl;
    } // if no section header line and not empty, read into a tuple
    else if (!line.empty()){
      std::istringstream sss(line);
      sss >> dest >> source  >> range;
      rangeend=source+range;
      //std::cout << isection << " " << source << " " << dest << " " << rangeend << std::endl;
      tvecvec.at(isection).push_back( std::make_tuple(source, dest, rangeend) );
    }
    else { //sections are separated by empty lines
      newsection = false;
      //      std::cout << "the section is over" << std::endl;
    }
  }

  int nvecs = tvecvec.size();
  // now: take a seed, follow it from vector to vector
  long initialvalue, newvalue;
  long minloc=-1, minlocseed;
  for (long seed: seeds){
    initialvalue = seed;
    // initial assumption: the value is mapped to itself
    newvalue = seed;
    for (int ivec=0; ivec<nvecs; ivec++){
      auto currentvec = tvecvec.at(ivec);
      for (auto currenttuple : currentvec){
	std::tie(source,dest,rangeend) = currenttuple;
	// if the seed number is included in this tuple, update value
	if (newvalue>=source && newvalue <rangeend){
	  // std::cout << newvalue << " found in range " << source << " " << rangeend << std::endl;
	  newvalue=newvalue+(dest-source);
	  // std::cout << "... found, remapping to " << newvalue << std::endl;
	  // once it was remapped once, break out of the loop
	  break;
	}	
      }
      // std::cout << ivec << " vector, end value of " << initialvalue << " is " << newvalue << std::endl;      
    }
    std::cout << "started with seed " << initialvalue
	      << ", the location is " << newvalue << std::endl;
    if ((minloc==-1) || (newvalue<minloc)){
      minloc=newvalue;
      minlocseed=initialvalue;
    }
  }
  std::cout << "min location is " << minloc << " for seed " << minlocseed << std::endl;

  return 0;
}


