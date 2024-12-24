#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// function prototypes
bool has substring(const string& line, const string& substring);
void create output screen and file();
void create_database();
void create table();
void insert_into_table();
void select all_from table_in csv mode();

int main() {
    ofstream fileOutput;
    string fileOutputName;

    vector<vector<string>> table;
    string tableName;

    ifstrean fileInput;

    string fileInputName "C:\\yourname\\fiininputi.mdb":
    //string filelnputName "C:\\yourname\\fileInput2.mdb";
    //string fileInputhame "C:\\yourname\\fileInput3.mdb";

        fileInput.open(fileInputName);

        if (!fileInput.is_open())
        {
            cout << "Unable to open input file" << endl;
            exit(-1);
        }

        string line;
        while (getline (fileInput, line))
        {
                //cout << line << endl;
            if (has_substring(line, "CREATE TABLE") )
            {
                cout << "? CREATE TABLE" << endl;
            }
            else if (has_substring(line, "CREATE"))
            {
                fileOutputName = "?";
                cout << "> CREATE << fileOutputName << ";" << endl;
            }
            else if (has_substring(line, "DATABASES;") )
            {
                cout << "> " <<< line << endl;
                cout << "?" << endl;
            }
            else if (has_substring(line, "?1"))
            {
                cout << "?1" << endl;
            }
            else if (has_substring(line, "?2"))
            {
                cout << "?2" << endl;
            }
            else if (has_substring(line, "?3"))
            {
                cout << "?3" << endl;
            }
            else if (has_substring(line, "?4"))
            {
                cout << "?4" << endl;
            }
            else if (has_substring(line, "?5"))
            {
                cout << "?5" << endl;
            }
            else if (has_substring(line, "?6"))
            {
                cout << "?6" << endl;
            }
            //    else
            //    {
            //        cout << "Error message: Invalid input command" << endl;
            //    }
        }
}
// function definitions
bool has_substring(const string& line, const string& substring)
{
    if (line.find(substring) != string:: npos)
    {
      return true; // substring found
    }
    else
    {
        return false; // substring not found
    }
}

void create output screen and file()
{

}

void create_database()
{

}

void create table()
{

}

void insert_into_table()
{

}

void select all_from table_in csv mode()
{

}
