/* ---------------------------
Labo        |   PRG1-Labo3
Author(s)   |   Agron Markaj
Start date  |   10.11.2023
Deadline    |   21.11.2023 (2359)
Goal        |   File with the function to show all the calculation
Remark(s)   |   ...
--------------------------- */
#include <filesystem>
#include <string>
#include <iostream>
#include "showResult.h"
#include "../files/fileReader.h"
#include "../formules/formules.h"

using namespace std;
namespace fs = std::filesystem;

const int &width1 = 8;  // for "Nr Mois"
const int &width2 = 12; // for "ROI moyen"
const int &width3 = 12; // for "Annualise"
const int &width4 = 11; // for "ROI min"
const int &width5 = 14; // for "Date min"
const int &width6 = 11; // for "ROI max"
const int &width7 = 15; // for "Date max"BRK

/*---------------------------
Name        | isInt
Parameter(s)| const std::string& str - the string to be checked
Return      | bool - true if the string represents a positive integer, false otherwise
Goal        | Determines if the given string can be successfully converted to a positive integer without any remaining characters left in the stream
--------------------------- */
bool isInt(const std::string& str){
    istringstream iss(str);
    int number;
    iss >> number;

    // Check if the reading was a success and if there aren't any char left int the buffer
    return iss.eof() && !iss.fail() && number > 0;
}

/*---------------------------
Name        | formatResult
Parameter(s)| vector<int> monthInsert - months for which to calculate ROI | string inputFileShare - name of the file containing share data | string inputDividendShare - name of the file containing dividend data
Return      | void
Goal        | Displays the ROI for each month specified in monthInsert, based on the data from inputFileShare and inputDividendShare files
--------------------------- */
void formatResult(vector<int> &monthInsert, string &inputFileShare, string &inputDividendShare) {

    // Show table header
    cout << left << setw(width1) << " Nr Mois";
    cout << left << setw(width2) << "| ROI moyen";
    cout << left << setw(width3) << "| Annualise";
    cout << left << setw(width4) << "| ROI min";
    cout << left << setw(width5) << "| Date min";
    cout << left << setw(width6) << "| ROI max";
    cout << left << setw(width7) << "| Date max" << endl;

    //Show values in the table
    for (int val: monthInsert) {

        //Declare var for Roi
        vector<Roi> result;
        result = allRoi(val, inputFileShare, inputDividendShare);

        if (!result.empty()){
            //Edit string for showing
            string monthWithSpace = ' ' + to_string(val);
            string dateMinWithSpace = ' ' + minRoi(result).second;
            string dateMaxWithSpace = ' ' + maxRoi(result).second;
            stringstream ss1;
            stringstream ss2;
            stringstream ss3;
            stringstream ss4;
            ss1 << fixed << setprecision(2) << ' ' << roiMean(result) << '%';
            ss2 << fixed << setprecision(2) << ' ' << roiAnnualise(roiMean(result), val) << '%';
            ss3 << fixed << setprecision(2) << ' ' << minRoi(result).first << "% ";
            ss4 << fixed << setprecision(2) << ' ' << maxRoi(result).first << "% ";

            // Showing ressult
            cout << left << setw(width1) << monthWithSpace << internal << "|";
            cout << left << setw(width2 - 1) << ss1.str() << internal << "|";
            cout << left << setw(width3 - 1) << ss2.str() << internal << "|";
            cout << left << setw(width4 - 1) << ss3.str() << internal << "|";
            cout << left << setw(width5 - 1) << dateMinWithSpace << internal << "|";
            cout << left << setw(width6 - 1) << ss4.str() << internal << "|";
            cout << left << setw(width7) <<  dateMaxWithSpace << endl;
        } else{
            cout << " " << val << " -> ce nombre de mois entree est trop grand par rapport aux dates du produit." << endl;
        }

    }
}

/*---------------------------
Name        | showString
Parameter(s)| None
Return      | void
Goal        | Interacts with the user to obtain the name of the investment product, the paths to the data files,
              and the months to be considered. Then calls formatResult with these inputs.
--------------------------- */
void showString() {

    //init Var
    string nameProduct;
    string csvNameProduct;
    string nameDividend;
    string pathData = "../data/";
    vector<int> monthInsert;
    string userInsert;
    string monthUserInsert;

    cout << "Dans quel produit voulez-vous investir ?";

    //Infinite loop until we have the right data
    while (true) {
        if (cin >> nameProduct) {

            //If the entry does not contain a CSV, it must be inserted
            if (nameProduct.find(".csv") == string::npos) {
                nameDividend = pathData + nameProduct + "-2.csv";
                csvNameProduct = pathData + nameProduct + ".csv";
            }

            //If it contains CSV, you must do the processing to insert the -2 for the dividen name
            else {
                size_t dotPosition = nameProduct.find_last_of('.');
                string baseName = nameProduct.substr(0, dotPosition);
                string extension = nameProduct.substr(dotPosition);
                nameDividend = pathData + baseName + "-2" + extension;
                csvNameProduct = pathData + nameProduct;
            }

            //Read data
            pair<vector<Share>, string> shares = readShare(csvNameProduct);

            //If the product exists we leave the loop
            if (shares.second.empty()) {
                pair<vector<Dividend>, string> dividends = readDividend(nameDividend);
                cout << dividends.second << endl;
                break;
            }
            // Clear the failure state and empty the buffer
            else {
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                cout << shares.second << endl;
                cout << "Veuillez inserrer un produit existent :";
            }
        }
    }

    cout << "Durees a considerer en mois ?";

    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, userInsert);
    istringstream iss(userInsert);

    // Read month data from 'iss'. If it is a valid integer, it's added to vector of month. Otherwise, an error message is displayed.
    while (iss >> monthUserInsert) {
        if (isInt(monthUserInsert)) {
            monthInsert.push_back(std::stoi(monthUserInsert));
        } else {
            cout << "Erreur : '" << monthUserInsert << "' n'est pas un nombre entier positif valide." << endl;
        }
    }

    //Show table
    formatResult(monthInsert, csvNameProduct, nameDividend);
}
