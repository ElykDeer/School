
def f(A):
	B=[]
	for x in A:
		B+=f(x) if isinstance(x,list) else [x]
	return B
		
print(f([5, [7, 4], 3, 2, [], [[2,3]]]))

def g(A):
	return sum(g(x) if isinstance(x,list) else [x] for x in A)
	
print(f([5, [7, 4], 3, 2, [], [[2,3]]]))
