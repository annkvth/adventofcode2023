# adventofcode2023
following along the adventofcode.com advent callender puzzles 2023

## Day 1:
part 1: extract first and last digit from input file -> done with zsh and grep

part 2: convert written-as-word numbers to digit first -> add in some sed



## Day 2:
part 1: parse strings to find counts of red/green/blue, compare with given max --> c++ string 

part 2: reuse all the code of part 1, just return the product of colors instead of the gameID



## Day 3:
part 1: find position of numbers, check those for symbols in prev/current/next line --> python lists of chars



## Day 4:
part 1: parse strings to create lists of winning/drawn numbers, compare and score matches --> c++ string

part 2: counts wins per card and multiply following cards --> c++ as before, with added map


## Day 5:
part 1: follow seed number through different lookup "maps" to location number --> c++ std::vector<std::tuple<long,long,long>

part 2: MILLIONS of seed numbers --> c++ as before, but brute-force reverse lookup to find a seed starting from min location


