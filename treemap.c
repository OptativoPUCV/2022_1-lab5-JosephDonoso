#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap* map = (TreeMap* ) malloc( sizeof(TreeMap) ); 
    map->root = NULL;
    map->current = NULL;
    map->lower_than = lower_than;
    return map;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    
    if( !tree->root ){
        tree->root = createTreeNode( key, value );
    }
    else{
        tree->current = tree->root;
        while( tree->current ){
        
            if ( is_equal(tree, tree->current->pair->key, key) ){
                return;
            } 

            if( tree->lower_than( tree->current->pair->key, key) ){
                if( !tree->current->right ){
                    tree->current->right = createTreeNode( key, value );
                    tree->current->right->parent = tree->current;
                    tree->current = tree->current->right;
                    return;
                }
                tree->current = tree->current->right;
            }
            else{
                if( !tree->current->left ){
                    tree->current->left = createTreeNode( key, value );
                    tree->current->left->parent = tree->current;
                    tree->current = tree->current->left;
                    return;
                }
                tree->current = tree->current->left;
            }
        
        } 
    }

    


    
}

TreeNode * minimum(TreeNode * x){
    while( x->left ){
        x = x->left;
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    if( !node->left && !node->right){
        if( tree->lower_than( node->parent->pair->key, node->pair->key ) ){
            node->parent->right = NULL;
        }
        else{
            node->parent->left = NULL;
        }
    }
    else if( node->left && node->right ){
        TreeNode* nodeAux = minimum(node);
        node->pair = nodeAux->pair;
        removeNode( tree, nodeAux );
    }
    else{

    }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    tree->current = tree->root;
    while( tree->current ){

        if ( is_equal(tree, tree->current->pair->key, key) ) return (Pair* ) tree->current->pair;

        if( tree->lower_than( tree->current->pair->key, key)){
            tree->current = tree->current->right;
        }
        else{
            tree->current = tree->current->left;
        }
        
    } 
    return NULL;
    
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
