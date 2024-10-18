#include <iostream>
using namespace std;

typedef struct Node* Nodeptr;

struct Node
{
    int info;
    Nodeptr next;
    Nodeptr prev;
};

class LinkedList
{
private:
    Nodeptr List;
public:
    LinkedList();
    void traverse();
    Nodeptr find(int);
    void iAS(int);
    int dAS();
    void iAE(int);
    int dAE();
    void iAM(int);
    int dAM(int);
};

LinkedList::LinkedList()
{
    List = NULL;
}

void LinkedList::iAS(int x)
{
    Nodeptr p = new Node;
    p->info = x;
    p->prev = NULL;
    p->next = List;

    if (List != NULL)
        List->prev = p;

    List = p;
}

int LinkedList::dAS()
{
    if (List == NULL)
        return -999;

    Nodeptr p = List->next;
    int x = List->info;

    if (p != NULL)
        p->prev = NULL;

    delete List;
    List = p;

    return x;
}

void LinkedList::traverse()
{
    for (Nodeptr p = List; p != NULL; p = p->next)
    {
        cout << p->info << " ";
    }
    cout << endl;
}

void LinkedList::iAE(int x)
{
    if (List == NULL)
        iAS(x);
    else
    {
        Nodeptr p = List;

        while (p->next != NULL)
        {
            p = p->next;
        }

        Nodeptr q = new Node;
        q->info = x;
        q->next = NULL;
        q->prev = p;
        p->next = q;
    }
}

int LinkedList::dAE()
{
    if (List == NULL)
        return -999;

    if (List->next == NULL)
        return dAS();

    Nodeptr p = List;
    while (p->next != NULL)
    {
        p = p->next;
    }

    Nodeptr prevNode = p->prev;
    prevNode->next = NULL;

    int x = p->info;
    delete p;

    return x;
}

Nodeptr LinkedList::find(int x)
{
    for (Nodeptr p = List; p != NULL; p = p->next)
    {
        if (p->info == x)
        {
            return p;
        }
    }
    return NULL;
}

void LinkedList::iAM(int x)
{
    Nodeptr p = List;

    while (p != NULL && p->info != x)
    {
        p = p->next;
    }

    if (p == NULL || p->next == NULL)
    {
        iAE(x);
    }
    else
    {
        Nodeptr r = p->next;
        Nodeptr q = new Node;
        q->info = x;
        q->next = r;
        q->prev = p;
        p->next = q;
        r->prev = q;
    }
}

int LinkedList::dAM(int x)
{
    Nodeptr p = find(x);

    if (p == NULL)
        return -999;

    if (p->next == NULL)
        return dAE();

    Nodeptr prevNode = p->prev;
    Nodeptr nextNode = p->next;

    if (prevNode != NULL)
        prevNode->next = nextNode;

    if (nextNode != NULL)
        nextNode->prev = prevNode;

    int data = p->info;
    delete p;

    return data;
}

int main  ()
{

}