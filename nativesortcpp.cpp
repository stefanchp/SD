#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

void read(vector<long long> &arr, size_t &n, char *input_file)
{
	ifstream fin(input_file);
	fin >> n;
	arr.resize(n);
	for (size_t i = 0; i < n; ++i) 
		fin >> arr[i];
	fin.close();
	return;
}

void PrintArray(vector<long long> &arr, size_t &n, char *output_file)
{
	ofstream fout(output_file);
	for (size_t i = 0; i < n; ++i)
		fout << arr[i] << ' ';
	fout.close();
	return;
}

int main(int argc, char *argv[])	
{
	size_t n;
	std::vector<long long> arr;
	read(arr, n, argv[1]);
	try {
		sort(arr.begin(), arr.end());
	} 
	catch (const std::exception &e) {
		return -1;
	}
	//PrintArray(arr, n, argv[2]);
	return 0;
}