// Dates.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <utility>
#include <iomanip>
#include <cctype>
#include <map>
#include <iterator>
#include <sstream>
#include <algorithm>

using namespace std;
using namespace std::rel_ops;

struct Date {

    int yyyy;
    int mm;
    int dd;

    // no dates before 1753
    static int const BASE_YEAR = 1753;

    // Enumerated type for names of the days of the week
    enum dayName { SUN, MON, TUE, WED, THU, FRI, SAT };

    // Is a date valid
    static bool validDate(int yr, int mon, int day)
    {
        return yr >= BASE_YEAR && mon >= 1 && mon <= 12 &&
            day > 0 && day <= daysIn(mon, yr);
    }

    bool isValid() const
    {
        return validDate(yyyy, mm, dd);
    }

    // Constructor to create a specific date.  If the date is invalid,
    // the behaviour is undefined
    Date(int yr = 1970, int mon = 1, int day = 1)
    {
        yyyy = yr;
        mm = mon;
        dd = day;
    }

    // Returns the day of the week for this
    dayName dayOfWeek() const
    {
        int a = (14 - mm) / 12;
        int y = yyyy - a;
        int m = mm + 12 * a - 2;
        return (dayName)((dd + y + y / 4 - y / 100 + y / 400 + 31 * m / 12) % 7);
    }

    // comparison operators
    bool operator==(const Date& d) const
    {
        return dd == d.dd && mm == d.mm && yyyy == d.yyyy;
    }

    bool operator<(const Date& d) const
    {
        return yyyy < d.yyyy || (yyyy == d.yyyy && mm < d.mm) ||
            (yyyy == d.yyyy && mm == d.mm && dd < d.dd);
    }

    // Returns true if yr is a leap year
    static bool leapYear(int y)
    {
        return (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0));
    }

    // number of days in this month
    static int daysIn(int m, int y)
    {
        switch (m) {
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            if (leapYear(y)) {
                return 29;
            }
            else {
                return 28;
            }
        default:
            return 31;
        }
    }

    // increment by day, month, or year
    //
    // Use negative argument to decrement
    //
    // If adding a month/year results in a date before BASE_YEAR, the result
    // is undefined.
    //
    // If adding a month/year results in an invalid date (Feb 29 on a non-leap
    // year, Feb 31, Jun 31, etc.), the results are automatically "rounded down"
    // to the last valid date

    // add n days to the date: complexity is about n/30 iterations
    void addDay(int n = 1)
    {
        dd += n;
        while (dd > daysIn(mm, yyyy)) {
            dd -= daysIn(mm, yyyy);
            if (++mm > 12) {
                mm = 1;
                yyyy++;
            }
        }

        while (dd < 1) {
            if (--mm < 1) {
                mm = 12;
                yyyy--;
            }
            dd += daysIn(mm, yyyy);
        }
    }

    // add n months to the date: complexity is about n/12 iterations
    void addMonth(int n = 1)
    {
        mm += n;
        while (mm > 12) {
            mm -= 12;
            yyyy++;
        }

        while (mm < 1) {
            mm += 12;
            yyyy--;
        }

        if (dd > daysIn(mm, yyyy)) {
            dd = daysIn(mm, yyyy);
        }
    }

    // add n years to the date
    void addYear(int n = 1)
    {
        yyyy += n;
        if (!leapYear(yyyy) && mm == 2 && dd == 29) {
            dd = 28;
        }
    }

    // number of days since 1753/01/01, including the current date
    int daysFromStart() const
    {
        int c = 0;
        Date d(BASE_YEAR, 1, 1);
        Date d2(d);

        d2.addYear(1);
        while (d2 < *this) {
            c += leapYear(d.yyyy) ? 366 : 365;
            d = d2;
            d2.addYear(1);
        }

        d2 = d;
        d2.addMonth(1);
        while (d2 < *this) {
            c += daysIn(d.mm, d.yyyy);
            d = d2;
            d2.addMonth(1);
        }
        while (d <= *this) {
            d.addDay();
            c++;
        }
        return c;
    }
};

// Reads a date in yyyy/mm/dd format, assumes date is valid and in the
// right format
istream& operator>>(istream& is, Date& d)
{
    char c;
    return is >> d.yyyy >> c >> d.mm >> c >> d.dd;
}

// print date in yyyy/mm/dd format
ostream& operator<< (ostream& os, const Date& d) {
    char t = os.fill('0');
    string s;

    switch (d.mm) {
    case 1:
        s = "January";
        break;
    case 2:
        s = "Febuary";
        break;
    case 3:
        s = "March";
        break;
    case 4:
        s = "April";
        break;
    case 5:
        s = "May";
        break;
    case 6:
        s = "June";
        break;
    case 7:
        s = "July";
        break;
    case 8:
        s = "August";
        break;
    case 9:
        s = "September";
        break;
    case 10:
        s = "October";
        break;
    case 11:
        s = "November";
        break;
    case 12:
        s = "December";
        break;
    }

    os << d.yyyy << '-' << setw(2) << s << '-' << setw(2) << d.dd;
    os.fill(t);
    return os;
}


int main()
{
    int rounds, yr, day, monthN, add;
    string s, month;
    Date d;

    cin >> rounds;

    for (int i = 1; i <= rounds; i++) {

        cin >> s >> add;

        for (int j = 0; j < s.length(); j++) {
            if (s[j] == '-') {
                s[j] = ' ';
            }
        }

        stringstream ss(s);
        ss >> yr >> month >> day;

        if (month == "January") {
            monthN = 1;
        }
        else if (month == "Febuary") {
            monthN = 2;
        }
        else if (month == "March") {
            monthN = 3;
        }
        else if (month == "April") {
            monthN = 4;
        }
        else if (month == "May") {
            monthN = 5;
        }
        else if (month == "June") {
            monthN = 6;
        }
        else if (month == "July") {
            monthN = 7;
        }
        else if (month == "August") {
            monthN = 8;
        }
        else if (month == "September") {
            monthN = 9;
        }
        else if (month == "October") {
            monthN = 10;
        }
        else if (month == "November") {
            monthN = 11;
        }
        else if (month == "December") {
            monthN = 12;
        }
        else {
            return 0;
        }

        if (d.validDate(yr, monthN, day)) {
            d.yyyy = yr;
            d.mm = monthN;
            d.dd = day;
        }
        else {
            return 0;
        }

        d.addDay(add);

        cout << "Case " << i << ": " << d << endl;

    }
}


