// Wifi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

vector<int> homes;

// for finding f(n,D)
int f(double D) {
    int wifi = 1;
    double range = homes[0] + D;
    for (int i = 0; i < homes.size(); i++) {
        if (homes[i] > range) {
            range = homes[i] + D;
            wifi++;
        }
    }
    return wifi;
}




int main()
{
    int wifi, house, rounds;
    
    cin >> rounds;
    // input format and stroage
    while (rounds--) {
        cin >> wifi >> house;
        homes.clear();

        for (int i = 0; i < house; i++) {
            int temp;
            cin >> temp;
            homes.push_back(temp);
        }
    }

    double lowD = 0.00;
    double hiD = 1000000000.00;
    double D;

    // find the optimal D with given variables
    while (hiD - lowD > 0.01) {
        D = (hiD + lowD) / 2.0;
        if (f(D) > house) {
            lowD = D;
        }
        else {
            hiD = D;
        }
    }

    cout << hiD;
    
}


