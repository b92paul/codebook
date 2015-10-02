const LD Magic=39281841021341.0;
const LD EPS = 1e-6;
bool same(LD a, LD b){return abs(a-b)<EPS;}
struct PT{
	LD x,y;
	PT(){}
	PT(LD X,LD Y):x(X),y(Y){}
	PT operator+(const PT &A)const{return PT(x+A.x,y+A.y);}
	PT operator-(const PT &A)const{return PT(x-A.x,y-A.y);}
	PT operator*(const LD &A)const{return PT(x*A,y*A);}
	LD operator^(const PT &A)const{return x*A.y-y*A.x;}
	PT norm()const{return PT(-y,x)*(1.0/len());}
	PT rot(LD a)const{
		return PT(cos(a)*x-sin(a)*y,
				  sin(a)*x+cos(a)*y);
	}
	bool operator<(const PT &A)const{//sort by theta
		int s1=(y?y:x)<0; // if(X+ || Y+ || face1,2)s=0
		int s2=(A.y?A.y:A.x)<0;
		return s1==s2?(x*A.y>y*A.x):(s1<s2);
	}
	LD len()const{return sqrt(x*x+y*y);}
	LD len2()const{return x*x+y*y;}
};
inline PT l2p(PT a,PT b,PT c,PT d) {
	PT v=d-c;
	if(abs(v^(b-a))<EPS)return PT(Magic,Magic);
	LD t=(v^(c-a))/(v^(b-a));
	return a+(b-a)*t;
}
LD area(){
	int a=0;//A[n]=A[0];
	for(int i=0;i<n;i++)
		a+=A[i]^A[i+1];
	return a/2.0;
}
PT centroid() {
	PT ret(0,0);
	FOR(i,n) {
		ret.x+=(A[i].x+A[i+1].x)*(A[i]^A[i+1]);
		ret.y+=(A[i].y+A[i+1].y)*(A[i]^A[i+1]);
	}
	return ret*(1.0/(6*area()));
}
LD simpson (LD a, LD b, int n) {
	//n must be even
	//x_j=a+jh
	LD h=(b-a)/n;
	\int_a^b f(x)dx = h/3*sigma(j=1~n/2){f(x_2j-2)+4f(x_2j-1)+f(x_2j)}
}
