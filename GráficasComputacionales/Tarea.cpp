/*********************************************************
Materia: Gráficas Computacionales
Fecha:   13 de Agosto del 2017
Autor: A01372911 Héctor Cruz Dorantes
*********************************************************/

#include <iostream>
#include <string>

int PerimetroRectangulo(int base, int altura) {
	int perimetro = 2 * (base)+2 * (altura);
	return perimetro;
}

float AreaTriangulo(float altura, float base) {
	float area = (altura*base) / (2);
	return area;
}

int Mayor(int num1, int num2, int num3) {
	if (num1>num2 && num1>num3) {
		return num1;
	}
	if (num2>num1 && num2>num3) {
		return num2;
	}
	if (num3>num1 && num3>num2) {
		return num3;
	}
	return 0;
}

int Menor(int num1, int num2, int num3) {
	if (num1<num2 && num1<num3) {
		return num1;
	}
	if (num2<num1 && num2<num3) {
		return num2;
	}
	if (num3<num1 && num3<num2) {
		return num3;
	}
	return 0;
}

void FilaEstrellas(int n) {
	for (int i = 0; i<n; ++i) {
		std::cout << "* ";
	}
	std::cout << " " << std::endl;
}

void MatrizEstrellas(int n) {
	for (int i = 0; i<n; ++i) {
		for (int j = 0; j<n; ++j) {
			std::cout << "* ";
		}
		std::cout << " " << std::endl;
	}
}

void PiramideEstrellas(int n) {
	for (int i = 1; i<n; ++i) {
		for (int j = 0; j<i; ++j) {
			std::cout << "* ";
		}
		std::cout << " " << std::endl;
	}
}

void FlechaEstrellas(int num) {
	int x = 1;
	while (num >= x) {
		std::string starString(x, '*');
		std::cout << starString << std::endl;
		x++;
	}
	x--;
	while (x >= 1) {
		x--;
		std::string starString(x, '*');
		std::cout << starString << std::endl;
	}
}

void Fibonacci(int n) {
	int sum = 0;
	int prev = -1;
	int next = 1;
	for (int i = 0; i <= n; ++i) {
		sum = next + prev;
		prev = next;
		next = sum;
		std::cout << sum << " ";
	}
	std::cout << " " << std::endl;
}

bool EsPrimo(int numero) {
	int i = 2;
	while (i < numero) {
		if (numero%i == 0) return 0;
		i++;
	}
	return 1;
}
/*
int main(int argc, const char * argv[]) {
	int p = PerimetroRectangulo(5, 3);
	std::cout << "El Perimetro del Rectangulo:\n" << p << std::endl;

	float a = AreaTriangulo(5.0f, 3.0f);
	std::cout << "\nEl Area  del Rectangulo:\n" << a << std::endl;

	int mayor = Mayor(5, 9, 1);
	std::cout << "\nEl numero Mayor es:\n" << mayor << std::endl;

	int menor = Menor(5, 9, 1);
	std::cout << "\nEl numero Menor es:\n" << menor << std::endl;

	std::cout << "\nFila Estrellas:" << std::endl;
	FilaEstrellas(5);

	std::cout << "\nMatriz Estrellas:" << std::endl;
	MatrizEstrellas(4);

	std::cout << "\nPiramideEstrellas:" << std::endl;
	PiramideEstrellas(6);

	std::cout << "\nFlechaEstrellas:" << std::endl;
	FlechaEstrellas(3);

	std::cout << "Fibonacci:" << std::endl;
	Fibonacci(9);
	std::cout << "" << std::endl;

	int Primo1 = 79;
	int Primo2 = 52;

	bool test1 = EsPrimo(Primo1);
	bool test2 = EsPrimo(Primo2);

	std::cout << std::boolalpha;
	std::cout << Primo1 << " es Primo? " << test1 << std::endl;
	std::cout << Primo2 << " es Primo? " << test2 << std::endl;

	std::cin.get();

	return 0;
}*/
