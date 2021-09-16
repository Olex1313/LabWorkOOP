#include "../include/record.h"

Record::Record(std::string fullName, int course, std::string date) {
    if (not Record::checkDate(date)) {
        throw std::exception();
    }
    if (not Record::checkCourse(course)) {
        throw std::exception();
    }
    this->fullName = fullName;
    this->course = course;
    this->date = date;
}

Record::Record(const Record& record) {
    fullName = record.fullName;
    course = record.course;
    date = record.date;
}

Record::Record() {
    fullName = "";
    course = 0;
    date = "";
}

const std::string& Record::getFullName() const {
    return this->fullName;
}

int Record::getCourse() const {
    return this->course;
}

const std::string& Record::getDate() const {
    return this->date;
}

void Record::setFullName(std::string newName) {
    this->fullName = newName;
}

void Record::setCourse(int newCourse) {
    if (not checkCourse(newCourse)) {
        throw std::exception();
    }
    this->course = newCourse;
}

bool Record::checkCourse(int course) {
    return (course > 0 && course < 5) ? true : false;
}

bool Record::checkDate(std::string date) {
    if (date.length() != 10) {
        return false;
    }
    int day = std::stoi(date.substr(0,2));
    if (day < 1 || day > 31) {
        return false;
    }
    int month = std::stoi(date.substr(3, 2));
    if (month < 1 || month > 12) {
        return false;
    }
    int year = std::stoi(date.substr(6, 4));
    if (year < 1) {
        return false;
    }
    return true;
}

std::string Record::toString() const {
    return this->fullName + ";" + this->date + ";" + std::to_string(this->course);
}

bool operator==(const Record& r1, const Record& r2) {
    return r1.getCourse() == r2.getCourse()
        && r1.getDate() == r2.getDate()
        && r1.getFullName() == r2.getFullName();
}