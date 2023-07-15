#include <bits/stdc++.h>
using namespace std;

int tin[100005], low[100005], block[100005], timer;
bool ap[100005];
vector<int> G[100005], bct[200005];
vector<vector<int>> grp;
stack<int> cur;

void dfs (int u, int p) {
	tin[u] = low[u] = ++timer;
	cur.push(u);
	for (auto& v : G[u]) if (v != p) {
		if (tin[v]) low[u] = min(low[u], tin[v]);
		else {
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if (low[u] >= low[v]) {
				ap[u] = p || tin[v] > 2;
				grp.push_back({u});
				while (grp.back().back() != v) {
					grp.back().push_back(cur.top());
					cur.pop();
				}
			}
		}
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	while (m--) {
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1, 0);
	int node = n+1;
	for (int i = 1; i <= n; i++) block[i] = node++;
	for (auto& g : grp) {
		int bk = node++;
		for (auto& u : g) {
			if (ap[u]) {
				bct[bk].push_back(block[u]);
				bct[block[u]].push_back(bk);
			} else block[u] = bk;
		}
	}
	
	return 0;
}
