#include <iostream>
using namespace std;

struct Node
{
    int key, height;
    Node *left, *right;
};

int getHeight(Node* node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

void updateHeight(Node* node)
{
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

int getBalance(Node* node)
{
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

Node* rotateRight(Node* node) {
    Node* temp = node->left;
    node->left = temp->right;
    temp->right = node;
    updateHeight(node);
    updateHeight(temp);
    return temp;
}

Node* rotateLeft(Node* node) {
    Node* temp = node->right;
    node->right = temp->left;
    temp->left = node;
    updateHeight(node);
    updateHeight(temp);
    return temp;
}

Node* rebalance(Node* node)
{
    int balanceFactor = getBalance(node);
    // Left heavy
    if (balanceFactor > 1)
    {
        // Left - Left
        if (getHeight(node->left->left) >= getHeight(node->left->right))
            node = rotateRight(node);
        // Left - Right
        else
        {
            node->left = rotateLeft(node->left);
            node = rotateRight(node);
        }
    }

    // Right heavy
    else if (balanceFactor < -1)
    {
        // Right - Right
        if (getHeight(node->right->right) >= getHeight(node->right->left))
            node = rotateLeft(node);
        // Right - Left
        else
        {
            node->right = rotateRight(node->right);
            node = rotateLeft(node);
        }
    }
    return node;
}

Node* insert(Node* node, int key)
{
    if (node == NULL)
    {
        node = new Node();
        node->key = key;
        node->left = NULL;
        node->right = NULL;
        node->height = 1;
    }
    else if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;
    updateHeight(node);
    node = rebalance(node);
    return node;
}

Node* remove(Node* node, int key) {
    if (node == NULL)
        return node;
    if (key < node->key)
        node->left = remove(node->left, key);
    else if (key > node->key)
        node->right = remove(node->right, key);
    // Node need to removed
    else
    {
        if (node->left == NULL)
        {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == NULL)
        {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        // Use most left of right side
        Node* temp = node->right;
        while (temp->left != NULL)
            temp = temp->left;
        node->key = temp->key;
        node->right = remove(node->right, temp->key);
    }
    updateHeight(node);
    node = rebalance(node);
    return node;
}

void LNR(Node* node)
{
    if (node != NULL)
    {
        LNR(node->left);
        cout << node->key << " ";
        LNR(node->right);
    }
}

void destroyTree(Node *&node)
{
    if (node == NULL)
        return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
    node = NULL;
}

int main()
{
    Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    LNR(root);
    cout << endl;

    root = remove(root, 25);
    LNR(root);
    cout << endl;

    destroyTree(root);
    LNR(root);
    cout << endl;

    return 0;
}