from collections import defaultdict
import io, atexit, sys


class undirected_graph:

    def __init__(self, vertices):
        self.V = vertices
        self.graph = defaultdict(list)

    def add_edge(self, u, v):
        self.graph[u].append(v)
        self.graph[v].append(u)

    def dfs_util(self, v, visited):
        visited[v] = True

        for i in self.graph[v]:
            if visited[i] is False:
                self.dfs_util(i, visited)

    def is_connected(self):

        # Mark all the vertices as not visited
        visited = [False] * self.V

        #  Find a vertex with non-zero degree
        for i in range(self.V):
            if len(self.graph[i]) > 1:
                break

        # If there are no edges in the graph, return true
        if i is self.V - 1:
            return True

        # Start DFS traversal from a vertex with non-zero degree
        self.dfs_util(i, visited)

        # Check if all non-zero degree vertices are visited
        for i in range(self.V):
            if visited[i] is False and len(self.graph[i]) > 0:
                return False

        return True

    '''The function returns one of the following values
       0 --> If grpah is not Eulerian
       1 --> If graph has an Euler path (Semi-Eulerian)
       2 --> If graph has an Euler Circuit (Eulerian)  '''

    def is_eulerian(self):
        if self.is_connected() is False:
            return 0
        else:
            odd = 0
            for i in range(self.V):
                if len(self.graph[i]) % 2 != 0:
                    odd += 1

            '''If odd count is 2, then semi-eulerian.
            If odd count is 0, then eulerian
            If count is more than 2, then graph is not Eulerian
            Note that odd count can never be 1 for undirected graph'''
            if odd == 0:
                return 2
            elif odd == 2:
                return 1
            elif odd > 2:
                return 0

    def test(self):
        res = self.is_eulerian()
        if res == 0:
            print "no"
        elif res == 1:
            print "no"
        else:
            print "yes"


class directed_graph:

    def __init__(self, vertices):
        self.V = vertices
        self.graph = defaultdict(list)
        self.IN = [0] * vertices

    def add_edge(self, v, u):

        self.graph[v].append(u)
        self.IN[u] += 1

    def dfs_util(self, v, visited):
        visited[v] = True
        for node in self.graph[v]:
            if visited[node] is False:
                self.dfs_util(node, visited)

    def get_transpose(self):
        gr = directed_graph(self.V)

        for node in range(self.V):
            for child in self.graph[node]:
                gr.add_edge(child, node)

        return gr

    def is_strong_component(self):
        visited = [False] * self.V

        v = 0
        for v in range(self.V):
            if len(self.graph[v]) > 0:
                break

        self.dfs_util(v, visited)

        # If DFS traversal doesn't visit all
        # vertices, then return false.
        for i in range(self.V):
            if visited[i] is False:
                return False

        gr = self.get_transpose()

        visited = [False] * self.V
        gr.dfs_util(v, visited)

        for i in range(self.V):
            if visited[i] is False:
                return False

        return True

    def is_eulerian_cycle(self):

        if self.is_strong_component() is False:
                return False

        for v in range(self.V):
            if len(self.graph[v]) != self.IN[v]:
                return False

        return True


if __name__ == "__main__":

    buffer = io.BytesIO()
    sys.stdout = buffer


    @atexit.register
    def write():
        sys.__stdout__.write(buffer.getvalue())

    t = int(raw_input())
    N, E = map(int, raw_input().split(' '))

    if t == 0:
        g = undirected_graph(N)
        for i in xrange(E):
            u, v = map(int, raw_input().split(' '))
            g.add_edge(u, v)

        g.test()

    elif t == 1:
        g = directed_graph(N)
        for i in xrange(E):
            u, v = map(int, raw_input().split(' '))
            g.add_edge(u, v)

        if g.is_eulerian_cycle():
            print "yes"
        else:
            print "no"
