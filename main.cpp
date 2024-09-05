#include <iostream>
#include <stdio.h>
#include <vector>
#include <array>
#include <string>
#include <set>
#include <algorithm>
#include <utility>
#include <functional>
#include <fstream>
#include <istream>
#include <climits>
#include <map>
#include <list>
#include <cmath>
#include <deque>
#include <numeric>
#include <unordered_set>
#include <bitset>
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <queue>
#include <stack>
#include <tuple>
#include <random>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define endl '\n' // comment for interactive problems
#define shibo                     \
	ios_base::sync_with_stdio(0); \
	cin.tie(0);                   \
	cout.tie(0);
using ll = long long int;
#ifndef ONLINE_JUDGE
#include "template.cpp"
#else
#define debug(...) 911
#endif
using namespace std::chrono;
using namespace std;
using namespace __gnu_pbds;
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> pbds; // find_by_order, order_of_key, less<ll> is comparator
auto start = high_resolution_clock::now();

// cf 970 div 3
// cc 150

ll mod = 998244353;
ll MAXN = 1e1 + 1;
ll facN = 1e1 + 1;
vector<ll> sieveerato(MAXN, 1);
vector<ll> spf(MAXN, 1);
vector<ll> primes;
vector<ll> f(facN), inv(facN), finv(facN);
const ll inf = LLONG_MAX - 1;

// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣤⣤⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⣿⣿⣿⣿⣶⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⠟⢿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠋⠀⠀⠀⠹⣿⣾⣿⣿⡿⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣤⡟⠀⠀⣠⣄⡀⠀⢙⠿⠿⠟⠁⠀⢧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⠟⢙⣧⠀⠀⠻⣿⣿⣷⣦⣆⠄⣀⣠⣶⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣤⣾⣿⠀⠀⠀⡆⣿⣿⡿⠛⠙⣿⣿⠋⢹⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡟⢸⣿⣿⣇⠀⠀⠉⠛⢣⠄⠀⠀⠈⡟⠈⠁⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡽⢾⣿⣿⣿⣶⣾⣿⣿⣿⣿⣷⣶⣶⣤⣤⣴⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡴⠊⠉⠀⣼⣿⣿⣿⣿⠿⠋⠉⠙⠛⠛⠻⠿⠿⣿⣿⡷⠦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠞⠉⠀⠀⠀⠀⢸⣿⣿⣿⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⡇⠀⠀⠉⠳⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡞⠁⠀⠀⠀⠀⠀⠀⠈⢻⣿⣿⣿⣿⣦⣤⣀⣀⠀⠀⣀⣼⣿⣿⠁⠀⠀⠀⠀⠈⠳⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⠀⠀⠀⠀⠀⠀⠀⠹⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠻⠿⠿⣿⣿⣿⣿⡿⠿⠿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣧⠀⠀⠀⠀⠀⢀⣳⣄⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡼⠁⠀⠀⠀⠀⠀⠀⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠀⠀⠀⠀⠀⠀⠀⢠⡏⠀⠀⣠⠖⠋⠁⣀⡀⠙⠳⣄⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠃⠀⠀⠀⠀⠀⠀⠀⠈⢳⣄⣀⠀⠀⠀⠀⠀⠀⠀⢀⣠⠟⠀⠀⠀⠀⠀⢀⣠⡾⣀⡀⣰⢁⡤⠞⠋⠁⠈⠙⢦⠈⢳⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡏⠀⠀⠀⠀⠀⠀⠀⠀⢠⣾⣁⣉⣉⣓⠶⠶⠶⠶⠿⠿⠷⠖⠚⠛⠒⠒⠒⠛⠓⢷⣀⡽⠿⠋⢉⡉⠉⠲⡆⠀⠀⢧⠀⣧⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡾⠧⠤⣤⣄⡀⠀⠀⠀⣠⠏⢾⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⠞⠉⣀⣴⣾⠋⠙⠛⠒⠃⠀⠀⢸⠀⡿⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⠏⠀⠀⠀⠀⠀⠉⠳⢄⣠⣧⣄⣸⣀⣀⣀⣀⣀⣀⣀⣀⣤⣤⣤⣤⣤⡤⠤⣤⠖⠋⢀⡴⠺⣅⣤⢯⠳⣤⣀⢀⡀⠀⠀⣿⣸⠇⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣧⣀⣀⡀⠀⠀⠀⠀⠀⢿⡀⢀⡟⠉⠉⣉⣩⣿⠉⠉⠁⠀⠀⠀⠀⠀⣠⠞⠁⣠⠖⠉⠀⠀⢿⢷⠈⠳⣄⣉⠉⠀⢠⣼⠟⠁⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡏⠉⠉⠉⠑⠒⢶⠴⠏⠹⣏⣠⡶⠋⠁⠀⠙⢦⠀⠀⠀⠀⠀⢠⡞⠁⣠⠞⠁⠀⠀⠀⣀⣾⡈⡷⢤⣈⣩⠴⠞⡉⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠲⣄⠘⡄⠀⣼⣿⠟⠁⠀⠀⠀⠀⠈⢳⣤⠤⠤⢴⠏⠀⣴⣥⣤⣤⠤⠴⠺⠯⣄⣿⠃⠀⣿⢁⡤⠚⣿⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⣀⡀⠀⠈⢣⣧⢞⡾⠃⠀⠀⠀⠀⠀⢀⣠⠞⠁⠀⢠⡏⠀⣼⠁⠀⠀⠀⠀⠀⢀⣤⣀⠈⢳⡤⠟⠃⠀⢠⡇⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⠀⠀⠀⠀⠸⡇⡹⠋⠙⠲⢦⣤⣿⠟⠀⠀⠀⠀⣀⣠⠖⠋⠀⠀⢰⣖⡛⠲⠶⠧⣀⣀⣠⠀⠀⠉⠉⠉⠉⠑⠚⠦⡠⡄⢀⡜⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⣠⣴⠏⠱⡌⠉⠉⠉⠑⠒⢲⣿⠁⠀⠀⢠⣾⣿⠉⠀⣀⣀⡐⡟⠉⠀⠀⠀⠀⠀⠘⣇⠹⣆⡀⠀⠀⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣎⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⣠⣾⠟⠁⠀⠀⠙⢆⠀⠀⠀⣴⡿⢻⡇⠀⡴⠋⣿⡟⠉⠉⠉⠀⠉⢻⡄⠀⠀⠀⠀⠀⠀⢸⡷⣄⡉⠳⣄⡅⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀
// ⢀⡴⠋⠀⠀⠀⠀⠀⠀⠈⢳⣠⢿⢥⡿⣾⣿⡞⠁⠀⣿⢿⠉⣽⠙⡟⣢⢤⣷⠀⠀⠀⠀⠀⠀⢸⡇⠀⡝⠳⣼⣞⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢧⠀⠀⠀⠀⠀⠀⠀⠀
// ⢺⠉⣠⣭⡉⠁⠐⢩⡤⡴⠚⠁⢿⣠⡷⠋⢹⠀⠀⠀⠘⡾⠵⣿⣤⠧⠼⣿⠋⠀⠀⠀⠀⠀⡀⢸⡇⠀⡇⠀⠁⠈⣩⣓⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢼⡄⠀⠀⠀⠀⠀⠀⠀
// ⢸⣇⢿⣤⡟⠀⠀⢸⣧⠟⠀⢀⣤⠋⠀⠀⢸⡆⠀⠀⠀⣷⠀⠈⠉⠉⠉⠁⠀⠀⠀⠀⠀⠀⠹⡾⡇⢰⡇⠀⠀⠢⡙⣾⣛⣻⠿⠆⠀⠀⠀⠀⠀⠀⠀⢸⡼⣦⠀⠀⠀⠀⠀⠀
// ⠀⠙⡏⠉⠉⠉⠉⠉⠉⠉⠉⠉⣧⠀⠀⠀⠀⢣⡀⠀⠀⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⡇⢸⡇⠀⢧⠀⠉⠓⠀⠀⠀⠀⠳⣄⠀⠀⢀⣀⣀⣀⢱⣌⣦⠀⠀⠀⠀⠀
// ⠀⠀⢻⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⡀⠀⠀⢀⠞⣇⠀⠀⣇⠀⠀⠀⢸⡄⠀⠀⠀⣄⠀⠀⠀⠀⠘⡇⠈⣷⠀⠈⠳⠤⠤⢴⣾⠁⠀⠀⠈⣰⢯⡿⠛⠋⠏⠉⢉⢯⣆⠀⠀⠀⡔
// ⠀⠀⠈⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⣧⠀⡴⢿⡏⣹⡄⠀⣿⠀⠀⠀⠀⣹⣄⠀⠀⠙⣆⠀⠀⠀⠀⣇⠀⢸⢧⡀⠀⠀⢀⡼⠹⣆⣀⠀⡾⠁⢠⣴⣶⡆⠀⣾⣿⣟⣿⡀⠀⣸⠃
// ⠀⠀⠀⣽⡀⣀⣀⠀⣀⣀⣀⣀⣀⣹⠞⣴⢺⣽⡟⠀⠀⣿⠀⠀⠀⢸⠁⠈⠙⠒⠶⣿⠀⠀⠀⠀⢸⠀⠘⡄⠙⠦⣄⢸⠃⠀⠹⣏⢧⣷⠀⠸⣿⣿⠇⠘⠿⢟⡾⠘⢿⣶⠃⠀
// ⠀⠀⠀⢷⢀⡖⠓⡄⠀⠀⣴⠲⡄⠀⠀⣹⣿⡟⠀⠀⠀⣿⢦⣄⣀⢸⡄⠀⠀⠀⠀⠸⡄⠀⠀⢀⣾⡆⠀⣷⠀⠀⠈⠻⣇⠀⠀⢸⡇⠙⢢⣄⡉⣉⣀⣤⢴⡿⠤⠤⠚⠃⠀⠀
// ⠀⠀⠀⠈⢷⣿⣿⣥⣤⡤⣽⣾⠥⢤⣴⡿⠋⠀⠀⠀⢠⠇⠀⢀⠃⠙⣧⠀⠀⠀⠀⠀⣇⠀⠀⠀⣏⢧⠀⠈⢦⣠⠴⠋⠘⢿⣶⣋⣀⡤⣞⡭⡽⠿⠭⠟⠉⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠀⠀⠀⠀⠀⢾⣀⣀⡼⠤⠴⠟⠀⠀⠀⠀⠀⣿⠦⣄⣀⣿⠈⢧⡀⠀⠀⠀⢀⡴⠋⠀⢹⡈⠉⠉⢰⣽⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⡇⠀⠀⡇⠸⡇⠀⠙⠲⠔⠚⠁⠀⠀⠀⠀⠙⠓⠚⠛⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢧⣤⡼⠷⠤⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀

void sievespf()
{
	MAXN = 1e5;
	spf.resize(MAXN, 1);
	spf[0] = 0;
	for (ll i = 2; i <= MAXN - 1; i++)
	{
		if (spf[i] == 1)
		{
			for (ll j = i; j <= MAXN - 1; j += i)
			{
				if (spf[j] == 1)
					spf[j] = i;
			}
		}
	}
}

vector<ll> getFactorization(ll x)
{
	vector<ll> ret;
	while (x != 1)
	{
		ret.push_back(spf[x]);
		x = x / spf[x];
	}
	return ret;
}

void sieve()
{
	MAXN = 5e7;
	sieveerato.resize(MAXN, 1);
	sieveerato[0] = 0;
	sieveerato[1] = 0;
	for (ll i = 2; i * i <= MAXN - 1; ++i)
	{
		if (sieveerato[i])
		{
			for (ll j = i * i; j <= MAXN - 1; j += i)
			{
				sieveerato[j] = 0;
			}
		}
	}
}

void prime()
{
	sieve();
	for (ll i = 0; i <= MAXN - 1; ++i)
	{
		if (sieveerato[i])
		{
			primes.push_back(i);
		}
	}
	sort(primes.begin(), primes.end());
}

bool isPrime(ll n)
{
	if (sieveerato[n] == 1)
	{
		return true;
	}
	return false;
}

ll power(ll x, ll y)
{
	ll res = 1;
	while (y)
	{
		if (y % 2)
		{
			res = res * x;
			--y;
		}
		else
		{
			x = x * x;
			y /= 2;
		}
	}
	return res;
}

ll powermod(ll x, ll y, ll m)
{
	ll res = 1;
	x = x % m;
	while (y)
	{
		if (y % 2 == 1)
		{
			res = (res * x) % m;
		}
		y = y >> 1;
		x = (x * x) % m;
	}
	return res;
}

vector<vector<ll>> matrixMultiply(vector<vector<ll>> a, vector<vector<ll>> b)
{
	vector<vector<ll>> res(a.size(), vector<ll>(b[0].size()));
	for (ll i = 0; i < a.size(); ++i)
	{
		for (ll j = 0; j < b[0].size(); ++j)
		{
			res[i][j] = 0;
			for (ll k = 0; k < a[0].size(); ++k)
			{
				res[i][j] = (res[i][j] + (a[i][k] * b[k][j]) % mod) % mod;
			}
		}
	}
	return res;
}

vector<vector<ll>> matrixPower(vector<vector<ll>> matrix, ll n)
{
	vector<vector<ll>> res(matrix.size(), vector<ll>(matrix.size()));
	for (ll i = 0; i < matrix.size(); ++i)
	{
		for (ll j = 0; j < matrix.size(); ++j)
		{
			if (i == j)
			{
				res[i][j] = 1;
			}
			else
			{
				res[i][j] = 0;
			}
		}
	}
	while (n)
	{
		if (n % 2)
		{
			res = matrixMultiply(res, matrix);
			--n;
		}
		else
		{
			matrix = matrixMultiply(matrix, matrix);
			n = n / 2;
		}
	}
	return res;
}

ll check_kth_bit(ll x, ll k)
{
	return (x >> k) & 1;
}

void print_on_bits(ll x)
{
	for (ll k = 0; k < 32; k++)
	{
		if (check_kth_bit(x, k))
		{
			cout << k << ' ';
		}
	}
	cout << '\n';
}

ll count_on_bits(ll x)
{
	ll ans = 0;
	for (ll k = 0; k < 64; k++)
	{
		if (check_kth_bit(x, k))
		{
			ans++;
		}
	}
	return ans;
}

ll set_kth_bit(ll x, ll k)
{
	return x | (1LL << k);
}

ll unset_kth_bit(ll x, ll k)
{
	return x & (~(1LL << k));
}

ll toggle_kth_bit(ll x, ll k)
{
	return x ^ (1LL << k);
}

bool check_power_of_2(ll x)
{
	return count_on_bits(x) == 1;
}

ll count_bits(ll n)
{
	ll c = 0;
	while (n)
	{
		c++;
		n /= 2;
	}
	return c;
}

vector<ll> get_divisors(ll n)
{
	vector<ll> divs;
	for (ll i = 2; 1LL * i * i <= n; i++)
	{
		if (n % i == 0)
		{
			divs.push_back(i);
			if (i != n / i)
			{
				divs.push_back(n / i);
			}
		}
	}
	sort(divs.begin(), divs.end());
	return divs;
}

vector<ll> getLPS(string &s)
{
	ll n = s.size();
	vector<ll> lps(n, 0);
	ll i = 1, j = 0;
	while (i < n)
	{
		while (j && s[i] != s[j])
		{
			j = lps[j - 1];
		}
		if (s[i] == s[j])
		{
			j++;
		}
		lps[i] = j;
		i++;
	}
	return lps;
}

vector<ll> zMatch(string &s)
{
	vector<ll> z(s.size(), 0);
	ll l = 0, r = 0;
	for (ll i = 1; i < s.size(); i++)
	{
		if (i < r)
		{
			z[i] = z[i - l];
			if (i + z[i] > r)
			{
				z[i] = r - i;
			}
		}
		while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]])
		{
			z[i]++;
		}
		if (i + z[i] > r)
		{
			l = i;
			r = i + z[i];
		}
	}
	return z;
}

ll cdiv(ll a, ll b)
{
	return a / b + ((a ^ b) > 0 && a % b);
}

ll fdiv(ll a, ll b)
{
	return a / b - ((a ^ b) < 0 && a % b);
}

ll sumDigits(ll num)
{
	ll sum = 0;
	while (num != 0)
	{
		sum += num % 10;
		num /= 10;
	}
	return sum;
}

void preNCR()
{
	facN = 2e5 + 1;
	f.resize(facN), inv.resize(facN), finv.resize(facN);
	f[0] = 1;
	for (ll i = 1; i < facN; i++)
	{
		f[i] = 1LL * i * f[i - 1] % mod;
	}
	inv[1] = 1;
	for (ll i = 2; i < facN; i++)
	{
		inv[i] = (-(1LL * mod / i) * inv[mod % i]) % mod;
		inv[i] = (inv[i] + mod) % mod;
	}
	finv[0] = 1;
	for (ll i = 1; i < facN; i++)
	{
		finv[i] = 1LL * inv[i] * finv[i - 1] % mod;
	}
}

ll ncr(ll n, ll r)
{
	if (n < r || n < 0 || r < 0)
	{
		return 0;
	}
	return 1LL * f[n] * finv[n - r] % mod * finv[r] % mod;
}

namespace MillerRabin
{
	mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
	const ll P = 1e6 + 9;
	ll primesMR[P], spfMR[P];
	inline ll mul_mod(ll x, ll y, ll m)
	{
		ll res = __int128(x) * y % m;
		return res;
	}
	inline ll pow_mod(ll x, ll n, ll m)
	{
		ll res = 1 % m;
		for (; n; n >>= 1)
		{
			if (n & 1)
				res = mul_mod(res, x, m);
			x = mul_mod(x, x, m);
		}
		return res;
	}
	inline bool miller_rabin(ll n)
	{
		if (n <= 2 || (n & 1 ^ 1))
			return (n == 2);
		if (n < P)
			return spfMR[n] == n;
		ll c, d, s = 0, r = n - 1;
		for (; !(r & 1); r >>= 1, s++)
		{
		}
		for (ll i = 0; primesMR[i] < n && primesMR[i] < 32; i++)
		{
			c = pow_mod(primesMR[i], r, n);
			for (ll j = 0; j < s; j++)
			{
				d = mul_mod(c, c, n);
				if (d == 1 && c != 1 && c != (n - 1))
					return false;
				c = d;
			}
			if (c != 1)
				return false;
		}
		return true;
	}
	void init()
	{
		ll cnt = 0;
		for (ll i = 2; i < P; i++)
		{
			if (!spfMR[i])
				primesMR[cnt++] = spfMR[i] = i;
			for (ll j = 0, k; (k = i * primesMR[j]) < P; j++)
			{
				spfMR[k] = primesMR[j];
				if (spfMR[i] == spfMR[k])
					break;
			}
		}
	}
}

void timer()
{
#ifndef ONLINE_JUDGE
	auto stop = high_resolution_clock::now();
	duration<double> duration = stop - start;
	cout << duration.count() << " seconds" << endl;
#endif
}

void fileIOE()
{
#ifndef ONLINE_JUDGE
	if (!freopen("input.txt", "r", stdin))
	{
		return;
	}
	if (!freopen("output.txt", "w", stdout))
	{
		return;
	}
	if (!freopen("error.txt", "w", stderr))
	{
		return;
	}
#endif
}

// 1.  Think DP/recursion.
// 2.  Think greedy.
// 3.  Think binary search.
// 4.  Think sliding window/two pointer.
// 5.  Think bit masking.
// 6.  Think bit manipulation.
// 7.  Think prefix.
// 8.  Think difference array.
// 9.  Think mapping.
// 10. Think multiset/ordered set.
// 11. Think gcd/lcm/modulo arithmetic.
// 12. Think in variables/expressions.
// 13. Think dfs/bfs.
// 14. Think bipartite.
// 15. Think in complement like all - answer.
// 16. In case of palindromic, think till half only.
// 17. Subtree -> Euler Tour.
// 18. Think brute force.

void solve()
{
}

signed main()
{
	shibo
	fileIOE(); // comment for interactive problems
	ll t = 1,
	   n = 2e5;
	// prime(); // uncomment to get prime numbers till 1e7 and isPrime functionality
	//  sievespf(); // uncomment for getFactorization functionality
	// preNCR(); // uncomment to get ncr of numbers % mod
	//  MillerRabin::init(); // uncomment to get primality test upto 1e18
	cin >> t; // uncomment to use test cases
	while (t--)
	{
		solve();
	}
	timer();
}
