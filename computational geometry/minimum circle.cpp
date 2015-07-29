#include <bits/stdc++.h>
using namespace std;
struct M{double x,y;void read(){scanf("%lf%lf",&x,&y);}};
const double limit=1e-5;
M a[3],o,p;
double r;
double sdis(M a,M b)
{return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);}
M O(int i,int j){
	M o;
	o.x=(a[i].x+a[j].x)/2.0,o.y=(a[i].y+a[j].y)/2.0;
	return o;
}
void make_c(){
	double x=sdis(a[0],a[1]),y=sdis(a[2],a[1]),z=sdis(a[0],a[2]);
	if(y+z<=x+limit)r=x/4.0,o=O(0,1);
	else if(x+z<=y+limit)r=y/4.0,o=O(2,1);
	else if(x+y<=z+limit)r=z/4.0,o=O(2,0);
	else{
		M m1=O(0,1),m2=O(1,2);
		double la1=a[0].x-a[1].x,lb1=a[0].y-a[1].y,lc1=-(la1*m1.x+lb1*m1.y);
		double la2=a[1].x-a[2].x,lb2=a[1].y-a[2].y,lc2=-(la2*m2.x+lb2*m2.y);
		o.x=(lb1*lc2-lb2*lc1)/(la1*lb2-la2*lb1);
		o.y=(la1*lc2-la2*lc1)/(lb1*la2-la1*lb2);
		r=sdis(o,a[0]);
	}
}
int main()
{
	int m;
	while(~scanf("%d",&m)){
		if(m==2){o.read();p.read();printf("%.3lf\n",sqrt(sdis(o,p)/4.0));continue;}
		for(int i=0;i<3;i++)a[i].read();
		make_c();m-=3;
		while(m--)
		{
			p.read();
			if(sdis(p,o)<=r+limit)continue;
			for(int i=0;i<3;i++){
				swap(p,a[i]);make_c();
				if(sdis(p,o)<=r+limit)break;
			}
		}
		printf("%.3lf\n",sqrt(r));
	}
}
