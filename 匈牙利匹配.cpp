#include<bits/stdc++.h>
using namespace std;

struct Edge {
    int to, nxt;
}edge[10066];
int head[106], tot;
void addedge(int x, int y) {
    edge[++tot].to = y; 
    edge[tot].nxt = head[x];
    head[x] = tot;
}

int n, m;
int linker[106];
bool vis[106];
bool dfs(int x) {
    for (int i = head[x]; i; i = edge[i].nxt) {
        int y = edge[i].to;
        if (!vis[y]) {
            vis[y] = 1;
            if (!linker[y] || dfs(linker[y])) {
                linker[y] = x;
                return true;
            }
        }
    }
    return false;
}

int main() {
    scanf("%d%d", &n, &m);
    int x, y;
    while (scanf("%d%d", &x, &y) && x > 0){
        addedge(x, y);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++){
        memset(vis, 0, sizeof(vis));
        if(dfs(i)) ans++;
    }
    printf("%d\n", ans);
    for (int i = 1; i <= m; i++)
        if (linker[i]) printf("%d %d\n", linker[i], i);
    return 0;
}


