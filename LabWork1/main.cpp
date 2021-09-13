#include <iostream>
#include "record.h"
#include "journal.h"
#include <string>
#include <exception>
#include <cassert>

int main() {
    Record record = Record("Full Name", 4, "13.10.2001", 5);
    Record defaultRecord = Record();
    Record copyRecord = Record(record);
    Journal journal = Journal(1);
    journal.add(record);
    journal.add(defaultRecord);
    journal.add(copyRecord);
    journal.remove();
    journal.add(Record("insert", 4, "13.12.2020", 5), 5);
    journal.print();
    std::cout << journal.size() << std::endl;
    journal.remove(5);
    journal.print();
    std::cout << journal.size() << std::endl;
    assert(record.getCourse() == 4);
    assert(record.getFullName() == "Full Name");
    assert(record.getDate() == "13.10.2001");
    assert(record.getVolume() == 5);
    assert(record.getCourse() == 4);
    assert(copyRecord.getFullName() == "Full Name");
    assert(copyRecord.getDate() == "13.10.2001");
    assert(copyRecord.getVolume() == 5);
    assert(copyRecord.getCourse() == 4);
    assert(defaultRecord.getFullName() == "");
    assert(defaultRecord.getDate() == "");
    assert(defaultRecord.getVolume() == 0);
    assert(defaultRecord.getCourse() == 0);
    assert(record == copyRecord);
    journal.dumpToFile("test.txt");
    journal.clear();
    assert(journal.size() == 0);

    std::cout << "All tests completed without errors" << std::endl;
    return 0;
}