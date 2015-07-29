const int NO_SOLUTION = -1;
class Edge { public:
    int v,u,l;
};
const int MAXEDGE=500000;
const int MAXNUM=600;
const int INF=1<<29;
Edge e[MAXEDGE],pred[MAXNUM];
int incycle[MAXNUM]={0},cycid;
bool contracted[MAXNUM];
int dmst(int s,int n,int m){
    int v,u,i,cost=0;
    for(i=0;i<n;i++) { pred[i].v=-1; contracted[i]=0; }
    while(1) {
        // find a uncontracted node with no in arc: v
        for(v=0;v<n;v++) if(v!=s&&!contracted[v]&&pred[v].v==-1) break;
        if(v==n) return cost; // done // find least-weighted in arc
        pred[v].l=INF;
        for(i=0;i<m;i++)
            if(e[i].u==v&&e[i].l<pred[v].l) pred[v]=e[i];
        if(pred[v].l==INF) return -1;
        // append arc, check cycle
        cost+=pred[v].l;
        for(u=pred[v].v;u!=v&&u!=-1;u=pred[u].v);
        if(u==-1) continue;
        // trace and contract nodes in cycle
        incycle[v]=++cycid;
        for(u=pred[v].v;u!=v;u=pred[u].v) {
            contracted[u]=1;
            incycle[u]=cycid;
        }
        // update arc costs into the cycle
        for(i=0;i<m;i++)
            if(incycle[e[i].v]!=cycid&&incycle[e[i].u]==cycid)
                e[i].l-=pred[e[i].u].l;
        // contract: update labels
        pred[v].v=-1;
        for(i=0;i<m;i++) {
            if(incycle[e[i].v]==cycid) e[i].v=v;
            if(incycle[e[i].u]==cycid) e[i].u=v;
            if(e[i].v==e[i].u) e[i--]=e[--m];
        }
        for(i=0;i<n;i++) {
            if(contracted[i]) continue;
            if(pred[i].v>=0&&incycle[pred[i].v]==cycid) pred[i].v=v;
        }
    }
}
int main(){}