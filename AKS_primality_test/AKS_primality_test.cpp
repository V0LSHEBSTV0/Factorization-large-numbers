#include <iostream>
#include <string>

using namespace std;

void str_to_int(string str, int* mas);
void print_num(int* mas);
void zero_mas(int* mas, int size);
int max_long(int* x, int* y);
void copy(int* x, int* y);
void sum_short(int* x, int b, int* z);
void sum(int* x, int* y, int* z);
void diff(int* x, int* y, int* z);
void mult_short(int* x, int b, int* z);
void mult_long(int* x, int* y, int* z);
void div(int* x, int* y, int* z, int* w); 

int main() {
	string str;
	int k = 0;							// Счётчик кол-ва делителей
	bool isLess = 1;					// Переменная для проверки кол-ва занков в числе
	cout << "Enter number\n";
	cin >> str;
	int max_size = str.length() + 2;
	int* a = new int[max_size];				// Массив, в котором будет записано само число
	int* d = new int[max_size] {1,2};		// Делитель
	int* e = new int[max_size] {1,1};		// Массив, в котором будет записана единица, чтобы прибавлять её к делителю
	int* tmp_mod = new int[max_size];
	int* tmp_div = new int[max_size];

	zero_mas(a, max_size);
	zero_mas(tmp_mod, max_size);
	zero_mas(tmp_div, max_size);

	str_to_int(str, a);

	int sq = (a[0] + 1) / 2;										// Кол-во знаков в целой части корня из a;
	while ((max_long(a, d) == 1 || max_long(a, d) == 0) && isLess){ // Основной цикл 
		div(a, d, tmp_div, tmp_mod);
		if (tmp_mod[0] == 1 && tmp_mod[1] == 0) {					// Вывод если остаток от деления на простое = 0
			print_num(d); 
			k++;
			if (tmp_div[0] == 1 && tmp_div[1] == 1) break;			// Выходим из цикла если при делении получили единицу в частном
			cout << " * ";
			copy(tmp_div, a);
			zero_mas(tmp_div, max_size);
			zero_mas(tmp_mod, max_size);
			isLess = d[0] <= sq;									// Обновляем проверку на кол-во знаков
			continue;
		}
		zero_mas(tmp_div, max_size);
		zero_mas(tmp_mod, max_size);
		sum(d, e, d);					// Прибавляем 1
		isLess = d[0] <= sq;
	}
	if (k == 0) {
		print_num(a);
		cout << " - prime number!"; 
	}
	else if (!isLess) print_num(a);		// Если мы вышли из цикла потому что проверели все числа количество знаков в которых, не превышает кол-во знаков в корне из a
	else if (k == 1 && isLess) 	
		cout << " - простое число!";
	return 0;
}

void str_to_int(string str, int* mas) {
	mas[0] = str.length();				// В нулевом элементе массива будем хранить длину числа
	for (int i = 1, j = mas[0] - 1; i <= mas[0]; i++, j--) {
		mas[i] = str[j] - '0';
	}	
}

void print_num(int* mas) {
	for (int i = mas[0]; i > 0; i--) {
		cout << mas[i];
	}
}

void zero_mas(int* mas, int size) {
	mas[0] = 1;
	for (int i = 1; i < size; i++) {
		mas[i] = 0;
	}
}

int max_long(int* x, int* y) {
	if (x[0] > y[0]) return 1;		// Первое число больше второго
	if (x[0] < y[0]) return 2;		// Второе больше первого
	for (int i = x[0]; i > 0; i--) {
		if (x[i] > y[i]) return 1;
		if (x[i] < y[i]) return 2;
	}
	return 0;
}

void copy(int* x, int* y) {
	for (int i = 0; i <= x[0]; i++) {
		y[i] = x[i];
	}
}

void sum(int* x, int* y, int* z)
{
	int m = max(x[0], y[0]);
	int p = 0;
	for (int i = 1; i <= m; i++)
	{
		z[i] = x[i] + y[i] + p;
		p = z[i] / 10;
		z[i] %= 10;
	}
	if (p) {
		m++;
		z[m] = p;
	}
	while (z[m] == 0 && m > 1) m--;
	z[0] = m;
}

void sum_short(int* x, int b, int* z) {
	int p;
	z[1] = x[1] + b;
	p = z[1] / 10;
	z[1] %= 10;
	int i = 2;
	for (; i <= x[0]; i++) {
		z[i] = x[i]+ p;
		p = z[i] / 10;
		z[i] %= 10;
	}
	if (p) {
		z[i] = p;
	}
	z[0] = i;
}

void diff(int* x, int* y, int* z) {
	int i = 1;
	int p = 0;
	while (i <= x[0]) {
		if (x[i] - p < y[i]) {
			z[i] = x[i] - p + 10 - y[i];
			p = 1;
			i++;
		}
		else {
			z[i] = x[i] - p - y[i];
			p = 0;
			i++;
		}
	}
	i--;
	while (z[i] == 0 && i > 1) i--;
	z[0] = i;
}

void mult_short(int* x, int b, int* z) {
	int p = 0;
	int i = 1;
	for (; i <= x[0]; i++) {
		z[i] = x[i] * b + p;
		p = z[i] / 10;
		z[i] -= p * 10; 
	}
	while (p > 0) {
		z[i] = p % 10;
		p = p / 10;
		i++;
	}
	i--;
	while (z[i] == 0) i--;
	z[0] = i;
	if (z[0] == 0) z[0]++;
}

void mult_long(int* x, int* y, int* z) {
	int tmp_size = x[0] + y[0] + 2;
	int* tmp = new int[tmp_size];
	zero_mas(tmp, tmp_size);
	for (int j = 1; j <= y[0]; j++) {
		mult_short(x, y[j], tmp);
		for (int i = 1; i < j; i++) {
			mult_short(tmp, 10, tmp);
		}
		sum(z, tmp, z);
		zero_mas(tmp, tmp_size);
	}
}

void div(int* x, int* y, int* z, int* w) {
	if (x[0] < y[0]) copy(x, w);
	else {
		int i = x[0], j = y[0], k;
		w[0] = y[0];
		for (; j > 0 && i > 0; i--, j--) {
			w[j] = x[i];
		}
		while (i >= 0) { // основной рабочий цикл деления
			k = 0;
			while (max_long(w, y) == 1 || max_long(w, y) == 0) {
				diff(w, y, w);
				k++;
			}
			mult_short(z, 10, z);
			z[1] = k;
			if (i > 0) {
				mult_short(w, 10, w);
				w[1] = x[i];
			}
			i--;
		}
	}
}