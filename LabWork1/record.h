#ifndef RECORD_H
#define RECORD_H
class Record {
    public:
        Record(std::string fullName, int course, std::string date) {
        }

        Record(const Record& record) {
        }

        Record() {
        }

        std::string getFullName() {
        }

        int getCourse() {
        }

        std::string getDate() {
        }

        void setFullName(std::string newName) {
        }

        void setCourse(int newCourse) {
        }

    private:
        std::string fullName;
        int course;
        std::string date;

        static bool checkCourse(int course) {
        }

        static bool checkDate(std::string date) {
        }
};

#endif