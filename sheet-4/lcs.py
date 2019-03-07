import atexit, io, sys


def lcs(X, Y, size):

    L = [[0 for i in range(size + 1)] for j in range(2)]

    # Binary index, used to index current row and
    # previous row.
    bi = bool

    for i in range(size):
        # Compute current binary index
        bi = i & 1

        for j in range(size + 1):
            if i == 0 or j == 0:
                L[bi][j] = 0

            elif X[i] == Y[j - 1]:
                L[bi][j] = L[1 - bi][j - 1] + 1

            else:
                L[bi][j] = max(L[1 - bi][j], L[bi][j - 1])

    return L[bi][size]


if __name__ == "__main__":

    buffer = io.BytesIO()
    sys.stdout = buffer


    @atexit.register
    def write():
        sys.__stdout__.write(buffer.getvalue())

    n = int(raw_input())
    for i in range(n):
        size = int(raw_input())
        a = map(int, raw_input().strip().split())
        b = map(int, raw_input().strip().split())
        print (lcs(a,b,size))
