#include <bits/stdc++.h>

const int MAXN = 100001;
const int MAXM = 200001;
const int INF = ~0u >> 2;

struct edge{int node,flow,next,opp;}e[MAXM];
struct road{
	int x, y, c;
}r[MAXM];

int n, m, x, t, d[MAXN], h[MAXN], gap[MAXN], cur[MAXN], pre[MAXN];

void addEdge(int x,int y,int f) {
    t++;e[t]=(edge){y,f,h[x],t+1};h[x]=t;
    t++;e[t]=(edge){x,0,h[y],t-1};h[y]=t;
}
int Maxflow_Isap(int s,int t,int n) {
	std::fill(pre + 1, pre + n + 1, -1);
	std::fill(d + 1, d + n + 1, 0);
	std::fill(gap, gap + n + 1, 0);
    for (int i=1;i<=n;i++) cur[i]=h[i];
    gap[0]=n;
    int u=pre[s]=s,v,maxflow=0;
    while (d[s]<n) {
      v=n+1;
      for (int i=cur[u];i;i=e[i].next)
        if (e[i].flow && d[u]==d[e[i].node]+1) {
          v=e[i].node;cur[u]=i;break;
        }
      if (v<=n) {
        pre[v]=u;u=v;
        if (v==t) {
          int dflow=INF,p=t;u=s;
          while (p!=s) {
            p=pre[p];
            dflow=std::min(dflow,e[cur[p]].flow);
          }
          maxflow+=dflow;p=t;
          while (p!=s) {
            p=pre[p];
            e[cur[p]].flow-=dflow;
            e[e[cur[p]].opp].flow+=dflow;
          }
        }
      }
      else{
        int mindist=n+1;
        for (int i=h[u];i;i=e[i].next)
          if (e[i].flow && mindist>d[e[i].node]) {
            mindist=d[e[i].node];cur[u]=i;
          }
        if (!--gap[d[u]]) return maxflow;
        gap[d[u]=mindist+1]++;u=pre[u];
      }
    }
    return maxflow;
}

double check(const double &answer) {
	std::fill(h + 1, h + n + 1, t = 0);
	for (int i = 1; i <= m; i++) {
		addEdge(r[i].x, r[i].y, (int)std::min(1.0 * INF, floor(1.0 * r[i].c / answer)));
	}
	return Maxflow_Isap(1, n, n) >= x;
}

int main() {
	std::cin >> n >> m >> x;
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &r[i].x, &r[i].y, &r[i].c);
	}
	double left = 0, right = 1ll << 40;
	for (int c = 1; c <= 80; c++) {
		double middle = (left + right) / 2.0;
		if (check(middle)) left = middle;
		else right = middle;
	}
	printf("%.10f\n", left * x);
	return 0;
}
