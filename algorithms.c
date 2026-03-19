/**
 * Master Computer Programming - ANSI C Implementations
 * Complete version with Neural Network
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

/* Simple square root implementation for integers/doubles */
double simple_sqrt(double x) {
    if (x <= 0) return 0;
    
    double guess = x / 2.0;
    double prev;
    
    /* Babylonian method (Newton-Raphson) */
    do {
        prev = guess;
        guess = (guess + x / guess) / 2.0;
    } while ((prev - guess) > 0.00001 || (guess - prev) > 0.00001);
    
    return guess;
}

/* Simple exponential implementation using Taylor series */
double simple_exp(double x) {
    double result = 1.0;  /* Start with term for n=0 */
    double term = 1.0;
    int n;
    
    /* e^x = 1 + x + x^2/2! + x^3/3! + ... */
    for (n = 1; n < 20; n++) {
        term *= x / n;
        result += term;
    }
    
    return result;
}

/* ============================================================================
   ARRAY OPERATIONS
   ============================================================================ */

int* array_create(int size, int initial_value) {
    int* arr = (int*)malloc(size * sizeof(int));
    if (arr != NULL) {
        int i;
        for (i = 0; i < size; i++) {
            arr[i] = initial_value;
        }
    }
    return arr;
}

int* array_insert_end(int* arr, int* size, int value) {
    (*size)++;
    arr = (int*)realloc(arr, (*size) * sizeof(int));
    if (arr != NULL) {
        arr[(*size) - 1] = value;
    }
    return arr;
}

int* array_insert_at(int* arr, int* size, int index, int value) {
    int i;
    (*size)++;
    arr = (int*)realloc(arr, (*size) * sizeof(int));
    if (arr != NULL) {
        for (i = (*size) - 1; i > index; i--) {
            arr[i] = arr[i - 1];
        }
        arr[index] = value;
    }
    return arr;
}

int* array_delete_at(int* arr, int* size, int index) {
    int i;
    if (index < 0 || index >= *size) return arr;
    
    for (i = index; i < (*size) - 1; i++) {
        arr[i] = arr[i + 1];
    }
    (*size)--;
    arr = (int*)realloc(arr, (*size) * sizeof(int));
    return arr;
}

void array_traverse(int* arr, int size, void (*callback)(int)) {
    int i;
    for (i = 0; i < size; i++) {
        callback(arr[i]);
    }
}

/* ============================================================================
   LINKED LIST
   ============================================================================ */

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} LinkedList;

void linkedlist_init(LinkedList* list) {
    list->head = NULL;
}

Node* create_node(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = value;
        newNode->next = NULL;
    }
    return newNode;
}

void linkedlist_insert_at_head(LinkedList* list, int value) {
    Node* newNode = create_node(value);
    if (newNode != NULL) {
        newNode->next = list->head;
        list->head = newNode;
    }
}

void linkedlist_insert_at_tail(LinkedList* list, int value) {
    Node* newNode = create_node(value);
    Node* current;
    
    if (newNode == NULL) return;
    
    if (list->head == NULL) {
        list->head = newNode;
        return;
    }
    
    current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

void linkedlist_delete_node(LinkedList* list, int value) {
    Node* current;
    Node* temp;
    
    if (list->head == NULL) return;
    
    if (list->head->data == value) {
        temp = list->head;
        list->head = list->head->next;
        free(temp);
        return;
    }
    
    current = list->head;
    while (current->next != NULL && current->next->data != value) {
        current = current->next;
    }
    
    if (current->next != NULL) {
        temp = current->next;
        current->next = current->next->next;
        free(temp);
    }
}

void linkedlist_traverse(LinkedList* list, void (*callback)(int)) {
    Node* current = list->head;
    while (current != NULL) {
        callback(current->data);
        current = current->next;
    }
}

void linkedlist_free(LinkedList* list) {
    Node* current = list->head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
}

/* ============================================================================
   STACK
   ============================================================================ */

typedef struct {
    int* elements;
    int top;
    int capacity;
} Stack;

Stack* stack_create(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack != NULL) {
        stack->elements = (int*)malloc(capacity * sizeof(int));
        stack->top = -1;
        stack->capacity = capacity;
    }
    return stack;
}

void stack_push(Stack* stack, int value) {
    if (stack->top < stack->capacity - 1) {
        stack->elements[++stack->top] = value;
    }
}

int stack_pop(Stack* stack) {
    if (stack->top >= 0) {
        return stack->elements[stack->top--];
    }
    fprintf(stderr, "Stack Underflow\n");
    return -1;
}

int stack_peek(Stack* stack) {
    if (stack->top >= 0) {
        return stack->elements[stack->top];
    }
    fprintf(stderr, "Stack is empty\n");
    return -1;
}

int stack_is_empty(Stack* stack) {
    return stack->top == -1;
}

void stack_free(Stack* stack) {
    if (stack != NULL) {
        free(stack->elements);
        free(stack);
    }
}

/* ============================================================================
   QUEUE
   ============================================================================ */

typedef struct {
    int* elements;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

Queue* queue_create(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue != NULL) {
        queue->elements = (int*)malloc(capacity * sizeof(int));
        queue->front = 0;
        queue->rear = -1;
        queue->size = 0;
        queue->capacity = capacity;
    }
    return queue;
}

void queue_enqueue(Queue* queue, int value) {
    if (queue->size < queue->capacity) {
        queue->rear = (queue->rear + 1) % queue->capacity;
        queue->elements[queue->rear] = value;
        queue->size++;
    }
}

int queue_dequeue(Queue* queue) {
    if (queue->size > 0) {
        int value = queue->elements[queue->front];
        queue->front = (queue->front + 1) % queue->capacity;
        queue->size--;
        return value;
    }
    fprintf(stderr, "Queue Underflow\n");
    return -1;
}

int queue_front(Queue* queue) {
    if (queue->size > 0) {
        return queue->elements[queue->front];
    }
    fprintf(stderr, "Queue is empty\n");
    return -1;
}

int queue_is_empty(Queue* queue) {
    return queue->size == 0;
}

void queue_free(Queue* queue) {
    if (queue != NULL) {
        free(queue->elements);
        free(queue);
    }
}

/* ============================================================================
   HASH TABLE (with chaining)
   ============================================================================ */

typedef struct HashNode {
    int key;
    int value;
    struct HashNode* next;
} HashNode;

typedef struct {
    HashNode** buckets;
    int size;
} HashTable;

HashTable* hashtable_create(int size) {
    int i;
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if (ht != NULL) {
        ht->size = size;
        ht->buckets = (HashNode**)malloc(size * sizeof(HashNode*));
        for (i = 0; i < size; i++) {
            ht->buckets[i] = NULL;
        }
    }
    return ht;
}

int hash_function(HashTable* ht, int key) {
    return abs(key) % ht->size;
}

void hashtable_insert(HashTable* ht, int key, int value) {
    int index = hash_function(ht, key);
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    
    if (newNode != NULL) {
        newNode->key = key;
        newNode->value = value;
        newNode->next = ht->buckets[index];
        ht->buckets[index] = newNode;
    }
}

int hashtable_search(HashTable* ht, int key) {
    int index = hash_function(ht, key);
    HashNode* current = ht->buckets[index];
    
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    fprintf(stderr, "Key not found\n");
    return -1;
}

void hashtable_delete(HashTable* ht, int key) {
    int index = hash_function(ht, key);
    HashNode* current = ht->buckets[index];
    HashNode* prev = NULL;
    
    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) {
                ht->buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void hashtable_free(HashTable* ht) {
    int i;
    for (i = 0; i < ht->size; i++) {
        HashNode* current = ht->buckets[i];
        while (current != NULL) {
            HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht->buckets);
    free(ht);
}

/* ============================================================================
   BINARY SEARCH TREE
   ============================================================================ */

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* tree_create_node(int value) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node != NULL) {
        node->data = value;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

TreeNode* tree_insert(TreeNode* root, int value) {
    if (root == NULL) {
        return tree_create_node(value);
    }
    if (value < root->data) {
        root->left = tree_insert(root->left, value);
    } else {
        root->right = tree_insert(root->right, value);
    }
    return root;
}

int tree_search(TreeNode* root, int value) {
    if (root == NULL) return FALSE;
    if (value == root->data) return TRUE;
    if (value < root->data) {
        return tree_search(root->left, value);
    } else {
        return tree_search(root->right, value);
    }
}

void tree_inorder(TreeNode* root, void (*callback)(int)) {
    if (root != NULL) {
        tree_inorder(root->left, callback);
        callback(root->data);
        tree_inorder(root->right, callback);
    }
}

void tree_free(TreeNode* root) {
    if (root != NULL) {
        tree_free(root->left);
        tree_free(root->right);
        free(root);
    }
}

/* ============================================================================
   GRAPH (Adjacency Matrix)
   ============================================================================ */

typedef struct {
    int** matrix;
    int num_vertices;
} Graph;

Graph* graph_create(int num_vertices) {
    int i, j;
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (graph != NULL) {
        graph->num_vertices = num_vertices;
        graph->matrix = (int**)malloc(num_vertices * sizeof(int*));
        for (i = 0; i < num_vertices; i++) {
            graph->matrix[i] = (int*)calloc(num_vertices, sizeof(int));
        }
    }
    return graph;
}

void graph_add_edge(Graph* graph, int u, int v, int directed) {
    if (u >= 0 && u < graph->num_vertices && v >= 0 && v < graph->num_vertices) {
        graph->matrix[u][v] = 1;
        if (!directed) {
            graph->matrix[v][u] = 1;
        }
    }
}

void graph_display(Graph* graph) {
    int i, j;
    for (i = 0; i < graph->num_vertices; i++) {
        printf("%d -> ", i);
        for (j = 0; j < graph->num_vertices; j++) {
            if (graph->matrix[i][j]) {
                printf("%d ", j);
            }
        }
        printf("\n");
    }
}

void graph_free(Graph* graph) {
    int i;
    for (i = 0; i < graph->num_vertices; i++) {
        free(graph->matrix[i]);
    }
    free(graph->matrix);
    free(graph);
}

/* ============================================================================
   HEAP (Min-Heap)
   ============================================================================ */

typedef struct {
    int* heap;
    int size;
    int capacity;
} MinHeap;

MinHeap* minheap_create(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (heap != NULL) {
        heap->heap = (int*)malloc(capacity * sizeof(int));
        heap->size = 0;
        heap->capacity = capacity;
    }
    return heap;
}

int minheap_parent(int i) { return (i - 1) / 2; }
int minheap_left(int i) { return 2 * i + 1; }
int minheap_right(int i) { return 2 * i + 2; }

void minheap_insert(MinHeap* heap, int value) {
    int current;
    int temp;
    
    if (heap->size >= heap->capacity) return;
    
    heap->heap[heap->size] = value;
    current = heap->size;
    heap->size++;
    
    while (current > 0 && heap->heap[minheap_parent(current)] > heap->heap[current]) {
        temp = heap->heap[minheap_parent(current)];
        heap->heap[minheap_parent(current)] = heap->heap[current];
        heap->heap[current] = temp;
        current = minheap_parent(current);
    }
}

void minheap_heapify(MinHeap* heap, int i) {
    int smallest = i;
    int left = minheap_left(i);
    int right = minheap_right(i);
    int temp;
    
    if (left < heap->size && heap->heap[left] < heap->heap[smallest]) {
        smallest = left;
    }
    if (right < heap->size && heap->heap[right] < heap->heap[smallest]) {
        smallest = right;
    }
    if (smallest != i) {
        temp = heap->heap[i];
        heap->heap[i] = heap->heap[smallest];
        heap->heap[smallest] = temp;
        minheap_heapify(heap, smallest);
    }
}

int minheap_extract_min(MinHeap* heap) {
    int min_val;
    
    if (heap->size == 0) {
        fprintf(stderr, "Heap is empty\n");
        return -1;
    }
    
    min_val = heap->heap[0];
    heap->heap[0] = heap->heap[heap->size - 1];
    heap->size--;
    minheap_heapify(heap, 0);
    
    return min_val;
}

void minheap_free(MinHeap* heap) {
    if (heap != NULL) {
        free(heap->heap);
        free(heap);
    }
}

/* ============================================================================
   TRIE
   ============================================================================ */

typedef struct TrieNode {
    struct TrieNode* children[26];
    int is_end_of_word;
} TrieNode;

TrieNode* trie_create_node(void) {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    int i;
    if (node != NULL) {
        for (i = 0; i < 26; i++) {
            node->children[i] = NULL;
        }
        node->is_end_of_word = FALSE;
    }
    return node;
}

void trie_insert(TrieNode* root, const char* word) {
    TrieNode* node = root;
    int index;
    while (*word) {
        index = *word - 'a';
        if (node->children[index] == NULL) {
            node->children[index] = trie_create_node();
        }
        node = node->children[index];
        word++;
    }
    node->is_end_of_word = TRUE;
}

int trie_search(TrieNode* root, const char* word) {
    TrieNode* node = root;
    int index;
    while (*word) {
        index = *word - 'a';
        if (node->children[index] == NULL) {
            return FALSE;
        }
        node = node->children[index];
        word++;
    }
    return node->is_end_of_word;
}

int trie_starts_with(TrieNode* root, const char* prefix) {
    TrieNode* node = root;
    int index;
    while (*prefix) {
        index = *prefix - 'a';
        if (node->children[index] == NULL) {
            return FALSE;
        }
        node = node->children[index];
        prefix++;
    }
    return TRUE;
}

void trie_free(TrieNode* root) {
    int i;
    if (root != NULL) {
        for (i = 0; i < 26; i++) {
            if (root->children[i] != NULL) {
                trie_free(root->children[i]);
            }
        }
        free(root);
    }
}

/* ============================================================================
   SET
   ============================================================================ */

typedef struct {
    int* elements;
    int size;
    int capacity;
} MySet;

MySet* set_create(int capacity) {
    MySet* set = (MySet*)malloc(sizeof(MySet));
    if (set != NULL) {
        set->elements = (int*)malloc(capacity * sizeof(int));
        set->size = 0;
        set->capacity = capacity;
    }
    return set;
}

int set_contains(MySet* set, int value) {
    int i;
    for (i = 0; i < set->size; i++) {
        if (set->elements[i] == value) return TRUE;
    }
    return FALSE;
}

void set_add(MySet* set, int value) {
    if (!set_contains(set, value) && set->size < set->capacity) {
        set->elements[set->size++] = value;
    }
}

void set_remove(MySet* set, int value) {
    int i, j;
    for (i = 0; i < set->size; i++) {
        if (set->elements[i] == value) {
            for (j = i; j < set->size - 1; j++) {
                set->elements[j] = set->elements[j + 1];
            }
            set->size--;
            return;
        }
    }
}

MySet* set_union(MySet* s1, MySet* s2) {
    int i;
    MySet* result = set_create(s1->size + s2->size);
    if (result != NULL) {
        for (i = 0; i < s1->size; i++) {
            set_add(result, s1->elements[i]);
        }
        for (i = 0; i < s2->size; i++) {
            set_add(result, s2->elements[i]);
        }
    }
    return result;
}

MySet* set_intersection(MySet* s1, MySet* s2) {
    int i;
    int min_capacity = s1->size < s2->size ? s1->size : s2->size;
    MySet* result = set_create(min_capacity);
    if (result != NULL) {
        for (i = 0; i < s1->size; i++) {
            if (set_contains(s2, s1->elements[i])) {
                set_add(result, s1->elements[i]);
            }
        }
    }
    return result;
}

MySet* set_difference(MySet* s1, MySet* s2) {
    int i;
    MySet* result = set_create(s1->size);
    if (result != NULL) {
        for (i = 0; i < s1->size; i++) {
            if (!set_contains(s2, s1->elements[i])) {
                set_add(result, s1->elements[i]);
            }
        }
    }
    return result;
}

void set_free(MySet* set) {
    if (set != NULL) {
        free(set->elements);
        free(set);
    }
}

/* ============================================================================
   SORTING ALGORITHMS
   ============================================================================ */

void bubble_sort_descending(int* data, int n) {
    int i, j, temp;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (data[j] < data[j + 1]) {
                temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    int j, temp;
    
    for (j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quick_sort_recursive(int* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort_recursive(arr, low, pi - 1);
        quick_sort_recursive(arr, pi + 1, high);
    }
}

void quick_sort(int* arr, int n) {
    quick_sort_recursive(arr, 0, n - 1);
}

void merge(int* arr, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    
    for (i = 0; i < n1; i++) L[i] = arr[left + i];
    for (j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    
    i = 0; j = 0; k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    
    free(L);
    free(R);
}

void merge_sort_recursive(int* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_recursive(arr, left, mid);
        merge_sort_recursive(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void merge_sort(int* arr, int n) {
    merge_sort_recursive(arr, 0, n - 1);
}

/* ============================================================================
   BINARY SEARCH
   ============================================================================ */

int binary_search(int* data, int n, int target) {
    int low = 0;
    int high = n - 1;
    int mid;
    
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (data[mid] == target) return mid;
        if (data[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

/* ============================================================================
   GRAPH TRAVERSAL
   ============================================================================ */

void bfs(Graph* graph, int start) {
    int* visited = (int*)calloc(graph->num_vertices, sizeof(int));
    int* queue = (int*)malloc(graph->num_vertices * sizeof(int));
    int front = 0, rear = 0;
    int i, current;
    
    visited[start] = TRUE;
    queue[rear++] = start;
    
    while (front < rear) {
        current = queue[front++];
        printf("%d ", current);
        
        for (i = 0; i < graph->num_vertices; i++) {
            if (graph->matrix[current][i] && !visited[i]) {
                visited[i] = TRUE;
                queue[rear++] = i;
            }
        }
    }
    printf("\n");
    
    free(visited);
    free(queue);
}

void dfs_iterative(Graph* graph, int start) {
    int* visited = (int*)calloc(graph->num_vertices, sizeof(int));
    int* stack = (int*)malloc(graph->num_vertices * sizeof(int));
    int top = -1;
    int i, current;
    
    stack[++top] = start;
    
    while (top >= 0) {
        current = stack[top--];
        
        if (!visited[current]) {
            visited[current] = TRUE;
            printf("%d ", current);
            
            for (i = graph->num_vertices - 1; i >= 0; i--) {
                if (graph->matrix[current][i] && !visited[i]) {
                    stack[++top] = i;
                }
            }
        }
    }
    printf("\n");
    
    free(visited);
    free(stack);
}

/* ============================================================================
   DIJKSTRA'S ALGORITHM
   ============================================================================ */

void dijkstra(Graph* graph, int start) {
    int* dist = (int*)malloc(graph->num_vertices * sizeof(int));
    int* visited = (int*)calloc(graph->num_vertices, sizeof(int));
    int i, j, min_dist, u;
    
    for (i = 0; i < graph->num_vertices; i++) {
        dist[i] = 999999; /* Infinity */
    }
    dist[start] = 0;
    
    for (i = 0; i < graph->num_vertices - 1; i++) {
        min_dist = 999999;
        u = -1;
        
        for (j = 0; j < graph->num_vertices; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }
        
        if (u == -1) break;
        visited[u] = TRUE;
        
        for (j = 0; j < graph->num_vertices; j++) {
            if (!visited[j] && graph->matrix[u][j] && 
                dist[u] + graph->matrix[u][j] < dist[j]) {
                dist[j] = dist[u] + graph->matrix[u][j];
            }
        }
    }
    
    printf("Vertex   Distance from Source\n");
    for (i = 0; i < graph->num_vertices; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
    
    free(dist);
    free(visited);
}

/* ============================================================================
   KNAPSACK (Dynamic Programming)
   ============================================================================ */

int knapsack_01(int* weights, int* values, int n, int capacity) {
    int** dp;
    int i, w, result;
    
    dp = (int**)malloc((n + 1) * sizeof(int*));
    for (i = 0; i <= n; i++) {
        dp[i] = (int*)calloc(capacity + 1, sizeof(int));
    }
    
    for (i = 1; i <= n; i++) {
        for (w = 0; w <= capacity; w++) {
            if (weights[i - 1] <= w) {
                int val = values[i - 1] + dp[i - 1][w - weights[i - 1]];
                if (val > dp[i - 1][w]) {
                    dp[i][w] = val;
                } else {
                    dp[i][w] = dp[i - 1][w];
                }
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    
    result = dp[n][capacity];
    
    for (i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

/* ============================================================================
   FIBONACCI (Dynamic Programming)
   ============================================================================ */

int fib_memo(int n, int* memo) {
    if (memo[n] != -1) return memo[n];
    if (n <= 1) return n;
    memo[n] = fib_memo(n - 1, memo) + fib_memo(n - 2, memo);
    return memo[n];
}

int fibonacci_memo(int n) {
    int* memo = (int*)malloc((n + 1) * sizeof(int));
    int i, result;
    for (i = 0; i <= n; i++) memo[i] = -1;
    result = fib_memo(n, memo);
    free(memo);
    return result;
}

int fibonacci_tab(int n) {
    int* dp;
    int i, result;
    
    if (n <= 1) return n;
    
    dp = (int*)malloc((n + 1) * sizeof(int));
    dp[0] = 0;
    dp[1] = 1;
    
    for (i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    result = dp[n];
    free(dp);
    return result;
}

/* ============================================================================
   LINEAR REGRESSION
   ============================================================================ */

typedef struct {
    double slope;
    double intercept;
} LinearModel;

LinearModel linear_regression_fit(double* X, double* Y, int n) {
    LinearModel model;
    double x_mean = 0, y_mean = 0;
    double numerator = 0, denominator = 0;
    int i;
    
    for (i = 0; i < n; i++) {
        x_mean += X[i];
        y_mean += Y[i];
    }
    x_mean /= n;
    y_mean /= n;
    
    for (i = 0; i < n; i++) {
        numerator += (X[i] - x_mean) * (Y[i] - y_mean);
        denominator += (X[i] - x_mean) * (X[i] - x_mean);
    }
    
    model.slope = numerator / denominator;
    model.intercept = y_mean - model.slope * x_mean;
    
    return model;
}

double* linear_regression_predict(double* X, int n, LinearModel model) {
    double* Y_pred = (double*)malloc(n * sizeof(double));
    int i;
    for (i = 0; i < n; i++) {
        Y_pred[i] = model.slope * X[i] + model.intercept;
    }
    return Y_pred;
}

/* ============================================================================
   LOGISTIC REGRESSION (without math.h)
   ============================================================================ */

double sigmoid(double z) {
    /* Use our simple_exp implementation */
    return 1.0 / (1.0 + simple_exp(-z));
}

typedef struct {
    double* weights;
    double bias;
    int num_features;
} LogisticModel;

LogisticModel* logistic_regression_create(int num_features) {
    LogisticModel* model = (LogisticModel*)malloc(sizeof(LogisticModel));
    int i;
    if (model != NULL) {
        model->weights = (double*)calloc(num_features, sizeof(double));
        model->bias = 0.0;
        model->num_features = num_features;
    }
    return model;
}

void logistic_regression_fit(LogisticModel* model, double** X, int* Y, 
                              int n, double lr, int epochs) {
    int epoch, i, j;
    double z, p, error;
    
    for (epoch = 0; epoch < epochs; epoch++) {
        for (i = 0; i < n; i++) {
            z = model->bias;
            for (j = 0; j < model->num_features; j++) {
                z += model->weights[j] * X[i][j];
            }
            p = sigmoid(z);
            error = p - Y[i];
            
            for (j = 0; j < model->num_features; j++) {
                model->weights[j] -= lr * error * X[i][j];
            }
            model->bias -= lr * error;
        }
    }
}

int logistic_regression_predict(LogisticModel* model, double* x) {
    double z = model->bias;
    int j;
    for (j = 0; j < model->num_features; j++) {
        z += model->weights[j] * x[j];
    }
    return sigmoid(z) >= 0.5 ? 1 : 0;
}

void logistic_regression_free(LogisticModel* model) {
    if (model != NULL) {
        free(model->weights);
        free(model);
    }
}

/* ============================================================================
   K-NEAREST NEIGHBORS (KNN) - without math.h
   ============================================================================ */

typedef struct {
    double** X_train;
    int* Y_train;
    int n_samples;
    int n_features;
    int k;
} KNNModel;

double euclidean_distance(double* a, double* b, int n_features) {
    double sum = 0;
    int i;
    for (i = 0; i < n_features; i++) {
        sum += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return simple_sqrt(sum);
}

KNNModel* knn_create(int k) {
    KNNModel* model = (KNNModel*)malloc(sizeof(KNNModel));
    model->k = k;
    model->X_train = NULL;
    model->Y_train = NULL;
    model->n_samples = 0;
    model->n_features = 0;
    return model;
}

void knn_fit(KNNModel* model, double** X, int* Y, int n_samples, int n_features) {
    model->X_train = X;
    model->Y_train = Y;
    model->n_samples = n_samples;
    model->n_features = n_features;
}

int knn_predict(KNNModel* model, double* x) {
    typedef struct {
        double dist;
        int label;
    } DistanceLabel;
    
    DistanceLabel* distances;
    int i, j;
    int* votes;
    int max_votes = 0;
    int prediction = -1;
    
    distances = (DistanceLabel*)malloc(model->n_samples * sizeof(DistanceLabel));
    
    for (i = 0; i < model->n_samples; i++) {
        distances[i].dist = euclidean_distance(x, model->X_train[i], model->n_features);
        distances[i].label = model->Y_train[i];
    }
    
    /* Simple selection sort for k smallest */
    for (i = 0; i < model->k && i < model->n_samples; i++) {
        int min_idx = i;
        for (j = i + 1; j < model->n_samples; j++) {
            if (distances[j].dist < distances[min_idx].dist) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            DistanceLabel temp = distances[i];
            distances[i] = distances[min_idx];
            distances[min_idx] = temp;
        }
    }
    
    /* Count votes among k neighbors */
    votes = (int*)calloc(10, sizeof(int)); /* Assuming labels 0-9 */
    for (i = 0; i < model->k && i < model->n_samples; i++) {
        votes[distances[i].label]++;
    }
    
    for (i = 0; i < 10; i++) {
        if (votes[i] > max_votes) {
            max_votes = votes[i];
            prediction = i;
        }
    }
    
    free(distances);
    free(votes);
    return prediction;
}

void knn_free(KNNModel* model) {
    free(model);
}

/* ============================================================================
   K-MEANS CLUSTERING - without math.h
   ============================================================================ */

double** kmeans_cluster(double** X, int n_samples, int n_features, int k, int max_iter) {
    double** centroids;
    double** new_centroids;
    int* assignments;
    int iter, i, j, c, best_c;
    double min_dist, dist;
    int changed;
    
    /* Initialize centroids */
    centroids = (double**)malloc(k * sizeof(double*));
    for (i = 0; i < k; i++) {
        centroids[i] = (double*)malloc(n_features * sizeof(double));
        for (j = 0; j < n_features; j++) {
            centroids[i][j] = X[i % n_samples][j]; /* Simple initialization */
        }
    }
    
    assignments = (int*)malloc(n_samples * sizeof(int));
    new_centroids = (double**)malloc(k * sizeof(double*));
    for (i = 0; i < k; i++) {
        new_centroids[i] = (double*)calloc(n_features, sizeof(double));
    }
    
    for (iter = 0; iter < max_iter; iter++) {
        /* Assign points to nearest centroid */
        for (i = 0; i < n_samples; i++) {
            min_dist = 1e9;
            best_c = 0;
            for (c = 0; c < k; c++) {
                dist = 0;
                for (j = 0; j < n_features; j++) {
                    dist += (X[i][j] - centroids[c][j]) * (X[i][j] - centroids[c][j]);
                }
                dist = simple_sqrt(dist);
                if (dist < min_dist) {
                    min_dist = dist;
                    best_c = c;
                }
            }
            assignments[i] = best_c;
        }
        
        /* Update centroids */
        for (c = 0; c < k; c++) {
            for (j = 0; j < n_features; j++) {
                new_centroids[c][j] = 0;
            }
        }
        
        int* counts = (int*)calloc(k, sizeof(int));
        for (i = 0; i < n_samples; i++) {
            c = assignments[i];
            counts[c]++;
            for (j = 0; j < n_features; j++) {
                new_centroids[c][j] += X[i][j];
            }
        }
        
        for (c = 0; c < k; c++) {
            if (counts[c] > 0) {
                for (j = 0; j < n_features; j++) {
                    new_centroids[c][j] /= counts[c];
                }
            }
        }
        free(counts);
        
        /* Check convergence */
        changed = 0;
        for (c = 0; c < k; c++) {
            for (j = 0; j < n_features; j++) {
                if ((centroids[c][j] - new_centroids[c][j]) > 0.000001 || 
                    (new_centroids[c][j] - centroids[c][j]) > 0.000001) {
                    changed = 1;
                    break;
                }
            }
        }
        
        if (!changed) break;
        
        /* Update centroids */
        for (c = 0; c < k; c++) {
            for (j = 0; j < n_features; j++) {
                centroids[c][j] = new_centroids[c][j];
            }
        }
    }
    
    free(assignments);
    for (i = 0; i < k; i++) {
        free(new_centroids[i]);
    }
    free(new_centroids);
    
    return centroids;
}

/* ============================================================================
   NEURAL NETWORK
   ============================================================================ */

typedef struct Neuron {
    double* weights;  /* weights including bias as last element */
    double output;    /* stored output for backpropagation */
    double delta;     /* error delta for backpropagation */
    int num_inputs;
} Neuron;

typedef struct Layer {
    Neuron* neurons;
    int num_neurons;
} Layer;

typedef struct NeuralNetwork {
    Layer* layers;
    int num_layers;
    double learning_rate;
} NeuralNetwork;

/* Activation function and its derivative */
double sigmoid_nn(double x) {
    return 1.0 / (1.0 + simple_exp(-x));
}

double sigmoid_derivative(double x) {
    return x * (1.0 - x);
}

/* Create a new neuron with random weights */
Neuron neuron_create(int num_inputs) {
    Neuron n;
    int i;
    
    n.num_inputs = num_inputs;
    n.weights = (double*)malloc((num_inputs + 1) * sizeof(double)); /* +1 for bias */
    n.output = 0.0;
    n.delta = 0.0;
    
    /* Initialize weights with small random values between -0.5 and 0.5 */
    for (i = 0; i <= num_inputs; i++) {
        n.weights[i] = ((double)rand() / RAND_MAX) - 0.5;
    }
    
    return n;
}

/* Free neuron memory */
void neuron_free(Neuron* n) {
    if (n->weights != NULL) {
        free(n->weights);
        n->weights = NULL;
    }
}

/* Create a new layer with specified number of neurons */
Layer layer_create(int num_neurons, int inputs_per_neuron) {
    Layer l;
    int i;
    
    l.num_neurons = num_neurons;
    l.neurons = (Neuron*)malloc(num_neurons * sizeof(Neuron));
    
    for (i = 0; i < num_neurons; i++) {
        l.neurons[i] = neuron_create(inputs_per_neuron);
    }
    
    return l;
}

/* Free layer memory */
void layer_free(Layer* l) {
    int i;
    if (l->neurons != NULL) {
        for (i = 0; i < l->num_neurons; i++) {
            neuron_free(&l->neurons[i]);
        }
        free(l->neurons);
        l->neurons = NULL;
    }
}

/* Create a neural network */
NeuralNetwork* nn_create(int* layer_sizes, int num_layers, double learning_rate) {
    NeuralNetwork* nn;
    int i;
    
    if (num_layers < 2) return NULL; /* Need at least input and output layers */
    
    nn = (NeuralNetwork*)malloc(sizeof(NeuralNetwork));
    if (nn == NULL) return NULL;
    
    nn->num_layers = num_layers;
    nn->learning_rate = learning_rate;
    nn->layers = (Layer*)malloc(num_layers * sizeof(Layer));
    
    if (nn->layers == NULL) {
        free(nn);
        return NULL;
    }
    
    /* Create input layer */
    nn->layers[0] = layer_create(layer_sizes[0], 0); /* Input layer has no incoming weights */
    
    /* Create hidden and output layers */
    for (i = 1; i < num_layers; i++) {
        nn->layers[i] = layer_create(layer_sizes[i], layer_sizes[i-1]);
    }
    
    return nn;
}

/* Free neural network memory */
void nn_free(NeuralNetwork* nn) {
    int i;
    if (nn != NULL) {
        if (nn->layers != NULL) {
            for (i = 0; i < nn->num_layers; i++) {
                layer_free(&nn->layers[i]);
            }
            free(nn->layers);
        }
        free(nn);
    }
}

/* Forward propagate input through the network */
double* nn_forward(NeuralNetwork* nn, double* input) {
    int i, j, k;
    double* current_input = input;
    double* layer_output = NULL;
    Layer* layer;
    Neuron* neuron;
    
    /* Input layer just passes through the values */
    for (i = 0; i < nn->layers[0].num_neurons; i++) {
        nn->layers[0].neurons[i].output = current_input[i];
    }
    
    /* Process each subsequent layer */
    for (i = 1; i < nn->num_layers; i++) {
        layer = &nn->layers[i];
        layer_output = (double*)malloc(layer->num_neurons * sizeof(double));
        
        for (j = 0; j < layer->num_neurons; j++) {
            neuron = &layer->neurons[j];
            double z = neuron->weights[neuron->num_inputs]; /* bias */
            
            /* Sum inputs * weights */
            for (k = 0; k < neuron->num_inputs; k++) {
                z += neuron->weights[k] * nn->layers[i-1].neurons[k].output;
            }
            
            /* Apply activation function */
            neuron->output = sigmoid_nn(z);
            layer_output[j] = neuron->output;
        }
        
        current_input = layer_output;
    }
    
    return layer_output; /* Output of the last layer */
}

/* Backward propagate error and update weights */
void nn_backward(NeuralNetwork* nn, double* target) {
    int i, j, k;
    Layer* output_layer = &nn->layers[nn->num_layers - 1];
    Layer* hidden_layer;
    Layer* prev_layer;
    Neuron* neuron;
    double error;
    
    /* Calculate error for output layer */
    for (j = 0; j < output_layer->num_neurons; j++) {
        neuron = &output_layer->neurons[j];
        error = target[j] - neuron->output;
        neuron->delta = error * sigmoid_derivative(neuron->output);
    }
    
    /* Backpropagate error through hidden layers */
    for (i = nn->num_layers - 2; i > 0; i--) {
        hidden_layer = &nn->layers[i];
        prev_layer = &nn->layers[i + 1];
        
        for (j = 0; j < hidden_layer->num_neurons; j++) {
            neuron = &hidden_layer->neurons[j];
            error = 0.0;
            
            /* Sum errors from next layer */
            for (k = 0; k < prev_layer->num_neurons; k++) {
                error += prev_layer->neurons[k].delta * prev_layer->neurons[k].weights[j];
            }
            
            neuron->delta = error * sigmoid_derivative(neuron->output);
        }
    }
    
    /* Update weights (starting from layer 1, skipping input layer) */
    for (i = 1; i < nn->num_layers; i++) {
        for (j = 0; j < nn->layers[i].num_neurons; j++) {
            neuron = &nn->layers[i].neurons[j];
            
            /* Update bias */
            neuron->weights[neuron->num_inputs] += nn->learning_rate * neuron->delta;
            
            /* Update weights from previous layer */
            for (k = 0; k < neuron->num_inputs; k++) {
                neuron->weights[k] += nn->learning_rate * neuron->delta * 
                                      nn->layers[i-1].neurons[k].output;
            }
        }
    }
}

/* Train the network on a single sample */
void nn_train_sample(NeuralNetwork* nn, double* input, double* target) {
    nn_forward(nn, input);
    nn_backward(nn, target);
}

/* Train the network on a dataset */
void nn_train(NeuralNetwork* nn, double** inputs, double** targets, 
              int num_samples, int epochs) {
    int epoch, sample;
    
    for (epoch = 0; epoch < epochs; epoch++) {
        double total_error = 0.0;
        
        for (sample = 0; sample < num_samples; sample++) {
            double* output = nn_forward(nn, inputs[sample]);
            int i;
            
            /* Calculate error */
            for (i = 0; i < nn->layers[nn->num_layers - 1].num_neurons; i++) {
                double err = targets[sample][i] - output[i];
                total_error += err * err;
            }
            
            nn_backward(nn, targets[sample]);
            free(output);
        }
        
        /* Print progress every 100 epochs or last epoch */
        if (epoch % 100 == 0 || epoch == epochs - 1) {
            printf("Epoch %d, Error: %f\n", epoch, total_error);
        }
    }
}

/* Predict output for a single input */
double* nn_predict(NeuralNetwork* nn, double* input) {
    return nn_forward(nn, input);
}

/* ============================================================================
   TOY VIRTUAL MACHINE
   ============================================================================ */

typedef struct {
    unsigned short R[16];
    unsigned short M[256];
    int PC;
    int halted;
} TOY;

void toy_init(TOY* toy) {
    int i;
    for (i = 0; i < 16; i++) toy->R[i] = 0;
    for (i = 0; i < 256; i++) toy->M[i] = 0;
    toy->PC = 0;
    toy->halted = 0;
}

void toy_load_program(TOY* toy, unsigned short* program, int length) {
    int i;
    for (i = 0; i < length && i < 256; i++) {
        toy->M[i] = program[i];
    }
}

int toy_signed_value(unsigned short val) {
    return (val > 32767) ? (int)val - 65536 : (int)val;
}

void toy_run(TOY* toy) {
    unsigned short IR;
    int op, d, s, t, addr;
    unsigned short temp;
    
    while (!toy->halted) {
        /* FETCH */
        IR = toy->M[toy->PC];
        toy->PC = (toy->PC + 1) % 256;
        
        /* DECODE */
        op = (IR >> 12) & 0xF;
        d = (IR >> 8) & 0xF;
        s = (IR >> 4) & 0xF;
        t = IR & 0xF;
        addr = IR & 0xFF;
        
        /* EXECUTE */
        switch (op) {
            case 0: toy->halted = 1; break;
            case 1: toy->R[d] = (toy->R[s] + toy->R[t]) % 65536; break;
            case 2: toy->R[d] = (toy->R[s] - toy->R[t]) % 65536; break;
            case 3: toy->R[d] = toy->R[s] & toy->R[t]; break;
            case 4: toy->R[d] = toy->R[s] ^ toy->R[t]; break;
            case 5: toy->R[d] = (toy->R[s] << toy->R[t]) % 65536; break;
            case 6: {
                int val = toy_signed_value(toy->R[s]);
                toy->R[d] = (unsigned short)((val >> toy->R[t]) % 65536);
                break;
            }
            case 7: toy->R[d] = addr; break;
            case 8: toy->R[d] = toy->M[addr]; break;
            case 9: toy->M[addr] = toy->R[d]; break;
            case 10: toy->R[d] = toy->M[toy->R[t] % 256]; break;
            case 11: toy->M[toy->R[t] % 256] = toy->R[d]; break;
            case 12: if (toy_signed_value(toy->R[d]) == 0) toy->PC = addr; break;
            case 13: if (toy_signed_value(toy->R[d]) > 0) toy->PC = addr; break;
            case 14: toy->PC = toy->R[d] % 256; break;
            case 15: {
                temp = toy->PC;
                toy->PC = addr;
                toy->R[d] = temp;
                break;
            }
        }
        /* Enforce R0 = 0 */
        toy->R[0] = 0;
    }
}

/* ============================================================================
   UTILITY FUNCTIONS
   ============================================================================ */

void print_int(int x) { printf("%d ", x); }

void neural_network_demo(void) {
    printf("\nNEURAL NETWORK DEMONSTRATION:\n");
    printf("==================================================\n");
    printf("Training a simple XOR network...\n\n");
    
    /* Seed random number generator */
    srand(42);
    
    /* Create network: 2 inputs, 4 hidden neurons, 1 output */
    int layer_sizes[] = {2, 4, 1};
    NeuralNetwork* nn = nn_create(layer_sizes, 3, 0.5);
    
    if (nn == NULL) {
        printf("Failed to create neural network\n");
        return;
    }
    
    /* XOR training data */
    double input1[] = {0, 0};
    double input2[] = {0, 1};
    double input3[] = {1, 0};
    double input4[] = {1, 1};
    double* inputs[] = {input1, input2, input3, input4};
    
    double target1[] = {0};
    double target2[] = {1};
    double target3[] = {1};
    double target4[] = {0};
    double* targets[] = {target1, target2, target3, target4};
    
    /* Train the network */
    printf("Training XOR function (0,0->0; 0,1->1; 1,0->1; 1,1->0)...\n");
    nn_train(nn, inputs, targets, 4, 1000);
    
    printf("\nTesting trained network:\n");
    printf("----------------------------------------\n");
    
    /* Test each input */
    double* output;
    int i;
    
    for (i = 0; i < 4; i++) {
        output = nn_predict(nn, inputs[i]);
        printf("Input: (%.0f, %.0f) -> Output: %f (expected: %.0f)\n", 
               inputs[i][0], inputs[i][1], output[0], targets[i][0]);
        free(output);
    }
    
    /* Clean up */
    nn_free(nn);
    printf("==================================================\n\n");
}

/* ============================================================================
   MAIN FUNCTION - DEMONSTRATION
   ============================================================================ */

int main() {
    printf("Master Computer Programming - ANSI C Implementations\n");
    printf("==================================================\n\n");
    
    /* Example: Array Operations */
    {
        printf("ARRAY OPERATIONS:\n");
        int size = 5;
        int* arr = array_create(size, 0);
        int i;
        
        printf("Initial array: ");
        for (i = 0; i < size; i++) arr[i] = i + 1;
        array_traverse(arr, size, print_int);
        printf("\n");
        
        arr = array_insert_end(arr, &size, 6);
        printf("After insert end: ");
        array_traverse(arr, size, print_int);
        printf("\n");
        
        arr = array_insert_at(arr, &size, 2, 10);
        printf("After insert at index 2: ");
        array_traverse(arr, size, print_int);
        printf("\n");
        
        arr = array_delete_at(arr, &size, 3);
        printf("After delete at index 3: ");
        array_traverse(arr, size, print_int);
        printf("\n\n");
        
        free(arr);
    }
    
    /* Example: Linked List */
    {
        printf("LINKED LIST:\n");
        LinkedList list;
        linkedlist_init(&list);
        
        linkedlist_insert_at_tail(&list, 10);
        linkedlist_insert_at_tail(&list, 20);
        linkedlist_insert_at_head(&list, 5);
        
        printf("List: ");
        linkedlist_traverse(&list, print_int);
        printf("\n");
        
        linkedlist_delete_node(&list, 20);
        printf("After deleting 20: ");
        linkedlist_traverse(&list, print_int);
        printf("\n\n");
        
        linkedlist_free(&list);
    }
    
    /* Example: Stack */
    {
        printf("STACK:\n");
        Stack* stack = stack_create(5);
        stack_push(stack, 1);
        stack_push(stack, 2);
        stack_push(stack, 3);
        
        printf("Pop: %d\n", stack_pop(stack));
        printf("Peek: %d\n", stack_peek(stack));
        printf("Is empty? %s\n\n", stack_is_empty(stack) ? "Yes" : "No");
        
        stack_free(stack);
    }
    
    /* Example: Queue */
    {
        printf("QUEUE:\n");
        Queue* queue = queue_create(5);
        queue_enqueue(queue, 1);
        queue_enqueue(queue, 2);
        queue_enqueue(queue, 3);
        
        printf("Dequeue: %d\n", queue_dequeue(queue));
        printf("Front: %d\n", queue_front(queue));
        printf("Is empty? %s\n\n", queue_is_empty(queue) ? "Yes" : "No");
        
        queue_free(queue);
    }
    
    /* Example: Hash Table */
    {
        printf("HASH TABLE:\n");
        HashTable* ht = hashtable_create(10);
        hashtable_insert(ht, 5, 100);
        hashtable_insert(ht, 15, 200);
        
        printf("Search key 5: %d\n", hashtable_search(ht, 5));
        printf("Search key 15: %d\n", hashtable_search(ht, 15));
        
        hashtable_delete(ht, 5);
        printf("After delete, search key 5: ");
        fflush(stdout);
        /* Will print error message */
        hashtable_search(ht, 5);
        printf("\n");
        
        hashtable_free(ht);
    }
    
    /* Example: Binary Search Tree */
    {
        printf("\nBINARY SEARCH TREE:\n");
        TreeNode* root = NULL;
        root = tree_insert(root, 50);
        root = tree_insert(root, 30);
        root = tree_insert(root, 70);
        root = tree_insert(root, 20);
        root = tree_insert(root, 40);
        
        printf("Inorder traversal: ");
        tree_inorder(root, print_int);
        printf("\n");
        
        printf("Search 40: %s\n", tree_search(root, 40) ? "Found" : "Not found");
        printf("Search 100: %s\n", tree_search(root, 100) ? "Found" : "Not found");
        
        tree_free(root);
    }
    
    /* Example: Graph */
    {
        printf("\nGRAPH:\n");
        Graph* graph = graph_create(5);
        graph_add_edge(graph, 0, 1, 0);
        graph_add_edge(graph, 0, 2, 0);
        graph_add_edge(graph, 1, 3, 0);
        graph_add_edge(graph, 2, 4, 0);
        
        printf("Graph adjacency:\n");
        graph_display(graph);
        printf("\n");
        
        printf("BFS from 0: ");
        bfs(graph, 0);
        
        printf("DFS from 0: ");
        dfs_iterative(graph, 0);
        printf("\n");
        
        graph_free(graph);
    }
    
    /* Example: Min Heap */
    {
        printf("MIN HEAP:\n");
        MinHeap* heap = minheap_create(10);
        minheap_insert(heap, 5);
        minheap_insert(heap, 3);
        minheap_insert(heap, 8);
        minheap_insert(heap, 1);
        
        printf("Extract min: %d\n", minheap_extract_min(heap));
        printf("Extract min: %d\n", minheap_extract_min(heap));
        printf("Extract min: %d\n\n", minheap_extract_min(heap));
        
        minheap_free(heap);
    }
    
    /* Example: Trie */
    {
        printf("TRIE:\n");
        TrieNode* root = trie_create_node();
        trie_insert(root, "hello");
        trie_insert(root, "world");
        
        printf("Search 'hello': %s\n", trie_search(root, "hello") ? "Found" : "Not found");
        printf("Search 'help': %s\n", trie_search(root, "help") ? "Found" : "Not found");
        printf("Starts with 'wor': %s\n", trie_starts_with(root, "wor") ? "Yes" : "No");
        printf("\n");
        
        trie_free(root);
    }
    
    /* Example: Set */
    {
        printf("SET OPERATIONS:\n");
        MySet* set1 = set_create(10);
        MySet* set2 = set_create(10);
        
        set_add(set1, 1);
        set_add(set1, 2);
        set_add(set1, 3);
        
        set_add(set2, 2);
        set_add(set2, 3);
        set_add(set2, 4);
        
        MySet* union_set = set_union(set1, set2);
        MySet* intersect_set = set_intersection(set1, set2);
        
        printf("Set1: ");
        array_traverse(set1->elements, set1->size, print_int);
        printf("\nSet2: ");
        array_traverse(set2->elements, set2->size, print_int);
        printf("\nUnion: ");
        array_traverse(union_set->elements, union_set->size, print_int);
        printf("\nIntersection: ");
        array_traverse(intersect_set->elements, intersect_set->size, print_int);
        printf("\n\n");
        
        set_free(set1);
        set_free(set2);
        set_free(union_set);
        set_free(intersect_set);
    }
    
    /* Example: Sorting */
    {
        printf("SORTING ALGORITHMS:\n");
        int arr1[] = {64, 34, 25, 12, 22, 11, 90};
        int n1 = sizeof(arr1) / sizeof(arr1[0]);
        
        printf("Bubble Sort Descending:\n");
        printf("Original: ");
        array_traverse(arr1, n1, print_int);
        printf("\n");
        
        bubble_sort_descending(arr1, n1);
        printf("Sorted:   ");
        array_traverse(arr1, n1, print_int);
        printf("\n\n");
    }
    
    /* Example: Binary Search */
    {
        printf("BINARY SEARCH:\n");
        int arr[] = {2, 3, 5, 7, 11, 13, 17, 19};
        int n = sizeof(arr) / sizeof(arr[0]);
        int target = 7;
        
        printf("Array: ");
        array_traverse(arr, n, print_int);
        printf("\n");
        
        int result = binary_search(arr, n, target);
        if (result != -1) {
            printf("Element %d found at index %d\n", target, result);
        } else {
            printf("Element %d not found\n", target);
        }
        printf("\n");
    }
    
    /* Example: Knapsack */
    {
        printf("KNAPSACK (0/1):\n");
        int weights[] = {10, 20, 30};
        int values[] = {60, 100, 120};
        int capacity = 50;
        int n = sizeof(weights) / sizeof(weights[0]);
        
        int max_value = knapsack_01(weights, values, n, capacity);
        printf("Maximum value in knapsack: %d\n\n", max_value);
    }
    
    /* Example: Fibonacci */
    {
        printf("FIBONACCI:\n");
        int n = 10;
        printf("fib(%d) using memoization: %d\n", n, fibonacci_memo(n));
        printf("fib(%d) using tabulation: %d\n\n", n, fibonacci_tab(n));
    }
    
    /* Example: Linear Regression */
    {
        printf("LINEAR REGRESSION:\n");
        double X[] = {1, 2, 3, 4, 5};
        double Y[] = {2, 4, 5, 4, 5};
        int n = 5;
        
        LinearModel model = linear_regression_fit(X, Y, n);
        printf("Slope: %f, Intercept: %f\n", model.slope, model.intercept);
        
        double* predictions = linear_regression_predict(X, n, model);
        printf("Predictions: ");
        int i;
        for (i = 0; i < n; i++) {
            printf("%.2f ", predictions[i]);
        }
        printf("\n\n");
        free(predictions);
    }
    
    /* Example: KNN */
    {
        printf("K-NEAREST NEIGHBORS:\n");
        double X1[] = {1, 1};
        double X2[] = {2, 2};
        double X3[] = {3, 3};
        double X4[] = {6, 6};
        double X5[] = {7, 7};
        double* X_train[] = {X1, X2, X3, X4, X5};
        int Y_train[] = {0, 0, 0, 1, 1};
        double x_test[] = {4, 4};
        
        KNNModel* knn = knn_create(3);
        knn_fit(knn, X_train, Y_train, 5, 2);
        int pred = knn_predict(knn, x_test);
        printf("Test point (4,4) predicted class: %d\n\n", pred);
        knn_free(knn);
    }
    
    /* Example: K-Means */
    {
        printf("K-MEANS CLUSTERING:\n");
        double p1[] = {1, 1};
        double p2[] = {2, 1};
        double p3[] = {4, 3};
        double p4[] = {5, 4};
        double* points[] = {p1, p2, p3, p4};
        
        double** centroids = kmeans_cluster(points, 4, 2, 2, 100);
        printf("Centroids:\n");
        int i, j;
        for (i = 0; i < 2; i++) {
            printf("Centroid %d: ", i);
            for (j = 0; j < 2; j++) {
                printf("%.2f ", centroids[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        
        for (i = 0; i < 2; i++) free(centroids[i]);
        free(centroids);
    }
    
    /* Example: Neural Network */
    neural_network_demo();
    
    /* Example: TOY Virtual Machine */
    {
        printf("TOY VIRTUAL MACHINE:\n");
        TOY toy;
        toy_init(&toy);
        
        /* Simple program: R[1] = 5, R[2] = 3, R[3] = R[1] + R[2] */
        unsigned short program[] = {
            0x7105,  /* R[1] = 5 */
            0x7203,  /* R[2] = 3 */
            0x1312,  /* R[3] = R[1] + R[2] */
            0x0000   /* HALT */
        };
        
        toy_load_program(&toy, program, 4);
        toy_run(&toy);
        
        printf("R[1] = %d\n", toy.R[1]);
        printf("R[2] = %d\n", toy.R[2]);
        printf("R[3] = %d (should be 8)\n", toy.R[3]);
    }
    
    printf("\nAll implementations complete!\n");
    return 0;
}