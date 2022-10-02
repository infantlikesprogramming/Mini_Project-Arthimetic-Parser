#include "defs.h"
#include "data.h"
#include "decl.h"

// - This file contain functions that will interpret the parse tree.
static char* operation[]={"+","-","*","/"};
// - interpretAST return an int, takes in a struct ASTnode pointer n(parsed tree);
int interpretAST(struct ASTnode* n){
    // - declare int leftval, rightval to hold the value of the (parsed) subtrees.
    int leftval, rightval;
    
    // - if n->left, leftval=interpretAST(n->left) to get the value of the left subtree
    if (n->left){
        leftval=interpretAST(n->left);
    }
    if (n->right){
        rightval=interpretAST(n->right);
        printf("Doing %d %s %d\n ",leftval, operation[n->op],rightval);
    }
    // - if n->right ...

    // - if n->op == A_INTLIT, print() the intvalue
    if(n->op==A_INTLIT){
        printf("int value is %d\n", n->intvalue);
    }

    /*
    - Use the switch structure on n->op to decide what operation result to return
    case A_ADD:
        return leftval+rightval
    ...
    ...
    */
    switch (n->op)
    {
    case A_ADD:
        return leftval + rightval;
    
    case A_SUBTRACT:
        return leftval - rightval;

    case A_MULTIPIY:
        return leftval * rightval;

    case A_DIVIDE:
        return leftval / rightval;

    case A_INTLIT:
        return n->intvalue;

    default:
        printf("Can't interpret the node/tree where n->op is %s\n",operation[n->op]);
        exit(1);
    }
};