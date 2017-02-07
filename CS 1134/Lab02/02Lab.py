#Kyle Reed Martin

import turtle, math, random, decimal, copy


def randomColor():
	return [random.random() for i in range(3)]

def draw():
	#ClearUniverse
	turtle.clear()

	#Update
	Sol.tick()
	for i in Bloom.blooms:
		i.tick()

	#DrawEffects
	for i in Bloom.blooms:
		i.draw()

	#DrawUniverse
	Sol.draw()

	#Cleanup
	screen.ontimer(draw,0) #This tells the system to call this function again as soon as possible
	return None


class Bloom:
	blooms=[]
	def __init__(self, center):
		self._center=center
		self._size=center.getSize()+2
		self._location=center.getLocation()
		self._color=center.getColor()
		Bloom.blooms.append(self)
	def draw(self):
		turtle.penup()
		turtle.goto(*self._location)
		turtle.dot(self._size*2,self._color)
		turtle.dot((self._size-2)*2,"Black")
	def tick(self):
		self._size+=1
		self._location=self._center.getLocation()
		for i in range(3):
			if self._color[i] >= 0.01:
				self._color[i]-=.01
			else:
				self._color[i]=0
		#for i in self._color:
			#print(i)
			#if i >= 0.1:
				#i=i-.1
			#else:
				#print("zero")
				#i=0
		if self._color==[0,0,0]:
			Bloom.blooms.remove(self)


class Sun:
	Suns=0
	def __init__(self,center,size,color):
		self._center=center
		self._size=size
		self._color=color
		
		#Edit Later to Equally Space Suns
		Sun.Suns+=1
		self._orbitRadius=0
		self._angle=0
		self._speed=decimal.Decimal(0)
		
		self.move()
		
	def draw(self):
		turtle.penup()
		turtle.goto(*self._location)
		turtle.dot(self._size*2,self._color)
	
	def move(self):
		self._location=[x+self._orbitRadius*f(self._angle) for x,f in zip(self._center, (math.sin,math.cos))]
	
	def getLocation(self):
		return self._location
		
	def getSize(self):
		return self._size
	
	def setColor(self, color):
		self._color=color
	
	def getColor(self):
		return self._color
			
	def isInside(self,location):
		x,y=location
		_x,_y=self._location
		if ((x - _x)**2 + (y - _y)**2) < self._size**2:
			return True
		else:
			return False
		
	def onClick(self,location):
		self.setColor(randomColor())
			
	def incSize(self):
		self._size+=1
		
	def decSize(self):
		if self._size>1:
			self._size-=1

	def incSpeed(self):
		self._speed+=decimal.Decimal(.0001)
		
	def decSpeed(self):
		self._speed-=decimal.Decimal(.0001)

	
class Planet(Sun):
	def __init__(self, center,size,color,speed,orbitRadius):
		self._center=center
		self._size=size
		self._color=color
		self._speed=speed
		self._orbitRadius=orbitRadius
		self._angle=random.randint(0,360)
		self._location=[x+self._orbitRadius*f(self._angle) for x,f in zip(self._center.getLocation(), (math.sin,math.cos))] 
	def move(self):
		self._angle+=self._speed
		self._location=[x+self._orbitRadius*f(self._angle) for x,f in zip(self._center.getLocation(), (math.sin,math.cos))] #Some trig to compute the location


class SolarSystem:
	def __init__(self):
		self._Suns=[Sun((0,0), 30, [random.random() for i in range(3)])]
		self._Planets=[Planet(self._Suns[0], random.randint(7,18), randomColor(), (decimal.Decimal(random.randint(1000,6000))/1000000), random.randint(50,400)) for i in range(0,6)]#random.randint(1,100)
		self._Moons=[Planet(self._Planets[random.randint(0,len(self._Planets)-1)], random.randint(1,6), randomColor(), (decimal.Decimal(random.randint(5000,6000))/1000000), random.randint(10,100)) for i in range(4,13)]#random.randint(1,100)
		self._lastClicked=None
		
	def draw(self):
		for i in self._Suns:
			i.draw()
		for i in self._Planets:
			i.draw()
		for i in self._Moons:
			i.draw()
	
	def tick(self):
		for i in self._Suns:
			i.move()
		for i in self._Planets:
			i.move()
		for i in self._Moons:
			i.move()
			
	def onClick(self,location):
		for i in self._Suns:
			if i.isInside(location):
				Bloom(i)
				i.onClick(location)
				self._lastClicked=i
				return
		for i in self._Planets:
			if i.isInside(location):
				Bloom(i)
				i.onClick(location)
				self._lastClicked=i
				return
		for i in self._Moons:
			if i.isInside(location):
				Bloom(i)
				i.onClick(location)
				self._lastClicked=i
				return
				
	def rightKey(self):
		self._lastClicked.incSize()
	def leftKey(self):
		self._lastClicked.decSize()
	def rightBrakKey(self):
		self._lastClicked.incSpeed()
	def leftBrakKey(self):
		self._lastClicked.decSpeed()
	def nKey(self):
		Bloom(self._lastClicked)
		self._lastClicked.setColor(randomColor())
	def spaceKey(self):
		self._Moons.append(Planet(self._lastClicked, random.randint(1,6), randomColor(), (decimal.Decimal(random.randint(5000,6000))/1000000), random.randint(10,100)))
		Bloom(copy.deepcopy(self._Moons[-1]))

	
def onClick(x,y):
	Sol.onClick((x,y))
def rightKey():
	Sol.rightKey()
def leftKey():
	Sol.leftKey()
def rightBrakKey():
	Sol.rightBrakKey()
def leftBrakKey():
	Sol.leftBrakKey()
def nKey():
	Sol.nKey()
def spaceKey():
	Sol.spaceKey()

		
#DefaultUniverse!
Sol=SolarSystem()

#Default Planets
#sun=Sun((0,0), 30, "yellow")
#planet=Planet(5, "Blue", .001, sun, 200)


turtle.bgcolor("black")
angle=0 
turtle.tracer(0,0)
turtle.ht() 
screen=turtle.Screen() #Needed for the following
screen.onkey(turtle.bye,"q") #quits if you press q
screen.ontimer(draw,0) #Tells the system to call draw. Don't call it directly

###Listeners###
screen.onclick(onClick)
screen.onkey(rightKey,"Right")
screen.onkey(leftKey,"Left")
screen.onkey(rightBrakKey,"bracketright")
screen.onkey(leftBrakKey,"bracketleft")
screen.onkey(nKey,"n")
screen.onkey(spaceKey,"space")

screen.listen() 
turtle.mainloop()
