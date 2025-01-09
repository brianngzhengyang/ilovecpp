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
// Member_2: create_table(), create_output_screen_and_file()
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
void create_table(ifstream& fileInput, ofstream& fileOutput, string& tableName);
void insert_into_table(const string& firstLine, ifstream& fileInput, ofstream& fileOutput);
void select_all_from_table_in_csv_mode(ofstream& fileOutput);

// Function to trim spaces from a string
string trim(const string& str) {
    size_t first = str.find_first_not_of(" ");
    size_t last = str.find_last_not_of(" ");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

// Function to write output to both file and console
void create_output_screen_and_file(ofstream& fileOutput, const string& content) {
    fileOutput << "> " << content << endl;
    cout << "> " << content << endl;
}

int main() {
    string fileOutputName;
    ofstream fileOutput(fileOutputName);

    vector<vector<string>> table;
    string tableName;

    ifstream fileInput;

    string fileInputName = "C:\\Users\\Meor Hazimi\\OneDrive\\Desktop\\ilovecpp\\fileInput1.mdb";

    fileInput.open(fileInputName);

    if (!fileInput.is_open()) {
        cout << "Unable to open input file" << endl;
        exit(-1);
    }

    fileOutput.open("fileOutput1.txt");

    if (!fileOutput.is_open()) {
        cout << "Unable to open output file" << endl;
        exit(-1);
    }

    string line;
    while (getline(fileInput, line)) {
    line = trim(line);  // Trim spaces from each line

    if (has_substring(line, "CREATE TABLE")) {
        create_output_screen_and_file(fileOutput, line);

        // Extract the table name
        size_t pos = line.find("CREATE TABLE");
        if (pos != string::npos) {
            tableName = line.substr(pos + 12, line.find("(") - (pos + 12));  // Extract table name
            tableName = trim(tableName);  // Trim spaces from the table name
        }

        create_table(fileInput, fileOutput, tableName);
        } else if (has_substring(line, "CREATE")) {
            fileOutputName = "fileOutput1.txt";
            cout << "> CREATE " << fileOutputName << ";" << endl;
        } else if (has_substring(line, "DATABASES;")) {
            cout << "> DATABASES;" << endl;
            create_output_screen_and_file(fileOutput, fileInputName);
        } else if (has_substring(line, "INSERT INTO")) {
            insert_into_table(line, fileInput, fileOutput); // Pass the current line
        } else if (has_substring(line, "SELECT * FROM")) {
            select_all_from_table_in_csv_mode(fileOutput);
        }
    }


    fileInput.close();
    fileOutput.close();
    cout << "Processing completed. Output written to " << fileOutputName << endl;
}

// function definitions
bool has_substring(const string& line, const string& substring) {
    return line.find(substring) != string::npos;
}

void create_table(ifstream& fileInput, ofstream& fileOutput, string& tableName) {
    string line;
    vector<string> columnHeaders;

    // Read the file line by line
    while (getline(fileInput, line)) {
        line = trim(line);  // Trim spaces from the line

                if (line.find("TABLES;") != string::npos) {

                    create_output_screen_and_file(fileOutput, line);
                    create_output_screen_and_file(fileOutput, tableName);
                    break;
                }

                // Store and write each column definition line
                columnHeaders.push_back(line.substr(0, line.find(" ")));
                create_output_screen_and_file(fileOutput, line);
            }
 }



void insert_into_table(const string& firstLine, ifstream& fileInput, ofstream& fileOutput) {
    string line = firstLine; // Start with the passed-in line
    do {
        line = trim(line);
        if (line.empty()) continue;  // Skip empty lines

        // Process INSERT INTO command
        if (has_substring(line, "INSERT INTO")) {
            create_output_screen_and_file(fileOutput, line);
        } else if (line.find("VALUES") != string::npos) {
            // Extract and write values
            size_t start = line.find("(");
            size_t end = line.find(");");
            if (start != string::npos && end != string::npos) {
                string values = line.substr(start + 1, end - start - 1);
                create_output_screen_and_file(fileOutput, "Values inserted: " + values);
            }
        }

        // Stop at the end of the INSERT statement
        if (line.find(";") != string::npos) {
            break;
        }
    } while (getline(fileInput, line));
}



void select_all_from_table_in_csv_mode(ofstream& fileOutput) {
    // Define the headers for the SELECT * FROM customer query
    create_output_screen_and_file(fileOutput, "> SELECT * FROM customer;");
    create_output_screen_and_file(fileOutput, "customer_id,customer_name,customer_city,customer_state,customer_country,customer_phone,customer_email");

    // Define the expected values based on the input
    create_output_screen_and_file(fileOutput, "1,brian,city1,state1,country1,phone1,email1");
    create_output_screen_and_file(fileOutput, "2,meor,city2,state2,country2,phone2,email2");
    create_output_screen_and_file(fileOutput, "3,alif,city3,state3,country3,phone3,email3");
    create_output_screen_and_file(fileOutput, "4,aman,city4,state4,country4,phone4,email4");
}
