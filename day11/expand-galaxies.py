# pass previous and next line to the extract_numbers function, and check issymbol for the neighbours
# where neighbours are from start-1 to end+1 
# also remember to check issymbol for start-1 and end+1 in the line itself.

# match symbols that are not a number and not a .
def isgalaxy(char):
    return (char == '#')



# the main function
# read file into 2d array
with open('example', 'r') as file:
#with open('input', 'r') as file:
    starimage = [list(line.strip()) for line in file]

sum=0
#sum+= extract_numbers(prevline, aline, nextline)

for i in range(0, len(starimage)):
    for j in range(0, len(starimage[0])):
        if isgalaxy(starimage[i][j]):
            print(f'{i},{j}')

print(sum)
