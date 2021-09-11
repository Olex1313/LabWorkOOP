#include "record.h"

Record::Record(std::string fullName, int course, std::string date, int volume) {
    if (not Record::checkDate(date)) {
        throw std::exception();
    }
    if (not Record::checkCourse(course)) {
        throw std::exception();
    }
    if (not Record::checkVolume(volume)) {
        throw std::exception();
    }
    this->fullName = fullName;
    this->course = course;
    this->volume = volume;
    this->date = date;
}

Record::Record(const Record& record) {
    fullName = record.fullName;
    course = record.course;
    date = record.date;
    volume = record.volume;
}

Record::Record() {
    fullName = "";
    course = 0;
    date = "";
    volume = 0;
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

int Record::getVolume() {
    return volume;
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

void Record::setVolume(int volume) {
    if (not checkVolume(volume)) {
        throw std::exception();
    }
    this->volume = volume;
}

bool Record::checkCourse(int course) {
    return (course > 0 && course < 5) ? true : false;
}

bool Record::checkVolume(int volume) {
    return (volume > 0) ? true : false;
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