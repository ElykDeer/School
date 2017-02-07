"""
Instructions: READ THE INSTRUCTIONS.

In this recitation you are to write 5 functions. The only code you should write
is in the five places marked "WRITE YOUR CODE HERE." The rest of the code is
to set up and test the code you write. You should of course try different test cases,
but several are written here.

I describe each of them below, and give test code and a header for each
Your task is to make them work as described


To endble the test code for each task, change the booleans below. When you are
working on one task you may want to disable the others.
"""


testTask1=True
testTask2=True
testTask3=True
testTask4=True
testTask5=True


#----------------Some code to check your answers. Ignore

def checkAnswer(yours,correct):
    print("Your answer:")
    print(yours)
    if yours==correct:
        print("Correct!")
    else:
        print("Wrong. The correct answer is:")
        print(correct)

#----------------TASK 1

"""
 Here you are to code a function firstN that takes an iterator I and
 a nonnegative integer n and you should return a list with the
 first n elements of I. You can assume I has at least n elements to
 iterate over

 For example: firstN(iter(range(10000)),10) should give
"""

def firstN(I,n):
    return [next(I) for i in range(n)]


# Here is a generator that generates all the Fibonacci numbers.
# This will be used in the test code
def fib():
    a,b=0,1
    yield a
    yield b
    while (True):
        a,b=b,a+b
        yield b

        
if testTask1:
    print("Task 1")

    checkAnswer( firstN(fib(),10) , [0, 1, 1, 2, 3, 5, 8, 13, 21, 34])

#----------------TASK 2

"""
In this task you are given a 2D array and you should with a funciton
which will return True if any of the elements are duplicated.

For example:
duplicated2D([[0, 1, 2], [3, 4, 5], [6, 7, 8]])
should return false

and

duplicated2D([[0, 1, 2], [3, 4, 5], [6, 7, 0]])
should return true as 0 is duplicated
"""

def duplicated2D(A):
    b=[]
    for y in A:
        for x in y:
            for i in b:
                if i==x:
                    return True
            b.append(x)
    return False


if testTask2:
    print("\nTask 2")

    A1=[ [i+3*j  for i in range(3)] for j in range(3)]
    A2=[ [ (i+3*j)%8  for i in range(3)] for j in range(3)]
    print("Duplicate in ",A1," ?")
    checkAnswer( duplicated2D(A1), False)
    print("\nDuplicate in ",A2," ?")
    checkAnswer( duplicated2D(A2), True)
                        
#----------------TASK 3

"""
 Here you are to write a function that computes the number of digits in a
 nonnegative integer

 It msut be recursive and have no loops

 For example howManyDigits(12345) should return 5
"""

def howManyDigits(x):
    a = (x-(x%10))/10
    if a>=10:
        return 1+howManyDigits(a)
    else:
        return 2
        

if testTask3:
    print("\nTask 3")
    for i,answer in ((5,1),(10,2),(90,2),(123456,6)):
        print()
        print(i," has this many digits:")
        checkAnswer(howManyDigits(i),answer)
    

#----------------TASK 4

"""
In this task you are to write a function to reverse a deque (collections.deque)
Your funciton must be recursive. It must have no loops, no for or while
"""


import collections

#def reverseDeque(D):
#    return D.reverse()

def reverseDeque(D):
    if D:
        a=D.pop()
        b=D.popleft()
        reverseDeque(D)
        D.append(b)
        D.appendleft(a)
    else:
        return collections.deque()

if testTask4:
    print("\nTask 4")
    D=collections.deque( range(10))
    print("Reversing: ",D)
    reverseDeque(D)
    checkAnswer(D,collections.deque([9, 8, 7, 6, 5, 4, 3, 2, 1, 0]))

#----------------TASK 5
"""
Your task here is to code a function that creates a multidimensional array and initializes it.

Your function should look like this:
def makeDDimensionalArray(d,n,f)
(hint: you may need to add other parameters, but give them default values)

n: This is the size in each dimension.
d: This is the number of dimensions
f: This is the function called to initialize the array. It should work as
follows: suppose you have a 3-D array, call it A and you need to initilize
A[i][j][k]. You shoud set it to f( (i,j,k) ).

For example, to create a 2D 5x5 array where A[i][j]=i+j you would call:
checkAnswer(makeDDimensionalArray(2,5,sum)
and this should return:
[[0, 1, 2, 3, 4], [1, 2, 3, 4, 5], [2, 3, 4, 5, 6], [3, 4, 5, 6, 7], [4, 5, 6, 7, 8]]

As another example, to create a 4D 2x2x2x2 array, all of ones, you would call:

checkAnswer(makeDDimensionalArray(4,2,always1)
and ti would return
[[[[1, 1], [1, 1]], [[1, 1], [1, 1]]], [[[1, 1], [1, 1]], [[1, 1], [1, 1]]]]
where always1 is the function defined below that always returns 1

Hint 1: Recursion
Hint 2: My answer is one line long. Yours should not be very long.

"""


def makeDDimensionalArray(d,n,f, location=[]):
    if d>=1:
        return [makeDDimensionalArray(d-1, n, f, location+[i]) for i in range(n)]
    else:
         return f(location)
    #return [[[f((a,b,c)) for a in range(n)] for b in range(d)] for c in range(d)]
    
def always1(x):
    return 1
    
if testTask5:
    print("\nTask 5")
    checkAnswer(makeDDimensionalArray(2,5,sum),
        [[0, 1, 2, 3, 4], [1, 2, 3, 4, 5], [2, 3, 4, 5, 6], [3, 4, 5, 6, 7], [4, 5, 6, 7, 8]])

    checkAnswer(makeDDimensionalArray(4,2,always1),
        [[[[1, 1], [1, 1]], [[1, 1], [1, 1]]], [[[1, 1], [1, 1]], [[1, 1], [1, 1]]]])



