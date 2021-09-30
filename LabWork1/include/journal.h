#include "record.h"
#include "flow_record.h"
#include "cut_record.h"
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <vector>
#include <sstream>
#ifndef JOURNAL_H
#define JOURNAL_H

class Journal {
    public:
        Journal(int size);

        Journal(const Journal &journal);

        Journal();

        ~Journal();

        void add(Record* record);

        void add(Record* record, int position);

        void remove(int index);

        void remove();

        void print();

        bool checkDates();

        int size() const;

        Record *operator [](int index);

        void clear();

        void dumpToFile(const std::string& filename) const;

        void loadFromFile(const std::string& filename);

        bool checkDates() const;

        bool checkErrors() const;

    private:
        Record **records;

        int capacity;

        int current;

        std::string serializeToString() const ;
};


#endif