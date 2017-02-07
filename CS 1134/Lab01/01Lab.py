import timeit
import turtle

def fib1(n):
	if n<2:
		return 1
	else:
		return(fib1(n-1) + fib1(n-2))

def fib2(n):
	a=[1,1]
	if n<2:
		return 1
	for i in range(n+3):
		a.append(a[-1]+a[-2])
		
	return a[-5]

def fib3(n):
	a=1
	b=1
	for i in range(n):
		a,b=b,a+b
	return a
	
def timeFunction(f,n,repeat=1):
	return timeit.timeit(f.__name__+'('+str(n)+')', setup="from __main__ import "+f.__name__,number=repeat)/repeat

def plotFunctionTimesSimple():
	for n in range(1,300):
		turtle.goto(n,timeFunction(fib2,n,100)*500000)
		
def plotFunctionTimes(f,rgb,ran,repeat=1): #(packedFunctionNames, PackedColors, Range, MaxYValue, repeatTimes)
	a=.0005
	b=0
	turtle.setworldcoordinates(0,0,ran[-1],a)
	t=[]
	for func,color in zip(f,rgb):
		t.append(turtle.Turtle())
		t[-1].pencolor(color)
		t[-1].speed(0)
	
	for i in ran:
		for turt,func in zip(t, f):
			b = timeFunction(func,i,repeat)
			if a < b:
				a=b
				turtle.setworldcoordinates(0,0,ran[-1],a)
			turt.goto(i,b)

##Exercise One:
#print([fib1(i) for i in range(10)])

##Exercise Two:
##print([fib2(i) for i in range(10)])

##Exercise Three:
#print([fib3(i) for i in range(10)])
#for f in (fib1,fib2,fib3):
#	print([f(i) for i in range(10)])

##Exercise Four:
#print(timeFunction(fib1,20))

##Exercise Five:
#plotFunctionTimesSimple()
for i in range(40):
	plotFunctionTimes((fib2,fib3), ("blue", "red"), range(1,500,2),repeat=10)
