void split(node *now,int x,node* &a,node* &b){
	//split first x nodes
	if(now==nil){a=b=nil;return;}
	now->sign_down();
	if(now->L->size+1 <= x){
		a=now;
		split(now->R,x-now->L->size-1,a->R,b);
		a->update();
	}
	else{
		b=now;
		split(now->L,x,a,b->L); 
		b->update();
	}
}
node* merge(node *a,node *b){
	if(a==nil)return b;
	else if(b==nil)return a;
	if( b->hval <= a->hval){
		a->sign_down();
		a->R = merge(a->R,b);
		a->update();
		return a;
	}
	else{
		b->sign_down();
		b->L = merge(a,b->L);
		b->update();
		return b;
	}
}
