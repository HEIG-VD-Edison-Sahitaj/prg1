/* ---------------------------
Labo        |   PRG1-Labo3
Author(s)   |   David Schildböck
Start date  |   10.11.2023
Deadline    |   21.11.2023 (2359)
Goal        |   File with all the functions for the calculations of the roi/mean/annualise/min/max
Remark(s)   |   ...
Source(s)   |   https://en.cppreference.com/w/cpp/concepts/predicate
--------------------------- */
#include "formules.h"
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <cmath>

using namespace std;

/*---------------------------
Name        | checkYear
Parameter(s)| const int& year - the year (4 digits)
Return      | bool
Goal        | To know if the year is leap or not.
--------------------------- */
bool checkYear(const int& year){
    return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

/*---------------------------
Name        | formatTwoDigits
Parameter(s)| const int& number - a number (2 digits)
Return      | string
Goal        | To convert a number into a string keeping the 2 digits. (1 -> 01)
--------------------------- */
string formatTwoDigits(const int& number){
    ostringstream oss;
    oss << setw(2) << setfill('0') << number;
    return oss.str();
}

/*---------------------------
Name        | isDateInVector
Parameter(s)| const string& date - the date to find | const vector<share>& share - the vector to check | long long int& index - the index if found
Return      | bool
Goal        | To look through the vector share to find the date
--------------------------- */
bool isDateInVector(const string& date, const vector<Share>& share, long long int& index){
    auto it = find_if(share.begin(), share.end(), [&date](const struct Share &arg) {
            return arg.date.format == date; });

    bool condition = it != share.end();
    if (condition){
        index = it - share.begin();
    }

    return condition;
}

/*---------------------------
Name        | isDateInVector
Parameter(s)| const string& date - the date to find | const vector<dividend>& dividend - the vector to check | long long int& index - the index if found
Return      | bool
Goal        | To look through the vector dividend to find the date
--------------------------- */
bool isDateInVector(const string& date, const vector<Dividend>& dividend, long long int& index){
    auto it = find_if(dividend.begin(), dividend.end(), [&date](const struct Dividend &arg) {
        return arg.date.format == date; });

    bool condition = it != dividend.end();
    index = (condition) ? it - dividend.begin() : -1;

    return condition;
}

/*---------------------------
Name        | newDate
Parameter(s)| int& day - the day | int& month - the month | int& year - the year
Return      | string
Goal        | To do date minus 1 day
--------------------------- */
string newDate(int& day, int& month, int& year){
    switch (month) {
        case 1: [[fallthrough]];
        case 3: [[fallthrough]];
        case 5: [[fallthrough]];
        case 7: [[fallthrough]];
        case 8: [[fallthrough]];
        case 10: if (day == 31){
                day = 1;
                month++;
            } else {
                day++;
        } break;
        case 4: [[fallthrough]];
        case 6: [[fallthrough]];
        case 9: [[fallthrough]];
        case 11: if (day >= 30){
                day = 1;
                month++;
            } else {
                day++;
            } break;
        case 12: if (day == 31){
                day = 1;
                month = 1;
                year++;
            } else {
                day++;
            } break;
        case 2:
            if (checkYear(year)){
                if (day >= 29){
                    day = 1;
                    month++;
                } else {
                    day++;
                }
            } else if (!checkYear(year)) {
                if (day >= 28) {
                    day = 1;
                    month++;
                } else {
                    day++;
                }
            } break;
        default:
            break; // instruction default never reached for this function
    }
    return to_string(year) + "/" + formatTwoDigits(month) + "/" + formatTwoDigits(day);
}

/*---------------------------
Name        | getNearestDateInVector
Parameter(s)| string& date - the date who will update through the fct | long long int& updatedIndex - the index who will update through the fct
            | int& day - the day | int& month - the month | int& year - the year | const vector<share>& share - the vector share to check
Return      | void
Goal        | To get the nearest date in vector share
--------------------------- */
void getNearestDateInVector(string& date, long long int& updatedIndex, int& day, int& month, int& year, const vector<Share>& share){
    while (!isDateInVector(date, share, updatedIndex)){
        date = newDate(day, month, year);
    }
}

/*---------------------------
Name        | getNearestDateInVector
Parameter(s)| string& date - the date who will update through the fct | long long int& updatedIndex - the index who will update through the fct
            | int& day - the day | int& month - the month | int& year - the year | const vector<dividend>& dividend - the vector dividend to check
Return      | void
Goal        | To get the nearest date in vector dividend
--------------------------- */
void getNearestDateInVector(string& date, long long int& updatedIndex, int day, int month, int year, const vector<Dividend>& dividend){
    while (!isDateInVector(date, dividend, updatedIndex)){
        date = newDate(day, month, year);
    }
}

/*---------------------------
Name        | sumDividends
Parameter(s)| const int& firstYear - the first year of the range | const int& firstMonth - the first month of the range | const int& firstDay - the first day of the range
            | const int& roiYear - the last year of the range | const int& roiMonth - the last month of the range | const int& roiDay - the last day of the range
            | string& firstDate - the fist date of the range | const string& roiDate - the last date of the range | const vector<dividend>& dividend - the vector dividend
Return      | double
Goal        | To calculate the sum of all dividends in the range of firstDate to roiDate
--------------------------- */
double sumDividends(const int& firstYear, const int& firstMonth, const int& firstDay, const int& roiYear, const int& roiMonth, const int& roiDay, const string& firstDate, const string& roiDate, const vector<Dividend>& dividend){
    double sumDividend = 0.;
    if (!dividend.empty()){
        long long int indexToCheck = 0;

        int firstDayDiv = dividend[0].date.day;
        int firstMonthDiv = dividend[0].date.month;
        int firstYearDiv = dividend[0].date.year;

        int lastDayDiv = dividend.back().date.day;
        int lastMonthDiv = dividend.back().date.month;
        int lastYearDiv = dividend.back().date.year;

        // firstDate > firstDateDiv
        bool conditionFirstDate = firstYearDiv < firstYear or (firstYearDiv <= firstYear and firstMonthDiv < firstMonth) or (firstYearDiv <= firstYear and firstMonthDiv <= firstMonth and firstDayDiv <= firstDay);
        // roiDate > firstDateDiv
        bool conditionRoiDate1 = firstYearDiv < roiYear or (firstYearDiv <= roiYear and firstMonthDiv < roiMonth) or (firstYearDiv <= roiYear and firstMonthDiv <= roiMonth and firstDayDiv <= roiDay);
        // firstDate > lastDateDiv
        bool conditionFirstDate2 = lastYearDiv < firstYear or (lastYearDiv <= firstYear and lastMonthDiv < firstMonth) or (lastYearDiv <= firstYear and lastMonthDiv <= firstMonth and lastDayDiv <= firstDay);
        // roiDate > lastDateDiv
        bool conditionRoiDate2 = lastYearDiv < roiYear or (lastYearDiv <= roiYear and lastMonthDiv < roiMonth) or (lastYearDiv <= roiYear and lastMonthDiv <= roiMonth and lastDayDiv <= roiDay);

        string roiDateTemp = roiDate;
        string firstDateTemp = firstDate;
        if (!conditionFirstDate2){
            if (conditionRoiDate2){
                roiDateTemp = dividend.back().date.format;
            }
            getNearestDateInVector(roiDateTemp, indexToCheck, roiDay, roiMonth, roiYear, dividend); //find roiDate in the vector dividend
            long long int indexRoiDate = indexToCheck;
            indexToCheck = 0;

            if (roiDateTemp != roiDate){ //need the date before the last date in range
                indexRoiDate--;
            }

            if (conditionFirstDate and conditionRoiDate1){ //firstDate > firstDateDiv -> correct else no date | roiDate > firstDateDiv -> correct else no date
                getNearestDateInVector(firstDateTemp, indexToCheck, firstDay, firstMonth, firstYear, dividend); //find firstDate in the vector dividend
                long long int indexFirstDate = indexToCheck;

                for (auto it = dividend.begin()+indexFirstDate; it <= dividend.begin()+indexRoiDate; it++) {
                    sumDividend += it->dividend;
                }
            } else if (conditionFirstDate xor conditionRoiDate1){
                for (auto it = dividend.begin(); it <= dividend.begin()+indexRoiDate; it++) {
                    sumDividend += it->dividend;
                }
            }
        }
    }
    return sumDividend;
}

/*---------------------------
Name        | oneRoi
Parameter(s)| size_t& firstIndex - the first index in the range | const int& userInputMonth - the timeline the user want | const vector<share>& share - the vector share
            | const std::vector<dividend>& dividend - the vector dividend | bool& error - a flag error
Return      | Roi
Goal        | To calculate 1 ROI -> (lastClose + sumDividends - firstClose) / firstClose * 100
--------------------------- */
Roi oneRoi(size_t& firstIndex, const int& userInputMonth, const vector<Share>& share, const std::vector<Dividend>& dividend, bool& error){
    Roi oneRoi;

    int firstDay = share[firstIndex].date.day;
    int firstMonth = share[firstIndex].date.month;
    int firstYear = share[firstIndex].date.year;
    string firstDate = to_string(firstYear) + "/" + formatTwoDigits(firstMonth) + "/" + formatTwoDigits(firstDay);

    int addYear = (int)((firstMonth + userInputMonth)/12);
    int addMonth = (int)(userInputMonth - (12 * addYear));

    int roiMonth = firstMonth + addMonth;
    if (roiMonth == 0) roiMonth = 12, addYear--;
    int roiYear = firstYear + addYear;
    int roiDay = firstDay;
    string roiDate = to_string(roiYear) + "/" + formatTwoDigits(roiMonth) + "/" + formatTwoDigits(roiDay);

    int lastDay = share.back().date.day;
    int lastMonth = share.back().date.month;
    int lastYear = share.back().date.year;

    if (roiYear < lastYear or (roiYear <= lastYear and roiMonth < lastMonth) or (roiYear <= lastYear and roiMonth <= lastMonth and roiDay <= lastDay)) { // lastDate > roiDate -> correct else error

        long long int updatedIndex = 0;
        getNearestDateInVector(roiDate, updatedIndex, roiDay, roiMonth, roiYear, share); //find dateRoi in vector share

        double sumDividend = sumDividends(firstYear, firstMonth, firstDay, roiYear, roiMonth, roiDay, firstDate, roiDate, dividend);

        auto lastIndex = static_cast<size_t>(updatedIndex);
        double firstPriceClose = share[firstIndex].close;
        double lastPriceClose = share[lastIndex].close;
        oneRoi.roi = (lastPriceClose + sumDividend - firstPriceClose) / firstPriceClose * 100;
        oneRoi.date = firstDate;

    } else{
        error = true;
    }
    return oneRoi;
}

/*---------------------------
Name        | allRoi
Parameter(s)| const int& userInputMonth - the timeline the user want | const string& fileNameShare - the file x.csv | const string& fileNameDividend - the file x-2.csv
Return      | vector<Roi>
Goal        | To get all the ROI in the file share (not x-2.csv)
--------------------------- */
vector<Roi> allRoi(const int& userInputMonth, const string& fileNameShare, const string& fileNameDividend){
    pair<vector<Share>, string> share = readShare(fileNameShare);
    pair<vector<Dividend>, string> dividend = readDividend(fileNameDividend);

    size_t indexToCheck = 0;
    Roi roi;
    vector<Roi> allRoi;
    bool error = false;
    indexToCheck = 0;
    allRoi.push_back(oneRoi(indexToCheck, userInputMonth, share.first, dividend.first, error));
    while (!error){
        indexToCheck++;
        allRoi.push_back(oneRoi(indexToCheck, userInputMonth, share.first, dividend.first, error));
    }
    if (allRoi.back().date.empty()) allRoi.erase(allRoi.end());
    return allRoi;
}

/*---------------------------
Name        | roiMean
Parameter(s)| const vector<Roi>& allRoi - the vector with all the ROI
Return      | vector<Roi>
Goal        | To calculate the mean of all the ROI -> sumRoi / totalRoi
--------------------------- */
double roiMean(const vector<Roi>& allRoi){
    double sumRoi = 0;
    for (const Roi& i : allRoi) {
        sumRoi += i.roi;
    }
    auto totalRoi = static_cast<double>(allRoi.size());
    return (sumRoi/totalRoi);
}

/*---------------------------
Name        | roiAnnualise
Parameter(s)| const double& sumRoi - the RoiMean | int& userInputMonth - the timeline the user want
Return      | double
Goal        | To calculate the annualized of all the ROI -> (1 + RoiMean(not in %))^(1/userInputYear) - 1)
--------------------------- */
double roiAnnualise(const double& sumRoi, int& userInputMonth){
    double year = (double)userInputMonth/12.;
    return (pow((1 + sumRoi/100), (1/year)) - 1) * 100;
}

/*---------------------------
Name        | minRoi
Parameter(s)| vector<Roi>& allRoi - the vector with all the ROI
Return      | pair<double, string>
Goal        | To find the ROI with the minimum value and its date
--------------------------- */
pair<double, string> minRoi(vector<Roi>& allRoi){
    vector<double> temp;
    for(const auto& s : allRoi) {
        temp.push_back(s.roi);
    }
    auto minRoi = *min_element(temp.begin(), temp.end());
    auto it = find_if(allRoi.begin(), allRoi.end(), [&minRoi](struct Roi &arg) {
        return arg.roi == minRoi; });
    string minDate = it->date;
    return make_pair(minRoi, minDate);
}

/*---------------------------
Name        | maxRoi
Parameter(s)| vector<Roi>& allRoi - the vector with all the ROI
Return      | pair<double, string>
Goal        | To find the ROI with the maximum value and its date
--------------------------- */
pair<double, string> maxRoi(vector<Roi>& allRoi){
    vector<double> temp;
    for(const auto& s : allRoi) {
        temp.push_back(s.roi);
    }
    auto maxRoi = *max_element(temp.begin(), temp.end());
    auto it = find_if(allRoi.begin(), allRoi.end(), [&maxRoi](struct Roi &arg) {
        return arg.roi == maxRoi; });
    string maxDate = it->date;
    return make_pair(maxRoi, maxDate);
}