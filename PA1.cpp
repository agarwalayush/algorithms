#include<bits/stdc++.h>
#include<ctime>
#include<cstdlib>
using namespace std;

vector<pair<pair<double,double>,double> > blue;
vector<pair<double,double> > yellow;  // Contains the start point of all vertical red lines
vector<pair<double,double> > violet;  // Contains the end point of all vertical red lines

class node{
	public:
	double x;
	int subtree_size;
	node * left;
	node * right;
	node * parent;
	node(){
		x = -1;
		subtree_size = 0;
		left = right = NULL;
		parent = NULL;
	}	
}*root;

bool blueFunction (pair< pair<double,double>,double> i, pair< pair<double,double>,double> j) { return i.second < j.second; }
bool redFunction (pair<double,double> i, pair<double,double> j) { return i.first < j.first; }

void BST_insert(node * root, node * pt){
	//cout<<"welcome to insert function\n";
	if(root == NULL){
		//cout<<"First entry\n";
		root = pt;
		root->subtree_size = 1;
		return;
	}
	root->subtree_size ++;
	if(pt->x <= root->x){
		if(root->left == NULL){
			//cout<<"Insert left\n";
			pt->parent = root;
			root->left = pt;
		}
		else BST_insert(root->left, pt);
	}
	else{
		if(root->right == NULL){
			//cout<<"Insert right\n";
			pt->parent = root;
                        root->right = pt;
                }
                else BST_insert(root->right, pt);
	}
}

void BST_delete(node * root, double key){
	//cout<<"Welcome to delete function\n";
	if(root == NULL) return;
	root->subtree_size --;
	if(key == root->x){
		if(root->left == NULL){
			if(root->parent == NULL) ;
			else if(root->parent->left == root)	root->parent->left = root->right;
			else	root->parent->right = root->right;
			delete(root);
			root = NULL;
		}
		else if(root->right == NULL){
			if(root->parent == NULL) ;
			else if(root->parent->left = root)   root->parent->left = root->left;
                        else    root->parent->right = root->left;
			delete(root);
			root = NULL;
                }	
		else{
			node * ptr = root->left;
			while(ptr!= NULL){
				ptr->subtree_size --;
				ptr = ptr->right;
			}		
			root->x = ptr->x;
			ptr->parent->right = ptr->left;
			delete(ptr);
			ptr = NULL;
		}	
	}
	else if(key < root->x) BST_delete(root->left, key);
        else BST_delete(root->right, key);
}

long long int BST_count(node * root, double x1, double x2){
	long long int count = 0;
	if(root == NULL)	return 0;
	map<node *,bool> m;
	node * ptr_x1 = root;
	while(ptr_x1 != NULL){
		if(ptr_x1->x == x1) break;
		else if(ptr_x1->x > x1){
			m[ptr_x1] = 1;
			ptr_x1 = ptr_x1->left;
		}
		else{
			ptr_x1 = ptr_x1->right;
		}	
	}
	node * LCA = NULL;
	node * ptr_x2 = root;
	while(ptr_x2 != NULL){
		if(ptr_x2->x == x2) break;
		if(m[ptr_x2]==1) LCA = ptr_x2;
                if(ptr_x2->x < x2){
                        ptr_x2 = ptr_x2->right;
                }
                else{
                        ptr_x2 = ptr_x2->left;
                }
        }
	if(ptr_x1 !=NULL && ptr_x1->right != NULL) count = count + ptr_x1->right->subtree_size;
	while(ptr_x1->parent != LCA && ptr_x1->parent != NULL){
		count++;
		if(ptr_x1->parent->left = ptr_x1)	count = count + ptr_x1->parent->right->subtree_size;
	}
	count ++; // To include LCA
	if(ptr_x2 != NULL && ptr_x2->left !=NULL) count = count + ptr_x2->left->subtree_size;
	while(ptr_x2->parent != LCA && ptr_x2->parent != NULL){
                count++;
                if(ptr_x2->parent->right = ptr_x2)       count = count + ptr_x2->parent->left->subtree_size;
        }
	return count;
}

long long int FindCount(){
	vector<pair<pair<double,double>,double> >::iterator b=blue.begin();
	vector<pair<double,double> >::iterator y=yellow.begin();
	vector<pair<double,double> >::iterator v=violet.begin();
	long long int count = 0;
	while((b!=blue.end())&&(v!=violet.end())){
		if(y!=yellow.end()){
			node *pt = new node;
			pt->x = (*y).second;
			pt->left = pt->parent = pt->right = NULL;
			pt->subtree_size = 0;
			//cout<<"before insert\n";
			BST_insert(root,pt);
			++y;
		}
		while(((*b).second<(*y).first)&&(b!=blue.end())){
			++b;
		}
		while(((*b).second <= (*(y+1)).first)&&(b!=blue.end())){
			//cout<<"before count\n";
			count = count + BST_count(root,(*b).first.first, (*b).first.second);
			++b;
		}
		while(((*b).second>(*v).first)&&(v!=violet.end())){
			//cout<<"before delete\n";
			BST_delete(root,(*v).second);
			++v;
		}
	}	
	return count;
}

int main(){
	srand (static_cast <unsigned> (time(0)));
	long long int n,count;
	double ans = 0.0;
	double max = 1.0;
	double min = 0.0;
	pair<pair<double,double>,double> A1;
	pair<double,double> A2;
	pair<double,double> A3;
	scanf("%lld",&n);
	long long int test_cases = 100000000/n;
	while(test_cases --){
			root = NULL;
// Blue lines input is taken first, in the format x1 x2 y\n
		for(int i=0; i<n; i++){
			A1.first.second = ((double) rand()*(max-min)/(double)RAND_MAX-min);
			A1.first.first = ((double) rand()*(A1.first.second-min)/(double)RAND_MAX-min);
			A1.second = ((double) rand()*(max-min)/(double)RAND_MAX-min);
			blue.push_back(A1);
			//printf("%lf %lf %lf\n",A1.first.first, A1.first.second, A1.second);
		}
// Red lines input is taken second, in the format y1 y2 x\n
		for(int i=0; i<n; i++){
			A3.first = ((double) rand()*(max-min)/(double)RAND_MAX-min);
                	A2.first = ((double) rand()*(A3.first-min)/(double)RAND_MAX-min);
                	A3.second = ((double) rand()*(max-min)/(double)RAND_MAX-min);
			A2.second = A3.second;
			yellow.push_back(A2);
			violet.push_back(A3);
			//printf("%lf %lf %lf %lf\n",A2.first, A2.second,A3.first,A3.second);
        	}
// Sort all the three vectors based on their Y-coordinates
		sort (blue.begin(), blue.end(), blueFunction);
		sort (yellow.begin(), yellow.end(), redFunction);
		sort (violet.begin(), violet.end(), redFunction);
		count = FindCount();
		printf("%lld\n", count);
		ans = ans + count;
	}
	printf("Averaged number of intersections for n = %lld is %lf\n",n,ans/n);
	return 0;
}
