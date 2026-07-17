/**
 * @file no7_dota2_senate.cpp
 * @author Computer Science Teaching Assistant
 * @brief LeetCode 649: Dota2 Senate
 * @difficulty Medium
 * @link https://leetcode.com/problems/dota2-senate/
 * 
 * @details
 * Problem Description:
 * In the world of Dota2, there are two parties: the Radiant and the Dire.
 * The Dota2 senate consists of senators coming from these two parties. Now the Senate 
 * wants to decide on a change in the Dota2 game. The voting for this change is a 
 * round-based procedure. In each round, each senator can exercise one of two rights:
 * 1. Ban one senator's right: A senator can make another senator lose all senate rights 
 *    in this and all the following rounds.
 * 2. Announce the victory: If this senator found the opponent senators already lost 
 *    all senate rights, the senator can announce the victory and decide on the change.
 * 
 * Given a string `senate` representing each senator's party affiliation ('R' or 'D').
 * The round-based procedure starts from the first senator to the last senator in the 
 * given order. This procedure will last until the end of voting. All the senators 
 * who have lost their rights will be skipped.
 * 
 * Suppose every senator is smart enough and will play the best strategy for his own 
 * party. Predict which party will finally announce the victory. The output should be 
 * "Radiant" or "Dire".
 * 
 * Constraints:
 * - n == senate.length
 * - 1 <= n <= 10^4
 * - senate[i] is either 'R' or 'D'.
 */

#include <iostream>
#include <string>
#include <queue>
#include <cassert>

class Solution {
public:
    /**
     * @brief Predicts which party wins the Dota2 Senate vote.
     * @details This is simulated efficiently using two queues representing the voting order.
     * One queue stores the indices of Radiant ('R') senators, and the other stores the indices 
     * of Dire ('D') senators.
     * In each turn:
     * - We compare the fronts of both queues. The senator with the smaller index gets to vote first 
     *   and bans the opponent at the front of the other queue.
     * - The banning senator survives to vote in the next round. To represent this, we add `n` 
     *   (the length of the senate string) to their index and push them back into their queue.
     * - The banned senator is popped and eliminated (not re-enqueued).
     * This continues until one of the queues becomes empty, meaning all senators of that party 
     * have been banned.
     * 
     * @param senate String representing the initial order of senators.
     * @return "Radiant" or "Dire" based on the winning party.
     * 
     * @time_complexity O(N) where N is the length of the senate string. Each senator can ban 
     * or be banned, and the number of active senators decreases or stays bounded, resulting 
     * in linear time simulation.
     * @space_complexity O(N) to store the indices of the senators in the two queues.
     */
    std::string predictPartySenate(std::string senate) {
        int n = senate.length();
        std::queue<int> radiant;
        std::queue<int> dire;

        // Step 1: Populates the queues with the indices of the senators
        for (int i = 0; i < n; ++i) {
            if (senate[i] == 'R') {
                radiant.push(i);
            } else {
                dire.push(i);
            }
        }

        // Step 2: Simulate voting round-by-round
        while (!radiant.empty() && !dire.empty()) {
            int r_idx = radiant.front();
            int d_idx = dire.front();
            radiant.pop();
            dire.pop();

            // The senator with the smaller index votes first and bans the other
            if (r_idx < d_idx) {
                // Radiant bans Dire. Radiant senator goes to the next round.
                radiant.push(r_idx + n);
            } else {
                // Dire bans Radiant. Dire senator goes to the next round.
                dire.push(d_idx + n);
            }
        }

        // Step 3: The party with remaining senators wins
        return radiant.empty() ? "Dire" : "Radiant";
    }
};

/**
 * ============================================================================
 *                             MANUAL DRY-RUN TRACE
 * ============================================================================
 * Input: senate = "RDD"
 * n = 3
 * 
 * Initial state of queues:
 * - radiant: [ 0 ]
 * - dire: [ 1, 2 ]
 * 
 * --- Round 1 ---
 * - Pop r_idx = 0 from radiant.
 * - Pop d_idx = 1 from dire.
 * - Compare: r_idx (0) < d_idx (1).
 *   - Radiant senator at 0 bans Dire senator at 1.
 *   - Radiant senator goes to the next round: enqueue (0 + 3) = 3 to radiant.
 * - Queues state:
 *   - radiant: [ 3 ]
 *   - dire: [ 2 ]
 * 
 * --- Round 2 ---
 * - Pop r_idx = 3 from radiant.
 * - Pop d_idx = 2 from dire.
 * - Compare: d_idx (2) < r_idx (3).
 *   - Dire senator at 2 bans Radiant senator at 3.
 *   - Dire senator goes to the next round: enqueue (2 + 3) = 5 to dire.
 * - Queues state:
 *   - radiant: [ ] (Empty)
 *   - dire: [ 5 ]
 * 
 * Loop terminates because radiant is empty.
 * Returns "Dire".
 */

int main() {
    Solution solver;

    // Test Case 1: Radiant wins easily
    assert(solver.predictPartySenate("RD") == "Radiant");

    // Test Case 2: Dire wins due to majority
    assert(solver.predictPartySenate("RDD") == "Dire");

    // Test Case 3: Alternating with Radiant dominance
    assert(solver.predictPartySenate("RRDD") == "Radiant");

    // Test Case 4: Long sequence of Dire dominance
    assert(solver.predictPartySenate("DDRRR") == "Dire");

    std::cout << "All assertions for Dota2 Senate passed successfully!" << std::endl;
    return 0;
}
