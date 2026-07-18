/**
 * @brief Custom - MaxHeap Class & Heap Sort
 * @difficulty Custom
 *
 * Problem:
 * Build MaxHeap class and implement Heap Sort.
 * 
 * Constraints: Use 0-indexed array, heapify up on insert, heapify down on extractMax */

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <string>

class MaxHeap {
private:
    std::vector<int> data;
    void heapifyUp(int i) { // TODO
    }
    void heapifyDown(int i) { // TODO
    }
public:
    void insert(int val) { // TODO
    }
    int extractMax() { // TODO
    }
    int size() const { return data.size(); }
};

std::vector<int> heapSort(std::vector<int> arr) {
    // TODO
}

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    MaxHeap h;
    h.insert(3); h.insert(1); h.insert(4); h.insert(1); h.insert(5);
    check(h.extractMax() == 5, "extractMax from [3,1,4,1,5] -> 5");
    check(h.extractMax() == 4, "extractMax next -> 4");
    check(h.extractMax() == 3, "extractMax next -> 3");
    check(h.size() == 2,       "size after 3 extracts == 2");

    MaxHeap h2;
    h2.insert(10);
    check(h2.extractMax() == 10, "single element extractMax");
    check(h2.size() == 0,        "empty after extract");

    MaxHeap h3;
    for (int v : {7,3,9,1,5,8,2,6,4}) h3.insert(v);
    int prev = h3.extractMax();
    bool sorted = true;
    while (h3.size() > 0) {
        int cur = h3.extractMax();
        if (cur > prev) sorted = false;
        prev = cur;
    }
    check(sorted, "extractMax always returns descending order");

    {
        std::vector<int> arr = {5,3,1,4,2};
        auto s = heapSort(arr);
        check(s[0]==1 && s[1]==2 && s[2]==3 && s[3]==4 && s[4]==5, "heapSort [5,3,1,4,2] -> [1,2,3,4,5]");
    }
    {
        std::vector<int> arr2 = {1};
        auto s = heapSort(arr2);
        check(s[0]==1, "heapSort single element");
    }
    {
        std::vector<int> arr3 = {2,2,2};
        auto s = heapSort(arr3);
        check(s[0]==2 && s[2]==2, "heapSort all equal");
    }

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
