"""
Master Computer Programming - Python Implementations

This file contains Python implementations of all algorithms
and data structures described in the Master Computer Programming document.
"""

import math
import random
from collections import deque
from typing import List, Dict, Any, Optional, Callable, Tuple, Set
import sys

# ============================================================================
# ARRAY OPERATIONS
# ============================================================================

class ArrayOperations:
    @staticmethod
    def create(size: int, initial_value: int = 0) -> List[int]:
        """Create an array of size n with initial value"""
        return [initial_value] * size
    
    @staticmethod
    def insert_end(arr: List[int], value: int) -> List[int]:
        """Insert element at the end"""
        arr.append(value)
        return arr
    
    @staticmethod
    def insert_at(arr: List[int], index: int, value: int) -> List[int]:
        """Insert element at specific index"""
        arr.insert(index, value)
        return arr
    
    @staticmethod
    def delete_at(arr: List[int], index: int) -> List[int]:
        """Delete element at specific index"""
        if 0 <= index < len(arr):
            arr.pop(index)
        return arr
    
    @staticmethod
    def traverse(arr: List[int], callback: Callable[[int], None] = print):
        """Traverse all elements"""
        for element in arr:
            callback(element)


# ============================================================================
# LINKED LIST
# ============================================================================

class Node:
    def __init__(self, data: Any):
        self.data = data
        self.next: Optional['Node'] = None


class LinkedList:
    def __init__(self):
        self.head: Optional[Node] = None
    
    def insert_at_head(self, value: Any) -> None:
        """Insert at beginning"""
        new_node = Node(value)
        new_node.next = self.head
        self.head = new_node
    
    def insert_at_tail(self, value: Any) -> None:
        """Insert at end"""
        new_node = Node(value)
        if self.head is None:
            self.head = new_node
            return
        
        current = self.head
        while current.next:
            current = current.next
        current.next = new_node
    
    def delete_node(self, value: Any) -> None:
        """Delete a node by value"""
        if self.head is None:
            return
        
        if self.head.data == value:
            self.head = self.head.next
            return
        
        current = self.head
        while current.next and current.next.data != value:
            current = current.next
        
        if current.next:
            current.next = current.next.next
    
    def traverse(self, callback: Callable[[Any], None] = print) -> None:
        """Traverse the list"""
        current = self.head
        while current:
            callback(current.data)
            current = current.next
    
    def to_list(self) -> List[Any]:
        """Convert linked list to Python list"""
        result = []
        current = self.head
        while current:
            result.append(current.data)
            current = current.next
        return result


# ============================================================================
# STACK
# ============================================================================

class Stack:
    def __init__(self):
        self.elements: List[Any] = []
    
    def push(self, value: Any) -> None:
        """Push element onto stack"""
        self.elements.append(value)
    
    def pop(self) -> Any:
        """Pop element from stack"""
        if self.is_empty():
            return "Stack Underflow"
        return self.elements.pop()
    
    def peek(self) -> Any:
        """Peek at top element"""
        if self.is_empty():
            return "Stack is empty"
        return self.elements[-1]
    
    def is_empty(self) -> bool:
        """Check if stack is empty"""
        return len(self.elements) == 0
    
    def size(self) -> int:
        """Get stack size"""
        return len(self.elements)


# ============================================================================
# QUEUE
# ============================================================================

class Queue:
    def __init__(self):
        self.elements: List[Any] = []
    
    def enqueue(self, value: Any) -> None:
        """Add element to rear"""
        self.elements.append(value)
    
    def dequeue(self) -> Any:
        """Remove element from front"""
        if self.is_empty():
            return "Queue Underflow"
        return self.elements.pop(0)
    
    def front(self) -> Any:
        """Get front element"""
        if self.is_empty():
            return "Queue is empty"
        return self.elements[0]
    
    def is_empty(self) -> bool:
        """Check if queue is empty"""
        return len(self.elements) == 0
    
    def size(self) -> int:
        """Get queue size"""
        return len(self.elements)


# ============================================================================
# HASH TABLE (with chaining)
# ============================================================================

class HashTable:
    def __init__(self, size: int = 10):
        self.size = size
        self.buckets: List[List[Tuple[Any, Any]]] = [[] for _ in range(size)]
    
    def _hash_function(self, key: Any) -> int:
        """Hash function for integer or string keys"""
        if isinstance(key, str):
            # Simple string hash
            return sum(ord(c) for c in key) % self.size
        # Integer hash
        return hash(key) % self.size
    
    def insert(self, key: Any, value: Any) -> None:
        """Insert key-value pair"""
        index = self._hash_function(key)
        # Check if key already exists
        for i, (k, v) in enumerate(self.buckets[index]):
            if k == key:
                self.buckets[index][i] = (key, value)
                return
        # Add new key-value pair
        self.buckets[index].append((key, value))
    
    def search(self, key: Any) -> Any:
        """Search for value by key"""
        index = self._hash_function(key)
        for k, v in self.buckets[index]:
            if k == key:
                return v
        return "Not found"
    
    def delete(self, key: Any) -> None:
        """Delete key-value pair"""
        index = self._hash_function(key)
        for i, (k, v) in enumerate(self.buckets[index]):
            if k == key:
                self.buckets[index].pop(i)
                return
    
    def __str__(self) -> str:
        """String representation"""
        result = []
        for i, bucket in enumerate(self.buckets):
            if bucket:
                result.append(f"Bucket {i}: {bucket}")
        return "\n".join(result)


# ============================================================================
# BINARY SEARCH TREE
# ============================================================================

class TreeNode:
    def __init__(self, data: Any):
        self.data = data
        self.left: Optional['TreeNode'] = None
        self.right: Optional['TreeNode'] = None


class BinarySearchTree:
    def __init__(self):
        self.root: Optional[TreeNode] = None
    
    def insert(self, value: Any) -> None:
        """Insert value into BST"""
        self.root = self._insert_rec(self.root, value)
    
    def _insert_rec(self, root: Optional[TreeNode], value: Any) -> TreeNode:
        """Recursive insert helper"""
        if root is None:
            return TreeNode(value)
        
        if value < root.data:
            root.left = self._insert_rec(root.left, value)
        else:
            root.right = self._insert_rec(root.right, value)
        
        return root
    
    def search(self, value: Any) -> bool:
        """Search for value in BST"""
        return self._search_rec(self.root, value)
    
    def _search_rec(self, root: Optional[TreeNode], value: Any) -> bool:
        """Recursive search helper"""
        if root is None:
            return False
        if value == root.data:
            return True
        if value < root.data:
            return self._search_rec(root.left, value)
        return self._search_rec(root.right, value)
    
    def inorder(self, callback: Callable[[Any], None] = print) -> None:
        """Inorder traversal"""
        self._inorder_rec(self.root, callback)
    
    def _inorder_rec(self, root: Optional[TreeNode], callback: Callable) -> None:
        """Recursive inorder helper"""
        if root:
            self._inorder_rec(root.left, callback)
            callback(root.data)
            self._inorder_rec(root.right, callback)
    
    def preorder(self, callback: Callable[[Any], None] = print) -> None:
        """Preorder traversal"""
        self._preorder_rec(self.root, callback)
    
    def _preorder_rec(self, root: Optional[TreeNode], callback: Callable) -> None:
        """Recursive preorder helper"""
        if root:
            callback(root.data)
            self._preorder_rec(root.left, callback)
            self._preorder_rec(root.right, callback)
    
    def postorder(self, callback: Callable[[Any], None] = print) -> None:
        """Postorder traversal"""
        self._postorder_rec(self.root, callback)
    
    def _postorder_rec(self, root: Optional[TreeNode], callback: Callable) -> None:
        """Recursive postorder helper"""
        if root:
            self._postorder_rec(root.left, callback)
            self._postorder_rec(root.right, callback)
            callback(root.data)


# ============================================================================
# GRAPH (Adjacency List)
# ============================================================================

class Graph:
    def __init__(self):
        self.adjacency_list: Dict[Any, List[Any]] = {}
    
    def add_vertex(self, vertex: Any) -> None:
        """Add a vertex to the graph"""
        if vertex not in self.adjacency_list:
            self.adjacency_list[vertex] = []
    
    def add_edge(self, u: Any, v: Any, directed: bool = False) -> None:
        """Add an edge between vertices u and v"""
        # Add vertices if they don't exist
        self.add_vertex(u)
        self.add_vertex(v)
        
        # Add edge
        self.adjacency_list[u].append(v)
        if not directed:
            self.adjacency_list[v].append(u)
    
    def display(self) -> None:
        """Display the graph"""
        for vertex in self.adjacency_list:
            print(f"{vertex} -> {self.adjacency_list[vertex]}")
    
    def get_vertices(self) -> List[Any]:
        """Get all vertices"""
        return list(self.adjacency_list.keys())
    
    def get_edges(self) -> List[Tuple[Any, Any]]:
        """Get all edges"""
        edges = []
        for u in self.adjacency_list:
            for v in self.adjacency_list[u]:
                edges.append((u, v))
        return edges


# ============================================================================
# HEAP (Min-Heap)
# ============================================================================

class MinHeap:
    def __init__(self):
        self.heap: List[Any] = []
    
    def parent(self, i: int) -> int:
        """Get parent index"""
        return (i - 1) // 2
    
    def left_child(self, i: int) -> int:
        """Get left child index"""
        return 2 * i + 1
    
    def right_child(self, i: int) -> int:
        """Get right child index"""
        return 2 * i + 2
    
    def insert(self, value: Any) -> None:
        """Insert value into heap"""
        self.heap.append(value)
        self._sift_up(len(self.heap) - 1)
    
    def _sift_up(self, i: int) -> None:
        """Sift up element at index i"""
        while i > 0 and self.heap[self.parent(i)] > self.heap[i]:
            # Swap with parent
            self.heap[self.parent(i)], self.heap[i] = \
                self.heap[i], self.heap[self.parent(i)]
            i = self.parent(i)
    
    def extract_min(self) -> Any:
        """Extract minimum value"""
        if not self.heap:
            return "Heap is empty"
        
        min_val = self.heap[0]
        self.heap[0] = self.heap[-1]
        self.heap.pop()
        
        if self.heap:
            self._heapify(0)
        
        return min_val
    
    def _heapify(self, i: int) -> None:
        """Heapify subtree rooted at i"""
        smallest = i
        left = self.left_child(i)
        right = self.right_child(i)
        
        if left < len(self.heap) and self.heap[left] < self.heap[smallest]:
            smallest = left
        if right < len(self.heap) and self.heap[right] < self.heap[smallest]:
            smallest = right
        
        if smallest != i:
            self.heap[i], self.heap[smallest] = self.heap[smallest], self.heap[i]
            self._heapify(smallest)
    
    def peek(self) -> Any:
        """Peek at minimum value"""
        return self.heap[0] if self.heap else "Heap is empty"
    
    def size(self) -> int:
        """Get heap size"""
        return len(self.heap)


# ============================================================================
# TRIE
# ============================================================================

class TrieNode:
    def __init__(self):
        self.children: Dict[str, 'TrieNode'] = {}
        self.is_end_of_word: bool = False


class Trie:
    def __init__(self):
        self.root = TrieNode()
    
    def insert(self, word: str) -> None:
        """Insert a word into the trie"""
        node = self.root
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode()
            node = node.children[char]
        node.is_end_of_word = True
    
    def search(self, word: str) -> bool:
        """Search for a word in the trie"""
        node = self.root
        for char in word:
            if char not in node.children:
                return False
            node = node.children[char]
        return node.is_end_of_word
    
    def starts_with(self, prefix: str) -> bool:
        """Check if any word starts with prefix"""
        node = self.root
        for char in prefix:
            if char not in node.children:
                return False
            node = node.children[char]
        return True
    
    def autocomplete(self, prefix: str) -> List[str]:
        """Get all words with given prefix"""
        node = self.root
        for char in prefix:
            if char not in node.children:
                return []
            node = node.children[char]
        
        # Find all words from this node
        results = []
        self._dfs(node, prefix, results)
        return results
    
    def _dfs(self, node: TrieNode, current: str, results: List[str]) -> None:
        """DFS helper for autocomplete"""
        if node.is_end_of_word:
            results.append(current)
        
        for char, child in node.children.items():
            self._dfs(child, current + char, results)


# ============================================================================
# SET (with operations)
# ============================================================================

class MySet:
    def __init__(self):
        self.elements: List[Any] = []
    
    def add(self, value: Any) -> None:
        """Add element to set"""
        if not self.contains(value):
            self.elements.append(value)
    
    def remove(self, value: Any) -> None:
        """Remove element from set"""
        if self.contains(value):
            self.elements.remove(value)
    
    def contains(self, value: Any) -> bool:
        """Check if set contains value"""
        return value in self.elements
    
    def size(self) -> int:
        """Get set size"""
        return len(self.elements)
    
    @staticmethod
    def union(s1: 'MySet', s2: 'MySet') -> 'MySet':
        """Union of two sets"""
        result = MySet()
        for value in s1.elements:
            result.add(value)
        for value in s2.elements:
            result.add(value)
        return result
    
    @staticmethod
    def intersection(s1: 'MySet', s2: 'MySet') -> 'MySet':
        """Intersection of two sets"""
        result = MySet()
        for value in s1.elements:
            if s2.contains(value):
                result.add(value)
        return result
    
    @staticmethod
    def difference(s1: 'MySet', s2: 'MySet') -> 'MySet':
        """Difference of two sets (s1 - s2)"""
        result = MySet()
        for value in s1.elements:
            if not s2.contains(value):
                result.add(value)
        return result
    
    def to_list(self) -> List[Any]:
        """Convert to list"""
        return self.elements.copy()


# ============================================================================
# SORTING ALGORITHMS
# ============================================================================

class Sorting:
    @staticmethod
    def bubble_sort_descending(data: List[int]) -> List[int]:
        """Bubble sort in descending order"""
        n = len(data)
        arr = data.copy()
        
        for i in range(n):
            for j in range(n - i - 1):
                if arr[j] < arr[j + 1]:
                    arr[j], arr[j + 1] = arr[j + 1], arr[j]
        
        return arr
    
    @staticmethod
    def quick_sort(arr: List[int]) -> List[int]:
        """Quick sort"""
        if len(arr) <= 1:
            return arr
        
        pivot = arr[0]
        left = [x for x in arr[1:] if x < pivot]
        right = [x for x in arr[1:] if x >= pivot]
        
        return Sorting.quick_sort(left) + [pivot] + Sorting.quick_sort(right)
    
    @staticmethod
    def merge_sort(arr: List[int]) -> List[int]:
        """Merge sort"""
        if len(arr) <= 1:
            return arr
        
        mid = len(arr) // 2
        left = Sorting.merge_sort(arr[:mid])
        right = Sorting.merge_sort(arr[mid:])
        
        return Sorting._merge(left, right)
    
    @staticmethod
    def _merge(left: List[int], right: List[int]) -> List[int]:
        """Merge two sorted lists"""
        result = []
        i = j = 0
        
        while i < len(left) and j < len(right):
            if left[i] <= right[j]:
                result.append(left[i])
                i += 1
            else:
                result.append(right[j])
                j += 1
        
        result.extend(left[i:])
        result.extend(right[j:])
        return result
    
    @staticmethod
    def insertion_sort(arr: List[int]) -> List[int]:
        """Insertion sort"""
        result = arr.copy()
        for i in range(1, len(result)):
            key = result[i]
            j = i - 1
            while j >= 0 and result[j] > key:
                result[j + 1] = result[j]
                j -= 1
            result[j + 1] = key
        return result
    
    @staticmethod
    def selection_sort(arr: List[int]) -> List[int]:
        """Selection sort"""
        result = arr.copy()
        n = len(result)
        
        for i in range(n):
            min_idx = i
            for j in range(i + 1, n):
                if result[j] < result[min_idx]:
                    min_idx = j
            result[i], result[min_idx] = result[min_idx], result[i]
        
        return result


# ============================================================================
# SEARCHING ALGORITHMS
# ============================================================================

class Searching:
    @staticmethod
    def binary_search(data: List[int], target: int) -> int:
        """Binary search - returns index of target or -1 if not found"""
        low = 0
        high = len(data) - 1
        
        while low <= high:
            mid = (low + high) // 2
            if data[mid] == target:
                return mid
            elif data[mid] < target:
                low = mid + 1
            else:
                high = mid - 1
        
        return -1
    
    @staticmethod
    def linear_search(data: List[int], target: int) -> int:
        """Linear search"""
        for i, value in enumerate(data):
            if value == target:
                return i
        return -1


# ============================================================================
# GRAPH TRAVERSAL ALGORITHMS
# ============================================================================

class GraphTraversal:
    @staticmethod
    def bfs(graph: Graph, start: Any) -> List[Any]:
        """Breadth-first search"""
        visited = set()
        queue = deque([start])
        result = []
        
        visited.add(start)
        
        while queue:
            vertex = queue.popleft()
            result.append(vertex)
            
            for neighbor in graph.adjacency_list.get(vertex, []):
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append(neighbor)
        
        return result
    
    @staticmethod
    def dfs_iterative(graph: Graph, start: Any) -> List[Any]:
        """Depth-first search (iterative)"""
        visited = set()
        stack = [start]
        result = []
        
        while stack:
            vertex = stack.pop()
            if vertex not in visited:
                visited.add(vertex)
                result.append(vertex)
                
                # Add neighbors in reverse order for correct order
                for neighbor in reversed(graph.adjacency_list.get(vertex, [])):
                    if neighbor not in visited:
                        stack.append(neighbor)
        
        return result
    
    @staticmethod
    def dfs_recursive(graph: Graph, start: Any, visited: Optional[Set] = None,
                      result: Optional[List] = None) -> List[Any]:
        """Depth-first search (recursive)"""
        if visited is None:
            visited = set()
        if result is None:
            result = []
        
        visited.add(start)
        result.append(start)
        
        for neighbor in graph.adjacency_list.get(start, []):
            if neighbor not in visited:
                GraphTraversal.dfs_recursive(graph, neighbor, visited, result)
        
        return result


# ============================================================================
# DIJKSTRA'S ALGORITHM (Shortest Path)
# ============================================================================

class Dijkstra:
    @staticmethod
    def shortest_path(graph: Graph, start: Any, end: Optional[Any] = None,
                      weight_func: Optional[Callable] = None):
        """
        Find shortest path using Dijkstra's algorithm
        
        Args:
            graph: Graph object
            start: Start vertex
            end: Optional end vertex
            weight_func: Function that returns weight between two vertices
                        (default: 1 for all edges)
        
        Returns:
            distances and previous nodes dictionary
        """
        if weight_func is None:
            weight_func = lambda u, v: 1
        
        # Initialize distances
        distances = {vertex: float('inf') for vertex in graph.adjacency_list}
        previous = {vertex: None for vertex in graph.adjacency_list}
        distances[start] = 0
        
        # Priority queue (min-heap) of (distance, vertex)
        pq = [(0, start)]
        visited = set()
        
        while pq:
            # Get vertex with smallest distance
            pq.sort()  # Simple sort - in production use heapq
            current_dist, current = pq.pop(0)
            
            if current in visited:
                continue
            
            visited.add(current)
            
            # If we reached the end, we can stop
            if end and current == end:
                break
            
            # Update neighbors
            for neighbor in graph.adjacency_list.get(current, []):
                if neighbor in visited:
                    continue
                
                new_dist = current_dist + weight_func(current, neighbor)
                
                if new_dist < distances[neighbor]:
                    distances[neighbor] = new_dist
                    previous[neighbor] = current
                    pq.append((new_dist, neighbor))
        
        return distances, previous
    
    @staticmethod
    def get_path(previous: Dict, start: Any, end: Any) -> List[Any]:
        """Reconstruct path from previous dictionary"""
        path = []
        current = end
        
        while current is not None:
            path.append(current)
            current = previous[current]
        
        path.reverse()
        
        # Check if path exists
        if path[0] == start:
            return path
        return []  # No path found


# ============================================================================
# KNAPSACK PROBLEM (Dynamic Programming)
# ============================================================================

class Knapsack:
    @staticmethod
    def zero_one_knapsack(weights: List[int], values: List[int], capacity: int) -> int:
        """
        0/1 Knapsack problem using dynamic programming
        
        Args:
            weights: List of item weights
            values: List of item values
            capacity: Maximum capacity
        
        Returns:
            Maximum value that can be achieved
        """
        n = len(weights)
        dp = [[0] * (capacity + 1) for _ in range(n + 1)]
        
        for i in range(1, n + 1):
            for w in range(capacity + 1):
                if weights[i - 1] <= w:
                    dp[i][w] = max(
                        values[i - 1] + dp[i - 1][w - weights[i - 1]],
                        dp[i - 1][w]
                    )
                else:
                    dp[i][w] = dp[i - 1][w]
        
        return dp[n][capacity]
    
    @staticmethod
    def unbounded_knapsack(weights: List[int], values: List[int], capacity: int) -> int:
        """
        Unbounded knapsack problem (items can be used multiple times)
        """
        dp = [0] * (capacity + 1)
        
        for w in range(capacity + 1):
            for i in range(len(weights)):
                if weights[i] <= w:
                    dp[w] = max(dp[w], dp[w - weights[i]] + values[i])
        
        return dp[capacity]


# ============================================================================
# FIBONACCI (Dynamic Programming)
# ============================================================================

class Fibonacci:
    @staticmethod
    def memoization(n: int, memo: Optional[Dict[int, int]] = None) -> int:
        """Fibonacci using memoization (top-down)"""
        if memo is None:
            memo = {}
        
        if n in memo:
            return memo[n]
        if n <= 1:
            return n
        
        memo[n] = Fibonacci.memoization(n - 1, memo) + Fibonacci.memoization(n - 2, memo)
        return memo[n]
    
    @staticmethod
    def tabulation(n: int) -> int:
        """Fibonacci using tabulation (bottom-up)"""
        if n <= 1:
            return n
        
        dp = [0] * (n + 1)
        dp[1] = 1
        
        for i in range(2, n + 1):
            dp[i] = dp[i - 1] + dp[i - 2]
        
        return dp[n]
    
    @staticmethod
    def space_optimized(n: int) -> int:
        """Space optimized Fibonacci"""
        if n <= 1:
            return n
        
        prev2, prev1 = 0, 1
        for _ in range(2, n + 1):
            current = prev1 + prev2
            prev2 = prev1
            prev1 = current
        
        return prev1


# ============================================================================
# LINEAR REGRESSION
# ============================================================================

class LinearRegression:
    def __init__(self):
        self.slope: float = 0.0
        self.intercept: float = 0.0
    
    def fit(self, X: List[float], Y: List[float]) -> 'LinearRegression':
        """Fit linear regression model"""
        n = len(X)
        x_mean = sum(X) / n
        y_mean = sum(Y) / n
        
        numerator = 0.0
        denominator = 0.0
        
        for i in range(n):
            numerator += (X[i] - x_mean) * (Y[i] - y_mean)
            denominator += (X[i] - x_mean) ** 2
        
        self.slope = numerator / denominator
        self.intercept = y_mean - self.slope * x_mean
        
        return self
    
    def predict(self, X: List[float]) -> List[float]:
        """Predict values for given X"""
        return [self.slope * x + self.intercept for x in X]
    
    def predict_single(self, x: float) -> float:
        """Predict single value"""
        return self.slope * x + self.intercept
    
    def r_squared(self, X: List[float], Y: List[float]) -> float:
        """Calculate R-squared score"""
        y_mean = sum(Y) / len(Y)
        y_pred = self.predict(X)
        
        ss_res = sum((y - y_p) ** 2 for y, y_p in zip(Y, y_pred))
        ss_tot = sum((y - y_mean) ** 2 for y in Y)
        
        return 1 - (ss_res / ss_tot)


# ============================================================================
# LOGISTIC REGRESSION
# ============================================================================

class LogisticRegression:
    def __init__(self, learning_rate: float = 0.01, epochs: int = 1000):
        self.learning_rate = learning_rate
        self.epochs = epochs
        self.weights: List[float] = []
        self.bias: float = 0.0
    
    def _sigmoid(self, z: float) -> float:
        """Sigmoid activation function"""
        return 1 / (1 + math.exp(-z))
    
    def fit(self, X: List[List[float]], Y: List[int]) -> 'LogisticRegression':
        """Fit logistic regression model"""
        n_samples = len(X)
        n_features = len(X[0])
        
        # Initialize parameters
        self.weights = [0.0] * n_features
        self.bias = 0.0
        
        # Gradient descent
        for _ in range(self.epochs):
            for i in range(n_samples):
                # Forward pass
                z = self.bias
                for j in range(n_features):
                    z += self.weights[j] * X[i][j]
                
                p = self._sigmoid(z)
                error = p - Y[i]
                
                # Backward pass (update)
                for j in range(n_features):
                    self.weights[j] -= self.learning_rate * error * X[i][j]
                self.bias -= self.learning_rate * error
        
        return self
    
    def predict_proba(self, X: List[List[float]]) -> List[float]:
        """Predict probabilities"""
        predictions = []
        for sample in X:
            z = self.bias
            for j in range(len(self.weights)):
                z += self.weights[j] * sample[j]
            predictions.append(self._sigmoid(z))
        return predictions
    
    def predict(self, X: List[List[float]], threshold: float = 0.5) -> List[int]:
        """Predict classes"""
        probas = self.predict_proba(X)
        return [1 if p >= threshold else 0 for p in probas]
    
    def predict_single(self, x: List[float], threshold: float = 0.5) -> int:
        """Predict single sample"""
        proba = self.predict_proba([x])[0]
        return 1 if proba >= threshold else 0


# ============================================================================
# NAIVE BAYES
# ============================================================================

class NaiveBayes:
    def __init__(self):
        self.classes: List[Any] = []
        self.priors: Dict[Any, float] = {}
        self.means: Dict[Any, List[float]] = {}
        self.stds: Dict[Any, List[float]] = {}
    
    def fit(self, X: List[List[float]], Y: List[Any]) -> 'NaiveBayes':
        """Fit Naive Bayes model (Gaussian)"""
        self.classes = list(set(Y))
        n_features = len(X[0])
        
        # Calculate priors and statistics for each class
        for c in self.classes:
            # Get samples of this class
            class_samples = [X[i] for i in range(len(X)) if Y[i] == c]
            self.priors[c] = len(class_samples) / len(X)
            
            # Calculate mean and std for each feature
            self.means[c] = []
            self.stds[c] = []
            
            for j in range(n_features):
                feature_values = [sample[j] for sample in class_samples]
                mean = sum(feature_values) / len(feature_values)
                variance = sum((x - mean) ** 2 for x in feature_values) / len(feature_values)
                std = math.sqrt(variance)
                
                self.means[c].append(mean)
                self.stds[c].append(std + 1e-9)  # Add small epsilon to avoid division by zero
        
        return self
    
    def _gaussian_pdf(self, x: float, mean: float, std: float) -> float:
        """Gaussian probability density function"""
        exponent = math.exp(-((x - mean) ** 2) / (2 * std ** 2))
        return (1 / (math.sqrt(2 * math.pi) * std)) * exponent
    
    def predict_proba(self, X: List[List[float]]) -> List[Dict[Any, float]]:
        """Predict probabilities for each class"""
        results = []
        
        for sample in X:
            probs = {}
            
            for c in self.classes:
                # Start with log prior
                log_prob = math.log(self.priors[c])
                
                # Add log likelihood for each feature
                for j in range(len(sample)):
                    prob = self._gaussian_pdf(sample[j], self.means[c][j], self.stds[c][j])
                    log_prob += math.log(prob)
                
                probs[c] = log_prob
            
            # Convert to probabilities using softmax
            max_log = max(probs.values())
            exp_probs = {c: math.exp(probs[c] - max_log) for c in probs}
            sum_exp = sum(exp_probs.values())
            probs = {c: exp_probs[c] / sum_exp for c in exp_probs}
            
            results.append(probs)
        
        return results
    
    def predict(self, X: List[List[float]]) -> List[Any]:
        """Predict classes"""
        probas = self.predict_proba(X)
        return [max(p, key=p.get) for p in probas]


# ============================================================================
# K-NEAREST NEIGHBORS (KNN)
# ============================================================================

class KNN:
    def __init__(self, k: int = 3):
        self.k = k
        self.X_train: List[List[float]] = []
        self.Y_train: List[Any] = []
    
    def fit(self, X: List[List[float]], Y: List[Any]) -> 'KNN':
        """Fit KNN model (just stores the data)"""
        self.X_train = X
        self.Y_train = Y
        return self
    
    def _euclidean_distance(self, a: List[float], b: List[float]) -> float:
        """Calculate Euclidean distance"""
        return math.sqrt(sum((x - y) ** 2 for x, y in zip(a, b)))
    
    def predict(self, X: List[List[float]]) -> List[Any]:
        """Predict classes for multiple samples"""
        return [self._predict_single(x) for x in X]
    
    def _predict_single(self, x: List[float]) -> Any:
        """Predict class for a single sample"""
        # Calculate distances to all training points
        distances = [(self._euclidean_distance(x, x_train), y_train)
                     for x_train, y_train in zip(self.X_train, self.Y_train)]
        
        # Sort by distance
        distances.sort(key=lambda d: d[0])
        
        # Get k nearest neighbors
        neighbors = distances[:self.k]
        
        # Count votes
        votes = {}
        for _, label in neighbors:
            votes[label] = votes.get(label, 0) + 1
        
        # Return class with most votes
        return max(votes.items(), key=lambda x: x[1])[0]
    
    def predict_proba(self, X: List[List[float]]) -> List[Dict[Any, float]]:
        """Predict class probabilities"""
        results = []
        
        for x in X:
            distances = [(self._euclidean_distance(x, x_train), y_train)
                         for x_train, y_train in zip(self.X_train, self.Y_train)]
            distances.sort(key=lambda d: d[0])
            neighbors = distances[:self.k]
            
            # Calculate probabilities
            probas = {}
            total_weight = 0
            
            for i, (dist, label) in enumerate(neighbors):
                # Weight by inverse distance (closer points have more weight)
                weight = 1 / (dist + 1e-9)  # Avoid division by zero
                probas[label] = probas.get(label, 0) + weight
                total_weight += weight
            
            # Normalize
            for label in probas:
                probas[label] /= total_weight
            
            results.append(probas)
        
        return results


# ============================================================================
# K-MEANS CLUSTERING
# ============================================================================

class KMeans:
    def __init__(self, k: int, max_iterations: int = 100):
        self.k = k
        self.max_iterations = max_iterations
        self.centroids: List[List[float]] = []
        self.labels: List[int] = []
    
    def fit(self, X: List[List[float]]) -> 'KMeans':
        """Fit K-Means clustering"""
        n_samples = len(X)
        n_features = len(X[0])
        
        # Step 1: Initialize centroids randomly
        self.centroids = random.sample(X, self.k)
        
        for iteration in range(self.max_iterations):
            # Step 2: Assign points to nearest centroid
            self.labels = []
            clusters = [[] for _ in range(self.k)]
            
            for point in X:
                distances = [self._euclidean_distance(point, centroid)
                             for centroid in self.centroids]
                label = distances.index(min(distances))
                self.labels.append(label)
                clusters[label].append(point)
            
            # Step 3: Update centroids
            new_centroids = []
            for i in range(self.k):
                if clusters[i]:
                    centroid = [sum(dim) / len(clusters[i]) for dim in zip(*clusters[i])]
                else:
                    centroid = X[random.randint(0, n_samples - 1)]
                new_centroids.append(centroid)
            
            # Step 4: Check convergence
            if self._centroids_equal(self.centroids, new_centroids):
                break
            
            self.centroids = new_centroids
        
        return self
    
    def predict(self, X: List[List[float]]) -> List[int]:
        """Predict cluster labels for new points"""
        labels = []
        for point in X:
            distances = [self._euclidean_distance(point, centroid)
                         for centroid in self.centroids]
            labels.append(distances.index(min(distances)))
        return labels
    
    def _euclidean_distance(self, a: List[float], b: List[float]) -> float:
        """Calculate Euclidean distance"""
        return math.sqrt(sum((x - y) ** 2 for x, y in zip(a, b)))
    
    def _centroids_equal(self, c1: List[List[float]], c2: List[List[float]]) -> bool:
        """Check if two centroid lists are equal"""
        for i in range(len(c1)):
            for j in range(len(c1[i])):
                if abs(c1[i][j] - c2[i][j]) > 1e-6:
                    return False
        return True
    
    def inertia(self, X: List[List[float]]) -> float:
        """Calculate inertia (sum of squared distances to nearest centroid)"""
        total = 0.0
        for point in X:
            distances = [self._euclidean_distance(point, centroid)
                         for centroid in self.centroids]
            total += min(distances) ** 2
        return total


# ============================================================================
# NEURAL NETWORK
# ============================================================================

class Neuron:
    def __init__(self, num_inputs: int):
        self.weights = [random.uniform(-0.5, 0.5) for _ in range(num_inputs)]
        self.bias = random.uniform(-0.5, 0.5)
        self.output = 0.0
        self.delta = 0.0
        self.num_inputs = num_inputs
    
    def activate(self, inputs: List[float]) -> float:
        """Forward pass through neuron"""
        z = self.bias
        for i in range(self.num_inputs):
            z += self.weights[i] * inputs[i]
        self.output = self._sigmoid(z)
        return self.output
    
    def _sigmoid(self, x: float) -> float:
        """Sigmoid activation"""
        return 1.0 / (1.0 + math.exp(-x))
    
    def _sigmoid_derivative(self) -> float:
        """Derivative of sigmoid"""
        return self.output * (1.0 - self.output)


class Layer:
    def __init__(self, num_neurons: int, inputs_per_neuron: int):
        self.neurons = [Neuron(inputs_per_neuron) for _ in range(num_neurons)]
        self.num_neurons = num_neurons
        self.outputs: List[float] = []
    
    def forward(self, inputs: List[float]) -> List[float]:
        """Forward pass through layer"""
        self.outputs = [neuron.activate(inputs) for neuron in self.neurons]
        return self.outputs


class NeuralNetwork:
    def __init__(self, layer_sizes: List[int], learning_rate: float = 0.1):
        """
        Create a neural network
        
        Args:
            layer_sizes: List where layer_sizes[0] is input size,
                        layer_sizes[-1] is output size
            learning_rate: Learning rate for gradient descent
        """
        self.layers = []
        self.learning_rate = learning_rate
        
        for i in range(1, len(layer_sizes)):
            self.layers.append(Layer(layer_sizes[i], layer_sizes[i - 1]))
    
    def forward(self, X: List[float]) -> List[float]:
        """Forward pass through the network"""
        current_input = X
        for layer in self.layers:
            current_input = layer.forward(current_input)
        return current_input
    
    def backward(self, X: List[float], y: List[float]) -> float:
        """
        Backward pass (backpropagation)
        
        Returns:
            Total error
        """
        # Forward pass
        output = self.forward(X)
        
        # Calculate error
        error = sum((target - pred) ** 2 for target, pred in zip(y, output))
        
        # Calculate output layer deltas
        for j, neuron in enumerate(self.layers[-1].neurons):
            neuron.delta = (y[j] - neuron.output) * neuron._sigmoid_derivative()
        
        # Backpropagate through hidden layers
        for i in range(len(self.layers) - 2, -1, -1):
            current_layer = self.layers[i]
            next_layer = self.layers[i + 1]
            
            for j, neuron in enumerate(current_layer.neurons):
                # Sum deltas from next layer
                error_sum = 0.0
                for next_neuron in next_layer.neurons:
                    error_sum += next_neuron.delta * next_neuron.weights[j]
                
                neuron.delta = error_sum * neuron._sigmoid_derivative()
        
        # Update weights
        # For first hidden layer, inputs are X
        prev_outputs = X
        
        for i, layer in enumerate(self.layers):
            for neuron in layer.neurons:
                # Update bias
                neuron.bias += self.learning_rate * neuron.delta
                
                # Update weights
                for j in range(len(neuron.weights)):
                    neuron.weights[j] += self.learning_rate * neuron.delta * prev_outputs[j]
            
            # Update prev_outputs for next layer
            prev_outputs = [neuron.output for neuron in layer.neurons]
        
        return error
    
    def train(self, X: List[List[float]], y: List[List[float]], epochs: int = 1000,
              verbose: bool = True) -> List[float]:
        """
        Train the neural network
        
        Args:
            X: Training data
            y: Target values
            epochs: Number of training epochs
            verbose: Whether to print progress
        
        Returns:
            List of errors per epoch
        """
        errors = []
        
        for epoch in range(epochs):
            total_error = 0.0
            
            for i in range(len(X)):
                total_error += self.backward(X[i], y[i])
            
            errors.append(total_error)
            
            if verbose and epoch % 100 == 0:
                print(f"Epoch {epoch}, Error: {total_error}")
        
        return errors
    
    def predict(self, X: List[List[float]]) -> List[List[float]]:
        """Predict for multiple samples"""
        return [self.forward(x) for x in X]
    
    def predict_single(self, x: List[float]) -> List[float]:
        """Predict for a single sample"""
        return self.forward(x)


# ============================================================================
# EXAMPLE USAGE AND DEMONSTRATION
# ============================================================================

def demonstrate_array():
    """Demonstrate array operations"""
    print("\n" + "="*50)
    print("ARRAY OPERATIONS")
    print("="*50)
    
    arr = ArrayOperations.create(5, 0)
    print(f"Create array: {arr}")
    
    for i in range(5):
        arr[i] = i + 1
    print(f"Set values: {arr}")
    
    arr = ArrayOperations.insert_end(arr, 6)
    print(f"After insert end: {arr}")
    
    arr = ArrayOperations.insert_at(arr, 2, 10)
    print(f"After insert at index 2: {arr}")
    
    arr = ArrayOperations.delete_at(arr, 3)
    print(f"After delete at index 3: {arr}")
    
    print("Traverse: ", end="")
    ArrayOperations.traverse(arr, lambda x: print(x, end=" "))
    print()


def demonstrate_linked_list():
    """Demonstrate linked list"""
    print("\n" + "="*50)
    print("LINKED LIST")
    print("="*50)
    
    ll = LinkedList()
    ll.insert_at_tail(10)
    ll.insert_at_tail(20)
    ll.insert_at_head(5)
    
    print("List: ", end="")
    ll.traverse(lambda x: print(x, end=" "))
    print()
    
    ll.delete_node(20)
    print("After deleting 20: ", end="")
    ll.traverse(lambda x: print(x, end=" "))
    print()
    print(f"As Python list: {ll.to_list()}")


def demonstrate_stack():
    """Demonstrate stack"""
    print("\n" + "="*50)
    print("STACK")
    print("="*50)
    
    stack = Stack()
    stack.push(1)
    stack.push(2)
    stack.push(3)
    
    print(f"Stack: {stack.elements}")
    print(f"Pop: {stack.pop()}")
    print(f"Peek: {stack.peek()}")
    print(f"Is empty? {stack.is_empty()}")
    print(f"Size: {stack.size()}")


def demonstrate_queue():
    """Demonstrate queue"""
    print("\n" + "="*50)
    print("QUEUE")
    print("="*50)
    
    queue = Queue()
    queue.enqueue(1)
    queue.enqueue(2)
    queue.enqueue(3)
    
    print(f"Queue: {queue.elements}")
    print(f"Dequeue: {queue.dequeue()}")
    print(f"Front: {queue.front()}")
    print(f"Is empty? {queue.is_empty()}")
    print(f"Size: {queue.size()}")


def demonstrate_hash_table():
    """Demonstrate hash table"""
    print("\n" + "="*50)
    print("HASH TABLE")
    print("="*50)
    
    ht = HashTable(5)
    ht.insert("apple", 5)
    ht.insert("banana", 7)
    ht.insert(42, "answer")
    
    print(f"Search 'apple': {ht.search('apple')}")
    print(f"Search 42: {ht.search(42)}")
    print(f"Search 'orange': {ht.search('orange')}")
    
    ht.delete("apple")
    print("After delete 'apple'")
    print(f"Search 'apple': {ht.search('apple')}")
    
    print("\nHash table structure:")
    print(ht)


def demonstrate_bst():
    """Demonstrate binary search tree"""
    print("\n" + "="*50)
    print("BINARY SEARCH TREE")
    print("="*50)
    
    bst = BinarySearchTree()
    values = [50, 30, 70, 20, 40, 60, 80]
    for v in values:
        bst.insert(v)
    
    print("Inorder traversal: ", end="")
    bst.inorder(lambda x: print(x, end=" "))
    print()
    
    print("Preorder traversal: ", end="")
    bst.preorder(lambda x: print(x, end=" "))
    print()
    
    print("Postorder traversal: ", end="")
    bst.postorder(lambda x: print(x, end=" "))
    print()
    
    print(f"Search 40: {bst.search(40)}")
    print(f"Search 100: {bst.search(100)}")


def demonstrate_graph():
    """Demonstrate graph"""
    print("\n" + "="*50)
    print("GRAPH")
    print("="*50)
    
    g = Graph()
    g.add_edge(0, 1)
    g.add_edge(0, 2)
    g.add_edge(1, 3)
    g.add_edge(2, 4)
    
    print("Graph adjacency:")
    g.display()
    
    print(f"\nBFS from 0: {GraphTraversal.bfs(g, 0)}")
    print(f"DFS from 0 (iterative): {GraphTraversal.dfs_iterative(g, 0)}")
    print(f"DFS from 0 (recursive): {GraphTraversal.dfs_recursive(g, 0)}")
    
    print(f"\nVertices: {g.get_vertices()}")
    print(f"Edges: {g.get_edges()}")


def demonstrate_heap():
    """Demonstrate min heap"""
    print("\n" + "="*50)
    print("MIN HEAP")
    print("="*50)
    
    heap = MinHeap()
    values = [5, 3, 8, 1, 2, 7]
    for v in values:
        heap.insert(v)
        print(f"Insert {v}: {heap.heap}")
    
    print(f"\nExtract min: {heap.extract_min()}")
    print(f"Heap after extract: {heap.heap}")
    print(f"Extract min: {heap.extract_min()}")
    print(f"Heap after extract: {heap.heap}")
    print(f"Peek: {heap.peek()}")
    print(f"Size: {heap.size()}")


def demonstrate_trie():
    """Demonstrate trie"""
    print("\n" + "="*50)
    print("TRIE")
    print("="*50)
    
    trie = Trie()
    words = ["hello", "world", "help", "hell", "hero"]
    for word in words:
        trie.insert(word)
    
    print(f"Search 'hello': {trie.search('hello')}")
    print(f"Search 'help': {trie.search('help')}")
    print(f"Search 'heaven': {trie.search('heaven')}")
    print(f"Starts with 'he': {trie.starts_with('he')}")
    print(f"Starts with 'wo': {trie.starts_with('wo')}")
    print(f"Autocomplete 'he': {trie.autocomplete('he')}")


def demonstrate_set():
    """Demonstrate set operations"""
    print("\n" + "="*50)
    print("SET OPERATIONS")
    print("="*50)
    
    s1 = MySet()
    s2 = MySet()
    
    for v in [1, 2, 3]:
        s1.add(v)
    for v in [2, 3, 4]:
        s2.add(v)
    
    print(f"Set1: {s1.to_list()}")
    print(f"Set2: {s2.to_list()}")
    
    union_set = MySet.union(s1, s2)
    intersect_set = MySet.intersection(s1, s2)
    diff_set = MySet.difference(s1, s2)
    
    print(f"Union: {union_set.to_list()}")
    print(f"Intersection: {intersect_set.to_list()}")
    print(f"Difference (s1 - s2): {diff_set.to_list()}")


def demonstrate_sorting():
    """Demonstrate sorting algorithms"""
    print("\n" + "="*50)
    print("SORTING ALGORITHMS")
    print("="*50)
    
    arr = [64, 34, 25, 12, 22, 11, 90]
    print(f"Original: {arr}")
    
    print(f"Bubble Sort (descending): {Sorting.bubble_sort_descending(arr)}")
    print(f"Quick Sort: {Sorting.quick_sort(arr)}")
    print(f"Merge Sort: {Sorting.merge_sort(arr)}")
    print(f"Insertion Sort: {Sorting.insertion_sort(arr)}")
    print(f"Selection Sort: {Sorting.selection_sort(arr)}")


def demonstrate_searching():
    """Demonstrate searching algorithms"""
    print("\n" + "="*50)
    print("SEARCHING ALGORITHMS")
    print("="*50)
    
    arr = [2, 3, 5, 7, 11, 13, 17, 19]
    target = 7
    print(f"Array: {arr}")
    print(f"Target: {target}")
    
    result = Searching.binary_search(arr, target)
    if result != -1:
        print(f"Binary Search: Found at index {result}")
    else:
        print("Binary Search: Not found")
    
    result = Searching.linear_search(arr, target)
    if result != -1:
        print(f"Linear Search: Found at index {result}")
    else:
        print("Linear Search: Not found")


def demonstrate_dijkstra():
    """Demonstrate Dijkstra's algorithm"""
    print("\n" + "="*50)
    print("DIJKSTRA'S ALGORITHM")
    print("="*50)
    
    # Create weighted graph
    g = Graph()
    g.add_edge('A', 'B')
    g.add_edge('A', 'C')
    g.add_edge('B', 'D')
    g.add_edge('C', 'D')
    g.add_edge('C', 'E')
    g.add_edge('D', 'E')
    
    # Custom weight function
    weights = {
        ('A', 'B'): 4, ('B', 'A'): 4,
        ('A', 'C'): 2, ('C', 'A'): 2,
        ('B', 'D'): 5, ('D', 'B'): 5,
        ('C', 'D'): 1, ('D', 'C'): 1,
        ('C', 'E'): 3, ('E', 'C'): 3,
        ('D', 'E'): 2, ('E', 'D'): 2,
    }
    
    def weight_func(u, v):
        return weights.get((u, v), float('inf'))
    
    distances, previous = Dijkstra.shortest_path(g, 'A', weight_func=weight_func)
    
    print("Distances from A:")
    for vertex, dist in distances.items():
        print(f"  {vertex}: {dist}")
    
    print("\nPaths:")
    for vertex in g.get_vertices():
        if vertex != 'A':
            path = Dijkstra.get_path(previous, 'A', vertex)
            print(f"  A -> {vertex}: {path}")


def demonstrate_knapsack():
    """Demonstrate knapsack problem"""
    print("\n" + "="*50)
    print("KNAPSACK PROBLEM")
    print("="*50)
    
    weights = [10, 20, 30]
    values = [60, 100, 120]
    capacity = 50
    
    print(f"Weights: {weights}")
    print(f"Values: {values}")
    print(f"Capacity: {capacity}")
    
    result = Knapsack.zero_one_knapsack(weights, values, capacity)
    print(f"0/1 Knapsack max value: {result}")
    
    result = Knapsack.unbounded_knapsack(weights, values, capacity)
    print(f"Unbounded Knapsack max value: {result}")


def demonstrate_fibonacci():
    """Demonstrate Fibonacci algorithms"""
    print("\n" + "="*50)
    print("FIBONACCI")
    print("="*50)
    
    n = 10
    print(f"Fibonacci({n})")
    print(f"  Memoization: {Fibonacci.memoization(n)}")
    print(f"  Tabulation: {Fibonacci.tabulation(n)}")
    print(f"  Space Optimized: {Fibonacci.space_optimized(n)}")


def demonstrate_linear_regression():
    """Demonstrate linear regression"""
    print("\n" + "="*50)
    print("LINEAR REGRESSION")
    print("="*50)
    
    X = [1, 2, 3, 4, 5]
    Y = [2, 4, 5, 4, 5]
    
    print(f"X: {X}")
    print(f"Y: {Y}")
    
    model = LinearRegression().fit(X, Y)
    print(f"Slope: {model.slope:.4f}")
    print(f"Intercept: {model.intercept:.4f}")
    
    predictions = model.predict(X)
    print(f"Predictions: {[f'{p:.2f}' for p in predictions]}")
    
    r2 = model.r_squared(X, Y)
    print(f"R² Score: {r2:.4f}")
    
    x_new = 6
    pred = model.predict_single(x_new)
    print(f"Predict for x={x_new}: {pred:.2f}")


def demonstrate_logistic_regression():
    """Demonstrate logistic regression"""
    print("\n" + "="*50)
    print("LOGISTIC REGRESSION")
    print("="*50)
    
    # Simple dataset
    X = [[1], [2], [3], [4], [5], [6]]
    Y = [0, 0, 0, 1, 1, 1]
    
    print(f"X: {X}")
    print(f"Y: {Y}")
    
    model = LogisticRegression(learning_rate=0.1, epochs=1000).fit(X, Y)
    
    print(f"Weights: {model.weights}")
    print(f"Bias: {model.bias:.4f}")
    
    predictions = model.predict(X)
    probabilities = model.predict_proba(X)
    
    print("\nPredictions:")
    for i in range(len(X)):
        print(f"  X={X[i][0]}, prob={probabilities[i]:.4f}, pred={predictions[i]}")


def demonstrate_knn():
    """Demonstrate K-Nearest Neighbors"""
    print("\n" + "="*50)
    print("K-NEAREST NEIGHBORS")
    print("="*50)
    
    X_train = [[1, 1], [2, 2], [3, 3], [6, 6], [7, 7]]
    Y_train = [0, 0, 0, 1, 1]
    X_test = [[4, 4], [2, 1], [7, 6]]
    
    print(f"Training data:")
    for i in range(len(X_train)):
        print(f"  {X_train[i]} -> {Y_train[i]}")
    
    knn = KNN(k=3).fit(X_train, Y_train)
    
    print("\nPredictions:")
    for x in X_test:
        pred = knn.predict([x])[0]
        proba = knn.predict_proba([x])[0]
        print(f"  {x} -> {pred} (probabilities: {proba})")


def demonstrate_kmeans():
    """Demonstrate K-Means clustering"""
    print("\n" + "="*50)
    print("K-MEANS CLUSTERING")
    print("="*50)
    
    # Generate sample data
    X = [[1, 1], [2, 1], [1, 2], [2, 2],
         [8, 8], [9, 8], [8, 9], [9, 9]]
    
    print(f"Data points: {X}")
    
    kmeans = KMeans(k=2).fit(X)
    
    print(f"\nCentroids:")
    for i, centroid in enumerate(kmeans.centroids):
        print(f"  Centroid {i}: {centroid}")
    
    print(f"\nLabels: {kmeans.labels}")
    print(f"Inertia: {kmeans.inertia(X):.4f}")


def demonstrate_neural_network():
    """Demonstrate neural network with XOR problem"""
    print("\n" + "="*50)
    print("NEURAL NETWORK - XOR PROBLEM")
    print("="*50)
    
    # XOR dataset
    X = [[0, 0], [0, 1], [1, 0], [1, 1]]
    y = [[0], [1], [1], [0]]
    
    print("XOR Truth Table:")
    print("  Input -> Output")
    for i in range(len(X)):
        print(f"  {X[i]} -> {y[i][0]}")
    
    # Create network: 2 inputs, 4 hidden, 1 output
    nn = NeuralNetwork([2, 4, 1], learning_rate=0.5)
    
    print("\nTraining neural network...")
    errors = nn.train(X, y, epochs=2000, verbose=False)
    print(f"Final error: {errors[-1]:.6f}")
    
    print("\nPredictions after training:")
    predictions = nn.predict(X)
    for i in range(len(X)):
        print(f"  {X[i]} -> {predictions[i][0]:.6f} (expected {y[i][0]})")


def demonstrate_toy_vm():
    """Demonstrate TOY Virtual Machine"""
    print("\n" + "="*50)
    print("TOY VIRTUAL MACHINE")
    print("="*50)
    
    class TOY:
        def __init__(self):
            self.R = [0] * 16
            self.M = [0] * 256
            self.PC = 0
            self.halted = False
        
        def load_program(self, program):
            for i, instr in enumerate(program):
                if i < 256:
                    self.M[i] = instr
        
        def signed_value(self, val):
            return val - 65536 if val > 32767 else val
        
        def run(self):
            while not self.halted:
                # FETCH
                IR = self.M[self.PC]
                self.PC = (self.PC + 1) % 256
                
                # DECODE
                op = (IR >> 12) & 0xF
                d = (IR >> 8) & 0xF
                s = (IR >> 4) & 0xF
                t = IR & 0xF
                addr = IR & 0xFF
                
                # EXECUTE
                if op == 0:
                    self.halted = True
                elif op == 1:  # ADD
                    self.R[d] = (self.R[s] + self.R[t]) % 65536
                elif op == 2:  # SUB
                    self.R[d] = (self.R[s] - self.R[t]) % 65536
                elif op == 7:  # LOADI
                    self.R[d] = addr
                elif op == 8:  # LOAD
                    self.R[d] = self.M[addr]
                elif op == 9:  # STORE
                    self.M[addr] = self.R[d]
                
                # Enforce R0 = 0
                self.R[0] = 0
    
    # Simple program: R[1] = 5, R[2] = 3, R[3] = R[1] + R[2]
    program = [
        0x7105,  # R[1] = 5
        0x7203,  # R[2] = 3
        0x1312,  # R[3] = R[1] + R[2]
        0x0000   # HALT
    ]
    
    toy = TOY()
    toy.load_program(program)
    toy.run()
    
    print(f"R[1] = {toy.R[1]}")
    print(f"R[2] = {toy.R[2]}")
    print(f"R[3] = {toy.R[3]} (should be 8)")
    print(f"R[0] = {toy.R[0]} (always 0)")


def main():
    """Main function to demonstrate all algorithms"""
    print("="*60)
    print("MASTER COMPUTER PROGRAMMING - PYTHON IMPLEMENTATIONS")
    print("="*60)
    
    demonstrations = [
        demonstrate_array,
        demonstrate_linked_list,
        demonstrate_stack,
        demonstrate_queue,
        demonstrate_hash_table,
        demonstrate_bst,
        demonstrate_graph,
        demonstrate_heap,
        demonstrate_trie,
        demonstrate_set,
        demonstrate_sorting,
        demonstrate_searching,
        demonstrate_dijkstra,
        demonstrate_knapsack,
        demonstrate_fibonacci,
        demonstrate_linear_regression,
        demonstrate_logistic_regression,
        demonstrate_knn,
        demonstrate_kmeans,
        demonstrate_neural_network,
        demonstrate_toy_vm
    ]
    
    for demo in demonstrations:
        demo()
    
    print("\n" + "="*60)
    print("ALL IMPLEMENTATIONS COMPLETE!")
    print("="*60)


if __name__ == "__main__":
    # Set random seed for reproducibility
    random.seed(42)
    main()