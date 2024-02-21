/* ---------------------------
Labo        |   PRG1-Labo3
Author(s)   |   David Schildböck
Start date  |   10.11.2023
Deadline    |   21.11.2023 (2359)
Goal        |   Header file to formules.cpp
--------------------------- */
#ifndef PRG1_LABO3_MSS_FORMULES_H
#define PRG1_LABO3_MSS_FORMULES_H

#include "../files/fileReader.h"
#include <vector>
#include <string>

std::string formatTwoDigits(const int& number);

struct Roi{
    double roi = 0.;
    std::string date;
};

std::vector<Roi> allRoi(const int& nbrMonth, const std::string& fileNameShare, const std::string& fileNameDividend);

double roiMean(const std::vector<Roi>& allRoi);

double roiAnnualise(const double& sumRoi, int& userInputMonth);

std::pair<double, std::string> minRoi(std::vector<Roi>& allRoi);

std::pair<double, std::string> maxRoi(std::vector<Roi>& allRoi);

#endif //PRG1_LABO3_MSS_FORMULES_H
