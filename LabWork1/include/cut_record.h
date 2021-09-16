#ifndef CUTRECORD_H
#define CUTRECORD_H
#include <string>
#include "../include/record.h"

class CutRecord : public Record {
    public:
        CutRecord(std::string fullName, int course, std::string date, int branches);

        CutRecord(const CutRecord& record);

        CutRecord();

        int getBranches() const;

        void setBranches(int newbranches);

        std::string toString() const;
    private:
        static bool checkBranches(int branches);
        int branches;
};
bool operator==(const CutRecord& r1, const CutRecord& r2);
#endif