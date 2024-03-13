#include <iostream>
#include <iomanip>
#include <string>
#include "myfuncs.h"
#include "constants.h"

/*������� ��� �������� ���������������� �����*/
//�������� �������� ������������� ������ �� ����������� �������������� � �����.
bool checkStrIsNumeric(std::string const& tempStr)
{
	bool negative_number{ false }, separator{ false };
	for (int i{}; i < tempStr.length(); i++)
	{
		if ((i == 0) && (tempStr[i] == '-'))
		{
			negative_number = true;
			continue;
		}
		if (!separator && i != 0 && (i != tempStr.length() - 1) && (tempStr[i] == '.' || tempStr[i] == ',' || tempStr[i] == '/'))
		{
			separator = true;
			continue;
		}
		if ((tempStr[i] < '0') || (tempStr[i] > '9'))
			return false;
	}
	return !tempStr.empty();
}
//�������������� �������� ������������� ������ � �����.
long double convertStrToNumber(std::string convertStr)
{
	long double number{}, number_for_fraction{};
	bool negative_number{ false }, fraction{ false };
	int separator_index{ -1 }, k{};
	for (int i{}; i < convertStr.length(); i++)
	{
		if (convertStr[i] == '.' || convertStr[i] == ',' || convertStr[i] == '/')
		{
			if (convertStr[i] == '/') fraction = true;
			separator_index = i;
			break;
		}
	}
	for (int i{}; i < convertStr.length(); i++)
	{
		if ((i == 0) && convertStr[i] == '-')
		{
			negative_number = true;
			continue;
		}
		if (convertStr[i] == '.' || convertStr[i] == ',' || convertStr[i] == '/')
			continue;
		if (separator_index == -1)
			number += static_cast<long double>(convertStr[i] - '0') * pow(10, convertStr.length() - i - 1);
		else
			if (!fraction)
				number += static_cast<long double>(convertStr[i] - '0') * pow(10, (i < separator_index) ? (convertStr.length() - i - 1 - 1) : (convertStr.length() - i - 1));
			else
			{
				i < separator_index ? number += static_cast<long double>(convertStr[i] - '0')* pow(10, separator_index - i - 1)
					: number_for_fraction += static_cast<long double>(convertStr[i] - '0') * pow(10, convertStr.length() - separator_index - 1 - k - 1);
				if (i > separator_index) k++;
			}
	}
	if (separator_index != -1 && !fraction)
		number /= pow(10, convertStr.length() - separator_index - 1);
	if (!fraction)
		return negative_number ? static_cast<long double>(-number) : static_cast<long double>(number);
	else
		return negative_number ? static_cast<long double>(-number / number_for_fraction) : static_cast<long double>(number / number_for_fraction);
}

/*������� ��� ������ ���������� �� �������*/
//����� ���������� �� ������, ��������, �������.
void printTask()
{
	std::cout << std::setw(210) << "�������� ����� ����������," << std::endl << std::setw(209) << "������ 4318" << std::endl;
	printDash();
	std::cout << "������� ��������������� �������: 2." << std::endl;
	std::cout << "�������� �������:" << std::endl;
	std::cout << "f(x) = 12x*sqrt(x^3 + 3)			D(f): x>= -1." << std::endl;
	std::cout << "��������� �������: [-0.75; -0.74]." << std::endl;
	std::cout << "��������� ���: h = " << h << std::endl;
}
//����� �������������� �����.
void printDash()
{
	std::cout << std::string(208, '-') << std::endl;
}
//����� ����� �������� ������� ��� ����������������.
void printTableInterpolation()
{
	std::cout << std::string(204, '_') << std::endl;
	std::cout << "|" << std::setw(13) << "x" <<
		"|" << std::setw(13) << "y(x)" <<
		"|" << std::setw(20) << "PI(x)" <<
		"|" << std::setw(27) << "|y(x) - PI(x)|     " <<
		"|" << std::setw(13) << "q" <<
		"|" << std::setw(20) << "PII(x)" <<
		"|" << std::setw(27) << "|y(x) - PII(x)|    " <<
		"|" << std::setw(13) << "t" <<
		"|" << std::setw(20) << "L(x)" <<
		"|" << std::setw(27) << "|y(x) - L(x)|      " <<
		"|" << std::endl;
	std::cout << std::string(204, '_') << std::endl;
}
//����� ����� �������� ������� ��� ���������� �����������������.
void printTableNumericalDefferentiation()
{
	std::cout << std::string(183, '_') << std::endl;
	std::cout << "|" << std::setw(13) << "x" <<
		"|" << std::setw(13) << "y'(x)" <<
		"|" << std::setw(13) << "~x_0" <<
		"|" << std::setw(20) << "(PI(x))'" <<
		"|" << std::setw(27) << "|y'(x) - (PI(x))'|    " <<
		"|" << std::setw(13) << "q" <<
		"|" << std::setw(13) << "~x_n" <<
		"|" << std::setw(20) << "(PII(x))'" <<
		"|" << std::setw(27) << "|y'(x) - (PII(x))'|      " <<
		"|" << std::setw(13) << "t" <<
		"|" << std::endl;
	std::cout << std::string(183, '_') << std::endl;
}

/*���������������� �������*/
//���������������� ����.
void MenuForChoices()
{
	std::cout << "��� �� ������ �������?" << std::endl <<
		"1) ��������� ��������� (�������� ����������)." << std::endl <<
		"2) ����� �� ���������." << std::endl;
}
//������ �������� � ������������.
char getCase()
{
	while (true)
	{
		MenuForChoices();
		std::cout << "��� �����: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2")
			return choice[0];
		else
			std::cout << std::endl << "������ �����! ��� ����� ������ ����� ������ ������ � ������������ � ������������������ �������� (�� 1 �� 2). ��������� ����:" << std::endl;
	}
}
//��������� �������� x �� ������������ �� ���������� �������.
long double getXValue(const int& number)
{

	switch (number)
	{
	case 1:
		std::cout << "������� ������ �������� x: ";
		break;
	case 2:
		std::cout << "������� ������ �������� x: ";
		break;
	case 3:
		std::cout << "������� ������ �������� x: ";
		break;
	default:
		break;
	}
	std::string x_value{};
	while (true)
	{
		std::getline(std::cin, x_value);
		if (checkStrIsNumeric(x_value))
		{
			long double numeric_x_value{ convertStrToNumber(x_value) };
			if (numeric_x_value >= a_x0 && numeric_x_value <= b_x5)
				return numeric_x_value;
			else
			{
				std::cout << "�������� x ������ ������������ ���������� �������. ��������� ����: ";
			}
		}
		else
			std::cout << "������ �����! �� ����� �� �����. ��������� ����: ";
	}
}

/*��������������� �������*/
long double getClosestToX(const long double& x_value, const int& method)
{
	long double x0{ -0.75 }, x1{ -0.748 }, x2{ -0.746 }, x3{ -0.744 }, x4{ -0.742 }, x5{ -0.74 };
	if (x_value != x0 && x_value != x1 && x_value != x2 && x_value != x3 && x_value != x4 && x_value != x5)
	{
		if (x_value > x0 && x_value < x1)
		{
			if (method == 1)
			{
				if (abs(x_value - x0) <= abs(x_value - x1))
					return x0;
				else
					return x1;
			}
			else
			{
				if (abs(x_value - x0) < abs(x_value - x1))
					return x0;
				else
					return x1;
			}
		}
		else if (x_value > x1 && x_value < x2)
		{
			if (method == 1)
			{
				if (abs(x_value - x1) <= abs(x_value - x2))
					return x1;
				else
					return x2;
			}
			else
			{
				if (abs(x_value - x1) < abs(x_value - x2))
					return x1;
				else
					return x2;
			}
		}
		else if (x_value > x2 && x_value < x3)
		{
			if (method == 1)
			{
				if (abs(x_value - x2) <= abs(x_value - x3))
					return x2;
				else
					return x3;
			}
			else
			{
				if (abs(x_value - x2) < abs(x_value - x3))
					return x2;
				else
					return x3;
			}
		}
		else if (x_value > x3 && x_value < x4)
		{
			if (method == 1)
			{
				if (abs(x_value - x3) <= abs(x_value - x4))
					return x3;
				else
					return x4;
			}
			else
			{
				if (abs(x_value - x3) < abs(x_value - x4))
					return x3;
				else
					return x4;
			}
		}
		else if (x_value > x4 && x_value < x5)
		{
			if (method == 1)
			{
				if (abs(x_value - x4) <= abs(x_value - x5))
					return x4;
				else
					return x5;
			}
			else
			{
				if (abs(x_value - x4) < abs(x_value - x5))
					return x4;
				else
					return x5;
			}
		}
	}
	else
	{
		if (x_value == x0)
			return x0;
		else if (x_value == x1)
			return x1;
		else if (x_value == x2)
			return x2;
		else if (x_value == x3)
			return x3;
		else if (x_value == x4)
			return x4;
		else if (x_value == x5)
			return x5;

	}
}

/*�������� �������*/
//������� ����������������.
void interpolation_formulas(const long double& x1, const long double& x2, const long double& x3)
{
	long double x_value{};
	for (int i{}; i < 3; i++)
	{
		if (i == 0)
			x_value = x1;
		else if (i == 1)
			x_value = x2;
		else
			x_value = x3;
		//���������� y(x).
		long double y_value{ 12 * x_value * sqrt(pow(x_value, 3) + 1) };
		//���������� q.
		long double q{ (x_value - a_x0) / h };
		//���������� PI(x).
		long double PI_x{ -6.84311 - q * 0.00159 + (q * (q - 1) * 0.00027) / 2 - (q * (q - 1) * (q - 2)) * 0.00001 / 6 + (q * (q - 1) * (q - 2) * (q - 3) * (0.00002)) / 24 - (q * (q - 1) * (q - 2) * (q - 3) * (q - 4) * 0.00005 / 120) };
		//���������� t.
		long double t{ (x_value - b_x5) / h };
		//���������� PII(x).
		long double PII_x{ -6.84841 - t * 0.00054 + (t * (t + 1)) / 2 * 0.00025 + (t * (t + 1) * (t + 2)) / 6 * (-0.00002) - (t * (t + 1) * (t + 2) * (t + 3)) / 24 * 0.00003 - (t * (t + 1) * (t + 2) * (t + 3) * (t + 4)) / 120 * 0.00005 };
		//���������� L(x).
		long double L_x{ 1782059895833.33 * (x_value + 0.748) * (x_value + 0.746) * (x_value + 0.744) * (x_value + 0.742) * (x_value + 0.74) +
						 -8912369791666.67 * (x_value + 0.75) * (x_value + 0.746) * (x_value + 0.744) * (x_value + 0.742) * (x_value + 0.74) +
						 +17828177083333.33 * (x_value + 0.75) * (x_value + 0.748) * (x_value + 0.744) * (x_value + 0.742) * (x_value + 0.74) +
						 -17830937500000 * (x_value + 0.75) * (x_value + 0.748) * (x_value + 0.746) * (x_value + 0.742) * (x_value + 0.74) +
						 +8916497395833.33 * (x_value + 0.75) * (x_value + 0.748) * (x_value + 0.746) * (x_value + 0.744) * (x_value + 0.74) +
						 -1783440104166.67 * (x_value + 0.75) * (x_value + 0.748) * (x_value + 0.746) * (x_value + 0.744) * (x_value + 0.742) };
		//���������� �������.
		std::cout << "|" << std::setw(13) << std::setprecision(13) << x_value <<
			"|" << std::setw(13) << std::setprecision(10) << y_value <<
			"|" << std::setw(20) << std::setprecision(10) << PI_x <<
			"|" << std::setw(27) << std::setprecision(10) << abs(y_value - PI_x) <<
			"|" << std::setw(13) << std::setprecision(10) << q <<
			"|" << std::setw(20) << std::setprecision(10) << PII_x <<
			"|" << std::setw(27) << std::setprecision(10) << abs(y_value - PII_x) <<
			"|" << std::setw(13) << std::setprecision(10) << t <<
			"|" << std::setw(20) << std::setprecision(10) << L_x <<
			"|" << std::setw(27) << std::setprecision(10) << abs(y_value - L_x) <<
			"|" << std::endl;
		std::cout << std::string(204, '_') << std::endl;
	}
}
//������� ���������� �����������������.
void numerical_differentiation_formulas(const long double& x1, const long double& x2, const long double& x3)
{
	long double x_value{};
	for (int i{}; i < 3; i++)
	{
		if (i == 0)
			x_value = x1;
		else if (i == 1)
			x_value = x2;
		else
			x_value = x3;
		//���������� y'(x).
		long double dy_value{ (30 * pow(x_value, 3) + 12) / sqrt(pow(x_value, 3) + 1) };
		//���������� ~x_0.
		long double tilde_x_0{ getClosestToX(x_value, 1) };
		//���������� q.
		long double q{ (x_value - tilde_x_0) / h };
		//���������� (PI(x))'.
		long double dPI_x{ 1 / h * (-0.00159 + (2 * q - 1) * 0.00027 / 2 - (3 * pow(q,2) - 6 * q + 2) * 0.00001 / 6 + (4 * pow(q, 3) - 18 * pow(q,2) + 22 * q - 6) * (0.00002) / 24 - (5 * pow(q,4) - 40 * pow(q,3) + 105 * pow(q,2) - 100 * q + 24) * 0.00005 / 120) };
		//���������� ~x_n.
		long double tilde_x_n{ getClosestToX(x_value, 2) };
		//���������� t.
		long double t{ (x_value - tilde_x_n) / h };
		//���������� (PII(x))'.
		long double dPII_x{ 1 / h * (-0.00054 + (2 * t + 1) * 0.00025 / 2 + (3 * pow(t, 2) + 6 * t + 2) * (-0.00002) / 6 - (4 * pow(t,3) - 18 * pow(t,2) + 22 * t + 6) * 0.00003 / 24 - (5 * pow(t,4) + 40 * pow(t,3) + 105 * pow(t,2) + 100 * t + 24) * 0.00005 / 120) };
		//���������� �������.
		std::cout << "|" << std::setw(13) << std::setprecision(13) << x_value <<
			"|" << std::setw(13) << std::setprecision(10) << dy_value <<
			"|" << std::setw(13) << std::setprecision(10) << tilde_x_0 <<
			"|" << std::setw(20) << std::setprecision(10) << dPI_x <<
			"|" << std::setw(27) << std::setprecision(10) << abs(dy_value - dPI_x) <<
			"|" << std::setw(13) << std::setprecision(10) << q <<
			"|" << std::setw(13) << std::setprecision(10) << tilde_x_n <<
			"|" << std::setw(20) << std::setprecision(10) << dPII_x <<
			"|" << std::setw(27) << std::setprecision(10) << abs(dy_value - dPII_x) <<
			"|" << std::setw(13) << std::setprecision(10) << t <<
			"|" << std::endl;
		std::cout << std::string(183, '_') << std::endl;
	}
}