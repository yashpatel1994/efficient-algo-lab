import atexit, io, sys


def ceil_array(arr1, l, r, x):  # returns ceil of "x" in a sorted array (i.e. smallest element >= x).

    while r - l > 1:
        m = l + (r - l)//2
        if arr1[m] >= x:
            r = m
        else:
            l = m
    return r


def lis(arr2):

    n = len(arr2)
    tail_arr = [0]*(n+1)    # storing all smallest tail of all increasing subsequences with length i+1 in tail_array[i]

    tail_arr[0] = arr2[0]
    length = 1

    for i in range(1, n):
        if arr2[i] < tail_arr[0]:
            tail_arr[0] = arr2[i]   # updated smallest value
        elif arr2[i] > tail_arr[length - 1]:
            tail_arr[length] = arr2[i] # case where previous largest sequence is extended
            length += 1
        else:
            tail_arr[ceil_array(tail_arr, -1, length - 1, arr2[i])] = arr2[i]  # arr2[i] will replace ceil of the tail_array
    return length


if __name__ == "__main__":

    buffer = io.BytesIO()
    sys.stdout = buffer


    @atexit.register
    def write():
        sys.__stdout__.write(buffer.getvalue())

    # arr = []
    #
    # while True:
    #     try:
    #         raw = raw_input()
    #         if raw == '':
    #             break
    #         arr.append(int(raw))
    #     except EOFError:
    #         break
    n = int(raw_input())
    a = []
    for i in range(n):
        temp = int(raw_input())
        a.append(temp)

    print lis(a)
