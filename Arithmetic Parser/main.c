#include "defs.h"
#include "data.h"
#include "decl.h"

static char* OP[] = {"EOF","+","-","*","/","intlit"};

void init(){
    Putback=0;
    Line=1;
}

int main(int argc,char* argv[]){
    init();
    Infile = fopen(argv[1],"r");
    if(Infile==NULL){
        printf("Can't find file\n");
        exit(1);
    }
    struct ASTnode* n;
    scan(&Token);
    n=binexpr(0);
    printf("value is %d",interpretAST(n));
    return 1;
}