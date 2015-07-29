//by david942j
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>
#define mpr std::make_pair
#define X first
#define Y second
#define ALL(c) (c).begin(),(c).end()
#define FOR(i,n) for(int i=0;i<n;i++)
#define FOR1(i,n) for(int i=1;i<=n;i++)
#define pb push_back
using namespace std;
typedef long long LL;
typedef vector<int> VI;
typedef std::pair<int,int> PII;
template<class T>inline void maz(T &a,T b){if(a<b)a=b;}
template<class T>inline void miz(T &a,T b){if(a>b)a=b;}
const int N=100000;
vector<PII> G[N];
int n,m;
vector<PII> edge;
VI bcc[N],cut;
int btop,d;
bool flag[N];
int dfn[N],low[N];
stack<int>S;
void add(int x,int y) {
    int etop=edge.size();
    G[x].pb(mpr(y,etop));
    G[y].pb(mpr(x,etop));
    edge.pb(mpr(x,y));
}
void init() {
    edge.clear();
    cut.clear();
    while(!S.empty())S.pop();
    d=0;
    FOR(i,btop)bcc[i].clear();
    btop=0;
    FOR1(i,n){
        flag[i]=false;
        G[i].clear();
    }
}
int root=1;
void DFS(int x,int par) {
    flag[x]=true;
    dfn[x]=low[x]=++d;
    int son=0;
    FOR(i,G[x].size()) {
        int y=G[x][i].X;
        if(y==par)continue;
        if(!flag[y]) {
            S.push(G[x][i].Y);//push edge id
            DFS(y,x);
            son++;
            if(low[y]>=dfn[x]) { //cut
                if(x!=root)cut.pb(x);//root special
                while(true) {
                    int id=S.top();S.pop();
                    bcc[btop].pb(id);
                    if(id==G[x][i].Y)break;
                }
                btop++;
            }
            miz(low[x],low[y]);
        }
        else {
            if(dfn[y] < dfn[x])S.push(G[x][i].Y);//back edge
            miz(low[x],dfn[y]);
        }
    }
    if(x==root && son>1) cut.pb(x);//root is cut
}
void output() {
    puts("cut");
    sort(ALL(cut));cut.resize(unique(ALL(cut))-cut.begin());
    FOR(i,cut.size())printf("%d ",cut[i]);
    puts("");
    printf("%d bcc\n",btop);
    FOR(i,btop) {
        FOR(j,bcc[i].size())
        printf("(%d,%d)",edge[bcc[i][j]].X,edge[bcc[i][j]].Y);
        puts("\n--");
    }
}
void BCC() {//multiedge seem as one edge
    DFS(root,0);
}
int main() {
    while(~scanf("%d%d",&n,&m)) {
        init();
        while(m--) {
            int x,y;scanf("%d%d",&x,&y);//1~n
            add(x,y);
        }
        BCC();
        output();
    }
}
/*
 3 3
 1 2 2 3 3 1
 
 7 9
 1 2 1 4 1 5
 2 3 2 4
 3 4
 5 6 5 7
 6 7
 
 7 10
 1 2 1 4 1 5
 2 3 2 4
 3 4
 5 6 5 7
 6 7
 2 6
 
 4 3
 2 1 2 3 2 4
 
 */
