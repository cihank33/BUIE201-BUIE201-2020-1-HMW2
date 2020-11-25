#include <iostream>
#include <vector>
#include <set>
#include <chrono>

using namespace std;

int FindSimpleWithRangeForLoop(vector<int>& v, int ValueToFind)
{
	int i = 0;
	for (int x : v)
	{
		if (x == ValueToFind)
			return i;
		i++;
	}
	return -1;
}

int FindBinarySearch(vector<int>& v, int ValueToFind, int StartIndex, int EndIndex)
{
	if (EndIndex < StartIndex)
		return -1;

	int mid = (EndIndex + StartIndex) / 2;

	if (v[mid] == ValueToFind)
		return mid;

	if (v[mid] > ValueToFind)
		return FindBinarySearch(v, ValueToFind, StartIndex, mid - 1);

	//if (v[mid] < ValueToFind)
	return FindBinarySearch(v, ValueToFind, mid + 1, EndIndex);
}



void TestVectorSet(int sz, int ValueToFind, vector<long>& v1)
{
	// measure 
	auto start0 = chrono::system_clock::now();

	vector<int> largev;
	largev.reserve(sz);
	for (int i = 0; i < sz; i++)
	{
		largev.push_back(i);
	}

	auto end0 = chrono::system_clock::now();
	auto diff0 = end0 - start0;
	v1.push_back(diff0.count());

	// measure FindSimpleWithRangeForLoop(largev, ValueToFind);

	auto start1 = chrono::system_clock::now();
	FindSimpleWithRangeForLoop(largev, ValueToFind);
	auto end1 = chrono::system_clock::now();
	auto diff1 = end1 - start1;
	v1.push_back(diff1.count());

	// measure FindBinarySearch(largev, largev.size() - 1, 0, ValueToFind);

	auto start2 = chrono::system_clock::now();
	FindBinarySearch(largev, ValueToFind, 0, sz - 1);
	auto end2 = chrono::system_clock::now();
	auto diff2 = end2 - start2;
	v1.push_back(diff2.count());

	// measure 

	auto start3 = chrono::system_clock::now();

	set<int> IntSet;
	for (int i = 0; i < sz; i++)
	{
		IntSet.emplace(i);
	}

	auto end3 = chrono::system_clock::now();
	auto diff3 = end3 - start3;
	v1.push_back(diff3.count());

	// measure IntSet.find(ValueToFind);

	auto start4 = chrono::system_clock::now();
	IntSet.find(ValueToFind);
	auto end4 = chrono::system_clock::now();
	auto diff4 = end4 - start4;
	v1.push_back(diff4.count());


}

int main()					//it works in relase mod
{
	vector<vector<vector<long>>> v3;   // v3 keeps the all data for 5 different sizes' time values
	vector<vector<long>>v2;			   //v2 keeps the ten times values for 5 functions (v1) 
	vector<long>v1;					   //v1 keeps the time values for the 5 functions in each random experiment 

	srand((unsigned int)time(NULL));
	vector<int> vec = { 1000, 10000, 100000, 1000000, 10000000 };
	for (int x : vec)
	{
		for (int i = 0; i < 10; i++)
		{
			int random = rand() % x;
			TestVectorSet(x, random, v1);

			v2.push_back(v1);
			v1.clear();

		}
		v3.push_back(v2);
		v2.clear();

	}

	long double results[5][5];       // results[size][function type]

	for (int j = 0; j < 5; j++)
	{
		for (int k = 0; k < 5; k++)
		{
			long a = 0;
			for (int b = 0;b < 10;b++)
			{
				a = a + v3[j][b][k];
			}

			results[j][k] = a / 10;
		}
	}
	string functionNames[5] = { "Vector construct", "FindSimpleWithRangeForLoop","FindBinarySearch",  "Set construct", "Set find" };
	cout << "Function | 1000 | 10000 | 100000 | 1000000 | 10000000" << endl;
	cout << "--------|----|-----|------|-------|--------|" << endl;
	for (int i = 0; i < 5; i++) {
		cout << "|" << functionNames[i] << " ";

		for (int j = 0; j < 5; j++) {
			cout << results[j][i] << " | ";
		}
		cout << endl;
	}

	return 0;
}
