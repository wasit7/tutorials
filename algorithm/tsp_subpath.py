# -*- coding: utf-8 -*-
"""
Created on Fri Feb 19 22:26:42 2016

@author: Wasit
"""
from matplotlib import pyplot as plt
import numpy as np
#import sys
def two_opt(A=np.zeros((3,3))):
    N=A.shape[0]
def mycost(A=np.zeros((3,3)),_path=np.arange(3),i=0,j=1 ):
    for    
    cost=A[path[i],path[np.mod(i+1,N)]] + A[path[j],path[np.mod(j+1,N)]]
if __name__=="__main__":
    plt.close('all')
    N=100
    pos=np.random.randint(low=0,high=100,size=(N,2))
    A=np.zeros((N,N))
    ix=range(N)
    ix.append(0)
    for i in xrange(N):
        for j in xrange(N):
            A[i,j]=A[j,i]=np.linalg.norm(pos[i]-pos[j])
        
    path=np.arange(N)   
    while(1):
        cost=new_cost=0.0
        i=j=k=0
        while(cost<=new_cost):
            k+=1
            if(1e4<k):
                return path#sys.exit()
            i,j=np.random.permutation(N)[:2]
            if(j<i):
                i,j=j,i
            cost=A[path[i],path[np.mod(i+1,N)]] + A[path[j],path[np.mod(j+1,N)]]
            new_cost = A[path[i],path[j]] + A[path[np.mod(i+1,N)],path[np.mod(j+1,N)]]
        if i<j:
            L=path[i+1:j+1]
            path[i+1:j+1]=L[::-1]
        else:
            L=path[j:i]
            path[j:i]=L[::-1]
        total_cost=0
        for i in xrange(N):
            j=np.mod(i+1,N)
            total_cost+=A[path[i],path[j]]
        print total_cost
        plt.hold(False)                
        plt.scatter(pos[:,0],pos[:,1])
        plt.hold(True)        
        plt.plot(pos[path[ix],0],pos[path[ix],1])
        plt.draw()
        plt.show(block=False)