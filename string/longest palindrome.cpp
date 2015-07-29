const int N=500001;
char s[N*2],c[N];
int pal[N*2],R;
int match(int a,int b,int m){
	int i=0;
	while(a-i>=0&&b+i<m&&s[a-i]==s[b+i])i++;
	return i;
}
int longest_palindrome(char c[]){
	int p,ii,m=strlen(c);
	for(int i=0;i<m;i++){
		s[i*2]='@';
		s[i*2+1]=c[i];
	}
	s[m*2]='@';m=m*2+1;
	pal[0]=0;p=R=0;
	//p=max_idx{pal[i]+i},R=max{pal[i]+i}
	for(int i=1;i<m;i++){
		ii=p-(i-p); //reflextion point
		int n=R-i;  //distance of i and pal[p]+p 
		if(i>R){ //overflow R
			pal[i]=match(i-1,i+1,m);
			R=i+pal[p=i];
		}
		else if(pal[ii]==n){ //exactly at n
			pal[i]=n+match(i-n-1,i+n+1,m);
			R=i+pal[p=i];
		}
		else pal[i]=min(pal[ii],n);
	}
	int ans=0;
	for(int i=0;i<m;i++)
		maz(ans,pal[i]);
	return ans;
}
int main(){
	scanf("%s",c);
	printf("%d\n",longest_palindrome(c));
}
