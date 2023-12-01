#!/bin/zsh

sum=0;

cat input | while read line; do;
       alldigits="";
       echo $line | grep -o -e "[0-9]" |   while read digit; do;
	    alldigits="${alldigits}${digit}";
       done;
       selecteddigits="${alldigits[1]}${alldigits[-1]}";
       #echo "$line becomes $alldigits becomes $selecteddigits";
       sum=$((sum + selecteddigits));
done

echo "Sum of extracted digits: $sum"
