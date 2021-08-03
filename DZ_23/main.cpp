/*
	Домашнее Задание №23
		Ученик: Шелест Александр

	Перенести классы для математических операций из прошлых работ
	в соответствующие пространства имён.
	Протестировать их работу с использованием механизма пространств имён.
*/

#include <iostream>
#include <clocale>
#include <cmath>
#include <iomanip>
#include <ctime>

/*
   						Древо пространства имён

                          +-----------------+
                          | math_operations |
                          +-----------------+
                            /             \
					 -------               ------
					/	                         \
	          +-----------+                 +-----------+
              | algebraic |                 | euclidean |
              +-----------+                 +-----------+
				/     \                       /       \
			   /       \                     /         \
	   +----------+ +---------------+    +-------+  +-------+
       | Fraction | | ComplexNumber |    | Vec2D |  | Vec3D |
	   +----------+ +---------------+    +-------+  +-------+
*/

namespace math_operations
{
	namespace algebraic
	{
		class Fraction
		{
		private:
			int numerator;		
			int denominator;

			int getGreatestCommonDivisor()
			{
				int tmp = numerator > denominator ? numerator : denominator;

				for (int i = tmp; i > 0; i--)
					if (numerator % i == 0 && denominator % i == 0)
						return i;

				return 1;
			}

		public:
			Fraction(int numerator = 0, int denominator = 1)
			{
				setNumerator(numerator);
				setDenominator(denominator);

				normalize();
			}

			~Fraction()
			{
				this->numerator = 0;
				this->denominator = 0;
			}

			int getNumerator() { return numerator; }
			int getDenominator() { return denominator; }

			void setNumerator(int numerator) 
			{ 
				this->numerator = numerator;
			}

			void setDenominator(int denominator) 
			{
				if (denominator == 0)
					throw "denominator of a fraction number cannot be zero";
				this->denominator = denominator;
			}

			explicit operator float() { return (float)numerator / (float)denominator; }

			Fraction reverse() { std::swap(numerator, denominator); return *this; }

			Fraction normalize()
			{
				int gcd = getGreatestCommonDivisor();

				numerator /= gcd;
				denominator /= gcd;

				return *this;
			}

			Fraction operator +(Fraction other)
			{
				Fraction res = *this;

				if (this->denominator != other.denominator)
				{
					res = res * other.denominator;
					other = other * this->denominator;
				}

				res.numerator += other.denominator;

				res.normalize();
				return res;
			}
			
			Fraction operator -(Fraction other)
			{
				Fraction res = *this;

				if (this->denominator != other.denominator)
				{
					res = res * other.denominator;
					other = other * this->denominator;
				}

				res.numerator -= other.denominator;

				res.normalize();
				return res;
			}

			Fraction operator *(int factor)
			{
				return Fraction(numerator * factor, denominator * factor).normalize();
			}

			Fraction operator *(Fraction& other)
			{
				return Fraction(numerator * other.numerator, 
						denominator * other.denominator).normalize();
			}

			Fraction operator /(int factor)
			{
				return Fraction(numerator / factor, denominator / factor).normalize();
			}

			Fraction operator /(Fraction& other)
			{
				return Fraction(*this).reverse() * other;
			}

			friend std::ostream& operator <<(std::ostream& ostr, Fraction f);
		};

		class ComplexNumber
		{
		private:
			float a;
			float b;
			bool sign;

		public:
			ComplexNumber(float a = 1, float b = 1) : a(a), b(b)
			{
				sign = b < 0;
			}

			float getA() { return a; }
			float getB() { return b; }
			char getSign() { return sign ? '-' : '+'; }

			void setA(float a) { this->a = a; }
			void setB(float b) { this->b = b; }

			ComplexNumber operator+(const ComplexNumber& other)
			{
				float a = this->a + other.a;	
				float b = this->b + other.b;
				return ComplexNumber(a, b);
			}

			ComplexNumber operator-(const ComplexNumber& other)
			{
				float a = this->a - other.a;	
				float b = this->b - other.b;
				return ComplexNumber(a, b);
			}

			ComplexNumber operator*(const ComplexNumber& other)
			{
				float a = (this->a * other.a) - (this->b * other.b);			
				float b = (this->b * other.a) + (this->a * other.b);		
				return ComplexNumber(a, b);
			}

			ComplexNumber operator/(const ComplexNumber& other)
			{
				float tmp = ((other.a * other.a) + (other.b * other.b));
				float a = ((this->a * other.a) + (this->b * other.b)) / tmp;	
				float b = ((this->b * other.a) - (this->a * other.b)) / tmp;
				return ComplexNumber(a, b);
			}

			friend std::ostream& operator<<(std::ostream& ostr, ComplexNumber c);
		};

		std::ostream& operator <<(std::ostream& ostr, Fraction f)
		{
			ostr << '(' << f.numerator << '/' << f.denominator << ')';
			return ostr;
		}

		std::ostream& operator<<(std::ostream& ostr, ComplexNumber c)
		{
			ostr << std::setprecision(3) << c.a << ' ' << c.getSign() << ' ' << fabs(c.b) << 'i';
			return ostr;
		}
	}

	namespace euclidean
	{
		class Vec2D
		{
		protected:
			float x;
			float y;

		public:
			explicit Vec2D(float l) : x(l), y(l)
			{}
			Vec2D(float _x, float _y) : x(_x), y(_y)
			{}

			float getX() { return x; }
			float getY() { return y; }

			void setX(float x) { this->x = x; }
			void setY(float y) { this->y = y; }

			float length() { return sqrt((x * x) + (y * y)); }

			Vec2D unit()
			{
				float len = length();

				if (len == 0)
					return Vec2D(0, 0);

				return Vec2D(x / len, y / len);
			}

			Vec2D operator +(float v) { return Vec2D(x + v, y + v); }
			Vec2D operator +(Vec2D& other) { return Vec2D(x + other.x, y + other.y); }
			Vec2D operator -(float v) { return Vec2D(x - v, y - v); }
			Vec2D operator -(Vec2D& other) { return Vec2D(x - other.x, y - other.y); }
			Vec2D operator *(float v) { return Vec2D(x * v, y * v); }
			Vec2D operator *(Vec2D& other) { return Vec2D(x * other.x, y * other.y); }
			Vec2D operator /(float v) { return Vec2D(x / v, y / v); }
			Vec2D operator /(Vec2D& other) { return Vec2D(x / other.x, y / other.y); }

			friend std::ostream& operator <<(std::ostream& ostr, Vec2D vec);
		};

		class Vec3D 
		{
		private:
			float x;
			float y;
			float z;

		public:
			explicit Vec3D(float l) : x(l), y(l), z(l)
			{}
			Vec3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
			{}

			float getX() { return x; }
			float getY() { return y; }
			float getZ() { return z; }

			void setX(float x) { this->x = x; }
			void setY(float y) { this->y = y; }
			void setZ(float z) { this->z = z; }

			float length()
			{
				return sqrt((x * x) + (y * y) + (z * z));
			}

			Vec3D unit()
			{
				float len = length();

				if (len == 0)
					return Vec3D(0, 0, 0);

				return Vec3D(x / len, y / len, z / len);
			}

			Vec3D operator +(float v) { return Vec3D(x + v, y + v, z + v); }
			Vec3D operator +(Vec3D& v) { return Vec3D(x + v.x, y + v.y, z + v.z); }
			Vec3D operator -(float v) { return Vec3D(x - v, y - v, z - v); }
			Vec3D operator -(Vec3D& v) { return Vec3D(x - v.x, y - v.y, z - v.z); }
			Vec3D operator *(float v) { return Vec3D(x * v, y * v, z * v); }
			Vec3D operator *(Vec3D& v) { return Vec3D(x * v.x, y * v.y, z * v.z); }
			Vec3D operator /(float v) { return Vec3D(x / v, y / v, z / v); }
			Vec3D operator /(Vec3D& v) { return Vec3D(x / v.x, y / v.y, z / v.z); }

			friend std::ostream& operator <<(std::ostream& ostr, Vec3D vec);
		};

		std::ostream& operator <<(std::ostream& ostr, Vec2D vec)
		{
			ostr << std::setprecision(3) << "{ " << vec.x << ", " << vec.y << " }"; 
			return ostr;
		}

		std::ostream& operator <<(std::ostream& ostr, Vec3D vec)
		{
			ostr << std::setprecision(3);
			ostr << "{ " << vec.x << ", " << vec.y << ", " << vec.z << " }"; 
			return ostr;
		}
	}
}


int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(0));

	std::cout << "\tДомашнее Задание №23\n"
		<< "\t\tУченик: Шелест Александр\n\n"
		<< "Перенести классы для математических операций из прошлых работ\n"
		<< "в соответствующие пространства имён.\n"
		<< "Протестировать их работу с использованием механизма пространств имён.\n\n\n";

	std::cout << "В ходе тестирования будут проведены различные операции между переменными разных типов.\n";
	std::cout << "Значения переменных генерируются случайным образом!\n";

#define pause_exec() std::cout << "нажмите Enter для продолжения...\n\n"; std::cin.get()

	pause_exec();
	math_operations::algebraic::Fraction f1(rand() % 16, rand() % 16);
	math_operations::algebraic::Fraction f2(rand() % 16, rand() % 16);
	std::cout << "math_operations::algebraic::Fraction:\n";
	std::cout << "\tf1 = " << f1 << '\n';
	std::cout << "\tf2 = " << f2 << "\n\n";
	std::cout << "f1 + f2 = " << f1 + f2 << '\n';
	std::cout << "f1 / f2 = " << f1 / f2 << "\n\n";

	pause_exec();
	math_operations::algebraic::ComplexNumber c1(rand() % 16, rand() % 16);
	math_operations::algebraic::ComplexNumber c2(rand() % 16, rand() % 16);
	std::cout << "math_operations::algebraic::ComplexNumber:\n";
	std::cout << "\tc1 = " << c1 << '\n';
	std::cout << "\tc2 = " << c2 << "\n\n";
	std::cout << "c1 + c2 = " << c1 + c2 << '\n';
	std::cout << "c1 / c2 = " << c1 / c2 << "\n\n";

	pause_exec();
	math_operations::euclidean::Vec2D v2d_1((rand() % 30) * 0.54, (rand() % 30) * 0.54);
	math_operations::euclidean::Vec2D v2d_2((rand() % 30) * 0.54, (rand() % 30) * 0.54);
	std::cout << "math_operations::euclidean::Vec2D:\n";
	std::cout << "\tv2d_1 = " << v2d_1 << '\n';
	std::cout << "\tv2d_2 = " << v2d_2 << "\n\n";
	std::cout << "v2d_1.length = " << v2d_1.length() << '\n';
	std::cout << "v2d_1.unit = " << v2d_1.unit() << '\n';
	std::cout << "v2d_1 * v2d_2 = " << v2d_1 * v2d_2 << '\n';
	std::cout << "v2d_1 - v2d_2 = " << v2d_1 - v2d_2 << "\n\n";

	pause_exec();
	math_operations::euclidean::Vec3D v3d_1((rand() % 30) * 0.54, 
											(rand() % 30) * 0.54,
											(rand() % 30) * 0.54);
	math_operations::euclidean::Vec3D v3d_2((rand() % 30) * 0.54, 
											(rand() % 30) * 0.54,
											(rand() % 30) * 0.54);
	std::cout << "math_operations::euclidean::Vec3D:\n";
	std::cout << "\tv3d_1 = " << v3d_1 << '\n';
	std::cout << "\tv3d_2 = " << v3d_2 << "\n\n";
	std::cout << "v3d_1.length = " << v3d_1.length() << '\n';
	std::cout << "v3d_1.unit = " << v3d_1.unit() << '\n';
	std::cout << "v3d_1 * v3d_2 = " << v3d_1 * v3d_2 << '\n';
	std::cout << "v3d_1 - v3d_2 = " << v3d_1 - v3d_2 << "\n\n";

	std::cout << "нажмите Enter для выхода из программы...\n\n";
	std::cin.get();
	return 0;
}

