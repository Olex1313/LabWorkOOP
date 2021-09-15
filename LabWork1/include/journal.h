#include "record.h"
#include <iostream>
#include <string>
#ifndef JOURNAL_H
#define JOURNAL_H

class Journal {
    public:
        Journal(int size);

        Journal(const Journal &journal);

        Journal();

        ~Journal();

        void add(Record record);

        void add(Record record, int position);

        void remove(int index);

        void remove();

        void print();

        bool checkDates();

        int size() const;

        Record &operator [](int index);

        void clear();

        void dumpToFile(std::string filename) const;
    private:
        Record *records;
        int capacity;
        int current;
        std::string serializeToString() const ;
};


#endif