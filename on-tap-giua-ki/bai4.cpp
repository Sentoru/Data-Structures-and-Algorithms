#include <iostream>
using namespace std;

#define MAX 50

// Khai báo cấu trúc BST
struct Node
{
    int key;
    Node *left;
    Node *right;
};

void init(Node *&root)
{
    root = NULL;
}

Node *createNode(int x)
{
    Node *p = new Node;
    p->key = x;
    p->left = NULL;
    p->right = NULL;
    return p;
}

void insertNode(Node *&root, int x)
{
    if (root == NULL)
        root = createNode(x);
    else
    {
        if (root->key == x)
            return;
        if (root->key < x)
            insertNode(root->right, x);
        else
            insertNode(root->left, x);
    }
}

Node *search(Node *root, int x)
{
    if (root != NULL)
    {
        if (root->key == x)
            return root;
        if (root->key > x)
            return search(root->left, x);
        else
            return search(root->right, x);
    }
    return NULL;
}

// Thế mạng phần từ trái nhất bên phải
void findAndReplace1(Node *&root, Node *&p)
{
    if (root->left != NULL) // Chưa phải trái nhất
        findAndReplace1(root->left, p);
    else
    {
        p->key = root->key;
        p = root;
        root = root->right;
    }
}

void deleteNode(Node *&root, int x)
{
    if (root != NULL)
    {
        if (root->key > x)
            deleteNode(root->left, x);
        else if (root->key < x)
            deleteNode(root->right, x);
        else // Node hiện tại là cần xóa
        {
            Node *p = root;
            if (root->left == NULL)
                root = root->right;
            else if (root->right == NULL)
                root = root->left;
            else
                findAndReplace1(root->right, p);
            delete p;
        }
    }
}

// Khai báo cấu trúc Stack
struct Stack
{
    Node *a[MAX];
    int top;
};

void initStack(Stack &s)
{
    s.top = -1;
}

void push(Stack &s, Node *x)
{
    if (s.top < MAX)
        s.a[++s.top] = x;
}

bool isEmpty(Stack s)
{
    return s.top == -1;
}

Node *pop(Stack &s)
{
    if (!isEmpty(s))
        return s.a[s.top--];
    return NULL;
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

void enQueue(Queue &q, int x)
{
    LinkedList *p = new LinkedList;
    p->data = x;
    p->next = NULL;

    if (q.rear == NULL)
        q.front = q.rear = p;
    else
    {
        q.rear->next = p;
        q.rear = p;
    }
}

int deQueue(Queue &q)
{
    if (q.front == NULL)
    {
        cout << "Queue is empty!\n";
        return -1;
    }

    int value = q.front->data;
    LinkedList *temp = q.front;
    q.front = q.front->next;

    if (q.front == NULL)
        q.rear = NULL;

    delete temp;
    return value;
}

bool isEmpty(Queue q)
{
    return q.front == NULL;
}

void printQueue(Queue q)
{
    LinkedList *temp = q.front;
    while (temp != NULL)
    {
        cout << temp->data << "\t";
        temp = temp->next;
    }
    cout << endl;
}

void destroyQueue(Queue &q)
{
    while (!isEmpty(q))
    {
        LinkedList *temp = q.front;
        q.front = q.front->next;
        delete temp;
    }
    q.rear = NULL;
}

// Duyệt cây
void LNR(Node *root)
{
    if (root != NULL)
    {
        LNR(root->left);
        cout << root->key << "\t";
        LNR(root->right);
    }
}

void LRN(Node *root)
{
    if (root != NULL)
    {
        LRN(root->left);
        LRN(root->right);
        cout << root->key << "\t";
    }
}

void NLR(Node *root)
{
    if (root != NULL)
    {
        cout << root->key << "\t";
        NLR(root->left);
        NLR(root->right);
    }
}

void LNRnoRec(Node *root)
{
    Stack s;
    initStack(s);

    Node *current = root;

    while (current != NULL || !isEmpty(s))
    {
        while (current != NULL)
        {
            push(s, current);
            current = current->left;
        }

        current = pop(s);
        cout << current->key << "\t";
        current = current->right;
    }
}

void NLRnoRec(Node *root)
{
    Stack s;
    initStack(s);

    Node *current = root;

    while (current != NULL || !isEmpty(s))
    {
        while (current != NULL)
        {
            cout << current->key << "\t";
            push(s, current);
            current = current->left;
        }

        current = pop(s);
        current = current->right;
    }
}

void LRNnoRec(Node *root)
{
    Stack s1, s2;
    initStack(s1);
    initStack(s2);
    push(s1, root);
    while (!isEmpty(s1))
    {
        Node *current = pop(s1);
        push(s2, current);
        if (current->left)
            push(s1, current->left);
        if (current->right)
            push(s1, current->right);
    }
    
    while (!isEmpty(s2))
    {
        Node *temp = pop(s2);
        cout << temp->key << "\t";
    }
}

void destroy(Node *&root)
{
    if (root != NULL)
    {
        destroy(root->left);
        destroy(root->right);
        delete root;
    }
}

int main()
{
    Queue q;
    initQueue(q);

    enQueue(q, 4);
    enQueue(q, 6);
    enQueue(q, 1);
    enQueue(q, 8);
    enQueue(q, 2);
    enQueue(q, 9);
    enQueue(q, 5);

    printQueue(q);

    deQueue(q);
    printQueue(q);

    destroyQueue(q);
    cout << "Da pha huy Queue!\n";

    return 0;
}