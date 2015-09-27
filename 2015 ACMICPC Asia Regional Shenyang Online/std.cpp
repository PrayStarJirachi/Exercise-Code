#include<algorithm>  
#include<iostream>  
#include<cstring>  
#include<cstdio>  
#include<vector>  
#include<cmath>  
#include<queue>  
#include<stack>  
#include<set>  
#include<map>  
#define LL long long  
#define MP make_pair  
#define xx first  
#define yy second  
#define lson l, m, rt << 1  
#define rson m + 1, r, rt << 1|1  
#define CLR(a, b) memset(a, b, sizeof(a))  
using namespace std;  
  
const int MAXN = 100010;  
struct Edge  
{  
    int to,next;  
} edge[MAXN*2];  
int head[MAXN],tot;  
int top[MAXN], fa[MAXN], deep[MAXN], num[MAXN];  
int p[MAXN], fp[MAXN], son[MAXN];  
///p[u] = i(树上节点在线段树中位置),fp[i] = u(线段树上i点对应树上节点u)  
int pos;  
void init()  
{  
    tot = 0;  
    memset(head,-1,sizeof(head));  
    pos = 1;  
    memset(son,-1,sizeof(son));  
}  
inline void addedge(int u,int v)  
{  
    edge[tot].to = v;  
    edge[tot].next = head[u];  
    head[u] = tot++;  
}  
inline void dfs1(int u,int pre,int d)  
{  
    deep[u] = d;  
    fa[u] = pre;  
    num[u] = 1;  
    for(int i = head[u]; i != -1; i = edge[i].next)  
    {  
        int v = edge[i].to;  
        if(v != pre)  
        {  
            dfs1(v,u,d+1);  
            num[u] += num[v];  
            if(son[u] == -1 || num[v] > num[son[u]])  
                son[u] = v;  
        }  
    }  
}  
inline void getpos(int u,int sp)  
{  
    top[u] = sp;  
    p[u] = pos++;  
    fp[p[u]] = u;  
    if(son[u] == -1)return;  
    getpos(son[u],sp);  
    for(int i = head[u]; i != -1; i = edge[i].next)  
    {  
        int v = edge[i].to;  
        if(v != son[u] && v != fa[u])  
            getpos(v,v);  
    }  
}  
  
int seg[MAXN<<2], tag[MAXN<<2];  
  
void up(int rt)  
{  
    seg[rt] = seg[rt<<1] + seg[rt<<1|1];  
}  
  
void build(int l, int r, int rt)  
{  
    tag[rt] = 0;  
    if(l == r)  
    {  
        seg[rt] = 1;  
        return ;  
    }  
    int m = (l + r) >> 1;  
    build(lson);  
    build(rson);  
    up(rt);  
}  
  
void down(int rt)  
{  
    if(tag[rt])  
    {  
        seg[rt<<1] = seg[rt<<1|1] = 0;  
        tag[rt<<1] = tag[rt<<1|1] = 1;  
        tag[rt] = 0;  
    }  
}  
  
void update(int L, int R, int l, int r, int rt)  
{  
    if(seg[rt] == 0) return ;  
    if(L <= l && r <= R)  
    {  
        seg[rt] = 0;  
        tag[rt] = 1;  
        return ;  
    }  
    down(rt);  
    int m = (l + r) >> 1;  
    if(L <= m) update(L, R, lson);  
    if(R > m) update(L, R, rson);  
    up(rt);  
}  
  
int query(int L, int R, int l, int r, int rt)  
{  
    if(seg[rt] == 0) return 0;  
    if(L <= l && r <= R)  
    {  
        return seg[rt];  
    }  
    down(rt);  
    int ret = 0;  
    int m = (l + r) >> 1;  
    if(L <= m) ret += query(L, R, lson);  
    if(R > m) ret += query(L, R, rson);  
    return ret;  
}  
  
int n;  
  
void add(int u,int v)    
{  
    int f1 = top[u], f2 = top[v];  
    while(f1 != f2)  
    {  
        if(deep[f1] < deep[f2])  
        {  
            swap(f1,f2);  
            swap(u,v);  
        }  
        update(p[f1], p[u], 2, n, 1);  
        u = fa[f1];  
        f1 = top[u];  
    }  
    if(u == v)return;  
    if(deep[u] > deep[v])swap(u,v);  
    update(p[son[u]], p[v], 2, n, 1);  
}  
int ask(int u,int v)  
{  
    int f1 = top[u], f2 = top[v];  
    int ret = 0;  
    while(f1 != f2)  
    {  
        if(deep[f1] < deep[f2])  
        {  
            swap(f1,f2);  
            swap(u,v);  
        }  
        ret += query(p[f1], p[u], 2, n, 1);  
        u = fa[f1];  
        f1 = top[u];  
    }  
    if(u == v) return ret;  
    if(deep[u] > deep[v])swap(u,v);  
    ret += query(p[son[u]], p[v], 2, n, 1);  
    return ret;  
}  
//适用于正负整数  
pair<int,int>pp[MAXN];  
int link[MAXN];  
  
template <class T>  
inline bool scan_d(T &ret)  
{  
    char c;  
    int sgn;  
    if(c=getchar(),c==EOF) return 0; //EOF  
    while(c!='-'&&(c<'0'||c>'9')) c=getchar();  
    sgn=(c=='-')?-1:1;  
    ret=(c=='-')?0:(c-'0');  
    while(c=getchar(),c>='0'&&c<='9') ret=ret*10+(c-'0');  
    ret*=sgn;  
    return 1;  
}  
  
struct Qeury  
{  
    int op, u, v, ans;  
    void inpt()  
    {  
        scan_d(op);  
        scan_d(u);  
        scan_d(v);  
    }  
} qrt[MAXN];  
  
map<pair<int, int>, int> mp1;  
  
int fat[MAXN];  
  
int Find(int x)  
{  
    return fat[x] == x ? x : fat[x] = Find(fat[x]);  
}  
  
int main()  
{  
	freopen("I.in", "r", stdin);
	freopen("Ibc.out", "w", stdout);
    int m,T,cas = 1, q;  
    scan_d(T);  
    while(T--)  
    {  
        init(); mp1.clear();  
        scan_d(n); scan_d(m); scan_d(q);  
        for(int i = 0; i < m; i ++)  
        {  
            int u, v;  
            scan_d(u);  
            scan_d(v);  
            if(u == v) continue;  
            if(u > v) swap(u, v);  
            mp1[MP(u, v)] ++;  
        }  
        for(int i = 0; i < q; i ++)  
        {  
            qrt[i].inpt();  
            if(qrt[i].op == 1)  
            {  
                int u = qrt[i].u, v = qrt[i].v;  
                if(u == v) continue;  
                if(u > v) swap(u, v);  
                mp1[MP(u, v)] --;  
                if(mp1[MP(u, v)] == 0)  
                    mp1.erase(MP(u, v));  
            }  
        }  
        map<pair<int, int>, int>::iterator it;  
        for(int i = 1; i <= n; i ++)  
            fat[i] = i;  
        int e_cnt = 1;  
        for(it = mp1.begin(); it != mp1.end(); it ++)  
        {  
            pair<int, int> e = it->xx;  
            int fu = Find(e.xx), fv = Find(e.yy);  
            if(fu == fv) continue;  
            pp[e_cnt ++] = e;  
            addedge(e.xx, e.yy);  
            addedge(e.yy, e.xx);  
            fat[fu] = fv; mp1[e] --;  
        }  
        dfs1(1,0,0);  
        getpos(1,1);  
        for(int i = 1; i < n; i++)  
        {  
            if(deep[pp[i].first] > deep[pp[i].second])  
                swap(pp[i].first,pp[i].second);  
            link[pp[i].second] = i;///每条边的深度大的点表示这个边!!  
        }  
        build(2, n, 1);  
        for(it = mp1.begin(); it != mp1.end(); it ++)  
        {  
            if(it->yy == 0) continue;  
            pair<int, int> e = it->xx;  
            add(e.xx, e.yy);  
        }  
        for(int i = q - 1; i >= 0; i --)  
        {  
            int u = qrt[i].u, v = qrt[i].v, op = qrt[i].op;  
            if(op == 1)  
            {  
                add(u, v);  
            }  
            else  
            {  
                qrt[i].ans = ask(u, v);  
            }  
        }  
        printf("Case #%d:\n", cas ++);  
        for(int i = 0; i < q; i ++)  
        {  
            if(qrt[i].op == 2) printf("%d\n", qrt[i].ans);  
        }  
  
    }  
    return 0;  
}  
