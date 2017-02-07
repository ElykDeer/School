import lab10

class positionalList(lab10.PositionalList):
    def __len__(self):
        p=self._header
        count=0
        while p._next is not self._trailer:
            p=p._next
            count+=1
        return count
    def firsttolast(self):
        a=self._header._next
        b=self._trailer._prev
        
        self._header._next = a._next
        a._next._prev = self._trailer
        
        b._next, a._prev, self._trailer._prev, a._next = a, b, b, self._trailer

class linkedBinaryTree(lab10.LinkedBinaryTree):
    def flip(self, p=-1):
        if p==-1:
            p=self.root()
            
        if not self.left(p) == None:
            self.flip(self.left(p))
        if not self.right(p) == None:
            self.flip(self.right(p))
            
        p._node._left, p._node._right = p._node._right, p._node._left
            

def stringTree(s):
    T=linkedBinaryTree()
    T._add_root("")
    for i in s:
        curs=""
        p=T.root()
        for l in i:
            curs+=l
            if l == "L":
                if not T.left(p) == None:
                    p=T.left(p)
                else:
                    T._add_left(p, curs)
                    p=T.left(p)
            if l=="R":
                if not T.right(p) == None:
                    p=T.right(p)
                else:
                    T._add_right(p, curs)
                    p=T.right(p)
    return T
            
        
class absoluteHeap(lab10.HeapPriorityQueue):
    def add(self,k):
        super().add(abs(k), k)
    def remove_absolute_min(self):
        return super().remove_min()[1]

PL=positionalList()
for i in range(10):
    PL.add_first(i)
print(len(PL))


print([i for i in PL])
PL.firsttolast()
print([i for i in PL])

T=stringTree(["LL","LRLL","LRR","RR","L"])
print([i.element() for i in T.preorder()])
T.flip()
print([i.element() for i in T.preorder()])

H=absoluteHeap()
H.add(5)
H.add(-2)
H.add(-7)
print(H.remove_absolute_min())
print(H.remove_absolute_min())
