
//imports
#include "AVLTree.h"

#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <ostream>

using namespace std;

AVLTree::AVLTree() {

    root = nullptr;

} //end AVLTree constructor

bool AVLTree::insert(const std::string& key, size_t value) {

    if (contains(key) == false) {

        if (recursiveInsert(root, key, value) == true) { //I'm pretty sure this will work?
            totalSize++;
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

        if (remove(root, key) == true) {
            totalSize--;
            return true;
        } //returns true if the node was removed properly

    }

    return false; //returns false if there is a duplicate key or if it was not removed properly

} //end remove

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
    } //if the key is greater than the current node, checks the nodes right key

    else {
        return nullopt;
    } //error catcher

} //end recursiveGet

size_t& AVLTree::operator[](const std::string& key) {

    return recursiveBracket(root, key).value;

} //end operator[]

AVLTree::AVLNode& AVLTree::recursiveBracket(AVLNode*& node, const std::string& key) {

    if (key == node->key) {
        return *node;
    } //returns the pointer to the node if they key matches the node's key

    else if (key < node->key) {
        return recursiveBracket(node->left, key);
    } //if the key is less than the current node, checks the nodes left key

    else if (key > node->key) {
        return recursiveBracket(node->right, key);
    } //if the key is greater than the current node, checks the nodes right key

    else {
        return *node;
    } //error catcher, isn't needed for this project just here to prevent errors

} //end recursiveBracket

vector<size_t> AVLTree::findRange(const std::string& lowKey, const string& highKey) const{

    return recursiveFindRange(root, lowKey,highKey);

} //end findRange

vector<size_t> AVLTree::recursiveFindRange(const AVLNode* node, const std::string& lowKey, const std::string& highKey) const {

    vector<size_t> range;

    if (node == nullptr) {
        return range;
    } //base case, returns the vector if the node is null

    if (node->key > lowKey) {
        return recursiveFindRange(node->left, lowKey, highKey);
    } //if the key is greater than the node's key, checks its left key

    if (node -> key >= lowKey && node -> key <= highKey) {
        range.push_back(node->value);
    } //if the node matches the conditions, adds value to the vector range

    if (node -> key < highKey) {
        return recursiveFindRange(node->right, lowKey, highKey);
    } //if the key is less than the node's key, checks its right key

    return range; //returns the result

} //end recursiveFindRange

vector<string> AVLTree::keys() const {

    return recursiveKeys(root);

} //end keys

vector<string> AVLTree::recursiveKeys(const AVLNode* node) const {

    vector<string> keys;

    if (node != nullptr) {

        recursiveKeys(node->left); //calls recursiveKeys on the left child node
        recursiveKeys(node->right); //calls recursiveKeys on the right child node
        keys.push_back(node->key); //adds the current key to the vector keys

    }

    return keys;

} //end recursiveKeys

size_t AVLTree::size() const{

    return totalSize;

} //end size

size_t AVLTree::getHeight() const{

    //TODO: this, use a max height var after balancing

} //end getHeight

AVLTree::AVLTree(const AVLTree& other) {

    //TODO: this

} //end AVLTree copy constructor

void AVLTree::operator=(const AVLTree& other) {

    //TODO: this

}

AVLTree::~AVLTree() {

    clear(root);

} //end ~AVLTree

void AVLTree::clear(AVLNode* node) {

    if (node != nullptr) {

        clear(node->left); //recursively calls clear on the current node's left node
        clear(node->right); //recursively calls clear on the current node's right node
        delete node; //removes the node from memory once its children are deleted
        node = nullptr; //sets the node to null

    }

} //end clear

ostream& operator<<(ostream& os, const AVLTree & avlTree) {

    avlTree.printTree(os, avlTree.root);
    return os;

} //end operator<<

void AVLTree::printTree(ostream& os, AVLNode* node) const {

    if (node == nullptr) {
        return;
    } //base case

    printTree(os, node->left);
    cout << "KEY: " << node->key << " with VALUE: " << node->value << endl;
    printTree(os, node->right);

} //end printTree


//these methods included at start
size_t AVLTree::AVLNode::numChildren() const {

    size_t numChildren = 0;

    if (left != nullptr) {
        numChildren++;
    } //adds 1 if left isn't null

    if (right != nullptr) {
        numChildren++;
    } //adds 1 if right isn't null

    return numChildren;

} //end numChildren

bool AVLTree::AVLNode::isLeaf() const {

    if (left == nullptr && right == nullptr) {
        return true;
    } //returns true if both left and right are empty

    else {
        return false;
    }

} //end isLeaf

size_t AVLTree::AVLNode::getHeight() const {

    return height;

} //end getHeight

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

    if (key == current->key) {
        delete current;
        //TODO: remove node properly
        return true;
    } //removes the node, deletes it from memory, and returns true when the node is found

    else if (key < current->key) {
        return recursiveRemove(current->left, key);
    } //if the key is less than the current node, checks the nodes left key

    else if (key > current->key) {
        return recursiveRemove(current->right, key);
    } //if the key is greater than the current node, checks the nodes right key

    else {
        return false; //error catcher
    }

    //TODO: balance tree

} //end remove

void AVLTree::balanceNode(AVLNode *&node) {

}
