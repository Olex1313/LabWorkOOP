#include <iostream>
#include "record.h"
#include <string>
#include <exception>

int main() {
    Record r("Full Name", 4, "13.10.2001");
    std::cout << r.getFullName() << " " << r.getCourse() << " " << r.getDate() << std::endl;
    return 0;
}