#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include "gene.h"

Chromosome* createChromosome(void)
{
	return (Chromosome*)malloc(sizeof(Chromosome));
}
float getLength(Node A,Node B)
{
	float x_abs, y_abs;
	float temp;

	if( A.x - B.x >= 0)
		x_abs = A.x - B.x;
	else
		x_abs = B.x - A.x;

	if( A.y - B.y >= 0)
		y_abs = A.y - B.y;
	else
		y_abs = B.y - A.y;
	
	temp = sqrtf( powf(x_abs,2) + powf(y_abs,2) );
	return temp;
}
void setLength(Chromosome *A)
{
	//set the Length of Chromosome
	int i;
	A->length=0;
	for( i=0 ; i<7 ; ++i)
		A->length += getLength(A->gene[i],A->gene[i+1]);

	A->length += getLength(A->gene[7],A->gene[0]);
}
void setGene(Chromosome *chromosome,Node A, Node B, Node C, Node D, Node E, Node F, Node G,Node H)
{
	chromosome->gene[0]=A;
	chromosome->gene[1]=B;
	chromosome->gene[2]=C;
	chromosome->gene[3]=D;
	chromosome->gene[4]=E;
	chromosome->gene[5]=F;
	chromosome->gene[6]=G;
	chromosome->gene[7]=H;
	setLength(chromosome);
}
void printChromosomeInfo(Chromosome *chromosome)
{
	int i;
	for(i=0 ; i<8 ; i++)
		printf(" %c",chromosome->gene[i].name);
	
	printf("\t%6.3f",chromosome->length);
}
void swapGene(Chromosome *A,Chromosome *B,int num)
{
	Node temp;
	temp = A->gene[num];
	A->gene[num] = B->gene[num];
	B->gene[num] = temp;
	setLength(A);
	setLength(B);
}
void mutate(Chromosome *A)
{
	int index1 = rand() % 8;
	int index2 = rand() % 8;
	Node temp;

	temp = A->gene[index1];
	A->gene[index1] = A->gene[index2];
	A->gene[index2] = temp;
	setLength(A);
}

// void swapChromosome(Chromosome** a, Chromosome** b)
// {
// 	Chromosome* temp = *a;
// 	*a = *b;
// 	*b = temp;
// }

// int findSameGene(Node* gene, Node* start, Node* end)
// {
// 	Node* itor;
// 	for (itor = start; itor != end; ++itor)
// 	{
// 		if (gene->name == itor->name)
// 			return itor - start;
// 	}
// 	return -1;
// }

// int findSameGene2(Node* gene, Chromosome* chromosome, int without)
// {
// 	int i;
// 	for (i = 0; i < without; ++i)
// 	{
// 		if (gene->name == chromosome->gene[i].name)
// 			return i;
// 	}
// 	for (i = without + 1; i < GENE_COUNT; ++i)
// 	{
// 		if (gene->name == chromosome->gene[i].name)
// 			return i;
// 	}
// 	return -1;
// }

Chromosome mating(Chromosome* A, Chromosome* B)
{
	//partially matched crossover
	Chromosome temp;
	int i, j;
	Chromosome* left = A;
	Chromosome* right = B;
	// 자름선 2개 설정
	int cut1 = rand()%8;
	int cut2 = rand()%8;

// 	if (rand() % 2)
// 		swapChromosome(&left, &right);
	
	// 자름선 cut1이 cut2 보다 작게 함
// 	if( cut1 > cut2 ){
// 		int temp = cut1;
// 		cut1 = cut2;
// 		cut2 = temp;
// 	}
// 	
// 	memcpy(temp.gene, right->gene, sizeof(right->gene));
// 	memcpy(temp.gene + cut1, left->gene + cut1, sizeof(Node) * (cut2 - cut1 + 1));
// 
// 	for (i = 0; i < GENE_COUNT; ++i)
// 	{
// 		if (i < cut1 || i > cut2)
// 		{
// 			int index = findSameGene2(&temp.gene[i], &temp, i);
// 			if (index != -1)
// 			{
// 				temp.gene[i] = right->gene[index];
// 				--i;
// 				continue;
// 			}
// 		}	
// 	}

	// 50% 로 left를 자를지 right를 자를지 정함
	if( rand()%2 == 0 ){
		Chromosome swapTemp = *left;
		*left = *right;
		*right = swapTemp;
	}
	
	temp = *right;
	
	//자른 값을 임시 염색체에 저장
	for(i=cut1 ; i <= cut2 ; ++i ){
		temp.gene[i] = left->gene[i];
	}
	
	// 잘리지 않은 B염색체의 값을 임시 염색체에 저장
	for(i=0 ; i<8 ; ++i){
		if( cut1 <= i && i <= cut2 )
			continue;

		for( j=0 ; j<8 ; ++j ){
			if(i == j)
				continue;

			if( temp.gene[i].name == temp.gene[j].name ){
				temp.gene[i] = right->gene[j];
				j = -1;
			}
		}
	}
	setLength(&temp);
	return temp;
}
void sort(Chromosome *A[],int size)
{
	int i,j;
	for(i=0 ; i<size-1 ; ++i)
		for(j=0 ; j<size-1-i ; ++j)
			if(A[j]->length > A[j+1]->length){
				Chromosome temp = *A[j];
				*A[j] = *A[j+1];
				*A[j+1] = temp;
			}
}