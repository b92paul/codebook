#define FN 5010 
#define FM 500010
#define INF 1023456789
#define Cost int
struct E {
    int k; Cost c;
    E(){}
    E( int _k, Cost _c ):k(_k),c(_c){}
} es[FM*2];

struct Flow {
    int n,m,dis[FN],ptr[FN];
    int qq[FN],ql,qr;
    VI e[FN];
    void init( int _n ) {
        n=_n; m=0;
        FOR(i,n)e[i].clear();
    }
    void add(int a,int b, Cost c) {
        e[a].pb(m);es[m++]=E(b,c);
        e[b].pb(m);es[m++]=E(a,0);
    }
    bool BFS() {
        FOR(i,n)dis[i]=-1;
        ql=qr=0;
        qq[qr++]=0;
        dis[0]=0;
        while ( ql!=qr && dis[n-1]==-1 ) {
            int p=qq[ql++];
            FOR(i,e[p].size()) {
                E &ee=es[ e[p][i] ];
                if ( ee.c<=0 || dis[ee.k]!=-1 ) continue;
                dis[ qq[qr++]=ee.k ]=dis[p]+1;
            }
        }
        return dis[n-1]!=-1;
    }
    Cost go( int p, Cost c ) {
        if ( p==n-1 ) return c;
        for(int &i=ptr[p];i<e[p].size();i++) {
            E &ee=es[e[p][i]];
            if ( ee.c<=0 || dis[p]+1!=dis[ee.k] ) continue;
            Cost tmp=go(ee.k,min(c,ee.c));
            if(tmp > 0){
                ee.c-=tmp; es[e[p][i]^1].c+=tmp;
                return tmp;
            }
        }
        return 0;
    }
    Cost maxflow() {
        Cost ret=0, tmp;
        while ( BFS() ){
            FOR(i,n)ptr[i]=0;
            while( (tmp=go(0,INF)) > 0)
                ret+=tmp;
        }
        return ret;
    }
} flow;
