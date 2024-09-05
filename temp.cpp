#include <bits/stdc++.h>
using namespace std;

int main()
{
	unordered_set<int> s;
	s.insert(2);
	s.insert(5);
	s.insert(7);
	s.erase(2);
	s.insert(2);
	for (auto i : s)
	{
		cout << i << " ";
	}
}