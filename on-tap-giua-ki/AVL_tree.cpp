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

int getHeight(Node *root)
{
    if (root == NULL)
        return 0;
    return root->height;
}

void updateHeight(Node *root)
{
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
}

int getBalance(Node *root)
{
    if (root == NULL)
        return 0;
    return getHeight(root->left) - getHeight(root->right);
}

Node *rotateRight(Node *root)
{
    Node *temp = root->left;
    root->left = temp->right;
    temp->right = root;
    updateHeight(root);
    updateHeight(temp);
    return temp;
}

Node *rotateLeft(Node *root)
{
    Node *temp = root->right;
    root->right = temp->left;
    temp->left = root;
    updateHeight(root);
    updateHeight(temp);
    return temp;
}

Node *rebalance(Node *root)
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

Node *insert(Node *&root, int x)
{
    if (root == NULL)
        root = createNode(x);
    else if (root->key > x)
        root->left = insert(root->left, x);
    else if (root->key < x)
        root->right = insert(root->right, x);
    else
        return root;
    updateHeight(root);
    root = rebalance(root);
    return root;
}

Node *remove(Node *&root, int x)
{
    if (root == NULL)
        return root;
    if (root->key > x)
        root->left = remove(root->left, x);
    else if (root->key < x)
        root->right = remove(root->right, x);
    // Node need to removed
    else
    {
        if (root->left == NULL)
        {
            Node *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root->left;
            delete root;
            return temp;
        }
        // Use most left of right side
        Node *temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;
        root->key = temp->key;
        root->right = remove(root->right, temp->key);
    }
    updateHeight(root);
    root = rebalance(root);
    return root;
}

void NLR(Node* root)
{
    if (root != NULL)
    {
        cout << root->key << " ";
        NLR(root->left);
        NLR(root->right);
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

// Khai báo cấu trúc Queue
struct LinkedList
{
    int data;
    LinkedList *next;
};

struct Queue
{
    LinkedList *front;
    LinkedList *rear;
};

void initQueue(Queue &q)
{
    q.front = q.rear = NULL;
}

bool isEmpty(Queue q)
{
    return q.front == NULL;
}

void enQueue(Queue &q, LinkedList *x)
{
    LinkedList *p = new LinkedList;
    p->data = x->data;
    p->next = NULL;

    if (q.rear == NULL)
        q.front = q.rear = NULL;
    else
    {
        q.rear->next = p;
        q.rear = p;
    }
}

LinkedList *deQueue(Queue &q)
{
    if (q.front == NULL)
        return NULL;
    
    Node *value = q.front->data;
    LinkedList *temp = q.front;
    q.front = q.front->next;

    if (q.front == NULL)
        q.rear = NULL;

    temp->next = NULL;
    delete temp;
    return value;
}

// Duyệt cây theo chiều rộng
void printLevelOrder(Node *root)
{
    if (root == NULL)
        return;

    Queue q;
    initQueue(q);

    enQueue(q, root);

    while (!isEmpty(q))
    {
        int value = deQueue(q);
        cout << value << "\t";

        if (root->left != NULL)
            enQueue(q, root->left->key);
        if (root->right != NULL)
            enQueue(q, root->right->key);

        Node *temp = root;
        root = NULL;

        if (!isEmpty(q))
        {
            root = createNode(deQueue(q));
            temp = root;
        }
    }
}

int main()
{
    Node *root;
    init(root);

    insert(root, 25);
    insert(root, 50);
    insert(root, 10);
    insert(root, 60);
    insert(root, 5);
    insert(root, 15);
    insert(root, 40);

    printLevelOrder(root);
    cout << endl;

    destroyTree(root);
    NLR(root);

    return 0;
}