def solve(N, iarr):
    cost = 0
    for i in range(N-1):
        minidx = i
        for j in range(i+1,N):
            if iarr[j] < iarr[minidx]:
                minidx, minval = j, iarr[j]
        iarr = iarr[:i] + iarr[i:minidx+1][::-1] + iarr[minidx+1:]
        cost += minidx-i+1
    return cost
        

if __name__ == '__main__':
    T = int(input())
    for t in range(T):
        N = int(input())
        iarr = list(map(int, input().split()))
        print('Case #{}: {}'.format(t+1, solve(N,iarr)))