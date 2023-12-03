# like part 1, but now search numbers in prev and next line,
# and look for * symbol in central line, then multiply

def isstar(char):
    return (char == '*')


# parse the line, find numbers
def extract_numbers(prevline, line, nextline):
    thestars = []
    returnval=0

    starsfound=False
    # checked with grep -there's no double-stars **, but there can be more than one * in a row
    for i, char in enumerate(lineline):
        if isstar(char):
            # keep track of the position of the stars
            thestars.append(i)
            starsfound=True

    # if a line has a star, I need to extract the numbers from the other lines
    if starsfound:
        # check if it touches a number both prev and next
           
        for i,starpos in enumerate(thestars):
            usethis=False
            rangeleft=starpos-1
            if rangeleft==-1:
                rangeleft=0
            rangeright=starpos+1
            if rangeright>=len(line):
                rangeright=len(line)-1
            matches=0
            for jchar in range(rangeleft, rangeright+1):
                if isdigit(prevline[jchar]):
                    matches+=1
                if isdigit(line[jchar]):
                    matches+=1
                if isdigit(nextline[jchar]):
                    matches+=1
            if matches == 2:
                # I found a star touching two digits, now I need to get the full number belonging to the digit
                print('this is still to do')
            
#            returnval=number1*number2
    # check the neighbour fields for symbols - if yes, use this number in the sum

    return returnval

# the main function - read the input and parse line by line to find where numbers are located

standardline = "." * 140
standardlist=list(standardline)
prevline = standardline
aline = standardline
nextline = standardline
sum=0

# for the first line, prepend a line without symbols (and append for the last line)
# I need to have the next line too to make a decision
# -> parsing can start after reading line 2
#with open('example', 'r') as file:
with open('input', 'r') as file:
    for iline, line in enumerate(file):
        line=line.strip()
        if iline == 0:
            prevline=standardlist
            aline=list(line)
        elif iline >= 1:
            nextline=list(line)
            sum+= extract_numbers(prevline, aline, nextline)
            #use extracted numbers, then move lines along
#            print(sum)
            prevline=aline
            aline=nextline
            nextline=standardlist

    # and the last line
    sum+= extract_numbers(prevline, aline, nextline)
    print(sum)
