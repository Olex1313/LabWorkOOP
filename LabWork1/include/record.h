#ifndef RECORD_H
#define RECORD_H
#include <string>
class Record {
    public:
        Record(std::string fullName, int course, std::string date, int volume);

        Record(const Record& record);

        Record();

        const std::string& getFullName() const;

        int getCourse() const;

        const std::string& getDate() const;

        int getVolume() const;

        void setFullName(std::string newName);

        void setCourse(int newCourse);

        void setDate(std::string newDate);

        void setVolume(int newVolume);

        std::string toString() const;
    private:
        std::string fullName;
        int course;
        std::string date;
        int volume;

        static bool checkCourse(int course);

        static bool checkDate(std::string date);

        static bool checkVolume(int volume);
};
bool operator==(const Record& r1, const Record& r2);
#endif