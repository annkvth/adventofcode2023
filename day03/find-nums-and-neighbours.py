# draft - still to do:
# pass previous and next line to the extract_numbers function, and check issymbol for the neighbours
# where neighbours are from start-1 to end+1 
# also remember to check issymbol for start-1 and end+1 in the line itself.

# match symbols that are not a number and not a .
def issymbol(char):
    return not (char.isalpha() or char.isdigit() or char == '.')

# check the neighbour fields for symbols - if yes, use this number in the sum
def usethisnumer():
    # to do
    #return 

# parse the line, find numbers
def extract_numbers(line):
    numbers = []
    starts = []
    ends = []
    thenumber = ''

    # find the numbers: keep looking until something isn't a digit
    numstart=-1
    numend=-1
    for i, char in enumerate(line):
        if char.isdigit():
            # keep track of the position of the numbers
            if numstart==-1:
                numstart=i
                starts.append(i)
            print(f"Found digit {char} at index {i}")
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

    print(starts)
    print(ends)

    return numbers

# the main function - read the input and parse line by line to find where numbers are located

file = ["467..114..", "...*......", "..35..633.", "......#..."]
# with open('input', 'r') as file:
for line in file:
    line = line.strip()
    char_array = list(line)
    numbers = extract_numbers(char_array)

    # Do something with the extracted numbers
    print(numbers)
