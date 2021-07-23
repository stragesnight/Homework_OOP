/*
	�������� ������� �20
		������: ������ ���������

	�������� ������ ��������� � ��������������
	������������ ������ � ������������ �����������.
*/

#include <iostream>
#include <clocale>
#include <cstring>
#include <vector>
#include <map>

#define log(msg) std::cout << "# " << msg << '\n'
#define logerr(msg) std::cout << "# ERROR: " << msg << '\n'

//#define FORCE_COMPOSITION


class Node;

std::map<std::string, Node*> expressions;
std::map<std::string, void(*)(const char*)> directives;

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
	const char* getName() { return name; }

	virtual long evaluate(std::vector<Node*>* args) = 0;
};


class NumericNode : public Node
{
private:
	long value;

public:
	NumericNode(const char* name, long value)
		: Node(name, 0)
	{
		this->value = value;
	}

	~NumericNode() override
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

/////////////////////////////////////////////////////////////////////////////////////

long parseNumber(const char* buff)
{
	long result = 0;

	for (size_t i = strlen(buff); i > 0; i--)
	{
		if (buff[i - 1] == '-')
			return -result;

		result *= 10;
		result += buff[i - 1] - '0';
	}

	return result;
}

void skipWS(const char* str, size_t& i)
{
	while (str[i] == ' ' || str[i] == '\t')
		i++;
}

int readWord(const char* src, char* buff, size_t& i)
{
	size_t len = 0;

	skipWS(src, i);

	if (src[i] == '!')
	{
		buff[len] = src[i];
		len++;
		i++;
		return len;
	}

	while ((src[i] >= 'a' && src[i] <= 'z')
		|| (src[i] >= 'A' && src[i] <= 'Z')
		|| (src[i] >= '0' && src[i] <= '9')
		|| (src[i] == '-'))
	{
		buff[len] = src[i];
		len++;
		i++;
	}

	return len;
}

/////////////////////////////////////////////////////////////////////////////////////

void def(const char* str);

/////////////////////////////////////////////////////////////////////////////////////

class MacroNode : public Node
{
private:
	enum class WORD_TYPE
	{
		SYMBOL,
		NUMERIC,
		DIRECTIVE,
		UNRECOGNIZED
	};

	char* expr;

	WORD_TYPE getWordType(const char* str)
	{
		if (*str == '!')
			return WORD_TYPE::DIRECTIVE;

		if ((*str >= 'a' && *str <= 'z')
			|| (*str >= 'A' && *str <= 'Z'))
			return WORD_TYPE::SYMBOL;

		if ((*str >= '0' && *str <= '9')
			|| (*str == '-'))
			return WORD_TYPE::NUMERIC;

		return WORD_TYPE::UNRECOGNIZED;
	}

	long evalNode(Node* node, const char* rest, size_t& i)
	{
		size_t nArgs = node->getNArgs();

		char buff[64]{};
		std::vector<Node*> args;

		for (size_t n = 0; n < nArgs; n++)
		{
			if (!readWord(rest, buff, i))
			{
				logerr("not enough arguments for symbol \"" << node->getName() << "\"");
				return -1;
			}

			WORD_TYPE word_type = getWordType(buff);

			switch (word_type)
			{
			case WORD_TYPE::NUMERIC:
			{
				args.push_back(new NumericNode("arg", parseNumber(buff)));
				break;
			}
			case WORD_TYPE::SYMBOL:
			{
				Node* next_node = expressions[buff];

				if (next_node == nullptr)
				{
					logerr("unable to find symbol \"" << buff << "\" in list");
					return -1;
				}

				args.push_back(new NumericNode("arg", evalNode(next_node, rest, i)));
				break;
			}
			case WORD_TYPE::UNRECOGNIZED:
			default:
				logerr("unexpected symbol \"" << buff << '\"');
				return -1;
			}

			memset(buff, 0, 64);
		}

		return node->evaluate(&args);
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
		long result = -1;

		if (strlen(expr) == 0)
			return 0;

		size_t i = 0;
		char buff[64]{};

		readWord(expr, buff, i);
		WORD_TYPE word_type = getWordType(buff);

		switch (word_type)
		{
		case WORD_TYPE::NUMERIC:
		{
			result = parseNumber(buff);
			break;
		}
		case WORD_TYPE::SYMBOL:
		{
			Node* node = expressions[buff];

			if (node == nullptr)
			{
				logerr("symbol \"" << buff << "\" is undefined");
				return -1;
			}

			result = evalNode(node, expr, i);
			break;
		}
		case WORD_TYPE::DIRECTIVE:
		{
			memset(buff, 0, 64);
			readWord(expr, buff, i);

			void(*directive)(const char*) = directives[buff];

			if (directive == nullptr)
			{
				logerr("directive \"" << buff << "\" is undefined");
				return -1;
			}

			directive(expr + i);

			return 1;
		}
		case WORD_TYPE::UNRECOGNIZED:
		default:
		{
			logerr("unexpected symbol \"" << buff << "\"");
			return -1;
		}
		}

		memset(buff, 0, 64);
		if (readWord(expr, buff, i))
		{
			logerr("unexpected symbol \"" << buff << "\" after finished expression");
			logerr("unexpected tail symbol would be ignored");
		}

		return result;
	}
};

/////////////////////////////////////////////////////////////////////////////////////

void def(const char* str)
{
	char buff[64] {};
	size_t i = 0;

	readWord(str, buff, i);
	MacroNode* to_add = new MacroNode(buff, str + i);

	expressions[buff] = to_add;
}

/////////////////////////////////////////////////////////////////////////////////////

long add(std::vector<Node*>* args)
{
	return args->at(0)->evaluate(nullptr) + args->at(1)->evaluate(nullptr);
}

long sub(std::vector<Node*>* args)
{
	return args->at(0)->evaluate(nullptr) - args->at(1)->evaluate(nullptr);
}

long mul(std::vector<Node*>* args)
{
	return args->at(0)->evaluate(nullptr) * args->at(1)->evaluate(nullptr);
}

long div(std::vector<Node*>* args)
{
	return args->at(0)->evaluate(nullptr) / args->at(1)->evaluate(nullptr);
}

long even(std::vector<Node*>* args)
{
	return (args->at(0)->evaluate(nullptr) & 1) == 0;
}

long odd(std::vector<Node*>* args)
{
	return (args->at(0)->evaluate(nullptr) & 1) == 1;
}

/////////////////////////////////////////////////////////////////////////////////////

int main()
{
	setlocale(LC_ALL, "rus");

	expressions["add"] = new ExpressionNode("add", 2, add);
	expressions["sub"] = new ExpressionNode("sub", 2, sub);
	expressions["mul"] = new ExpressionNode("mul", 2, mul);
	expressions["div"] = new ExpressionNode("div", 2, div);
	expressions["even"] = new ExpressionNode("even", 1, even);
	expressions["odd"] = new ExpressionNode("odd", 1, odd);

	directives["def"] = def;

	while (true)
	{
		char input[512] {};
		std::cout << "\n> ";
		std::cin.getline(input, 512);

		MacroNode expression("expr", input);
		long result = expression.evaluate(nullptr);
		log("result: " << result);
	}

	std::cin.get();
	expressions.clear();
	return 0;
}

