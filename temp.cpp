#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 3e5 + 5;
const int MAXA = 1e6 + 5;

int n, m;
vector<int> a(MAXN);
vector<long long> sumTree(4 * MAXN);
vector<int> maxTree(4 * MAXN);
vector<int> divisorCount(MAXA);

void precompute_divisor_counts()
{
    for (int i = 1; i < MAXA; i++)
    {
        for (int j = i; j < MAXA; j += i)
        {
            divisorCount[j]++;
        }
    }
}

void build(int node, int start, int end)
{
    if (start == end)
    {
        sumTree[node] = a[start];
        maxTree[node] = a[start];
    }
    else
    {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        sumTree[node] = sumTree[2 * node] + sumTree[2 * node + 1];
        maxTree[node] = max(maxTree[2 * node], maxTree[2 * node + 1]);
    }
}

void update(int node, int start, int end, int l, int r)
{
    if (maxTree[node] <= 2)
        return;
    if (start == end)
    {
        a[start] = divisorCount[a[start]];
        sumTree[node] = a[start];
        maxTree[node] = a[start];
    }
    else
    {
        int mid = (start + end) / 2;
        if (l <= mid)
            update(2 * node, start, mid, l, r);
        if (r > mid)
            update(2 * node + 1, mid + 1, end, l, r);
        sumTree[node] = sumTree[2 * node] + sumTree[2 * node + 1];
        maxTree[node] = max(maxTree[2 * node], maxTree[2 * node + 1]);
    }
}

long long query_sum(int node, int start, int end, int l, int r)
{
    if (r < start || end < l)
        return 0;
    if (l <= start && end <= r)
        return sumTree[node];
    int mid = (start + end) / 2;
    return query_sum(2 * node, start, mid, l, r) + query_sum(2 * node + 1, mid + 1, end, l, r);
}

void process_queries()
{
    int t, l, r;
    for (int i = 0; i < m; i++)
    {
        cin >> t >> l >> r;
        l--;
        r--;
        if (t == 1)
        {
            update(1, 0, n - 1, l, r);
        }
        else
        {
            cout << query_sum(1, 0, n - 1, l, r) << endl;
        }
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    precompute_divisor_counts();
    build(1, 0, n - 1);
    process_queries();
    return 0;
}
