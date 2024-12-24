 // *********************************************************
// Program: TT4L_06_main.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC2L
// Tutorial Class: TT4L
// Trimester: 2430
// Member_1: 242UC244PU | MEOR HAZIMI BIN MEOR MOHAMMAD FARED | meor.hazimi.meor@student.mmu.edu.my | 019-7521755
// Member_2: 242UC244RD | BRIAN NG ZHENG YANG | BRIAN.NG.ZHENG@student.mmu.edu.my | 017-7793199
// Member_3: 242UC244L7 | ALIF AKMAL BIN ABDUL HALIM | ALIF.AKMAL.ABDUL@student.mmu.edu.my  | 018-3555944
// Member_4: 1231300581 | MOHAMMED AMAN | 1231300581@student.mmu.edu.my | 011-39843157
// *********************************************************
// Task Distribution
// Member_1:
// Member_2: create_table(), insert_into_table()
// Member_3:
// Member_4:
// *********************************************************

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// function prototypes
bool has_substring(const string& line, const string& substring);
void create_output_screen_and_file();
void create_database();
void create_table();
void insert_into_table();
void select_all_from_table_in_csv_mode();

int main() {
    ofstream fileOutput;
    string fileOutputName;

    vector<vector<string>> table;
    string tableName;

    ifstream fileInput;

    string fileInputName = "C:\\Users\\brian\\Desktop\\ilovecpp\\fileInput1.mdb";
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
                cout << "> CREATE "<< fileOutputName << ";" << endl;
            }
            else if (has_substring(line, "DATABASES;") )
            {
                cout << "> " << line << endl;
                cout << fileInputName << endl;
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

void create_output_screen_and_file()
{

}

void create_database()
{

}

void create_table()
{

}

void insert_into_table()
{

}

void select_all_from_table_in_csv_mode()
{

}
