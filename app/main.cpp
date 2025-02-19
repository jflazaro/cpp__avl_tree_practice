#include <iostream>
#include <queue>
#include <vector>

#define DEBUG_TAG "[DEBUG]: "
#define TEST_CASE_HEADING "=================================="

using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node() : val(0), left(nullptr), right(nullptr) {}
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
    Node(int v, Node* left, Node* right) : val(v), left(left), right(right) {}
};

class AvlTree {
private:
    Node* root;

private:
    Node* _copyTree(Node* src, Node* dest) {
        if (src == nullptr) {
            return nullptr;
        }

        if (dest == nullptr) {
            dest = new Node();
        }

        dest->val = src->val;

        dest->left = _copyTree(src->left, dest->left);
        dest->right = _copyTree(src->right, dest->right);

        return dest;
    }

    void _deleteTree() {
        _deleteTree(root);
        root = nullptr;
    }

    void _deleteTree(Node* node) {
        if (node == nullptr) {
            return;
        }

        _deleteTree(node->left);
        _deleteTree(node->right);

        cout << DEBUG_TAG << "deleting " << node->val << endl;
        delete node;
    }

private:
    Node* _rotateLL(Node* node) {
        Node* pCurr = node;
        Node* pLeft = node->left;

        pCurr->left = pLeft->right;
        pLeft->right = pCurr;

        return pLeft;
    }

    Node* _rotateRR(Node* node) {
        Node* pCurr = node;
        Node* pRight = node->right;

        pCurr->right = pRight->left;
        pRight->left = pCurr;

        return pRight;
    }

    Node* _rotateLR(Node* node) {
        Node* pCurr = node;
        Node* pLeft = node->left;
        Node* pRight = node->left->right;
        
        pLeft->right = pRight->left;
        pCurr->left = pRight->right;
        pRight->left = pLeft;
        pRight->right = pCurr;

        return pRight;
    }

    Node* _rotateRL(Node* node) {
        Node* pCurr = node;
        Node* pRight = node->right;
        Node* pLeft = node->right->left;

        pCurr->right = pLeft->left;
        pRight->left = pLeft->right;
        pLeft->left = pCurr;
        pLeft->right = pRight;

        return pLeft;
    }

public:
    AvlTree() : root(nullptr) {}
    AvlTree(Node* node) : root(node) {}
    AvlTree(const AvlTree& tree) : root(nullptr) {
        root = _copyTree(tree.root, root);
    }
    AvlTree(AvlTree&& tree) noexcept : root(tree.root) { 
        tree.root = nullptr;
    }
    ~AvlTree() {
        _deleteTree();
    }

    AvlTree& operator=(const AvlTree& tree) {
        if (this == &tree) {
            return *this;
        }

        _deleteTree();

        root = _copyTree(tree.root, root);

        return *this;
    }

    void printTree() {
        queue<Node*> q;

        if (root == nullptr) {
            return;
        }

        q.push(root);

        while (!q.empty()) {
            int level_size = q.size();
            vector<int> level_vals;

            for (int i = 0; i < level_size; ++i) {
                Node* curr = q.front();
                q.pop();

                if (curr != nullptr) {
                    level_vals.push_back(curr->val);
                    q.push(curr->left);
                    q.push(curr->right);
                }
                else {
                    level_vals.push_back(-1);
                }
            }

            for (int val : level_vals) {
                if (val != -1) {
                    cout << val << "  ";
                }
                else {
                    cout << "*" << "  ";
                }
            }
            cout << endl;
        }
    }
};

class Solution {
public:
    void testCase1() {
        cout << endl;
        cout << TEST_CASE_HEADING << endl;
        cout << "test case 1: constructors." << endl;

        Node* root = new Node(4);
        root->left = new Node(2);
        root->right = new Node(6);
        root->left->left = new Node(1);
        root->left->right = new Node(3);
        root->right->left = new Node(5);
        root->right->right = new Node(7);

        AvlTree tree(root);
        tree.printTree();

        cout << DEBUG_TAG << "copy constructor begin." << endl;
        AvlTree tree_copy(tree);
        tree_copy.printTree();

        cout << DEBUG_TAG << "move constructor begin." << endl;
        AvlTree tree_move = move(tree_copy);
        tree_move.printTree();

        cout << DEBUG_TAG << "operator= begin." << endl;
        AvlTree tree_assign;
        tree_assign = tree_move;
        tree_assign.printTree();

        cout << TEST_CASE_HEADING << endl << endl;
    }
};

int main() {
    Solution sln;

    sln.testCase1();

    return 0;
}
