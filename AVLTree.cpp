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

    if (contains(key) == false) {

        if (recursiveRemove(root, key) == true) {
            return true;
        } //returns true if the node was removed properly

        return false; //returns false if there is a duplicate key or if it was not removed properly
    }

} //end remove

bool AVLTree::recursiveRemove(AVLNode *&node, const string &key) {

    if (key == node->key) {
        delete node;
        //TODO: remove node properly
        return true;
    } //removes the node, deletes it from memory, and returns true when the node is found

    else if (key < node->key) {
        return recursiveRemove(node->left, key);
    } //if the key is less than the current node, checks the nodes left key

    else if (key > node->key) {
        return recursiveRemove(node->right, key);
    } //if the key is greater than the current node, checks the nodes right key

    else {
        return false; //error catcher
    }

    //TODO: balance tree

} //remove recursiveRemove


bool AVLTree::contains(const std::string& key) const {

    return recursiveContains(root, key);

} //end contains

bool AVLTree::recursiveContains(const AVLNode *node, const string& key) const {

    if (node == nullptr) {
        return false;
    } //returns false if the tree is empty

    if (key == node->key) {
        return true;
    } //returns true if the key is found

    else if (key < node->key) {
        return recursiveContains(node->left, key);
    } //if the key is less than the current node, checks the nodes left key

    else if (key > node->key) {
        return recursiveContains(node->right, key);
    } //if the key is greater than the current node, checks the nodes right key

    else {
        return false; //returns false if the key is not found in the tree and is an error catcher
    }

} //end recursiveContains

optional<size_t> AVLTree::get(const std::string& key) const {

    if (contains(key) == false) {

        return recursiveGet(root, key);

    } //if the key is in the tree, returns the result of recursiveGet

    else {
        return nullopt;
    } //returns nullopt if key is not in tree

} //end get

optional<size_t> AVLTree::recursiveGet(const AVLNode *node, const string& key) const {

    if (key == node->key) {
        return node->value;
    } //returns the value associated with the node if the key matches the current node's key

    else if (key < node->key) {
        return recursiveGet(node->left, key);
    } //if the key is less than the current node, checks the nodes left key

    else if (key > node->key) {
        return recursiveGet(node->right, key);
    } //if the key is greaterthan the current node, checks the nodes right key

    else {
        return nullopt;
    } //error catcher

} //end recursiveGet

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
