#pragma once
#include <string>
class checkinput
{
public:
    checkinput();
    ~checkinput();
    bool days_to_int_convertible(const std::string& days, int& daysInt);
    bool status_check(const std::string& status);
    bool ISBN_check(const std::string& ISBN);
    void ISBN_standardize(std::string& ISBN);
    bool checkifUIDexists(const std::string& uid);
    bool checkifbookIDexists(const std::string& bookID);
};


