#include <stdio.h>
#include <stdlib.h>


/*----------------------------- FUNCTIONS ---------------------*/

int EulersAlgorithm(int a, int b)
{

	int remainder = a%b; // remainder of the devision 

	while (remainder != 0)
	{

		printf("\n\n%d = %d * %d + %d", a, b, a/b, remainder); // print temporary result

		a = b; // change the numerator
		b = remainder; // change the denumerator ande save last remainder
		remainder = a%b; // calculate new remainder

	}

	return b; // output last (non zero) remainder, that will be the greatest common divisor

}


int ExtendedEulersAlgprithm(int a, int b, int d)
{

	int q, r, x, y; // q = a/b; r = a%b; x,y - solutions of the equation
	int old_a = a, old_b = b; // save start values
	int x2 = 1, x1 = 0, y2 = 0, y1 = 1; // start coefficients

	while (b > 0)
	{

		// calculate coefficients
		q = a / b;
		r = a % b;
		x = x2 - q * x1; 
		y = y2 - q * y1; 

		// swap them for next cyrcle  
		a = b;
		b = r; 
		x2 = x1;
		x1 = x;
		y2 = y1;
		y1 = y;

	}

	printf("\n%d = %d * %d + %d * %d\n",  d, old_a, x2, old_b, y2); // print final result


	// x ≡ a^(-1)(mod m)
	if (x2 > 0)
		return x2;
	if (x2 < 0)
		return (old_b + x2);

}


/*-------------------------------- MAIN -----------------------*/

int main()
{

	// a - 1st argument, m - module, d - greatest common divisor (short arithmetic), r - reverse element value
	int x, m, d, r;

	printf("Input x: ");
	scanf("%d", &x);
	printf("Input modul value: ");
	scanf("%d", &m);

	d = EulersAlgorithm(x, m); // calculate GCD (short arithmetic)
	printf("\n\nGCD result: %d\n", d);

	if (d > 1) {printf("Does not exist!\n");} // if d > 1, x has got divisor of 0, wich is not null
	else
	{
		r = ExtendedEulersAlgprithm(x, m, d); // calculate r with help of extended euler's algorithm
		printf("\nReverse element: r = %d\n", r);
	}

	return 0;

}