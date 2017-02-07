import copy
import collections

def f(x,n):
	temp, total = 1, 0
	for i in range(n):
		total+=temp
		temp*=x
	return total+temp

def check(x, y):
	countx, county = 0, 0
	while 1:
		if x[countx]==y[county]:
			return True
		elif x[countx]<y[county]:
			countx+=1
			if len(x)==countx:
				return False
		elif x[countx]>y[county]:
			county+=1
			if len(y)==county:
				return False
				
#a=['f','g','k']
#b=['c','d','i']

#if check(a, b):
	#print("Yes")
#else:
	#print("No")
	
class counter:
	def __init__(self):
		self._i=0
	def print_and_increment(self):
		print(self._i)
		self._i=self._i+1

#A=[0]*5
#for c in A:
	#print(c)
	#c=c+1

countz=0

def rev(A, end=0):
	if end==-1:
		return []
	else:
		return [A[end]]+rev(A, end-1)

#A = [1,2,3,4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0]
#print(rev(A, len(A)-1))

def revLoop():
	for i in A:
		stack.push(A[i])
	B = [stack.pop() for i in A]

a = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15 ,16]]

def flipArray(A):
	B = copy.deepcopy(A)
	iCont=-1
	nCont=-1
	for i in A:
		iCont+=1
		nCont=-1
		for n in i:
			nCont+=1
			B[iCont][nCont] = A[nCont][iCont]
	return B

#print(flipArray(a))

total=0
def fg(n,i=0):
	if n>0:
		i=fg(n-1,i)
		i=fg(n-1,i)
		print(i)
		return i+1
	else:
		global total
		total+=1
		return 0

#fg(3)
#print("")
#print(total)


class flipstack:
	def __init__(self):
		self._stack=collections.deque()
	def push(self, A):
		self._stack.append(A)
	def pop(self):
		return self._stack.pop()
	def flip(self):
		self._stack.reverse()
	def __len__(self):
		return len(self._stack)
		

fs=flipstack()
for i in range(4):
	fs.push(i)
#stack now has 0 1 2 3
fs.flip()
#stack now has 3 2 1 0
for i in range(4):
	fs.push(i+10)
#stack now has 3 2 1 0 10 11 12 13 
while len(fs)>0:
	print(fs.pop())
	fs.flip()
#prints out 13 3 12 2 11 1 10 0


