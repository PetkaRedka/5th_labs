#include <stdio.h>
#include <stdlib.h>
#include <time>


/*------------------------ MAIN ------------------------*/

int main()
{

	srand(time(NULL));

	// p - big prime number
	int P[] = {5,7,8,9,6,0,4,4,6,1,8,6,5,8,0,9,7,7,1,1,7,8,5,4,9,2,5,0,4,3,4,3,9,5,3,9,2,6,6,3,4,9,\
		9,2,3,3,2,8,2,0,2,8,2,0,1,9,7,2,8,7,9,2,0,0,3,9,5,6,5,6,4,8,2,1,0,4,1};

	// a - start point; x,y - random power of a
	int a = 2; 
	int x, y;

	x = rand()%100;
	y = rnad()%100;

	printf("%d %d", x, y);

	return 0;

}