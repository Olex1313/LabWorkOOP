#include <iostream>
#include "../include/record.h"
#include "../include/journal.h"
#include "../include/flow_record.h"
#include "../include/cut_record.h"
#include <exception>
#include <cassert>

int main() {
    Record record = Record("Full Name", 4, "13.10.2001");
    Record defaultRecord = Record();
    Record copyRecord = Record(record);
    assert(record.getCourse() == 4);
    assert(record.getFullName() == "Full Name");
    assert(record.getDate() == "13.10.2001");
    assert(record.getCourse() == 4);
    assert(copyRecord.getFullName() == "Full Name");
    assert(copyRecord.getDate() == "13.10.2001");
    assert(copyRecord.getCourse() == 4);
    assert(defaultRecord.getFullName() == "");
    assert(defaultRecord.getDate() == "");
    assert(defaultRecord.getCourse() == 0);
    assert(record == copyRecord);

    Journal journal = Journal(2);
    Record* p = &record;
    FlowRecord* flowRecord = new FlowRecord("flow record", 3, "15.09.2021", 4);
    CutRecord* cutRecord = new CutRecord("cut record", 3, "15.09.2021", 4);
    journal.add(p);
    journal.add(flowRecord);
    journal.add(cutRecord);
    journal.print();
    journal.dumpToFile("test.txt");
    std::cout << "All tests completed without errors" << std::endl;
    return 0;
}