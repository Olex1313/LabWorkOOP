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

int compareDates(const std::string& firstDate, const std::string& secondDate) {
    // if left is later than right it returns 1
    // if right is later than left it returns -1
    // otherwise it returns 0
    if (firstDate == secondDate) {
        return 0;
    }
    int firstYear = std::stoi(firstDate.substr(6, 4));
    int secondYear = std::stoi(secondDate.substr(6, 4));
    if (firstYear > secondYear) {
        return 1;
    }
    if (secondYear > firstYear) {
        return -1;
    }
    int firstMonth = std::stoi(firstDate.substr(3, 2));
    int secondMonth = std::stoi(secondDate.substr(3, 2));
    if (firstMonth > secondMonth) {
        return 1;
    }
    if (secondMonth > firstMonth) {
        return -1;
    }
    int firstDay = std::stoi(firstDate.substr(0, 2));
    int secondDay = std::stoi(secondDate.substr(0, 2));
    if (firstDay > secondDay) {
        return 1;
    }
    if (secondDay > firstDay) {
        return -1;
    }
    return 0;
}

int determineWeek(const int& day) {
    if (day <= 28 && day >= 22) {
        return 4;
    }
    if (day >= 21 && day <= 15) {
        return 3;
    }
    if (day >= 8 && day <= 14) {
        return 2;
    }
    return 1;
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

Record& Journal::operator[](int index) {
    return (*(this->records[index]));
}

Record& Journal::get(int index) const {
    return *(this->records[index]);
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
            if(elems[0] ==  "Record") {
                std::string fullName = elems[1];
                int course = std::stoi(elems[2]);
                std::string date = elems[3];
                Record* record = new Record(fullName, course, date);
                this->add(record);
            }
            else if (elems[0] == "FlowRecord") {
                std::string fullName = elems[1];
                int course = std::stoi(elems[2]);
                std::string date = elems[3];
                int volume = std::stoi(elems[4]);
                FlowRecord* record = new FlowRecord(fullName, course, date, volume);
                this->add(record);
            }
            else if( elems[0] == "CutRecord") {
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

bool Journal::checkDates() {
    if (this->current == 0 || this->current == 1) {
        return true;
    }
    for (int i = 1; i < this->current; i++) {
        std::string firstDate = this->records[i]->getDate();
        std::string secondDate = this->records[i - 1]->getDate();
        int dateDiff = compareDates(firstDate, secondDate);
        if (dateDiff == -1) {
            return false;
        }
    }
    return true;
}

bool Journal::checkErrors() const {
    if (this->current == 1) {
        if (this->records[0]->getType() == "CutRecord" || this->records[0]->getType() == "Record") {
            return false;
        }
        else {
            FlowRecord* ptr = (FlowRecord*) this->records[0];
            return ptr->getVolume() >= 1 && ptr->getVolume() <= 2;
        }
    }
    int branchesCut = 0;
    int waterFlown = 0;
    int current_day = 0;
    int last_day = 0;
    int current_week = 0;
    int last_week = 0;
    for(int i = 0; i < this->current; i++) {
        current_day = std::stoi(this->records[i]->getDate().substr(0, 2));
        current_week = determineWeek(current_day);
        std::cerr << "Iteration: " << i << std::endl;
        std::cerr << "Day: " << current_day << std::endl;
        std::cerr << "Last Day: " << last_day << std::endl;
        if (this->records[i]->getType() == "FlowRecord") {
            waterFlown = ((FlowRecord*) this->records[i])->getVolume();
        }
        if (this->records[i]->getType() == "CutRecord") {
            branchesCut += ((CutRecord*) this->records[i])->getBranches();
        }
        if (current_day != last_day && this->records[i]->getType() != "FlowRecord") {
            if (waterFlown < 1 || waterFlown > 2) {
                std::cerr << "Wrong water amount: " << waterFlown << std::endl;
                return false;
            }
            waterFlown = 0;
        }
        if (current_week != last_week && last_week > 0 && this->records[i]->getType() != "CutRecord") {
            if (branchesCut < 4 || branchesCut > 8) {
                std::cerr << "Wrong branches amount" << std::endl;
                return false;
            }
            branchesCut = 0;
        }
        last_day = current_day;
        last_week = current_week;
    }
    if (waterFlown < 1 || waterFlown > 2) {
        return false;
    }
    return true;
}
std::string Journal::serializeToString() const {
    std::string result = "";
    for (int i = 0; i < current; i++) {
        result += this->records[i]->getType();
        result += ";";
        result += this->records[i]->toString();
        if (i < current - 1) {
            result += "\n";
        }
    }
    return result;
}

void printJournal(const Journal& journal) {
    for (int i = 0; i < journal.size(); i++) {
        std::cout << journal.get(i).toString() << std::endl;
    }
}