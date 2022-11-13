// https://www.codeabbey.com/index/task_view/hexagonal-grid
// https://www.redblobgames.com/grids/hexagons/
//https://en.wikipedia.org/wiki/Hexagon#Parameters
//https://www.redblobgames.com/grids/hexagons/implementation.html
//https://stackoverflow.com/questions/5084801/manhattan-distance-between-tiles-in-a-hexagonal-grid
//https://stackoverflow.com/questions/2459402/hexagonal-grid-coordinates-to-pixel-coordinates?rq=1

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <chrono>
#include <cmath>
#include <cassert>
#include <limits>

#include "Console.h"
#include "CodeAbbey.h"
#include "LS_library.h"
#define VERSION "1.0"

using namespace std;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

class OffCoord {
public:
	int row;
	int col;

	OffCoord() {
		this->col = 0;
		this->row = 0;
	}
	OffCoord(int c, int r) {
		this->col = c;
		this->row = r;
	}
	void print() {
		cout << "col: " << this->col << " row: " << this->row << endl;
	}
	/*double distance() {
		float x = this->col;
		float y = ((this->col + this->row) / 2) * (2 / sqrt(3));
		return sqrt(pow(x, 2) + pow(y, 2));
	}*/
};

class Hex {
public:
	int q;
	int r;
	int s;

	Hex() {
		this->q = 0;
		this->r = 0;
		this->s = 0;
	}
	Hex(int _q, int _r, int _s) {
		this->q = _q;
		this->r = _r;
		this->s = _s;
		if (this->q + this->r + this->s != 0) throw "q + r + s must be 0";
	}
	void print() {
		cout << "q: " << this->q << " r: " << this->r << " s: " << this->s << endl;
	}
	void add(Hex dir) {
		this->q += dir.q;
		this->r += dir.r;
		this->s += dir.s;
	}
	/*OffCoord to_oddr() {
		int col = this->q + (this->r - (this->r & 1)) / 2;
		int row = this->r;
		return OffCoord(col, row);
	}*/
	float distance() {
		const float S = 1 / sqrt(3.0); // hardcoding the size W = S*sqrt(3); W = 1;
		float y = 3.0 / 2 * S * this->r;
		float x = sqrt(3.0) * S * (this->r/2.0 + this->s);
		return sqrt(pow(x, 2) + pow(y, 2));
	}
};



map<char, Hex> SetDirections();

int main() {
	auto t1 = high_resolution_clock::now();
	cout << "Hexagonal Grid v" << VERSION << "!\n\n";
	string path = "Test.txt";
	//string path = "Try.txt";
	vector<string> raw_data = loadData(path);
	vector<string> solution;

	map<char, Hex> DIR = SetDirections();

	for (int i = 1; i < raw_data.size(); i++) {
		string problem = raw_data[i];
		cout << problem << " : " << endl;
		Hex origin = Hex();
		Hex reference = Hex();
		for (char c : problem) {
			reference.add(DIR[c]);
		}
		reference.print();
		//OffCoord ref = reference.to_oddr();
		//ref.print();
		cout << reference.distance() << endl;



	}

	cout << "\nSolution: " << joinVector(solution, " ") << endl;;

	/***********************/
	auto t2 = high_resolution_clock::now();
	auto ms_int = duration_cast<milliseconds>(t2 - t1);
	cout << "Execution time: " << ms_int.count() << " ms" << endl;
}

map<char, Hex> SetDirections() {
	map<char, Hex> dirs;
	dirs['A'] = Hex(1, 0, -1);
	dirs['B'] = Hex(1, -1, 0);
	dirs['C'] = Hex(0, -1, 1);
	dirs['D'] = Hex(-1, 0, 1);
	dirs['E'] = Hex(-1, 1, 0);
	dirs['F'] = Hex(0, 1, -1);
	return dirs;
}
