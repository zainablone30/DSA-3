#include <iostream>
#include <fstream>  // For file operations
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
    void iAS(int);   // Insertion at Start
    int dAS();       // Deletion from Start
    void iAE(int);   // Insertion at End
    int dAE();       // Deletion from End
    void iAM(int);   // Insertion at Middle
    int dAM(int);    // Deletion from Middle
    void saveToFile(const string& filename);
    void loadFromFile(const string& filename);
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
    int pos, count = 0;

    cout << "Enter position to insert: ";
    cin >> pos;

    if (pos == 1)
    {
        iAS(x);
        return;
    }

    while (p != NULL && count < pos - 1)
    {
        p = p->next;
        count++;
    }

    if (p == NULL)
    {
        cout << "Position out of bounds. Inserting at end." << endl;
        iAE(x);
    }
    else
    {
        Nodeptr q = new Node;
        q->info = x;
        q->next = p->next;
        q->prev = p;

        if (p->next != NULL)
            p->next->prev = q;

        p->next = q;
    }
}

int LinkedList::dAM(int pos)
{
    if (List == NULL)
        return -999;

    if (pos == 1)
        return dAS();

    Nodeptr p = List;
    int count = 1;

    while (p != NULL && count < pos)
    {
        p = p->next;
        count++;
    }

    if (p == NULL)
        return -999;

    if (p->next != NULL)
        p->next->prev = p->prev;

    if (p->prev != NULL)
        p->prev->next = p->next;

    int x = p->info;
    delete p;

    return x;
}

void LinkedList::saveToFile(const string& filename)
{
    ofstream file;
    file.open(filename);

    for (Nodeptr p = List; p != NULL; p = p->next)
    {
        file << p->info << " ";
    }

    file.close();
    cout << "List saved to " << filename << endl;
}

void LinkedList::loadFromFile(const string& filename)
{
    ifstream file;
    file.open(filename);

    int x;
    while (file >> x)
    {
        iAE(x);  // Insert each value at the end of the list
    }

    file.close();
    cout << "List loaded from " << filename << endl;
}

// Main menu system to interact with the user
int main()
{
    LinkedList list;
    int choice, value, pos;
    string filename = "list_data.txt";

    // Load previous data from file if exists
    list.loadFromFile(filename);

    do
    {
        cout << "\nMenu:\n";
        cout << "1. Insertion at the start" << endl;
        cout << "2. Insertion at the end" << endl;
        cout << "3. Insertion at the middle" << endl;
        cout << "4. Deletion from the start" << endl;
        cout << "5. Deletion from the end" << endl;
        cout << "6. Deletion from the middle" << endl;
        cout << "7. Search for an element" << endl;
        cout << "8. Display the list" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value to insert at front: ";
            cin >> value;
            list.iAS(value);
            break;
        case 2:
            cout << "Enter value to insert at end: ";
            cin >> value;
            list.iAE(value);
            break;
        case 3:
            cout << "Enter value to insert in the middle: ";
            cin >> value;
            list.iAM(value);
            break;
        case 4:
            value = list.dAS();
            if (value == -999)
                cout << "List is empty.\n";
            else
                cout << "Deleted value from the start: " << value << endl;
            break;
        case 5:
            value = list.dAE();
            if (value == -999)
                cout << "List is empty.\n";
            else
                cout << "Deleted value from the end: " << value << endl;
            break;
        case 6:
            cout << "Enter position to delete from: ";
            cin >> pos;
            value = list.dAM(pos);
            if (value == -999)
                cout << "Invalid position or list is empty.\n";
            else
                cout << "Deleted value from position " << pos << ": " << value << endl;
            break;
        case 7:
            cout << "Enter value to search: ";
            cin >> value;
            if (list.find(value) != NULL)
                cout << "Element " << value << " found in the list.\n";
            else
                cout << "Element " << value << " not found.\n";
            break;
        case 8:
            cout << "The list is: ";
            list.traverse();
            break;
        case 9:
            cout << "Exiting program...\n";
            list.saveToFile(filename);
            break;
        default:
            cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 9);

    return 0;
}
