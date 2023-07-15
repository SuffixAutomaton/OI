#include <bits/stdc++.h>
using namespace std;

int low[100005], tin[100005], timer;
vector<pair<int, int>> G[100005];
bool bridge[100005];

void dfs (int u, int p) {
	tin[u] = low[u] = ++timer;
	for (auto& [v, id] : G[u]) if (v != p) {
		if (tin[v]) low[u] = min(low[u], tin[v]);
		else {
			dfs(v, u);
			low[u] = min(low[u], low[v]);
		}
		bridge[id] = tin[u] < low[v];
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	int id = 0;
	while (m--) {
		int u, v;
		cin >> u >> v;
		G[u].push_back({v, ++id});
		G[v].push_back({u, id});
	}
	dfs(1, 0);
	
	return 0;
}
