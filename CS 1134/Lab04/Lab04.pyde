import random
import time

colN=30
rowN=20

w = 50 # width of each cell

ticking=False

grid = [ [0]*(colN+1) for n in range((rowN+1))] # list comprehension

for row in range(0,rowN):
    for col in range(0,colN):
        grid[row][col] = 0#random.randint(0,1)
        
grid[2][2] = 1
grid[2][3] = 1
grid[2][4] = 1

def setup():
    fullScreen()
    #size(565,575)
    
def draw():
    global ticking
    if ticking:
        #ticking = False
        for row in range(0,rowN):
            for col in range(0,colN):  #Gets to a tile
                ################### Life Check ###################
                Living=0
                
                if row > 0 and row < rowN:
                    checkRangeRow = range(row-1, row+2)
                    tpo=False
                    bottom=False
                elif row==0:
                    checkRangeRow = range(row, row+2)
                    top=True
                    bottom=False
                elif row==rowN:
                    checkRangeRow = range(row-1, row)
                    top=False
                    bottom=True
                
                if col > 0 and col < colN:
                    checkRangeCol = range(col-1, col+2)
                    left=False
                    right=False
                elif col==0:
                    checkRangeCol = range(col, col+2)
                    left=True
                    right=False
                elif col==colN:
                    checkRangeCol = range(col-1, col)
                    left=False
                    right=True
                
                if left:
                    for checkRow in checkRangeRow: #Look at row above and below
                        if not grid[checkRow][-1]==0 and not grid[checkRow][-1]==3:
                            Living+=1
                            print "Left Live"
                if right:
                    for checkRow in checkRangeRow: #Look at row above and below
                        if not grid[checkRow][0]==0 and not grid[checkRow][0]==3:
                            Living+=1
                if top:
                    for checkCol in checkRangeCol: #Look at collumn to left and right
                        if not grid[-1][checkCol]==0 and not grid[-1][checkCol]==3:
                            Living+=1
                if bottom:
                    for checkCol in checkRangeCol: #Look at collumn to left and right
                        if not grid[0][checkCol]==0 and not grid[0][checkCol]==3:
                            Living+=1
                
                for checkRow in checkRangeRow: #Look at row above and below
                    for checkCol in checkRangeCol: #Look at collumn to left and right
                        #print(checkCol, checkRow)
                        if not checkRow==row or not checkCol==col:
                            if not grid[checkRow][checkCol]==0 and not grid[checkRow][checkCol]==3:
                                Living+=1
                           
                #Debugging:
                
                
                ################### GAME RULES ####################
                if Living<2 and not grid[row][col]<1 and not grid[row][col]==3:
                    grid[row][col] = -1
                elif Living>3 and not grid[row][col]<1 and not grid[row][col]==3:
                    grid[row][col] = -1
                elif Living==2 and grid[row][col]==2:
                    grid[row][col] = 1
                elif Living==3 and grid[row][col]==0:
                    grid[row][col] = 3
                elif Living==3 and grid[row][col]==1:
                    grid[row][col] = 2
    
    x,y = 0,0 # starting position

    for row in range(0,rowN):
       for col in range(0,colN):
           if grid[row][col]==-1:
               grid[row][col]=0
           if grid[row][col]==3:
               grid[row][col]=2
               #print row, col 

    for row in range(0,rowN):
        for col in range(0,colN):  #Gets to a tile
          if grid[row][col] == 1:
              fill(250,0,0)
          elif grid[row][col] == 2:
              fill(0,250,0)
          else:
              fill(255)
          rect(x, y, w, w)
          x = x + w  # move right
        y = y + w # move down
        x = 0 # rest to left edge

def keyPressed():
    if key==" ":
        global ticking
        ticking= not ticking
        
    if key=="n":
        for row in range(0,rowN):
            for col in range(0,colN):
                grid[row][col] = 0
    
    if key=="v":
        for row in range(0,rowN):
            for col in range(0,colN):
                grid[row][col] = random.randint(0,1)

def mousePressed():
    if grid[mouseY/w][mouseX/w] == 0:
        grid[mouseY/w][mouseX/w]=1
    elif grid[mouseY/w][mouseX/w] == 1:
        grid[mouseY/w][mouseX/w] = 0
    # integer division is good here!