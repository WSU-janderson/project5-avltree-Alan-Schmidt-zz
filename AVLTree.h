/*
*Alan Schmidt
 *AVLTree Project
 *This header file contains all of the method headers and global variables used
 *through the project. As stated in the cpp file, I don't have time to add a block comment above
 *each method header, but there are many inline comments in the cpp file that
 *I typed as I was programming, so hopefully those will suffice.
 */

#ifndef AVLTREE_H
#define AVLTREE_H
#include <string>
#include <vector>
#include <optional>

using namespace std;

class AVLTree {
public:
    using KeyType = string;
    using ValueType = size_t;

    AVLTree();

    bool insert(const string& key, size_t value);

    bool remove(const string& key);

    bool contains(const string& key) const;

    optional<size_t> get(const string& key) const;

    size_t& operator[](const string& key);

    vector<int> findRange( const string& lowKey, const string& highKey) const;

    vector<string> keys() const;

    size_t size() const;

    size_t getHeight() const;

    AVLTree(const AVLTree& other);

    void operator=(const AVLTree& other);

    ~AVLTree();

    friend ostream& operator<<(ostream& os, const AVLTree & avlTree);

 //declarations provided at start
protected:
    class AVLNode {
    public:
        KeyType key;
        ValueType value;
        size_t height;

        AVLNode* left;
        AVLNode* right;

        // 0, 1 or 2
        size_t numChildren() const;
        // true or false
        bool isLeaf() const;
        // number of hops to deepest leaf node
        size_t getHeight() const;


    };

    private:
    AVLNode* root;
    size_t totalSize = 0;

    bool recursiveInsert(AVLNode*& node, const string& key, size_t value);

    bool recursiveContains(const AVLNode* node, const string& key) const;

    optional<size_t> recursiveGet(const AVLNode* node, const string& key) const;

    AVLNode& recursiveBracket(AVLNode*& node, const string& key);

    vector<int> recursiveFindRange(const AVLNode* node, const std::string& lowKey, const std::string& highKey, vector<int>& range) const;

    vector<string> recursiveKeys(const AVLNode* node) const;

    AVLNode* recursiveCopy(const AVLNode* node);

    void clear(AVLNode* node);

    void printTree(ostream& os, AVLNode* node, size_t depth) const;

    /* Helper methods for remove */
    // this overloaded remove will do the recursion to remove the node
    bool remove(AVLNode*& current, KeyType key);
    // removeNode contains the logic for actually removing a node based on the numebr of children
    bool removeNode(AVLNode*& current);
    // You will implement this, but it is needed for removeNode()
    void balanceNode(AVLNode*& node);

    void setHeight(AVLNode* node);

    int getBalance(AVLNode* node);

    void rightRotation(AVLNode*& node);

    void leftRotation(AVLNode*& node);

}; //end class AVLTree

#endif //AVLTREE_H
