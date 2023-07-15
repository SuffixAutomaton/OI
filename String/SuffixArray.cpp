#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main () {
	ios::sync_with_stdio(false);
	cin.tie(0);
	string s;
	cin >> s;
	s += "$";
	int n = s.size();
	vector<int> p (n), c (n);
	iota(p.begin(), p.end(), 0);
	sort(p.begin(), p.end(), [&] (int a, int b) {return s[a] < s[b];});
	for (int i = 1; i < n; i++) {
		if (s[p[i]] == s[p[i-1]]) c[p[i]] = c[p[i-1]];
		else c[p[i]] = c[p[i-1]] + 1;
	}
	for (int k = 0; (1<<k) < n; k++) {
		for (int i = 0; i < n; i++) p[i] = (p[i] - (1<<k) + n) % n;
		vector<int> cnt (n+1), p_new (n), c_new (n);
		for (auto& x : c) cnt[x+1]++;
		for (int i = 1; i < n; i++) cnt[i] += cnt[i-1];
		for (auto& x : p) p_new[cnt[c[x]]++] = x;
		swap(p, p_new);
		for (int i = 1; i < n; i++) {
			pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1<<k)) % n]};
			pair<int, int> cur = {c[p[i]], c[(p[i] + (1<<k)) % n]};
			if (prev == cur) c_new[p[i]] = c_new[p[i-1]];
			else c_new[p[i]] = c_new[p[i-1]] + 1;
		}
		swap(c, c_new);
	}
	vector<int> lcp (n-1);
	for (int i = 0, k = 0; i < n; i++) {
		if (c[i] == n-1) {
			k = 0;
			continue;
		}
		int j = p[c[i]+1];
		while (i+k < n && j+k < n && s[i+k] == s[j+k]) k++;
		lcp[c[i]] = k;
		k = max(0, k-1);
	}
	for (int i = 1; i < n; i++) cout << p[i] << ' ';
	cout << '\n';
	for (int i = 0; i < n-1; i++) cout << lcp[i] << ' ';
	cout << '\n';
	return 0;
}