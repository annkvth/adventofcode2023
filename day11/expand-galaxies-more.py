# pass previous and next line to the extract_numbers function, and check issymbol for the neighbours
# where neighbours are from start-1 to end+1 
# also remember to check issymbol for start-1 and end+1 in the line itself.

import numpy as np


def isgalaxy(char):
    return (char == '#')


# new expansion idea: change characters of rows that have to be expanded
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
        starimage[row]=np.char.replace(starimage[row], '.', 'x')

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
#print(starimage)

galaxies = []
for i in range(0, len(starimage)):
    for j in range(0, len(starimage[0])):
        if isgalaxy(starimage[i][j]):
#            print(f'{i},{j}')
            galaxies.append( (i,j) )

#print(galaxies)


sumofpairs=0
sumdistance=0
expansion=1000000
# the distance is row-difference plus col difference
for g in range(0, len(galaxies)):
    galaxy1=galaxies[g]
    # only count each pair once
    for h in range(g+1, len(galaxies)):
        if not g==h:
            galaxy2=galaxies[h]            
            sumofpairs+=1
            #define the path from one to another
            if galaxy1[0]<galaxy2[0]:
                rstart=galaxy1[0]
                rstop=galaxy2[0]
            else:
                rstart=galaxy2[0]
                rstop=galaxy1[0]
            if galaxy1[1]<galaxy2[1]:
                cstart=galaxy1[1]
                cstop=galaxy2[1]
            else:
                cstart=galaxy2[1]
                cstop=galaxy1[1]

#            print(f'{galaxy1} {galaxy2} {rstart} {rstop} {cstart} {cstop}')
            
            #check number of 'x' expand markers on the way down and over
            rdist=0
            cdist=0
            for ir in range(rstart, rstop):
                if starimage[ir][cstart]=='x':
                    rdist+=expansion
                else:
                    rdist+=1

            for ic in range(cstart, cstop):
                if starimage[rstart][ic]=='x':
                    cdist+=expansion
                else:
                    cdist+=1
#            print(f'{rdist} {cdist}')            
            sumdistance+=cdist+rdist
            
print(sumofpairs)

print(sumdistance)
