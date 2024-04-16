#include<iostream>
#include<cmath>

int main() 
{
	const char abc[] = "abcdeifghijklmnopqrstuvwxyz";
	const int power = 27;
	char cont='y';
	char program;
	do {
		std::cout << "Enter the number of the program you want to run." << std::endl;
		std::cout << "0.Exit\n1.Discriminant\n2.Factorial\n3.Mirror\n4.Coctale filter\n5.Maximum array element\n6.Convert from decimal to binary\n7.Calculator\n8.Caesar cipher" << std::endl;
		std::cin >> program;
		system("cls");
		switch (program) {
		case '0':
		{
			std::cout << "You left the pgrogram\nWhy?";
			cont = 'n';
			break;
		}
		case '1'://Дискриминант
		{
			float a1, b1, c1, D1;
			std::cout << "You entere the program'Discriminant'\nEnter a b c." << std::endl;
			std::cin >> a1 >> b1 >> c1;
			if (a1 == 0 && b1 == 0)
				std::cout << "No quadratic roots" << std::endl;
			else if (a1 == 0)
				std::cout << "x = " << c1 / b1 << std::endl;
			else {
				D1 = pow(b1, 2) - 4 * a1 * c1;
				if (D1 < 0)
					std::cout << "No quadratic roots" << std::endl;
				else if (D1 == 0)
					std::cout << "x = " << -b1 / (2 * a1) << std::endl;
				else if (D1 > 0)
					std::cout << "x1 = " << (-b1 + sqrt(D1)) / (2 * a1) << std::endl << "x2 = " << (-b1 - sqrt(D1)) / (2 * a1) << std::endl;
			}
			break;
		}
		case '2'://Факториал
		{
			std::cout << "You entere the program'Factorial'" << std::endl;
			int n2;
			double F2;
			std::cout << "Enter number." << std::endl;
			std::cin >> n2;
			if (n2 < 0)
				std::cout << "Error" << std::endl;
			else if (n2 == 0)
				std::cout << "0! = 1" << std::endl;
			else {
				F2 = 1;
				for (int i = 1; i < (n2 + 1); i++)
					F2 = F2 * i;
				std::cout << n2 << "!= " << F2 << std::endl;
			}
			break;
		}
		case '3'://Зеркало
		{
			std::cout << "You entere the program'Mirror'" << std::endl;
			int n3;
			std::cout << "Enter n" << std::endl;
			std::cin >> n3;
			int** a = new int* [n3];
			for (int i = 0; i < n3; i++)
				a[i] = new int[n3];
			for (int i = 0; i < n3; i++) {
				for (int j = 0; j < n3; j++) {
					a[i][j] = rand() % 50;
					std::cout << a[i][j] << ' ';
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
			for (int i = 0; i < n3; i++) {
				for (int j = 0; j < n3; j++)
					std::cout << a[j][i] << ' ';
				std::cout << std::endl;
			}
			break;
		}
		case '4': //Шейк-Шейк-Шейк
		{
			std::cout << "You entere the program'Coctale filter'" << std::endl;
			int n, m;
			std::cout << "Enter the number of items: " << std::endl;
			std::cin >> n;
			std::cout << "Enter the limit of the random function: " << std::endl;
			std::cin >> m;
			std::cout << "Filling the array" << std::endl;
			int* ar = new int[n];
			for (int i = 0; i < n; i++) {
				ar[i] = rand() % m;
				std::cout << ar[i] << " ";
			}
			std::cout << std::endl;
			std::cout << "Shake filter" << std::endl;
			int L, R;
			L = 0;
			R = n - 1;
			while (L < R) {
				for (int i = L; i < R; i++)
					if (ar[i] > ar[i + 1])
						std::swap(ar[i], ar[i + 1]);
					R--;
				for (int i = R; i > L; i--)
					if (ar[i] < ar[i - 1])
						std::swap(ar[i], ar[i - 1]);
				L++;
			}
			for (int i = 0; i < n; i++)
				std::cout << ar[i] << " ";
			std::cout << std::endl;
			break; 
		}
		case '5'://Максимальный элимент массива
		{
			std::cout << "You entere the program'Maximum array element'" << std::endl;
			int n, j, max;
			j = 0;
			std::cout << "Enter the length of the array" << std::endl;
			std::cin >> n;
			int* a = new int[n];
			for (int i = 0; i < n; i++) {
				a[i] = rand() % 10;
				std::cout << a[i] << ' ';
			}
			std::cout << std::endl;
			max = a[0];
			for (int i = 1; i < n; i++) {
				if (max < a[i]) {
					max = a[i];
					j = i;
				}
			}
			std::cout << "Max = " << max << std::endl << "His index = " << j << std::endl;
			break;
		}
		case '6'://10 в 2
		{
			std::cout << "You entere the program'Convert from decimal to binary'" << std::endl;
			int n, res, s;
			res = 0;
			s = 1;
			std::cout << "Enter number" << std::endl;
			std::cin >> n;
			std::cout << n;
			while (n > 0) {
				res += (n % 2) * s;
				n = n / 2;
				s = s * 10;
			}
			std::cout << " in 2 = " << res << std::endl;
			break;
		}
		case '7'://Калькулятор
		{
			std::cout << "You entere the program'Calculator'" << std::endl;
			float a, b;
			char c;
			std::string yn = "y";
			std::cin >> a;
			do {
				std::cin >> c;
				std::cin >> b;
				switch (c)
				{
				case '+':
					std::cout << a << " + " << b << " = " << a + b << std::endl;
					a = a + b;
					std::cout << "Continue?(y/n)" << std::endl;
					std::cin >> yn;
					break;
				case '-':
					std::cout << a << " - " << b << " = " << a - b << std::endl;
					a = a - b;
					std::cout << "Continue?(y/n)" << std::endl;
					std::cin >> yn;
					break;
				case '*':
					std::cout << a << " * " << b << " = " << a * b << std::endl;
					a = a * b;
					std::cout << "Continue?(y/n)" << std::endl;
					std::cin >> yn;
					break;
				case '/':
					if (b == 0) {
						std::cout << "Error (Division by 0 is not possible)" << std::endl;
					}
					else {
						std::cout << a << " / " << b << " = " << a / b << std::endl;
						a = a / b;
						std::cout << "Continue?(y/n)" << std::endl;
						std::cin >> yn;
					}
					break;
				case '^':
					std::cout << a << " ^ " << b << " = " << pow(a, b) << std::endl;
					a = pow(a, b);
					std::cout << "Continue?(y/n)" << std::endl;
					std::cin >> yn;
					break;
				default:
					std::cout << "Unknown action";
				}
				if (yn == "y")
					std::cout << a << ' ';
			} while (yn == "y");
			break;
		}
		case '8'://Шифр цезаря
		{
			std::cout << "You entere the program'Caesar cipher'" << std::endl;
			int step = 0;
			wchar_t word[1000];
			std::cout << "Enter word: ";
			std::cin.ignore();
			std::wcin.getline(word, 1000);
			std::cout << "Enter the number of characters for the offset: ";
			std::cin >> step;
			for (int i = 0; i < 1000; i++) {
				for (int j = 0; j < power; j++) {
					if (word[i] == abc[j]) {
						word[i] = abc[(j + step) % power];
						break;
					}
				}
			}
			std::cout << std::endl;
			std::wcout << word << std::endl;
			break;
		}
		default:
			std::cout << "Andrey Vladivirovich, it won't work <3" << std::endl;
		}
		if (cont == 'y') 
		{
			std::cout << "Continue program?(y/n)" << std::endl;
			std::cin >> cont;
			if (cont == 'y')
				system("cls");
		}
	} while (cont == 'y');
} 