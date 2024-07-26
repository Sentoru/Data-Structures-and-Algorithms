#include <iostream>
using namespace std;
#define M 7

struct Node
{
    int value;
    Node *next;
};

void initHash(Node *heads[])
{
    for (int i = 0; i < M; i++)
        heads[i] = NULL;    
}

Node *createNode(int x)
{
    Node *p = new Node;
    p->value = x;
    p->next = NULL;
    return p;
}

int hashFunc(int value)
{
    return value % M;
}

void insertNode(Node *heads[], int value)
{
    int h = hashFunc(value);
    Node *r = heads[h];
    Node *prev = NULL;

    while (r != NULL && r->value < value)
    {
        prev = r;
        r = r->next;
    }
    
    Node *p = createNode(value);
    if (prev == NULL) // Thêm vào đầu
    {
        heads[h] = p;
        p->next = r;
    }
    else if (r == NULL) // Thêm vào cuối
        prev->next = p;
    else // Thêm vào trước r
    {
        p->next = r;
        prev->next = p;
    }
}

void display(Node *heads[])
{
    for (int i = 0; i < M; i++)
    {
        if (heads[i] != NULL)
        {
            cout << "=== BUCKET " << i << " ===" << endl;
            Node *p = heads[i];

            while (p != NULL)
            {
                cout << p->value << "\t";
                p = p->next;
            }
            cout << endl;
        }          
    }
}

Node *search(Node *heads[], int value)
{
    int h = hashFunc(value);
    Node *r = heads[h];

    while (r != NULL && r->value != value)
        r = r->next;
    return r;
}

int main()
{
    Node *heads[M];
    initHash(heads);

    insertNode(heads, 17);
    insertNode(heads, 0);
    insertNode(heads, 34);
    insertNode(heads, 51);
    insertNode(heads, 68);
    insertNode(heads, 76);
    insertNode(heads, 25);

    display(heads);

    if (search(heads, 3) == NULL)
        cout << "KHONG TIM THAY 3\n";

    if (search(heads, 76) != NULL)
        cout << "TIM THAY 76\n";

    return 0;
}