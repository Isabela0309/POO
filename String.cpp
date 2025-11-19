#include <iostream>
#include <fstream>

class sstring
{
private:
	char* s;
public:
	sstring(const char* st = "")
	{
		s = new char[strlen(st) + 1];
		strcpy(s, st);
	}
	sstring(const sstring& st)
	{
		s = new char[strlen(st.s) + 1];
		strcpy(s, st.s);
	}
	~sstring()
	{
		delete[] s;
	}
	sstring operator=(const sstring& st)
	{
		if(this==&st) return *this;
		delete[] s;
		s = new char[strlen(st.s) + 1];
		strcpy(s, st.s);
		return *this;
	}

	sstring operator+(const sstring& st)
	{
		char* str = new char[strlen(s) + strlen(st.s) + 1];
		strcpy(str, s);
		strcat(str, st.s);
		sstring result(str);
		delete[] str;
		return result;
	}

	sstring operator+=(sstring& st)
	{
		*this = *this + st;
		return *this;
	}

	int operator==(const sstring& st)
	{
		if (!strcmp(s, st.s))
		{
			return 1;
		}
		return 0;
	}

	int operator!=(const sstring& st)
	{
		if (strcmp(s, st.s))
		{
			return 1;
		}
		return 0;
	}

	bool operator<(const sstring& st)
	{
		if (strcmp(s, st.s) < 0) return true;
		return false;
	}

	bool operator<=(const sstring& st)
	{
		if (strcmp(s, st.s) <= 0) return true;
		return false;
	}

	bool operator>(const sstring& st)
	{
		if (strcmp(s, st.s) > 0) return true;
		return false;
	}

	bool operator>=(const sstring& st)
	{
		if (strcmp(s, st.s) >= 0) return true;
		return false;
	}

	int operator!()
	{
		return strlen(s);
	}

	char operator[](int i)
	{
		if (i < 0 || i >= strlen(s))
		{
			throw std::out_of_range("Idx invalid");
		}
		return s[i];
	}

	friend std::ostream& operator<<(std::ostream& fl, const sstring& str)
	{
		fl << str.s;
		return fl;
	}

	friend std::istream& operator>>(std::istream& fl, sstring& str)
	{
		char buffer[1001];
		fl >> buffer;
		if (strlen(buffer) >= 1000)
		{
			throw std::length_error("Input prea lung.");
		}
		delete[] str.s;
		str.s = new char[strlen(buffer) + 1];
		strcpy(str.s, buffer);
		return fl;
	}

	void citireFisier()
	{
		std::ifstream f("input.txt");
		if (!f)
		{
			std::cerr << "Eroare la deschiderea fisierului.";
			return;
		}

		f >> *this;

		f.close();
	}
};