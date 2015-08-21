# -*- coding: utf-8 -*-
"""
Created on Sun Jul 26 12:51:58 2015

@author: Wasit
"""
import numpy as np
from matplotlib import pyplot as plt

# the saleman starts from node0 and find the shortest 
# to visit all nodes before comming back to node0
def tsp(A=[],nodes=[],prenode=[],visit={}):    
    if len(nodes)==1:
        curnode=nodes[0]
        return A[prenode,curnode]+A[curnode,0]
    else:
        curnode=nodes.pop()
        return A[prenode,curnode]+tsp(A,nodes,curnode)
if __name__=='__main__':
#create points    
    N=4
    points=np.random.randint(-10,10,[N,2])
#init adjacency matrix
    A=np.zeros([N,N])
    for i in xrange(N):
        for j in xrange(i+1,N):
            print "i:%d,j:%d"%(i,j)
            A[i,j]=A[j,i]=np.linalg.norm(points[i,:]-points[j,:])
#create remaining nodes
    nodes=np.arange(2,N,dtype=np.uint16)

    print tsp(A,nodes,0)
    
    plt.plot(points[:,0],points[:,1])