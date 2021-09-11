#ifndef RECORD_H
#define RECORD_H
#include <string>
class Record {
    public:
        Record(std::string fullName, int course, std::string date, int volume);

        Record(const Record& record);

        Record();

        std::string getFullName();

        int getCourse();

        std::string getDate();

        int getVolume();

        void setFullName(std::string newName);

        void setCourse(int newCourse);

        void setDate(std::string newDate);

        void setVolume(int newVolume);

    private:
        std::string fullName;
        int course;
        std::string date;
        int volume;

        static bool checkCourse(int course);

        static bool checkDate(std::string date);

        static bool checkVolume(int volume);
};

#endif