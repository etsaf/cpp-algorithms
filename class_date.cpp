/* date from January 1, 1970 to December 31, 2099
++ and -- return next and previous day, + int and - int return
date that is int days away, - Date returns number of days between these dates */

#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

class Date {
private:
int Days;

public:
    Date(int days)
    : Days(days) {
        if (days < 1 || days > 47482) {
            throw std::invalid_argument("Incorrect date");
        }
    }

    Date(int day, int month, int year)
            : Days(day) {
        std::vector<int> month_length = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
            month_length[1] = 29;
        } else {
            month_length[1] = 28;
        }
        if (year > 2099 || year < 1970) {
            throw std::invalid_argument("Incorrect date");
        }
        if (month > 12 || month < 1) {
            throw std::invalid_argument("Incorrect date");
        }
        if (day > month_length[month - 1] || day < 1) {
            throw std::invalid_argument("Incorrect date");
        }
        Days = DateToDays(day, month, year);
    }

    int GetDay() const {
        return std::get<0>(DaysToDate(Days));
    }

    int GetMonth() const {
        return std::get<1>(DaysToDate(Days));
    }

    int GetYear() const {
        return std::get<2>(DaysToDate(Days));
    }

    Date& operator++() {
        *this = Date(Days + 1);
        return *this;
    }

    Date& operator--() {
        *this = Date(Days - 1);
        return *this;
    }

    Date operator+(const int rhs) const {
        Date tmp(Days + rhs);
        return tmp;
    }

    Date operator-(const int rhs) const {
        Date tmp(Days - rhs);
        return tmp;
    }

    int operator-(const Date& rhs) const {
        Date tmp(Days);
        int counter = 0;
        counter = tmp.Days - rhs.Days;
        return counter;
    }

    int DateToDays(int Day, int Month, int Year) const {
        int res = 0;
        int y = 1970;
        int m = 1;
        int year = Year;
        std::vector<int> month_length = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
            month_length[1] = 29;
        } else {
            month_length[1] = 28;
        }
        while (y < Year) {
            if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0)) {
                res += 366;
            } else {
                res += 365;
            }
            ++y;
        }
        while (m < Month) {
            res += month_length[m - 1];
            ++m;
        }
        res += Day;
        return res;
    }

    std::tuple<int, int, int> DaysToDate(int days) const {
        int temp = 0;
        int y = 1970;
        int m = 1;
        while (true) {
            int add;
            if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0)) {
                add = 366;
            } else {
                add = 365;
            }
            if ((temp + add) >= days) {
                break;
            } else {
                temp += add;
                y += 1;
            }
        }
        while (true) {
            int add;
            std::vector<int> month_length = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
            if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0)) {
                month_length[1] = 29;
            } else {
                month_length[1] = 28;
            }
            add = month_length[m - 1];
            if ((temp + add) >= days) {
                break;
            } else {
                temp += add;
                m += 1;
            }
        }
        int d = days - temp;
        return std::tie(d, m, y);
    }
};

