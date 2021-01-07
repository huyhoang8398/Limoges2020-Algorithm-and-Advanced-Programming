#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

typedef long long int64;
const int maxN = 10000002;
int N;
pair<int64,int> time[maxN];
int64 bestTimeExhaustive, bestTimeGreedy;
int bestOrderExhaustive[maxN], bestOrderGreedy[maxN];

void exhaustiveSearch()
{    
    bestTimeExhaustive = LLONG_MAX;
    sort(time + 1, time + N + 1);
    do {
        int64 waitTime = 0;
        for (int i = 1; i <= N; i++) waitTime += (N - i + 1) * time[i].first;
        if (waitTime < bestTimeExhaustive) {
            bestTimeExhaustive = waitTime;
            for (int i = 1; i <= N; i++) bestOrderExhaustive[i] = time[i].second;
        }
    } while (next_permutation(time + 1, time + N + 1));
}

void greedySearch()
{
    bestTimeGreedy = 0;
    sort(time + 1, time + N + 1);
    for (int i = 1; i <= N; i++) {
        bestTimeGreedy += (N - i + 1) * time[i].first;
        bestOrderGreedy[i] = time[i].second;
    }
}

int main()
{
    ifstream fin("input2.txt");
    fin >> N;
    for (int i = 1; i <= N; i++) {
        fin >> time[i].first;
        time[i].second = i;
    }
    fin.close();
    
    exhaustiveSearch();
    greedySearch();
    
    
    ofstream fo("output2.txt");
    fo << "Exhaustive time  = " << bestTimeExhaustive << "\n";
    fo << "Exhaustive order = ";
    for (int i = 1; i <= N; i++) fo << bestOrderExhaustive[i] << " "; 
    fo << "\n\n-------\n\n";

    fo << "Greedy time  = " << bestTimeGreedy << "\n";
    fo << "Greedy order = ";
    for (int i = 1; i <= N; i++) fo << bestOrderGreedy[i] << " ";
    
    fo.close();
    return 0;
}
