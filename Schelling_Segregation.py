def main():
    import numpy as np
    import random
    import seaborn as sns
    import matplotlib.pyplot as plt
    from matplotlib import animation

    #Create Agents
    Empty = 0

    #Create city with NxN places to live
    N = 50
    nIter = 1000
    city = np.ndarray((nIter,N,N),dtype = int)

    #begin with empty houses
    for i in np.arange(nIter):
        city[i] = np.zeros((N,N),dtype = int)
    
    for num_i in range(1,N-1):
        for num_j in range(1,N-1):
            city[0,num_i,num_j] = np.random.randint(low = 0, high = 3,dtype = int) 

    #rules
    def lHappiness(center,upLeft,up,upRight,left,right,botLeft,bot,botRight):
        #treshold of segregation
        tresh = 0.8
        #counts of similarity
        nSim = 0
        nDif = 0
        for j in [upLeft,up,upRight,left,right,botLeft,bot,botRight]:
            if (j == center):
                nSim += 1
                #print(nSim)
            else:
                nDif +=1
                #print(nDif)
        if (nSim + nDif) == 0:
            return False
        else:
            return ((nSim/(nSim + nDif)) < tresh)
    
    for k in range(nIter-1):
        for l in range(1,N-1):
            for m in range(1,N-1):
                #if this part is empty we want to continue with the next point
                if city[k,l,m] == Empty:
                    continue
                #if its happy then continue with the next point
                elif lHappiness(city[k,l,m],city[k,(l-1)%N,(m-1)%N],city[k,(l-1)%N,(m)%N],city[k,(l-1)%N,(m+1)%N],city[k,(l)%N,(m-1)%N],city[k,(l)%N,(m+1)%N],city[k,(l+1)%N,(m-1)%N],city[k,(l+1)%N,(m)%N],city[k,(l+1)%N,(m+1)%N]) == False:
                    continue
                #if its not happy then move
                elif lHappiness(city[k,l,m],city[k,(l-1)%N,(m-1)%N],city[k,(l-1)%N,(m)%N],city[k,(l-1)%N,(m+1)%N],city[k,(l)%N,(m-1)%N],city[k,(l)%N,(m+1)%N],city[k,(l+1)%N,(m-1)%N],city[k,(l+1)%N,(m)%N],city[k,(l+1)%N,(m+1)%N]) == True:
                    newPosBool = True
                    while(newPosBool):
                        newX = random.randint(1,N-1)
                        newY = random.randint(1,N-1)
                        if (city[k,newX,newY] == Empty):
                            city[k,newX,newY] = city[k,l,m]
                            city[k,l,m] = 0
                            break
                else:
                    print("else? not right")
                    continue
        city[k+1] = city[k]
    
    sns.heatmap(city[0],cmap = "Blues")
    plt.show()
    sns.heatmap(city[nIter-1],cmap = "Blues")
    plt.show()
    


if __name__ == "__main__":
    main()
