#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

#define MAX_SIZE 36 // Giới hạn kích thước tối đa của ma trận hệ số

// a là ma trận mở rộng (kích thước n x n+1). 
double a[MAX_SIZE][MAX_SIZE + 1];
int n; // Số lượng phương trình (hoặc số ẩn)

void mtrx_in();
void gss();
int findPiv(int, int);
void rowSwp(int, int);
void mtrx_out();

int main()
{
    printf("enter the number of equations: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_SIZE)
    {
        printf("im not einstien🥀\n");
        return 36;
    }

    printf("(%d x %d):\n", n, n + 1);
    mtrx_in(); // Gọi hàm nhập ma trận
    gss();     // Gọi hàm xử lý khử Gauss (đưa về dạng tam giác trên)
    
    printf("\nresult:\n");
    mtrx_out(); // In kết quả ma trận sau khi biến đổi

    return 0;
}

// Hàm nhập dữ liệu cho ma trận mở rộng
void mtrx_in()
{
    for (int i = 0; i < n; i++)
    {
        printf("row %d: ", i + 1);
        for (int j = 0; j <= n; j++)
        {
            scanf("%lf", &a[i][j]); // Đọc từng phần tử của hàng i
        }
    }
}

// Hàm cốt lõi: Khử Gauss để đưa ma trận về dạng bậc thang (tam giác trên)
void gss()
{
    for (int i = 0; i < n; i++)
    {
        // 1. Tìm hàng có phần tử lớn nhất ở cột hiện tại (xoay trục - partial pivoting)
        // Mục đích: Tránh sai số làm tròn và lỗi chia cho số quá nhỏ (hoặc số 0).
        int pivotRow = findPiv(i, i);
        
        // 2. Nếu hàng có phần tử lớn nhất không phải là hàng hiện tại (i), thì đổi chỗ 2 hàng này.
        if (pivotRow != i)
        {
            rowSwp(i, pivotRow);
        }

        // 3. Nếu phần tử trên đường chéo chính (sau khi đổi) vẫn xấp xỉ 0 -> Bỏ qua, tránh lỗi chia cho 0.
        if (fabs(a[i][i]) < 1e-9)
        {
            continue;
        }

        // 4. Khử các phần tử nằm bên dưới đường chéo chính (biến chúng thành 0)
        for (int j = i + 1; j < n; j++)
        {
            // Tính hệ số khử
            double factor = a[j][i] / a[i][i]; 
            
            // Trừ hàng j cho (hàng i * hệ số khử) để phần tử a[j][i] thành 0
            for (int k = i; k <= n; k++)
            {
                a[j][k] -= factor * a[i][k];
            }
        }
    }
}

// Hàm tìm hàng có phần tử chốt (pivot) có giá trị tuyệt đối lớn nhất trong một cột
int findPiv(int col, int start)
{
    int maxRow = start; // Mặc định hàng đầu tiên chứa số lớn nhất
    for (int i = start + 1; i < n; i++)
    {
        // So sánh giá trị tuyệt đối, thằng nào to hơn thì cập nhật vị trí
        if (fabs(a[i][col]) > fabs(a[maxRow][col]))
        {
            maxRow = i;
        }
    }
    return maxRow; // Trả về chỉ số của hàng chứa phần tử to nhất
}

// Hàm hoán đổi vị trí toàn bộ phần tử của 2 hàng r1 và r2 cho nhau
void rowSwp(int r1, int r2)
{
    for (int j = 0; j <= n; j++)
    {
        double temp = a[r1][j];
        a[r1][j] = a[r2][j];
        a[r2][j] = temp;
    }
}

// Hàm in ma trận ra màn hình
void mtrx_out()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            // In mỗi số với định dạng: chiếm 10 khoảng trống, lấy 3 số sau dấu phẩy
            printf("%10.3f", a[i][j]); 
        }
        printf("\n");
    }
}
