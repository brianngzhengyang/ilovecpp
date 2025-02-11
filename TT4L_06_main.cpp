// *********************************************************
// Program: TT4L_06_main.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC2L
// Tutorial Class: TT4L
// Trimester: 2430
// Member_1: 242UC244L7 | ALIF AKMAL BIN ABDUL HALIM | ALIF.AKMAL.ABDUL@student.mmu.edu.my  | 018-3555944
// Member_2: 242UC244RD | BRIAN NG ZHENG YANG | BRIAN.NG.ZHENG@student.mmu.edu.my | 017-7793199
// Member_3: 242UC244PU | MEOR HAZIMI BIN MEOR MOHAMMAD FARED | MEOR.HAZIMI.MEOR@student.mmu.edu.my | 019-7521755
// Member_4: 1231300581 | MOHAMMED AMAN | 1231300581@student.mmu.edu.my | 011-39843157
// *********************************************************
// Task Distribution
// Member_1: create_database(), select_all_from_table_in_csv_mode()
// Member_2: insert_into_table(), trim(), delete_from_table()
// Member_3: create_table(), update_table()
// Member_4: create_output_screen_and_file(), count_from_table()
// *********************************************************


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// function prototypes
bool has_substring(const string& line, const string& substring);
void create_output_screen_and_file(ofstream& fileOutput, const string& content);
void create_database(ofstream& fileOutput);
void insert_into_table(const string& line, ofstream& fileOutput, vector<vector<string>>& table);
void create_table(ifstream& fileInput, ofstream& fileOutput, string& tableName, vector<vector<string>>& table);
void select_all_from_table_in_csv_mode(ofstream& fileOutput, vector<vector<string>>& table);
void update_table(const string& line, ofstream& fileOutput, vector<vector<string>>& table);
void delete_from_table(const string& line, ofstream& fileOutput, vector<vector<string>>& table);
void count_from_table(const string& line, ofstream& fileOutput, vector<vector<string>>& table);
string trim(const string& str);

int main()
{

    string fileOutputName;
    ofstream fileOutput(fileOutputName);

    vector<vector<string>> table;
    string tableName;

    ifstream fileInput;

    //string fileInputName = "fileInput1.mdb";
//    string fileInputName = "fileInput2.mdb";
    string fileInputName = "fileInput3.mdb";

    fileInput.open(fileInputName);

    if (!fileInput.is_open())
    {
        cout << "Unable to open input file" << endl;
        exit(-1);
    }

    string line;
    while (getline(fileInput, line))
    {
        line = trim(line);  // Trim spaces from each line


        if (has_substring(line, "CREATE TABLE"))
        {
            create_output_screen_and_file(fileOutput, "> " + line);

            // Extract the table name
            size_t pos = line.find("CREATE TABLE");
            if (pos != string::npos)
            {
                tableName = line.substr(pos + 12, line.find("(") - (pos + 12));  // Extract table name
                tableName = trim(tableName);  // Trim spaces from the table name
            }

            create_table(fileInput, fileOutput, tableName, table);
        }
        else if (has_substring(line, "CREATE"))
        {
            //fileOutputName = "fileOutput1.txt";
//            fileOutputName = "fileOutput2.txt";
            fileOutputName = "fileOutput3.txt";

            create_output_screen_and_file(fileOutput, "> CREATE " + fileOutputName + ";" );
        }
        else if (has_substring(line, "DATABASES;") )
        {
            create_database(fileOutput); // create the text file database
            create_output_screen_and_file(fileOutput,"> " + line);
            create_output_screen_and_file(fileOutput, fileInputName);
        }
        else if (has_substring(line, "INSERT INTO"))
        {
            insert_into_table(line, fileOutput, table);
        }
        else if (has_substring(line, "SELECT * FROM"))
        {
            create_output_screen_and_file(fileOutput, "> " + line);
            select_all_from_table_in_csv_mode(fileOutput, table);
        }
        else if (has_substring(line, "UPDATE"))
        {
            create_output_screen_and_file(fileOutput, "> " + line);
            update_table(line, fileOutput, table);
        }
        else if (has_substring(line, "DELETE FROM"))
        {
            create_output_screen_and_file(fileOutput, "> " + line);
            delete_from_table(line, fileOutput, table);
        }
        else if (has_substring(line, "SELECT COUNT(*) FROM"))
        {
            create_output_screen_and_file(fileOutput, "> " + line);
            count_from_table(line, fileOutput, table);
        }
        else if (has_substring(line, "TABLES"))
        {
            create_output_screen_and_file(fileOutput, "> TABLES;");
            create_output_screen_and_file(fileOutput, tableName);
        }
    }


    fileInput.close();
    fileOutput.close();
    cout << "Processing completed. Output written to " << fileOutputName << endl;
}

// function definitions

// Function to trim spaces from a string
string trim(const string& str)
{
    size_t first = str.find_first_not_of(" ");
    size_t last = str.find_last_not_of(" ");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
    // Check if both first and last non-space positions are valid; return the trimmed substring
}

// Function to write output to both file and console
void create_output_screen_and_file(ofstream& fileOutput, const string& content)
{
    fileOutput << content << endl;
    cout << content << endl;
}


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

void create_database(ofstream& fileOutput)
{
    //fileOutput.open("fileOutput1.txt");
    //fileOutput.open("fileOutput2.txt");
    fileOutput.open("fileOutput3.txt");

    if (!fileOutput.is_open())
    {
        cout << "Unable to open output file" << endl;
        exit(-1);
    }
}

void create_table(ifstream& fileInput, ofstream& fileOutput, string& tableName,vector<vector<string>>& table)
{
    string line;
    vector<string> columnHeaders;

    // Read the file line by line
    while (getline(fileInput, line))
    {
        line = trim(line);  // Trim spaces from the line

        if (line.find(")") != string::npos)    // End of table definition
        {
            create_output_screen_and_file(fileOutput,line);  // Write the closing part of the table definition
            break;
        }
        string columnName = line.substr(0, line.find(" "));  // Get the column name (before first space)
        columnHeaders.push_back(columnName);  // Store the column name
        create_output_screen_and_file(fileOutput, line);  // Write each column definition
    }
    table.push_back(columnHeaders);  // Store column headers as the first row in the table
}

void insert_into_table(const string& line, ofstream& fileOutput, vector<vector<string>>& table)
{
    if (line.find("INSERT INTO") != string::npos)
    {
        size_t pos = line.find("INSERT INTO ");

        // Remove the "INSERT INTO " part from the line
        string modifiedLine = line.substr(pos + string("INSERT INTO ").length());

        size_t valuesPos = line.find("VALUES (");
        if (valuesPos != string::npos)
        {
            string values = line.substr(valuesPos + 8); // Extract values after "VALUES ("
            // Remove trailing ')' and ';'
            while (!values.empty() && (values.back() == ')' || values.back() == ';'))
            {
                values.pop_back();
            }

            // Split the values by commas and store each value as a separate entry in the row
            vector<string> rowData;
            stringstream ss(values);
            string value;
            while (getline(ss, value, ','))
            {
                value = trim(value); // Trim spaces from each value
                // Remove single quotes around string values like emails
                if (!value.empty() && value.front() == '\'' && value.back() == '\'')
                {
                    value = value.substr(1, value.length() - 2); // Remove single quotes
                }
                rowData.push_back(value); // Add the cleaned value to the row
            }
            // Add the row data to the table
            table.push_back(rowData);
            create_output_screen_and_file(fileOutput, "> INSERT INTO ");
            create_output_screen_and_file(fileOutput, modifiedLine);
        }
    }
}

void select_all_from_table_in_csv_mode(ofstream& fileOutput, vector<vector<string>>& table)
{
    // Output the column headers
    string headerLine = "";
    for (size_t i = 0; i < table[0].size(); ++i)
    {
        if (i > 0)
        {
            headerLine += ",";
        }
        headerLine += table[0][i];
    }
    create_output_screen_and_file(fileOutput, headerLine);

    // Output each row stored in table
    for (size_t i = 1; i < table.size(); ++i)
    {
        string rowLine = "";
        for (size_t j = 0; j < table[i].size(); ++j)
        {
            if (!rowLine.empty()) rowLine += ",";
            rowLine += table[i][j];
        }
        create_output_screen_and_file(fileOutput, rowLine);
    }
}

void update_table(const string& line, ofstream& fileOutput, vector<vector<string>>& table) {
    size_t setPos = line.find("SET ");
    size_t wherePos = line.find("WHERE ");

    if (setPos != string::npos && wherePos != string::npos) {
        // Extract the SET clause (e.g., "customer_email='email333'")
        string setClause = trim(line.substr(setPos + 4, wherePos - (setPos + 4)));

        // Extract the WHERE clause (e.g., "customer_id=3")
        string whereClause = trim(line.substr(wherePos + 6));

        // Parse the SET clause: column = new value
        size_t equalsPosSet = setClause.find("=");
        if (equalsPosSet == string::npos) {
            return; // Invalid SET clause
        }

        string columnToUpdate = trim(setClause.substr(0, equalsPosSet));
        string newValue = trim(setClause.substr(equalsPosSet + 1));

        // Remove single quotes from the new value if present
        if (newValue.front() == '\'' && newValue.back() == '\'') {
            newValue = newValue.substr(1, newValue.length() - 2);
        }

        // Parse the WHERE clause: column = value
        size_t equalsPosWhere = whereClause.find("=");
        if (equalsPosWhere == string::npos) {
            return; // Invalid WHERE clause
        }

        string conditionColumn = trim(whereClause.substr(0, equalsPosWhere));
        string conditionValue = trim(whereClause.substr(equalsPosWhere + 1));

        // Remove single quotes and trailing semicolon from the condition value if present
        if (conditionValue.front() == '\'' && conditionValue.back() == '\'') {
            conditionValue = conditionValue.substr(1, conditionValue.length() - 2);
        }
        if (conditionValue.back() == ';') {
            conditionValue.pop_back(); // Remove trailing semicolon
        }

        // Find the indices of the columns
        int updateColumnIndex = -1;
        int conditionColumnIndex = -1;

        for (size_t i = 0; i < table[0].size(); ++i) {
            if (table[0][i] == columnToUpdate) {
                updateColumnIndex = i;
            }
            if (table[0][i] == conditionColumn) {
                conditionColumnIndex = i;
            }
        }

        // Update rows that match the condition
        if (updateColumnIndex != -1 && conditionColumnIndex != -1) {
            for (size_t i = 1; i < table.size(); ++i) {
                if (table[i][conditionColumnIndex] == conditionValue) {
                    table[i][updateColumnIndex] = newValue;
                }
            }
        }
    }
}

void delete_from_table(const string& line, ofstream& fileOutput, vector<vector<string>>& table) {
    size_t wherePos = line.find("WHERE ");

    if (wherePos != string::npos) {
        // Extract the WHERE clause (e.g., "customer_id=4")
        string whereClause = trim(line.substr(wherePos + 6));

        // Parse the WHERE clause: column = value
        size_t equalsPos = whereClause.find("=");
        if (equalsPos == string::npos) {
            return; // Invalid WHERE clause
        }

        string conditionColumn = trim(whereClause.substr(0, equalsPos));
        string conditionValue = trim(whereClause.substr(equalsPos + 1));

        // Remove single quotes and trailing semicolon from the condition value if present
        if (conditionValue.front() == '\'' && conditionValue.back() == '\'') {
            conditionValue = conditionValue.substr(1, conditionValue.length() - 2);
        }
        if (conditionValue.back() == ';') {
            conditionValue.pop_back(); // Remove trailing semicolon
        }

        // Find the index of the condition column
        int conditionColumnIndex = -1;
        for (size_t i = 0; i < table[0].size(); ++i) {
            if (table[0][i] == conditionColumn) {
                conditionColumnIndex = i;
                break;
            }
        }

        // Remove rows that match the condition
        if (conditionColumnIndex != -1) {
            for (size_t i = 1; i < table.size(); ) {
                if (table[i][conditionColumnIndex] == conditionValue) {
                    table.erase(table.begin() + i);
                } else {
                    ++i;
                }
            }
        }
    }
}

void count_from_table(const string& line, ofstream& fileOutput, vector<vector<string>>& table) {
    int rowCount = table.size() - 1; // Subtract 1 to exclude the header row
    create_output_screen_and_file(fileOutput, to_string(rowCount));
}
