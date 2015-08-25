#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<utility>
#include<algorithm>
#include<ctime>
#include<time.h>
using namespace std;

#define x1 first.first
#define x2 first.second
#define y second
long long int total=0;
pair< pair<double, double>, double > b[10000000]; 
pair<double, double> y[10000000]; 
pair<double, double> v[10000000];

typedef struct node {
    double x;
    int subtree_size;
    node *left;
    node *right;
} node;

bool blueFunction (pair< pair<double,double>,double> i, pair< pair<double,double>,double> j) { return i.second < j.second; }
bool redFunction (pair<double,double> i, pair<double,double> j) { return i.first < j.first; }
node* bst=NULL;

node* nodeCreator(double key){
    node* temp;
    temp=(node*)malloc(sizeof(node));
    temp->x = key;
    temp->left = NULL;
    temp->right = NULL;
    temp->subtree_size = 1;
    return temp;
}

void insert_key(double key){
    node *parent,*root;
    parent=root=bst;
    while(root!= NULL){
        parent=root;
        root->subtree_size++;
        if(key > root->x)
            root = root->right;
        else if(key < root->x)
            root = root->left;
        else{
            return ;
        }

    }
    if(parent != NULL){
        if(key > parent->x)
            parent->right = nodeCreator(key);
        else
            parent->left = nodeCreator(key);
    }else
        bst = nodeCreator(key);
}

void delete_key(double key){
    node* root=bst;
    while(root->x != key){
        root->subtree_size--;
        if(key > root->x)
            root = root->right;
        else if(key <root->x)
            root = root->left;
    }
    root->subtree_size--;
}

int size(node* t){
    if(t == NULL)
        return 0;
    else return t->subtree_size;
}


int greater_than(double x){
 node *root=bst;
    int sum=0;
    while(root != NULL){
        if(x >= root->x){
            root=root->right;
        }
        else {
            sum += size(root) - size(root->left) ;
            root = root->left;
        }
    }
    return sum;
}

int greater_(double x){
 node *root=bst;
    int sum=0;
    while(root != NULL){
        if(x > root->x){
            root=root->right;
        }
        else {
            sum += size(root) - size(root->left) ;
            root = root->left;
        }
    }
    return sum;
}

int search(double x_first, double x_second){
    return greater_(x_first) - greater_than(x_second);
}

int findtotal(int n,pair<pair<double,double>, double > *b, pair<double,double> *y, pair<double,double> *v){
    int i,j,k,temp;//i for b, j for y, k for v
    i=j=k=0;
    while(i<n){
        while(j<n && b[i].y >= y[j].first){
            insert_key(y[j].second);
            j++;
        }
        while(k<n && b[i].y > v[k].first){
            delete_key(v[k].second);
            k++;
        }
        temp=search(b[i].x1,b[i].x2);
        total+=temp;
        i++;
    }
}

int delete_tree(node* root){
    if(root == NULL) return 0;
    if(root->left != NULL)
        delete_tree(root->left);
    if(root->right != NULL)
        delete_tree(root->right);
    delete(root);
    root=NULL;
    return 0;
}

int main(){
    srand (static_cast <unsigned> (time(0))); 
    std::ios_base::sync_with_stdio(false);
    int n,i,t=0;
    clock_t begin,e;
    time_t start, end;
    double p,q,r,total_time=0;
    cin>>n;
    int testcase=10000000/n;
    long long answer=0;
    while(t < testcase){
        t++;
        for(i=0; i<n; i++){
            p = ((double) rand()/(double)RAND_MAX);
            q = ((double) rand()/(double)RAND_MAX);
            r = ((double) rand()/(double)RAND_MAX);
            b[i].x1 = min(p,q);
            b[i].x2 = max(p,q);
            b[i].y = r;
        }
        for(i=0; i<n; i++){
            p = ((double) rand()/(double)RAND_MAX);
            q = ((double) rand()/(double)RAND_MAX);
            r = ((double) rand()/(double)RAND_MAX);
            y[i].first = min(p,q);
            v[i].first = max(p,q);
            v[i].second = y[i].second = r;
        }
        time(&start);
        //begin = clock();
        sort(b,b+n, blueFunction);
        sort(y,y+n,redFunction);
        sort(v,v+n, redFunction);
        findtotal(n,b,y,v);
        time(&end);
        //e = clock();
        total_time+=difftime(end,start);
        answer+=total;
        delete_tree(bst);
        bst=NULL;
        total=0;
    }
    cout<<answer*(1.0)/testcase<<endl;
    cout<<"time elapsed "<<total_time/testcase<<endl;
}

