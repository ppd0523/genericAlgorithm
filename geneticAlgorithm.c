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
	printf("\t\t%d세대\n",generation);
	fputs("부 :",stdout);
	printChromosomeInfo(parent[0]);
	fputs("\n모 :",stdout);
	printChromosomeInfo(parent[1]);

	for(generation=1 ; generation<1000 ; ++generation){
	// crossing over 25%, 2/8
		
		// 자식 8마리에게 유전시킴
		for(i=0 ; i<8 ; ++i){
			*child[i] = mating(parent[0],parent[1]);

			// 2% 확률로 돌연변이
			if( rand()%50 == 0)
				mutate(child[i]);

		}

		//자식들을 우수한 순서대로 정렬
		sort(child,8);

		//우수한 2마리를 부모로 한다.
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
// 			printf("자%d:",i);
// 			printChromosomeInfo(child[i]);
// 			puts("");
// 		}
		printf("\t\t%d세대\n",generation);
		fputs("부 :",stdout);
		printChromosomeInfo(parent[0]);
		fputs("\n모 :",stdout);
		printChromosomeInfo(parent[1]);

		if(minimum < 38)
			break;
	}		

	return 0;
}
