#include "../include/journal.h"

std::vector<std::string> split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(std::move(item));
    }
    return elems;
}

Journal::Journal(int size) {
    this->records = new Record*[size];
    this->current = 0;
    this->capacity = size;
}

Journal::Journal(const Journal& journal) { // Needs fix due to copying adress
    this->records = journal.records;
    this->capacity = journal.capacity;
    this->current = 0;
}

Journal::Journal() {
    int capacity = 1;
    this->records = new Record*[capacity];
    for (int i = 0; i < capacity; this->records[i] = new Record);
    this->current = 0;
}

Journal::~Journal() {
    delete[] this->records;
}

void Journal::add(Record* record) {
    if (current == capacity) {
        Record** temporary = new Record*[2 * capacity];
        for (int i = 0; i < capacity; i++) {
            temporary[i] = this->records[i];
        }
        delete[] this->records;
        capacity *= 2;
        this->records = temporary;
    }
    this->records[current] = record;
    current++;
}

void Journal::add(Record* record, int index) {
    if (current == capacity) {
        Record** temporary = new Record*[2 * capacity];
        for (int i = 0; i < capacity; i++) {
            temporary[i] = this->records[i];
            delete[] this->records[i];
        }
        delete[] this->records;
        capacity *= 2;
        this->records = temporary;
    }
    if (index > current) {
        this->add(record);
        return;
    }
    for (int i = current; i >= index - 1; i--) {
        this->records[i + 1] = this->records[i];
    }
    current++;
    this->records[index] = record;
}

void Journal::remove() {
    this->current--;

}

void Journal::remove(int index) {
    if (index > current - 1) {
        return;
    }
    for (int i = index; i < current - 1; i++) {
        this->records[i] = this->records[i + 1];
    }
    this->current--;
}

int Journal::size() const {
    return this->current;
}

Record* Journal::operator[](int index) {
    return (this->records[index]);
}


void Journal::clear() {
    this->current = 0;
}

void Journal::print() {
    for (int i = 0; i < this->current; i++) {
        std::cout << this->records[i]->toString() << std::endl;
    }
}

void Journal::dumpToFile(const std::string& filename) const {
    std::ofstream outfile;
    outfile.open(filename);
    outfile << this->serializeToString();
    outfile.close();
}

void Journal::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::vector<std::string> elems = split(line, ';');
            std::cout << line << std::endl;
            if(elems[0] ==  "6Record") {
                std::string fullName = elems[1];
                int course = std::stoi(elems[2]);
                std::string date = elems[3];
                Record* record = new Record(fullName, course, date);
                this->add(record);
            }
            else if (elems[0] == "10FlowRecord") {
                std::string fullName = elems[1];
                int course = std::stoi(elems[2]);
                std::string date = elems[3];
                int volume = std::stoi(elems[4]);
                FlowRecord* record = new FlowRecord(fullName, course, date, volume);
                this->add(record);
            }
            else if( elems[0] == "9CutRecord") {
                std::string fullName = elems[1];
                int course = std::stoi(elems[2]);
                std::string date = elems[3];
                int branches = std::stoi(elems[4]);
                CutRecord* record = new CutRecord(fullName, course, date, branches);
                this->add(record);
            }
            else {
                continue;
            }
        }
        file.close();
    }
}

std::string Journal::serializeToString() const {
    std::string result = "";
    for (int i = 0; i < current; i++) {
        result += typeid(*(this->records[i])).name();
        result += ";";
        result += this->records[i]->toString();
        if (i < current - 1) {
            result += "\n";
        }
    }
    return result;
}
