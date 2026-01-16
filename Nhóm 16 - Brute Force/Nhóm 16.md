```c++
pair<float,float> getNextPoint(float x, float y, int lastBossID) {
    static bool found_zone = 0;
    static pair<int,int> zone_center;
    static int ang_idx = 0, rad_idx = 1;
    static const float STEP_R = 100;
    static const float STEP_ANG = M_PI / 4;

    if (lastBossID == 36) {
        found_zone = 1;
        zone_center = {(int)x,(int)y};
    }
    if (found_zone) {
        float r = 100 + rand() % 300;
        float t = (rand() % 360) * M_PI / 180.0;
        return {zone_center.first + r * cos(t),
                zone_center.second + r * sin(t)};
    }
    float r = rad_idx * STEP_R;
    float t = ang_idx * STEP_ANG;
    float nx = r * cos(t);
    float ny = r * sin(t);
    ang_idx++;
    if (ang_idx * STEP_ANG >= 2 * M_PI) {
        ang_idx = 0;
        rad_idx++;
    }
    return {nx, ny};
}

```

Thuật toán được mô tả như sau:
- Nhân vật bắt đầu quá trình quét bằng cách di chuyển quanh vị trí này theo một **đường tròn nhỏ** có bán kính cố định (ví dụ 100 đơn vị).
- Sau khi quét hết một vòng tròn (tức là đi đủ 360 độ), nhân vật **tăng bán kính thêm 100 đơn vị** và tiếp tục di chuyển quanh vòng tròn mới lớn hơn.  Cách này giúp nhân vật dần dần bao phủ toàn bộ khu vực xung quanh theo các vòng tròn mở rộng.
- Trong quá trình di chuyển, nếu nhân vật hạ gục được một boss có **ID = 36**, vị trí đó được ghi nhận là **trung tâm của khu vực đặc biệt**.
- Khi đã tìm thấy khu vực đặc biệt, nhân vật **ngừng mở rộng tìm kiếm** và bắt đầu **di chuyển ngẫu nhiên trong phạm vi khoảng 300–400 đơn vị** quanh tâm khu vực này để tiêu diệt nhiều boss nhất có thể.
- Nếu trong quá trình khai thác không còn boss, nhân vật có thể quay lại bước quét vòng tròn để tiếp tục tìm thêm khu vực đặc biệt khác.
