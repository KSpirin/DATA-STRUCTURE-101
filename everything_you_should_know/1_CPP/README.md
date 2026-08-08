# C++ Fundamentals & Data Structure Core Concepts

Welcome to the ultimate C++ study guide designed for Data Structures and Algorithms. C++ is a powerful, high-performance, compiled language that provides low-level memory access, object-oriented capabilities, and generic programming via templates. This guide explains all key language design aspects, compiler rules, and implementation practices from your lecture slides.

---

## 🎯 THE CORE
## 1. Theoretical Explanations

### 1.1 Input & Output (I/O) Streams
In C++, standard input and output are handled via streams. Output printing is done by overloading the **left-shift operator** `<<` with the `std::ostream` object `std::cout` (console output).
* **How Operator Overloading Works**: The statement `cout << "The square of 3 is " << sqr(3) << endl;` is evaluated from left to right as:
  ```cpp
  ((cout << "The square of 3 is ") << sqr(3)) << endl;
  ```
  The operator `<<` returns a reference to the `ostream` object (`std::cout`), allowing chaining. At the compiler level, this is equivalent to nested function calls:
  ```cpp
  operator<<(operator<<(operator<<(cout, "The square of 3 is "), sqr(3)), endl);
  ```
* **Input**: Standard input is read using the **right-shift operator** `>>` with the `std::cin` object (console input):
  ```cpp
  int x, y;
  cin >> x >> y; // Reads two whitespace-separated values
  ```

### 1.2 Control Statements & Arrays
* **Control Statements**: C++ supports standard flow control structures:
  * Selection: `if-else if-else` statements.
  * Loops: `for` loops, `while` loops, and `do-while` loops (which run at least once before checking the condition).
* **Arrays**: Memory is allocated contiguously.
  * **Capacity vs. Size**: 
    * **Capacity**: The maximum number of entries the array can hold (fixed at allocation time).
    * **Size**: The number of *useful* or active entries currently stored in the array.
  * Access is 0-indexed. Example of array declaration and loop-based manipulation:
    ```cpp
    const int N = 10;
    int arr[N];
    arr[0] = 1;
    for (int i = 1; i < N; ++i) {
        arr[i] = 2 * arr[i - 1] + 1;
    }
    ```

### 1.3 Recursion
Recursion is a method where a function calls itself to solve a smaller subproblem. Each recursive call adds a frame to the execution stack containing local variables and return addresses.
* Example from notes:
  ```cpp
  int func(int x) {
      if (x < 1) return 0;
      else return x + func(x - 1);
  }
  ```
  * **Trace of `func(5)`**:
    $$\text{func}(5) = 5 + \text{func}(4)$$
    $$\text{func}(4) = 4 + \text{func}(3)$$
    $$\text{func}(3) = 3 + \text{func}(2)$$
    $$\text{func}(2) = 2 + \text{func}(1)$$
    $$\text{func}(1) = 1 + \text{func}(0)$$
    $$\text{func}(0) = 0 \text{ (Base Case)}$$
    Summing back up: $1+0=1 \to 2+1=3 \to 3+3=6 \to 4+6=10 \to 5+10=15$.

### 1.4 The C++ Preprocessor
The preprocessor is a program that processes source files before compilation. Commands starting with `#` in the first column are **preprocessor directives**.
* **Lexical Substitutions**: The preprocessor performs basic text substitution and does not verify syntax.
* **Compilation Pipeline**:
  $$\text{Source Code (.cpp/.h)} \longrightarrow \text{Preprocessor} \longrightarrow \text{Compiler (g++)} \longrightarrow \text{Object Code (.o)} \longrightarrow \text{Linker} \longrightarrow \text{Executable}$$
* **Header Guards**: Crucial to prevent duplicate compilation and "multiple definition" errors when a header file is included multiple times.
  ```cpp
  #ifndef SINGLE_LIST_H
  #define SINGLE_LIST_H
  
  // Declarations and definitions...
  
  #endif
  ```

### 1.5 Libraries & Unit of Compilation
* **Unit of Compilation**: The basic unit is the `.cpp` file. Each `.cpp` file compiles into an independent object file. Only files containing the `int main()` function can compile into an executable.
* **Include Search Paths**:
  * `#include <iostream>`: Search in system directories (standard libraries shipped with the compiler).
  * `#include "Single_list.h"`: Search in the current directory (user-defined local header files).
* **Header-Only Implementations**: In template-heavy libraries, definitions are usually kept in the header file because C++ compilers instantiate templates at compile time when they see the type parameters.

### 1.6 Namespaces
A namespace creates a declarative region to prevent naming conflicts in large projects.
```cpp
namespace ca_uwaterloo_dwharder {
    int n = 4;
    void init() { /* ... */ }
}
```
Accessing members:
1. **Fully Qualified Name**: `ca_uwaterloo_dwharder::init();`
2. **Using Directive**: `using namespace ca_uwaterloo_dwharder;`
> [!IMPORTANT]
> Avoid writing `using namespace std;` in production or header files, as it pollutes the global namespace and causes collisions.

### 1.7 Classes & Visibility
C++ classes encapsulate member variables and functions.
* **Visibility Blocks**: Unlike Java/C#, which require visibility modifiers on each member, C++ groups them in blocks (`private:`, `protected:`, `public:`).
  * `private`: Only accessible inside the class.
  * `public`: Accessible from any code utilizing the class.
  * `protected`: Accessible within the class and its derived/child classes.
* **Friend Classes**: If class `A` declares class `B` as a `friend`, class `B` is allowed to access the private and protected members of class `A`.
  ```cpp
  class ClassX {
  private:
      int privy;
      friend class ClassY; // ClassY is a friend
  };
  
  class ClassY {
  private:
      ClassX value;
  public:
      void set_x() { value.privy = 42; } // Valid because ClassY is a friend
  };
  ```

### 1.8 Accessors vs. Mutators and `const`
* **Accessors**: Member functions that inspect the state of an object but do not modify its member variables. Enforced by appending the `const` keyword to the function signature:
  ```cpp
  double real() const;
  ```
  If a const function attempts to modify any member variables (e.g., `re = 1.0;`), the compiler issues a compilation error.
* **Mutators**: Member functions that modify the object's state (e.g., `void normalize()`).

### 1.9 Templates
Templates enable generic programming, allowing functions and classes to operate with arbitrary types.
* **Function Template**:
  ```cpp
  template <typename Type>
  Type sqr(Type x) { return x * x; }
  ```
* **Class Template**: Requires template parameters during instantiation: `Complex<double> z(3.7, 4.2);`.

### 1.10 Pointers & Memory Management
* **Pointers**: Variables that store the memory address of another variable.
  * `&`: Address-of operator (gets the memory address of a variable).
  * `*`: Dereference operator (accesses or modifies the value at the address).
  * `->`: Member selection via pointer. `pz->abs()` is a shorthand for `(*pz).abs()`.
* **Dynamic Memory Allocation**:
  * **C++ Operators**: `new` (allocates memory on the heap and runs the constructor) and `delete` (calls the destructor and deallocates heap memory).
  * **Memory Lifecycles**:
    * **Stack Allocation**: Managed automatically by the compiler. Stack memory is reclaimed when variables go out of scope.
    * **Heap Allocation**: Must be manually freed using `delete`. Failing to free heap memory results in **memory leaks**.
  * **C++ vs. Java**: Java relies on automatic garbage collection (GC) running in the background. C++ requires explicit manual deallocation (though modern C++ supports smart pointers like `std::unique_ptr` and `std::shared_ptr` to achieve automated RAII memory management).

---

## 2. Key Complexities

| Operation / Area | Time Complexity | Space Complexity | Description |
|---|---|---|---|
| **Stack Allocation** | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | Very fast; resolved by modifying the stack pointer. |
| **Heap Allocation (`new`)** | $\mathcal{O}(1)$ (amortized) | $\mathcal{O}(N)$ | Involves OS searching for free block; expensive. |
| **Recursion Frame** | $\mathcal{O}(1)$ per call | $\mathcal{O}(d)$ | Stack depth $d$ determines memory overhead. |
| **Pointer Dereference** | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | Direct memory access. |

---

---

> 💡 **Bonus & Applications:** 
> The sections below contain supplementary materials, lab applications, C++ reference code, and LeetCode problems. You may skip this part if you are only reviewing core theory for the exam.

## 🛠️ THE BONUS

## 3. Templated Complex Number Class Implementation

Here is the complete implementation of a templated `Complex` number class matching your lecture details, with clean separation of accessor and mutator methods, proper initialization lists, and standard guard clauses.

```cpp
#ifndef COMPLEX_H
#define COMPLEX_H

#include <cmath>
#include <iostream>

template <typename Type>
class Complex {
private:
    Type re; // Real component
    Type im; // Imaginary component

public:
    // Constructor (using member initialization list in matching order)
    Complex(Type const &r = Type(), Type const &i = Type());

    // Accessors (const-qualified to prevent modifications)
    Type real() const;
    Type imag() const;
    Type abs() const;
    Complex exp() const;

    // Mutators (modify state)
    void normalize();

    // Friend operator overload for output stream
    template <typename T>
    friend std::ostream& operator<<(std::ostream &out, Complex<T> const &c);
};

// --- IMPLEMENTATION ---

// Constructor Implementation
template <typename Type>
Complex<Type>::Complex(Type const &r, Type const &i) 
    : re(r), im(i) {
    // Empty constructor body
}

// Return the real component
template <typename Type>
Type Complex<Type>::real() const {
    return re;
}

// Return the imaginary component
template <typename Type>
Type Complex<Type>::imag() const {
    return im;
}

// Return the absolute value |z|
template <typename Type>
Type Complex<Type>::abs() const {
    return std::sqrt(re * re + im * im);
}

// Return the exponential of the complex value: e^z = e^x * (cos(y) + i*sin(y))
template <typename Type>
Complex<Type> Complex<Type>::exp() const {
    Type exp_re = std::exp(re);
    return Complex<Type>(exp_re * std::cos(im), exp_re * std::sin(im));
}

// Normalize the complex number to unit norm (|z| = 1)
template <typename Type>
void Complex<Type>::normalize() {
    if (re == Type(0) && im == Type(0)) {
        return; // Avoid division by zero
    }
    Type absval = abs();
    re /= absval;
    im /= absval;
}

// Helper friend operator to print Complex numbers
template <typename T>
std::ostream& operator<<(std::ostream &out, Complex<T> const &c) {
    out << c.re << " + " << c.im << "i";
    return out;
}

#endif // COMPLEX_H
```

---

## 4. LeetCode Practice & Solutions

Below is the curated list of LeetCode problems covering C++ fundamentals, control flow, recursion, custom implementation of data structures, and basic array/string manipulations.

| # | Problem Name | Difficulty | Core Concept / Technique | Source Code Link |
| :-: | :--- | :--- | :--- | :--- |
| 1 | **Fibonacci Number** (LeetCode 509) | Easy | Iterative dynamic programming, space optimization | [no1_fibonacci.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/1_CPP/no1_fibonacci.cpp) |
| 2 | **Climbing Stairs** (LeetCode 70) | Easy | Combinatorics, recurrence relations, Fibonacci structure | [no2_stairs.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/1_CPP/no2_stairs.cpp) |
| 3 | **Custom Templated Vector** | Medium / Design | Rule of 5, dynamic array resizing, templates | [no3_vector.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/1_CPP/no3_vector.cpp) |
| 4 | **Reverse String** (LeetCode 344) | Easy | In-place character modification, two-pointer technique | [no4_reverse_string.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/1_CPP/no4_reverse_string.cpp) |
| 5 | **Valid Palindrome** (LeetCode 125) | Easy | String traversal, non-alphanumeric filtering, case insensitivity, two-pointer technique | [no5_palindrome.cpp](file:///Users/miyaks/Desktop/self-learn-1/the_BibleOfDataStructure/leetcode/1_CPP/no5_palindrome.cpp) |

---

### Detailed Walkthroughs of Selected Problems

#### LeetCode 344: Reverse String
* **Problem Statement**: Reverse a vector of characters in-place with $\mathcal{O}(1)$ auxiliary memory.
* **Approach (Two-Pointer Technique)**:
  1. Maintain two index pointers: `left` initialized to `0` and `right` initialized to `s.size() - 1`.
  2. While `left < right`, perform an in-place swap of `s[left]` and `s[right]`.
  3. Increment `left` and decrement `right` to move toward the center of the array.
* **Complexity**:
  * **Time Complexity**: $\mathcal{O}(N)$ where $N$ is the number of characters in the string, as we perform $N/2$ swaps.
  * **Space Complexity**: $\mathcal{O}(1)$ since all swapping is performed in-place.

#### LeetCode 125: Valid Palindrome
* **Problem Statement**: Determine if a string is a palindrome, considering only alphanumeric characters and ignoring cases.
* **Approach (In-Place Two-Pointer Technique)**:
  1. Position a `left` pointer at index `0` and a `right` pointer at index `s.length() - 1`.
  2. Advance `left` forward while the character at `s[left]` is non-alphanumeric (using `std::isalnum` and checking bounds).
  3. Regress `right` backward while the character at `s[right]` is non-alphanumeric.
  4. Compare the characters at `left` and `right` case-insensitively using `std::tolower`. If they differ, return `false`.
  5. Increment `left` and decrement `right` and repeat until the pointers cross.
* **Complexity**:
  * **Time Complexity**: $\mathcal{O}(N)$ where $N$ is the length of the string, since each character is visited at most twice.
  * **Space Complexity**: $\mathcal{O}(1)$ because the filtering is performed dynamically during pointer traversal, requiring no temporary strings.

