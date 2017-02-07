import random

class PQ:
    class Node:
        def __init__(self, left=None, right=None, data=None, parent=None):
            self._left=left
            self._right=right
            self._data=data
            self._par=parent
            
    class Pos:
        def __init__(self, node=None):
            self.node = node

    def __init__(self, rootData=None, TreeRootNode=None):  #Helpful to create a tree and init the root, but don't have to
        if TreeRootNode:
            self._root = TreeRootNode
        if rootData:
            self._root=self.Node(data=rootData)
        else:
            self._root=None

    def merge(self, N1, N2):
        if not N1:
            return N2
        if not N2:
            return N1

        if N1._data<N2._data:
            N1._left=self.merge(N1._left, N2)
            return N1
        else:
            N2._left=self.merge(N2._left, N1)
            return N2
            
    def flip(self,N):
        #if N==-1:
        #    N=self._root
        if N._left:
            self.flip(N._left)
        N._left, N._right = N._right, N._left
        

    def insert(self, data):  #insert a new data point in heap
        #if self._root:  #Check if the tree is empty
        #    self._root=self.merge(self._root, self.Node(data=data))  #Make a new tree and join it
        #else:
        #    self._root=self.Node(data=data)
        tmp=self.Node(data=data)
        self._root=self.merge(tmp,self._root)
        self.flip(self._root)
            
    def exMin(self):  #Take out the minimum value, the root, and make a new tree
        temp = self._root._data
        self._root=self.merge(self._root._left, self._root._right)
        return temp
    
    def _subtree_size(self, node):
        if node is None:
            return 0
        else:
            return 1+self._subtree_size(node._left)+self._subtree_size(node._right)

    def draw(self, node=None, level=1, x=20, parx=None, pary=None):
        if node==None:
            node=self._root
        XSEP=15
        YSEP=30
        fill(0)
        textAlign(CENTER,CENTER)
        textSize(15)
        lsize=self._subtree_size(node._left)
        myx,myy=x+lsize*XSEP,YSEP*level
        text(str(node._data),myx,myy)
        if node._left is not None:
            self.draw(node._left,level+1,x,myx,myy)
        if node._right is not None:
            self.draw(node._right,level+1,x+(lsize+1)*XSEP,myx,myy)
        if parx is not None:
            strokeWeight(10)
            stroke(0,255,0,30)
            line(parx,pary,myx,myy)


####################### Test Code #######################

#print([pq.exMin() for i in range(20)])

####################### Processing Code #######################
def setup():
    size(1000,1000)
    pixelDensity(displayDensity())

def draw():

    A=list(range(20))
    random.shuffle(A)
    pq=PQ()
    for i in A:
        pq.insert(i)
    print([pq.exMin() for i in range(20)])
    #pq.draw()
    #    b.draw()
    noLoop()