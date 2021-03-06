#include<bits/stdc++.h>
#include<ctime>
#include<cstdlib>
using namespace std;

#define tr(c,i) for(typeof(c.begin()) i = (c).begin(); i != (c).end(); i++)
#define DEBUG_MAIN 0
#define DEBUG_INSERT 0
#define DEBUG_SEARCH 0 
#define DEBUG_DELETE 0
#define DEBUG_COUNT 0
#define DEBUG_FINDCOUNT 0
#define DEBUG_BRUTE 1

vector<pair<pair<double,double>,double> > blue;
vector<pair<double,double> > yellow;  // Contains the start point of all vertical red lines
vector<pair<double,double> > violet;  // Contains the end point of all vertical red lines
vector<pair<pair<double,double>,double> > red;

class node{
	public:
	double x;
	int subtree_size;
	int count;
	node * left;
	node * right;
	node * parent;
	node(){
		count = 1;
		x = -1;
		subtree_size = 0;
		left = right = NULL;
		parent = NULL;
	}	
}*root;

bool blueFunction (pair< pair<double,double>,double> i, pair< pair<double,double>,double> j) { return i.second < j.second; }
bool redFunction (pair<double,double> i, pair<double,double> j) { return i.first < j.first; }

node * BST_search(node * root, double key){
	if(DEBUG_SEARCH) 	cout<< "Welcome to Search\n";
	node * ptr = root;
	while(ptr!=NULL){
		if(ptr->x == key)	return ptr;
		else if(ptr->x > key)	ptr = ptr->left; 
		else  ptr = ptr->right;
	}
	return NULL;
}

node * BST_insert(node * root, double key){
	if(DEBUG_INSERT)	cout<<"key inserted : "<<key<<endl;
	if(DEBUG_INSERT)	cout<<"welcome to insert function\n";
	if(root == NULL){
		node *pt = new node;
        	pt->x = key;
        	pt->left = NULL;
        	pt->parent = NULL;
        	pt->right = NULL;
        	pt->subtree_size = 1;
		pt->count =1;
		if(DEBUG_INSERT)	cout<<"First entry\n";
		root = pt;
		if(DEBUG_INSERT)	cout<<"Assignment done\n";
		return root;
	}
	root->subtree_size ++;
	if(key <= root->x){
		if(root->left == NULL){
			node *pt = new node;
        		pt->x = key;
        		pt->left = NULL;
        		pt->right = NULL;
        		pt->subtree_size = 1;
			pt->count =1;
			if(DEBUG_INSERT)	cout<<"Insert left\n";
			pt->parent = root;
			root->left = pt;
		}
		else BST_insert(root->left, key);
	}
	else{
		if(root->right == NULL){
			node *pt = new node;
        		pt->x = key;
        		pt->left = NULL;
 			pt->count =1;
       			pt->right = NULL;
        		pt->subtree_size = 1;
			if(DEBUG_INSERT)	cout<<"Insert right\n";
			pt->parent = root;
                        root->right = pt;
                }
                else BST_insert(root->right, key);
	}
	return root;
}

node * BST_delete(node * root, double key){
	if(DEBUG_DELETE) cout<<"Key to be deleted : "<<key<<"\n";
	if(root == NULL) return NULL;
	root->subtree_size --;
	if(key == root->x){
		if(root->left == NULL){
			if(DEBUG_DELETE) cout<<"Inside left\n";
			node *ptr = root;
			if(ptr->parent == NULL){
				if(DEBUG_DELETE)	cout<<"1\n";
				root = ptr->right;
				if(root	!= NULL)	root->parent = NULL;
			}
			else if(ptr->parent->left == ptr){
				if(DEBUG_DELETE)	cout<<"2\n";
				root = ptr->right;
				ptr->parent->left = ptr->right;
				if(ptr->right != NULL)	ptr->right->parent = ptr->parent;
			}
			else{
				if(DEBUG_DELETE)	cout<<"3\n";
				root = ptr->right;
				ptr->parent->right = ptr->right;
				if(ptr->right != NULL)	ptr->right->parent = ptr->parent;
			}
			double new_value = (root != NULL)?root->x : -1.0;
			if(DEBUG_DELETE) cout<<"Key replaced with : "<<new_value<<"	Key deleted : "<<ptr->x<<"\n";
			free(ptr);
			ptr = NULL;
		}
		else if(root->right == NULL){
			if(DEBUG_DELETE) cout<<"Inside right\n";
			node *ptr = root;
			if(ptr->parent == NULL){
				if(DEBUG_DELETE) 	cout<<"1\n";
				root = ptr->left;
				if(root != NULL)	root->parent = NULL;
			}
			else if(ptr->parent->left == ptr){
				root = ptr->left;
				ptr->parent->left = ptr->left;
				if(ptr->left != NULL)	ptr->left->parent = ptr->parent;
			}
                        else{
				root = ptr->left;
				ptr->parent->right = ptr->left;
				if(ptr->left != NULL)	ptr->left->parent = ptr->parent;
			}
			double new_value = (root != NULL)?root->x : -1.0;
                        if(DEBUG_DELETE) cout<<"Key replaced with : "<<new_value<<"	Key deleted : "<<ptr->x<<"\n";
			free(ptr);
			ptr = NULL;
                }		
		else{
			if(DEBUG_DELETE) cout<<"inside Else\n";
			node * ptr = root->left;
			if(ptr->right==NULL){
				if(DEBUG_DELETE)	cout<<"Inside If\n";
				root->x = ptr->x;
				root->count = ptr->count;
				root->left = ptr->left;
				if(root->left != NULL)	root->left->parent = root;
			}
			else{	
				if(DEBUG_DELETE) cout<<"inside Else\n";
				while(ptr->right!= NULL){
					ptr->subtree_size --;
					ptr = ptr->right;
				}
				root->count = ptr->count;
				while(ptr->right!= NULL){
					ptr->count = ptr->count - root->count +1;
					ptr = ptr->right;
                		}		
				root->x = ptr->x;
				ptr->parent->right = ptr->left;
				if(ptr->left != NULL)	ptr->left->parent = ptr->parent;
			}
			if(DEBUG_DELETE) cout<<"Ending Else\n";
			double new_value = (root != NULL)?root->x : -1.0;
                        if(DEBUG_DELETE) cout<<"Key replaced with : "<<new_value<<"	Key deleted : "<<ptr->x<<"\n";
			free(ptr);
			ptr = NULL;
		}	
	}
	else if(key < root->x) BST_delete(root->left, key);
        else BST_delete(root->right, key);
	if(DEBUG_DELETE)        cout<<"Closing delete\n";
	return root;
}

long long int BST_count(node * root, double x1, double x2){
	if(DEBUG_COUNT)	cout<<"Welcome to BST_count\n";
	long long int count = 0;
	if(root == NULL)	return 0;
	map<node *,bool> m;
	node * ptr_x1 = root;
	if(DEBUG_COUNT)	cout<<"Before while 1\n";
	while(ptr_x1 != NULL){
		if(DEBUG_COUNT)	cout<<"in x1 locating loop of count\n";
		m[ptr_x1] = 1;
		if(ptr_x1->x == x1) break;
		else if(ptr_x1->x > x1){
			if(DEBUG_COUNT) cout<<"WHAT THE HELL! \n";
			ptr_x1 = ptr_x1->left;
		}
		else{
			if(DEBUG_COUNT) cout<<"I WILL HAVE TO JUNK THIS DUMB CODE\n";
			ptr_x1 = ptr_x1->right;
		}	
	}
	m[NULL] = 0;
	node * LCA = NULL;
	node * ptr_x2 = root;
	if(DEBUG_COUNT)	cout<<"Before while 2\n";
	while(ptr_x2 != NULL){
		if(DEBUG_COUNT) cout<<"in x1 locating loop of count\n";
		if(m[ptr_x2]==1) LCA = ptr_x2;
		if(ptr_x2->x == x2) break;
                else if(ptr_x2->x < x2){
			if(DEBUG_COUNT) cout<<"WHAT THE HELL!\n";
                        ptr_x2 = ptr_x2->right;
                }
                else{
			if(DEBUG_COUNT) cout<<"I WILL HAVE TO JUNK THIS CODE\n";
                        ptr_x2 = ptr_x2->left;
                }
        }
	if(DEBUG_COUNT && LCA == NULL) cout<<"LCA is NULL \n";
	if(DEBUG_COUNT)	cout<<"After while 2\n";
	node * ptr = LCA;
    //cout<< ptr->x <<endl;
    if(LCA->x >= x1 && LCA->x <= x2)
    {
        count++;
        ptr=LCA->left;    
        while(ptr!=NULL){
                    if(ptr->x == x1){ 
                            count = (ptr->right == NULL)? count +ptr->count : count + ptr->right->subtree_size +ptr->count;
                            break;
		    }
                    else if(ptr->x < x1){
                        ptr = ptr->right;
                    }
                    else{
                            count = (ptr->right == NULL)? count +ptr->count : count + ptr->right->subtree_size +ptr->count;
		     	ptr = ptr->left;
                    }
        }
    	if(DEBUG_COUNT && LCA == NULL) cout<<"LCA is NULL \n";
	    if(DEBUG_COUNT)	cout<<"After while 3\n";
	    ptr = LCA->right;
        while(ptr!=NULL){
		        if(ptr->x == x2){
			        count = (ptr->left == NULL)? count +ptr->count : count + ptr->left->subtree_size +ptr->count;
        			break;
	        	}
		        else if(ptr->x > x2){
			        ptr = ptr->left;
		        }
    		    else{
	    		    count = (ptr->left == NULL)? count +ptr->count : (count + ptr->left->subtree_size +ptr->count);
		    	    ptr = ptr->right;
		         } 
	        }   
        }
	if(DEBUG_COUNT)	cout<<"After while 4\n";
	if(DEBUG_COUNT) cout<<"Exit BST_count\n";
	return count;
}

long long int FindCount(){
	vector<pair<pair<double,double>,double> >::iterator b=blue.begin();
	vector<pair<double,double> >::iterator y=yellow.begin();
	vector<pair<double,double> >::iterator v=violet.begin();
	long long int count = 0;
	while(b!=blue.end()&& v!=violet.end()){
		while(y!=yellow.end() && (*b).second >= (*y).first){
			if(DEBUG_FINDCOUNT)	cout<<"before insert, key : "<<(*y).second<<"\n";
			double key = (*y).second;
			node * exists = BST_search(root,key);
			if(exists != NULL){
				node * p = root;
				while(p!=NULL){
					p->subtree_size++;
					if(p->x == key){
						p->count++;
						break;
					}
					else if(p->x >= key) p = p->left;
					else	p = p->right;
				}	
			}
			else{
				root = BST_insert(root,key);
			}
			++y;
		}
		while(((*b).second>(*v).first)&&(v!=violet.end())){
			if(DEBUG_FINDCOUNT)	cout<<"before delete,key : "<<(*v).second<<"\n";
			double key = (*v).second;
			node * exists = BST_search(root,key);
			if(exists != NULL){
				if(exists->count >1){
					node *p = root;
					while(p!=NULL){
                        			p->subtree_size--;
                        			if(p->x == key){
                                			p->count--;
                                			break;
                        			}
                       				else if(p->x >= key) p = p->left;
                        			else    p = p->right;
                			}
				}
				else{
					root = BST_delete(root,key);
				}
			}
			else {
				cout<<" ERROR IN CODE!!!!!!!\n";
            		}
			++v;
		}
       // cout<<"end of first iteration in FindCount"<<endl;
		count = count + BST_count(root,(*b).first.first, (*b).first.second);
		++b;
		if(DEBUG_FINDCOUNT)	cout<<"The big while last step\n";
	}	
	return count;
}

int main_test(){
    cout<<rand()<<endl<<rand()<<endl;
    node *root = new node;
    root->x =10;
    node *left = new node;
    left->x =5;
    node *right = new node;
    right->x= 15;
    root->left=left;
    root->right=right;
    left->parent=root;
    right->parent=root;
    left->left=right->left=left->right=right->right=NULL;
    BST_delete(root, 15);
}

int main_tst(){
    //int A[] = {10,5,15,2,7,12,17,1,3,6,100,-500,460,123,-46,13,8};
    
    int i = 0,n;
    cin>>n;
    int A[n];
    root = NULL;
    while(i<n){
        A[i]=rand();
        cout<<A[i]<<endl;
		root = BST_insert(root,A[i]);
		i++;
    }
    i=0;
    while(i<n){
		root = BST_delete(root,A[i]);
        i++;
    }
}

long long int brute(){
	long long int x = 0;
	vector<pair<pair<double,double>,double> >::iterator b=blue.begin();
        vector<pair<pair<double,double>,double> >::iterator r=red.begin();
	while(b!=blue.end()){
		r = red.begin();
		while(r!=red.end()){
			if(((*r).first.first<=(*b).second)&&((*r).first.second>=(*b).second)&&((*b).first.first<=(*r).second)&&((*b).first.second>=(*r).second))	x++;
			++r;
		}
		++b;	
	}
	return x;
}

int main_testing(){
	pair<pair<double,double>,double> b = make_pair(make_pair(0.5,0.7),0.3);
	pair<pair<double,double>,double> r = make_pair(make_pair(0.3,0.4),0.7);
	blue.push_back(b);
	red.push_back(r);
	cout<<"Brute force : "<<brute()<<"\n";
	pair<double,double> y = make_pair(0.3,0.7);
	pair<double,double> v = make_pair(0.4,0.7);
	violet.push_back(v);
	yellow.push_back(y);
	cout<<"Our Answer : "<<FindCount()<<"\n";
	return 0;
}

int main(){
	srand (static_cast <unsigned> (time(0)));
	long long int n,count;
	double brute_force_ans = 0.0;
	double ans = 0.0;
	double max = 1.0;
	double min = 0.0;
	pair<pair<double,double>,double> A1;
	pair<pair<double,double>,double> A4;
	pair<double,double> A2;
	pair<double,double> A3;
	scanf("%lld",&n);
	long long int test_cases = 1000000/n;
	long long int r =0;
	while(r<test_cases){
			blue.clear(); yellow.clear(); violet.clear(); 
			if(DEBUG_BRUTE)	red.clear();
			root = NULL;
// Blue lines input is taken first, in the format x1 x2 y\n
		for(int i=0; i<n; i++){
			A1.first.second = ((double) rand()*(max-min)/(double)RAND_MAX-min);
			A1.first.first = ((double) rand()*(A1.first.second-min)/(double)RAND_MAX-min);
			A1.second = ((double) rand()*(max-min)/(double)RAND_MAX-min);
			blue.push_back(A1);
			if(DEBUG_MAIN)	printf("%lf %lf %lf\n",A1.first.first, A1.first.second, A1.second);
		}
// Red lines input is taken second, in the format y1 y2 x\n
		for(int i=0; i<n; i++){
			A3.first = ((double) rand()*(max-min)/(double)RAND_MAX-min);
                	A2.first = ((double) rand()*(A3.first-min)/(double)RAND_MAX-min);
                	A3.second = ((double) rand()*(max-min)/(double)RAND_MAX-min);
			A2.second = A3.second;
			if(DEBUG_BRUTE){
				A4.first.first = A2.first;
				A4.first.second = A3.first;
				A4.second = A3.second;
				red.push_back(A4);
			}
			yellow.push_back(A2);
			violet.push_back(A3);
			if(DEBUG_MAIN)	printf("%lf %lf %lf %lf\n",A2.first, A2.second,A3.first,A3.second);
        	}
// Sort all the three vectors based on their Y-coordinates
		
        	sort (blue.begin(), blue.end(), blueFunction);
		sort (yellow.begin(), yellow.end(), redFunction);
		sort (violet.begin(), violet.end(), redFunction);
        	if(DEBUG_MAIN){
            		tr(blue,i){
                		cout<<"blue"<<" "<< (*i).first.first <<" "<< (*i).first.second<<" "<<(*i).second<<endl;
            		}
            		tr(yellow,i){
                		cout<<"yellow"<<" "<< (*i).first <<" "<< (*i).second<<endl;
            		}
            		tr(violet,i){
                		cout<<"violet"<<" "<< (*i).first <<" "<< (*i).second<<endl;
            	}
		}
		if(DEBUG_BRUTE)	brute_force_ans += brute();
		count = FindCount();
		if(DEBUG_MAIN)	printf("%lld\n", count);
		ans = ans + count;
		r++;
	}	
	printf("Averaged number of intersections for n = %lld is %lf\n",n, ans/test_cases);
	if(DEBUG_BRUTE)	printf("Brute force answer for n = %lld is %lf\n",n,brute_force_ans/test_cases);
	return 0;
}

