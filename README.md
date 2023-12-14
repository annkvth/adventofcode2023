
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

part 2: find star symbols, check for touching digits, convert those to full numbers and count (using set to keep numbers unique when more than one digit touches)


## Day 4:
part 1: parse strings to create lists of winning/drawn numbers, compare and score matches --> c++ string

part 2: counts wins per card and multiply following cards --> c++ as before, with added map


## Day 5:
part 1: follow seed number through different lookup "maps" to location number --> c++ std::vector<std::tuple<long,long,long>

part 2: MILLIONS of seed numbers --> c++ as before, but brute-force reverse lookup to find a seed starting from min location


## Day 6:
part 1: read races, use derived (pq-formula) equation to calculate win options --> c++ 

part 2: as part 1, just squash the spaces --> just modify regex


## Day 7:
part 1: order cards by value, rate according to type of set, muliply --> c++ using tuple sort

part 2: as part 1, but give J another worth and apply joker logic



## Day 8
part 1: follow map to left-or-right location in pair --> c++ map

part 2: this was tough! needed a hint from reddit to finish (in hidsight it's obvious...) --> std::lcm




## Day 11:
part 1: find galaxy symbols after expanding input --> python, numpy arrays, re-insert rows to expand

part 2: don't duplicate rows, instead use x to mark which should be expanded --> just add expansion when summing



## Day 12:
part 1: find all possible combinations that match spring-pattern --> C++, recursion for pattern expansion

part 2: ... shoud have written part 1 spring-group-based instead of pattern based! need a new plan...



## Day 13:
part 1: find mirror symmetries --> python 2D array. Fun with edge cases.

part 2: simple edit of part 1: look for exactly a single difference when matching.

