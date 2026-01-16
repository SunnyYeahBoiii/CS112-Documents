import sys
input = sys.stdin.readline

INF = int(1e9)

protocol = "BGRY"
mixture = ["BG", "BR", "BY", "GR", "GY", "RY"]

idx = {pr : 1 << i for i, pr in enumerate(protocol)}

def get_mask(s : str) -> int:
    return (idx[s[0]] | idx[s[1]])

n, q = map(int, input().split())
computer = input().split()

mixture_mask = {pr : get_mask(pr) for pr in mixture}
mask = [mixture_mask[_] for _ in computer]

left = [None] * n
right = [None] * n

current_dict = {mixture_mask[pr] : INF for pr in mixture}
for i in range(n):
    left[i] = current_dict.copy()
    current_dict[mask[i]] = i

current_dict = {mixture_mask[pr] : -INF for pr in mixture}
for i in range(n - 1, -1, -1):
    right[i] = current_dict.copy()
    current_dict[mask[i]] = i
    
res = []
for i in range(q):
    u, v = map(int, input().split())
    u = u - 1
    v = v - 1
    ans = INF
    if (mask[u] & mask[v]):
        ans = min(ans, abs(u - v))
    else:
        for bridge in mixture_mask.values():
            if (bridge == mask[u] or bridge == mask[v]):
                continue
            if (bridge & mask[u] and bridge & mask[v]):
                if left[u][bridge] != INF:
                    ans = min(ans, abs(u - left[u][bridge]) + abs(v - left[u][bridge]))
                if left[v][bridge] != INF:
                    ans = min(ans, abs(u - left[v][bridge]) + abs(v - left[v][bridge]))
                if right[u][bridge] != -INF:
                    ans = min(ans, abs(u - right[u][bridge]) + abs(v - right[u][bridge]))
                if right[v][bridge] != -INF:
                    ans = min(ans, abs(u - right[v][bridge]) + abs(v - right[v][bridge]))

    if (ans >= INF):
        ans = -1
        
    print(ans)