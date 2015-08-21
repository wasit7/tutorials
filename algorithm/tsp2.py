# -*- coding: utf-8 -*-
"""
from http://www.digitalmihailo.com/
traveling-salesman-problem-dynamic-algorithm-implementation-in-python/
"""
import numpy as np
import itertools as it

if __name__=='__main__':    
#create points    
    N=17
    points=np.random.randint(-10,10,[N,2])
#calc all lengths
    all_distances = [[np.linalg.norm(x-y) for y in points] for x in points]
#initial value - just distance from 0 to every other point + keep the track of edges
    A = {(frozenset([0, idx+1]), idx+1): (dist, [0,idx+1]) for idx,dist in enumerate(all_distances[0][1:])}
    cnt = len(points)
    for m in range(2, cnt):
        B = {}
        for S in [frozenset(C) | {0} for C in it.combinations(range(1, cnt), m)]:
            for j in S - {0}:
                B[(S, j)] = min( [(A[(S-{j},k)][0] 
                + all_distances[k][j], A[(S-{j},k)][1] 
                + [j]) for k in S if k != 0 and k!=j])  
#this will use 0th index of tuple for ordering, 
#the same as if key=itemgetter(0) used
        A = B
    res = min([(A[d][0] + all_distances[0][d[1]], A[d][1]) for d in iter(A)])
    print res[1]