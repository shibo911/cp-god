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

    // int a = 7;
    // long long b = 15;
    // float f = 3.14;
    // double d = 3.14144151;
    // char c = 'c';
    // bool flag = false;
    // cin >> b;
    // cout << b << endl;

    // cout << a + 5;

    // int a;
    // cin >> a;
    // int area;
    // area = a*a;
    // cout << area << '\n';

    // cout << 'y' << "e" << 's' << endl;
    // CHECK IF THE GIVEN NUMBNER IS ODD OR EVEN , IF ITS EVEN THEN
    // PRINT TWICE THAT NUMBER OTHERWISE PRINT "shivang sir : )"
    int a;
    cin >> a;
    if (a % 2 == 0)
    {
        cout << a * 2;
    }

    else
    {
        cout << "Shivang Sir";
    }

    return 0;
}