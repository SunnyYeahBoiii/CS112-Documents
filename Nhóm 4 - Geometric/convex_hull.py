import sys
input = sys.stdin.readline

def check(o, a, b) -> bool:
    return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0]) <= 0

def convex_hull(points):
    points.sort()
    
    lower = []
    for pt in points:
        while (len(lower) >= 2) and check(lower[-2], lower[-1], pt):
            lower.pop()
        lower.append(pt)
        
    upper = []
    for pt in reversed(points):
        while (len(upper) >= 2) and check(upper[-2], upper[-1], pt):
            upper.pop()
        upper.append(pt)
    
    lower.pop()
    upper.pop()
    
    return lower + upper

def area(poly):
    s = 0
    n = len(poly)
    
    for i in range(n):
        x1, y1 = poly[i]
        x2, y2 = poly[(i + 1) % n]
        s += x1*y2 - x2*y1
    return abs(s)

def main():
    n = int(input())
    points = []
    for _ in range(n):
        x, y = map(int, input().split())
        points.append((x, y))
        
    hull = convex_hull(points)
    print(area(hull))
    
if __name__ == "__main__":
    main()
