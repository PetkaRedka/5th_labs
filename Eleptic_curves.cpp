#include <stdio.h>
#include <stdlib.h>
#include "arifm_mirea.cpp"
#define SIZE 9

/*----------- GLOBAL CONSTANTS ---------------*/

// Значение модуля эллептической кривой
const unsigned int p[SIZE] = {0x431, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x80000000, 0x0};
// k = 2^64 + t, где t = 6
// k = 1... 61 ноль ...110
const unsigned int k[SIZE] = {0x6, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
// Коэффициенты элептической кривой
const unsigned int a[SIZE] = {0x7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
// Координаты точки P
const unsigned int Xp_start[SIZE] = {0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
const unsigned int Yp_start[SIZE] = {0xEA7E8FC8, 0x2B96ABBC, 0x9CA26712, 0x85C97F0A,
	0x0E16D19C, 0xBD631603, 0xE65147D4, 0x08E2A8A0, 0x0};


/*---------------- FUNCTIONS -----------------*/

// Вывод массива в 16-ом виде
void Print(unsigned int *a)
{
	for (int i = 8; i >= 0; i--)
		printf("%.8X", a[i]);
	printf("\n");
}

// Функция расчета наклона прямой
void CalculateS(unsigned int *S, unsigned int *Xp, unsigned int *Xq, unsigned int *Yp, unsigned int *Yq, unsigned short flag)
{

	unsigned int *Xp_temp = (unsigned int*)calloc(SIZE, sizeof(unsigned int));
	unsigned int *Yp_temp = (unsigned int*)calloc(SIZE, sizeof(unsigned int));
	unsigned int *znamenatel = (unsigned int*)calloc(SIZE, sizeof(unsigned int));

	// S = [(3*Xp^2 + a)/(2*Yp)(mod p)], если P = Q
	if (flag == 1)
	{

		unsigned int *koef = (unsigned int*)calloc(SIZE, sizeof(unsigned int));
		unsigned int *Xp_3 = (unsigned int*)calloc(SIZE, sizeof(unsigned int));
		unsigned int *Xp_3_a = (unsigned int*)calloc(SIZE, sizeof(unsigned int));

		koef[0] = 0x3;	
		// Числитель
		mulp(SIZE, Xp, Xp, p, Xp_temp);
		umn(SIZE, Xp_temp, koef, Xp_3);
		sum_mod(SIZE, Xp_3, a, p, Xp_3_a);

		koef[0] = 0x2;
		// Знаменатель
		umn(SIZE, Yp, koef, Yp_temp);
		obr(SIZE, Yp_temp, p, znamenatel);
		mulp(SIZE, Xp_3_a, znamenatel, p, S);

		free(koef);
		free(Xp_3);
		free(Xp_3_a);

	}

	else
	{

		// S = [(Yp - Yq)/(Xp - Xq)](mod p)
		raz_mod(SIZE, Yp, Yq, p, Yp_temp);
		raz_mod(SIZE, Xp, Xq, p, Xp_temp);
		obr(SIZE, Xp_temp, p, znamenatel);
		mulp(SIZE, znamenatel, Yp_temp, p, S);

	}

	free(znamenatel);
	free(Yp_temp);
	free(Xp_temp);

}

// Функция расчета нового X
void CalculateX(unsigned int *S, unsigned int *Xp, unsigned int *Xq,  unsigned int *X_res)
{


	unsigned int *S_square = (unsigned int*)calloc(SIZE, sizeof(unsigned int));
	unsigned int *X_sum = (unsigned int*)calloc(SIZE, sizeof(unsigned int));

	// Xr = (S^2 - Xp -Xq)(mod p)
	mulp(SIZE, S, S, p, S_square);
	sum_mod(SIZE, Xp, Xq, p, X_sum);
	raz_mod(SIZE, S_square, X_sum, p, X_res);

	free(S_square);
	free(X_sum);

}

// Функция расчета нового Y
void CalculateY(unsigned int *S, unsigned int *Xp, unsigned int *Yp, unsigned int *Y_res, unsigned int *X_res)
{

	unsigned int *X_raz = (unsigned int*)calloc(SIZE, sizeof(unsigned int));
	unsigned int *X_raz_S = (unsigned int*)calloc(SIZE, sizeof(unsigned int));

	// Yr = S(Xp - Xr) - Yp(mod p)
	raz_mod(SIZE, Xp, X_res, p, X_raz);
	mulp(SIZE, X_raz, S, p, X_raz_S);
	raz_mod(SIZE, X_raz_S, Yp, p, Y_res);

	free(X_raz);
	free(X_raz_S);

}

// Функция расчета новой точки
void CalculateNewPoint(unsigned int *S, unsigned int *Xp, unsigned int *Xq, unsigned int *Yp,	unsigned int *Yq)
{

	unsigned int *X_res = (unsigned int*)calloc(SIZE, sizeof(unsigned int));
	unsigned int *Y_res = (unsigned int*)calloc(SIZE, sizeof(unsigned int));

	// Вычислим наклон прямой
	// Если точки совпадают
	if ((cmp(SIZE, Xp, Xq) == 0) && (cmp(SIZE, Yp, Yq) == 0))
		CalculateS(S, Xp, Xq, Yp, Yq, 1);

	// Если не совпадают
	else
		CalculateS(S, Xp, Xq, Yp, Yq, 0);

	// Вычисляем координаты новой точки
	CalculateX(S, Xp, Xq, X_res);
	CalculateY(S, Xp, Yp, Y_res, X_res);

	// Перепишем результат
	memcpy(Xq, X_res, SIZE * sizeof(unsigned int));
	memcpy(Yq, Y_res, SIZE * sizeof(unsigned int));

	free(X_res);
	free(Y_res);

}

// Функция нахождение кратной точки
void CalculateMultiplePoint(unsigned int *S, unsigned int *Xq, unsigned int *Yq)
{

	int high_bit = 0, bit;

	for (int i = 8; i >= 0; --i) {
		for (int j = 31; j >=0 ; j--) 
		{

			bit = (k[i] >> j) & 1;

			// Ищем страший бит
			if ((bit == 1) && (high_bit == 0))
			{
			    high_bit = 1;
			    continue;
			}   

			if (bit) 
			{
				// Складываем с собой
		   		CalculateNewPoint(S, Xq, Xq, Yq, Yq);
		   		// Складываем с начальной точкой 
		   		CalculateNewPoint(S, Xp_start, Xq, Yp_start, Yq);

			}
		   	else
		   		// Складываем с собой
		   		CalculateNewPoint(S, Xq, Xq, Yq, Yq);
		   		
		}
	}

}


/*------------------- MAIN -------------------*/

int main()
{

	// Начальные Xq, Yq
	unsigned int Xq[SIZE] = {0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
	unsigned int Yq[SIZE] = {0xEA7E8FC8, 0x2B96ABBC, 0x9CA26712, 0x85C97F0A,
		0x0E16D19C, 0xBD631603, 0xE65147D4, 0x08E2A8A0, 0x0};
	// Массив для наклона прямой
	unsigned int S[SIZE] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

	CalculateMultiplePoint(S, Xp, Yp, Xq, Yq);

	printf("Q(\n X: ");
	Print(Xq);
	printf("\n Y: ");
	Print(Yq);
	printf(")\n");

	return 0;
}
