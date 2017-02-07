import math
import random


def randomColor():
    """Code is not used here but you may find it usefull"""
    return [random.randrange(255) for i in range(3)]


def drawPlanet(center,size,color,orbitRadius,angle):
    location=[x+orbitRadius*f(angle)
              for x,f in zip(center, (math.sin,math.cos))] #Some trig to compute the location
    ellipseMode(RADIUS)
    fill(*color)
    ellipse( location[0],location[1],size,size)


def draw():
    """This draw function will be repeatedly called"""
    clear()
    background(255)
    global angle #Python requires this to change a global variable
    drawPlanet( (400,400), 30, (0,0,255), 200, angle) #Replace this with your code to draw
    angle+=0.01

def setup():
    """This function is called once at the beginning"""
    size(800,800)
    global angle
    angle=0