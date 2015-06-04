// Bruno Pinto Silva Cartão: 217446 bpsilva



#ifndef HASH_H_
#define HASH_H_


#define TAM 997
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

struct hash
{
struct hash *prox;
char* word;
int type;
int dataType;
int defcounter;
int natureza;
int definitionline[20];
int linenumber;
int amount_of_param;
};
int ln;

struct hash *table[TAM];

void print();
struct hash* insert(char* text, int type, int line);

void initMe();
int genAddress();

#endif
