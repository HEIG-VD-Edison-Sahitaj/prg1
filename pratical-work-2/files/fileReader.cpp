/* ---------------------------
Labo        |   PRG1-Labo3
Author(s)   |   Edison Sahitaj
Start date  |   10.11.2023
Deadline    |   21.11.2023 (2359)
Goal        |   File with all the functions for reading files
Remark(s)   |   ...
--------------------------- */
#include <fstream>
#include <vector>
#include <sstream>
#include "fileReader.h"
#include "../formules/formules.h"

using namespace std;

/*---------------------------
Name        | readShare
Parameter(s)| const string &filename - the name of the file to read
Return      | pair<vector<Share>, string> - a vector of share and a string with an error message
Goal        | read a csv file and return a vector of share and error message
--------------------------- */
pair<vector<Share>, string> readShare(const string &fileName) {
    vector<Share> result;
    string line;
    string error;
    char separator = ',';
    ifstream file(fileName);
    if (file.is_open()) {
        getline(file, line);
        while (getline(file, line)) {
            istringstream iss(line);
            string cell;
            while (std::getline(iss, cell, separator)) {
                Share share;
                share.date.year = stoi(cell.substr(0, 4));
                share.date.month = stoi(cell.substr(5, 2));
                share.date.day = stoi(cell.substr(8, 2));
                share.date.format +=
                        to_string(share.date.year) + "/" + formatTwoDigits(share.date.month) + "/" +
                        formatTwoDigits(share.date.day);
                getline(iss, cell, separator);
                getline(iss, cell, separator);
                getline(iss, cell, separator);
                getline(iss, cell, separator);
                share.close = stod(cell);
                result.push_back(share);
                getline(iss, cell, separator);
                getline(iss, cell, separator);
            }
        }
        file.close();
    } else {
        error = "Pas de cours (" + fileName + " illisible)";
    }
    return make_pair(result, error);
}

/*---------------------------
 * Name        | readDividend
 * Parameter(s)| const string &filename - the name of the file to read
 * Return      | pair<vector<Dividend>, string> - a vector of dividend and a string with an error message
 * Goal        | read a csv file and return a vector of dividend and error message
 *--------------------------- */
pair<vector<Dividend>, string> readDividend(const string &fileName) {
    vector<Dividend> result;
    string error;
    string line;
    ifstream file(fileName);
    char separator = ',';
    if (file.is_open()) {
        getline(file, line);
        while (getline(file, line)) {
            istringstream iss(line);
            string cell;
            while (getline(iss, cell, separator)) {
                Dividend dividend;
                dividend.date.year = stoi(cell.substr(0, 4));
                dividend.date.month = stoi(cell.substr(5, 2));
                dividend.date.day = stoi(cell.substr(8, 2));
                dividend.date.format +=
                        to_string(dividend.date.year) + "/" + formatTwoDigits(dividend.date.month) + "/" +
                        formatTwoDigits(dividend.date.day);
                getline(iss, cell);
                dividend.dividend = stod(cell);
                result.push_back(dividend);
            }
        }
        file.close();
    } else {
        error = "Pas de dividendes (" + fileName + " illisible)";
    }
    return make_pair(result, error);
}
