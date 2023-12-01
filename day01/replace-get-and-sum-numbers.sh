#!/bin/zsh

# like get-and-sum-numbers.sh, but I need to add one more step
# first to replace written-as-words numbers with digits
# (for readability, split replacement in three lines)
# challenge: xtwone3four should have the two extracted,
# not the one, so I need to read and replace char by char

function read_and_replace(){
  wordstart="";
  wordend=$1
  while test -n "$wordend";
  do;
    wordstart="${wordstart}${wordend:0:1}";
    wordstart=$(replace_nums "$wordstart")
    #echo "beginning is $wordstart , end of word $wordend";
    wordend=${wordend:1};
  done

  echo $wordstart
}


# aparently sevenine should be read as 79 and not 7ine,
# so I need to leave some letters intact
function replace_nums(){
  numline=$(echo $1 | sed -e 's/one/o1e/g' -e 's/two/t2o/g' -e 's/three/t3e/g')
  numline=$(echo $numline | sed -e 's/four/f4r/g' -e 's/five/f5e/g' -e 's/six/s6x/g')
  numline=$(echo $numline | sed -e 's/seven/s7n/g' -e 's/eight/e8t/g' -e 's/nine/n9e/g')
  echo "$numline"
}

sum=0;

cat input |while read line;
do;
  alldigits="";
  numline=$(read_and_replace "$line")
  echo $numline | grep -o -e "[0-9]" |   while read digit;
  do;
    alldigits="${alldigits}${digit}";
  done;
  selecteddigits="${alldigits[1]}${alldigits[-1]}";
  #echo "$line becomes $alldigits becomes $selecteddigits";
  sum=$((sum + selecteddigits));
done

echo "Sum of extracted digits: $sum"
