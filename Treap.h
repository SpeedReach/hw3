//
// Created by gomil on 2022/12/24.
//

#ifndef SCHOOLHW_TREAP_H
#define SCHOOLHW_TREAP_H


// C++ program to demonstrate search, insert and delete in Treap
#include <bits/stdc++.h>
#include "Collection.h"
using namespace std;

// A Treap Node
struct TreapNode
{
    int key, priority;
    TreapNode *left, *right;
};

/* T1, T2 and T3 are subtrees of the tree rooted with y
(on left side) or x (on right side)
				y							 x
			/ \	 Right Rotation		 / \
			x T3 – – – – – – – >	 T1 y
			/ \	 < - - - - - - -		 / \
			T1 T2	 Left Rotation		 T2 T3 */

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
TreapNode *rightRotate(TreapNode *y)
{
    TreapNode *x = y->left, *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
TreapNode *leftRotate(TreapNode *x)
{
    TreapNode *y = x->right, *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Return new root
    return y;
}

/* Utility function to add a new key */
TreapNode* newNode(int key)
{
    TreapNode* temp = new TreapNode;
    temp->key = key;
    temp->priority = rand()%100;
    temp->left = temp->right = NULL;
    return temp;
}

// C function to search a given key in a given BST
TreapNode* search(TreapNode* root, int key)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->key == key)
        return root;

    // Key is greater than root's key
    if (root->key < key)
        return search(root->right, key);

    // Key is smaller than root's key
    return search(root->left, key);
}

/* Recursive implementation of insertion in Treap */
TreapNode* treapInsert(TreapNode* root, int key)
{
    // If root is NULL, create a new node and return it
    if (!root)
        return newNode(key);

    // If key is smaller than root
    if (key <= root->key)
    {
        // Insert in left subtree
        root->left =  treapInsert(root->left, key);

        // Fix Heap property if it is violated
        if (root->left->priority > root->priority)
            root = rightRotate(root);
    }
    else // If key is greater
    {
        // Insert in right subtree
        root->right =  treapInsert(root->right, key);

        // Fix Heap property if it is violated
        if (root->right->priority > root->priority)
            root = leftRotate(root);
    }
    return root;
}

/* Recursive implementation of Delete() */
TreapNode* deleteNode(TreapNode* root, int key)
{
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);

        // IF KEY IS AT ROOT

        // If left is NULL
    else if (root->left == NULL)
    {
        TreapNode *temp = root->right;
        delete(root);
        root = temp; // Make right child as root
    }

        // If Right is NULL
    else if (root->right == NULL)
    {
        TreapNode *temp = root->left;
        delete(root);
        root = temp; // Make left child as root
    }

        // If key is at root and both left and right are not NULL
    else if (root->left->priority < root->right->priority)
    {
        root = leftRotate(root);
        root->left = deleteNode(root->left, key);
    }
    else
    {
        root = rightRotate(root);
        root->right = deleteNode(root->right, key);
    }

    return root;
}

// A utility function to print tree
void treapInOrder(TreapNode* root)
{
    if (root)
    {
        treapInOrder(root->left);
        cout << "key: "<< root->key << " | priority: %d "
             << root->priority;
        if (root->left)
            cout << " | left child: " << root->left->key;
        if (root->right)
            cout << " | right child: " << root->right->key;
        cout << endl;
        treapInOrder(root->right);
    }
}

class Treap: public Collection{
public:

    void insert(int value){
        root =  treapInsert(root,value);
    }

    bool search(int value){
        if (root)
        {
            TreapNode* node = root;
            while (node != nullptr){
                if(node->key == value) return true;
                if(value > node->key) node = node->right;
                else node = node->left;
            }
        }
        return false;
    }
    void print(){
        treapInOrder(root);
    }
    void deleteChildren(TreapNode* node){
        if(node == nullptr) return;
        if(node->left){
            deleteChildren(node->left);
        }
        if(node->right){
            deleteChildren(node->right);
        }
        delete node;
    }
    ~Treap(){
        deleteChildren(root);
    }
    string name(){return "Treap";}
private:
    TreapNode* root = nullptr;
};

#endif //SCHOOLHW_TREAP_H
