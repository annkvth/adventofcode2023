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
  std::string line; 
  
  // the first line contains the seeds (seed: numbers+RANGES separated by spaces)
  std::getline(infile, line);
  size_t thecolon=line.find(':');
  // everything after the colon is seed numbers (+2 to skip the leading space)
  std::string seedlist = line.substr(thecolon+2);
  // stringstream to parse this seedlist with getline
  std::istringstream ss(seedlist);
  std::string sPart, sSubpart;
  // fun in part 2: every second number is a range number rather than a seed number
  // don't eat up all the memory by creating all seeds already here, do that later
  std::vector<long> seedstart;
  std::vector<long> seedrange;
  int inum=0;
  while (std::getline(ss, sPart, ' ')) {
    std::istringstream partStream(sPart);
    long value, lastseed;
    while (partStream >> value) {
      if(inum%2==0){
	seedstart.push_back(value);
      }
      else{
	seedrange.push_back(value);
      }
      inum++;
    }
  }
  // new read secton by section and fill the maps
  size_t pos;
  bool newsection=false;
  int isection=-1;
  long source, dest, range;
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
      //std::cout << isection << " " << source << " " << dest << " " << rangeend << std::endl;
      tvecvec.at(isection).push_back( std::make_tuple(source, dest, range) );
    }
    else { //sections are separated by empty lines
      newsection = false;
      //      std::cout << "the section is over" << std::endl;
    }
  }

  // new approach: start at the location, do the mapping in reverse
  int nvecs = tvecvec.size();
  int nseedstart = seedstart.size();
  // now: take a seed, follow it from vector to vector
  long initialvalue, newvalue;
  long minloc=0, minlocseed;
  bool seedfound=false;
  while(!seedfound){
    if(minloc%100000 ==0) std::cout << "checking location " << minloc << std::endl;
    initialvalue=minloc;
    newvalue=minloc;
    for (int ivec=nvecs-1; ivec>=0; ivec--){
      auto currentvec = tvecvec.at(ivec);
      for (auto currenttuple : currentvec){
	std::tie(source,dest,range) = currenttuple;
	// if the destination number is included in this tuple, update value
	if (newvalue>=dest && newvalue <dest+range){
	  //	  std::cout << newvalue << " found in range " << dest << " " << dest+range << std::endl;
	  newvalue=newvalue+(source-dest);
	  //	  std::cout << "... found, remapping to " << newvalue << std::endl;
	  // once it was remapped once, break out of the loop
	  break;
	}
      }
      // std::cout << ivec << " vector, end value of " << initialvalue << " is " << newvalue << std::endl;      
    } // end of the loop over the vectors
    // now see if the seednumber I found is one of the possible seeds
    for(int istart = 0; istart < nseedstart; istart++){
      if(newvalue>=seedstart.at(istart) && newvalue <seedstart.at(istart)+seedrange.at(istart)){
	seedfound=true;
	minlocseed=newvalue;
	//	std::cout << "found seed for location " << minloc << std::endl;
	break;
      }
    }    
    minloc++;
  }
  minloc--; //evil hack to avoid extra if-seedfound in the while loop
  std::cout << "min location is " << minloc << " for seed " << minlocseed << std::endl;

  
  
  return 0;
}


