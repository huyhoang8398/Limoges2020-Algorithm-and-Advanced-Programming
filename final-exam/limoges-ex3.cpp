#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

typedef long long int64;
const int maxN = 10000002;
int N;
pair<int,int> df[maxN];
pair<int,int> selected[maxN];

bool earlyEndingFirst(pair<int, int> exam1, pair<int, int> exam2) {
    return exam1.second < exam2.second;
}

int main()
{
    ifstream fin("input3.txt");
    fin >> N;
    for (int i = 1; i <= N; i++) fin >> df[i].first >> df[i].second;
    fin.close();

    sort(df + 1, df + N + 1, earlyEndingFirst);
    int numberOfExam = 0, currentTime = 0;
    for (int i = 1; i <= N; i++) {
        if (currentTime > df[i].first) continue;
        numberOfExam++;
        selected[numberOfExam] = df[i];
        currentTime = df[i].second;
    }
    
    ofstream fo("output3.txt");    
    fo << numberOfExam << "\n";
    for (int i = 1; i <= numberOfExam; i++) fo << selected[i].first << " " << selected[i].second << "\n";
    fo.close();
    return 0;
}
