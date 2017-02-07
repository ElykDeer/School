###################################################################
#                           Kyle Martin                           #
# Controls:                                                       #
#    "+"/"-" to increase/dcrease recursions (number of leaves)    #
#    "l" to toggle numbering of "nodes" (recursion order)         #
#    Click And Drag Horizontally to adjust branch angle           #
#    Click And Drag Vertically to adjust branch length            #
#    Move Mouse Back and forth on the top of the screen to        #
#        increase windowforce blowing from the right.             #
###################################################################

import sys
import random
import math
import decimal

numb=0
leaf=True
initRec=4
mousesX=0.0
lenScale=800.0
MouseWheeler=0.0

def setup():
    size(1100, 800)
    background(255)
    pixelDensity(displayDensity())

def drawLineAngle(color, start, angle, length, width=1):
    angle += 180  # make up zero degrees
    
    delta_x = mouseX - start[0]
    delta_y = start[1] - mouseY
    if mouseY<height/2.0:
        theta_radians = (atan2(delta_y, delta_x))**4
        if mouseX<1000/2.0:
            theta_radians += random.uniform(0, 8)*(1.0/(mouseX/3.0/width+1.0))
    else:
        theta_radians = 0
    
    end = (start[0] + math.sin(math.radians(angle+theta_radians)) * length,
           start[1] + math.cos(math.radians(angle+theta_radians)) * length)
    
    stroke(*color)
    if width:
        strokeWeight(width)
    else:
        noStroke()
    line(*(start + end))
    return end

def drawText(location,size=10l):
    global numb
    x,y=location
    textSize(size)
    fill("0xff0000")
    textAlign(CENTER)
    text(str(numb), x, y+4)

def drawLeaf(location):
    stroke(0, 50, 0)
    fill(100, 255, 100)
    strokeWeight(0.5)
    ellipse(location[0],location[1],15,15)
    if not leaf:
        drawText(location)
    
def drawNumb(location):
    stroke(0, 50, 0)
    fill(255, 255, 255)
    strokeWeight(0.5)
    ellipse(location[0],location[1],15,15)
    drawText(location)

def recTree(start, angle, length, recDepth, width):
    global numb
    
    if recDepth==0:
        drawLeaf(start)
        return
    else:
        lenz = (length-(length/4.0))*((height+1.0)/(lenScale+1.0))
        
        ang=((recDepth/initRec)*40.0)+((((width/2.0)-mousesX)/(width+1.0/2.0))*(recDepth/initRec)*5.0)
        
        newWid = width-(width/2)
        
        end=drawLineAngle((0,0,0), start, angle, lenz, width)
        
        recTree(end, angle+ang, lenz, recDepth-1.0, newWid)
        recTree(end, angle-ang, lenz, recDepth-1.0, newWid)
        numb+=1
        if not leaf:
            drawNumb(start)
       
def drawTree(start,leaf):
    end = drawLineAngle((255,0,0),start,0,300)
    endL = drawLineAngle((0,255,255),end,25,300)
    endR = drawLineAngle((0,0,255),end,-25,300)
    if leaf:
        drawLeaf(endL)
        drawLeaf(endR)

def keyPressed():
    global leaf
    if key=="l":
        leaf = not leaf
    if key=="p":
        global mousesX
        global lenScale
        print(mousesX, lenScale)
    if key=="+":
        global initRec
        initRec+=1
    if key=="-":
        global initRec
        if initRec > 0:
            initRec-=1
        
def mouseDragged():
    global mousesX
    global lenScale
    mousesX=mouseX
    lenScale=mouseY
    return

def mouseWheel(event):
    global MouseWheeler
    e = event.getCount()
    MouseWheeler += e

def setup():
    global leaf
    leaf=True

def draw():
    clear()
    background(255)
    global numb
    numb=0
    recTree((550,800), 0, 200, initRec, 30)