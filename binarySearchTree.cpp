#include "binarySearchTree.hpp"
#include <iostream>


BinarySearchTree::BinarySearchTree() : root(nullptr) {}

BinarySearchTree::~BinarySearchTree() {
    clear();
}

Node* BinarySearchTree::insertHelper(Node* node, int val) {
    if (!node) {
        return new Node(val);
    }

    if (val < node->val) {
        node->left = insertHelper(node->left, val);
    }

    if (val > node->val) {
        node->right = insertHelper(node->right, val);
    }

    return node;
}

void BinarySearchTree::insert(int val) {
    insertHelper(root, val);
}

void BinarySearchTree::inorderHelper(Node* node) {
    if (node) {
        inorderHelper(node->left);
        std::cout << node->val << " ";
        inorderHelper(node->right);
    }   
}

void BinarySearchTree::inorder() {
    inorderHelper(root);
    std::cout << std::endl;
}

void BinarySearchTree::preorderHelper(Node* node) {
    if (node) {
        std::cout << node->val << " ";
        preorderHelper(node->left);
        preorderHelper(node->right);
    }
}

void BinarySearchTree::preorder() {
    preorderHelper(root);
    std::cout << std::endl;
}

void BinarySearchTree::postorderHelper(Node* node) {
    if (node) {
        preorderHelper(node->left);
        preorderHelper(node->right);
        std::cout << node->val << " ";
    }
}

void BinarySearchTree::postorder() {
    postorderHelper(root);
    std::cout << std::endl;
}

Node* BinarySearchTree::find_minHelper(Node* node) {
    if (!node) {
        return nullptr;
    }

    if (node->left) {
        while(node->left) {
            node = node->left;
        }
    }
    return node;

}

int BinarySearchTree::findMin() {
    Node* tmp = find_minHelper(root);
    if (tmp) {
        return tmp->val;
    }
    return -1;
}

Node* BinarySearchTree::find_maxHelper(Node* node) {
    if (!node) {
        return nullptr;
    }

    if (node->right) {
        while (node->right) {
            node = node->right;
        }
    }

    return node;
}

int BinarySearchTree::findMax() {
    Node* tmp = find_maxHelper(root);
    if (tmp) {
        return tmp->val;
    }
    return -1;
}

Node* BinarySearchTree::removeHelper(Node* node, int val) {
    if (!node) {
        return nullptr;
    }

    if (val < node->val) {
        node->left = removeHelper(node->left, val);
    }

    if (val > node->val) {
        node->right = removeHelper(node->right, val);
    }

    if (val == node->val) {
        if (node->left == nullptr) {
            Node* tmp = node->right;
            delete node;
            return tmp;
        }

        else if (node->right == nullptr) {
            Node* tmp = node->left;
            delete node;
            return tmp;
        }

        Node* succ = find_minHelper(node);
        node->val = succ->val;
        node->right = removeHelper(node->right, succ->val);
    }
    return node;
}

void BinarySearchTree::remove(int val) {
    root = removeHelper(root, val);
}

Node* BinarySearchTree::searchHelper(Node* node, int val) {
    if (!node) {
        return nullptr;
    }

    if (val == node->val) {
        return node;
    }

    if (val < node->val) {
        return searchHelper(node->left, val);
    }

    else {
        return searchHelper(node->right, val);
    }
}

bool BinarySearchTree::search(int val) {
    if (searchHelper(root, val)) {
        return true;
    }
    return false;
}

int BinarySearchTree::sizeHelper(Node* node) {
    if (!node) {
        return 0;
    }

    int leftSize = sizeHelper(node->left);
    int rightSize = sizeHelper(node->right);

    return leftSize + rightSize + 1;
}

int BinarySearchTree::size() {
    return sizeHelper(root);
}

int BinarySearchTree::heightHelper(Node* node) {
    if (!node) {
        return 0;
    }

    int leftSide = heightHelper(node->left);
    int rightSide = heightHelper(node->right);

    return 1 + std::max(leftSide, rightSide);
}

int BinarySearchTree::height() {
    return heightHelper(root);
}

void BinarySearchTree::clearHelper(Node* &node) {
    if (!node)  {
        return;
    }

    clearHelper(node->left);
    clearHelper(node->right);

    delete node;
    node = nullptr;
}

void BinarySearchTree::clear() {
    clearHelper(root);
}

void BinarySearchTree::serializeHelper(Node* node, std::vector<int>& vec) {
    if (!node) {
        return;
    }

    serializeHelper(node->left, vec);
    vec.push_back(node->val);
    serializeHelper(node->right, vec);
}

std::vector<int> BinarySearchTree::serialize() {
    std::vector<int> res;

    serializeHelper(root, res);
    return res;
}

void BinarySearchTree::range_query(int start, int end) {
    for (int i = start; i < end; ++i) {
        if (search(i)) {
            std::cout << i << std::endl;
        }
    }
}

void BinarySearchTree::levelorderHelper(Node* node, int level) {
    if (!node) {
        return;
    }

    if (level == 1) {
        std::cout << node->val << " ";
    }
    else if (level > 1) {
        levelorderHelper(node->left, level - 1);
        levelorderHelper(node->right, level - 1);
    }
}

void BinarySearchTree::levelorder() {
    int h = heightHelper(root);
    for (int i = 1; i <= h; ++i) {
        levelorderHelper(root, i);
    }
}

Node* BinarySearchTree::successorHelper(Node* node, Node* &succ , int val) {
    if (!node) {
        return nullptr;
    }

    if (node->val == val && node->right == nullptr) {
        return find_minHelper(node);
    }

    Node* curr = node;
    
    while (curr != nullptr) {
        if (val < curr->val) {
            succ = curr;
            curr = curr->left;
        }
        else if (val >= curr->val) {
            curr = curr->right;
        }
        else {
            break;
        }
    }

    return succ;
}       

int BinarySearchTree::successor(int val) {
    if (!search(val)) {
        std::cout << "Value doesn't exist." << std::endl;
        return -1;
    }

    Node* succ = nullptr;
    succ = successorHelper(root, succ, val);
    if (succ) {
        return succ -> val;
    }
    else {
        std::cout << "Successor of this value doesn't exist." << std::endl;
        return -1;
    }
}


Node* BinarySearchTree::predecessorHelper(Node* node, Node* &pred , int val) {
    if(!node) {
        return nullptr;
    }

    if (val == node->val && node->left != nullptr) {
        return find_maxHelper(node->left);
    }

    Node* curr = node;

    while (curr != nullptr) {
        if (val > curr->val) {
            pred = node;
            node = node->right;
        }
        else if (val <= curr->val) {
            node = node->left;
        }
    }
}     

int BinarySearchTree::predecessor(int val) {
    if (!search(val)) {
        std::cout << "Value doesn't exist." << std::endl;
        return -1;
    }

    Node* pred = nullptr;
    pred = predecessorHelper(root, pred, val);
    if (pred) {
        return pred->val;
    }
    else {
        std::cout << "Predecessor of this value doesn't exist." << std::endl;
        return -1;
    }
}

Node* BinarySearchTree::find(int val) {
    return searchHelper(root, val);
}

Node* BinarySearchTree::copyHelper(Node* node) {
    if (!node) {
        return nullptr;
    }
    
    Node* newRoot = new Node(node->val);

    newRoot->left = copyHelper(node->left);
    newRoot->right = copyHelper(node->right);

    return newRoot;
}

Node* BinarySearchTree::copy() {
    return copyHelper(root);
}

