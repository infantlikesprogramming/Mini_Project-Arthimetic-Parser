#include "defs.h"
#include "data.h"
#include "decl.h"

// - next() that returns an int and takes in void. This function return the next character to be considered from the input stream.
static int next(void){
    // - declare int c to hold the character to be considered.
    int c;
    // - if Putback is not 0, c takes value from Putback, set Putback to 0. return c.
    if (Putback){
        c= Putback;
        Putback=0;
        return c;
    }
    //* Putback is a global int variable that takes the value of the extra character resulted from calling scanint()(all digits from intlit token are considered,extra character is popped and not a digit).

    // - Now that there is no Putback. Check if Infile is null or not. If NULL, printf() the error, then exit()
    if (Infile == NULL){
        printf("File stream error.");
        exit(1);
    }
    // - Infile is not NULL. Get the next chracter from the input stream by calling fgetc(Infile) and pass it back to c.
    c=fgetc(Infile);
    // - Now c holds the value to be considered for the current token. If c is \n, increment Line.
    if (c=='\n'){
        Line++;
    }
    //* Line holds the line number of the input file.
    // - return c to be considered regarding the current token 
    return c;
}

// - skip() that returns an int and takes in nothing. This function get the next non-special character from input stream
static int skip(void){
    // - declare int c to hold the next character
    int c;

    // - call next() and return to c to get the next character
    // * next() is a function that takes in void and return int, the next character to be considered from the input stream.
    c=next();
    /*
    - Use a Conditional loop. As long as c == ' ',/ntrf, c=next() to consider the next character. 
    */
    while(' '==c || '\n' == c || '\t' == c || '\r'==c || '\f'==c){
        c=next();
    }

    // - now that all special characters are ignored, return c for consideration
    return c;
}

// - digitIntValue() return an int, takes in a string, and a int for a character. If the character exist in that string, it will return the position (int) of the character in the string, starting from 0 to 9. If the current character does not exist in the string, it will return -1.
static int digitIntValue(char* s,int c){
    // - declare char pointer p to hold the value of c in s.
    char *p;
    // - call strchr(s,c) to get the address char c in string s. Returned address will be passed to p
    p=strchr(s,c);
    // - if p exist, return p-s (for the pos of c rel to s), else return -1
    return (p? p-s : -1);
}

// - putback() return void, takes in int c. It will record c in Putback to be considered next.
static void putback(int c){
    // Record c in global variable Putback to be considered later
    Putback = c;
}

// - scanint() returns an int (for the value of the intlit token) , takes in int c (the current digit).
static int scanint(int c){
    // - We are going to use a function to get the int value of c. So we need a variable k to hold that value. We will need a another variable val to hold the value of the current string of digits (by the arithmetic val=val*10+k).
    int k, val =0;
    // - call digitIntValue("0123456789",c) to get the int value for k.   
    //* digitIntValue("0123456789",c) takes in a string and a character. If the character exist in that string, it will return the position (int) of the character in the string, starting from 0 to 9. If the current character does not exist in the string, it will return -1.
    // -  While k is not -1 (or>=0), c=next() (to take the next character) and change value of val by mentioned arithmetic. Call k=digitIntValue("0123456789",c) to record the int value of the next digit. 
    while((k=digitIntValue("0123456789",c))>=0){
        val=val*10+k;
        c=next();
    }

    // - Now that k is <0, c is not a digit character, call putback(c) to record c in Putback to be the next character to be considered.
    putback(c);
    // - return val for the int value of the current token
    return val;
}


/* - This function return int (to confirm found token)
- it takes in a token pointer to record token state
*/
int scan(struct token *t){
    // - create int c to contain the current charactter
    int c;
    // - call a function skip() and pass returned value to c to get the next meaningful character from input stream
    c=skip();
    /*
    - switch structure on c to decide the token for current token *t
    case: EOF
        t->token=T_EOF
        return 0;
    case '+';
        t->token=T_PLUS;
        break;
    ...
    default: (This is when we consider digit and other characters)
    - if the c is digit, call scanint() (pass in c) to get the int value of the current token. Change t->token to T_INTLIT. break;
    - scanint(int c) in a function that returns the value of the current intlit token. It also pop continuos digits from the input file and put the extra character into putback.
    - When c is not a digit(). Call printf() to signal unrecognized character and call exit(1);
    */
    switch (c)
    {
    case EOF:
        t->token=T_EOF;
        return 0;
    
    case '+':
        t->token=T_PLUS;
        break;

    case '-':
        t->token=T_MINUS;
        break;

    case '*':
        t->token=T_STAR;
        break;
    
    case '/':
        t->token=T_SLASH;
        break;

    default:
        if(isdigit(c)){
            t->intvalue=scanint(c);
            t->token=T_INTLIT;
            break;
        }
        printf("Unrecognized character %c at at Line %d",c,Line);
        exit(1);
    }
    // - return 1 since switch worked 
    return 1;

}