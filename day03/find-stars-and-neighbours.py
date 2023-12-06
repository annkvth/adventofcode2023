# like part 1, but now look for * symbol in central line,
# then find numbers touching it and  multiply

def isstar(char):
    return char == '*'

def isdigit(char):
    return char.isdigit()

def extract_numbers(prevline, line, nextline):
    thestars = []
    returnval = 0

    starsfound = False

    for i, char in enumerate(line):
        if isstar(char):
            thestars.append(i)
            starsfound = True

    if starsfound:
#        print(f'found a star in the line {line}')
        for starpos in thestars:
            unique_numbers = set()
            for jchar in range(starpos - 1, starpos + 2):
                if isdigit(prevline[jchar]):
#                    print(prevline[jchar])
#                    print(get_full_number(prevline, jchar))
                    unique_numbers.add(get_full_number(prevline, jchar))
                if isdigit(line[jchar]):
                    unique_numbers.add(get_full_number(line, jchar))
                if isdigit(nextline[jchar]):
                    unique_numbers.add(get_full_number(nextline, jchar))

            if len(unique_numbers) == 2:
                unique_list = list(unique_numbers)
                returnval = returnval + int(unique_list[0])*int(unique_list[1])
#                print(f'{unique_list[0]} and {unique_list[1]} found for the lines')
#                print(''.join(prevline))
#                print(''.join(line))
#                print(''.join(nextline)+'\n')
                

    return returnval


# need to lock forwards and backwords to combine digits into number
def get_full_number(line, start_index):
    number = ""
    
    index = start_index
    while index < len(line) and isdigit(line[index]):
        number += line[index]
        index += 1
    
    index = start_index - 1
    while index >= 0 and isdigit(line[index]):
        number = line[index] + number
        index -= 1
    
    return number


## ------------------------
# the main function
## ------------------------


standardline = "." * 140
standardlist = list(standardline)
prevline = standardline
aline = standardline
nextline = standardline
sum = 0

with open('input', 'r') as file:
    for iline, line in enumerate(file):
        line = line.strip()
        if iline == 0:
            prevline = standardlist
            aline = list(line)
        elif iline >= 1:
            nextline = list(line)
            sum += extract_numbers(prevline, aline, nextline)
            prevline, aline, nextline = aline, nextline, standardlist

    sum += extract_numbers(prevline, aline, nextline)
    print(sum)
