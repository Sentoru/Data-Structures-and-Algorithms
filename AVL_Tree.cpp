#include <iostream>
using namespace std;

struct Node
{
    int key, height;
    Node *left, *right;
};

void init(Node *&root)
{
    root = NULL;
}

Node *createNode(int x)
{
    Node *p = new Node;
    p->key = x;
    p->left = p->right = NULL;
    p->height = 1;
    return p;
}

int getHeight(Node* root)
{
    if (root == NULL)
        return 0;
    return root->height;
}

void updateHeight(Node* root)
{
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
}

int getBalance(Node* root)
{
    if (root == NULL)
        return 0;
    return getHeight(root->left) - getHeight(root->right);
}

Node* rotateRight(Node* root)
{
    Node* temp = root->left;
    root->left = temp->right;
    temp->right = root;
    updateHeight(root);
    updateHeight(temp);
    return temp;
}

Node* rotateLeft(Node* root)
{
    Node* temp = root->right;
    root->right = temp->left;
    temp->left = root;
    updateHeight(root);
    updateHeight(temp);
    return temp;
}

Node* rebalance(Node* root)
{
    int balanceFactor = getBalance(root);
    // Left heavy
    if (balanceFactor > 1)
    {
        // Left - Left
        if (getHeight(root->left->left) >= getHeight(root->left->right))
            root = rotateRight(root);
        // Left - Right
        else
        {
            root->left = rotateLeft(root->left);
            root = rotateRight(root);
        }
    }

    // Right heavy
    else if (balanceFactor < -1)
    {
        // Right - Right
        if (getHeight(root->right->right) >= getHeight(root->right->left))
            root = rotateLeft(root);
        // Right - Left
        else
        {
            root->right = rotateRight(root->right);
            root = rotateLeft(root);
        }
    }
    return root;
}

Node *insert(Node *&root, int key)
{
    if (root == NULL)
        root = createNode(key);
    else if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root;
    updateHeight(root);
    root = rebalance(root);
    return root;
}

Node* remove(Node *&root, int key) {
    if (root == NULL)
        return root;
    if (key < root->key)
        root->left = remove(root->left, key);
    else if (key > root->key)
        root->right = remove(root->right, key);
    // Node need to removed
    else
    {
        if (root->left == NULL)
        {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        // Use most left of right side
        Node* temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;
        root->key = temp->key;
        root->right = remove(root->right, temp->key);
    }
    updateHeight(root);
    root = rebalance(root);
    return root;
}

void LNR(Node* root)
{
    if (root != NULL)
    {
        LNR(root->left);
        cout << root->key << " ";
        LNR(root->right);
    }
}

void destroyTree(Node *&root)
{
    if (root == NULL)
        return;
    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
    root = NULL;
}

int main()
{
    Node *root;
    init(root);

    insert(root, 30);
    insert(root, 50);
    insert(root, 20);
    insert(root, 31);
    insert(root, 59);
    insert(root, 22);

    LNR(root);
    cout << endl;

    remove(root, 30);
    LNR(root);
    cout << endl;

    destroyTree(root);
    LNR(root);
    cout << endl;

    return 0;
}
