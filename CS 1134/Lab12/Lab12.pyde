Compressed=False

class suffixTrie:
    class _Node:
        def __init__(self,start,end):
            self.children={}
            self._start=start
            self._end=end
        
        #If I have only one child, add one to my index, take that child's children, anex that child
        def Compress(self, n=None):
            if n==None:
                n = self
            for i in self.children.values():
                if len(i.children)>0:
                    i.Compress(i)
            if len(self.children)==1:
                self._end=self.children[self.children.keys()[0]]._end
                self.children=self.children[self.children.keys()[0]].children
        
        def draw(self,c,x,y):
            textbox=TextBox(c,x,y)
            textbox.draw()
            xend=x
            for childChar in self.children:
                (xend,childbox)=self.children[childChar].draw(S[self.children[childChar]._start:self.children[childChar]._end],xend,y+70)  #Not using a slice in the creation of tree, as directed... Only using a slice when drawing the tree.
                textbox.drawLineToOtherBoxBelow(childbox)
            return (max(xend,x+textbox.width()+10),textbox)
    
    def __init__(self,s=None):
        self._root=self._Node(0,0)
        self._string=s
        if s:
            for i in range(len(s)):
                self.insert(i)
        if Compressed:
            self._root.Compress()
    
    def insert(self,a):
        n=self._root
        for c in range(a,len(self._string)):
            if self._string[c] not in n.children:
                n.children[self._string[c]]=self._Node(c, c+1)
            n=n.children[self._string[c]]
    def draw(self,x,y):
        self._root.draw("",x,y)

class TextBox:
    TEXTSIZE = 30

    def __init__(self, text, x=0, y=0):
        self._text, self._x, self._y = text, x, y

    def replaceText(self, text):
        self._text = text

    def setLocation(self, x, y):
        self._x, self._y = x, y

    def draw(self):
        textAlign(LEFT, TOP)
        textSize(TextBox.TEXTSIZE)
        rectMode(CORNER)
        fill(255)
        stroke(0)
        strokeWeight(1)
        rect(self._x, self._y, self.width(), self.height())
        fill(0)
        text(self._text, self._x + textWidth(" ") //
             2, self._y - textDescent() // 2)

    def width(self):
        textSize(TextBox.TEXTSIZE)
        return textWidth(self._text + " ")

    def height(self):
        textSize(TextBox.TEXTSIZE)
        return textAscent() + textDescent()

    def drawLineToOtherBoxBelow(self, otherBox):
        stroke(0)
        textSize(TextBox.TEXTSIZE)
        strokeWeight(1)
        line(self._x + self.width() / 2, self._y + self.height(),
             otherBox._x + otherBox.width() / 2, otherBox._y)

def keyPressed():
    global S
    if key==u'\x08':
        S=S[:-1]
    elif key==TAB:
        global Compressed
        Compressed = not Compressed
    elif key!=65535:
        S+=key
    redraw()

def setup():
    global S
    S=""
    size(1200, 1000)
    pixelDensity(displayDensity())
    noLoop()

def draw():
    background(200,150,200)
    TextBox(S,10,10).draw()
    ST=suffixTrie(S)
    ST.draw(50,100)