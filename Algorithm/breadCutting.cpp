#include<bits/stdc++.h>
using namespace std;

int const MAX = 100;
int length, n;
int a[MAX];
int table[MAX][MAX];

int BreadCut(int start, int finish)
{
    if(table[start][finish] != -1) return table[start][finish];

    bool ok = false;
    int cost = INT_MAX;
    for(int i = 1; i <= n; i++)
    {
        if(a[i] <= start || a[i] >= finish) continue;

        ok = true;

        cost = min(cost, finish - start + BreadCut(start, a[i]) + BreadCut(a[i], finish));
    }

    if(!ok) return 0;
    return cost;
}

int main()
{
    int length;
    cin >> length;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];

    memset(table, -1, sizeof table);

    cout <<"The minimum cost of cutting the bread is : " << BreadCut(0, length) << endl;

    return 0;
}
