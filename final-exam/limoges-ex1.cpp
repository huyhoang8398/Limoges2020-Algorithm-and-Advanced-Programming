#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<double, int> DoubleIntPair;

const int maxN = 102;
int N;
bool siteBuilded[maxN]; // siteBuilded[i] = true if the i-th site has been used
double cost[maxN][maxN]; // cost to build base i at site j
vector<DoubleIntPair> sortedCost[maxN]; // contains sorted cost of base i. sortedCost[i][j].first is the cost to build base i at site sortedCost[i][j].second
double currentCost, bestCost;
int currentMatch[maxN], bestMatch[maxN];

void dfs(int baseId)
{
    if (baseId == N+1) {
        if (currentCost < bestCost) {
            bestCost = currentCost;
            for (int i = 1; i <= N; i++) bestMatch[i] = currentMatch[i];
        }
        return;
    }

    for (int siteId = 1; siteId <= N; siteId++) if (!siteBuilded[siteId])
    {
        currentMatch[baseId] = siteId;
        currentCost += cost[baseId][siteId];        
        siteBuilded[siteId] = true;
        if (currentCost < bestCost) dfs(baseId + 1); // branch and bound
        currentCost -= cost[baseId][siteId];
        siteBuilded[siteId] = false;
    }
}

void bestFirstSearch(int baseId)
{
    if (baseId == N+1) {
        if (currentCost < bestCost) {
            bestCost = currentCost;
            for (int i = 1; i <= N; i++) bestMatch[i] = currentMatch[i];
        }
        return;
    }

    // vector goes from 0->N
    for (int i = 0; i < N; i++) 
    {
        int siteId = sortedCost[baseId][i].second;
        if (siteBuilded[siteId]) continue;

        currentMatch[baseId] = siteId;
        currentCost += sortedCost[baseId][i].first; // cost[baseId][siteId];
        siteBuilded[siteId] = true;
        if (currentCost < bestCost) bestFirstSearch(baseId + 1); // branch and bound
        currentCost -= sortedCost[baseId][i].first;
        siteBuilded[siteId] = false;
    }
}

int main()
{
    ifstream fin("input1.txt");
    fin >> N;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            fin >> cost[i][j];
    fin.close();
        
    ofstream fo("output1.txt");

    currentCost = 0;
    bestCost = 1000000000; // big number, infinity
    for (int i = 1; i <= N; i++) siteBuilded[i] = false;
    dfs(1);

    fo << "Depth-first-search\n";
    fo << "Min cost = " << bestCost << "\n";
    fo << "Matching: ";
    for (int i = 1; i <= N; i++) fo << bestMatch[i] << " ";
    fo << "\n\n--------\n\n";

    //*******************//

    currentCost = 0;
    bestCost = 1000000000; // big number, infinity
    for (int i = 1; i <= N; i++) siteBuilded[i] = false;
    for (int i = 1; i <= N; i++) {
        sortedCost[i].clear();        
        for (int j = 1; j <= N; j++) sortedCost[i].push_back(DoubleIntPair(cost[i][j], j));
        sort(sortedCost[i].begin(), sortedCost[i].end());
    }
    bestFirstSearch(1);

    fo << "Best-first-search\n";
    fo << "Min cost = " << bestCost << "\n";
    fo << "Matching: ";
    for (int i = 1; i <= N; i++) fo << bestMatch[i] << " ";
    fo << "\n";

    fo.close();
    return 0;
}
