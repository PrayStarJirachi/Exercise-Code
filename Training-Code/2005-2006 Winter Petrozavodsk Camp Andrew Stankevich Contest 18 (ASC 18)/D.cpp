#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

const int INF = ~0u >> 4;
const int MAXN = 111111;
const int MAXM = 222222;

struct edge{int node,dist,flow,from,cost,opp,next;}e[MAXM];
int n,m,t,h[MAXN],p[MAXN],a[MAXN],d[MAXN],q[MAXN], delta[MAXN];
std::pair<int, int> record[MAXM];
bool v[MAXN];

void addedge(int x,int y,int f,int c) {
    t++;e[t].from=x;e[t].node=y;e[t].flow=f;e[t].cost=c;e[t].opp=t+1;e[t].next=h[x];h[x]=t;
    t++;e[t].from=y;e[t].node=x;e[t].flow=0;e[t].cost=-c;e[t].opp=t-1;e[t].next=h[y];h[y]=t;
}
bool spfa(int s,int t,int n) {
    memset(v,false,sizeof(v));
    memset(p,0,sizeof(p));  
    for (int i=1;i<=n;i++) d[i]=INF;
    int l=0,r=0;v[q[++r]=s]=true;d[s]=0;
    while (l<r) {
      l++;
      for (int i=h[q[l]];i;i=e[i].next)
        if (e[i].flow && d[e[i].node]>d[q[l]]+e[i].cost) {
          d[e[i].node]=d[q[l]]+e[i].cost;p[e[i].node]=i;
          if (!v[e[i].node]) v[q[++r]=e[i].node]=true;
        }
      v[q[l]]=false;
    }
    return d[t]<INF;
}
std::pair<int, int> MCMF(int s,int t,int n) {
    int ret=0, maxflow = 0;
    while (spfa(s,t,n)) {
      int dflow=INF,dcost=0;
      for (int i=p[t];i;i=p[e[i].from]) dflow=std::min(dflow,e[i].flow);
      maxflow += dflow;
      for (int i=p[t];i;i=p[e[i].from]) {
        e[i].flow-=dflow;
        e[e[i].opp].flow+=dflow;
        ret+=dflow*e[i].cost;
        dcost+=dflow*e[i].cost;
      }
    }
    return std::make_pair(maxflow,ret);
}

int main() {
	freopen("D.in", "r", stdin);
	scanf("%d%d", &n, &m);
	long long answer = 0;
	for (int i = 1; i <= m; i++) {
		int x, y, d;
		scanf("%d%d%d", &x, &y, &d);
		addedge(x, y, INF, 1);
		answer += d;
		delta[x] -= d;
		delta[y] += d;
		record[i] = std::make_pair(t, d);
	}
	int sumS = 0, sumT = 0;
	for (int i = 1; i <= n; i++) {
		if (delta[i] > 0) {
			addedge(n + 1, i, delta[i], 0);
			sumS += delta[i];
		}
		if (delta[i] < 0) {
			addedge(i, n + 2, -delta[i], 0);
			sumT += -delta[i];
		}
	}
	std::pair<int, int> ret = MCMF(n + 1, n + 2, n + 2);
	if (ret.first != sumS || ret.first != sumT) return printf("-1\n"), 0;
	printf("%lld\n", answer + ret.second);
	for (int i = 1; i <= m; i++)
		printf("%d\n", record[i].second + e[record[i].first].flow);
	return 0;
}
