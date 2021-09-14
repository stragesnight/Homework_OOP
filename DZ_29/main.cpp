/*
 * 	-= Домашнее Задание №29 =-
 * 		Ученик: Шелест Алексвндр
 *
 * 	используя класс string, написать программу для
 * 	анализа строки, содержащей математическое выражение.
 * 	результат выражения вывести на экран.
 */

#include <iostream>
#include <clocale>
#include <string>
#include <vector>
#include <map>


// возможные типы токенов выражения
enum class token_type : char 
{ 
	NUMERAL,  		// числовая константа
	OPERATION, 		// операция (+, -, *. /)
	OPEN_PAREN,  	// открытая скобка
	CLOSED_PAREN, 	// закрытая скобка
	END 			// конец выражения
};

// токен - еденица информации в выражении
struct token
{
	token_type type;
	int data;
};


std::ostream& operator<<(std::ostream& ostr, const token& t) 
{
	switch (t.type)
	{
	case token_type::NUMERAL:
		ostr << "numerical token \'" << t.data << '\'';
		break;
	case token_type::OPERATION:
		ostr << "operation token \'" << (char)t.data << '\'';
		break;
	case token_type::OPEN_PAREN:
	case token_type::CLOSED_PAREN:
		ostr << "paren token \'" << (char)t.data << '\'';
		break;
	case token_type::END:
		ostr << "END token";
	}

	return ostr;
}

// класс для лексической обработки строки - её превращения в токены
class lexer
{
private:
	// прочесть числовую константу из строки
	int parse_int(std::string::iterator& it)
	{
		int res = 0;

		while (*it >= '0' && *it <= '9')
		{
			res *= 10;
			res += *it - '0';

			it++;
		}

		return res;
	}

	// пропустить "белое место" в строке
	void skip_ws(std::string::iterator& it)
	{
		while (*it == ' ' || *it == '\t' || *it == '\n')
			it++;
	}

	// прочесть один токен из строки
	token read_token(std::string::iterator& it)
	{
		token res {};

		skip_ws(it);
		char next = *it;
		it++;

		switch (next)
		{
		case '(':
			res.type = token_type::OPEN_PAREN;
			res.data = (int)next;
			break;
		case ')':
			res.type = token_type::CLOSED_PAREN;
			res.data = (int)next;
			break;
		case '+':
		case '-':
		case '*':
		case '/':
			res.type = token_type::OPERATION;
			res.data = (int)next;
			break;
		default:
			if (next >= '0' && next <= '9')
			{
				res.type = token_type::NUMERAL;
				it--;
				res.data = parse_int(it);
				break;
			}

			throw exception("unknown symbol", next);
		}

		return res;
	}

public:
	// класс лексического исключения
	class exception
	{
	private:
		std::string msg;
		char sym;
	public:
		exception(const std::string& _msg, char _sym)
			: msg(_msg), sym(_sym)
		{}
		std::string what() 
		{ 
			return "lexical error: " + msg + " at \'" + sym + '\''; 
		}
	};

	// превратить исходную строку в массив токенов
	std::vector<token>* tokenize(std::string& str)
	{
		std::vector<token>* res = new std::vector<token>();
		std::string::iterator it = str.begin();
		std::string::iterator end = str.end();

		while (it != end)
			res->push_back(read_token(it));
		res->push_back(token{token_type::END, 0});

		return res;
	}
};

// контекстно-свободная грамматика для математических выражений:
// (без неоднозначности)
//
// Expr 	-> V LExpr
// 
// LExpr 	-> + Expr
// LExpr 	-> - Expr
// LExpr 	-> TExpr LExpr
// LExpr 	-> e
// 
// TExpr 	-> * V
// TExpr 	-> / V
//
// V 		-> NUMERAL
// V 		-> (Expr)

// класс для синтаксической и грамматической обработки строки
class parser
{
private:
	int eval_expr(std::vector<token>::iterator& it)
	{
		return eval_lexpr(it, eval_v(it));
	}

	int eval_lexpr(std::vector<token>::iterator& it, int prev)
	{
		std::vector<token>::iterator tmp = it;
		it++;

		switch (tmp->type)
		{
		case token_type::OPERATION:
		{
			char op = (char)tmp->data;
			switch (op)
			{
			case '+':
				return prev + eval_expr(it);
			case '-':
				return prev - eval_expr(it);
			case '*':
			case '/':
				return eval_lexpr(it, eval_texpr(--it, prev));
			default:
				throw exception("unknown operation", *tmp);
			}
		}
		case token_type::CLOSED_PAREN:
		case token_type::END:
			return prev;
		default:
			throw exception("unexpected lexpr token", *tmp);
		}

		return -1;
	}

	int eval_texpr(std::vector<token>::iterator& it, int prev)
	{
		std::vector<token>::iterator tmp = it;
		it++;

		switch (tmp->type)
		{
		case token_type::OPERATION:
		{
			char op = (char)tmp->data;
			switch (op)
			{
			case '*':
				return prev * eval_v(it);
			case '/':
				return prev / eval_v(it);
			default:
				throw exception("unknown operation", *tmp);
			}
		}
		default:
			throw exception("unexpected texpr token", *tmp);
		}

		return -1;
	}

	int eval_v(std::vector<token>::iterator& it)
	{
		std::vector<token>::iterator tmp = it;
		it++;

		switch (tmp->type)
		{
		case token_type::OPEN_PAREN:
		{
			int res = eval_expr(it);
			if ((it - 1)->type != token_type::CLOSED_PAREN)
				throw exception("unmatched paren", *it);

			return res;
		}
		case token_type::NUMERAL:
			return tmp->data;
		default:
			throw exception("unexpected expression", *tmp);
		}

		return -1;
	}

public:
	// вычислить результат выражения из массива токенов
	int parse(std::vector<token>* tokens)
	{
		std::vector<token>::iterator it = tokens->begin();
		return eval_expr(it);
	}

	// класс лексических и грамматический исключений
	class exception
	{
	private:
		std::string msg;
		token t;
	public:
		exception(const std::string& _msg, token _t)
			: msg(_msg), t(_t)
		{}
		std::string what() 
		{ 
			return "syntax error: " + msg; 
		}

		const token& get_token() { return t; }
	};

};

// проверить ввод на специальные комманды
bool check_commands(const std::string& input)
{
	if (input == "exit")
	{
		exit(0);
	}
	else if (input == "examples")
	{
		std::cout << "\nпримеры выражений:\n";
		std::cout << "2 + 2\t\t\t// = 4\n";
		std::cout << "1+2 * (3 - 4)\t\t// = -1\n";
		std::cout << "2 + 3*(4 + 1)\t\t// = 17\n";
		std::cout << "(2 + 3)*4 + 1\t\t// = 21\n";
		std::cout << "15 - (14/(4+3) - 2)\t// = 15\n";
		std::cout << "15 - (14/(4 + (3-2)))\t// = 13\n";

		return true;
	}
	else if (input == "greeting")
	{
		std::cout << "\t-= Домашнее Задание №29 =-\n"
			<< "\t\tУченик: Шелест Алексвндр\n\n"
			<< "используя класс string, написать программу для\n"
			<< "анализа строки, содержащей математическое выражение.\n"
			<< "результат выражения вывести на экран.\n\n";
		std::cout << "доступные комманды:\n";
		std::cout << "  exit - выход из программы\n";
		std::cout << "  examples - примеры выражений\n";
		std::cout << "  greeting - это сообщение\n\n";
		std::cout << "введите выражение для обрабоки:";

		return true;
	}

	return false;
}

int main()
{
	setlocale(LC_ALL, "rus");

	lexer l;
	parser p;

	check_commands("greeting");
	check_commands("examples");

	while (true)
	{
		std::string input = "";

		while (input == "")
		{
			std::cout << "\n> ";
			std::getline(std::cin, input);
		}

		if (check_commands(input))
			continue;

		// обработать строку и словить любые лексические/синтаксические ичключения
		try
		{
			std::vector<token>* tokens = l.tokenize(input);
			int res = p.parse(tokens);
			std::cout << "  = " << res << ";\n";
		}
		catch (lexer::exception& ex)
		{
			std::cout << ex.what() << '\n';
		}
		catch (parser::exception& ex)
		{
			std::cout << ex.what() << " on " << ex.get_token() << '\n';
		}
	}

	return 0;
}

