#include <iostream>
using namespace std;

void fileIOE()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}

int main()
{
    fileIOE();

    // CODE NOW:

    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }
    // for (int i=1; i<n; ++i)
    // {
    //     a[i] = a[i] + a[i-1];
    // }
    // for (int i=0; i<n; ++i)
    // {
    //     cout << a[i] << " ";
    // }
    // cout << endl;
    // int ans[n];
    // int sum = 0;
    // for (int i = 0; i < n; ++i)
    // {
    //     sum = sum + a[i];
    //     ans[i] = sum;
    // }
    // for (int i=0; i<n; ++i)
    // {
    //     cout << ans[i] << " ";
    // }
    cout << endl;

    return 0;
}