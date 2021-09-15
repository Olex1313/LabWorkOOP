#include "../include/flow_record.h"

FlowRecord::FlowRecord(std::string fullName, int course, std::string date, int volume) : Record(fullName, course, date) {
    this->volume = volume;
}

FlowRecord::FlowRecord(const FlowRecord& record) {
    this->setFullName(record.getFullName());
    this->setCourse(record.getCourse());
    this->setDate(record.getDate());
    volume = record.volume;
}

FlowRecord::FlowRecord() : Record() {

    volume = 0;
}

int FlowRecord::getVolume() const {
    return this->volume;
}

bool FlowRecord::checkVolume(int volume) {
    return (volume > 0) ? true : false;
}

void FlowRecord::setVolume(int volume) {
    if (not checkVolume(volume)) {
        throw std::exception();
    }
    this->volume = volume;
}

const std::string& FlowRecord::toString() const {
    std::string result = "";
    result += this->getFullName() + ", ";
    result += std::to_string(this->getCourse()) + ", ";
    result += this->getDate() + ", ";
    result += std::to_string(this->getVolume());
    return result;
}

bool operator==(const FlowRecord& r1, const FlowRecord& r2) {
    return r1.getCourse() == r2.getCourse()
        && r1.getDate() == r2.getDate()
        && r1.getFullName() == r2.getFullName()
        && r1.getVolume() == r2.getVolume();
}