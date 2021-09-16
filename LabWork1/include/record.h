#ifndef RECORD_H
#define RECORD_H
#include <string>
class Record {
    public:
        Record(std::string fullName, int course, std::string date);

        Record(const Record& record);

        Record();

        const std::string& getFullName() const;

        int getCourse() const;

        const std::string& getDate() const;

        void setFullName(std::string newName);

        void setCourse(int newCourse);

        void setDate(std::string newDate);

        virtual std::string toString() const;

        virtual std::string getType() const;
    private:
        std::string fullName;

        int course;

        std::string date;
    protected:
        static bool checkCourse(int course);

        static bool checkDate(std::string date);
};
bool operator==(const Record& r1, const Record& r2);
#endif