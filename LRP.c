#include <stdio.h>
#include <stdlib.h>


/*--------------------- FUNCTIONS ---------------------*/


// Функция начального заполнения
void StartFilling(short *a)
{

	for (int i = 0; i < 32; i++)
		a[i] = i + 6; // Вариант №6
}

// Функция вычисляющая значения элементов последоваельности
int LRP(unsigned short *a)
{

	// Неприводимый многочлен f(X) = x^16 + x^9 + x^8 + x^7 + x^6 + x^3 + x^2 + x + 1
	unsigned short Fx = 0x3CF;
	unsigned short flag = 0;

	
	if (a[0] & 0x8000)
		flag = 1;
	// alpha * S(n) = (0..10) * S(n) = S(n) * x или же << 1 или же * 2 
	unsigned short current = a[0] * 2;
	
	// Проверка на 17-ый бит
	if (flag)
	{
		current = current ^ Fx;
		flag = 0;
	}

	// S(n + k) + alpha * S(n) = S(n + k) XOR (alpha * S(n)) - сложение в поле
	current = a[6] ^ current;

	// Последний посчитаный элемент, это последний элемент массива
	// Следовательно S(n) - всегда a[0]
	for (int i = 0; i < 31; i++)
        a[i] = a[i + 1];

    a[31] = current;

  	return current;


}

/*--------------------- MAIN ---------------------*/

int main()
{

	// Элементы последовательности
	unsigned short *a = (short*)calloc(32, sizeof(short));
	// Начальное заполнение
	StartFilling(a);

	unsigned short len = 96;

	// Расчет элементов последовательности
	for (int i = 0; i < len; i++)
	{	
		if (i < 32)
			printf("%X ", a[i]);

		else
			printf("%X ", LRP(a));
	
	}

	free(a);

	return 0;
}