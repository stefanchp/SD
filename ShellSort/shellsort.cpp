/* SHELL SORT
 * Time complexity: O(n^2)
 * Space complexity: O(1)
 * Stable: No
 * In-place: Yes
 *
 * Shell sort e un insertion sort imbunatait. Foarte pe scurt, spre deosebire de insertion sort, shell sort
 * compara elemente care sunt la o distanta [gap] una de cealalta, nu elemente consecutive. Dupa ce compara
 * elementele la distanta [gap], shell sort reduce [gap] si repeta procesul pana cand [gap] devine 1, caz in
 * care shell sort devine un insertion sort.
 *
 * Diversi matematicieni au incercat sa gaseasca o formula pentru [gap] care sa duca la un timp de executie
 * optim. In prezent, nu exista o formula care sa duca la un timp de executie optim in toate cazurile, dar
 * exista cateva formule care dau rezultate bune in majoritatea cazurilor.
 *
 * SHELL'S ORGINIAL SEQUENCE:   gap = n / (2^k).                                Worst case: O(n^2)
 * KNUTH'S SEQUENCE:            gap = (3^k - 1) / 2.                            Worst case: O(n^(3/2))
 * SEDGEWICK'S SEQUENCE:        gap = 4^k + 3 * 2^(k - 1) + 1.                  Worst case: O(n^(4/3)
 * CIURA'S SEQUENCE:            gap = 1, 4, 10, 23, 57, 132, 301, 701, 1750.    Worst case: O(n^(4/3)) (unknown)
 *      (nota: se opreste la 1750, dar vom folosi diversi multiplieri pentru a prelungi secventa,
 *       aici incepe alta discutie fara raspuns, dar niste numere populare sunt 2.25, 2.35, 2.20)
 *
 * Ne vom opri aici, pentru ca sunt secvente cate-n luna si in stele, dintre care unele mai complicate pe care nu am
 * chef sa le implementez.
 *
 *      0 / SH = SHELL'S ORGINIAL SEQUENCE
 *      1 / KN = KNUTH'S SEQUENCE
 *      2 / SW = SEDGEWICK'S SEQUENCE
 *    > 3 / CI220 = CIURA'S SEQUENCE (2.20 multiplier)
 *      5 / CI220O = CIURA'S SEQUENCE (2.20 multiplier, forced odd)
 *      6 / CI225 = CIURA'S SEQUENCE (2.25 multiplier)
 *      7 / CI225O = CIURA'S SEQUENCE (2.25 multiplier, forced odd)
 *      8 / CI235 = CIURA'S SEQUENCE (2.35 multiplier)
 * 	9 / CI235O = CIURA'S SEQUENCE (2.35 multiplier, forced odd)
 */

 #include <fstream>
 #include <vector>
 #include <algorithm>
 
 void GenerateGaps(const size_t &n, std::vector<long long> &gaps)
 {
     std::vector<long long> Ciura = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
 
     for (size_t i = 0; i < Ciura.size(); i++) {
         if (Ciura[i] < n) {
             gaps.push_back(Ciura[i]);
         }
     }
 
     long long gap = 2.20 * Ciura[Ciura.size() - 1];
     while (gap < n) {
         gaps.push_back(gap);
         gap = 2.20 * gap;
     }
 
     std::reverse(gaps.begin(), gaps.end());
 
     return;
 }
 
 void RunShellSort(std::vector<long long> &arr, const size_t &n)
 {
     std::vector<long long> gaps;
     GenerateGaps(n, gaps);
 
     size_t gaps_count = gaps.size();
 
     for (size_t i = 0; i < gaps_count; ++i) {
         long long gap = gaps[i];
         for (size_t j = gap; j < n; ++j) {
             long long temp = arr[j];
             long long k;
             for (k = j; k >= gap && arr[k - gap] > temp; k -= gap) {
                 arr[k] = arr[k - gap];
             }
             arr[k] = temp;
         }
     }
 
     return;
 }
 
 void ReadArray(std::vector<long long> &arr, size_t &n, char *input_file)
 {
     std::ifstream in(input_file);
 
     in >> n;
     arr.resize(n);
 
     for (size_t i = 0; i < n; ++i)
     {
         in >> arr[i];
     }
 
     in.close();
     return;
 }
 
 void PrintArray(std::vector<long long> &arr, size_t &n, char *output_file)
 {
     std::ofstream out(output_file);
 
     for (size_t i = 0; i < n; ++i)
     {
         out << arr[i] << ' ';
     }
 
     out.close();
     return;
 }
 
 int main(int argc, char *argv[])
 {
     if (argc < 3)
     {
         return 1;
     }
 
     size_t n;
     std::vector<long long> array;
 
     ReadArray(array, n, argv[1]);
 
     try {
         RunShellSort(array, n);
     } catch (const std::exception &e) {
         return -1;
     }
 
     //PrintArray(array, n, argv[2]);
 
     return 0;
 }