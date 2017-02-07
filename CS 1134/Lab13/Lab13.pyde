import copy
import xml.etree.ElementTree as etree

def getMap(file):
    """
This loads the map and returns a pair (V,E)
V contains the coordinates of the veritcies
E contains pairs of coordinates of the verticies
"""
    G=open(file)   
    root = etree.parse(G).getroot()
    v={}
    for child in root:
        if (child.tag=="node"):
            v[child.attrib["id"]]=(float(child.attrib["lon"]),float(child.attrib["lat"]))
    e=[]
    for child in root:
        if (child.tag=="way"):
            a=[]
            for gc in child:
                if gc.tag=="nd":
                    a.append(v[gc.attrib["ref"]])
            for i in range(len(a)-1):
                e.append((a[i],a[i+1]))
    return list(v.values()),e

class Graph:
  """Representation of a simple graph using an adjacency map."""

  #------------------------- nested Vertex class -------------------------
  class Vertex:
    """Lightweight vertex structure for a graph."""
    __slots__ = '_element, _dist'
  
    def __init__(self, x):
      """Do not call constructor directly. Use Graph's insert_vertex(x)."""
      self._element = x
      self._dist=None
  
    def element(self):
      """Return element associated with this vertex."""
      return self._element
  
    def __hash__(self):         # will allow vertex to be a map/set key
      return hash(id(self))

    def __str__(self):
      return str(self._element)
  
    def __getitem__(self, i):
      return self._element[i]
    
  #------------------------- nested Edge class -------------------------
  class Edge:
    """Lightweight edge structure for a graph."""
    __slots__ = '_origin', '_destination', '_element'
  
    def __init__(self, u, v, x):
      """Do not call constructor directly. Use Graph's insert_edge(u,v,x)."""
      self._origin = u
      self._destination = v
      self._element = x
  
    def endpoints(self):
      """Return (u,v) tuple for vertices u and v."""
      return (self._origin, self._destination)
  
    def opposite(self, v):
      """Return the vertex that is opposite v on this edge."""
      if not isinstance(v, Graph.Vertex):
        raise TypeError('v must be a Vertex')
      return self._destination if v is self._origin else self._origin
      raise ValueError('v not incident to edge')
  
    def element(self):
      """Return element associated with this edge."""
      return self._element
  
    def __hash__(self):         # will allow edge to be a map/set key
      return hash( (self._origin, self._destination) )

    def __str__(self):
      return '({0},{1},{2})'.format(self._origin,self._destination,self._element)
    
  #------------------------- Graph methods -------------------------
  def __init__(self, directed=False):
    """Create an empty graph (undirected, by default).

    Graph is directed if optional paramter is set to True.
    """
    self._outgoing = {}
    # only create second map for directed graph; use alias for undirected
    self._incoming = {} if directed else self._outgoing

  def _validate_vertex(self, v):
    """Verify that v is a Vertex of this graph."""
    if not isinstance(v, self.Vertex):
      raise TypeError('Vertex expected')
    if v not in self._outgoing:
      raise ValueError('Vertex does not belong to this graph.')
    
  def is_directed(self):
    """Return True if this is a directed graph; False if undirected.

    Property is based on the original declaration of the graph, not its contents.
    """
    return self._incoming is not self._outgoing # directed if maps are distinct

  def vertex_count(self):
    """Return the number of vertices in the graph."""
    return len(self._outgoing)

  def vertices(self):
    """Return an iteration of all vertices of the graph."""
    return self._outgoing.keys()

  def edge_count(self):
    """Return the number of edges in the graph."""
    total = sum(len(self._outgoing[v]) for v in self._outgoing)
    # for undirected graphs, make sure not to double-count edges
    return total if self.is_directed() else total // 2

  def edges(self):
    """Return a set of all edges of the graph."""
    result = set()       # avoid double-reporting edges of undirected graph
    for secondary_map in self._outgoing.values():
      result.update(secondary_map.values())    # add edges to resulting set
    return result

  def get_edge(self, u, v):
    """Return the edge from u to v, or None if not adjacent."""
    self._validate_vertex(u)
    self._validate_vertex(v)
    return self._outgoing[u].get(v)        # returns None if v not adjacent

  def degree(self, v, outgoing=True):   
    """Return number of (outgoing) edges incident to vertex v in the graph.

    If graph is directed, optional parameter used to count incoming edges.
    """
    self._validate_vertex(v)
    adj = self._outgoing if outgoing else self._incoming
    return len(adj[v])

  def incident_edges(self, v, outgoing=True):   
    """Return all (outgoing) edges incident to vertex v in the graph.

    If graph is directed, optional parameter used to request incoming edges.
    """
    self._validate_vertex(v)
    adj = self._outgoing if outgoing else self._incoming
    for edge in adj[v].values():
      yield edge

  def insert_vertex(self, x=None):
    """Insert and return a new Vertex with element x."""
    v = self.Vertex(x)
    self._outgoing[v] = {}
    if self.is_directed():
      self._incoming[v] = {}        # need distinct map for incoming edges
    return v
      
  def insert_edge(self, u, v, x=None):
    """Insert and return a new Edge from u to v with auxiliary element x.

    Raise a ValueError if u and v are not vertices of the graph.
    Raise a ValueError if u and v are already adjacent.
    """
    if self.get_edge(u, v) is not None:      # includes error checking
      raise ValueError('u and v are already adjacent')
    e = self.Edge(u, v, x)
    self._outgoing[u][v] = e
    self._incoming[v][u] = e

#############################################################################
class Map:
    def __init__(self, map):
        self._Graph=Graph()
        self._Vert, self._Edge = getMap(map)
        self._VertsHash={}
        for v in self._Vert:
            self._VertsHash[v] = self._Graph.insert_vertex(v)
        for e in self._Edge:
            #print(e)
            if self._Graph.get_edge(self._VertsHash[e[0]], self._VertsHash[e[1]]) is None:
                self._Graph.insert_edge(self._VertsHash[e[0]], self._VertsHash[e[1]])
                
    def draw(self, closeC=False):
        scale(float(width)/(maxlon-minlon),float(height)/(maxlat-minlat))
        translate(-minlon,-minlat)
        strokeWeight(0.00001)
        stroke(100,100,100)
        if closeC:
            x,y=mouseToScreen(mouseX,mouseY)
            closeL={}
        for e in self._Graph.edges():
            a,b=e.endpoints()
            line(a[0], a[1], b[0], b[1])
            if closeC:
                midx, midy=(a[0]+b[0])/2, (a[1]+b[1])/2
                closeL[dist(x, y, midx, midy)]=e
        if closeC:
            closestI=min(closeL.keys())
            a,b=closeL[closestI].endpoints()
            strokeWeight(0.0001)
            stroke(0, 255, 0)
            line(a[0], a[1], b[0], b[1])
            self.nrDFS(a)
            
    def nrDFS(self, v):
        v._dist=0
        ops=[v]
        answer=set(v)
        while len(ops)>0:
            v=ops.pop()
            for e in self._Graph.incident_edges(v):
                w=e.opposite(v)
                if w not in answer:
                    w._dist=v._dist+1
                    answer.add(w)
                    ops.append(w)
                    strokeWeight(0.00001)
                    stroke(255-v._dist/2, 0, 0+v._dist/2)
                    line(v[0], v[1], w[0], w[1])
                
    def _DFS(self, v, answer={}, distance=0):
        answer[v]=True
        #if distance>500:
            #return
        #print(distance)
        for e in self._Graph.incident_edges(v):
            w=e.opposite(v)
            if w not in answer:
                strokeWeight(0.00001)
                stroke(255-distance, 0, 0+distance)
                line(v[0], v[1], w[0], w[1])
                self._DFS(w, answer, distance+1)
        
def mouseToScreen(mx,my):
    return (minlon+(mx/float(width))*(maxlon-minlon), minlat+(my/float(height))*(maxlat-minlat))

def setup():
    global Map, maxlat, minlat, maxlon, minlon
    Map = Map("map.osm")
    size(1200, 900)
    pixelDensity(displayDensity())
    maxlat=40.6903
    minlat=40.7061
    maxlon=-73.9728
    minlon=-74.0065
    sys.setrecursionlimit(100000)

def draw():
    background(255,255,255)
    Map.draw(True)