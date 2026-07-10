#include <stdio.h>
#include <string.h>

#define MAX_Q 200005
#define HASH_SIZE 500009
#define EMPTY 0
#define DELETED -1


int queue[MAX_Q];
int head = 0, tail = 0;


int hash_table[HASH_SIZE];

// Hàm băm cho số nguyên
int get_hash(int x) {
    return x % HASH_SIZE;
}

// Kiểm tra xem ID có trong Hash Table không
int contains(int x) {
    int h = get_hash(x);
    while (hash_table[h] != EMPTY) {
        if (hash_table[h] == x) return 1; 
        h = (h + 1) % HASH_SIZE;
    }
    return 0;
}

// Thêm ID vào Hash Table
void insert_hash(int x) {
    int h = get_hash(x);
    int first_deleted = -1;
    
    while (hash_table[h] != EMPTY) {
        if (hash_table[h] == x) return; // Đã tồn tại
        
        // Ghi nhớ vị trí DELETED đầu tiên để có thể tái sử dụng
        if (hash_table[h] == DELETED && first_deleted == -1) {
            first_deleted = h;
        }
        h = (h + 1) % HASH_SIZE;
    }
    
    // Ưu tiên chèn vào ô đã xóa nếu có, nếu không thì chèn vào ô trống
    if (first_deleted != -1) {
        hash_table[first_deleted] = x;
    } else {
        hash_table[h] = x;
    }
}

// Xóa ID khỏi Hash Table
void erase_hash(int x) {
    int h = get_hash(x);
    while (hash_table[h] != EMPTY) {
        if (hash_table[h] == x) {
            hash_table[h] = DELETED; // Đánh dấu là "Bia mộ" (Tombstone)
            return;
        }
        h = (h + 1) % HASH_SIZE;
    }
}

// ==========================================
// CHƯƠNG TRÌNH CHÍNH
// ==========================================
int main() {
    // Tối ưu I/O (Nếu dùng C++)
    // ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int q;
    if (scanf("%d", &q) != 1) return 0;

    char cmd[10];
    int id;

    for (int i = 0; i < q; i++) {
        scanf("%s", cmd);

        // Chỉ cần check chữ cái đầu tiên để tăng tốc độ tối đa
        if (cmd[0] == 'a') { // lệnh "add"
            scanf("%d", &id);
            if (!contains(id)) {
                queue[tail++] = id; // Đẩy vào cuối hàng đợi
                insert_hash(id);    // Đánh dấu vào Hash Table
            }
        } 
        else if (cmd[0] == 'n') { // lệnh "next"
            if (head == tail) {
                printf("EMPTY\n");
            } else {
                int val = queue[head++]; // Lấy phần tử đầu ra
                erase_hash(val);         // Xóa khỏi Hash Table
                printf("%d\n", val);
            }
        } 
        else if (cmd[0] == 'c') { // lệnh "check"
            scanf("%d", &id);
            if (contains(id)) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        }
    }
    
    return 0;
}
