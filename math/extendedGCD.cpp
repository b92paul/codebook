void exgcd(int a,int b,int &i,int &j,int &g){
	if(b==0){g=a;i=1;j=0;return;}
	exgcd(b,a%b,j,i,g);
	j-=(a/b)*i;
}//a*p+b*q=g, min(|p|+|q|)
int main(){
	RI(a,b);
	int p,q,g;
	exgcd(a,b,p,q,g);
	printf("%d %d %d\n",p,q,g);
}
