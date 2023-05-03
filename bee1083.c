#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct stack{
    char u;
    pilha v;
}*pilha;

void push(pilha* s, int u){
    pilha node = (pilha)malloc(sizeof(struct stack));
    node->u = u;
    node->v = *s;
    *s = node;
    return;
}

void pop(pilha* s){
    if(*s == NULL)
        return;
    pilha temp = *s;
    *s = (*s)->v;
    free(temp);
    return;
}

int isOperand(char c){
    if(c >= 'a' && c <= 'z')
        return 1;
    if(c >= 'A' && c <= 'Z')
        return 1;
    if(c >= '0' && c <= '9')
        return 1;
    return 0;
}

int priority(char c){
    if(c == '^')
        return 6;
    if(c == '*' || c == '/')
        return 5;
    if(c == '+' || c == '-')
        return 4;
    if(c == '>' || c == '<' || c == '=' || c == '#')
        return 3;
    if(c == '.')
        return 2;
    if(c == '|')
        return 1;
    if(c == '(' || c == ')')
        return 0;
    return -1;
}

int main(){
    pilha s = NULL;
    pilha parenteses = NULL;
    char entrada[1000];
    char posfixa[1000];
    int i, len, erro, op;

    while(scanf("%s%*c", entrada) != EOF){
        strcat(entrada, ")");
        push(&s, '(');
        push(&parenteses, '(');
        len = 0;
        erro = 0;
        op = 0;
        for(i = 0; i < strlen(entrada) && erro == 0; i++){
            if(entrada[i] == '('){
                push(&parenteses, entrada[i]);
                push(&s, entrada[i]);
            }
            else if(entrada[i] == ')'){
                while(s != NULL && s->u != '('){
                    posfixa[len++] = s->u;
                    pop(&s);
                }
                if(parenteses == NULL){
                    erro = 1;
                }
                else{
                    pop(&parenteses);
                }
                pop(&s);
           }else if(isOperand(entrada[i]) == 1){
                if(op == 0){
                    op = 1;
                }
                else{
                    erro = 1;
                }
                posfixa[len++] = entrada[i];
           }else{
                if(op == 1){
                    op = 0;
                }
                else{
                    erro = 1;
                }
                if(priority(entrada[i]) == -1){
                    erro = 2;
                }else{
                    while(priority(s->u) > 0 && priority(s->u) >= priority(entrada[i])){
                        posfixa[len++] = s->u;
                        pop(&s);
                    }
                    push(&s, entrada[i]);
                }
           }
        }
        if(parenteses != NULL && erro == 0)
            erro = 1;

        while(s != NULL){
            posfixa[len++] = s->u;
            pop(&s);
        }
        posfixa[len] = '\0';
        if(erro == 2){
            printf("Lexical Error!\n");
        }
        else{
            if(erro == 1){
                printf("Syntax Error!\n");
            }
            else{
                printf("%s\n", posfixa);
            }
        }
        while(parenteses != NULL)
            pop(&parenteses);
    }
}
