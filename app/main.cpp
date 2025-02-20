#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

#define DEBUG_TAG "[DEBUG]: "
#define TEST_CASE_HEADING "=================================="

using namespace std;

struct Node {
    int val;
    int height;
    Node* left;
    Node* right;
    Node() : val(0), height(0), left(nullptr), right(nullptr) {}
    Node(int v, int h = 0) : val(v), height(h), left(nullptr), right(nullptr) {}
    Node(int v, Node* left, Node* right, int h = 0) : val(v), height(h), left(left), right(right) {}
};

class AvlTree {
private:
    Node* root;

private:
    Node* _balance(Node* node) {
        int bf = _getBalanceFactor(node);

        if (bf < -1) { // node is right-heavy.
            if (_getBalanceFactor(node->right) < 0) {
                node = _rotateRR(node);
            }
            else if (_getBalanceFactor(node->right) > 0) {
                node = _rotateRL(node);
            }
        }
        else if (bf > 1) { // node is left-heavy.
            if (_getBalanceFactor(node->left) > 0) {
                node = _rotateLL(node);
            }
            else if (_getBalanceFactor(node->left) < 0) {
                node = _rotateLR(node);
            }
        }

        return node;
    }

    Node* _copyTree(Node* src, Node* dest) {
        if (src == nullptr) {
            return nullptr;
        }

        if (dest == nullptr) {
            dest = new Node();
        }

        dest->val = src->val;
        dest->height = src->height;

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

    int _getBalanceFactor(Node* node) {
        return (node != nullptr) ? _getHeight(node->left) - _getHeight(node->right) : 0;
    }

    int _getHeight(Node* node) {
        return (node != nullptr) ? node->height : -1;
    }

    Node* _insertRecursion(int val, Node* node) {
        if (node == nullptr) {
            node = new Node(val);
        }

        if (val < node->val) {
            node->left = _insertRecursion(val, node->left);
        }
        else if (val > node->val) {
            node->right = _insertRecursion(val, node->right);
        }

        node = _balance(node);
        _updateHeight(node);

        return node;
    }

    Node* _rotateLL(Node* node) {
        cout << DEBUG_TAG << "LL rotation on " << node->val << "." << endl;

        Node* pCurr = node;
        Node* pLeft = node->left;

        pCurr->left = pLeft->right;
        pLeft->right = pCurr;

        _updateHeight(pCurr);
        _updateHeight(pLeft);

        return pLeft;
    }

    Node* _rotateRR(Node* node) {
        cout << DEBUG_TAG << "RR rotation on " << node->val << "." << endl;

        Node* pCurr = node;
        Node* pRight = node->right;

        pCurr->right = pRight->left;
        pRight->left = pCurr;

        _updateHeight(pCurr);
        _updateHeight(pRight);

        return pRight;
    }

    Node* _rotateLR(Node* node) {
        cout << DEBUG_TAG << "LR rotation on " << node->val << "." << endl;

        Node* pCurr = node;
        Node* pLeft = node->left;
        Node* pRight = node->left->right;
        
        pLeft->right = pRight->left;
        pCurr->left = pRight->right;
        pRight->left = pLeft;
        pRight->right = pCurr;

        _updateHeight(pCurr);
        _updateHeight(pLeft);
        _updateHeight(pRight);

        return pRight;
    }

    Node* _rotateRL(Node* node) {
        cout << DEBUG_TAG << "RL rotation on " << node->val << "." << endl;

        Node* pCurr = node;
        Node* pRight = node->right;
        Node* pLeft = node->right->left;

        pCurr->right = pLeft->left;
        pRight->left = pLeft->right;
        pLeft->left = pCurr;
        pLeft->right = pRight;

        _updateHeight(pCurr);
        _updateHeight(pLeft);
        _updateHeight(pRight);

        return pLeft;
    }

    void _updateHeight(Node* node) {
        node->height = max(_getHeight(node->left), _getHeight(node->right)) + 1;
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

    void insert(int val) {
        root = _insertRecursion(val, root);
        printTree();
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
            vector<Node*> level_nodes;

            for (int i = 0; i < level_size; ++i) {
                Node* curr = q.front();
                q.pop();

                if (curr != nullptr) {
                    level_nodes.push_back(curr);
                    q.push(curr->left);
                    q.push(curr->right);
                }
                else {
                    level_nodes.push_back(nullptr);
                }
            }

            for (Node* node : level_nodes) {
                if (node != nullptr) {
                    cout << node->val << "(" << _getHeight(node) << ")" << "   ";
                }
                else {
                    cout << "*" << "(-1)   ";
                }
            }
            cout << endl;
        }
        cout << endl;
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

    void testCase2() {
        cout << endl;
        cout << TEST_CASE_HEADING << endl;
        cout << "test case 2: insertions." << endl;

        AvlTree tree;
        tree.insert(10);
        tree.insert(7);
        tree.insert(4); // LL rotation.
        tree.insert(2);
        tree.insert(3); // LR rotation.
        tree.insert(13);
        tree.insert(16); // RR rotation.
        tree.insert(19);
        tree.insert(17); // RL rotation.

        cout << TEST_CASE_HEADING << endl << endl;
    }
};

int main() {
    Solution sln;

    sln.testCase2();

    return 0;
}
