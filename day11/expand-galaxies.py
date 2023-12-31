# pass previous and next line to the extract_numbers function, and check issymbol for the neighbours
# where neighbours are from start-1 to end+1 
# also remember to check issymbol for start-1 and end+1 in the line itself.

import numpy as np

# match symbols that are not a number and not a .
def isgalaxy(char):
    return (char == '#')

def expand_rows(starimage):
    galaxyinrow=False
    tobeexpanded = []
    for i in range(0, len(starimage)):
        galaxyinrow=False
        for j in range(0, len(starimage[0])):
            #print(f'i {i}, j {j} : {starimage[i][j]}')
            if isgalaxy(starimage[i][j]):
                galaxyinrow=True
        if not galaxyinrow:
            tobeexpanded.append(i)
    
    for row in reversed(tobeexpanded):
        starimage=np.insert(starimage, row, starimage[row], 0)

    return starimage

    
# the main function
# read file into 2d array
#with open('example', 'r') as file:
with open('input', 'r') as file:
    starlist = [list(line.strip()) for line in file]


starimage = np.array(starlist)
starimage = expand_rows(starimage)
# transpose with number to reuse funcion (don't care about row/col)
starimage = expand_rows(starimage.transpose())


galaxies = []
for i in range(0, len(starimage)):
    for j in range(0, len(starimage[0])):
        if isgalaxy(starimage[i][j]):
#            print(f'{i},{j}')
            galaxies.append( (i,j) )

#print(galaxies)


sumofpairs=0
sumdistance=0
# the distance is row-difference plus col difference
for g in range(0, len(galaxies)):
    galaxy1=galaxies[g]
    # only count each pair once
    for h in range(g+1, len(galaxies)):
        if not g==h:
            galaxy2=galaxies[h]            
            sumofpairs+=1
            sumdistance+=abs(galaxy2[0]-galaxy1[0])+abs(galaxy2[1]-galaxy1[1])
            
print(sumofpairs)

print(sumdistance)
