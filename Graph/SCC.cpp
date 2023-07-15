#include <bits/stdc++.h>
using namespace std;

bool vis[100005];
int scc[100005], k;
vector<int> G[100005], Gr[100005], post;

void dfs (int u) {
	vis[u] = true;
	for (auto& v : G[u]) if (!vis[v]) dfs(v);
	post.push_back(u);
}

void dfsr (int u) {
	scc[u] = k;
	for (auto& v : Gr[u]) if (!scc[v]) dfsr(v);
}

int main() {
	int n, m;
	cin >> n >> m;
	while (m--) {
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		Gr[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) if (!vis[i]) dfs(i);
	reverse(post.begin(), post.end());
	for (auto& u : post) if (!scc[u]) {
		k++;
		dfsr(u);
	}
	return 0;
}
