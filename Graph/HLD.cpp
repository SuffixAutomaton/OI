#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> g[100005];
int n, sz[100005], t[100005], h[100005], d[100005], p[100005], k;

void dfs (int u, int f) {
	p[u] = f;
	if ((int) g[u].size() > 1 && g[u][0] == f) swap(g[u][0], g[u][1]);
	for (int i = 0; i < (int) g[u].size(); i++) if (g[u][i] != f) {
		d[g[u][i]] = d[u]+1;
		dfs(g[u][i], u);
		sz[u] += sz[g[u][i]];
		if (sz[g[u][i]] > sz[g[u][0]]) swap(g[u][i], g[u][0]);
	}
}

void hld (int u, int head) {
	t[u] = ++k;
	h[u] = head;
	if (!g[u].empty() && g[u][0] != p[u]) hld(g[u][0], head);
	for (int i = 1; i < (int) g[u].size(); i++) if (g[u][i] != p[u]) hld(g[u][i], g[u][i]);
}

struct node {
	ll sum, lz;
	node () {sum = lz = 0;}
} seg[400005];

void push (int id, int sz) {
	seg[id].sum += seg[id].lz * sz;
	if (id <= n*2) {
		seg[id*2].lz += seg[id].lz;
		seg[id*2+1].lz += seg[id].lz;
	}
	seg[id].lz = 0;
}

void upd (int l, int r, int id, int ql, int qr, ll x) {
	push(id, r-l+1);
	if (qr < l || r < ql) return;
	if (ql <= l && r <= qr) {
		seg[id].lz += x;
		push(id, r-l+1);
		return;
	}
	upd(l, (l+r)/2, id*2, ql, qr, x);
	upd((l+r)/2+1, r, id*2+1, ql, qr, x);
	seg[id].sum = seg[id*2].sum + seg[id*2+1].sum;
}

ll query (int l, int r, int id, int ql, int qr) {
	push(id, r-l+1);
	if (qr < l || r < ql) return 0;
	if (ql <= l && r <= qr) return seg[id].sum;
	return query(l, (l+r)/2, id*2, ql, qr) + query((l+r)/2+1, r, id*2+1, ql, qr);
	return 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int m;
	cin >> n >> m;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1, 0);
	hld(1, 1);
	while (m--) {
		char op;
		int a, b;
		cin >> op >> a >> b;
		if (op == 'P') {
			while (h[a] != h[b]) {
				if (d[h[a]] < d[h[b]]) swap(a, b);
				upd(1, n, 1, t[h[a]], t[a], 1);
				a = p[h[a]];
			}
			if (d[a] < d[b]) swap(a, b);
			upd(1, n, 1, t[b]+1, t[a], 1);
		} else {
			ll ans = 0;
			while (h[a] != h[b]) {
				if (d[h[a]] < d[h[b]]) swap(a, b);
				ans += query(1, n, 1, t[h[a]], t[a]);
				a = p[h[a]];
			}
			if (d[a] < d[b]) swap(a, b);
			ans += query(1, n, 1, t[b]+1, t[a]); // +1 iff updating nodes instead of edges
			cout << ans << '\n';
		}
	}
	return 0;
}
