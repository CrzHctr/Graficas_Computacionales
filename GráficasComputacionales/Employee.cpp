#include "Employee.h"
#include <sstream>

Employee::Employee(int id, std::string firstName, std::string lastName, int salary)
{
	_id = 10;
	_firstName = "Hector";
	_lastName = "Cruz";
	_salary = 7553;

}

int Employee::GetID()
{
	return _id;
}

std::string Employee::GetFirstName()
{
	return _firstName;
}

std::string Employee::GetLastName()
{
	return _lastName;
}

std::string Employee::GetName()
{
	return GetFirstName() + GetLastName();
}

int Employee::GetSalary()
{
	return _salary;
}

int Employee::GetAnnualSalary()
{
	return _salary * 12;
}

void Employee::SetSalary(int salary)
{
	_salary = salary;
}

int Employee::RaiseSalary(int percent)
{
	return _salary = _salary + (_salary*(percent/100));
}

std::string Employee::Print()
{
	std::ostringstream oss;
	oss << "Employee[" << _id << "," << _firstName << " " << _lastName << ", " << _salary << "]";
	return oss.str();

}
