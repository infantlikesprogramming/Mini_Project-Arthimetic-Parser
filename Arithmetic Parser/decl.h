int scan(struct token *t);
struct ASTnode* mkastnode(int op, struct ASTnode* left, struct ASTnode* right, int intvalue);
struct ASTnode* mkastleaf(int op, int intvalue);
struct ASTnode* binexpr(int ptp);
int interpretAST(struct ASTnode* n);