#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct edge {
	int v;
	ll c, f;
};

const int maxn = 6e4, maxm = 4e5, int s = maxn-2, t = maxn-1;
const ll inf = 1e18;
edge E[maxm];
vector<int> g[maxn];
int level[maxn], ptr[maxn], cnt = 1;

void add (int u, int v, ll c) {
	g[u].push_back(++cnt);
	E[cnt] = {v, c, 0};
	g[v].push_back(++cnt);
	E[cnt] = {u, 0, 0};
}

bool bfs () {
	fill(level, level+maxn, -1);
	level[s] = 0;
	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		auto u = q.front();
		q.pop();
		for (auto& id : g[u]) if (E[id].c > E[id].f && level[E[id].v] == -1) {
			level[E[id].v] = level[u] + 1;
			q.push(E[id].v);
		}
	}
	return level[t] != -1;
}

ll dfs (int u, ll flow) {
	if (!flow) return 0;
	if (u == t) return flow;
	for (int& cid = ptr[u]; cid < (int) g[u].size(); cid++) {
		int id = g[u][cid];
		if (level[E[id].v] == level[u] + 1 && E[id].c > E[id].f) {
			ll cur = dfs(E[id].v, min(flow, E[id].c - E[id].f));
			if (!cur) continue;
			E[id].f += cur;
			E[id^1].f -= cur;
			return cur;
		}
	}
	return 0;
}

ll flow () {
	ll f = 0;
	while (true) {
		if (!bfs()) break;
		fill(ptr, ptr+maxn, 0);
		while (ll flow = dfs(s, inf)) f += flow;
	}
	return f;
}

int main () {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	while (m--) {
		int u, v;
		ll c;
		cin >> u >> v >> c;
		add(u, v, c);
	}
	cout << flow() << '\n';
	return 0;
}