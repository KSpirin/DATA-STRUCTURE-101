/**
 * @brief LeetCode 933 - Number of Recent Calls
 * @difficulty Easy
 * @link https://leetcode.com/problems/number-of-recent-calls/
 *
 * Problem:
 * Count requests in the last 3000ms window.
 * 
 * Example: ping(1)->1, ping(100)->2, ping(3001)->3, ping(3002)->3
 * 
 * Constraints: 1 <= t <= 10^9, strictly increasing t */

#include <iostream>
#include <queue>
#include <cassert>
#include <string>

class RecentCounter {
public:
    RecentCounter() { // TODO
    }
    int ping(int t) { // TODO (return count in [t-3000, t])
    }
};

int main() {
    int passed = 0, failed = 0;
    auto check = [&](bool ok, const std::string& label) {
        if (ok) { passed++; std::cout << "  [PASS] " << label << std::endl; }
        else    { failed++; std::cout << "  [FAIL] " << label << std::endl; }
    };

    RecentCounter r;
    check(r.ping(1)    == 1, "ping(1) -> 1");
    check(r.ping(100)  == 2, "ping(100) -> 2");
    check(r.ping(3001) == 3, "ping(3001) -> 3");
    check(r.ping(3002) == 3, "ping(3002) -> 3");
    check(r.ping(5000) == 2, "ping(5000) -> 2 (3001 dropped)");

    std::cout << "\n" << passed << "/" << (passed + failed) << " test cases passed";
    if (failed == 0) std::cout << " -- All passed!" << std::endl;
    else             std::cout << " -- " << failed << " failed." << std::endl;
    return 0;
}
