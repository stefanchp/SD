#include <iostream>
#include <fstream>
#include <vector>
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

void heap(vector<long long>& v, long long n, long long i)
{
    long long Max = i;
    long long st = 2 * i + 1;
    long long dr = 2 * i + 2;
    if(st < n && v[st] > v[Max])
        Max = st;

    if(dr < n && v[dr] > v[Max])
        Max = dr;

    if(Max != i)
    {
        swap(v[i], v[Max]);
        heap(v, n, Max);
    }
}

void heapSort(vector<long long>& v, long long n)
{
    for(long long i = n / 2 - 1; i >= 0; i--)
        heap(v, n, i);

    for(long long i = n - 1; i >= 0; i--)
    {
        swap(v[0], v[i]);
        heap(v, i, 0);
    }
}

void printArray(const vector<long long>& arr) 
{
    for (long long x : arr)
        cout << x << " ";
    cout << '\n';
}

int main(int argc, char *argv[])
{
    size_t n;
	vector<long long> array;
    read(array, n, argv[1]);
    heapSort(array, n);
    //printArray(array);
    return 0;
}