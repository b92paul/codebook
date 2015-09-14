//by david942j
#include <cstdio>
#include <cstring>
#include <set>
#include <map>
#include <ctime>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <deque>
#include <cassert>
#include <queue>
#include <stack>
#include <cstdlib>
#define openfile(s) freopen(s".in","r",stdin);freopen(s".out","w",stdout)
#define mpr std::make_pair
#define lg(x) (31-__builtin_clz(x))
#define lgll(x) (63-__builtin_clzll(x))
#define __count __builtin_popcount
#define __countll __builtin_popcountll
#define X first
#define Y second
#define mst(x) memset(x,0,sizeof(x))
#define mst1(x) memset(x,-1,sizeof(x))
#define ALL(c) (c).begin(),(c).end()
#define FOR(i,n) for(int i=0;i<n;i++)
#define FOR1(i,n) for(int i=1;i<=n;i++)
#define FORit(it,c) for(__typeof(c.begin()) it=c.begin();it!=c.end();++it)
#define pb push_back
#define RI(x) scanf("%d",&x)
#define RID(x) int x;RI(x)
using namespace std;
typedef long long LL;
typedef double LD;
typedef vector<int> VI;
typedef std::pair<int,int> PII;
template<class T>inline void maz(T &a,T b){if(a<b)a=b;}
template<class T>inline void miz(T &a,T b){if(a>b)a=b;}
template<class T>inline T abs(T a){return a>0?a:-a;}
const int N=10010,INF=1e9;
struct Big{
    #define mod 10000000LL // 7
    //#define MN 1000 // max digit = 1000*7 
    int s; //sign, if no sign need, take s===1 for all occurrence
    vector<LL> p; // must sure p.size()*mod*mod < LL; 18-7*2=>10000
    Big(){zero();}
    Big(LL n) {
        if(n==0){zero();return;}
        s=n>0?1:-1;
        n*=s;
        while(n) {
            p.pb(n%mod);
            n/=mod;
        }
    }
    void zero(){s=1;p.pb(0);}
    void initH(int h){p.resize(h);FOR(i,h)p[i]=0;}
    LL& operator[](const int &i){return p[i];}
    LL operator[](const int &i)const{return p[i];}
    inline int h()const{return p.size();}
    inline void _flip(){s=-s;}
    Big flip()const{Big a=*this;a._flip(); return a;}
    void norm() {
        FOR(i,h())if(p[i] >= mod){
            p[i+1]+=p[i]/mod;
            p[i]%=mod;
        }
        while(p.size()>1 && p.back()==0)p.pop_back();
        if(p.back()==0)s=1;
    }
    Big operator*(const Big &A)const {
        Big tmp; tmp.initH(h()+A.h());
        FOR(i,h())FOR(j,A.h())tmp[i+j] += p[i]*A[j];
        tmp.s = s*A.s;
        tmp.norm();
        return tmp;
    }
    Big operator+(const Big &A)const {
        if(s != A.s) {
            if(s>0)return operator-(A.flip());
            return A-(flip());
        }
        Big tmp; tmp.initH(max(h(),A.h())+1);
        FOR(i,h())tmp[i] += p[i];
        FOR(i,A.h())tmp[i] += A[i];
        tmp.s = s;
        tmp.norm();
        return tmp;
    }
    // for minus
    bool operator<(const Big &A)const {
        if(s!=A.s)return s < A.s;
        bool f= s==-1;
        if(h() != A.h()) return (h()<A.h()) ^ f;
        for(int i=h()-1;i>=0;i--)
            if(p[i] < A[i]) return true ^ f;
            else if(p[i] > A[i]) return false ^ f;
        return false;
    }
    Big operator-(const Big &A)const {
        if(s!=A.s) {
            if(s>0) return operator+(A.flip());
            return (A+flip()).flip();
        }
        if(s<0) return A.flip()-flip();
        if(operator<(A)) return (A-(*this)).flip();
        Big tmp; tmp=*this;
        FOR(i,A.h())tmp[i] -= A[i];
        FOR(i,h()) if(tmp[i]<0)tmp[i+1]--,tmp[i]+=mod;
        tmp.norm();
        return tmp;
    }
    // for division
    void shift(int h) {
        p.resize(p.size() + h);
        for(int i=p.size()-1; i>=h; i--)
            p[i]=p[i-h];
        for(int i=h-1;i>=0;i--)p[i]=0;
    }
    Big operator/(const Big &A)const {
        if(h() < A.h()) return Big();
        if(A[A.h()-1] == 0) throw "divided by 0";
        Big c = *this, ans;
        c.s=1;
        for(int i=h()-A.h();i>=0;i--) {
            Big tmp=A; tmp.shift(i); tmp.s=1;
            
            int low=0,up=mod-1;
            while(low<=up) {
                int mid=low+up>>1;
                if(!(c<tmp*mid)) low=mid+1;
                else up=mid-1;
            }
            c = c-tmp*up;
            ans.p.pb(up);
        }
        reverse(ALL(ans.p));
        ans.s=s*A.s;
        ans.norm();
        return ans;
    }
    void print() {
        if(s<0)putchar('-');
        printf("%d",(int)p[h()-1]);
        for(int i=h()-2;i>=0;i--)printf("%07d",(int)p[i]);
        puts("");
    }
};
int main() {
}
