#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

#define nline           "\n"
#define pii             pair<int, int>

ll expo(ll a, ll b, ll m) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % m; a = (a * a) % m; b = b >> 1;} return res;}
ll mminvprime(ll a, ll b) {return expo(a, b - 2, b);}


struct Hashing {
	ll p = 1001;
	ll m;
	int n;
	string s;

	vector<ll> prefixHash;
	vector<ll> powersOfP;
	vector<ll> inversePowersOfP;

	Hashing(string a, ll M) {
		s = a;
		n = s.size();
		m = M;
		prefixHash.resize(n + 1);
		powersOfP.resize(n + 1);
		inversePowersOfP.resize(n + 1);

		calculatePowAndInversePowOfP();
		calculatePrefixHash();
	}

	void calculatePowAndInversePowOfP() {
		ll currPow = 1;
		for (int i = 0; i <= n; i++) {
			powersOfP[i] = currPow;
			currPow = (currPow * p) % m;
		}

		inversePowersOfP[n] = mminvprime(powersOfP[n], m);
		for (int i = n - 1; i >= 0; i--) {
			inversePowersOfP[i] = (inversePowersOfP[i + 1] * p) % m;
		}
	}

	void calculatePrefixHash() {
		ll hashSoFar = 0;
		for (int i = 0; i < n; i++) {
			hashSoFar = (hashSoFar + (s[i] - '!' + 1) * powersOfP[i]) % m;
			prefixHash[i] = hashSoFar;
		}
	}

	ll substringHash(int l, int r) {
		ll val1 = prefixHash[r];
		ll val2 = l > 0 ? prefixHash[l - 1] : 0LL;
		return ((val1 - val2 + m) * inversePowersOfP[l]) % m;
	}
};

void solver() {
	int n, k;
	cin >> n >> k;
	string s;
	cin >> s;

	Hashing stringHash1 = Hashing(s, 1e9 + 9);
	Hashing stringHash2 = Hashing(s, 1e9 + 7);

	int count = 0;
	set<pii> substr;
	for (int i = 0; i <= n - k; i++) {
		pii s1 = {stringHash1.substringHash(i, i + k - 1), stringHash2.substringHash(i, i + k - 1)};
		substr.insert(s1);
	}
	cout << substr.size() << nline;

}

int main() {
	ll t = 1;
	cin >> t;
	while (t--) solver();
}