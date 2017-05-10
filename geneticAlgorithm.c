#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "gene.h"

Node A={-5,6,'A'}, B={-2,4.5,'B'}, C={3,6,'C'}, D={7,3,'D'},
	E={2.5,-1.5,'E'}, F={-3.5,-3,'F'}, G={-5,2,'G'}, H={-7,5,'H'};


int main(void)
{
	Chromosome *parent[2]={createChromosome(),createChromosome()};
	Chromosome *child[8];
	int generation=0;
	int i;
	float minimum=100.0;
	srand( (unsigned int)time(NULL) );
	
	for(i=0 ; i<8 ; ++i)
		child[i]=createChromosome();

	setGene(parent[0],E,F,G,A,C,D,H,B);
	setGene(parent[1],D,E,A,C,B,G,H,F);

// 	for(i=0 ; i<10 ; ++i){
// 		*child[i] = mating(parent[0],parent[1]);
// 		printChromosomeInfo(child[i]);
// 		puts("");
// 	}
	printf("\t\t%d����\n",generation);
	fputs("�� :",stdout);
	printChromosomeInfo(parent[0]);
	fputs("\n�� :",stdout);
	printChromosomeInfo(parent[1]);

	for(generation=1 ; generation<1000 ; ++generation){
	// crossing over 25%, 2/8
		
		// �ڽ� 8�������� ������Ŵ
		for(i=0 ; i<8 ; ++i){
			*child[i] = mating(parent[0],parent[1]);

			// 2% Ȯ���� ��������
			if( rand()%50 == 0)
				mutate(child[i]);

		}

		//�ڽĵ��� ����� ������� ����
		sort(child,8);

		//����� 2������ �θ�� �Ѵ�.
		*parent[0] = *child[0];
		*parent[1] = *child[1];

		if(minimum > child[0]->length )
			minimum = child[0]->length;

		printf("\tminimum:%6.3f\n",minimum);

		for(i=0 ; i<6 ; ++i){
			if( parent[1]->length == parent[0]->length )
				*parent[1] = *child[i+2];
			else
				break;
		}
		
// 		for(i=0 ; i<8 ; ++i){
// 			printf("��%d:",i);
// 			printChromosomeInfo(child[i]);
// 			puts("");
// 		}
		printf("\t\t%d����\n",generation);
		fputs("�� :",stdout);
		printChromosomeInfo(parent[0]);
		fputs("\n�� :",stdout);
		printChromosomeInfo(parent[1]);

		if(minimum < 38)
			break;
	}		

	return 0;
}
