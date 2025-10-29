## Solution

### Hướng tiếp cận & Thuật toán

- Chỉ số phức tạp công việc của mỗi nhân viên $u$, với $deg(u)$ là số cấp dưới trực tiếp của $u$:
$$
C_u = w_u \ + \ deg(u)
$$

- Nếu ta sa thải $x$ với cha là $p$ thì, chỉ có duy nhất chỉ số phức tạp của $p$ bị thay đổi, $C_p$ tăng lên một lượng bằng:
$$
    \Delta_p(x) = (w_x + deg(x) - 1)
$$

Vì vậy , nếu ta đang đứng ở một nút $u$, khi sa thải một cấp dưới $v$ của $u$ thì $u$ phải gánh chịu một chi phí là: $cost(v) = w_v + deg(v) - 1$

Gọi khả năng gánh chịu chỉ số phức tạp của một nhân viên $u$ là $S_u = m - (w_u + deg(u))$. Ta chỉ được sa thải một tập con các con trực tiếp hiện tại của $u$ sao cho tổng $cost \le S_u$.

**Chi tiết thuật toán**

Ta duyệt DFS theo thứ tự PostOrder. Với mỗi nút $u$:

- Gọi đệ quy xử lý xong mọi cây con của $u$.
- Tạo một tập ứng viên là toàn bộ con $v$ trực tiếp hiện tại của $u$ và chi phí mà $u$ phải gánh chịu khi mà sa thải $v$, ta dùng CTDL priority_queue ưu tiên theo chi phí tăng dần (min-heap).
- Trong khi min-heap không rỗng thì ta xem xét nút $v$ có chi phí sa thải nhỏ nhất, nếu $cost_v \le S_u$ thì ta có thể sa thải nút $v$ này và cập nhật $S_u$ và $w_u$.
- Khi phần tử có chi phí sa thải thấp nhất còn lại trong heap mà $u$ không thể sa thải được do $cost \gt S_u$ thì ta dừng việc sa thải nhân viên dưới quyền $u$.

Lưu ý: Ở một nút $u$, khi ta sa thải một nhân viên trực tiếp $v$ thì $u$ không thể sa thải bất kì một nhân viên nào khác ở dưới quyền của $v$ bởi vì theo tính chất tham lam của thuật toán, ta ưu tiên sa thải hết những nhân viên theo thứ tự tăng dần về chi phí cho đến khi không thể sa thải được nữa. Gọi $k$ là nhân viên có chi phí sa thải thấp nhất của $v$, nhưng khi $v$ không thể sa thải được $k$ thì tức là: $cost_k + w_v \gt m$. Suy ra, khi $u$ sa thải $v$ và sa thải luôn $k$ thì không được vì $cost_k + cost_v + w_u \gt m$.

### Tính đúng đắn của thuật toán tham lam

1. Khi xét một nút u, ta có thể thấy được thứ tự loại bỏ các nút không quan trọng.
2. Với một tập các ứng viên của $u$ có chi phí sa thải cố định và một khả năng có thể carry được chỉ số phức tạp $S_u$ thì ta thực hiện chiến lược luôn chọn nhân viên có chi phí sa thải thấp nhất để sa thải đến khi không thể sa thải được nữa. 
3. Ta duyệt cây theo thứ tự PostOrder: mọi cây con của $u$ đã được tối ưu cục bộ (theo mục 2), nên các tham số $w_v$ và $deg(v)$ dùng để tính $cost_v$ đã là ổn định.
    Áp dụng mục 1 và 2 tại $u$, ta nhận được nghiệm tối ưu trong phạm vi ảnh hưởng của $u$ khi mọi thay đổi hướng đến $C_u$.
    Tiếp tục đi lên cha $p_u$: chi phí $cost_u$ mà $p_u$ nhìn thấy là đúng nhất có thể vì cây con $u$ đã được tối ưu và áp dụng quy tắc ở mục 1 và 2 cho $p_u$.
    Quy nạp dần đến gốc ta thu được nghiệm tối ưu toàn cục.
