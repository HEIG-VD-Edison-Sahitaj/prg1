/* ---------------------------
Labo        |   PRG1-Labo3
Author(s)   |   Edison Sahitaj
Start date  |   10.11.2023
Deadline    |   21.11.2023 (2359)
Goal        |   Header file to fileReader.cpp
--------------------------- */

#ifndef PRG1_LABO3_MSS_FILEREADER_H
#define PRG1_LABO3_MSS_FILEREADER_H

#include <vector>
#include <string>

struct Date {
    int day=0;
    int month=0;
    int year=0;
    std::string format;
};

struct Share {
    Date date;
    double close=0.;
};

struct Dividend {
    Date date;
    double dividend=0.;
};

std::pair<std::vector<Share>, std::string> readShare(const std::string& fileName);
std::pair<std::vector<Dividend>, std::string> readDividend(const std::string& fileName);

#endif //PRG1_LABO3_MSS_FILEREADER_H