/*
	Домашнее задание №20
		Ученик: Шелест Александр

	Написать пример программы с использованием 
	абстрактного класса и виртуального деструктора.
*/

#include <iostream>
#include <clocale>
#include <cstring>
#include <vector>
#include <map>

class Node;

std::map<std::string, Node*> expressions;
std::map<std::string, const char*> macro_expressions;

class Node
{
protected:
	char* name;
	size_t nArgs;

public:
	Node(const char* name, size_t nArgs = 0)
	{
		this->nArgs = nArgs;
	
		size_t len = strlen(name);
		this->name = new char[len + 1];

		for (size_t i = 0; i < len; i++)
			this->name[i] = name[i];
		this->name[len] = '\0';
	}

	virtual ~Node()
	{
		delete[] name;
	}

	size_t getNArgs() { return nArgs; }
	
	virtual long evaluate(std::vector<Node*>* args) = 0;
};


class NumericalNode : public Node
{
private:
	long value;

public:
	NumericalNode(const char* name, long value)
		: Node(name, 0)
	{
		this->value = value;
	}

	~NumericalNode() override
	{
		value = 0;
	}

	long evaluate(std::vector<Node*>*) override
	{
		return value;
	}
};


class ExpressionNode : public Node
{
private:
	long (*func)(std::vector<Node*>*);
	
public:
	ExpressionNode(const char* name, size_t nArgs, long(*func)(std::vector<Node*>*))
		: Node(name, nArgs)
	{
		this->func = func;
	}

	~ExpressionNode() override
	{
		func = nullptr;
	}

	long evaluate(std::vector<Node*>* args) override
	{
		return func(args);
	}
};

class MacroNode : public Node
{
private:
	enum class SYM_TYPE
	{
		SYMBOL,
		NUMERIC,
		OPEN_PAREN,
		CLOSED_PAREN,
		MISC
	};

	char* expr;
	
	void skipWS(size_t& i)
	{
		while (expr[i] == ' ' || expr[i] == '\t')
			i++;
	}
	
	void readWord(char* buff, size_t& i)
	{
		size_t len = 0;
		while((expr[i] >= 'a' && expr[i] <= 'z')
			|| (expr[i] >= 'A' && expr[i] <= 'Z'))
		{
			buff[len] = expr[i];
			len++;
			i++;
		}

		std::cout << "red word \"" << buff << "\"\n";
	}
	
	std::string expand()
	{
		std::string res = "";
		size_t len = strlen(expr);
		char buff[512];

		for (size_t i = 0; i < len; i++)
		{
			size_t i_start = i;
		
			memset(buff, 0, 512);
			skipWS(i);

			readWord(buff, i);

			if (macro_expressions[buff] != NULL)
			{
				res += macro_expressions[buff];
				i = i_start;
			}
			else
			{
				std::cout << "no macro found for \"" << buff << "\"\n";
			}
		}

		return res;
	}

public:
	MacroNode(const char* name, const char* expr)
		: Node(name, 0)
	{
		size_t len = strlen(expr);
		this->expr = new char[len + 1];

		for (size_t i = 0; i < len; i++)
			this->expr[i] = expr[i];
		this->expr[len] = '\0';
	}

	~MacroNode() override
	{
		delete expr;
	}

	long evaluate(std::vector<Node*>* args) override
	{
		long result = 0;

		//expand();
		size_t i = 0;
		char buff[512]{};
		readWord(buff, i);

		if (expressions[buff] == NULL)
		{
			std::cout << "no expression found for \"" << buff << "\"\n";
			return -1;
		}

		
		
		return result;
	}
};

long add(std::vector<Node*>* args)
{
	if (args->size() != 2)
	{
		std::cout << "invalid number of arguments, expected 2\n";
		return -1;
	}

	return args->at(0)->evaluate(nullptr) + args->at(1)->evaluate(nullptr);
}

long sub(std::vector<Node*>* args)
{
	if (args->size() != 2)
	{
		std::cout << "invalid number of arguments, expected 2\n";
		return -1;
	}

	return args->at(0)->evaluate(nullptr) - args->at(1)->evaluate(nullptr);
}

long mul(std::vector<Node*>* args)
{
	if (args->size() != 2)
	{
		std::cout << "invalid number of arguments, expected 2\n";
		return -1;
	}

	return args->at(0)->evaluate(nullptr) * args->at(1)->evaluate(nullptr);
}

long div(std::vector<Node*>* args)
{
	if (args->size() != 2)
	{
		std::cout << "invalid number of arguments, expected 2\n";
		return -1;
	}

	return args->at(0)->evaluate(nullptr) / args->at(1)->evaluate(nullptr);
}

int main()
{
	setlocale(LC_ALL, "rus");

	expressions["add"] = new ExpressionNode("add", 2, add);
	expressions["sub"] = new ExpressionNode("sub", 2, sub);
	expressions["mul"] = new ExpressionNode("mul", 2, mul);
	expressions["div"] = new ExpressionNode("div", 2, div);
	expressions["a"] = new NumericalNode("a", 2);
	expressions["b"] = new NumericalNode("b", 3);

	MacroNode mn("macronode", "add a b");
	long res = mn.evaluate(nullptr);
	std::cout << "\"add(a b)\" evaluated to " << res << '\n';
	
	std::cin.get();
	return 0;
}

