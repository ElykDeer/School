import turtle
import math
import random


def randomColor():
    """Code is not used here but you may find it usefull"""
    return [random.random() for i in range(3)]

def drawPlanet(center,size,color,orbitRadius,angle):
    location=[x+orbitRadius*f(angle)
              for x,f in zip(center, (math.sin,math.cos))] #Some trig to compute the location
    turtle.penup()
    turtle.goto(*location)
    turtle.dot(size*2,color) #dot takes diameter rather than radius


def draw():
    """This draw function will be repeatedly called"""
    turtle.clear() 
    turtle.penup()
    turtle.goto(0,0)
    turtle.dot(100,"yellow")
    drawPlanet( (0,0), 30, "Blue", 200, angle) #Replace this with your code to draw
    global angle #Python requires this to change a global variable
    angle+=0.01 
    screen.ontimer(draw,0) #This tells the system to call this function again as soon as possible

angle=0 
turtle.tracer(0,0)
turtle.ht() 
screen=turtle.Screen() #Needed for the following
screen.onkey(turtle.bye,"q") #quits if you press q
screen.ontimer(draw,0) #Tells the system to call draw. Don't call it directly
screen.listen() 
turtle.mainloop()
