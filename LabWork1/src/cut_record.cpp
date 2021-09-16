#include "../include/cut_record.h"

CutRecord::CutRecord(std::string fullName, int course, std::string date, int branches) : Record(fullName, course, date) {
    this->branches = branches;
}

CutRecord::CutRecord(const CutRecord& record) : Record(record) {
    branches = record.branches;
}

CutRecord::CutRecord() : Record() {

    branches = 0;
}

int CutRecord::getBranches() const {
    return this->branches;
}

bool CutRecord::checkBranches(int branches) {
    return (branches > 0) ? true : false;
}

void CutRecord::setBranches(int branches) {
    if (not checkBranches(branches)) {
        throw std::exception();
    }
    this->branches = branches;
}

std::string CutRecord::toString() const {
    std::string result = "";
    result += this->getFullName() + ";";
    result += std::to_string(this->getCourse()) + ";";
    result += this->getDate() + ";";
    result += std::to_string(this->getBranches());
    return result;
}

bool operator==(const CutRecord& r1, const CutRecord& r2) {
    return r1.getCourse() == r2.getCourse()
        && r1.getDate() == r2.getDate()
        && r1.getFullName() == r2.getFullName()
        && r1.getBranches() == r2.getBranches();
}