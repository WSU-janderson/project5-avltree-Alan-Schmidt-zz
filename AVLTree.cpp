#include "AVLTree.h"

#include <string>
#include <vector>
#include <optional>

//import
using namespace std;

bool insert(const std::string& key, size_t value) {

}

bool remove(const std::string& key) {

}

bool contains(const std::string& key) const {

}

optional<size_t> get(const std::string& key) const {

}

size_t& operator[](const std::string& key) {

}

vector<string> findRange( const std::string& lowKey, const string& highKey) const {

}

vector<string> keys() const {

}

size_t size() const {

}

size_t getHeight() const {

}

AVLTree(const AVLTree& other) {

}

void operator=(const AVLTree& other) {

}

~AVLTree() {

}

ostream& operator<<(ostream& os, const AVLTree & avlTree) {

}


//these methods included at start
size_t AVLTree::AVLNode::numChildren() const {
    return 0;
}

bool AVLTree::AVLNode::isLeaf() const {
    return false;
}

size_t AVLTree::AVLNode::getHeight() const {
    return 0;
}

bool AVLTree::removeNode(AVLNode*& current){
    if (!current) {
        return false;
    }

    AVLNode* toDelete = current;
    auto nChildren = current->numChildren();
    if (current->isLeaf()) {
        // case 1 we can delete the node
        current = nullptr;
    } else if (current->numChildren() == 1) {
        // case 2 - replace current with its only child
        if (current->right) {
            current = current->right;
        } else {
            current = current->left;
        }
    } else {
        // case 3 - we have two children,
        // get smallest key in right subtree by
        // getting right child and go left until left is null
        AVLNode* smallestInRight = current->right;
        // I could check if smallestInRight is null,
        // but it shouldn't be since the node has two children
        while (smallestInRight->left) {
            smallestInRight = smallestInRight->left;
        }
        std::string newKey = smallestInRight->key;
        int newValue = smallestInRight->value;
        remove(root, smallestInRight->key); // delete this one

        current->key = newKey;
        current->value = newValue;

        current->height = current->getHeight();
        balanceNode(current);

        return true; // we already deleted the one we needed to so return
    }
    delete toDelete;

    return true;
}

bool AVLTree::remove(AVLNode *&current, KeyType key) {
    return false;
}

void AVLTree::balanceNode(AVLNode *&node) {
}
