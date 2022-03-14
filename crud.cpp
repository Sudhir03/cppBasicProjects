using namespace std;
#include <iostream>
#include <fstream>

class Student
{
public:
    int roll;
    Student *next;

    Student()
    {
    }

    Student(int r)
    {
        roll = r;
        next = NULL;
    }
};

void display(Student *head)
{
    Student *temp = head;
    while (temp != NULL)
    {
        // cout << temp->roll << " " << temp->name << endl;
        cout << temp->roll << endl;
        temp = temp->next;
    }
}

void insertAtTail(Student *&head, int r)
{

    Student *n = new Student(r);
    if (head == NULL)
    {
        head = n;
    }
    else
    {
        Student *temp = head;
        while (temp->next == NULL)
        {
            cout << "in inserattail" << endl;

            temp = temp->next;
        }
        temp->next = n;
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
    Student *temp = head;
    while (temp != NULL)
    {
        if (temp->roll == key)
        {
            cout << "Record found with roll number " << key << endl;
            cout << temp->roll << endl;
            break;
        }
        temp = temp->next;
    }
    cout << "Record not found wit roll number " << key << endl;
}

void updateRecord(Student *&head, int key)
{
    Student *temp = head;
    while (temp != NULL)
    {
        if (temp->roll == key)
        {
            cout << "Enter new data to update records" << endl;
            cin >> temp->roll;
            cout << "Record updated successfully" << endl;
            break;
        }
        temp = temp->next;
    }
    cout << "Record not found wit roll number " << key << endl;
}

void deleteRecord(Student *&head, int key)
{
    Student *temp = head;
    while (temp != NULL)
    {
        if (temp->next->roll == key)
        {
            temp = temp->next->next;
            cout << "Record deleted successfully" << endl;
            break;
        }
        temp = temp->next;
    }
    cout << "Record not found wit roll number " << key << endl;
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
    insertAtTail(head, 1);
    insertAtTail(head, 2);
    insertAtTail(head, 3);
    insertAtTail(head, 4);
    insertAtTail(head, 5);
    display(head);
    return 0;
}

// int main()
// {
//     int key, roll;
//     char y;

//     Student *head;
//     while (1)
//     {
//         // system("cls");

//         switch (menu())
//         {
//         case 1:
//             cout << "Enter details of student" << endl;
//             do
//             {
//                 cout << "Enter roll number of student: ";
//                 cin >> roll;
//                 insertAtTail(head, roll);
//                 cout << "Enter y to add more records... ";
//                 cin >> y;
//             } while (y == 'y' || y == 'Y');
//             break;
//         case 2:
//             display(head);
//             break;
//         case 3:
//             do
//             {
//                 cout << "Enter roll number to search for a record: ";
//                 cin >> key;
//                 search(head, key);
//                 cout << "Enter y to search for more records... ";
//                 cin >> y;
//             } while (y == 'y' || y == 'Y');
//             break;
//         case 4:
//             do
//             {
//                 cout << "Enter roll number to update record" << endl;
//                 cin >> key;
//                 updateRecord(head, key);
//                 cout << "Enter y to update more records... ";
//                 cin >> y;
//             } while (y == 'y' || y == 'Y');
//             break;
//         case 5:
//             do
//             {
//                 cout << "Enter roll number to delete record" << endl;
//                 cin >> key;
//                 deleteRecord(head, key);
//                 cout << "Enter y to delete more records... ";
//                 cin >> y;
//             } while (y == 'y' || y == 'Y');
//             break;
//         case 6:
//             exit(6);
//             break;
//         default:
//             cout << "Invalid Choice!" << endl;
//         }
//     }
//     return 0;
// }