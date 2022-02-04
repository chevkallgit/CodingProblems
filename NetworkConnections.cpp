// NetworkConnections.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class UnionFind
{
	struct UF { int p; int rank; };

public:
	UnionFind(int n) {          // constructor
		howMany = n;
		uf = new UF[howMany];
		for (int i = 0; i < howMany; i++) {
			uf[i].p = i;
			uf[i].rank = 0;
		}
	}

	~UnionFind() {
		delete[] uf;
	}

	int find(int x) { return find(uf, x); }        // for client use

	bool merge(int x, int y) {
		int res1, res2;
		res1 = find(uf, x);
		res2 = find(uf, y);
		if (res1 != res2) {
			if (uf[res1].rank > uf[res2].rank) {
				uf[res2].p = res1;
			}
			else {
				uf[res1].p = res2;
				if (uf[res1].rank == uf[res2].rank) {
					uf[res2].rank++;
				}
			}
			return true;
		}
		return false;
	}

private:
	int howMany;
	UF* uf;

	int find(UF uf[], int x) {     // recursive funcion for internal use
		if (uf[x].p != x) {
			uf[x].p = find(uf, uf[x].p);
		}
		return uf[x].p;
	}
};

int main()
{
	int cases, computers, firstN, secondN;
	string line;
	char cq;
	
	// first input for how many times we loop
	cin >> cases;

	for (int i = 0; i < cases; i++) {

		// input how many possible computers are in a case and create union
		cin >> computers;
		cin.ignore(1);
		UnionFind uf(computers);
		int  yes = 0, no = 0;

		while (1) {

			// get input line of union instructions
			getline(cin, line);
			if (line.empty() || cin.eof()) {
				break;
			}

			// format input
			stringstream ss(line);
			ss >> cq >> firstN >> secondN;

			firstN -= 1;
			secondN -= 1;

			// union logic
			if (cq == 'c') {
				uf.merge(firstN, secondN);
			}
			else if (cq == 'q') {
				if (uf.find(firstN) == uf.find(secondN)) {
					yes++;
				}
				else {
					no++;
				}
			}
			
		}

		// output
		if (i != (cases - 1)) {
			cout << yes << "," << no << endl << endl;
		}
		else {
			cout << yes << "," << no << endl;
		}
	}
}

