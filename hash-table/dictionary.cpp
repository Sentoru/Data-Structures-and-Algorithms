#include <iostream>
#include <string>
#define M 101
using namespace std;

struct Word
{
    string word; // English
    string type; // From type
    string mean; // Vietnamese
};

struct DictNode
{
    Word word;
    DictNode *next;
};

void init(DictNode *heads[])
{
    for (int i = 0; i < M; i++)
        heads[i] = NULL;
}

int hashFunc(Word w)
{
    int h = 0;

    for (int i = 0; i < w.word.length(); i++)
        h += (int)tolower(w.word[i]) * (i + 1);

    return h % M;
}

DictNode *createWord(Word w)
{
    DictNode *word = new DictNode;
    word->word = w;
    word->next = NULL;
    return word;
}

void addWord(DictNode *heads[], Word w)
{
    int h = hashFunc(w);
    DictNode *r = heads[h];

    DictNode *p = createWord(w);

    if (r == NULL) // Add first
        heads[h] = p;
    else // Add last
    {
        while (r->next != NULL)
            r = r->next;
        r->next = p;
    }
}

void display(DictNode *heads[])
{
    for (int i = 0; i < M; i++)
    {
        if (heads[i] != NULL)
        {
            cout << "=== BUCKET " << i << " ===\n";
            DictNode *p = heads[i];

            while (p != NULL)
            {
                cout << p->word.word << " (" << p->word.type << "): " << p->word.mean << endl;
                p = p->next;
            }
        }
    }
}

int main()
{
    cout << "DICTIONARY\n";
    Word w1, w2, w3, w4;
    w1.word = "Hello";
    w1.type = "Verb";
    w1.mean = "Xin chao";
    w2.word = "Teacher";
    w2.type = "Noun";
    w2.mean = "Giao vien";
    w3.word = "Good";
    w3.type = "Adjective";
    w3.mean = "Tot";
    w4.word = "Student";
    w4.type = "Noun";
    w4.mean = "Hoc sinh";
    
    DictNode *dicts[M];
    init(dicts);

    addWord(dicts, w1);
    addWord(dicts, w2);
    addWord(dicts, w3);
    addWord(dicts, w4);

    display(dicts);

    return 0;
}