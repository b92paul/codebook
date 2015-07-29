const int N=501,INF=1<<26;
const LD EPS=1e-9;
const int mod=100000007;
int sgn(LD x){return (x>EPS)-(x<-EPS);}
struct PT {
    LD x,y;
    PT(LD X=0,LD Y=0):x(X),y(Y){}
    void read() {
        scanf("%lf%lf",&x,&y);
    }
    LD ang(){return atan2(y,x);}
    PT operator+(const PT &A)const {
        return PT(x+A.x,y+A.y);
    }
    PT operator-(const PT &A)const {
        return PT(x-A.x,y-A.y);
    }
    PT operator*(LD a)const{
        return PT(x*a,y*a);
    }
    PT operator/(const LD &A)const {
        return PT(x/A,y/A);
    }
    LD operator^(const PT &A)const {
        return x*A.y-y*A.x;
    }
    PT norm()const {
        return PT(-y,x);
    }
}p[N];
LD X(PT o, PT a,PT b){return (a-o)^(b-o);}
struct Ln {
    PT p1,p2;
    LD ang;
    Ln(){}
    Ln(PT P1,PT P2):p1(P1),p2(P2),ang((p2-p1).ang()){}
};
PT jiao(Ln a,Ln b) {
    LD u=X(a.p1,a.p2,b.p1);
    LD v=X(a.p2,a.p1,b.p2);
    return (b.p1*v+b.p2*u)/(u+v);
}
vector<Ln>L;
vector<PT>convex;
deque<Ln>Q;
bool cmp(Ln a, Ln b) {
    int ret = sgn(a.ang-b.ang);
    return ret!=0?ret>0:sgn(X(a.p1,a.p2,b.p1))<0;
}
bool check(Ln a, Ln b, Ln c) {
    //PT t=jiao(a,b);printf("jiao = %.2f, %.2f\n",t.x,t.y);
    return sgn(X(c.p1,c.p2,jiao(a,b)))>0;
}
void solve() {
    sort(ALL(L),cmp);
    FOR(i,L.size()) {
        if(i>0&&sgn(L[i].ang-L[i-1].ang)==0)continue;
        while(Q.size()>=2 && !check(Q[Q.size()-2],Q[Q.size()-1],L[i]))Q.pop_back();
        while(Q.size()>=2 && !check(Q[0],Q[1],L[i]))Q.pop_front();
        Q.pb(L[i]);
    }
    while(Q.size()>=2 && !check(Q[Q.size()-2],Q[Q.size()-1],Q[0]))Q.pop_back();
    while(Q.size()>=2 && !check(Q[0],Q[1],Q[Q.size()-1]))Q.pop_front();
    if(Q.size()<2)return;
    FOR(i,Q.size())convex.pb(jiao(Q[i],Q[(i+1)%Q.size()]));
}
int n;
#define LOG(a) (cerr<<__LINE__<<": "#a" = "<<(a)<<endl)
LD area() {
    LD ans=0;
    FOR(i,convex.size())ans+=convex[i]^convex[(i+1)%convex.size()];
    return fabs(ans)*0.5;
}
int main() {
    L.pb(Ln(PT(0,0),PT(10000,0)));
    L.pb(Ln(PT(10000,0),PT(10000,10000)));
    L.pb(Ln(PT(10000,10000),PT(0,10000)));
    L.pb(Ln(PT(0,10000),PT(0,0)));
    int n;scanf("%d",&n);
    FOR(i,n){
        PT a,b;a.read();b.read();
        L.pb(Ln(a,b));
    }
    solve();
    printf("%.1f\n",area());
}

