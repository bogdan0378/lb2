#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

class Auto  // NOLINT(cppcoreguidelines-special-member-functions)
{
	long id;
	string name="";
	double mileage=100;
public:

	double get_mileage() const;

	string get_name() const;

	void set_name(string x);

	void set_mileage(double x);


	long get_id() const;

	static long count;
	Auto()
	{
		cout << "Auto\n";
	}
	Auto(string name, double mileage = 100.0);
	friend ostream& operator<<(ostream&, const Auto&);
	friend class Customer;
	~Auto();
};

double Auto::get_mileage() const
{
	return this->mileage;
}

string Auto::get_name() const
{
	return this->name;
}

void Auto::set_name(string x)
{
	this->name = std::move(x);
}

void Auto::set_mileage(double x)
{
	this->mileage = x;
}

long Auto::get_id() const
{
	return this->id;
}

Auto::Auto(string name, double mileage) : id(++count), name(std::move(name)), mileage(mileage)
{
}

Auto::~Auto() = default;  // NOLINT(clang-diagnostic-deprecated-copy-dtor)

ostream& operator<<(ostream & out, const Auto & w)
{
	string decor = "-";
	for (int i = 0; i < 16; ++i)
	{
		decor += decor[0];
	}
	out << decor << "\nid: " << w.id << "\nname: " << w.name << "\nmileage: " << w.mileage << " miles" << endl << decor << endl;
	return out;
}

class Customer
{
public:
	static void set_mileage(Auto& w, double mileage)
	{
		w.mileage = mileage;
	}
};

long Auto::count = 0;

int main()
{
	Auto pj;
	Auto rj("Bogdan Galtsov", 350);
	Auto bj("baza", 150);
	vector<Auto> wears;
	wears.emplace_back("Bogdan Galtsov", 350);
	wears.emplace_back("zzz", 1350.90);
	wears.emplace_back("Macho Gun", 135000.9);
	cout << "\nBefore tech station:\n";
	cout << rj << bj;
	Customer::set_mileage(rj, rj.get_mileage() * 0.25);
	Customer::set_mileage(bj, 100.50);
	for (auto it = wears.begin(); it < wears.end(); ++it)
	{
		cout << *it;
		Customer::set_mileage(*it, it->get_mileage() * static_cast<double>(0.75));
	}
	cout << "\nAfter tech station:\n";
	for (const auto& it : wears)
	{
		cout << it;
	}
	std::cout << rj << bj;
	system("pause");
}
