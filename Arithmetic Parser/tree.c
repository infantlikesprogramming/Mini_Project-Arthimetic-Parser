#include "defs.h"
#include "data.h"
#include "decl.h"

// - This file declare's three function for use

// - mkastnode() returns struct ASTnode pointer, takes in int op, struct ASTnode pointer left, struct ASTnode pointer right, int intvalue. It creates a node of struct ASTnode
struct ASTnode* mkastnode(int op, struct ASTnode* left, struct ASTnode* right, int intvalue){
    // - create a struct ASTnode pointer n
    struct ASTnode* n;
    // - malloc a struct pointer to n
    n= (struct ASTnode*) malloc(sizeof(struct ASTnode));
    // - if n is null. printf() malloc is unsuccesfull. exit(1)
    if (n==NULL){
        printf("malloc() not successful.");
        exit(1);
    }
    // - assign arguments to fields of *n.
    n->op=op;
    n->left=left;
    n->right=right;
    n->intvalue=intvalue;

    // - return the node created
    return n;
}

// - mkastleaf() returns struct ASTnode pointer, takes in int op, int intvalue. This function creates a leaf node (no child node).
struct ASTnode* mkastleaf(int op, int intvalue){
    return mkastnode(op, NULL, NULL, intvalue);
}
