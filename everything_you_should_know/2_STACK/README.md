# Study Guide: Stack Data Structure

A comprehensive study guide on the **Stack Abstract Data Type (Stack ADT)**, its implementations, complexities, applications, and C++ implementations based on course material.

---

## 1. Theoretical Foundations & Stack ADT

A **Stack** is an abstract data type (ADT) that models a linear collection of elements with a strict insertion and removal discipline.

### Core Characteristics:
- **Last In, First Out (LIFO):** The last element added to the stack is the first one to be removed.
- **Single-End Access:** All insertions (pushes) and deletions (pops) are performed at one designated end called the **top**. Only the element at the top is directly accessible.
- **Linear Ordering:** Elements are stored in a sequential structure.

### Core Stack Operations:
- `push(data)`: Inserts an element onto the top of the stack.
- `pop()`: Removes and returns the top element of the stack.
- `top()` (or `peek()`): Returns the top element without removing it.
- `empty()`: Returns `true` if the stack contains no elements, otherwise `false`.
- `full()`: Returns `true` if the stack is at its maximum storage capacity (relevant for fixed-size arrays).

### Exceptional Conditions:
1. **Stack Underflow:** Attempting to call `pop()` or `top()` on an empty stack. In C++ systems, this leads to undefined behavior or assertions unless guarded.
2. **Stack Overflow:** Attempting to call `push()` on a full stack (when using a fixed-capacity representation).

---

## 2. Implementation Paradigms & Complexity Analysis

Stacks can be implemented using either **Singly Linked Lists** or **One-Ended Arrays**. The optimal target time complexity for all stack operations is $\mathcal{O}(1)$.

### Comparison of Implementations:

| Operation | Singly Linked List (at Head) | Array (at Back / $n$-th) | Array (at Front / 1st) |
| :--- | :--- | :--- | :--- |
| **Push / Insert** | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | $\mathcal{O}(n)$ (due to shifts) |
| **Pop / Erase** | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | $\mathcal{O}(n)$ (due to shifts) |
| **Top / Find** | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ |
| **Space Overhead** | $\mathcal{O}(n)$ (pointers per node) | $\mathcal{O}(1)$ (fixed size / array capacity) | $\mathcal{O}(1)$ |

#### Why One-Ended Array Stack uses the Back:
For a standard array, adding or removing elements at the *front* (index 0) requires shifting all other elements, resulting in a time complexity of $\mathcal{O}(n)$. However, operations at the *back* (index `top - 1`) do not require shifting and run in $\mathcal{O}(1)$ amortized time.

---

## 3. C++ Class Implementations

Below are two implementations:
1. **The Slide-Specific Stack-as-Array Class:** Mimicking the unique layout in slide code where `Array[0]` stores the capacity of the stack, and elements are indexed starting at 1.
2. **A Standard Generic Templated Stack Class:** A robust, professional, templated stack implementation.

### Implementation 1: Slide-Specific Stack Class
In this implementation (from slide pages 11-15):
- `top` tracks the index of the top element (initialized to 0).
- `Array[0]` stores the capacity limit (in the slides, initialized to 4).
- The array has size 5, meaning the user data is stored at indices `1` to `top`.

```cpp
#include <iostream>

template <typename Type>
class SlideStack {
public:
    int top;
    Type Array[5];

    // Constructor: slide specifies Array[0] = 4 to hold capacity
    SlideStack() : top(0) {
        Array[0] = static_cast<Type>(4); 
    }

    // Checks if the stack is empty (top == 0)
    bool empty() const {
        return top == 0;
    }

    // Checks if the stack is full (top == capacity stored at Array[0])
    bool full() const {
        return top == static_cast<int>(Array[0]);
    }

    // Pushes an element onto the stack if not full
    void push(Type data) {
        if (!full()) {
            top++;
            Array[top] = data;
        } else {
            std::cerr << "Stack Overflow!" << std::endl;
        }
    }

    // Pops and returns the top element if not empty
    Type pop() {
        if (!empty()) {
            Type temp = Array[top];
            top--;
            return temp;
        }
        std::cerr << "Stack Underflow!" << std::endl;
        return static_cast<Type>(-1); // Guard return
    }

    // Prints stack elements from bottom to top
    void print() const {
        for (int i = 1; i <= top; ++i) {
            std::cout << Array[i] << " ";
        }
        std::cout << "\n";
    }
};
```

### Implementation 2: Modern Generic Templated Stack (Dynamic Array)
A clean, robust C++ class using dynamic memory allocation and standard 0-based indexing.

```cpp
#include <iostream>
#include <stdexcept>

template <typename Type>
class Stack {
private:
    Type* array;
    int stack_size;
    int array_capacity;

    void resize(int new_capacity) {
        Type* temp = new Type[new_capacity];
        for (int i = 0; i < stack_size; ++i) {
            temp[i] = array[i];
        }
        delete[] array;
        array = temp;
        array_capacity = new_capacity;
    }

public:
    // Constructor
    explicit Stack(int capacity = 10) : stack_size(0), array_capacity(capacity) {
        if (capacity <= 0) {
            throw std::invalid_argument("Capacity must be positive");
        }
        array = new Type[array_capacity];
    }

    // Destructor
    ~Stack() {
        delete[] array;
    }

    // Copy Constructor
    Stack(const Stack& other) : stack_size(other.stack_size), array_capacity(other.array_capacity) {
        array = new Type[array_capacity];
        for (int i = 0; i < stack_size; ++i) {
            array[i] = other.array[i];
        }
    }

    // Assignment Operator
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            delete[] array;
            stack_size = other.stack_size;
            array_capacity = other.array_capacity;
            array = new Type[array_capacity];
            for (int i = 0; i < stack_size; ++i) {
                array[i] = other.array[i];
            }
        }
        return *this;
    }

    // Push operation (amortized O(1))
    void push(const Type& data) {
        if (stack_size == array_capacity) {
            resize(array_capacity * 2);
        }
        array[stack_size++] = data;
    }

    // Pop operation (O(1))
    void pop() {
        if (empty()) {
            throw std::underflow_error("Pop called on empty stack");
        }
        stack_size--;
    }

    // Top accessor (O(1))
    const Type& top() const {
        if (empty()) {
            throw std::underflow_error("Top called on empty stack");
        }
        return array[stack_size - 1];
    }

    // Size accessor (O(1))
    int size() const {
        return stack_size;
    }

    // Check if empty (O(1))
    bool empty() const {
        return stack_size == 0;
    }
};
```

---

## 4. Stack Applications

### A. Parsing Parentheses and Brackets
Matching symmetric delimiters (e.g., `( )`, `[ ]`, `{ }`).
- For every opening symbol, push to stack.
- For every closing symbol, pop the top of the stack and check for compatibility. If stack is empty or symbols mismatch, expression is invalid.

### B. XHTML / XML Document Parsing
XML markup consists of nested opening tags (e.g., `<html>`) and closing tags (e.g., `</html>`). The rules require tags to be balanced and nested.

#### XHTML Parsing Dry Run Trace
Input Document:
```html
<html>
 <head><title>Hello</title></head>
 <body><p>This appears in the <i>browser</i>.</p></body>
</html>
```

| Step | Parsed Tag | Action | Stack State (Bottom $\rightarrow$ Top) | Matches Top? / Notes |
| :--- | :---: | :---: | :--- | :--- |
| 1 | `<html>` | Push | `[ <html> ]` | - |
| 2 | `<head>` | Push | `[ <html>, <head> ]` | - |
| 3 | `<title>` | Push | `[ <html>, <head>, <title> ]` | - |
| 4 | `</title>` | Pop & Match | `[ <html>, <head> ]` | Matches `<title>` $\checkmark$ |
| 5 | `</head>` | Pop & Match | `[ <html> ]` | Matches `<head>` $\checkmark$ |
| 6 | `<body>` | Push | `[ <html>, <body> ]` | - |
| 7 | `<p>` | Push | `[ <html>, <body>, <p> ]` | - |
| 8 | `<i>` | Push | `[ <html>, <body>, <p>, <i> ]` | - |
| 9 | `</i>` | Pop & Match | `[ <html>, <body>, <p> ]` | Matches `<i>` $\checkmark$ |
| 10 | `</p>` | Pop & Match | `[ <html>, <body> ]` | Matches `<p>` $\checkmark$ |
| 11 | `</body>` | Pop & Match | `[ <html> ]` | Matches `<body>` $\checkmark$ |
| 12 | `</html>` | Pop & Match | `[ ]` | Matches `<html>` $\checkmark$ (Empty Stack = Success) |

---

### C. Reverse-Polish Notation (RPN) / Postfix Evaluation
In **Postfix notation**, operators follow their operands (e.g., `3 4 +` instead of `3 + 4`). This removes operator precedence ambiguity and eliminates the need for parentheses.

#### RPN Evaluation Stack Trace
Evaluation of expression:
$$\text{1  2  3  +  4  5  6  *  –  7  *  +  –  8  9  *  +}$$

| Step | Token | Type | Stack Action | Stack State (Bottom $\rightarrow$ Top) | Computations / Notes |
| :--- | :---: | :---: | :--- | :--- | :--- |
| 1 | `1` | Operand | Push `1` | `[ 1 ]` | |
| 2 | `2` | Operand | Push `2` | `[ 1, 2 ]` | |
| 3 | `3` | Operand | Push `3` | `[ 1, 2, 3 ]` | |
| 4 | `+` | Operator | Pop `3` & `2`, Push `2 + 3 = 5` | `[ 1, 5 ]` | $2 + 3 = 5$ |
| 5 | `4` | Operand | Push `4` | `[ 1, 5, 4 ]` | |
| 6 | `5` | Operand | Push `5` | `[ 1, 5, 4, 5 ]` | |
| 7 | `6` | Operand | Push `6` | `[ 1, 5, 4, 5, 6 ]` | |
| 8 | `*` | Operator | Pop `6` & `5`, Push `5 * 6 = 30` | `[ 1, 5, 4, 30 ]` | $5 \times 6 = 30$ |
| 9 | `–` | Operator | Pop `30` & `4`, Push `4 - 30 = -26` | `[ 1, 5, -26 ]` | $4 - 30 = -26$ |
| 10 | `7` | Operand | Push `7` | `[ 1, 5, -26, 7 ]` | |
| 11 | `*` | Operator | Pop `7` & `-26`, Push `-26 * 7 = -182` | `[ 1, 5, -182 ]` | $-26 \times 7 = -182$ |
| 12 | `+` | Operator | Pop `-182` & `5`, Push `5 + (-182) = -177` | `[ 1, -177 ]` | $5 + (-182) = -177$ |
| 13 | `–` | Operator | Pop `-177` & `1`, Push `1 - (-177) = 178` | `[ 178 ]` | $1 - (-177) = 178$ |
| 14 | `8` | Operand | Push `8` | `[ 178, 8 ]` | |
| 15 | `9` | Operand | Push `9` | `[ 178, 8, 9 ]` | |
| 16 | `*` | Operator | Pop `9` & `8`, Push `8 * 9 = 72` | `[ 178, 72 ]` | $8 \times 9 = 72$ |
| 17 | `+` | Operator | Pop `72` & `178`, Push `178 + 72 = 250` | `[ 250 ]` | $178 + 72 = 250$ |

**Final Evaluated Value:** **250**

---

### D. Other Key Applications
- **Function Call Tracking:** Activations records (local variables, parameters, return addresses) are pushed onto the call stack when a function is called and popped when it returns.
- **Undo / Redo Buffers:** Storing state history snapshots in a stack allows reverting back step-by-step.

---

## 5. Standard Template Library (STL) `std::stack`

In modern C++, `std::stack` acts as a **container adapter**, wrapping an underlying sequence container (by default `std::deque`, but can be `std::vector` or `std::list`).

### Declaration:
```cpp
template <typename T, typename Container = std::deque<T>>
class stack;
```

### Essential STL Methods:
- `bool empty() const`: Returns whether the stack is empty.
- `size_type size() const`: Returns the number of elements in the stack.
- `reference top()` / `const_reference top() const`: Returns a reference to the top element.
- `void push(const value_type& val)`: Inserts element at the top.
- void pop(): Removes (erases) the top element (does *not* return it).

---

## 6. LeetCode Practice & Solutions

Below is the curated list of LeetCode problems covering the Stack data structure, ranging from basic bracket matching to advanced monotonic stack applications.

| # | Problem Name | Difficulty | Core Concept / Technique | Source Code Link |
| :-: | :--- | :--- | :--- | :--- |
| 1 | **Valid Parentheses** (LeetCode 20) | Easy | Push open brackets, match & pop closing brackets | [no1_parentheses.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/2_STACK/no1_parentheses.cpp) |
| 2 | **Evaluate Reverse Polish Notation** (LeetCode 150) | Medium | Push operands, pop twice on operator & push result | [no2_rpn.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/2_STACK/no2_rpn.cpp) |
| 3 | **Min Stack** (LeetCode 155) | Medium | Parallel value stack & min-value tracker stack | [no3_minstack.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/2_STACK/no3_minstack.cpp) |
| 4 | **Longest Valid Parentheses** (LeetCode 32) | Hard | Stack indices tracking for valid substrings | [no4_longest_parentheses.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/2_STACK/no4_longest_parentheses.cpp) |
| 5 | **Largest Rectangle in Histogram** (LeetCode 84) | Hard | Monotonic increasing index stack | [no5_histogram.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/2_STACK/no5_histogram.cpp) |
| 6 | **Daily Temperatures** (LeetCode 739) | Medium | Monotonic decreasing index stack to track next warmer day | [no6_daily_temperatures.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/2_STACK/no6_daily_temperatures.cpp) |
| 7 | **Remove Duplicate Letters** (LeetCode 316) | Medium | Monotonic lexicographical stack with character counter & presence tracker | [no7_remove_duplicate_letters.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/2_STACK/no7_remove_duplicate_letters.cpp) |

---

### Detailed Walkthroughs of Advanced Problems

#### LeetCode 32: Longest Valid Parentheses
- **Problem Statement:** Given a string containing just the characters `'('` and `')'`, find the length of the longest valid (well-formed) parentheses substring.
- **Approach (Index Tracking Stack):**
  Instead of storing characters on the stack, we store the **indices** of the characters. This provides positional information necessary to calculate the length of valid substrings.
  1. We initialize the stack with `-1` as a dummy element. This represents the boundary index before the start of the string.
  2. We iterate through the string.
     - If we see `'(''`, we push its index onto the stack.
     - If we see `')'`, we pop the top index from the stack.
       - If the stack is now empty, it means the current closing bracket is unmatched. We push the current index onto the stack to act as the new boundary.
       - If the stack is not empty, the current valid substring length is the difference between the current index `i` and the index now at the top of the stack (`i - stack.top()`). We update the maximum length.
- **Complexity:**
  - **Time Complexity:** $\mathcal{O}(N)$ where $N$ is the length of the string. We perform a single pass over the string, pushing and popping indices.
  - **Space Complexity:** $\mathcal{O}(N)$ in the worst case to store the indices of the brackets.

#### LeetCode 84: Largest Rectangle in Histogram
- **Problem Statement:** Given an array of integers `heights` representing a histogram where each bar has a width of $1$, find the area of the largest rectangle in the histogram.
- **Approach (Monotonic Stack):**
  To find the largest rectangle, we want to determine the maximum width for each bar acting as the shortest/limiting height of a rectangle. This is equivalent to finding the first bar to the left and the first bar to the right that is strictly shorter than the current bar.
  1. We maintain a **monotonic increasing stack** of indices. This guarantees that heights corresponding to the indices on the stack are always sorted in non-decreasing order.
  2. We append a dummy height of `0` at the end of the heights array. This guarantees that all elements in the stack will be popped and processed by the end of the iteration.
  3. We iterate through the array. For each bar:
     - While the stack is not empty and the current height is less than the height of the bar at `stack.top()`:
       - Pop the top index. This index represents the rectangle's height ($H$).
       - The right boundary is the current index `i` (exclusive).
       - The left boundary is the new `stack.top()` (exclusive), or `-1` if the stack is empty.
       - Width ($W$) is calculated as: `i - left_boundary - 1`.
       - Compute area: $A = H \times W$ and update the maximum area.
     - Push the current index onto the stack.
- **Complexity:**
  - **Time Complexity:** $\mathcal{O}(N)$ where $N$ is the number of bars. Each bar index is pushed onto the stack exactly once and popped at most once.
  - **Space Complexity:** $\mathcal{O}(N)$ to store the indices on the stack and hold the extended heights.

#### LeetCode 739: Daily Temperatures
- **Problem Statement:** Given an array of integers `temperatures` representing the daily temperatures, return an array `answer` such that `answer[i]` is the number of days you have to wait after the `i`-th day to get a warmer temperature. If there is no future day for which this is possible, keep `answer[i] == 0` instead.
- **Approach (Monotonic Decreasing Stack):**
  We maintain a **monotonic decreasing stack** containing the indices of days. The temperatures corresponding to these indices are in strictly decreasing order.
  1. We iterate through the `temperatures` array from left to right.
  2. For each day `i`, while the stack is not empty and the current day's temperature `temperatures[i]` is greater than the temperature at the index stored at the top of the stack (`temperatures[stack.top()]`):
     - Pop the top index, say `prev_index`.
     - Calculate the waiting days: `answer[prev_index] = i - prev_index`.
  3. Push the current day's index `i` onto the stack.
  4. Any indices remaining in the stack at the end have no warmer day in the future, so their answer remains `0` (default initialized).
- **Complexity:**
  - **Time Complexity:** $\mathcal{O}(N)$ where $N$ is the number of days. Each index is pushed and popped at most once.
  - **Space Complexity:** $\mathcal{O}(N)$ to store the indices in the stack in the worst-case scenario.

#### LeetCode 316: Remove Duplicate Letters
- **Problem Statement:** Given a string `s`, remove duplicate letters so that every letter appears once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.
- **Approach (Monotonic Lexicographical Stack):**
  We build the result subsequence character-by-character using a stack, maintaining it in the smallest lexicographical order possible.
  1. We compute the total frequency of each character in `s` to know if a character will appear later.
  2. We keep a `visited` set or boolean array to track if a character is already in our stack (to maintain uniqueness).
  3. We iterate through the string `s`. For each character `c`:
     - Decrement `c`'s remaining frequency.
     - If `c` is already in the stack, we skip it.
     - While the stack is not empty, the top of the stack `stack.top()` is lexicographically greater than `c` (`stack.top() > c`), and the top character will appear again later in the string (`remaining_count[stack.top()] > 0`):
       - Pop `stack.top()` and mark it as not visited.
     - Push `c` onto the stack and mark it as visited.
  4. The elements in the stack from bottom to top form the lexicographically smallest subsequence of unique letters.
- **Complexity:**
  - **Time Complexity:** $\mathcal{O}(N)$ where $N$ is the length of the string. Each character is pushed and popped from the stack at most once.
  - **Space Complexity:** $\mathcal{O}(1)$ auxiliary space, since the stack and tables contain at most $26$ distinct lowercase English characters.
