import atexit, io, sys


def is_bipartite(graph, N):

    stack = [(0, [0] + [-1]*(N-1), (0, [1] + [-1]*N-1))]

    while stack:
        node, n_colors = stack.pop()

        black_used = [n_colors[neighbor]
                      for neighbor in graph[node]
                      if n_colors[neighbor] == 1]
        if not black_used:
            # the node can be a black node, the n_colors should copy by value
            n_colors[node] = 1
            stack.append((node + 1, n_colors[:]))
        # backtrack, and the node must can be a white node
        n_colors[node] = 0
        stack.append((node + 1, n_colors[:]))



if __name__ == "__main__":

    buffer = io.BytesIO()
    sys.stdout = buffer


    @atexit.register
    def write():
        sys.__stdout__.write(buffer.getvalue())


    while True:
        try:
            N, E = map(int, raw_input().split(' '))
            graph = [[] for _ in range(N)]
            for _ in xrange(E):
                n1, n2 = list(map(int, raw_input().split(' ')))
                graph[n1].append(n2)
                graph[n2].append(n1)
            print graph
        except ValueError:
            break
