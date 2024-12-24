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

// Function to write output to both file and console
void writeOutput(ofstream& outputFile, const string& content) {
    outputFile << "> " << content << endl;
    cout << "> " << content << endl;
}

int main() {
    string inputFilename="C:\\Users\\brian\\Desktop\\ilovecpp\\fileInput1.mdb";
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
                columnHeaders.push_back(line.substr(0, line.find(" ")));
                writeOutput(outputFile, line);
            }
        }

        // Handle INSERT statements
        if (line.find("INSERT INTO") != string::npos) {
            size_t valuesPos = line.find("VALUES (");
            if (valuesPos != string::npos) {
                string values = line.substr(valuesPos + 8); // Extract values after "VALUES ("
                values.pop_back(); // Remove trailing ')'
                tableData.push_back(values); // Store the entire row
            }
        }

        // Handle SELECT * FROM statements
        if (line.find("SELECT * FROM") != string::npos) {
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

    cout << "Processing completed. Output written to " << outputFilename << endl;
    return 0;
}
