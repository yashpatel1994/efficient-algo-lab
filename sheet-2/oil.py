import atexit, io, sys, math


def create_matrix(list):
    mat = []
    n = int(len(list)**(1/2.0))
    for i in xrange(n):
        row_list = []
        for j in range(n):
            row_list.append(list[n * i + j])
        mat.append(row_list)

    return mat


def max_sub_array(a):
    max_so_far = a[0]
    curr_max = a[0]

    for i in range(1, len(a)):
        curr_max = max(a[i], curr_max + a[i])
        max_so_far = max(max_so_far, curr_max)

    return max_so_far


def max_sub_matrix(arr):

    col = len(arr[0])
    row = len(arr)
    max_sum = 0

    for i in range(col):
        temp = [0 for _ in range(row)]
        for j in range(i,col):
            for k in range(row):
                temp[k] += arr[k][j]

            summ = max_sub_array(temp)

            if summ > max_sum:
                max_sum = summ

    return max_sum


if __name__ == "__main__":

    buffer = io.BytesIO()
    sys.stdout = buffer


    @atexit.register
    def write():
        sys.__stdout__.write(buffer.getvalue())

    n = int(raw_input())
    raw = raw_input().split()
    raw = map(int, raw)
    #raw = [int(x) for x in raw]
    arr1 = create_matrix(raw)
    result = max_sub_matrix(arr1)

    print result