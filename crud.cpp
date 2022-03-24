using namespace std;
#include <bits/stdc++.h>
#include <conio.h>

bool isDataReaded;
const string filename("records.dat");

class Student
{
public:
    int roll;
    char name[20];
    Student *next;

    Student()
    {
    }

    Student(int r, char *n)
    {
        roll = r;
        strcpy(name, n);
        next = NULL;
    }
};

bool isEmpty(Student *head)
{
    return (head == NULL) ? true : false;
}

void addNode(Student *&head, int r, char *n)
{
    Student *node = new Student(r, n);

    if (isEmpty(head))
    {
        head = node;
        return;
    }

    Student *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = node;
}

void display(Student *head)
{

    if (isEmpty(head))
    {
        cout << "Your record file is empty" << endl;
        return;
    }
    cout << left << setw(10) << "Roll No." << left << setw(20) << "Name" << endl;

    while (head != NULL)
    {
        cout << left << setw(10) << head->roll << left << setw(20) << head->name << endl;
        head = head->next;
    }
}

void readFromDisk(Student *&head)
{
    ifstream filein;
    filein.open(filename, ios::in | ios::binary);

    if (filein.fail())
    {
        ofstream fileout;
        fileout.open(filename, ios::out);
        fileout.close();
        filein.open(filename, ios::in | ios::binary);
        (filein.fail()) ? isDataReaded = false : isDataReaded = true;
    }

    Student temp;
    filein.read((char *)&temp, sizeof(temp));
    while (!filein.eof())
    {
        addNode(head, temp.roll, temp.name);
        filein.read((char *)&temp, sizeof(temp));
    }
    filein.close();
    isDataReaded = true;
}

void storeData(Student *&head)
{
    if (isEmpty(head))
    {
        return;
    }

    ofstream file;
    (isDataReaded) ? (file.open(filename, ios::out | ios::binary)) : file.open(filename, ios::app | ios::binary);

    if (file.fail())
    {
        cout << "File not found!" << endl;
        return;
    }
    Student *temp = head;
    while (temp != NULL)
    {
        file.write((char *)temp, sizeof(*temp));
        temp = temp->next;
    }
    file.close();
}

void search(Student *head, int key)
{
    bool flag;
    while (head != NULL)
    {
        if (head->roll == key)
        {
            cout << "Record found with roll number " << key << endl;
            cout << endl
                 << left << setw(10) << "Roll No." << left << setw(20) << "Name" << endl;
            cout << left << setw(10) << head->roll << left << setw(20) << head->name << endl;
            flag = true;
        }
        head = head->next;
    }
    if (!flag)
    {
        cout << "Record not found with roll number " << key << endl;
    }
}

void updateRecord(Student *&head, int key)
{
    bool flag;
    char name[20];
    int choice;
    Student *temp = head;
    while (temp != NULL)
    {
        if (temp->roll == key)
        {
            cout << "Record found with roll number " << key << endl;
            cout << endl
                 << left << setw(10) << "Roll No." << left << setw(20) << "Name" << endl;
            cout << left << setw(10) << temp->roll << left << setw(20) << temp->name << endl
                 << endl;
            cout << "Choose options to continue..." << endl;
            cout << "Press 1 to update roll number:" << endl;
            cout << "Press 2  to update name:" << endl;
            cout << "Press 3 to update both:" << endl;
            cin >> choice;

            switch (choice)
            {
            case 1:
                cout << "Enter new roll number:" << endl;
                cin >> temp->roll;
                break;
            case 2:
                cout << "Enter new name:" << endl;
                cin.ignore();
                cin.getline(name, 20);
                strcpy(temp->name, name);
                break;
            case 3:
                cout << "Enter new roll number:" << endl;
                cin >> temp->roll;
                cout << "Enter new name:" << endl;
                cin.ignore();
                cin.getline(name, 20);
                strcpy(temp->name, name);
                break;
            default:
                cout << "Invalid Choice!" << endl;
                break;
            }

            cout << endl
                 << "Record updated successfully" << endl;
            cout << endl
                 << left << setw(10) << "Roll No." << left << setw(20) << "Name" << endl;
            cout << left << setw(10) << temp->roll << left << setw(20) << temp->name << endl;
            flag = true;
            break;
        }
        temp = temp->next;
    }
    if (!flag)
    {
        cout << "Record not found with roll number " << key << endl;
    }
}

void deleteRecords(Student *&head, int key)
{
    bool flag;

    if (head->roll == key)
    {
        Student *toDelete = head;
        head = head->next;
        delete toDelete;
        flag = true;
    }
    else
    {
        Student *temp = head;
        Student *prev = NULL;
        while (temp != NULL && temp->roll != key)
        {
            prev = temp;
            temp = temp->next;
        }

        // If key was not present in linked list
        if (temp == NULL)
            return;

        // Unlink the node from linked list
        prev->next = temp->next;

        // Free memory
        delete temp;
        flag = true;
    }

    if (flag)
    {
        cout << "Record Deleted Successfully" << endl;
    }
    else
    {
        cout << "Record not found with roll number " << key << endl;
    }
}

Student *SortedMerge(Student *&a, Student *&b)
{
    Student *result = NULL;

    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    if (a->roll <= b->roll)
    {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else
    {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);
}

void FrontBackSplit(Student *source, Student *&frontRef, Student *&backRef)
{
    Student *fast;
    Student *slow;
    slow = source;
    fast = source->next;

    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    frontRef = source;
    backRef = slow->next;
    slow->next = NULL;
}

void MergeSort(Student *&head)
{
    Student *temp = head;

    if ((head == NULL) ||
        (head->next == NULL))
    {
        return;
    }

    Student *a, *b;

    FrontBackSplit(head, a, b);

    MergeSort(a);
    MergeSort(b);

    head = SortedMerge(a, b);
}

void removeDuplicates(Student *&head)
{
    if (isEmpty(head))
    {
        return;
    }

    Student *temp = head;
    while (temp->next != NULL)
    {
        if (temp->roll == temp->next->roll)
        {
            Student *todelete = temp->next;
            temp->next = temp->next->next;
            delete (todelete);
        }
        else
        {
            temp = temp->next;
        }
    }
}

void deleteLinkedList(Student *&head)
{
    Student *temp = head;
    while (temp != NULL)
    {
        temp = temp->next;
        delete head;
        head = temp;
    }
}

int menu()
{
    int choice;
    cout << "Choose options from below to continue" << endl;
    cout << "1. Add Record" << endl;
    cout << "2. View Records" << endl;
    cout << "3. Search Record" << endl;
    cout << "4. Update Record" << endl;
    cout << "5. Delete Record" << endl;
    cout << "6. Quit" << endl;
    cin >> choice;
    system("cls");
    return choice;
}

int main()
{
    Student *head;

    int key, roll;
    char y;
    char name[20];

    while (1)
    {
        head = NULL;
        cout << "STUDENT MANAGEMENT SYSTEM" << endl
             << endl;
        readFromDisk(head);

        switch (menu())
        {
        case 1:
            cout << "Enter details of student" << endl;
            do
            {
                cout << "Enter roll number: ";
                cin >> roll;
                cout << "Enter name: ";
                cin.ignore();
                cin.getline(name, 20);

                addNode(head, roll, name);
                cout << endl
                     << "Enter y to add more records... ";
                cin >> y;
            } while (y == 'y' || y == 'Y');
            system("cls");
            break;
        case 2:
            display(head);
            cout << endl
                 << "Press any key to continue..." << endl;
            getch();
            system("cls");
            break;
        case 3:
            if (isEmpty(head))
            {
                cout << "Your record file is empty" << endl;
            }
            else
            {
                do
                {
                    cout << "Enter roll number to search for a record: ";
                    cin >> key;
                    search(head, key);
                    cout << endl
                         << "Enter y to search for more records... ";
                    cin >> y;
                } while (y == 'y' || y == 'Y');
                system("cls");
            }
            break;
        case 4:
            if (isEmpty(head))
            {
                cout << "Your record file is empty" << endl;
            }
            else
            {
                do
                {
                    cout << "Enter roll number to update record: ";
                    cin >> key;
                    updateRecord(head, key);
                    cout << endl
                         << "Enter y to update more records... ";
                    cin >> y;
                } while (y == 'y' || y == 'Y');
                system("cls");
            }
            break;
        case 5:
            if (isEmpty(head))
            {
                cout << "Your record file is empty" << endl;
                cout << endl
                     << "Press any key to contiue..." << endl;
                getch();
                break;
            }
            cout << endl
                 << "Enter roll number to delete record" << endl;
            cin >> key;
            deleteRecords(head, key);
            system("cls");
            break;
        case 6:
            MergeSort(head);
            removeDuplicates(head);
            storeData(head);
            deleteLinkedList(head);
            exit(6);
            break;
        default:
            cout << "Invalid Choice!" << endl;
        }

        MergeSort(head);
        removeDuplicates(head);
        storeData(head);
        deleteLinkedList(head);
    }
    return 0;
}
