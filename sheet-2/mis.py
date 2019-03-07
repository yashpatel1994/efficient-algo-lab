import atexit, io, sys


def coloring(graph, n_node):
    """
    maximizing the black color nodes will give us the largest MIS.
    the graph may contain isolated nodes or disconnected components.
    0 is white, 1 is black
    """
    max_n_black = 0

    # the first node can be a white or a black node.
    stack = [(0, [0] + [-1] * (n_node - 1)), (0, [1] + [-1] * (n_node - 1))]
    while stack:
        node, n_colors = stack.pop()
        if node >= n_node:
            # assert sum(1 for c in n_colors if c == -1) == 0
            n_black = sum(n_colors)
            if n_black > max_n_black:
                max_n_black = n_black
            continue
        # test if the current can be a black node.
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

    return (max_n_black)


if __name__ == '__main__':

    recs = iter(sys.stdin.readlines())
    n = int(next(recs))

    for c in range(n):
        nodes, edges = list(map(int, next(recs).split()))
        graph = [[] for _ in range(nodes)]
        for _ in range(edges):
            n1, n2 = list(map(int, next(recs).split()))
            graph[n1 - 1].append(n2 - 1)
            graph[n2 - 1].append(n1 - 1)

        n_black = coloring(graph, nodes)

        print (n_black)