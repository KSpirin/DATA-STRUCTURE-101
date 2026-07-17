/**
 * @file no5_sorted_list_to_bst.cpp
 * @brief LeetCode 109: Convert Sorted List to Binary Search Tree
 * @difficulty Medium
 * @link https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/
 *
 * Problem Description:
 * Given the head of a singly linked list where elements are sorted in ascending order,
 * convert it to a height-balanced binary search tree.
 *
 * A height-balanced binary tree is a binary tree in which the depth of the two subtrees
 * of every node never differs by more than one.
 *
 * Example 1:
 * Input: head = [-10,-3,0,5,9]
 * Output: [0,-3,9,-10,null,5]
 * Explanation: [0,-3,9,-10,null,5] is a height-balanced BST. Other valid outputs include [0,-10,5,null,-3,null,9].
 */

#include <iostream>
#include <vector>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    /**
     * @brief Helper function to construct BST in-order.
     * By building the BST structure in-order (Left -> Root -> Right), we can construct
     * the tree in one pass matching the order of nodes in the sorted linked list.
     * 
     * @param head A reference to the current ListNode pointer. This pointer is moved
     *             forward as elements are processed.
     * @param n The number of nodes to process in the current range.
     * @return TreeNode* The root of the height-balanced BST constructed from the range.
     */
    TreeNode* buildBSTInorder(ListNode*& head, int n) {
        // Base case: If there are no elements to process, return nullptr
        if (n <= 0) {
            return nullptr;
        }

        // 1. Recursively construct the left subtree using the first n/2 elements.
        // This advances 'head' to the middle node of the current range.
        TreeNode* leftChild = buildBSTInorder(head, n / 2);

        // 2. Create the root node using the current 'head' node.
        TreeNode* root = new TreeNode(head->val);
        root->left = leftChild;

        // 3. Move the 'head' pointer to the next list node.
        head = head->next;

        // 4. Recursively construct the right subtree using the remaining elements.
        // The number of remaining elements is: total (n) - left (n/2) - root (1)
        root->right = buildBSTInorder(head, n - n / 2 - 1);

        return root;
    }

    /**
     * @brief Utility function to calculate the length of the linked list.
     * Runs in O(N) time.
     */
    int getLength(ListNode* head) {
        int length = 0;
        while (head != nullptr) {
            length++;
            head = head->next;
        }
        return length;
    }

public:
    /**
     * @brief Converts a sorted linked list to a height-balanced BST.
     * Runs in O(N) time and O(log N) auxiliary space.
     */
    TreeNode* sortedListToBST(ListNode* head) {
        int length = getLength(head);
        return buildBSTInorder(head, length);
    }
};

/*
 * =========================================================================
 * MANUAL DRY-RUN TRACE
 * =========================================================================
 * Input List: -10 -> -3 -> 0 -> 5 -> 9 -> nullptr
 *
 * 1. Count list length:
 *    getLength(head) traverses the list and returns length = 5.
 *
 * 2. Initial Call:
 *    buildBSTInorder(head, n = 5)
 *    - leftChild = buildBSTInorder(head, n/2 = 2)
 *
 *    ---------------------------------------------------------------------
 *    Subcall A: buildBSTInorder(head, n = 2)
 *    - leftChild = buildBSTInorder(head, n/2 = 1)
 *
 *      -------------------------------------------------------------------
 *      Subcall B: buildBSTInorder(head, n = 1)
 *      - leftChild = buildBSTInorder(head, n/2 = 0) -> Returns nullptr
 *      - root = new TreeNode(head->val) -> root = [-10]
 *      - root->left = nullptr (leftChild)
 *      - head advances: head = head->next (now points to -3)
 *      - root->right = buildBSTInorder(head, n - n/2 - 1 = 0) -> Returns nullptr
 *      - Returns node [-10]
 *      -------------------------------------------------------------------
 *
 *    - Back to Subcall A (n = 2):
 *      - leftChild = [-10]
 *      - root = new TreeNode(head->val) -> root = [-3] (since head points to -3)
 *      - root->left = [-10]
 *      - head advances: head = head->next (now points to 0)
 *      - root->right = buildBSTInorder(head, 2 - 1 - 1 = 0) -> Returns nullptr
 *      - Returns node [-3]
 *    ---------------------------------------------------------------------
 *
 * - Back to Initial Call (n = 5):
 *   - leftChild = [-3] (with left child [-10])
 *   - root = new TreeNode(head->val) -> root = [0] (since head points to 0)
 *   - root->left = [-3]
 *   - head advances: head = head->next (now points to 5)
 *   - root->right = buildBSTInorder(head, 5 - 2 - 1 = 2)
 *
 *   ---------------------------------------------------------------------
 *   Subcall C: buildBSTInorder(head, n = 2)
 *   - leftChild = buildBSTInorder(head, n/2 = 1)
 *
 *     --------------------------------------------------------------------
 *     Subcall D: buildBSTInorder(head, n = 1)
 *     - leftChild = buildBSTInorder(head, n/2 = 0) -> Returns nullptr
 *     - root = new TreeNode(head->val) -> root = [5] (since head points to 5)
 *     - root->left = nullptr
 *     - head advances: head = head->next (now points to 9)
 *     - root->right = buildBSTInorder(head, 0) -> Returns nullptr
 *     - Returns node [5]
 *     --------------------------------------------------------------------
 *
 *   - Back to Subcall C (n = 2):
 *     - leftChild = [5]
 *     - root = new TreeNode(head->val) -> root = [9] (since head points to 9)
 *     - root->left = [5]
 *     - head advances: head = head->next (now nullptr)
 *     - root->right = buildBSTInorder(head, 0) -> Returns nullptr
 *     - Returns node [9] (with left child [5])
 *   ---------------------------------------------------------------------
 *
 * - Back to Initial Call (n = 5):
 *   - root->right = [9]
 *   - Returns root [0]
 *
 * Final Constructed Tree:
 *          0
 *        /   \
 *      -3     9
 *      /     /
 *    -10    5
 *
 * Balance factors verification:
 * - Node -10: Left height = -1, Right height = -1. BF = 0.
 * - Node -3:  Left height =  0, Right height = -1. BF = 1.
 * - Node 5:   Left height = -1, Right height = -1. BF = 0.
 * - Node 9:   Left height =  0, Right height = -1. BF = 1.
 * - Node 0:   Left height =  1, Right height =  1. BF = 0.
 * All balance factors are in {-1, 0, 1}. The tree is perfectly height-balanced.
 *
 * =========================================================================
 * TIME AND SPACE COMPLEXITY ANALYSIS
 * =========================================================================
 * - Time Complexity: O(N)
 *   We count the length of the list in O(N). The recursive division traverses 
 *   exactly N subproblems, visiting each node in the list once as we advance 
 *   'head' in-order. Thus, the runtime is strictly linear O(N).
 *
 * - Space Complexity: O(log N)
 *   Unlike solutions that copy elements into an array/vector (which uses O(N) auxiliary space), 
 *   this solution constructs the BST in-place. The only auxiliary space is the recursive 
 *   call stack, which has a maximum depth of O(log N) since the BST is built in a 
 *   perfectly balanced manner.
 */

// Helper function to print tree inorder (for testing)
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    std::cout << root->val << " ";
    printInorder(root->right);
}

// Helper function to delete tree and free memory
void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// Helper function to free list memory
void freeList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    // Create test sorted list: -10 -> -3 -> 0 -> 5 -> 9 -> nullptr
    ListNode* head = new ListNode(-10);
    ListNode* node1 = new ListNode(-3);
    ListNode* node2 = new ListNode(0);
    ListNode* node3 = new ListNode(5);
    ListNode* node4 = new ListNode(9);
    head->next = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;

    Solution solver;
    // We pass a copy of the pointer so that we can delete the list using the original pointers afterwards
    ListNode* headCopy = head;
    TreeNode* bstRoot = solver.sortedListToBST(headCopy);

    std::cout << "Successfully built balanced BST!\n";
    std::cout << "BST Inorder Traversal (should match sorted order): ";
    printInorder(bstRoot);
    std::cout << "\n";

    if (bstRoot != nullptr && bstRoot->val == 0) {
        std::cout << "Verification passed! Root node is: " << bstRoot->val << "\n";
    } else {
        std::cout << "Verification failed!\n";
    }

    // Clean up memory
    freeTree(bstRoot);
    freeList(head); 
    return 0;
}
