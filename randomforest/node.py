# -*- coding: utf-8 -*-
"""
Created on Sun Nov 08 12:03:47 2015

@author: Wasit
"""
import numpy as np
class mnode:
    def __init__(self,depth=0,H=0,Q=0,char='*',parent=None):
        self.theta=None  #vector array
        self.tau=None  #scalar
        self.H=H  #scalar
        self.P=None  #vector array
        self.parent=parent  #mnode
        self.depth=depth  #int
        self.L=None  #mnode
        self.R=None  #mnode
        self.char=char
        self.Q=Q
    def __del__(self):
        del self.theta
        del self.tau
        del self.H
        del self.P
        del self.parent
        del self.depth
        del self.L
        del self.R
        del self.char
    def table(self):
        text = self.__repr__()+'\n'
        if self.L is not None:
            text=text+self.L.table()
        if self.R is not None:
            text=text+self.R.table()
 
        return text
    
    def __repr__(self):
        #np.set_printoptions(formatter={'float': '{: 0.2f}'.format})
        if self.tau is None:
            if self.P is None:
                return "Empty!"
            else:
                ids = self.P.argsort()[::-1][:3]
                string='%s %02d H:%.3e,Q:%06d (cl,P):(%03d,%.2f) (%03d,%.2f) (%03d,%.2f)' % (
                self.char,self.depth,self.H,self.Q,ids[0],self.P[ids[0]],ids[1],self.P[ids[1]],ids[2],self.P[ids[2]])
        else:
            string='%s %02d H:%.3e,Q:%06d tau:%s' % (self.char,self.depth,self.H,self.Q,self.tau)
        return string


class tree(mnode):    
    def settree(self,root=mnode(0,0,0)):
        self.theta=root.theta  #vector array
        self.tau=root.tau  #scalar
        self.H=root.H  #scalar
        self.P=root.P  #vector array
        self.parent=root.parent  #mnode
        self.depth=root.depth  #int
        self.char=root.char
        self.Q=root.Q
        if root.L is not None:
            self.L=tree()  #mnode
            self.L.settree(root.L)
            self.R=tree()  #mnode
            self.R.settree(root.R)
    def getP(self,x,dset):
        '''
        input:
            x sample index [int]
            dset the dataset object
        output:
            P [1d ndarray] probability P(L|Ix)
        '''
        #print("test>>mnode:{}".format(self))
        if self.tau is None:#reaching terminal node
            return self.P
        else:
            #if (self.L is not None and goLeft) :
            if (dset.getI(self.theta,x)<self.tau) :
                return self.L.getP(x,dset)
            else:
                return self.R.getP(x,dset)
    
    def getL(self,x,dset):
        '''
        input:
            x sample index [int]
            dset the dataset object
        output:
            L [integer] label
        '''
        return np.argmax(self.getP(x,dset))

if __name__ == '__main__':
    from dataset import dataset
    dset=dataset()
    print dset
    root=mnode()
    
    