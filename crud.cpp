using namespace std;
#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
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

Student *SortedMerge(Student *&, Student *&);
void FrontBackSplit(Student *, Student *&, Student *&);

void insertAtTail(Student *&head, int r, char *n)
{

    Student *p = new Student(r, n);

    if (head == NULL)
    {
        head = p;
        return;
    }

    Student *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = p;
}

bool readFromDisk(Student *&head)
{
    ifstream file;
    file.open(filename, ios::in | ios::binary);
    if (file.fail())
    {
        ofstream file;
        file.open(filename, ios::out);
        file.close();
        return false;
    }

    Student temp;
    file.read((char *)&temp, sizeof(temp));
    while (!file.eof())
    {
        cout << "Roll " << temp.roll << " & "
             << "Name is " << temp.name << endl;
        file.read((char *)&temp, sizeof(temp));
    }
    file.close();
    return true;
}

void display(Student *head)
{

    if (head == NULL)
    {
        cout << "No records to show" << endl;
        return;
    }
    cout << endl
         << left << setw(10) << "Roll No." << left << setw(24) << "Name" << endl;
    Student *temp = head;
    while (temp != NULL)
    {

        cout << left << setw(10) << temp->roll << left << setw(24) << temp->name << endl;
        temp = temp->next;
    }
}

void search(Student *head, int key)
{
    bool flag;
    Student *temp = head;
    while (temp != NULL)
    {
        if (temp->roll == key)
        {
            cout << endl
                 << "Record found with roll number " << key << endl;
            cout << temp->roll << "\t" << temp->name << endl;
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
            cout << endl
                 << "Record found with roll number " << key << endl;
            cout << endl
                 << left << setw(10) << "Roll No." << left << setw(24) << "Name" << endl;
            cout << left << setw(10) << temp->roll << left << setw(24) << temp->name << endl
                 << endl;
            cout << "Press 1 to update roll number:" << endl;
            cout << "Press 2  to update name:" << endl;
            cout << "Press 3 to update both:" << endl;
            cin >> choice;

            switch (choice)
            {
            case 1:
                cout
                    << "Enter new roll number:" << endl;

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
                 << left << setw(10) << "Roll No." << left << setw(24) << "Name" << endl;
            cout << left << setw(10) << temp->roll << left << setw(24) << temp->name << endl;
            flag = true;
            break;
        }
        temp = temp->next;
    }
    if (!flag)
    {
        cout << endl
             << "Record not found with roll number " << key << endl;
    }
}

bool isEmpty(Student *head)
{
    return (head == NULL) ? true : false;
}

void deleteRecords(Student *&head, int key)
{
    bool flag;
    if (isEmpty(head))
    {
        return;
    }

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
        while (temp != NULL)
        {
            if (temp->next->roll == key)
            {
                Student *todelete = temp->next;
                temp->next = temp->next->next;
                delete todelete;
                flag = true;
                break;
            }

            temp = temp->next;
        }
        head = temp;
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

void MergeSort(Student *&head)
{
    Student *temp = head;

    if ((temp == NULL) ||
        (temp->next == NULL))
    {
        return;
    }

    Student *a, *b;

    FrontBackSplit(temp, a, b);

    MergeSort(a);
    MergeSort(b);

    head = SortedMerge(a, b);
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
void removeDuplicates(Student *head)
{
    if (isEmpty(head))
    {
        return;
    }

    Student *temp, *temp2;
    temp = head;

    while (temp != NULL && temp->next != NULL)
    {
        temp2 = temp;

        while (temp2->next != NULL)
        {
            /* If duplicate then delete it */
            if (temp->roll == temp2->next->roll)
            {
                Student *todelete;
                todelete = temp2->next;
                temp2->next = temp2->next->next;
                delete (todelete);

                if (temp2->next == NULL)
                {
                    return;
                }
            }
        }
        temp = temp->next;
    }
}

void storeToDrive(Student *&head)
{
    ofstream file;
    (isDataReaded) ? (file.open(filename, ios::out | ios::binary)) : file.open(filename, ios::ate | ios::binary);

    if (file.fail())
    {
        cout << "File not found!" << endl;
        return;
    }
    if (isEmpty(head))
    {
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
        cout << "STUDENT MANAGEMENT SYSTEM" << endl
             << endl;
        isDataReaded = readFromDisk(head);
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

                insertAtTail(head, roll, name);
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
            do
            {
                cout << endl
                     << "Enter roll number to search for a record: ";
                cin >> key;
                search(head, key);
                cout << endl
                     << "Enter y to search for more records... ";
                cin >> y;
            } while (y == 'y' || y == 'Y');
            system("cls");
            break;
        case 4:
            do
            {
                cout << endl
                     << "Enter roll number to update record: ";
                cin >> key;
                updateRecord(head, key);
                cout << endl
                     << "Enter y to update more records... ";
                cin >> y;
            } while (y == 'y' || y == 'Y');
            system("cls");
            break;
        case 5:
            if (isEmpty(head))
            {
                cout << endl
                     << "No Record To Delete" << endl;
                cout << endl
                     << "Press any key to contiue..." << endl;
                getch();
            }
            else
            {
                do
                {
                    cout << endl
                         << "Enter roll number to delete record" << endl;
                    cin >> key;
                    deleteRecords(head, key);
                    if (isEmpty(head))
                    {
                        y = 'n';
                    }
                    else
                    {
                        cout << endl
                             << "Enter y to delete more records... ";
                        cin >> y;
                    }

                } while (y == 'y' || y == 'Y');
            }
            system("cls");
            break;
        case 6:
            MergeSort(head);
            // removeDuplicates(head);
            storeToDrive(head);
            exit(6);
            break;
        default:
            cout << "Invalid Choice!" << endl;
        }

        MergeSort(head);
        // removeDuplicates(head);
        storeToDrive(head);
    }
    return 0;
}
