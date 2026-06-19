#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 16        // Kích thước mặc định ban đầu
#define LOAD_FACTOR_LIMIT 0.75 // Giới hạn hệ số tải (75%)

typedef struct Node {
    char* key;
    void* value;
    struct Node* next;
} Node;

typedef struct HashTable {
    int size;      // Kích thước mảng hiện tại
    int count;     // Số lượng phần tử đang lưu trữ
    Node** table;  
} HashTable;

// băm djb2
unsigned long hash_string(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

HashTable* create_table(int size) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    ht->size = size > 0 ? size : INITIAL_SIZE;
    ht->count = 0;
    ht->table = (Node**)calloc(ht->size, sizeof(Node*));
    return ht;
}

void resize_table(HashTable* ht) {
    int new_size = ht->size * 2;
    Node** new_table = (Node**)calloc(new_size, sizeof(Node*));

    // Di chuyển các node cũ sang mảng mới (Rehashing)
    for (int i = 0; i < ht->size; i++) {
        Node* entry = ht->table[i];
        while (entry != NULL) {
            Node* next = entry->next; // Lưu lại con trỏ next
            
            // Tính toán vị trí mới
            unsigned long new_slot = hash_string(entry->key) % new_size;
            
            // Chèn node vào mảng mới
            entry->next = new_table[new_slot];
            new_table[new_slot] = entry;
            
            entry = next;
        }
    }

    free(ht->table); // Giải phóng mảng cũ
    ht->table = new_table;
    ht->size = new_size;
}

void insert(HashTable* ht, const char* key, void* value) {
    // Kiểm tra và tự động mở rộng nếu vượt quá Load Factor
    if ((float)ht->count / ht->size >= LOAD_FACTOR_LIMIT) {
        resize_table(ht);
    }

    unsigned long slot = hash_string(key) % ht->size;
    Node* entry = ht->table[slot];

    // Nếu key đã tồn tại -> Cập nhật value
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value; 
            return;
        }
        entry = entry->next;
    }

    // Nếu key chưa có -> Tạo node mới
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->key = strdup(key);
    new_node->value = value;
    new_node->next = ht->table[slot];
    
    ht->table[slot] = new_node;
    ht->count++; // Tăng số lượng phần tử
}

void* search(HashTable* ht, const char* key) {
    unsigned long slot = hash_string(key) % ht->size;
    Node* entry = ht->table[slot];

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}

int remove_key(HashTable* ht, const char* key, void (*free_value)(void*)) {
    unsigned long slot = hash_string(key) % ht->size;
    Node* entry = ht->table[slot];
    Node* prev = NULL;

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            if (prev == NULL) { // Xóa node ở đầu danh sách
                ht->table[slot] = entry->next;
            } else {            // Xóa node ở giữa/cuối danh sách
                prev->next = entry->next;
            }

            // Dọn dẹp bộ nhớ của node này
            free(entry->key);
            if (free_value != NULL && entry->value != NULL) {
                free_value(entry->value);
            }
            free(entry);
            ht->count--;
            return 1; // Xóa thành công
        }
        prev = entry;
        entry = entry->next;
    }
    return 0; // Không tìm thấy
}

void free_table(HashTable* ht, void (*free_value)(void*)) {
    for (int i = 0; i < ht->size; i++) {
        Node* entry = ht->table[i];
        while (entry != NULL) {
            Node* temp = entry;
            entry = entry->next;
            
            free(temp->key);
            if (free_value != NULL && temp->value != NULL) {
                free_value(temp->value);
            }
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}

// Định nghĩa dữ liệu cần lưu
typedef struct {
    char name[50];
    int price;
} Product;

Product* create_product(const char* name, int price) {
    Product* p = (Product*)malloc(sizeof(Product));
    strcpy(p->name, name);
    p->price = price;
    return p;
}

void free_product(void* ptr) {
    free(ptr);
}

int main() {
    // Khởi tạo với kích thước nhỏ
    HashTable* ht = create_table(2); 

    // Thêm dữ liệu
    insert(ht, "SP01", create_product("Laptop Dell", 1500));
    insert(ht, "SP02", create_product("Macbook Pro", 2000));
    insert(ht, "SP03", create_product("Chuot Logitech", 50));
    
    printf("So luong phan tu: %d, Kich thuoc mang thuc te: %d\n", ht->count, ht->size);

    // Tìm kiếm
    Product* p = (Product*)search(ht, "SP02");
    if (p != NULL) {
        printf("\nTim thay SP02: %s - $%d\n", p->name, p->price);
    }

    // Xóa
    printf("\nDang xoa SP01...\n");
    remove_key(ht, "SP01", free_product);
    
    if (search(ht, "SP01") == NULL) {
        printf("Da xoa thanh cong SP01!\n");
    }

    free_table(ht, free_product);

    return 0;
}
