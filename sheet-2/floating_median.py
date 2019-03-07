a = []

while True:
    try:
        a.append(int(raw_input()))
    except EOFError:
        break

    a.sort()
    half = len(a) // 2
    print(int((a[half] + a[~half]) / 2))