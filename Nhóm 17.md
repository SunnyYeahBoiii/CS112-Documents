# Bài 1:

Từ bài toán, ta có một thuật toán loang cơ bản như sau:
```python
dir = [[1 , 0] , [0 , 1] , [-1 , 0] , [0 , -1]]
vis = {}
  
n = int(input())

def flood(x , y):
    if vis.get((x , y)) == True:
        return 0
    vis[(x , y)] = True

    if(abs(x) + abs(y) >= n):
        return 1

    result = 1
    for dx , dy in dir:
        dx = int(dx)
        dy = int(dy)
        if abs(x + dx) + abs(y + dy) > abs(x) + abs(y):
            result += flood(x + dx , y + dy)
    return result

print(flood(0 , 0))
```

Ta xác định độ phức tạp của thuật toán qua các bước sau:
- Đếm phép toán cơ bản của bài toán: một lần loang của ô đen.
- Từ đó, mỗi bước số ô mới được loang là $4 * t$ nên ta có:$$f(t) = f(t - 1) + 4t$$
$$ \Leftrightarrow f(t) = 1 + 4 \cdot 1 + 4 \cdot 2 + ... + 4 \cdot(t - 1) + 4 \cdot t$$
$$\Leftrightarrow f(t) = 1 + 4 \cdot \frac{t \cdot (t + 1)}{2}$$
$$\Leftrightarrow f(t) = 1 + 2 \cdot t \cdot (t + 1)$$
- Kết luận, ta có độ phức tạp của thuật toán như trên

# Bài 2:

### a) Công thức truy hồi cho thuật toán đã cho:

$$T(n) = T(n - 2) + 2$$
Giải công thức trên, ta có:
$$
T(n) = 
\begin{cases}
n, & \text{n chẵn} \\
n+1, & \text{n lẻ}
\end{cases}
$$
### b) Phân tích tính tối ưu:

Ta thấy rằng thuật toán trên chưa hoàn toàn tối ưu tại trường hợp $n$ lẻ. Vì nếu lẻ ra $1$ chiếc bánh thì đầu bếp sẽ nướng lẻ. Điều này là không tối ưu và ta phải nhắm tới việc tối ưu không gian trên chiếc bếp nhỏ.


Có thể chứng mình được rằng với mọi $n > 2$ thì $T_{\text{optimize}}(n) = n$.

### c) Thuật toán tối ưu

Thuật toán tối ưu như sau:
- Tưởng tượng $n$ chiếc bánh như 1 vòng tròn. Tại mỗi thời điểm $i$ ta sẽ nướng chiếc bánh $i + 1$, nếu $i = n$ thì ta sẽ nướng bánh $n$ và bánh $1$.
- Cụ thể hơn:
	- Thời điểm $i = 1$, nướng bánh $(1 , 2)$
	- Thời điểm $i = 2$, nướng bánh $(2 , 3)$
	- Thời điểm $i = 3$, nướng bánh $(3 , 4)$
	- ...
	- Thời điểm $i = n$, nướng bánh $(n , 1)$
- Khi đó, ta thấy mọi bánh đều được nướng 2 mặt và chỉ tốn đúng $n$ thời gian để nướng đủ $2$ mặt cho $n$ chiếc bánh.

## Bài 3:

- Ta có thể phân tích như sau từ đoạn code:
$$T(n) = 
	\begin{cases}
	\Theta(1) & , n \le 1\\
	\sum_{i = 0}^{n - 1}(T(i) + T(n - 1 - i)) + \Theta(n) &, n \ge 2
	\end{cases}
$$

$$\Leftrightarrow T(n) = 
	\begin{cases}
	\Theta(1) & , n \le 1\\
	2 \cdot \sum_{i = 0}^{n - 1}T(i) + \Theta(n) &, n \ge 2
	\end{cases}$$
- Xét trường hợp $n \ge 2$:
$$T(n) = 2 \cdot \sum_{i = 0}^{n - 1}T(i) + \Theta(n)$$
- Đặt $S(n) = \sum_{k = 0}^n T(k)$
$$\Rightarrow T(n) = 2 \cdot S(n - 1) + \Theta(n)$$
$$\Rightarrow S(n) = S(n - 1) + T(n)$$
$$\Leftrightarrow S(n) = S(n - 1) + 2 \cdot S(n - 1) + \Theta(n)$$
$$\Leftrightarrow S(n) = 3 \cdot S(n - 1) + \Theta(n)$$
- Lấy bậc mũ chính:
$$\Rightarrow S(n) = \Theta(3^n)$$
- Vì $T(n) = S(n) - S(n - 1)$
$$\Rightarrow T(n) = \Theta(3^n)$$