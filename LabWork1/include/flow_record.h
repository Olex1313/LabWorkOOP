#ifndef FLOWRECORD_H
#define FLOWRECORD_H
#include <string>
#include "../include/record.h"

class FlowRecord : public Record {
    public:
        FlowRecord(std::string fullName, int course, std::string date, int volume);

        FlowRecord(const FlowRecord& record);

        FlowRecord();

        int getVolume() const;

        void setVolume(int newVolume);

        std::string toString() const;
    private:
        static bool checkVolume(int volume);
        int volume;
};
bool operator==(const FlowRecord& r1, const FlowRecord& r2);
#endif