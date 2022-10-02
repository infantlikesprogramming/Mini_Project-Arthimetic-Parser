#include "defs.h"
#include "data.h"
#include "decl.h"
static int count=0;
// - The functions in this file will create a parse tree in a particular file
static char* tok[]={"EOF","+","-","*","/","INTLIT"};
// - primary() return struct ASTnode pointer, takes in void. This function return a left child node for the current token. It also call scan() to visit the next token.
static struct ASTnode* primary(void){
    // - declare a struct ASTnode* pointer n. 
    struct ASTnode* n;

    // - check to see if Token.token is intlit. If not, printf() error and exit(1)
    if (Token.token!=T_INTLIT){
        printf("Error: Token %s is not T_INTLIT",tok[Token.token]);
        exit(1);
    }
    // - call mkastleaf() (pass in A_INTLIT, Token.intvalue). Returned value pass to n
    n=mkastleaf(A_INTLIT, Token.intvalue);
    if (n==NULL){
        printf("mkastleaf unsuccessful.");
        exit(1);
    }
    scan(&Token);

    // - return the leaf-node n
    return n;

}

// - arithop() takes in an int and return an int. Takes in the token type and return operation.
static int arithop(int token){
    /*- use switch struct to decide operation of Token.token
    + case T_PLUS:
        return A_ADD
    ...
    default:
        printf() error wrong syntax at token...
        exit(1);
    */
    switch (token)
    {
    case T_PLUS:
        return A_ADD;

    case T_MINUS:
        return A_SUBTRACT;
    
    case T_STAR:
        return A_MULTIPIY;
    
    case T_SLASH:
        return A_DIVIDE;
    
    default:
        printf("Error token %s is not an operation, count is %d",tok[Token.token],count);
        exit(1);
    }
   

}

// - binexpr() returns a struct ASTnode pointer, takes in void. This function considers tokens and return a parse tree for an arithmetic expression.
struct ASTnode* binexpr(void){
    // - declare struct ASTnode pointers left,right
    struct ASTnode* left,*right;
    
    // - call primary() to create a leaf node (holds an intlit token). This function also call scan() to visit the next token. Returned value passed to left. If the token is not intlit, the function will exit the program
    count++;
    left=primary();
    
    // - if Token.token is EOF, end of expression, return left.
    if (Token.token==T_EOF){
        return left;
    }
    // - create int tokentype to get the current token. Assign tokentype to Token.token.
    int tokentype;
    tokentype = Token.token;
    // - assign arithop to int op to check if the current token is an operation token. If not it will exit the program
    count++;
    int op = arithop(tokentype);
    
    // - scan() the next token
    scan(&Token);

    // binexpr() to parse the tree for the rest of the input stream. Pass the tree to right
    right= binexpr();
    // - mkastnode() (pass in arithop(tokentype),left,right,0). Pass the tree to left.
    left = mkastnode(op,left,right,0);

    // - return left to return the parse tree
    return left;
 
}
