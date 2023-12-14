
import numpy as np

def countmatches(array1, array2):
    diffs = 0
    for num1, num2 in zip(array1,array2):
        if num1 != num2:
            diffs+=1
    return diffs

    

def find_mirror(rockarray):
    #print(rockarray)
    #print(rockarray.shape)
    # compare one row to all others to find a mirror copy
    # new in part 2: we want the one that contails one 'smudge' --> exactly one difference 
    matchfound=False
    atedge=False
    mirror=-1
    diffs=0
    for i in range(0, len(rockarray)):
        #print(rockarray[i])
        for j in range(i+1, len(rockarray)):            
            #print(f'comparing {rockarray[j]} and {rockarray[i]}')
            diffs=countmatches(rockarray[j],rockarray[i])
            if diffs <= 1:
                if (i==0) or (j==len(rockarray)-1):
                    # either the first or last row have to be included in the match
                    # can't have mirror axis inside a row
                    if ((j-i)%2 != 0):
                        matchfound=True
                        #print(f'rows {i} and {j} match')
                        if((j-i)==1) and diffs==1:
                            #print('at the edge! it is done')
                            mirror=i+1 #+1 for elf counting
                            return mirror
                        else:
                            # if first and last row match, second and second-to last have to match, and so on
                            for k in range(1, (j+1-i)//2 ):
                                #print(f'checking {i+k} {j-k}')
                                #print(f'comparing {rockarray[i+k]} and {rockarray[k-k]}')
                                diffs+=countmatches(rockarray[i+k],rockarray[j-k])
                                if diffs > 1:
                                    matchfound=False
                                    mirror=-1
                                    #print(f'it broke when checking {i+k} {j-k}')
                                else:
                                    mirror=i+k+1 #+1 for elf counting
                            if matchfound and diffs==1:
                                return mirror                            
                    else:
                        print('dropped out in division ')
                                
               # else:
               #     print(f'rows {i} and {j} match but are not edge')
    if (matchfound is True) and diffs==1:
        #print(f"mirror is {mirror}")
        return mirror
    else:
        return -1
        
   



def process_list(rocklist):
    sum=0
    rockarray = np.array(rocklist)
    mirHoriz = find_mirror(rockarray)
    if (mirHoriz != -1):
        sum+=100*mirHoriz
        print(rockarray.shape)
        print(f"Horizontal symmetry after row {mirHoriz}")
    # transpose with number to reuse funcion (don't care about row/col)
    rockarray = np.transpose(rockarray)
    print('transpose')
    mirVert=find_mirror(rockarray)
    if (mirVert != -1):
        # debug check
        if(sum!=0):
            print("Weird! There's another reflection!")
            print(f"horizontal {mirHoriz}, vertical {mirVert}")
        sum+=mirVert
        print(rockarray.shape)
        print(f"Vertical symmetry after col {mirVert}")

    if (sum==0):
        print("ERROR! NO MIRROR FOUND!!!")
#        print(rocklist)
    return sum


    
# the main function
# read file into 2d array
# empty line mark new patterns
rocklist=[]
sum=0
ipattern=0
#with open('example', 'r') as file:
with open('input', 'r') as file:
#with open('pattern96', 'r') as file:
    for iline, line in enumerate(file):
        rockline=line.strip()
        if rockline != '':
            print(rockline)
#            print(list(rockline))
            rocklist.append(list(rockline))
        elif iline > 0:
            # a pattern is over - process it, then start new one
            ipattern+=1
            print(f"Pattern {ipattern}")
#            print(rocklist)
            sum+=process_list(rocklist)            
            rocklist=[]
            print("\n")

# treat the last pattern too
ipattern+=1
print(f"Pattern {ipattern}")
#print(rocklist)
sum+=process_list(rocklist)


print(f'\n\n\n{sum}')
