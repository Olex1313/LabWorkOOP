#include <iostream>
#include "record.h"

int main() {
    Record r("Full Name", 4, "13.10.2001");
    std::cout << r.getFullName() << " " << r.getCourse() << " " << r.getDate() << std::endl;
    return 0;
}