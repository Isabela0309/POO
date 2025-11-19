#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>

class Autoturism
{
private:
	char* model;
	char* producator;
	int putere;
	char* combustibil;
public:
	Autoturism()
	{
		model = nullptr;
		producator = nullptr;
		combustibil = nullptr;
		putere = 0;
	}

	Autoturism(char* mod, char* prod, char* comb, int power)
	{
		model = new char[strlen(mod)+1];
		strcpy(model, mod);

		producator = new char[strlen(prod) + 1];
		strcpy(producator, prod);

		combustibil = new char[strlen(comb) + 1];
		strcpy(combustibil, comb);

		putere = power;
	}

	Autoturism(const Autoturism& a)
	{
		model = new char[strlen(a.model) + 1];
		strcpy(model, a.model);

		combustibil = new char[strlen(a.combustibil) + 1];
		strcpy(combustibil, a.combustibil);

		producator = new char[strlen(a.producator) + 1];
		strcpy(producator, a.producator);

		putere = a.putere;
	}

	Autoturism& operator=(const Autoturism& a)
	{
		if (this == &a) return *this;

		delete[] model;
		delete[] producator;
		delete[] combustibil;

		model = new char[strlen(a.model) + 1];
		strcpy(model, a.model);

		combustibil = new char[strlen(a.combustibil) + 1];
		strcpy(combustibil, a.combustibil);

		producator = new char[strlen(a.producator) + 1];
		strcpy(producator, a.producator);

		putere = a.putere;

		return *this;
	}

	~Autoturism()
	{
		delete[] model;
		delete[] producator;
		delete[] combustibil;
	}

	int getPutere()
	{
		return putere;
	}

	char* getCombustibil()
	{
		return combustibil;
	}

	friend std::ostream& operator<<(std::ostream& out, const Autoturism& a)
	{
		out << "Producator: " << a.producator << ", model: " << a.model << ", combustibil: " << a.combustibil << ", cai putere: " << a.putere << std::endl;

		return out;
	}

	friend std::istream& operator>>(std::istream& in, Autoturism& a)
	{
		char bufferM[100], bufferP[100], bufferC[100];
		in >> a.putere;
		if (a.putere < 20 || a.putere>1500)
		{
			throw std::out_of_range("Putere invalida.");
		}

		delete[] a.model;
		delete[] a.combustibil;
		delete[] a.producator;

		in >> bufferM >> bufferP >> bufferC;

		a.model = new char[strlen(bufferM) + 1];
		strcpy(a.model, bufferM);

		a.producator = new char[strlen(bufferP) + 1];
		strcpy(a.producator, bufferP);

		a.combustibil = new char[strlen(bufferC) + 1];
		strcpy(a.combustibil, bufferC);

		return in;
	}

	bool operator<(const Autoturism& a) const
	{
		if (putere < a.putere)
		{
			return true;
		}
		return false;
	}
};

std::pair<Autoturism*, int> citireDinFisier(const std::string& fileName)
{
	std::ifstream f(fileName);
	if (!f) throw std::runtime_error("Nu s-a putut deschide fisierul.");

	int n;
	f >> n;

	Autoturism* vec = new Autoturism[n];

	for (int i = 0; i < n; ++i)
	{
		f >> vec[i];
	}
	return std::make_pair(vec, n);
}

int main()
{
	auto result = citireDinFisier("date.txt");
	int n = result.second;
	Autoturism* vec = result.first;

	std::sort(vec, vec + n, [](const Autoturism& a, const Autoturism& b)
		{
			return a < b;
		});

	for (int i = 0; i < n; ++i)
	{
		if (strcmp(vec[i].getCombustibil(), "benzina") == 0)
		{
			std::cout << vec[i] << std::endl;
		}
	}

	for (int i = 0; i < n; ++i)
	{
		if (strcmp(vec[i].getCombustibil(), "motorina") == 0)
		{
			std::cout << vec[i] << std::endl;
		}
	}
	
	for (int i = 0; i < n; ++i)
	{
		if (strcmp(vec[i].getCombustibil(), "electric") == 0)
		{
			std::cout << vec[i] << std::endl;
		}
	}
	delete[] vec;

	return 0;
}