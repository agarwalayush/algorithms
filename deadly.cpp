#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<utility>
#include<algorithm>
using namespace std;

#define x1 first.first
#define x2 first.second
#define y second

typedef struct node {
    int x;
    int subtree_size;
    node *left;
    node *right;
} node;

node* bst=NULL;

node* nodeCreator(int key){
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


int main(){
    int n,i;
    double p,q,r;
    cin>>n;
    pair< pair<double, double>, double> b[n]; 
    pair<double, double> y[n]; 
    pair<double, double> v[n];
    for(i=0; i<n; i++){
        cin>>p>>q>>r;
        b[i].x1 = p;
        b[i].x2 = q;
        b[i].y = r;
    }
    for(i=0; i<n; i++){
        cin>>p>>q>>r;
        y[i].first = p;
        v[i].first = q;
        v[i].second = y[i].second = r;
    }
    sort(b,b+n);
    sort(y,y+n);
    sort(v,v+n);
}
