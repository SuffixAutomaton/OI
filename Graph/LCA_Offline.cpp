#include <bits/stdc++.h>
using namespace std;

vector<int> g[500001];
int lift[500001][21], tin[500001], tout[500001], timer = 0, w;

void dfs (int u, int p) {
	tin[u] = ++timer;
	lift[u][0] = p;
	for (int i = 1; i <= w; i++) lift[u][i] = lift[lift[u][i-1]][i-1];
	for (auto& v : g[u]) if (v != p) dfs(v, u);
	tout[u] = ++timer;
}

bool anc (int u, int v) {
	return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca (int u, int v) {
	if (anc(u, v)) return u;
	if (anc(v, u)) return v;
	for (int i = w; i >= 0; i--) if (!anc(lift[u][i], v)) u = lift[u][i];
	return lift[u][0];
}

int main () {
	int n, q, u, v;
	cin >> n >> q;
	for (int i = 1; i < n; i++) {
		cin >> v;
		g[i].push_back(v);
		g[v].push_back(i);
	}
	w = ceil(log2(n));
	dfs(0, 0);
	while (q--) {
		cin >> u >> v;
		cout << lca(u, v) << "\n";
	}
	return 0;
}
