/*
 *Alan Schmidt
 *AVLTree Project
 *This file contains all of the methods needed to make a binary search tree
 *and *supposedly* properly balance it, although I don't think it works properly
 Also, I don't have time to make header comments for each method, but I did comment
 along each line as I went along.
 */
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
        node->height = 0;
        return true;

    } //adds a new node with its key and value if the node is null and sets it's new left and right nodes to null

    bool done = false;

    if (key < node->key) {
        done = recursiveInsert(node->left, key, value);
    } //tries to insert left if key is less than the node's key

    else if (key > node->key) {
        done = recursiveInsert(node->right, key, value);
    } //tries to insert right if key is greater than the node's key

    else {
        return false;
    } //error catcher

    if (done) {
        balanceNode(node);
    } //balances if the node was inserted correctly

    return done;

} //end recursiveInsert

bool AVLTree::remove(const std::string& key) {

    if (contains(key) == true) {

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

    if (contains(key) == true) {

        return recursiveGet(root, key);

    } //if the key is in the tree, returns the result of recursiveGet

    else {
        return nullopt;
    } //returns nullopt if key is not in tree

} //end get

optional<size_t> AVLTree::recursiveGet(const AVLNode* node, const string& key) const {

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

vector<int> AVLTree::findRange(const std::string& lowKey, const string& highKey) const{

    vector<int> range;

    return recursiveFindRange(root, lowKey,highKey, range);

} //end findRange

vector<int> AVLTree::recursiveFindRange(const AVLNode* node, const std::string& lowKey, const std::string& highKey, vector<int>& range) const {

    if (node == nullptr) {
        return range;
    } //base case, returns the vector if the node is null

    if (node->key > lowKey) {
        recursiveFindRange(node->left, lowKey, highKey, range);
    } //if the key is greater than the node's key, checks its left key

    if (node -> key >= lowKey && node -> key <= highKey) {
        range.push_back(node->value);
    } //if the node matches the conditions, adds value to the vector range

    if (node -> key < highKey) {
        recursiveFindRange(node->right, lowKey, highKey, range);
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

    return root->height;

} //end getHeight

AVLTree::AVLTree(const AVLTree& other) {

    root = recursiveCopy(other.root);

} //end AVLTree copy constructor

AVLTree::AVLNode* AVLTree::recursiveCopy(const AVLTree::AVLNode* node) {

    if (node == nullptr) {
        return nullptr;
    } //base case; if the original node is null, sets the new node to null as well

    AVLNode* newNode = new AVLNode(); //creates the new node

    newNode->key = node->key;
    newNode->value = node->value;
    newNode->height = node->height; //copies the original node's values to the new one's

    newNode->left = recursiveCopy(node->left);
    newNode->right = recursiveCopy(node->right); //recursively copies the child nodes

    return newNode;

} //end recursiveCopy

void AVLTree::operator=(const AVLTree& other) {

    clear(root); //empties tree for reassignment

    root = recursiveCopy(other.root); //calls recursiveCopy to copy all nodes from the other tree

} //end operator=

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

    size_t depth = 0;

    avlTree.printTree(os, avlTree.root, depth);
    return os;

} //end operator<<

void AVLTree::printTree(ostream& os, AVLNode* node, size_t depth) const {

    if (node == nullptr) {
        return;
    } //base case

    printTree(os, node->right, depth + 1);

    for (size_t i = 0; i < depth; i++) {
        cout << "\t";
    } //adds tabs equal to the height of the node for formatting
    cout << "{" << node->key << ": " << node->value << "}" << endl;

    printTree(os, node->left, depth + 1);

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

    bool done = false;

    if (key == current->key) {
        removeNode(current);
        done = true;
    } //removes the node, deletes it from memory, and returns true when the node is found

    else if (key < current->key) {
        done = remove(current->left, key);
    } //if the key is less than the current node, checks the nodes left key

    else if (key > current->key) {
        done = remove(current->right, key);
    } //if the key is greater than the current node, checks the nodes right key

    else {
        return false; //error catcher
    }

    if (done) {
        balanceNode(current);
    } //balances node if node was removed correctly

    return done;

} //end remove

void AVLTree::balanceNode(AVLNode *&node) {

    if (node == nullptr) {
        return;
    } //base case

    setHeight(node);

    int balanceFactor = getBalance(node);
    int leftBalanceFactor = getBalance(node->left);
    int rightBalanceFactor = getBalance(node->right);

    if (balanceFactor > 1 && leftBalanceFactor >= 0) {
        rightRotation(node);
    }

    else if (balanceFactor > 1 && leftBalanceFactor < 0) {
        leftRotation(node->left);
        rightRotation(node);
    }

    else if (balanceFactor < -1 && rightBalanceFactor <= 0) {
        leftRotation(node);
    }

    else if (balanceFactor < -1 && rightBalanceFactor > 0) {
        rightRotation(node->right);
        leftRotation(node);
    } // all of these check the balanc factor and rotate as needed

    else {
        return;
    } //error catcher

} //end balanceNode

void AVLTree::setHeight(AVLNode* node) {

    if (node != nullptr) {

        int leftHeight;
        int rightHeight;

        if (node->left == nullptr) {
            leftHeight = -1;
        }
        else {
            leftHeight = node->left->getHeight();
        } //sets left height to height if not null

        if (node->right == nullptr) {
            rightHeight = -1;
        }
        else {
            rightHeight = node->right->getHeight();
        } //sets right height to height if not null

        node->height = 1 + max(leftHeight, rightHeight);

    } //end if

} //end setHeight

int AVLTree::getBalance(AVLNode* node) {

    if (node == nullptr) {
        return -1;
    } //sets balance factor to -1 if it's a leaf

    int leftHeight;
    int rightHeight;

    if (node->left == nullptr) {
        leftHeight = -1;
    }
    else {
        leftHeight = node->left->getHeight();
    } //sets left height to height if not null

    if (node->right == nullptr) {
        rightHeight = -1;
    }
    else {
        rightHeight = node->right->getHeight();
    } //sets right height to height if not null

    return leftHeight - rightHeight;

} //end getBalance

void AVLTree::rightRotation(AVLNode*& node) {

    AVLNode* leftNode = node->left;
    AVLNode* rotatedNode = leftNode->right;

    leftNode->right = node;
    node->left = rotatedNode; //rotates right

    setHeight(node);
    setHeight(rotatedNode); //resets heights of nodes

    node = leftNode;

} //end rightRotation

void AVLTree::leftRotation(AVLNode*& node) {

    AVLNode* rightNode = node->right;
    AVLNode* rotatedNode = rightNode->left;

    rightNode->left= node;
    node->right = rotatedNode; //rotates left

    setHeight(node);
    setHeight(rotatedNode); //resets heights of nodes

    node = rightNode;

} //end leftRotation
