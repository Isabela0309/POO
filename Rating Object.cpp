#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>

class RatingObject
{
private:
	char* nume;
	int* vector;
	int size;
public:
	RatingObject()
	{
		nume = nullptr;
		vector = nullptr;
		size = 0;
	}
	RatingObject(char* name, int* vec, int s)
	{
		size = s;

		nume = new char[strlen(name) + 1];
		strcpy(nume, name);

		vector = new int[size];
		for (int i = 0; i < size; i++)
		{
			vector[i] = vec[i];
		}
	}

	RatingObject(const RatingObject& ro)
	{
		size = ro.size;
		nume = new char[strlen(ro.nume) + 1];
		strcpy(nume, ro.nume);

		vector = new int[ro.size];
		for (int i = 0; i < size; ++i)
		{
			vector[i] = ro.vector[i];
		}
	}
	RatingObject& operator=(const RatingObject& ro)
	{
		if (this == &ro) return *this;
		delete[] vector;
		delete[] nume;

		size = ro.size;
		nume = new char[strlen(ro.nume) + 1];
		strcpy(nume, ro.nume);

		vector = new int[size];
		for (int i = 0; i < size; ++i)
		{
			vector[i] = ro.vector[i];
		}

		return *this;
	}

	~RatingObject()
	{
		delete[] nume;
		delete[] vector;
	}

	friend std::istream& operator>>(std::istream& in, RatingObject& ro)
	{
		char tempName[100];
		in >> tempName;
		in >> ro.size;

		delete[] ro.nume;
		ro.nume = new char[strlen(tempName) + 1];
		strcpy(ro.nume, tempName);

		delete[] ro.vector;
		ro.vector = new int[ro.size];

		for (int i = 0; i < ro.size; ++i)
		{
			in >> ro.vector[i];
			if (ro.vector[i] < 1 || ro.vector[i]>10)
			{
				throw std::out_of_range("Nota trebuie sa fie intre 1 si 10.");
			}
		}
		return in;
	}

	friend std::ostream& operator<<(std::ostream& out,const RatingObject& ro)
	{
		out << "Nume obiect: " << ro.nume << std::endl;
		out << "Note: ";
		for (int i = 0; i < ro.size; i++)
		{
			out << ro.vector[i]<<" ";
		}
		return out;
	}

	RatingObject& operator+=(int nota)
	{
		if (nota < 1 || nota>10)
		{
			throw std::out_of_range("Nota trebuie sa fie cuprinsa intre 1 si 10.");
		}

		int* newVec = new int[size + 1];

		for (int i = 0; i < size; ++i)
		{
			newVec[i] = vector[i];
		}

		newVec[size] = nota;
		delete[] vector;

		vector = newVec;
		size = size + 1;
		
		return *this;
	}

	double operator!() const
	{
		double medie;
		double numarator = 0;
		for (int i = 0; i < size; ++i)
		{
			numarator += static_cast<double>(vector[i]);
		}
		medie = numarator / size;
		return medie;
	}
};

std::pair<RatingObject*, int> citireDinFisier(const std::string& numeFisier)
{
	std::ifstream f(numeFisier);

	if (!f) throw std::runtime_error("Nu s-a putut deschide fisierul.");

	int n;
	f >> n;
	RatingObject* objects = new RatingObject[n];
	for (int i = 0; i < n; ++i)
	{
		f >> objects[i];
	}

	f.close();
	return std::make_pair(objects, n);
}

int main()
{
	auto result = citireDinFisier("date.txt");
	RatingObject* ro = result.first;
	int n = result.second;

	std::sort(ro, ro + n, [](const RatingObject& a, const RatingObject& b)
		{
			return !a > !b;
		});

	int topCount = (n < 10) ? n : 10;
	std::cout << "Top " << topCount << " obiecte dupa rating: " << std::endl;
	for (int i = 0; i < topCount; ++i)
	{
		std::cout << ro[i] << ", Medie: " << !ro[i] << std::endl;
	}

	delete[] ro;

	return 0;
}
