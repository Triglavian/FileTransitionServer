#pragma once
#include "IDataType.h"
class Double : public IDataType
{
public:
	Double();
	Double(const double& _double);
	Double(const Double& _double);
	~Double();
	std::string ToString();
	double ToFloat();
	Double operator=(const Double& _double);
	Double operator=(const double& _double);
	Double operator+(const Double& _double);
	Double operator+(const double& _double);
	Double operator-(const Double& _double);
	Double operator-(const double& _double);
	Double operator*(const Double& _double);
	Double operator*(const double& _double);
	Double operator/(const Double& _double);
	Double operator/(const double& _double);
	bool operator==(const Double& _double);
	bool operator==(const double& _double);
	bool operator!=(const Double& _double);
	bool operator!=(const double& _double);
	friend std::ostream& operator<<(std::ostream& out, const Double& _double);
private:
	double _double;
};

