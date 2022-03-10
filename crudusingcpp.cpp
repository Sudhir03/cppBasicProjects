using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

class Students
{
    int roll;
    char name[20];

public:
    void getData()
    {
        cout << "Enter the details of student" << endl;
        cout << "Enter roll/id" << endl;
        cin >> roll;
        cout << "Enter name of student" << endl;
        cin.ignore();
        cin.getline(name, 20);
    }
    void showData()

    {
        cout << roll << "\t" << name << endl;
    }

    void storeData()
    {
        ofstream fout;
        fout.open("studentsRecords.dat", ios::app | ios::binary);
        fout.write((char *)this, sizeof(*this));
        fout.close();
    }

    void viewAllData()
    {
        ifstream fin;
        fin.open("studentsRecords.dat", ios::in);
        if (!fin.is_open())
        {
            cout << "File not found!" << endl;
        }

        fin.read((char *)this, sizeof(*this));

        while (!fin.eof())
        {
            showData();
            fin.read((char *)this, sizeof(*this));
        }
        fin.close();
    }

    int searchByRoll(int r)
    {
        int found = 0;
        ifstream fin;
        fin.open("studentsRecords.dat", ios::in);
        if (!fin.is_open())
        {
            cout << "File not found!" << endl;
        }

        while (!fin.eof())
        {
            fin.read((char *)this, sizeof(*this));
            if (roll == r)
            {
                cout << "Record found with roll number: " << r << endl;
                cout << "R.no"
                     << "\t"
                     << "Name" << endl;
                showData();
                found = 1;
                break;
            }

            fin.read((char *)this, sizeof(*this));
        }
        fin.close();
        return found;
    }

    void updateRecord()
    {
    }

    void deleteRecord()
    {
    }
};

int main()
{
    int choice;
    char again;
    Students s;

    cout << "Choose options to continue" << endl;
    cout << "1. Add New Record" << endl;
    cout << "2. View All Records" << endl;
    cout << "3. View Record With Roll Number" << endl;
    cout << "4. Update Record" << endl;
    cout << "5. Delete Record" << endl;
    cout << "6. Quit" << endl;

    cin >> choice;
    switch (choice)
    {
    case 1:
        s.getData();
        s.storeData();
        break;
    case 2:
        cout << "R.no"
             << "\t"
             << "Name" << endl;
        s.viewAllData();
        break;
    case 3:
        int search;
        cout << "Enter roll number to search record: " << endl;
        cin >> search;
        if (s.searchByRoll(search))
        {
        }
        else
        {
            cout << "Record not found with roll number: " << search << endl;
        }
        break;
    case 4:
        s.updateRecord();
        break;
    case 5:
        s.deleteRecord();
        break;
    case 6:
        exit(6);
        break;
    default:
        cout << "Invalid Choice!" << endl;
    }

    return 0;
}