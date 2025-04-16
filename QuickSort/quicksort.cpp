#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
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

long long partition(vector<long long>& arr, long long low, long long high) 
{
    long long pivot = arr[low];
    long long i = low;
    long long j = high - 1;
    long long pasi = 0, pasj = 1;
    while (i < j) 
    {
        if (arr[i] > arr[j])
        {
            swap(arr[i], arr[j]);
            swap(pasi, pasj);
        }
        i += pasi;
        j -= pasj;
    }
    return i;
}

void quickSort(vector<long long>& arr, long long low, long long high) 
{
    if (low < high) 
    {
        long long pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
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
    quickSort(array, 0, n - 1);
    //printArray(array);
    return 0;
}
