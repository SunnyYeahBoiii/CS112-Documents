from collections import defaultdict, deque
import heapq

class LongestPathBranchAndBound:
    def __init__(self, n, m):
        self.n = n
        self.m = m
        self.graph = defaultdict(list)
        self.best_path = []
        self.best_length = 0

    def add_edge(self, u, v):
        # đồ thị vô hướng
        self.graph[u].append(v)
        self.graph[v].append(u)

    def calculate_upper_bound(self, current_vertex, visited, current_length):
        """
        Upper bound estimation using BFS to count reachable unvisited vertices
        """
        reachable = set()
        queue = deque([current_vertex])
        temp_visited = set([current_vertex])

        while queue:
            u = queue.popleft()
            for v in self.graph[u]:
                if v not in visited and v not in temp_visited:
                    reachable.add(v)
                    temp_visited.add(v)
                    queue.append(v)

        return current_length + len(reachable)

    def branch_and_bound(self):
        initial_visited = frozenset([1])
        initial_path = [1]
        initial_upper_bound = self.calculate_upper_bound(1, initial_visited, 1)

        # Max heap
        heap = [(-initial_upper_bound, -1, 1, initial_visited, initial_path)]

        while heap:
            neg_ub, neg_length, current_vertex, visited, path = heapq.heappop(heap)
            current_length = -neg_length
            upper_bound = -neg_ub

            # prune
            if upper_bound <= self.best_length:
                continue

            # nếu đến đỉnh N → cập nhật nghiệm
            if current_vertex == self.n:
                if current_length > self.best_length:
                    self.best_length = current_length
                    self.best_path = path[:]
                # không mở rộng nữa
                continue

            # mở rộng
            for next_vertex in self.graph[current_vertex]:
                if next_vertex not in visited:
                    new_visited = visited | {next_vertex}
                    new_path = path + [next_vertex]
                    new_length = current_length + 1
                    new_upper_bound = self.calculate_upper_bound(
                        next_vertex, new_visited, new_length
                    )

                    if new_upper_bound > self.best_length:
                        heapq.heappush(
                            heap,
                            (-new_upper_bound, -new_length, next_vertex, new_visited, new_path)
                        )

        return self.best_length, self.best_path


# Main solution
n, m = map(int, input().split())
solver = LongestPathBranchAndBound(n, m)

for _ in range(m):
    u, v = map(int, input().split())
    solver.add_edge(u, v)

length, path = solver.branch_and_bound()

# số cạnh = số đỉnh - 1
print(length - 1)
print(*path)