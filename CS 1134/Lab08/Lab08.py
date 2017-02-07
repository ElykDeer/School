class HT:
    def __init__(self):
        self._size=0
        self._A=[-1 for i in range(20)]
        self._B=[-1 for i in range(20)]

    def _bucket(self,k):
        bucky=k
        bucker=2
        while 1:
            bucky=hash(bucky)
            buckyt=bucky%len(self._A)
            if bucker%2==0:
                if bucky==hash(k) and not bucker == 2:
                    return self._resize(2* len(self._A), k)
                if self._A[buckyt]==None or self._A[buckyt]==-1:
                    return (buckyt, "A")
                elif self._A[buckyt][0]==k: 
                #Only don't return if there is something that's someone else in my spot, then continue to next empty/deleted/me
                    return (buckyt, "A")
            elif bucker%2==1:
                if self._B[buckyt]==None or self._B[buckyt]==-1:
                    return (buckyt, "B")
                elif self._B[buckyt][0]==k:
                #Only don't return if there is something that's someone else in my spot, then continue to next empty/deleted/me
                    return (buckyt, "B")
            bucker+=1

    def __getitem__(self,k):
        b=self._bucket(k)
        if b[1] == "A":
            if self._A[b[0]][0] == k: #This Code Replaces Its Own Stuff
                return self._A[b[0]][1]
            raise KeyError( "Key Error:   "+ repr(k))
        else:
            if self._B[b[0]][0] == k: #This Code Replaces Its Own Stuff
                return self._A[b[0]][1]
            raise KeyError( "Key Error:   "+ repr(k))

    def __setitem__(self,k,v):
        b=self._bucket(k)
        if b[1] == "A":
            if self._A[b[0]]==None or self._A[b[0]]==-1: #This Code Replaces Stuff That's Not There
                self._A[b[0]]=(k, v)
            elif self._A[b[0]][0] == k: #This Code Replaces Its Own Stuff
                self._A[b[0]]=(k, v)
            else: #This Code Shifts Stuff If There's Someone In My Way
                temp=self._B[b[0]]
                self._A[b[0]]=(k, v)
                sets = self._bucket(temp[0])
                if sets[1]=="A":
                    self._A[sets[0]]=temp
                else:
                    self._B[sets[0]]=temp
        else:
            if self._B[b[0]]==None or self._B[b[0]]==-1: #This Code Replaces Stuff That's Not There
                self._B[b[0]]=(k, v)
            elif self._B[b[0]][0] == k: #This Code Replaces Its Own Stuff
                self._B[b[0]]=(k, v)
            else: #This Code Shifts Stuff If There's Someone In My Way
                temp=self._B[b[0]]
                self._B[b]=(k, v)
                sets = self._bucket(temp[0])
                if sets[1]=="A":
                    self._A[sets[0]]=temp
                else:
                    self._B[sets[0]]=temp
        self._size+=1
        if self._size > 0.5* len(self._A):
            self._resize(2* len(self._A))

    def __delitem__(self,k):
        
        b=self._bucket(k)
        if b[1] == "A":
            if self._A[b[0]][0] == k: #This Code Replaces Its Own Stuff
                self._A[b[0]] = None
                self._size-=1
                return
            raise KeyError( "Key Error:   "+ repr(k))
        else:
            if self._B[b[0]][0] == k: #This Code Replaces Its Own Stuff
                self._B[b[0]] = None
                self._size-=1
                return
            raise KeyError( "Key Error:   "+ repr(k))

    def __len__(self):
        return self._size

    def __contains__(self,k):
        b=self._bucket(k)
        if b[1] == "A":
            try:
                if self._A[b[0]][0] == k: #This Code Replaces Its Own Stuff
                    return True
            except:
                return False
        else:
            try:
                if self._B[b[0]][0] == k: #This Code Replaces Its Own Stuff
                    return True
            except:
                return False

    def __iter__(self):
        for b in self._A:
            #yield b
            if not b==None and not b==-1:
                yield b[0]
        for b in self._B:
            #yield b
            if not b==None and not b==-1:
                yield b[0]

    def keys(self):
        return list(iter(self))

    def values(self):
        return [self[k] for k in self]

    def items(self):
        return [(k,self[k]) for k in self]

    def _resize(self, newsize, k=None):
        data=self.items()
        self._A=[-1 for i in range(newsize)]
        self._B=[-1 for i in range(newsize)]
        self._size=0
        for k,v in data:
            self[k]=v
        if not k==None:
            return self._bucket(k)
            
            
############################Tests############################
#print(hash("Kyle"))

T=HT()
for i in range(200):
    T[i]=i*i
for i in T.keys():
    T[i]=T[i]+1
for i in range(5,400):
    if i in T:
        del T[i]
K=T.items()
K.sort()
print(K, ",", len(K))
print("[(0, 1), (1, 2), (2, 5), (3, 10), (4, 17)] , 5")
