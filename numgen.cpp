// arg[1] = number of numbers to generate  		type: size_t         
// arg[2] = real numbers? 0 = lls, 1 = doubles  	type: bool
// arg[3] = lower bound of numbers to generate  	type: double
// arg[4] = upper bound of numbers to generate  	type: double
// arg[5] = type of distribution to generate		type: *char
// 		0 = uniform = uni
// 		1 = normal = gss
//		2 = exponential = exp
// 		3 = sorted = srt
// 		4 = reverse sorted = rev
// 		5 = almost sorted = alm
// arg[6] = output file name				type: string
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>

using namespace std;

void gen_uniform(const size_t n, const bool real, const double lower, const double upper, ofstream &fout)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<long long> dis(lower, upper);
	for (size_t i = 0; i < n; ++i) 
		fout << dis(gen) << ' ';

	return;
}

void gen_normal(const size_t n, const bool real, const double lower, const double upper, ofstream &fout)
{
	// Generated nums should generate a bell curve around the center of the range, but never exceed it
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<long long> dis(lower, upper);
	normal_distribution<double> dis2((lower + upper) / 2, (upper - lower) / 6);
	for (size_t i = 0; i < n; ++i) 
	{
		long long num = dis2(gen);
		while (num < lower || num > upper)
			num = dis2(gen);
		fout << num << ' ';
	}
}

void gen_exponential(const size_t n, const bool real, const double lower, const double upper, ofstream &fout)
{
	random_device rd;
	mt19937 gen(rd());
	exponential_distribution<double> dis(0.0005);
	for (size_t i = 0; i < n; ++i) 
	{
		long long num = dis(gen);
		while (num < lower || num > upper) 
			num = dis(gen);
		fout << num << ' ';
	}
	return;
}

void gen_sorted(const size_t n, const bool real, const double lower, const double upper, ofstream &fout)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<long long> dis(lower, upper);
	vector<long long> nums;
	for (size_t i = 0; i < n; ++i)
		nums.push_back(dis(gen));
	sort(nums.begin(), nums.end());
	for (size_t i = 0; i < n; ++i)
		fout << nums[i] << ' ';

	return;
}

void gen_rev_sorted(const size_t n, const bool real, const double lower, const double upper, ofstream &fout)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<long long> dis(lower, upper);
	vector<long long> nums;
	for (size_t i = 0; i < n; ++i)
		nums.push_back(dis(gen));
	sort(nums.begin(), nums.end(), greater<long long>());
	for (size_t i = 0; i < n; ++i) 
		fout << nums[i] << ' ';
	return;
}

void gen_alm_sorted(const size_t n, const bool real, const double lower, const double upper, ofstream &fout)
{
	random_device rd;
	mt19937 gen(rd());

	uniform_int_distribution<long long> dis(lower, upper);
	vector<long long> nums;
	for (size_t i = 0; i < n; ++i) 
		nums.push_back(dis(gen));

	sort(nums.begin(), nums.end());
	uniform_int_distribution<size_t> dis2(0, n / 4);
	size_t swaps = dis2(gen);
	for (size_t i = 0; i < swaps; ++i) 
	{
		uniform_int_distribution<size_t> dis3(0, n - 1);
		size_t idx1 = dis3(gen);
		size_t idx2 = dis3(gen);
		swap(nums[idx1], nums[idx2]);
	}
	for (size_t i = 0; i < n; ++i)
		fout << nums[i] << ' ';
	return;
}

int main(int argc, char *argv[])
{
	if (argc < 7)
		return 1;

	size_t n = stoull(argv[1]);
	bool real = stoi(argv[2]);
	double lower = stod(argv[3]);
	double upper = stod(argv[4]);
	string dist = argv[5];
	string output_file = argv[6];

	ofstream fout(output_file);
	fout << n << ' ';
	if (dist == "uni")
		gen_uniform(n, real, lower, upper, fout);
	else if (dist == "gss") 
		gen_normal(n, real, lower, upper, fout);
	else if (dist == "exp") 
		gen_exponential(n, real, lower, upper, fout);
	else if (dist == "srt") 
		gen_sorted(n, real, lower, upper, fout);
	else if (dist == "rev") 
		gen_rev_sorted(n, real, lower, upper, fout);
	else if (dist == "alm") 
		gen_alm_sorted(n, real, lower, upper, fout);
	else 
		return 1;

	fout.close();
	return 0;
}