---
title: "Algorithm and Advanced Programming Final Report"
author: \textbf{DO Duy Huy Hoang} \newline
        \newline
        \newline
        \textit{University of Limoges} \newline 
date: \today
titlepage: false
header-includes: |
    \usepackage{multicol}
    \usepackage{graphicx}
footer-left: DO Duy Huy Hoang
mainfont: NewComputerModern
sansfont: NewComputerModern
monofont: Dank Mono
caption-justification: centering
...
\pagenumbering{Roman} 

\newpage{}

\listoffigures
\newpage{}
\tableofcontents
\newpage{}

\pagenumbering{arabic} 

# I. Exercise 1

## 1. Problem modelling:

- Input: 
  - Integer N, number of bases/sites
  - `cost[][]`: 2D array size `NxN`, where `cost[i][j]` is the cost to build base `i` on at site `j`. 
- Output (Form of solution)
  - Integer minCost: the minimum energy needed to build N bases
  - N integers: `matching[i]` = the site where base `i` is built on
- Constraint:
  - Since this is intended to be a recursive research problem with worst-case complexity O(N!), N must be small. Such as `N <= 30`
  - `cost[][]` can be float or integers. In my code, I use double.
- Optimality:
  - This problem can be solved using exhaustive search with complexity O(N!). But in practice, it is much faster than O(N!) because we use branch and bound.

## 2. Branch and bound strategy:

- During recursive search, if the current cost is already larger than the best cost that we found, we can stop searching deeper.

```c++
currentMatch[baseId] = siteId;
currentCost += sortedCost[baseId][i].first; // cost[baseId][siteId];
siteBuilded[siteId] = true;
if (currentCost < bestCost) bestFirstSearch(baseId + 1); // branch and bound
currentCost -= sortedCost[baseId][i].first;
siteBuilded[siteId] = false;
```

## 3. Implementing depth-first-search and best-first-search:

- Both methods have been implemented in my code.
- For best-first-search, before the actual exhaustive search, we create an array `sortedCost[][]` where `sortedCost[i][j]` is an array of `pair<double,int>`. `sortedCost[i][j].first` is the cost to build base i at site `sortedCost[i][j].second`
- By doing the above step, finding the next best-node during the recursive search is trivial, we just need to loop over `sortedCost[][]`.

- The solution my code produced is:

  - Min cost = 9
  - Best matching = base1-site3, base2-site1, base3-site2

# Exercise 2.
## 1. Problem modelling:
- Input: 
  - Integer N, number of clients
  - time[]: time to serve client i
- Output (Form of solution)
  - Integer minTime: the minimum total waiting time to serve all customers
  - N integers: the order of customer serving
- Constraint:
  - time[] is an array of integers
- Optimality:
  - This problem can be solved using exhaustive search with complexity O(N! * N). But the optimal method is using greedy algorithm with complexity O(N * log(N)) due to sorting.

## 2. Optimal solution for example: 
- Min total time: 40 seconds
- Order of serving: 2 -> 4 -> 1 -> 3
- I implemented both the exhaustive search and the greedy algorithm in my program

## 3. Optimal greedy algorithm:
- If T[] contains the serving time of each customer, and the serving order must be T[1] -> T[2] -> T[3], then the total waiting time can be computed using the following formula:
```c++
waitTime = 0;
for (i=1; i<=N; i++) waitTime += (N - i + 1) * T[i]
```
Explanation: for the first customer, (N - 1 + 1) people have to wait T[1] seconds for him to finish (including himself). For the second, (N - 2 + 1) people have to wait T[2] seconds, … and so on.

Optimal greedy strategy: set T[] = sorted(time[]), meaning we serve customers in order of increasing serving time (customers who require less time to serve is served first).

Proof: Given any array T[], assume we have i, j such that i < j and T[i] != T[j]. Assuming all other positions k are fixed. We easily see that in this situation, the total waiting time caused by the k-th person is constant.  So, we only need to compare the waiting time caused by person i and j

- W = T[i] * (N - i + 1) + T[j] * (N - j + 1)
We know that (N - i + 1) > (N - j + 1), since i < j.

- Trivially, we see that to minimize W, we must ensure T[i] < T[j]. Basically, that means swapping T[i] and T[j] if T[i] > T[j]. Naturally, this means sorting array T[], which means sorting the array time[]

=> The optimal solution is to serve the customers with lower time cost first.
