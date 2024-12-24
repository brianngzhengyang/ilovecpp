#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
using namespace std;

// Function to trim spaces from a string
string trim(const string& str) {
    size_t first = str.find_first_not_of(" ");
    size_t last = str.find_last_not_of(" ");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

// Function to split a string by a delimiter
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(trim(token));
    }
    return tokens;
}

// Function to write output to both file and console
void writeOutput(ofstream& outputFile, const string& content) {
    outputFile << "> " << content << endl;
    cout << "> " << content << endl;
}

int main() {
    string inputFilename = "fileInput1.mdb";
    string outputFilename = "fileOutput1.txt";

    ifstream inputFile(inputFilename);
    ofstream outputFile(outputFilename);

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open input file: " << inputFilename << endl;
        return 1;
    }

    if (!outputFile.is_open()) {
        cerr << "Error: Could not create output file: " << outputFilename << endl;
        return 1;
    }

    string line;
    vector<string> tableData;
    vector<string> columnHeaders;

    writeOutput(outputFile, "CREATE " + outputFilename + ";");

    while (getline(inputFile, line)) {
        line = trim(line);

        if (line.empty()) continue;

        writeOutput(outputFile, line);

<<<<<<< HEAD
=======
        // alif test part //

        // Handle CREATE FILE
        if (line.find("CREATE fileOutput1.txt") != string::npos) {
            continue; // No action needed; the output file is already created
        }

        // Handle DATABASES
        if (line.find("DATABASES") != string::npos) {
            writeOutput(outputFile, "C:\\mariadb\\" + inputFilename);
            continue;
        } // alif test part //

        

        // Handle table creation
>>>>>>> main
        if (line.find("CREATE TABLE") != string::npos) {
            getline(inputFile, line); // Skip "(" line
            line = trim(line);
            writeOutput(outputFile, line);

            while (getline(inputFile, line)) {
                line = trim(line);
                if (line.find(")") != string::npos) {
                    writeOutput(outputFile, line);
                    break;
                }
                size_t spacePos = line.find(" ");
                if (spacePos != string::npos) {
                    columnHeaders.push_back(line.substr(0, spacePos)); // Extract column name
                }
                writeOutput(outputFile, line);
            }
        }

        // Handle INSERT statements
        if (line.find("INSERT INTO") != string::npos) {
            size_t valuesPos = line.find("VALUES (");
            if (valuesPos == string::npos) {
                cerr << "ERROR: 'VALUES (' not found in line: " << line << endl;
            } else {
                string values = line.substr(valuesPos + 8); // Extract values after "VALUES ("

                values.pop_back(); // Remove trailing ')'

                vector<string> parsedValues = split(values, ',');


                // Remove single quotes from parsed values
                for (auto& value : parsedValues) {
                    if (value.front() == '\'') value = value.substr(1, value.size() - 2);
                }

                string joinedValues = "";
                for (size_t i = 0; i < parsedValues.size(); ++i) {
                    if (i > 0) joinedValues += ",";
                    joinedValues += parsedValues[i];
                }

                tableData.push_back(joinedValues);
            }
        }


        // Handle SELECT * FROM statements
        if (line.find("SELECT * FROM") != string::npos) {
            // Ensure columnHeaders contains all column names
            if (columnHeaders.empty()) {
                cerr << "Error: No column headers found before SELECT statement." << endl;
                continue;
            }

            for (const auto& header : columnHeaders) {
                cout << header << " ";
            }
            cout << endl;


            // Output the column headers
            string headerLine = "";
            for (const auto& header : columnHeaders) {
                if (!headerLine.empty()) headerLine += ",";
                headerLine += header;
            }
            writeOutput(outputFile, headerLine);

            // Output each row stored in tableData
            for (const auto& row : tableData) {
                writeOutput(outputFile, row);
            }
        }
    }

    inputFile.close();
    outputFile.close();
    return 0;
}
