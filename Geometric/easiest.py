import sys
from bisect import bisect_left

input = sys.stdin.readline

W, H, R, Q = map(int, input().split())

events = []
ys = []

for idx in range(R):
    x1, y1, x2, y2 = map(int, input().split())
    events.append((x1, 1, y1, y2, idx))
    events.append((x2, -1, y1, y2, idx))
    ys.extend((y1, y2))

region_aura = [0] * R

for _ in range(Q):
    x, y, a = map(int, input().split())
    events.append((x, 0, y, a, -1))
    ys.append(y)

ys_sorted = sorted(set(ys))
y_id = {v: i for i, v in enumerate(ys_sorted)}  # Fast mapping
S = len(ys_sorted)

def getY(v): return y_id[v]

seg = [-1] * (2 * S)

def seg_update(l, r, val):
    l += S
    r += S
    while l <= r:
        if l & 1:
            seg[l] = val
            l += 1
        if not r & 1:
            seg[r] = val
            r -= 1
        l >>= 1
        r >>= 1

def seg_get(p):
    p += S
    res = -1
    while p:
        if seg[p] != -1:
            res = seg[p]
        p >>= 1
    return res

events.sort(key=lambda x: (x[0], -x[1]))

free = 0

for x, typ, a, b, idx in events:
    if typ == 1 or typ == -1:
        l = getY(a)
        r = getY(b)
        seg_update(l, r, idx if typ == 1 else -1)
    else:
        hy = getY(a)
        rid = seg_get(hy)
        if rid == -1:
            free += b
        else:
            region_aura[rid] += b

print(*region_aura, free)