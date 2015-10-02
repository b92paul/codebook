#include <bits/stdc++.h>
#define FOR(i,n) for(int i=0;i<n;i++)
#define FOR1(i,n) for(int i=1;i<=n;i++)
#define pb push_back
#define mpr make_pair
#define X first
#define Y second
#define ALL(c) (c).begin(),(c).end()
#define RI(x) scanf("%d",&x)
#define RID(x) int x;RI(x)
typedef long long LL;
using namespace std;
typedef vector<int> VI;
typedef pair<int,int> PII;
typedef double LD;
const int N=200101,INF=1e9;
const LD EPS=1e-6;
char s[N],c[N];
struct Node{
    Node* nxt[28], *fail;
    int len;
    int cnt;
    Node() {}
    Node(int _len) {
        len=_len;
        memset(nxt,0,sizeof(nxt));
        fail=0;
        cnt=1;
    }
}sta[N*2];
struct PanTree {
    int n; // number of state
    int slen; // length of char added
    Node *last;
    #define FN N*2+1 // FN = sizeof string + 1
    char s[FN]; // 1base s[0]=-1
    void init() {
        sta[0]=Node(0);
        sta[1]=Node(-1);
        last=&sta[0];
        sta[0].fail = &sta[1];
        n=1;
        slen=0;
    }
    Node* getfail(Node *last){
        while(s[slen-1-last->len] != s[slen]) last=last->fail;
        return last;
    }
    void add(char c) {
        s[++slen]=c;
        last=getfail(last);
        if(last->nxt[c] !=0) {
            last = last->nxt[c];
            last->cnt++;
            return;
        }
        sta[n+1] = Node(last->len+2);
        last->nxt[c] = &sta[n+1];
        if(last->fail == 0) 
            sta[n+1].fail = &sta[0];
        else {
            last=getfail(last->fail);
            sta[n+1].fail = last->nxt[c];
        }
        last = &sta[++n];
    }
    void expand(char *_s) { // 0base _s
        init();
        s[0]=-1;
        for(int i=0;_s[i];i++)
            add(_s[i]-'a');
    }
    void count() {
        for(int i=n;i>=2;i--) sta[i].fail->cnt += sta[i].cnt;
    }
}ptree;
int cntA[N*2],cntB[N*2];
void solve() {
    ptree.init();
    ptree.expand(s);
    ptree.count();
    int tmpn=ptree.n;
    for( int i=2;i<=ptree.n;i++)
        cntA[i]=sta[i].cnt;
    ptree.add('z'+1 -'a');
    ptree.add('z'+2-'a');
    for( int i=2;i<=ptree.n;i++)sta[i].cnt=0;
    for(int i=0;c[i];i++) {
        ptree.add(c[i]-'a');
    }
    ptree.count();
    for( int i=2;i<=ptree.n;i++)
        cntB[i]=sta[i].cnt;
    LL ans=0;
    for(int i=2;i<=tmpn;i++) {
        ans+=(LL)cntA[i]*cntB[i];
    }
    cout << ans <<"\n";
}
int main() {
    RID(T);
    FOR1(w,T) {
        scanf("%s%s",s,c);
        printf("Case #%d: ",w);
        solve();
    }
}
/*
3
abacab
abccab
aba
aba
ab
ab
aba
aba
//6
3
abacab
abccab
faultydogeuniversity
hasnopalindromeatall
abbacabbaccab
youmayexpectedstrongsamplesbutnow
*/