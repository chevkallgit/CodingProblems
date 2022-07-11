// Bumper-To-BumperTraffic.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

//
// For input i used a vector to store possible times of stop
// because of the unknown size, i also treated the car that was
// behind to be car1 or x1 and just swaped corrisponding values.
// 
// For logic I just used a bool (track) to use as my switch 
// condition for starting and stoping then incremented each cars
// position (x) depending on track and if car1 + 4.4 (size of car)
// ever exceeds car2 we have a bump, and run for the max
// time given to look for all possible bumps.
// 
//

int main()
{
    int tmp, x1, x2, n1, n2;
    long long crrTime = 1;

    vector<int> t1, t2;

    cin >> x1 >> x2;

    cin >> n1;
    while (n1--) {
        cin >> tmp;
        if (x2 < x1) {
            t2.push_back(tmp);
        }
        else {
            t1.push_back(tmp);
        }
    }

    cin >> n2;
    while (n2--) {
        cin >> tmp;
        if (x2 < x1) {
            t1.push_back(tmp);
        }
        else {
            t2.push_back(tmp);
        }
    }

    tmp = x2;
    if (x2 < x1) {
        x2 = x1;
        x1 = tmp;
    }

    int i = 0, j = 0;
    bool trackX1 = false, trackX2 = false;

    while (true) {

        if (i < t1.size()) {
            if (t1.at(i) == crrTime) {
                trackX1 = !trackX1;
                
                i++;
            }
        }
        if (trackX1) {
                x1++;
        }

        if (j < t2.size()) {
            if (t2.at(j) == crrTime) {
                trackX2 = !trackX2;
                
                j++;
            }
        }
        if (trackX2) {
                x2++;
        }

        crrTime++;

        if (x2 < (x1 + 4.4)) {
            cout << "bumper tap at time " << crrTime << endl;
            cout << x1 << endl << x2;
            break;
        }

        if (crrTime == 1000000) {
            cout << "safe and sound";
            break; 
        }

        
    }


}
