
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <ctype.h>
#include <sstream>
#include <locale>
using namespace std;

int main()
{
    //beginning varriables
    int keywords, excuses;
    int count = 1;
    string s, s1;

    //while loop that will stop when the propmts for keywords and excuses stop
    while (cin >> keywords >> excuses) {

        //vectors for varables so we have an index to refer too
        vector<string> key;
        vector<string> excuse;
        vector<int> keywordsUsed;

        //for loop to put keywords into a vector
        for (int i = 0; i < keywords; i++) {
            cin >> s;
            key.push_back(s);
        }

        //for loop to loop thorugh the number of excuses and put them into the vector
        for (int i = 0; i < (excuses + 1); i++) {
            getline(cin, s);
            excuse.push_back(s);
            keywordsUsed.push_back(0);

            //formatting our input to make it easier to read
            s1 = " " + excuse[i] + " ";
            for (int x = 0; x < s1.length(); x++) {
                if (!isalpha(s1[x])) {
                    s1[x] = ' ';
                }
                s1[x] = tolower(s1[x]);
            }

            //using a string stream to break apart the excuses to compaire each word with a key word
            //then adding the amount found to a keyword count
            istringstream iss(s1);
            string word;
            while (iss >> word) {
                for (int j = 0; j < key.size(); j++) {
                    if (word == key[j]) {
                        keywordsUsed[i]++;
                    }
                }
            }
        }

        //for finding the highest number of keywords used out of the excuses
        int max = 0;
        for (int i = 0; i < keywordsUsed.size(); i++) {
            if (keywordsUsed[i] > max) {
                max = keywordsUsed[i];
            }
        }

        //write out the correct excuses acorrding to key words used
        cout << "Excuse Set #" << count << endl;
        for (int i = 0; i < keywordsUsed.size(); i++) {
            if (keywordsUsed[i] == max) {
                cout << excuse[i] << endl;
            }
        }
        count++;
        cout << endl;
    }
}

