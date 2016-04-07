#include <bits/stdc++.h>
using namespace std;
#define FOR(i,n) for(int i=0;i<n;++i)

class treap {
public:
	treap() : root(NULL) {}
	~treap() {
		destroy(root);
	}
	void insert(int val) {
		add(root,new node(val));
	}
	bool remove(int val) {
		if(find(root,val)==NULL) return false;
		del(root,val);
		return true;
	}
	int count(int val) {
		return cnt(root,val);
	}
	
	void print() {
		ptr(root);
		printf("\n");
	}
	

private:
	struct node {
		node *l,*r;
		int size,value;
		double p;
		node(int value) : l(NULL), r(NULL), size(1), value(value), p(rand()) {}
	};
	
	node *root;
	
	
	void ptr(node* root) {
		if(root==NULL) return;
		ptr(root->l);
		printf("%d ",root->value);
		ptr(root->r);
	}
	
	inline void update(node* &root) {
		if(root==NULL) return;
		int a = root->l?root->l->size:0;
		int b = root->r?root->r->size:0;
		root->size = a+b+1;
	}
	
	void split(node* root,node* &left,node* &right,int val) {
		if(root==NULL) {
			left = NULL;
			right = NULL;
			return;
		}
		if(root->value <= val) {
			split(root->r,root->r,right,val);
			left = root;
			update(root);
		}
		else {
			split(root->l,left,root->l,val);
			right = root;
			update(root);
		}
	}
	
	void merge(node *left, node *right, node* &root) {
		if(left==NULL || right==NULL) {
			root = left==NULL?right:left;
			return;
		}
		if(left->p > right->p) {
			merge(left->r,right,left->r);
			root = left;
			update(root);
		}
		else {
			merge(left,right->l,right->l);
			root = right;
			update(root);
		}
	}
	
	void add(node* &root,node* value) {
		if(root==NULL || value->p > root->p) {
			split(root,value->l,value->r,value->value);
			root = value;
		}
		else {
			if(value->value <= root->value) {
				add(root->l,value);
			}
			else {
				add(root->r,value);
			}
			
		}
		update(root);
	}
	
	void del(node* &root,int value) {
		if(root->value == value) {
			node* temp = root;
			merge(root->l,root->r,root);
			update(root);
			delete temp;
		}
		else {
			if(value<=root->value) del(root->l,value);
			else del(root->r,value);
			update(root);
		}
	}
	
	node* find(node* root, int value) {
		if(root==NULL) return NULL;
		if(root->value == value) return root;
		if(value<=root->value) return find(root->l,value);
		return find(root->r,value);
	}
	
	// return number of vertices <= val
	int cnt(node* &root,int val) {
		if(root==NULL) return 0;
		if(root->value<=val) {
			return 1+(root->l?root->l->size:0)+cnt(root->r,val);
		}
		else {
			return cnt(root->l,val);
		}
	}
	
	void destroy(node* root) {
		if(root==NULL) return;
		destroy(root->l);
		destroy(root->r);
		delete root;
	}
};

class range_query {
public:
	range_query(int y) {
		size = 1;
		while(size<y) size<<=1;
		arr = new treap[2*size];
	}
	~range_query() {
		delete[] arr;
	}
	// (x1,y1) is bottom left corner
	int query(int x1,int y1,int x2,int y2) {
		return qry(0,size,y1,y2+1,1,x2)-qry(0,size,y1,y2+1,1,x1-1);
	}
	
	void add(int x,int y) {
		y+=size;
		while(y) {
			arr[y].insert(x);
			y>>=1;
		}
		
	}
	void remove(int x,int y) {
		y+=size;
		if(arr[y].remove(x)) {
			for(y>>=1;y;y>>=1) arr[y].remove(x);
		}
	}
private:
	int size;
	treap *arr;
	
	// <b,e)
	int qry(int b,int e,int z,int k,int root,int time) {
		if(e<=z || k<=b) return 0;
		if(z<=b && e<=k) return arr[root].count(time);
		return qry(b,(b+e)/2,z,k,2*root,time)+qry((b+e)/2,e,z,k,2*root+1,time);
	}	
};



int main(void) {
	
	
}
