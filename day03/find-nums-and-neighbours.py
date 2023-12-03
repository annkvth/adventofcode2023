# pass previous and next line to the extract_numbers function, and check issymbol for the neighbours
# where neighbours are from start-1 to end+1 
# also remember to check issymbol for start-1 and end+1 in the line itself.

# match symbols that are not a number and not a .
def issymbol(char):
    return not (char.isalpha() or char.isdigit() or char == '.')


# parse the line, find numbers
def extract_numbers(prevline, line, nextline):
    numbers = []
    starts = []
    ends = []
    thenumber = ''
    returnval=0

    # find the numbers: keep looking until something isn't a digit
    numstart=-1
    numend=-1
    for i, char in enumerate(line):
        if char.isdigit():
            # keep track of the position of the numbers
            if numstart==-1:
                numstart=i
                starts.append(i)
            thenumber += char
            numend=i
        elif thenumber:
            ends.append(numend)
            numbers.append(int(thenumber))
            thenumber = ''
            numstart=-1
            

    # if a number is in progress when the line ends, finish that one too.
    if thenumber:
        numbers.append(int(thenumber))
        ends.append(numend)

    #print(starts)
    #print(ends)

    # now check if the number should be used
    # one char to left and right, except start or end of line
    for i,anumber in enumerate(numbers):
        usethis=False
        rangeleft=starts[i]-1
        if rangeleft==-1:
            rangeleft=0
        rangeright=ends[i]+1
        if rangeright>=len(line):
            rangeright=len(line)-1
        #print(f'{rangeleft} -- {rangeright}')
        for jchar in range(rangeleft, rangeright+1):
            if (issymbol(prevline[jchar]) or issymbol(line[jchar]) or issymbol(nextline[jchar])):
                usethis=True

        if usethis==True:
            returnval+=anumber
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
