/* a^x = b(mod m), need (a,m)=1 */
int logM(int a,int b,int m) {
	map<int,int>x;//a^0,...,a^(n-1)
	int n=sqrt(m);
	int t=1;
	for(int i=0;i<n;i++) {
		if(t==b)return i;
		if(!x.count(t))x[t]=i;
		t=mul(t,a,m);//t=t*a%m
	}
	//a^n..a^(2n-1)
	//a^2n..a^(3n-1)
	//...
	int f=inv(t,m);
	for(int i=0;i<n+1;i++) {
		if(x.count(b))return i*n+x[b];
		b=mul(b,f,m);
	}
	return -1;
}
