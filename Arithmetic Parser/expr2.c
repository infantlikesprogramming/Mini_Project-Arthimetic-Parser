#include "defs.h"
#include "data.h"
#include "decl.h"

// - This file contain a function that helps parse a tree with precedence in consideration
static int count=0;
// - The functions in this file will create a parse tree in a particular file
static char* tok[]={"EOF","+","-","*","/","INTLIT"};
// - static int opPrec[] 
static int OpPrec[] ={10,10,20,20,0};

// - primary() return struct ASTnode pointer, takes in void. This function return a left child node for the current token. It also call scan() to visit the next token.
static struct ASTnode* primary(void){
    // - declare a struct ASTnode* pointer n. 
    struct ASTnode* n;

    // - check to see if Token.token is intlit. If not, printf() error and exit(1)
    if (Token.token!=T_INTLIT){
        printf("Error: Token %s is not T_INTLIT\n Wrong syntax\n ",tok[Token.token]);
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

// - binexpr() return a struct ASTnode pointer, takes in an int ptp (for previous token precedence). 
struct ASTnode* binexpr(int ptp){
    // - create struct ASTnode* left, *right
    struct ASTnode *left, *right;
    count++;
    // - call primary() to initialize a leaf node, and assign it to left. At the same time the function call also, move to scan the next token.
    left = primary();

    // - declare tokentype, assign it to Token.token
    int tokentype = Token.token;

    // - in the case that tokentype = EOF, return left.
    if (tokentype==T_EOF){
        return left;
    }

    // - declare op and assign it to arithop(tokentype)
    count++;
    int op = arithop(tokentype);

    /* - conditional while loop. When ever the precedence of op is higher than ptp (OpPrec[op]>ptp), do the following:
    + scan the next token
    +  call binexpr(opPrec[op]);
    +  now that we have both left and right, call mkastnode to parse a tree, and return the tree to left
    + In the case that the next token (scanned) is EOF (end of the input stream), op cant be change since their is no op for EOF. In this case, just return left (the tree parsed) and be done with the whole process
    + change op to the op of the current token type
    */
    while (OpPrec[op]>ptp){
        scan(&Token);
        right = binexpr(OpPrec[op]);
        left = mkastnode(op,left,right,0);
        tokentype=Token.token;
        if (tokentype==T_EOF){
            return left;
        }
        op = arithop(tokentype);
        count++;
        
    }

    // - return left when the loop is finished
    return left;
}


