// HoaxOrWhat.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <set>

using namespace std;

int main()
{
    int round, amount;
    
    while (cin >> round && round != 0) {
        
        long long add = 0;

        multiset<int> container;

        for (int i = 0; i < round; i++) {
            cin >> amount;
            
            for (int j = 0; j < amount; j++) {
                 int temp;
                 cin >> temp;
                 container.insert(temp);
             }

            multiset<int>::iterator itE = --container.end();
            multiset<int>::iterator itB = container.begin();

            add += *itE - *itB;

            container.erase(container.begin());
            container.erase(--container.end());
        }

        cout << add << endl;
    }

}


