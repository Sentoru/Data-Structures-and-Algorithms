#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#define MAX 100

struct SinhVien
{
    string hoTen;
    string mssv;
    string lop;
    string sdt;
    float dtb;
};

void addStudent(SinhVien &sv)
{
    cin.ignore();
    cout << "Nhap ho va ten: ";
    getline(cin, sv.hoTen, '\n');
    cout << "Nhap MSSV: ";
    getline(cin, sv.mssv, '\n');
    cout << "Nhap lop: ";
    getline(cin, sv.lop, '\n');
    cout << "Nhap sdt: ";
    getline(cin, sv.sdt, '\n');
    cout << "Nhap diem trung binh: ";
    cin >> sv.dtb;
}

void output(const SinhVien sv)
{
    cout << "=======================\n";
    cout << "Ho va ten: " << sv.hoTen << endl;
    cout << "MSSV: " << sv.mssv << endl;
    cout << "Lop: " << sv.lop << endl;
    cout << "So dien thoai: " << sv.sdt << endl;
    cout << "Diem trung binh: " << sv.dtb << endl;
    cout << "=======================\n";
}

ostream &operator <<(ostream &out, const SinhVien sv)
{;
    out << "=======================\n";
    out << "Ho va ten: " << sv.hoTen << endl;
    out << "MSSV: " << sv.mssv << endl;
    out << "Lop: " << sv.lop << endl;
    out << "So dien thoai: " << sv.sdt << endl;
    out << "Diem trung binh: " << sv.dtb << endl;
    out << "=======================\n";
    return out;
}

// Setting Double Linked List
struct Node
{
    SinhVien info;
    Node *next, *prev;
};

struct DoubleLinkedList
{
    Node *head;
    Node *tail;
};

void init(DoubleLinkedList &dl)
{
    dl.head = dl.tail = NULL;
}

Node *createNode(SinhVien sv)
{
    Node *p = new Node;
    p->info = sv;
    p->next = NULL;
    p->prev = NULL;
    return p;
}

void addFirst(DoubleLinkedList &dl, SinhVien sv)
{
    Node *p = createNode(sv);
    if (dl.head == NULL)
        dl.head = dl.tail = p;
    else
    {
        p->next = dl.head;
        dl.head->prev = p;
        dl.head = p;
    }
}

void addLast(DoubleLinkedList &dl, SinhVien sv)
{
    Node *p = createNode(sv);
    if (dl.head == NULL)
        dl.head = dl.tail = p;
    else
    {
        dl.tail->next = p;
        p->prev = dl.tail;
        dl.tail = p;
    }
}

void addAfter(DoubleLinkedList &dl, SinhVien sv)
{
    Node *p = createNode(sv);
    Node *q = dl.head;
    if (dl.head == NULL)
        dl.head = dl.tail = p;
    else
    {
        while (q != NULL)
        {
            if (q->info.dtb > p->info.dtb && q->next->info.dtb < p->info.dtb)
            {
                q->next->prev = p;
                p->next = q->next;

                q->next = p;
                p->prev = q;
            }
            q = q->next;
        }
    }
}

void insertStudent(DoubleLinkedList &dl)
{
    int chon = 1;
    while (chon != 0)
    {
        SinhVien sv;
        addStudent(sv);
        addFirst(dl, sv);
        cout << "Continue? (1-Yes/ 0-No): ";
        cin >> chon;
    }
}

void deleteFirst(DoubleLinkedList &dl)
{
    if (dl.head != NULL)
    {
        Node *p = dl.head;
        dl.head = p->next;

        if (p->next != NULL)
        {
            p->next->prev = NULL;
            p->next = NULL;
        }
        delete p;
    }
}

void deleteLast(DoubleLinkedList &dl)
{
    if (dl.head != NULL)
    {
        Node *p = dl.tail;
        dl.tail = p->prev;

        if (p->prev != NULL)
        {
            p->prev->next = NULL;
            p->prev = NULL;
        }
        delete p;
    }
}

void deleteAfter(DoubleLinkedList &dl, string lop)
{
    if (dl.head != NULL)
    {
        Node *p = dl.head;
        while (p != NULL && p->info.lop != lop)
            p = p->next;
        if (p != NULL)
        {
            p->next->prev = p->prev;
            p->prev->next = p->next;

            p->prev = NULL;
            p->next = NULL;
        }
        delete p;
    }
}

void printListFromHead(DoubleLinkedList dl)
{
    if (dl.head != NULL)
    {
        Node *p = dl.head;
        while (p != NULL)
        {
            cout << p->info;
            // output(p->info);
            p = p->next;
        }
        cout << endl;
    }
}

void printListFromTail(DoubleLinkedList dl)
{
    if (dl.tail != NULL)
    {
        Node *p = dl.tail;
        while (p != NULL)
        {
            cout << p->info;
            // output(p->info);
            p = p->prev;
        }
        cout << endl;
    }
}

void printWithCondition(DoubleLinkedList dl)
{
    int conditions[5] = {0}; // Mảng để lưu trữ các điều kiện được chọn
    int choice;
    cout << "Select the conditions to print (0 to stop):\n";
    cout << "1. Ho va ten\n";
    cout << "2. MSSV\n";
    cout << "3. Lop\n";
    cout << "4. So dien thoai\n";
    cout << "5. Diem trung binh\n";

    do
    {
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice >= 1 && choice <= 5)
            conditions[choice - 1] = 1; // Đánh dấu điều kiện được chọn
    } while (choice != 0);

    if (dl.head != NULL)
    {
        Node *p = dl.head;
        while (p != NULL)
        {
            for (int i = 0; i < 5; i++)
            {
                if (conditions[i] == 1)
                {
                    switch (i + 1)
                    {
                        case 1:
                            cout << "Ho va ten: " << p->info.hoTen << endl;
                            break;
                        case 2:
                            cout << "MSSV: " << p->info.mssv << endl;
                            break;
                        case 3:
                            cout << "Lop: " << p->info.lop << endl;
                            break;
                        case 4:
                            cout << "So dien thoai: " << p->info.sdt << endl;
                            break;
                        case 5:
                            cout << "Diem trung binh: " << p->info.dtb << endl;
                            break;
                    }
                }
            }
            cout << endl;
            p = p->next;
        }
    }
}

void checkInfo(DoubleLinkedList dl, string hoTen, string lop)
{
    if (dl.head != NULL)
    {
        Node *p = dl.head;
        while (p != NULL)
        {
            if (p->info.hoTen == hoTen && p->info.lop == lop)
            {
                cout << "Sinh vien da ton tai!\n";
                cout << "Thong tin sinh vien:\n";
                output(p->info);
                return;
            }
            p = p->next;
        }
        if (p == NULL)
            cout << "Sinh vien khong ton tai!\n";
    }
}

void deleteStudent(DoubleLinkedList &dl, string lop)
{
    if (dl.head != NULL)
    {
        Node *p = dl.head;
        while (p != NULL)
        {
            if (p->info.lop == lop)
            {
                if (p->prev == NULL)
                    deleteFirst(dl);
                else if (p->next == NULL)
                    deleteLast(dl);
                else
                    deleteAfter(dl, lop);
                return;
            }
            p = p->next;
        }
    }
}

void sortByGrade(DoubleLinkedList &dl)
{
    if (dl.head != NULL)
    {
        for (Node* i = dl.head; i->next != NULL; i = i->next)
        {
            for (Node* j = i->next; j != NULL; j = j->next)
            {
                if (i->info.dtb < j->info.dtb)
                    swap(i->info, j->info);
            }
        }
    }
}

void inputStudent(DoubleLinkedList &dl, SinhVien sv)
{
    if (dl.head != NULL)
    {
        Node *p = dl.head;
        while (p != NULL)
        {
            if (dl.head->info.dtb < sv.dtb)
            {
                addFirst(dl, sv);
                return;
            }
            else if (dl.tail->info.dtb > sv.dtb)
            {
                addLast(dl, sv);
                return;
            }
            else
            {
                if (p->info.dtb > sv.dtb && p->next->info.dtb < sv.dtb)
                {
                    addAfter(dl, sv);
                    return;
                }
            }
            p = p->next;
        }
    }
}

void outputFlexible(DoubleLinkedList dl)
{
    if (dl.head != NULL)
    {
        Node *p = dl.head;
        int chon;
        while (p != NULL)
        {
            cout << p->info;
            cout << "Chon 1 de tiep tuc, 2 de quay lai: ";
            cin >> chon;
            if (chon == 1 && p->next != NULL)
                p = p->next;
            if (chon == 2 && p->prev != NULL)
                p = p->prev;
        }
    }
}

void outputFile(DoubleLinkedList dl)
{
    ofstream outFile("DoubleLinkedList.txt");
    if (outFile.is_open())
    {
        Node *p = dl.head;
        while (p != NULL)
        {
            outFile << p->info << endl;
            p = p ->next;
        }
        outFile.close();
    }
}

void destroy(DoubleLinkedList &dl)
{
    while (dl.head != NULL)
        deleteFirst(dl);
    dl.head = dl.tail = NULL;
}

int main()
{
    DoubleLinkedList dl;
    init(dl);
    SinhVien sv;

    insertStudent(dl);

    outputFile(dl);

    destroy(dl);
    cout << "=== DESTROY LIST ===\n";
    printListFromTail(dl);

    return 0;
}