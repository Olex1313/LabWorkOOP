#include "journal.h"
#include <iostream>

Journal::Journal(int size) {
    this->records = new Record[size];
    this->current = 0;
    this->capacity = size;
}

Journal::Journal(const Journal& journal) {
    this->records = journal.records;
    this->capacity = journal.capacity;
    this->current = 0;
}

Journal::Journal() {
    int capacity = 0;
    this->records = new Record[capacity];
    for (int i = 0; i < capacity; this->records[i] = Record());
    this->current = 0;
}

Journal::~Journal() {
    this->clear();
}

void Journal::add(Record record) {
    if (current == capacity) {
        Record* temporary = new Record[2 * capacity];
        for (int i = 0; i < capacity; i++) {
            temporary[i] = this->records[i];
        }
        delete[] this->records;
        capacity *= 2;
        this->records = temporary;
    }
    this->records[current++] = record;
}

void Journal::add(Record record, int index) {
    if (current == capacity) {
        Record* temporary = new Record[2 * capacity];
        for (int i = 0; i < capacity; i++) {
            temporary[i] = this->records[i];
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

int Journal::size() {
    return this->current;
}

Record& Journal::operator[](int index) {
    return this->records[index];
}

void Journal::clear() {
    delete[] this->records;
}

Record* Journal::getRecords() {
    return this->records;
}

void Journal::print() {
    for (int i = 0; i < this->current; i++) {
        std::cout << this->records[i].getFullName() << std::endl;
    }
}