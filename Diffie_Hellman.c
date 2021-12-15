#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*---------------------- FUNCTIONS ---------------------*/

void ReverseArray(int *P)
{
	int temp;

	for (int i = 0; i<)
}

int LongAddition(int *A, int *B, int sizeA, int sizeB)
{

	int length;

	if (sizeA > sizeB)
		length = sizeA + 1;
	else
		length = sizeB + 1;

	for (int i = 0; i < length; i++)
	{
		B[i] += A[i];
		B[i + 1] += (B[i] / 10);
		B[i] %= 10;
	}

	if (B[length - 1] == 0)
		length--;

	return length;

}



/*------------------------ MAIN ------------------------*/

int main()
{

	srand(time(NULL));

	// p - big prime number
	int P[] = {5,7,8,9,6,0,4,4,6,1,8,6,5,8,0,9,7,7,1,1,7,8,5,4,9,2,5,0,4,3,4,3,9,5,3,9,2,6,6,3,4,9,\
		9,2,3,3,2,8,2,0,2,8,2,0,1,9,7,2,8,7,9,2,0,0,3,9,5,6,5,6,4,8,2,1,0,4,1};

	int *A, *B;
	A = (int*)calloc(100, sizeof(int));
	B = (int*)calloc(100, sizeof(int));

	// a - start point; x,y - random power of a
	int a = 2; 
	int x =  rand()%100, y =  rand()%100;

	a = LongAddition(A, B, 2, 3);
	for (int i = a-1; i>=0; i--);
		printf("%d", B[i]);

	return 0;

}