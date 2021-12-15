#pragma once
#include "TStack.h"
#include <iostream>
#include <string>
#include <map>


using namespace std;

class Math_expression
{
	//private:
private:
	string MatExp;
	TStack<string> RPNExp;
	map<string, double> Varibles;
	bool Error = 0;
	string ErrorText = "The solution did not run";
	double result = 0;

public:
	Math_expression(string matExp) {
		MatExp = matExp;
	}

	void Exp() {

		if (Error) {
			return;
		}
		
		if (!Check()) return;
		RPN();
		if (Error) return;

		TStack<string> exp = (RPNExp.reverse());
		TStack<double> nums = TStack<double>(1);
		double a, b;

		string letter = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		string num = "0123456789";

		while (!exp.IsEmpty()) {
			string str = exp.Pop();
			if (str.find_first_of(letter) != string::npos) {
				if (Varibles.count(str)) {
					nums.Push(Varibles[str]);
					continue;
				}
				else {
					//cout << "No varible str";
					Error = 1;
					ErrorText = "No varible";
					break;
				}
			}

			if (str.find_first_of(num) != string::npos) {
				nums.Push(stod(str));
				continue;
			}

			switch (str[0])
			{
			case '-':
				 b = nums.Pop();
				 a = nums.Pop();
				 nums.Push(a - b);
				break;
			case '+':
				b = nums.Pop();
				a = nums.Pop();
				nums.Push(a + b);
				break;
			case'/':
				b = nums.Pop();
				a = nums.Pop();
				if (b == 0) {
					//cout << "division by 0 is not possible ";
					Error = 1;
					ErrorText = "division by 0 is not possible";
					break;
				}
				nums.Push(a / b);
				break;
			case'*':
				b = nums.Pop();
				a = nums.Pop();
				nums.Push(a * b);
				break;

			default:
				break;
			}

		}

		if (Error) {
			return;
		}

		result = nums.Pop();
		ErrorText = "No error";
		return ;
	}

	string GetError() {
		return ErrorText;
	}

	void PrintRPN(){
		if (ErrorText == "The solution did not run") {
			cout << "The solution did not run";
			return;
		}
		RPNExp.print();
	}

	double GetResult() {
		return result;
	}

private:

	bool Check() {
		TStack<char> st = TStack<char>();

		for (char i : MatExp) {
			if (i == '\n') break;

			if (i == '(') {
				st.Push('(');
			}
			else {
				if (i == ')') {
					if (!st.IsEmpty()) {
						st.Pop();
					}
					else {
						//cout << "Brackets error";
						ErrorText = "Brackets error";
						return false;
					}
				}
			}
		}

		if (!st.IsEmpty()) {
			//cout << "Brackets error";
			ErrorText = "Brackets error";
			return false;
		}
		return true;
	}

	TStack<string> RPN() {
		map<char, int> op({ { '+',1 },
								{'-',1},
								{'*',2},
								{'/',2},
								{'(',-1} });

		TStack<string> operation(5);
		TStack<string> exp(5);
		string num = "";
		bool lastNum = 0;
		bool space = 0;

		for (char s : MatExp) {
			if (s == ' ') {
				space = 1;
				continue;
			}
			if (s == '\n')  break;


			if (s == ';') {
				if (num != "") {
					exp.Push(num);
				}

				while (!operation.IsEmpty()) {
					exp.Push(operation.Pop());
				}


				RPNExp = exp;
				Varib(MatExp.substr(MatExp.find(';') + 1));
				if (Error) {
					return TStack<string>();
				}
				return exp; // Функция для выделения переменных
			}

			if (isdigit(s) || s == '.'  || isalpha(s)) {
				if (space && lastNum) {
					//cout << "Two num error";
					ErrorText = "Two num error";
					Error = 1;
					return TStack<string>();
					break;
				}
				num += s;
				lastNum = 1;
				space = 0;
			}
			else {
				space = 0;
				if (num != "") {
					exp.Push(num);
				}

				num = "";
				switch (s)
				{
				case ')':

					if (lastNum == 0) {
						//cout << "Fail expression";
						ErrorText = "Fail expression";
						Error = 1;
						return TStack<string>();
						break;
					}

					while (operation.Top() != "(") {
						if (operation.Top() != " ") {
							exp.Push(operation.Pop());
						}
						else {
							operation.Pop();
						}
					}
					operation.Pop();
					lastNum = 1;
					break;

				case '(':
					if (lastNum == 1) {
						//cout << "Fail expression";
						ErrorText = "Fail expression";
						Error = 1;
						return TStack<string>();
						break;
					}

					operation.Push("(");


					lastNum = 0;
					break;
				default:
					if (lastNum == 0) {
						
						//cout << "Fail expression";
						ErrorText = "Fail expression";
						Error = 1;
						return TStack<string>();
						break;
					}

					if (!op.count(s)) {
						//cout << "Uncnown symbol " << s;
						ErrorText = "Uncnown symbol " ;
						ErrorText += s;
						Error = 1;
						return TStack<string>();
						break;
					}

					while((!operation.IsEmpty()) &&  (op[*operation.Top().c_str()] >= op[s])) {
						exp.Push(operation.Pop());
					}


					string a = string(1,s);

					operation.Push(a);
					lastNum = 0;

					break;
				}

			}

			
		}

		if (num != "") {
			exp.Push(num);
		}

		while (!operation.IsEmpty()) {
			exp.Push(operation.Pop());
		}

		RPNExp = exp;
		return  exp;
	}

	map<string, double> Varib(string s) {

		string Varib = "";
		string num = "";
		bool sign = 0;
		bool er = 0;
		bool ln = 0;
		bool minus = false;

		for (char c : s) {
			if (c == ' ') continue;
			if (c == '\n')  break;

			if (er == 1) break;

			if (sign == 1) {
				switch (c)
				{
				case ';':
					if (num == "") {
						//cout << "Fail num";
						ErrorText = "Fail num";
						Error = 1;
						er = 1;
						continue;
					}
					if (Varibles.find(Varib) != Varibles.end()){
						ErrorText = "the variables have the same names";
						Error = 1;
						er = 1;
						continue;
					}
					Varibles.insert({Varib, stod(num)});
					Varib = "";
					num = "";
					sign = 0;
					minus = false;
					break;
				default:
					if (isdigit(c) || c == '.' || c == '-') {
						minus = true;
						num += c;
					}
					else {
						//cout << "Fail Varible";
						ErrorText = "Fail Varible";
						Error = 1;
						er = 1;
						continue;
					}
					break;
				}
				continue;
			}
			

			if (isdigit(c) || isalpha(c)) {
				Varib += c;
			}

			if (c == '=') {
				if (Varib == "") {
					//cout << "Fail Varible";
					ErrorText = "Fail Varible";
					Error = 1;
					er = 1;
					continue;
				}
				sign = 1;
			}
		}

		if (er) return map<string,double>();

		if (num != "") {
			if (Varibles.find(Varib) != Varibles.end()) {
				ErrorText = "the variables have the same names";
				Error = 1;
				er = 1;
			}
			else {
				Varibles.insert({ Varib, stod(num) });
			}
		}

		// Рассмотреть случаи где до либо после = нет знаков;
		return Varibles;
	}

};

