#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

const int MAXN = 100005;

int n, k;
vector<int> g[MAXN];
int timer = 0;
int tin[MAXN], low[MAXN];
bool visited[MAXN];
set<pair<int, int>> bridges; 

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for (int to : g[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v]) {
                bridges.insert({min(v, to), max(v, to)}); 
            }
        }
    }
}

int comp_id[MAXN];

void dfs_comp(int v, int cid) {
    comp_id[v] = cid;
    visited[v] = true;
    for (int to : g[v]) {
        if (visited[to]) continue;
        if (bridges.count({min(v, to), max(v, to)})) continue;
        dfs_comp(to, cid);
    }
}

int main() {
    cin >> n >> k;

    for (int i = 0; i < k; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    fill(visited, visited + n + 1, false);
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) dfs(i);
    }

    int cid = 0;
    fill(visited, visited + n + 1, false);
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs_comp(i, cid++);
        }
    }

    vector<int> tree_deg(cid, 0); 

    for (auto [u, v] : bridges) {
        int cu = comp_id[u];
        int cv = comp_id[v];
        tree_deg[cu]++;
        tree_deg[cv]++;
    }

    vector<int> leaf_comps;
    for (int i = 0; i < cid; ++i) {
        if (tree_deg[i] == 1) leaf_comps.push_back(i);
    }

    map<int, vector<int>> nodes_by_comp;
    for (int i = 1; i <= n; ++i) {
        nodes_by_comp[comp_id[i]].push_back(i);
    }

    vector<pair<int,int>> added_edges;

    for (int i = 0; i + 1 < leaf_comps.size(); i += 2) {
        int c1 = leaf_comps[i];
        int c2 = leaf_comps[i + 1];
        int u = nodes_by_comp[c1][0];
        int v = nodes_by_comp[c2][0];
        added_edges.push_back({u, v});
    }

    if (leaf_comps.size() % 2 == 1) {
        int c1 = leaf_comps.back();
        int c2 = leaf_comps[0];
        if (c1 != c2) {
            int u = nodes_by_comp[c1][0];
            int v = nodes_by_comp[c2][0];
            added_edges.push_back({u, v});
        }
    }

    cout << added_edges.size() << endl;
    for (auto [u, v] : added_edges) {
        cout << u << " " << v << endl;
    }

    return 0;
}