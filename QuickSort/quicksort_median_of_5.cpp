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

int medianOfFive(vector<long long>& arr, int low, int high) 
{
    int size = high - low + 1;
    if (size < 5) return low + size / 2;
    int step = size / 4;
    vector<int> indices = {low, low + step, low + 2 * step, low + 3 * step, high};
    vector<pair<long long, int>> values;
    for (int i : indices)
        values.push_back({arr[i], i});
    sort(values.begin(), values.end());
    return values[2].second;
}


long long partition(vector<long long>& arr, long long low, long long high) 
{
    long long pivot = medianOfFive(arr, low, high);
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
