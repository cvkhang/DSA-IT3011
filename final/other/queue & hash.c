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
// typedef struct {
//     char name[50];
//     int price;
// } Product;

// Product* create_product(const char* name, int price) {
//     Product* p = (Product*)malloc(sizeof(Product));
//     strcpy(p->name, name);
//     p->price = price;
//     return p;
// }

// void free_product(void* ptr) {
//     free(ptr);
// }

typedef int datatype;

typedef struct qnode{
  datatype data;
  struct qnode* next;
} qnode;

typedef struct queue{
  qnode* first;
  qnode* last;
} queue;

queue* makeQueue(){
  queue* a = (queue*) malloc(sizeof(queue));
  a->first = NULL;
  a->last = NULL;
  return a;
}

qnode* makeQNode(datatype x){
  qnode* a = (qnode*) malloc(sizeof(qnode));
  a->data = x;
  a->next = NULL;
  return a;
}

qnode* enqueue(queue* a, datatype x){
  	if(a==NULL) return NULL;
	if(a->first==NULL && a->last!=NULL) return NULL;
	if(a->first!=NULL && a->last==NULL) return NULL;
	
	qnode *b = makeQNode(x);
	if(a->first==NULL && a->last==NULL){
		a->first = b;
		a->last = b;
		return b;
	}

	a->last->next = b;
	a->last = b;

	return b;
}

int dequeue(queue* a, datatype* out){
    if(a == NULL || a->first == NULL) return 0;

    qnode* tofree = a->first;
    *out = tofree->data;

    if(a->first == a->last){
        a->first = NULL;
        a->last = NULL;
    } else {
        a->first = a->first->next;
    }

    free(tofree);
    return 1;
}

int isQueueEmpty(queue* a){
	if(a==NULL) return 1;
	if(a->first==NULL && a->last==NULL) return 1;
	return 0;
}

datatype peek(queue* a){
    if(a == NULL || a->first == NULL){
        printf("Queue is empty\n");
        exit(1);
    }

    return a->first->data;
}

void printQueue(queue* a){
    if(a == NULL || a->first == NULL){
        printf("Queue is empty\n");
        return;
    }

    qnode* p = a->first;
    while(p != NULL){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int countQueue(queue* a){
    if(a == NULL) return 0;

    int count = 0;
    qnode* p = a->first;

    while(p != NULL){
        count++;
        p = p->next;
    }

    return count;
}

void clearQueue(queue* a){
    if(a == NULL) return;

    qnode* p = a->first;

    while(p != NULL){
        qnode* temp = p;
        p = p->next;
        free(temp);
    }

    a->first = NULL;
    a->last = NULL;
}


int main() {
    
    freopen("stress_test_input.txt", "r", stdin);
    freopen("my_output.txt", "w", stdout);
	
    // Khởi tạo với kích thước nhỏ
    HashTable* ht = create_table(2); 
	queue* waiting = makeQueue();

    // Thêm dữ liệu
    // insert(ht, "SP01", create_product("Laptop Dell", 1500));
    // insert(ht, "SP02", create_product("Macbook Pro", 2000));
    // insert(ht, "SP03", create_product("Chuot Logitech", 50));
    

	int Q;
	scanf("%d\n", &Q);

	for(int i = 0; i < Q; i++){
		//read input line
		char* line = (char*) calloc(50,sizeof(char));
		fgets(line,50,stdin);
		
		// remove '\n'
		line[strcspn(line, "\n")] = '\0';

		//command's space split
		char* cmd = strtok(line," ");

		// algorithm
		if(strcmp(cmd, "add") == 0){
			char* id = strtok(NULL," ");
			if(search(ht, id) != NULL){
				free(line);
				continue;
			}
			else{
				insert(ht, id, enqueue(waiting, atoi(id)));
			}
		}
		else if(strcmp(cmd, "next") == 0){
			if(isQueueEmpty(waiting)){
				printf("EMPTY\n");
			}
			else{
				int* id = (int*) malloc(sizeof(int));
				dequeue(waiting, id);
				printf("%d\n", *id);

				char id_str[20]; 
				sprintf(id_str, "%d", *id); 
				remove_key(ht, id_str, NULL);
				free(id);
			}
		}
		else if(strcmp(cmd, "check") == 0){
			char* id = strtok(NULL," ");
			if(search(ht, id) != NULL){
				printf("YES\n");
			}
			else printf("NO\n");
		}

		free(line);
	}

    return 0;
}
