LL cross(PT x,PT a,PT b){
	return (a-x)^(b-x);
}
void convex_hull(PT t[], int n){
	sort(t,t+n);
	top=0;
	for(int i=0;i<n;i++){
		while(top>=2&&cross(s[top-2],s[top-1],t[i])<=0)top--;
		s[top++]=t[i];
	}
	for(int i=n-2,k=top+1;i>=0;i--){
		while(top>=k&&cross(s[top-2],s[top-1],t[i])<=0)top--;
		s[top++]=t[i];
	}
	//top--;
}
