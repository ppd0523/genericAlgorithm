#ifndef _FUNCTION_H_
#define _FUNCTION_H_

typedef struct Node{
	float x;
	float y;
	char name;
} Node;
typedef struct Chromosome{
	Node gene[8];
	float length;
} Chromosome;

Chromosome* createChromosome(void);
float getLength(Node A,Node B);
void setGene(Chromosome *chromosome,Node A, Node B, Node C, Node D, Node E, Node F, Node G,Node H);
void printChromosomeInfo(Chromosome* chromosome);
void swapGene(Chromosome *A,Chromosome* B,int num);
void mutate(Chromosome *A);
Chromosome mating(Chromosome* A, Chromosome* B);
void sort(Chromosome *A[],int size);
#endif