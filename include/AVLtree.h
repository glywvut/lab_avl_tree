#include<iostream>

using namespace std;

template <typename T>
class AVL_Tree
{
public:
    class Node
    {
    public:
        T value;
        int height;
        Node* left;
        Node* right;

        Node(const T& val, const int& h = 1) : value(val), height(h), left(nullptr), right(nullptr) {}
    };

    AVL_Tree() : root(nullptr) {}

    bool search(Node* node, const T val) const
    {
        if (node == nullptr) return false;
        if (node->value == val) return true;
        if (val > node->value) return search(node->right, val);
        else return search(node->left, val);
    }

    void updateHeight(Node* node)
    {
        if (node == nullptr) return;
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    int getHeight(Node* node) const
    {
        return (node == nullptr) ? -1 : node->height;
    }

    int getBalance(Node* node) const
    {
        return (node == nullptr) ? 0 : (getHeight(node->right) - getHeight(node->left));
    }

    void rightRotate(Node*& node)
    {
        Node* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        updateHeight(node);
        updateHeight(newRoot);
        node = newRoot;
    }

    void leftRotate(Node*& node)
    {
        Node* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        updateHeight(node);
        updateHeight(newRoot);
        node = newRoot;
    }

    void makeBalance(Node* node)
    {
        int balance = getBalance(node);
        if (balance == -2)
        {
            if (getBalance(node->left) == 1) leftRotate(node->left);
            rightRotate(node);
        }
        else if (balance == 2)
        {
            if (getBalance(node->right) == -1) rightRotate(node->right);
            leftRotate(node);
        }
    }

    bool insert(Node*& node, const T val)
    {
        if (node == nullptr)
    {
        node = new Node(val);
        return true;
    }

    bool inserted = false;
    if (val < node->value)
    {
        inserted = insert(node->left, val);
    }
    else if (val > node->value)
    {
        inserted = insert(node->right, val);
    }
    else
    {
        return false; 
    }

    if (inserted)
    {
        updateHeight(node);
        makeBalance(node);
    }
    return inserted;
    }

    Node* findMin(Node* node)
    {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    Node* erase(Node* node, const T val)
    {
        if (node == nullptr) return nullptr;

        if (val < node->value)
        {
            node->left = erase(node->left, val);
        }
        else if (val > node->value)
        {
            node->right = erase(node->right, val);
        }
        else
        {
            if (node->left == nullptr || node->right == nullptr)
            {
                Node* temp = (node->left == nullptr) ? node->right : node->left;
                delete node;
                return temp;
            }
            else
            {
                Node* minRight = findMin(node->right);
                node->value = minRight->value;
                node->right = erase(node->right, minRight->value);
            }
        }

        if (node == nullptr) return nullptr;

        updateHeight(node);
        makeBalance(node);
        return node;
    }

public:
    Node* root;
};
