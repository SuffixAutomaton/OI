#include <bits/stdc++.h>
using namespace std;

int k = 1;
struct node {
	int c[26], link;
} ac[100005];

int main() {
	for (int i = 0; i < 26; i++) ac[1].c[i] = 0;
	string s;
	int n;
	cin >> s >> n;
	vector<int> word;
	while (n--) {
		int m;
		string t;
		cin >> m >> t;
		int u = 1;
		for (int i = 0; i < (int) t.size(); i++) {
			if (!ac[u].c[t[i]-'a']) {
				ac[u].c[t[i]-'a'] = ++k;
				for (int j = 0; j < 26; j++) ac[k].c[j] = 0;
			}
			u = ac[u].c[t[i]-'a'];
		}
		word.push_back(u);
	}
	queue<int> bfs;
	bfs.push(1);
	while (!bfs.empty()) {
		auto u = bfs.front();
		bfs.pop();
		for (int i = 0; i < 26; i++) {
			int c = ac[u].c[i], v = ac[u].link;
			if (!c) continue;
			while (v && !ac[v].c[i]) v = ac[v].link;
			if (v) ac[c].link = ac[v].c[i];
			else ac[c].link = 1;
			bfs.push(c);
		}
	}
	return 0;
}