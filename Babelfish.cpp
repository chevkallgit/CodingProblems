

#include <iostream>
#include <map>
#include <string>
#include <iterator>
#include <sstream>
#include <algorithm>
using namespace std;

/**
* The data type used is a map in order to do a binary search
* Then we take in all words with their key word
* And use the find function to search the map
**/
int main()
{
    map<string, string> oof;
    map<string, string>::iterator it;
    string s, firstS, secondS, search;

    while (getline(cin, s) && s != "") {
        stringstream ss(s);
        ss >> firstS >> secondS;

        oof[secondS] = firstS;
    }

    while (cin >> search) {
        it = oof.find(search);

        if (it != oof.end()) {
            cout << it->second << endl;
        }
        else {
            cout << "eh" << endl;
        }
    }
}

