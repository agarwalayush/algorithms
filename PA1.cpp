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

node * BST_insert(node * root, double key){
	//cout<<"welcome to insert function\n";
	node *pt = new node;
        pt->x = key;
        pt->left = pt->parent = pt->right = NULL;
        pt->subtree_size = 1;
	if(root == NULL){
		//cout<<"First entry\n";
		root = pt;
		//cout<<"Assignment done\n";
		return root;
	}
	root->subtree_size ++;
	if(key <= root->x){
		if(root->left == NULL){
			//cout<<"Insert left\n";
			pt->parent = root;
			root->left = pt;
		}
		else BST_insert(root->left, key);
	}
	else{
		if(root->right == NULL){
			//cout<<"Insert right\n";
			pt->parent = root;
                        root->right = pt;
                }
                else BST_insert(root->right, key);
	}
	return root;
}

node * BST_delete(node * root, double key){
	//cout<<"Welcome to delete function\n";
	if(root == NULL) return NULL;
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
	return root;
}

long long int BST_count(node * root, double x1, double x2){
	//cout<<"Welcome to BST_count\n";
	long long int count = 0;
	if(root == NULL)	return 0;
	map<node *,bool> m;
	node * ptr_x1 = root;
	//cout<<"Before while 1\n";
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
	//cout<<"Before while 2\n";
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
	//cout<<"After while 2\n";
	node * ptr = LCA;
	if(ptr == root){
		count = count + 1 + BST_count(root->left, x1, 2.0) + BST_count(root->right, x2, -1.0);
		return count;
	}
	//cout<<"LCA is not root\n";
	while(ptr!=NULL){
                if(ptr->x == x1){ 
                        count = (ptr->right == NULL)? count +1 : count + ptr->right->subtree_size +1;
                        break;
                }
                else if(ptr->x < x1){
                        ptr = ptr->right;
                }
                else{
                        count = (ptr->right == NULL)? count +1 : count + ptr->right->subtree_size +1;
			ptr = ptr->left;
                }
        }
	//cout<<"After while 3\n";
	ptr = LCA;
	while(ptr!=NULL){
		if(ptr->x == x2){
			count = (ptr->left == NULL)? count +1 : count + ptr->left->subtree_size +1;
			break;
		}
		else if(ptr->x > x2){
			ptr = ptr->left;
		}
		else{
			count = (ptr->left == NULL)? count +1 : count + ptr->left->subtree_size +1;
			ptr = ptr->right;
		} 
	}
	//cout<<"After while 4\n";
	count --; // As LCA would have been included twice
	return count;
}

long long int FindCount(){
	vector<pair<pair<double,double>,double> >::iterator b=blue.begin();
	vector<pair<double,double> >::iterator y=yellow.begin();
	vector<pair<double,double> >::iterator v=violet.begin();
	long long int count = 0;
	while(b!=blue.end()){
		if(y!=yellow.end() && (*b).second >= (*y).first){
			//cout<<"before insert\n";
			root = BST_insert(root,(*y).second);
			++y;
		}
		while(((*b).second>(*v).first)&&(v!=violet.end())){
			//cout<<"before delete\n";
			root = BST_delete(root,(*v).second);
			++v;
		}
		count = count + BST_count(root,(*b).first.first, (*b).first.second);
		++b;
		//cout<<"The big while last step\n";
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
	long long int test_cases = 1 ;//100000000/n;
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
