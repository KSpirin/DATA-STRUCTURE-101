# HASH: Comprehensive Study Guide & Implementation Manual

Welcome to the ultimate study guide for **Hashing and Hash Tables**. This document covers theoretical searching paradigms, hash functions, collision resolution methods with their underlying mathematics, rehashing strategies, and complete, production-ready, templated C++ implementations.

---

## 1. Searching Paradigms: An Overview

Before diving into hashing, it is crucial to understand the landscape of search algorithms and where hashing fits.

| Algorithm | Data Structure Requirement | Core Mechanics | Time Complexity (Average) | Time Complexity (Worst) | Space Complexity |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Linear / Sequential Search** | Unordered or ordered sequential container (Array, Linked List) | Scans elements one by one from start to end. | $O(N)$ | $O(N)$ | $O(1)$ |
| **Binary Search** | Sorted contiguous container (Sorted Array) | Divides search space in half repeatedly by comparing the middle element. | $O(\log N)$ | $O(\log N)$ | $O(1)$ (iterative) |
| **Index Sequential Search** | Divided blocks/segments with an index table | Uses an index table to jump to a specific block, then performs a linear search within that block. | $O(\sqrt{N})$ | $O(N)$ | $O(K)$ index size |
| **Hash Search** | Associative container (Hash Table / Hash Map) | Applies a hash function to the key to compute a direct index (address) in constant time. | $O(1)$ | $O(N)$ | $O(N)$ |

---

## 2. The Hash Table Abstraction

A **Hash Table** (or **Hash Map**) is an abstract data type that maps **keys** to **values** (implementing an associative array or dictionary). 

- **Key**: The unique identifier used to look up, insert, or delete data (e.g., student ID, string word).
- **Value**: The data record associated with the key.
- **Hash Function**: A mathematical function $H(K)$ that maps a large key space to a smaller, fixed integer range $[0, N-1]$, where $N$ is the size of the table.
- **Bucket / Slot**: An entry in the table array that stores the key-value pair or points to a chain.

---

## 3. Hash Functions

A good hash function should be **deterministic**, **fast to compute**, and **distribute keys uniformly** across the array slots to minimize collisions. The following are classical hashing techniques:

### A. Direct Hashing
The key itself is directly used as the index. No calculation is performed.
$$\text{Address} = K$$
- **Pros**: $O(1)$ lookup, zero collisions.
- **Cons**: Only usable if the key space is small, dense, and non-negative (e.g., indices $0$ to $99$). Extremely wasteful of space if keys are sparse.

### B. Subtraction Hashing
The key is shifted down by a constant offset $C$ to fit into a $0$-indexed table.
$$\text{Address} = K - C$$
- **Example**: Mapping employee IDs in the range $[1000, 1999]$ to a table of size 1000:
  $$\text{Address} = \text{ID} - 1000$$

### C. Digit-Extraction Hashing
Selected digits (positions) are extracted from the key, and concatenated to form the address. Positions with the highest variability are chosen to prevent clustering.
- **Example**: From key $125434$, if we extract the 2nd, 4th, and 6th digits:
  - Digit at position 2: `2`
  - Digit at position 4: `4`
  - Digit at position 6: `4`
  - Address = $244$

### D. Mid-Square Hashing
1. Square the key ($K^2$).
2. Extract the middle $r$ digits of the squared result as the address.
- **Example**: Let $K = 1234$.
  - $K^2 = 1,522,756$
  - Middle digits = $227$ (Address)
- **Rationale**: Since the middle digits of the square depend on all digits of the original key, it results in good distribution.

### E. Fold Shift Hashing
1. Divide the key into parts of equal size (except possibly the last part).
2. Sum the parts.
3. Compute the sum modulo the table size $M$.
- **Formula**:
  $$\text{Address} = \left(\sum \text{parts}\right) \pmod M$$
- **Example**: Let key = $12345678$, Table Size $M = 1000$.
  - Split into: $a = 123$, $b = 456$, $c = 78$.
  - Sum = $123 + 456 + 78 = 657$.
  - Address = $657 \pmod{1000} = 657$.

### G. Fold Boundary Hashing
Similar to Fold Shift Hashing, but the boundary parts (the leftmost and rightmost segments) are **reversed** (folded inward) before summation.
- **Example**: Let key = $12345678$, Table Size $M = 1000$.
  - Split into: $a = 123$, $b = 456$, $c = 78$.
  - Reverse boundaries: $a' = 321$, $c' = 87$.
  - Sum = $321 + 456 + 87 = 864$.
  - Address = $864 \pmod{1000} = 864$.

### H. Modulo-Division Hashing (Division Method)
The key is divided by the table size $N$, and the remainder is used as the address.
$$H(K) = K \pmod N$$
- **Important**: To achieve optimal distribution and avoid patterns in key digits, the table size $N$ should be a **prime number** not close to a power of $2$ or $10$.

---

## 4. Collision Resolution

A **Collision** occurs when two distinct keys hash to the same table slot:
$$K_1 \neq K_2 \quad \text{but} \quad H(K_1) = H(K_2)$$
As shown in the slides, if $N = 7$:
$$17 \pmod 7 = 3 \quad \text{and} \quad 24 \pmod 7 = 3 \quad \text{(Collision!)}$$

There are two primary paradigms for resolving collisions:

### A. Separate Chaining (Open Hashing / Closed Addressing)
Each bucket in the hash table points to a linked list (or chain) of elements that hash to the same index.

- **Insertion**: Compute $H(K)$, then insert the element at the head/tail of the list at $H(K)$.
- **Search**: Compute $H(K)$, then traverse the list at $H(K)$ looking for key $K$.
- **Deletion**: Compute $H(K)$, find the node in the list, and remove it.
- **Load Factor ($\lambda$)**:
  $$\lambda = \frac{M}{N}$$
  where $M$ is the number of elements, and $N$ is the table size. In Separate Chaining, $\lambda$ can be greater than $1$.
- **Time Complexity**:
  - Insert: $O(1)$ (inserting at the head of the list)
  - Search/Delete: $O(1 + \lambda)$ average; $O(M)$ worst-case (if all keys hash to the same bucket).

---

### B. Open Addressing (Closed Hashing / Open Addressing)
All elements are stored directly in the hash table array. If a collision occurs, we probe other slots sequentially according to a probing sequence until an empty slot is found.

#### 1. Linear Probing
If a collision occurs at index $H(K)$, we probe adjacent slots sequentially ($+1, +2, +3, \dots$).
- **Formula**:
  $$h_i(K) = (H(K) + i) \pmod N$$
  where $i$ is the collision count ($i = 0, 1, 2, \dots$).
- **Example (from slides)**: $N = 13$, keys inserted: $156, 85, 42, 54, 189$
  - $156 \pmod{13} = 0 \implies \text{slot } 0$
  - $85 \pmod{13} = 7 \implies \text{slot } 7$
  - $42 \pmod{13} = 3 \implies \text{slot } 3$
  - $54 \pmod{13} = 2 \implies \text{slot } 2$
  - $189 \pmod{13} = 7 \implies \text{Collision! } i=1 \implies (7 + 1) \pmod{13} = 8 \implies \text{slot } 8$
- **Primary Clustering**: Linear probing suffers from *Primary Clustering*, where contiguous blocks of occupied slots build up, making future search paths longer.

#### 2. Quadratic Probing
Eliminates primary clustering by probing using quadratic offsets ($+1^2, +2^2, +3^2, \dots$).
- **Formula**:
  $$h_i(K) = (H(K) + i^2) \pmod N$$
  where $i$ is the collision count ($i = 0, 1, 2, \dots$).
- **Example (from slides)**: $N = 11$, keys: $85, 55, 42, 96$
  - $85 \pmod{11} = 8 \implies \text{slot } 8$
  - $55 \pmod{11} = 0 \implies \text{slot } 0$
  - $42 \pmod{11} = 9 \implies \text{slot } 9$
  - $96 \pmod{11} = 8 \implies \text{Collision! } i=1 \implies (8 + 1^2) \pmod{11} = 9 \text{ (Collision!)} \implies i=2 \implies (8 + 2^2) \pmod{11} = 1 \implies \text{slot } 1$
- **Secondary Clustering**: Keys hashing to the same initial address will follow the exact same probing path. Furthermore, it is only guaranteed to find an empty slot if $N$ is prime and $\lambda < 0.5$.

#### 3. Double Hashing
Uses a secondary hash function $f(K)$ to determine the probe step size. This eliminates both primary and secondary clustering.
- **Formula**:
  $$h_i(K) = (H(K) + i \cdot f(K)) \pmod N$$
  where $i$ is the collision count ($i = 0, 1, 2, \dots$).
  - Primary Hash: $H(K) = K \pmod N$
  - Secondary Hash: $f(K) = R - (K \pmod R)$, where $R$ is a prime number smaller than $N$ ($R < N$). Note that $f(K)$ must never return $0$ (otherwise, the probe step size would be $0$, causing an infinite loop on the same slot).
- **Example (from slides)**: $N = 11, R = 7$, insert $75, 152, 171, 38, 211, 18, 189$
  - $75 \pmod{11} = 9 \implies \text{slot } 9$
  - $152 \pmod{11} = 9 \implies \text{Collision! } 152\%7 = 5 \implies f(152) = 7 - 5 = 2$
    - $h_1(152) = (9 + 1 \cdot 2) \pmod{11} = 11 \pmod{11} = 0 \implies \text{slot } 0$

---

### C. Lazy Deletion
In Open Addressing, if we delete an element from slot $x$ and simply set it to `empty`, we break the probing path for other elements inserted after it that collided at $x$. 
- **Solution**: **Lazy Deletion**. Instead of emptying the slot, we mark it with a special state flag (e.g., `DELETED` or `-1`).
- **During Search**: We continue probing past `DELETED` slots.
- **During Insertion**: We can overwrite a `DELETED` slot to save space.

---

### D. Rehashing
When the load factor $\lambda$ exceeds a threshold (typically $0.5$ for Open Addressing or $0.75 - 1.0$ for Separate Chaining), search performance degrades significantly. 
- **Rehashing** is the process of allocating a new array of larger size (typically the next prime number larger than $2N$), and re-inserting all existing elements into the new array using the new hash function.
- **Slide example**: Increasing table size from $9$ to $19$ to resolve insertion collision of $1989$.

---

## 5. Templated C++ Implementations

Here are the complete, clean, and robust C++ implementations of both **Separate Chaining** and **Open Addressing (Double Hashing)**.

### A. Separate Chaining Hash Table

```cpp
#ifndef SEPARATE_CHAINING_HPP
#define SEPARATE_CHAINING_HPP

#include <vector>
#include <list>
#include <algorithm>
#include <stdexcept>
#include <iostream>

template <typename K, typename V>
class SeparateChainingHashMap {
private:
    struct HashNode {
        K key;
        V value;
        HashNode(const K& k, const V& v) : key(k), value(v) {}
    };

    std::vector<std::list<HashNode>> table;
    size_t numElements;
    size_t tableSize;
    const double maxLoadFactor = 0.75;

    size_t hashFunction(const K& key) const {
        return std::hash<K>{}(key) % tableSize;
    }

    bool isPrime(size_t n) const {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (size_t i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    size_t nextPrime(size_t n) const {
        if (n % 2 == 0) n++;
        while (!isPrime(n)) {
            n += 2;
        }
        return n;
    }

    void rehash() {
        size_t oldSize = tableSize;
        tableSize = nextPrime(oldSize * 2);
        std::vector<std::list<HashNode>> oldTable = std::move(table);

        table.resize(tableSize);
        numElements = 0;

        for (const auto& chain : oldTable) {
            for (const auto& node : chain) {
                insert(node.key, node.value);
            }
        }
    }

public:
    explicit SeparateChainingHashMap(size_t initialCapacity = 11) 
        : numElements(0) {
        tableSize = isPrime(initialCapacity) ? initialCapacity : nextPrime(initialCapacity);
        table.resize(tableSize);
    }

    ~SeparateChainingHashMap() = default;

    // Mutators
    void insert(const K& key, const V& value) {
        if (getLoadFactor() > maxLoadFactor) {
            rehash();
        }

        size_t idx = hashFunction(key);
        for (auto& node : table[idx]) {
            if (node.key == key) {
                node.value = value; // Update existing key
                return;
            }
        }

        table[idx].emplace_back(key, value);
        numElements++;
    }

    bool remove(const K& key) {
        size_t idx = hashFunction(key);
        auto& chain = table[idx];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->key == key) {
                chain.erase(it);
                numElements--;
                return true;
            }
        }
        return false;
    }

    // Accessors
    bool contains(const K& key) const {
        size_t idx = hashFunction(key);
        for (const auto& node : table[idx]) {
            if (node.key == key) {
                return true;
            }
        }
        return false;
    }

    V& get(const K& key) {
        size_t idx = hashFunction(key);
        for (auto& node : table[idx]) {
            if (node.key == key) {
                return node.value;
            }
        }
        throw std::out_of_range("Key not found in hash table");
    }

    const V& get(const K& key) const {
        size_t idx = hashFunction(key);
        for (auto& node : table[idx]) {
            if (node.key == key) {
                return node.value;
            }
        }
        throw std::out_of_range("Key not found in hash table");
    }

    size_t size() const { return numElements; }
    size_t capacity() const { return tableSize; }
    bool empty() const { return numElements == 0; }
    double getLoadFactor() const { return static_cast<double>(numElements) / tableSize; }
    
    void printTable() const {
        for (size_t i = 0; i < tableSize; ++i) {
            std::cout << "[" << i << "]: ";
            for (const auto& node : table[i]) {
                std::cout << "{" << node.key << ": " << node.value << "} -> ";
            }
            std::cout << "nullptr\n";
        }
    }
};

#endif
```

---

### B. Open Addressing Hash Table (Double Hashing with Lazy Deletion)

```cpp
#ifndef OPEN_ADDRESSING_HPP
#define OPEN_ADDRESSING_HPP

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>

enum SlotState { EMPTY, OCCUPIED, DELETED };

template <typename K, typename V>
class OpenAddressingHashMap {
private:
    struct HashEntry {
        K key;
        V value;
        SlotState state;
        HashEntry() : state(EMPTY) {}
    };

    std::vector<HashEntry> table;
    size_t numElements;
    size_t tableSize;
    size_t secondaryPrime; // Prime R for double hashing
    const double maxLoadFactor = 0.5;

    bool isPrime(size_t n) const {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (size_t i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    size_t nextPrime(size_t n) const {
        if (n % 2 == 0) n++;
        while (!isPrime(n)) {
            n += 2;
        }
        return n;
    }

    size_t getSecondaryPrime(size_t size) const {
        for (size_t i = size - 1; i > 1; --i) {
            if (isPrime(i)) return i;
        }
        return 3;
    }

    size_t hash1(const K& key) const {
        return std::hash<K>{}(key) % tableSize;
    }

    size_t hash2(const K& key) const {
        size_t hashed = std::hash<K>{}(key);
        return secondaryPrime - (hashed % secondaryPrime);
    }

    void rehash() {
        size_t oldSize = tableSize;
        std::vector<HashEntry> oldTable = std::move(table);

        tableSize = nextPrime(oldSize * 2);
        secondaryPrime = getSecondaryPrime(tableSize);
        table.assign(tableSize, HashEntry());
        numElements = 0;

        for (const auto& entry : oldTable) {
            if (entry.state == OCCUPIED) {
                insert(entry.key, entry.value);
            }
        }
    }

public:
    explicit OpenAddressingHashMap(size_t initialCapacity = 11) 
        : numElements(0) {
        tableSize = isPrime(initialCapacity) ? initialCapacity : nextPrime(initialCapacity);
        secondaryPrime = getSecondaryPrime(tableSize);
        table.resize(tableSize);
    }

    ~OpenAddressingHashMap() = default;

    // Mutators
    void insert(const K& key, const V& value) {
        if (getLoadFactor() > maxLoadFactor) {
            rehash();
        }

        size_t h1 = hash1(key);
        size_t step = hash2(key);
        size_t idx = h1;
        int firstDeletedIndex = -1;

        for (size_t i = 0; i < tableSize; ++i) {
            if (table[idx].state == EMPTY) {
                size_t targetIdx = (firstDeletedIndex != -1) ? firstDeletedIndex : idx;
                table[targetIdx].key = key;
                table[targetIdx].value = value;
                table[targetIdx].state = OCCUPIED;
                numElements++;
                return;
            }
            else if (table[idx].state == OCCUPIED) {
                if (table[idx].key == key) {
                    table[idx].value = value; // Update key value
                    return;
                }
            }
            else if (table[idx].state == DELETED) {
                if (firstDeletedIndex == -1) {
                    firstDeletedIndex = idx;
                }
            }
            idx = (h1 + (i + 1) * step) % tableSize;
        }

        if (firstDeletedIndex != -1) {
            table[firstDeletedIndex].key = key;
            table[firstDeletedIndex].value = value;
            table[firstDeletedIndex].state = OCCUPIED;
            numElements++;
        } else {
            throw std::runtime_error("Hash table is full");
        }
    }

    bool remove(const K& key) {
        size_t h1 = hash1(key);
        size_t step = hash2(key);
        size_t idx = h1;

        for (size_t i = 0; i < tableSize; ++i) {
            if (table[idx].state == EMPTY) {
                return false;
            }
            if (table[idx].state == OCCUPIED && table[idx].key == key) {
                table[idx].state = DELETED;
                numElements--;
                return true;
            }
            idx = (h1 + (i + 1) * step) % tableSize;
        }
        return false;
    }

    // Accessors
    bool contains(const K& key) const {
        size_t h1 = hash1(key);
        size_t step = hash2(key);
        size_t idx = h1;

        for (size_t i = 0; i < tableSize; ++i) {
            if (table[idx].state == EMPTY) {
                return false;
            }
            if (table[idx].state == OCCUPIED && table[idx].key == key) {
                return true;
            }
            idx = (h1 + (i + 1) * step) % tableSize;
        }
        return false;
    }

    V& get(const K& key) {
        size_t h1 = hash1(key);
        size_t step = hash2(key);
        size_t idx = h1;

        for (size_t i = 0; i < tableSize; ++i) {
            if (table[idx].state == EMPTY) {
                break;
            }
            if (table[idx].state == OCCUPIED && table[idx].key == key) {
                return table[idx].value;
            }
            idx = (h1 + (i + 1) * step) % tableSize;
        }
        throw std::out_of_range("Key not found in hash table");
    }

    const V& get(const K& key) const {
        size_t h1 = hash1(key);
        size_t step = hash2(key);
        size_t idx = h1;

        for (size_t i = 0; i < tableSize; ++i) {
            if (table[idx].state == EMPTY) {
                break;
            }
            if (table[idx].state == OCCUPIED && table[idx].key == key) {
                return table[idx].value;
            }
            idx = (h1 + (i + 1) * step) % tableSize;
        }
        throw std::out_of_range("Key not found in hash table");
    }

    size_t size() const { return numElements; }
    size_t capacity() const { return tableSize; }
    bool empty() const { return numElements == 0; }
    double getLoadFactor() const { return static_cast<double>(numElements) / tableSize; }

    void printTable() const {
        for (size_t i = 0; i < tableSize; ++i) {
            std::cout << "[" << i << "]: ";
            if (table[i].state == OCCUPIED) {
                std::cout << "OCCUPIED {" << table[i].key << ": " << table[i].value << "}\n";
            } else if (table[i].state == DELETED) {
                std::cout << "DELETED\n";
            } else {
                std::cout << "EMPTY\n";
            }
        }
    }
};

#endif
```

---

## 6. LeetCode Practice Problems

This section catalogs the LeetCode practice problems implemented in the repository, organized by difficulty.

### Easy Problems

1. **Two Sum** (LeetCode 1)
   - **File Link**: [no1_islands.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/5_HASH/no1_twosum.cpp)
   - **Concept**: Finding two elements that sum to a target value.
   - **Approach**: Uses a single-pass hash map to map each number to its index. For each number, it checks if `target - num` already exists in the map.
   - **Complexities**: Time: $O(N)$, Space: $O(N)$

2. **Design HashMap** (LeetCode 706)
   - **File Link**: [no2_course.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/5_HASH/no2_hashmap.cpp)
   - **Concept**: Implementing a hash map from scratch.
   - **Approach**: Uses Separate Chaining with a vector of lists to handle collisions, demonstrating standard hash bucket operations.
   - **Complexities**: Time: $O(1)$ average, Space: $O(N + K)$ where $K$ is the bucket size.

3. **First Unique Character in a String** (LeetCode 387)
   - **File Link**: [no3_warshall.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/5_HASH/no3_unique_char.cpp)
   - **Concept**: Finding the index of the first non-repeating character.
   - **Approach**: Uses a frequency hash map (or fixed-size array since character space is small) to count character occurrences, then scans the string a second time to find the first character with a count of 1.
   - **Complexities**: Time: $O(N)$, Space: $O(1)$ (since alphabet size is constant, 26 characters).

---

### Medium (Advanced) Problems

4. **LRU Cache** (LeetCode 146)
   - **File Link**: [no4_clone.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/5_HASH/no4_lru.cpp)
   - **Code Reference**: [LRUCache](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/5_HASH/no4_lru.cpp#L20)
   - **Concept**: Cache eviction policy (Least Recently Used).
   - **Approach**: Combines a hash map (`std::unordered_map`) and a doubly linked list. The hash map maps keys to node pointers in the doubly linked list, enabling $O(1)$ access. The doubly linked list keeps track of the element usage order.
   - **Eviction Mechanics**:
     - On a `get` or `put` of an existing key: the corresponding node is moved to the head (Most Recently Used).
     - On a `put` of a new key when capacity is exceeded: the node at the tail (Least Recently Used) is popped from both the list and the hash map.
   - **Complexities**: Time: $O(1)$ average for both `get` and `put`, Space: $O(C)$ where $C$ is the cache capacity.

5. **Longest Consecutive Sequence** (LeetCode 128)
   - **File Link**: [no5_redundant.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/5_HASH/no5_consecutive.cpp)
   - **Code Reference**: [Solution::longestConsecutive](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/5_HASH/no5_consecutive.cpp#L17)
   - **Concept**: Finding the length of the longest sequence of consecutive integers.
   - **Approach**: Inserts all elements into an `std::unordered_set` for $O(1)$ lookup. It then iterates through the elements. For each element `num`, it checks if it is the start of a sequence by verifying that `num - 1` is not in the set. If it is the start, it sequentially checks for `num + 1`, `num + 2`, etc., computing the sequence length.
   - **Optimization**: The `num - 1` check ensures that the inner loop is only entered for the first element of any sequence. Therefore, each element is processed at most twice overall, yielding a strict linear time complexity.
   - **Complexities**: Time: $O(N)$ average, Space: $O(N)$

6. **Group Anagrams** (LeetCode 49)
   - **File Link**: [no6_group_anagrams.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/5_HASH/no6_group_anagrams.cpp)
   - **Code Reference**: [Solution::groupAnagrams](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/5_HASH/no6_group_anagrams.cpp#L19)
   - **Concept**: Grouping character-frequency equivalent strings.
   - **Approach**: Sorts each string to create a unique anagram key, then maps each key to its corresponding list of original strings in a hash map.
   - **Complexities**: Time: $O(N \cdot L \log L)$ average, Space: $O(N \cdot L)$ where $N$ is the number of strings and $L$ is the max string length.

7. **Subarray Sums Divisible by K** (LeetCode 974)
   - **File Link**: [no7_subarrays_divisible_by_k.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/5_HASH/no7_subarrays_divisible_by_k.cpp)
   - **Code Reference**: [Solution::subarraysDivByK](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/5_HASH/no7_subarrays_divisible_by_k.cpp#L17)
   - **Concept**: Frequency counting of prefix sum remainders.
   - **Approach**: Uses cumulative sum modulo $K$ (adjusting for negative remainders in C++: `(sum % k + k) % k`). We store prefix sum remainder frequencies in a vector of size $K$. If a remainder has been seen $C$ times, it implies there are $C$ subarrays ending at the current index whose sum is divisible by $K$.
   - **Complexities**: Time: $O(N)$ average, Space: $O(K)$


