import sys
import bisect
input = sys.stdin.readline

def squared_dist(a, b):
    dx = a[0] - b[0]
    dy = a[1] - b[1]
    return dx*dx + dy*dy

n = int(input())
pts = [tuple(map(int, input().split())) for _ in range(n)]
pts.sort()

active = []
ans = squared_dist(pts[0], pts[1])
left = 0

for x, y in pts:
    d = int(ans**0.5)

    while left < n and pts[left][0] < x - d:
        oldx, oldy = pts[left]
        idx = bisect.bisect_left(active, (oldy, oldx))
        if idx < len(active) and active[idx] == (oldy, oldx):
            active.pop(idx)
        left += 1

    lo = bisect.bisect_left(active, (y - d, -10**20))
    hi = bisect.bisect_right(active, (y + d, 10**20))

    for yy, xx in active[lo:hi]:
        dist = (x - xx)*(x - xx) + (y - yy)*(y - yy)
        if dist < ans:
            ans = dist
            d = int(ans**0.5)

    bisect.insort(active, (y, x))

print(ans)
