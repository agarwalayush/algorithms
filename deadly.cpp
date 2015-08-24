#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<utility>
#include<algorithm>
using namespace std;

#define x1 first.first
#define x2 first.second
#define y second
long long int total=0;
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
    //cout<<"inserting key "<<key<<endl;
    parent=root=bst;
    while(root!= NULL){
        parent=root;
        root->subtree_size++;
        if(key > root->x)
            root = root->right;
        else
            root = root->left;
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
    //cout<<"deleting key "<<key<<endl;
    node* root=bst;
    while(root->x != key){
        root->subtree_size--;
        if(key > root->x)
            root = root->right;
        else
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
        //cout<<"inside the loop of greater_than "<<root->x<<" "<<x<<endl;
        if(x > root->x) root=root->right;
        else {
            sum += size(root->right) + 1;
            root = root->left;
        }
    }
    return sum;
}

int search(double x_first, double x_second){
    return greater_than(x_first) - greater_than(x_second);
}

int findtotal(int n,pair<pair<double,double>, double > *b, pair<double,double> *y, pair<double,double> *v){
    int i,j,k,temp;//i for b, j for y, k for v
    i=j=k=0;
    while(i<n){
        while(j<n && b[i].y >= y[j].first){
            insert_key(y[j].second);
          //  cout<<"key is inserted and blue value was "<<b[i].y<<endl;
            j++;
        }
        while(k<n && b[i].y > v[k].first){
            delete_key(v[k].second);
            k++;
          //  cout<<"key deleted"<<endl;
        }
        temp=search(b[i].x1,b[i].x2);
        total+=temp;
        i++;
        //cout<<"incrementing blue and search count was "<<temp<<endl;
    }
}

int main(){
    srand (static_cast <unsigned> (time(0))); 
    int n,i;
    double p,q,r;
    cin>>n;
    pair< pair<double, double>, double > b[n]; 
    pair<double, double> y[n]; 
    pair<double, double> v[n];
    for(i=0; i<n; i++){
        //cin>>p>>q>>r;
        p = ((double) rand()/(double)RAND_MAX);
        q = ((double) rand()/(double)RAND_MAX);
        r = ((double) rand()/(double)RAND_MAX);
        b[i].x1 = min(p,q);
        b[i].x2 = max(p,q);
        b[i].y = r;
    }
    for(i=0; i<n; i++){
        //cin>>p>>q>>r;
        p = ((double) rand()/(double)RAND_MAX);
        q = ((double) rand()/(double)RAND_MAX);
        r = ((double) rand()/(double)RAND_MAX);
        y[i].first = min(p,q);
        v[i].first = max(p,q);
        v[i].second = y[i].second = r;
    }
    //for(i=0; i<n; i++)
    //    cout<<"blue "<<b[i].x1<<" "<<b[i].x2<<" "<<b[i].y<<endl;
    sort(b,b+n, blueFunction);
    sort(y,y+n,redFunction);
    sort(v,v+n, redFunction);
    /*for(i=0; i<n; i++)
        cout<<"blue "<<b[i].x1<<" "<<b[i].x2<<" "<<b[i].y<<endl;
    for(i=0; i<n; i++)
        cout<<"yellow "<<y[i].first<<" "<<y[i].second<<endl;
    for(i=0; i<n; i++)
        cout<<"violet "<<v[i].first<<" "<<v[i].second<<endl;
    */
    findtotal(n,b,y,v);
    cout<<total<<endl;
}
