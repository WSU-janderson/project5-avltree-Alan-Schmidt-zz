#include "AVLTree.h"

#include <string>
#include <vector>
#include <optional>

//import
using namespace std;

AVLTree::AVLTree() {

    root = nullptr;

} //end AVLTree constructor

bool AVLTree::insert(const std::string& key, size_t value) {

    if (contains(key) == false) {

        if (recursiveInsert(root, key, value) == true) { //I'm pretty sure this will work?
            return true;
        } //returns true if they key was inserted properly

    }

    return false; //returns false if there is a duplicate key or if it was not inserted properly

} //end insert

bool AVLTree::recursiveInsert(AVLNode*& node, const string& key, size_t value) {

    if (node == nullptr) {

        node = new AVLNode();
        node->key = key;
        node->value = value;
        node->left = nullptr;
        node->right = nullptr;
        return true;

    } //adds a new node with its key and value if the node is null and sets it's new left and right nodes to null

    if (key < node->key) {
        return recursiveInsert(node->left, key, value);
    } //tries to insert left if key is less than the node's key

    else if (key > node->key) {
        return recursiveInsert(node->right, key, value);
    } //tries to insert right if key is greater than the node's key

    else {
        return false; //error catcher
    }

    //TODO: Balance Tree

} //end recursiveInsert

bool AVLTree::remove(const std::string& key) {

}

bool AVLTree::contains(const std::string& key) const {

}

optional<size_t> AVLTree::get(const std::string& key) const {

}

size_t& AVLTree::operator[](const std::string& key) {

}

vector<string> AVLTree::findRange( const std::string& lowKey, const string& highKey) const{

}

vector<string> AVLTree::keys() const {

}

size_t AVLTree::size() const{

}

size_t AVLTree::getHeight() const{

}

AVLTree::AVLTree(const AVLTree& other) {

}

void AVLTree::operator=(const AVLTree& other) {

}

AVLTree::~AVLTree() {

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
