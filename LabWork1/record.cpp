#include "record.h"

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
    fullName = nullptr;
    course = 0;
    date = nullptr;
}

std::string Record::getFullName() {
    return fullName;
}

int Record::getCourse() {
    return course;
}

std::string Record::getDate() {
    return date;
}

void Record::setFullName(std::string newName) {
    fullName = newName;
}

void Record::setCourse(int newCourse) {
    if (newCourse < 1 || newCourse > 4) {
        throw std::exception();
    }
    course = newCourse;
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