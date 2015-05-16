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
};

struct hash *table[TAM];

void print();
struct hash* insert(char* text, int type);

void initMe();
int genAddress();

#endif
