/**
 * @brief Custom - Templated Vector (Rule of 5)
 * @difficulty Custom
 *
 * Problem:
 * Implement a dynamic array (Rule of 5):
 * push_back, operator[], Destructor, Copy Constructor,
 * Copy Assignment, Move Constructor, Move Assignment.
 * 
 * Constraints: Deep copy (no double-free) */

#include <iostream>
#include <cassert>
#include <utility>
#include <string>

template <typename T>
class Vector {
private:
    T* data;
    size_t sz, cap;
public:
    Vector() : data(nullptr), sz(0), cap(0) {}
    void push_back(const T& val) {
        // TODO
    }
    T& operator[](size_t i) {
        // TODO
    }
    size_t size() const { return sz; }
    ~Vector() { // TODO
    }
    Vector(const Vector& other) { // TODO
    }
    Vector& operator=(const Vector& other) { // TODO
        return *this;
    }
    Vector(Vector&& other) noexcept { // TODO
    }
    Vector& operator=(Vector&& other) noexcept { // TODO
        return *this;
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    {
        Vector<int> v;
        check(v.size() == 0, "initial size == 0");
        v.push_back(10); v.push_back(20); v.push_back(30);
        check(v.size() == 3,  "size after 3 pushes == 3");
        check(v[0] == 10,     "v[0] == 10");
        check(v[1] == 20,     "v[1] == 20");
        check(v[2] == 30,     "v[2] == 30");
    }
    {
        Vector<int> v;
        for (int i = 0; i < 10; i++) v.push_back(i);
        check(v.size() == 10, "10 push_backs -> size 10");
        check(v[9] == 9,      "v[9] == 9 (capacity doubled correctly)");
    }
    {
        // copy constructor
        Vector<int> a;
        a.push_back(1); a.push_back(2); a.push_back(3);
        Vector<int> b = a;
        check(b[0]==1 && b[2]==3, "copy constructor deep copies");
        b.push_back(4);
        check(a.size()==3, "original unchanged after copy push_back");
    }
    {
        // copy assignment
        Vector<int> a;
        a.push_back(5); a.push_back(6);
        Vector<int> c;
        c = a;
        check(c[0]==5 && c[1]==6, "copy assignment works");
    }
    {
        // move constructor
        Vector<int> a;
        a.push_back(7);
        Vector<int> d = std::move(a);
        check(d[0]==7,       "move constructor transfers data");
        check(a.size()==0,   "moved-from object has size 0");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
