#include <stdio.h>
#include <stdlib.h>

int distance[100001];
int indx[100001];
int prio_queue[100001];
int n = 0;

typedef struct node {
  int vertex;
  struct node* next;
  int weight;
}node;

typedef struct Graph {
    int numVertices;
    node** adjLists;
} graph;

// Create a node
node* createNode(int v, int weight) {
  node* newNode = malloc(sizeof(node));
  newNode->vertex = v;
  newNode->next = NULL;
  newNode->weight = weight;
  return newNode;
}

// Create a graph
graph* createAGraph(int vertices) {
  graph* g = (graph*) malloc(sizeof(graph));
  g->numVertices = vertices;
  g->adjLists = (node**) malloc((vertices+1) * sizeof(node*));

  int i;
  for (i = 1; i <= vertices; i++){
    g->adjLists[i] = NULL;
  }

  return g;
}

// Add edge
void addEdge(graph* g, int s, int d, int weight) {
  // Add edge from s to d
  node* newNode = createNode(d,weight);
  newNode->next = g->adjLists[s];
  g->adjLists[s] = newNode;

}

void swap(int i,int j){
  int temp = prio_queue[i];
  prio_queue[i] = prio_queue[j];
  prio_queue[j] = temp;

  indx[prio_queue[i]] = i;
  indx[prio_queue[j]] = j;
}

void min_heapify(int i){
  int left = i * 2 + 1;
  int right = i * 2 + 2;
  int min = i;

  if( left < n && distance[prio_queue[left]] < distance[prio_queue[i]] ){
    min = left;
  }
  if( right < n && distance[prio_queue[right]] < distance[prio_queue[i]] ){
    min = right;
  }

  if(min != i){
    swap(i,min);
    min_heapify(min);
  }
}

void upHeap(int i){
  while(i > 0){
    int dad = (i-1)/2;
    if( distance[prio_queue[i]] < distance[prio_queue[dad]] ){
      swap(dad,i);
    }
    else{
      break;
    }
    i = dad;
  }
}

int deleteMin(){
  int current_min_vertex = prio_queue[0];
  swap(0, n - 1);
  n--;
  min_heapify(0);
  return current_min_vertex;
}

int inHeap(int v){
  if(indx[v] >= 0){
    return 1;
  }
  return 0;
}

void update_Distance(int v, int new_distance){
  if(distance[v] > new_distance){
    distance[v] = new_distance;
    upHeap(indx[v]);
  }
}

void insert_queue(int v, int v_distance){
  distance[v] = v_distance;
  prio_queue[n] = v;
  indx[v] = n;
  upHeap(n);
  n++;
}

void init(int s, graph* g){
  n = 0;
  for(int i = 1; i <= g->numVertices; i++){
    //-2 -> chua vao heap
    //-1 -> da vao heap, da duoc lay ra
    indx[i] = -2;
    distance[i] = 1e9;
  }

  distance[s] = 0;
  indx[s] = -1;
  node* s_adj = g->adjLists[s];
  while(s_adj != NULL){
    int v = s_adj->vertex;
    int w = s_adj->weight;
    insert_queue(v,w);
    s_adj = s_adj->next;
  }
}


int main(){

  int v,e;
  scanf("%d %d", &v,&e);
  getchar();

  int s,d,w;
  graph* g = createAGraph(v);
  for(int i = 0; i < e; i++){
    scanf("%d %d %d",&s,&d,&w);
    getchar();
    addEdge(g,s,d,w);
  }

  scanf("%d %d", &s, &d);

  init(s,g);
  while(n > 0 && indx[d] != -1){
    int u = deleteMin();
    indx[u] = -1;
    node* u_adj = g->adjLists[u];
    while(u_adj != NULL){
      v = u_adj->vertex;
      w = u_adj->weight;
      //da duoc lay ra
      if(indx[v] == -1){
        u_adj = u_adj->next;
        continue;
      }
      //dang o trong queue
      if(indx[v] >= 0){
        if(distance[v] > distance[u] + w){
          update_Distance(v,distance[u] + w);
        }
      }
      //chua vao queue
      else{
        insert_queue(v,w+distance[u]);
      }
      u_adj = u_adj->next;
    }
  }

  if(indx[d] == -2){
    printf("-1");
  }
  else{
    printf("%d", distance[d]);
  }

  return 0;
}
