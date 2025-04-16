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
}

long long getMax(const vector<long long>& arr) 
{
    long long mx = arr[0];
    for (size_t i = 1; i < arr.size(); i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void countingSort(vector<long long>& arr, long long exp) 
{
    size_t n = arr.size();
    vector<long long> output(n);
    int count[65536] = {0};  // Baza 65536
    for (size_t i = 0; i < n; i++)
        count[(arr[i] / exp) % 65536]++;
    for (long long i = 1; i < 65536; i++)
        count[i] += count[i - 1];

    for (long long i = n - 1; i >= 0; i--) 
    {
        output[count[(arr[i] / exp) % 65536] - 1] = arr[i];
        count[(arr[i] / exp) % 65536]--;
    }
    for (size_t i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(vector<long long>& arr) 
{
    if (arr.empty()) 
        return;
    long long m = getMax(arr);
    for (long long exp = 1; m / exp > 0; exp *= 65536)
        countingSort(arr, exp);
}

void radixSortWithNegatives(vector<long long>& arr) 
{
    vector<long long> pos, neg;
    for (long long x : arr) 
        if (x < 0)
            neg.push_back(-x);  // Transformăm în pozitiv
        else
            pos.push_back(x);
    
    radixSort(pos);
    radixSort(neg);
    reverse(neg.begin(), neg.end());
    for (long long& x : neg)
        x = -x;

    arr.clear();
    arr.insert(arr.end(), neg.begin(), neg.end());
    arr.insert(arr.end(), pos.begin(), pos.end());
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
    radixSortWithNegatives(array);
    //printArray(array);
    return 0;
}
