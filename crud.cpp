using namespace std;

#include <iostream>
#include <string>
#include <fstream>

class Student
{
public:
    int roll;
    string name;
    Student *next;

    Student()
    {
    }

    Student(int r, string n)
    {
        roll = r;
        name = n;
        next = NULL;
    }
};

void insertAtTail(Student *&head, int r, string n)
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

void display(Student *head)
{
    Student *temp = head;
    if (head == NULL)
    {
        cout << "No records to show" << endl;
        return;
    }

    while (temp != NULL)
    {
        cout << temp->roll << "\t" << temp->name << endl;
        temp = temp->next;
    }
}

// void readData(Student *&head)
// {
//     cout << "in read data" << endl;
//     Student *temp = head;
//     Student *ptr;
//     Student obj;

//     ifstream file;
//     file.open("records.dat", ios::in | ios ::binary);

//     if (file.fail())
//     {
//         cout << "Error while opening file" << endl;
//     }
//     else
//     {
//         file.read((char *)&ptr, sizeof(ptr));
//         display(temp);
//         while (!file.eof())
//         {
//             display(temp);
//             cout << "before creating a node" << endl;
//             cout << temp->roll;
//             insertAtTail(temp, ptr->roll);
//             cout << "after creating a node" << endl;
//             display(temp);
//             file.read((char *)&ptr, sizeof(ptr));
//         }
//     }
//     file.close();
// }

void search(Student *head, int key)
{
    bool flag;
    Student *temp = head;
    while (temp != NULL)
    {
        if (temp->roll == key)
        {
            cout << "Record found with roll number " << key << endl;
            cout << temp->roll << "\t" << temp->name << endl;
            flag = true;
            break;
        }
        temp = temp->next;
    }
    if (!flag)
    {
        cout << "Record not found wit roll number " << key << endl;
    }
}

void updateRecord(Student *&head, int key)
{
    bool flag;
    string name;
    int choice;
    Student *temp = head;
    while (temp != NULL)
    {
        if (temp->roll == key)
        {
            cout << "Record found with roll number " << key << endl;
            cout << temp->roll << "\t" << temp->name << endl;
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
                getline(cin, name);
                temp->name = name;
                break;
            case 3:
                cout << "Enter new roll number:" << endl;
                cin >> temp->roll;
                cout << "Enter new name:" << endl;
                cin.ignore();
                getline(cin, name);
                temp->name = name;
                break;
            default:
                cout << "Invalid Choice!" << endl;
                break;
            }

            cout << "Record updated successfully" << endl;
            cout << "Updated record: " << temp->roll << "\t" << temp->name << endl;
            flag = true;
            break;
        }
        temp = temp->next;
    }
    if (!flag)
    {
        cout << "Record not found wit roll number " << key << endl;
    }
}

void deleteRecord(Student *&head, int key)
{
    bool flag;
    Student *temp = head;
    while (temp != NULL)
    {
        if (temp->next->roll == key)
        {
            temp = temp->next->next;
            cout << "Record deleted successfully" << endl;
            flag = true;

            break;
        }
        temp = temp->next;
    }
    head = temp;
    if (!flag)
    {
        cout << "Record not found wit roll number " << key << endl;
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
    return choice;
}

int main()

{
    Student *head;

    int key, roll;
    char y;
    string name;

    while (1)
    {
        switch (menu())
        {
        case 1:
            cout << "Enter details of student" << endl;
            do
            {
                cout << "Enter roll number: ";
                cin >> roll;
                cout << "Enter name: " << endl;
                cin.ignore();

                getline(cin, name);

                insertAtTail(head, roll, name);
                cout << "Enter y to add more records... ";
                cin >> y;
            } while (y == 'y' || y == 'Y');
            break;
        case 2:
            display(head);
            break;
        case 3:
            do
            {
                cout << "Enter roll number to search for a record: ";
                cin >> key;
                search(head, key);
                cout << "Enter y to search for more records... ";
                cin >> y;
            } while (y == 'y' || y == 'Y');
            break;
        case 4:
            do
            {
                cout << "Enter roll number to update record" << endl;
                cin >> key;
                updateRecord(head, key);
                cout << "Enter y to update more records... ";
                cin >> y;
            } while (y == 'y' || y == 'Y');
            break;
        case 5:
            do
            {
                cout << "Enter roll number to delete record" << endl;
                cin >> key;
                deleteRecord(head, key);
                cout << "Enter y to delete more records... ";
                cin >> y;
            } while (y == 'y' || y == 'Y');
            break;
        case 6:
            exit(6);
            break;
        default:
            cout << "Invalid Choice!" << endl;
        }
    }
    return 0;
}
