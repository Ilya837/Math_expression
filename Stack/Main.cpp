//#include "TStack.h"
#include "Math_expression.h"
#include "TStack.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
	string m1 = "1 + 2";
	string m2 = "1 + 2* (3-2) - 4";
	string m3 = "(((1+23)*1-22)+5)*2-(7";
	string m4 = "1 + 2/(3-3)";
	string m5 = "1 ++ 1";
	string m6 = "20 / 2 * 5";
	string m7 = "20 * 2 / 5";
	string m8 = "20*    4";
	string m9 = "20/0";
	string m10 = "20/0.0";
	string m11 = "20/0.0 * 10";
	string m12 = "0/0";
	string m13 = "1/3";
	string m14 = "1/0.0000003";
	string m15 = "0.0000003 / 0.0000003";
	string m16 = "0.1 + 0.2";
	string m17 = "(1 + 1 ] 2[2 + 11)a + b; a = 2.5; b = 63";
	string m18 = "20 / 2 / 5";
	string m19 = "1 (20)";
	string m20 = "7 ** 3";
	string m21 = "2 + 4 * (1 + a); a=10";
	string m22 = "2*(1+2/3)+2";
	string m23 = "2 ** 4";
	string m24 = "2 + 2*2";
	string m25 = "1 + b; a=42";
	string m26 = "1 + 2";
	string m27 = "1 + 2 * (3-2)-4";
	string m28 = "(((1+23)*1-22)+5)*2-(1";
	string m29 = "1 + a; a=5";
	string m30 = "2 * a + b - c; a=5; b=7; c=-3";
	string m31 = "5 // 5";

	vector<string> expressions(0);

	{
		expressions.push_back(m1);
		expressions.push_back(m2);
		expressions.push_back(m3);
		expressions.push_back(m4);
		expressions.push_back(m5);
		expressions.push_back(m6);
		expressions.push_back(m7);
		expressions.push_back(m8);
		expressions.push_back(m9);
		expressions.push_back(m10);
		expressions.push_back(m11);
		expressions.push_back(m12);
		expressions.push_back(m13);
		expressions.push_back(m14);
		expressions.push_back(m15);
		expressions.push_back(m16);
		expressions.push_back(m17);
		expressions.push_back(m18);
		expressions.push_back(m19);
		expressions.push_back(m21);
		expressions.push_back(m22);
		expressions.push_back(m23);
		expressions.push_back(m24);
		expressions.push_back(m25);
		expressions.push_back(m26);
		expressions.push_back(m27);
		expressions.push_back(m28);
		expressions.push_back(m29);
		expressions.push_back(m30);
		expressions.push_back(m31);
	}

	

	for (string exp : expressions) {
		Math_expression  m = Math_expression(exp);
		cout << "-------------------------------------------------------------"<<endl;
		cout << exp <<endl << endl;
		m.Exp();
		if (m.GetError() != "The solution did not run" && m.GetError() != "No error") {
			cout <<"Error: "<< m.GetError()<< endl;
		}
		else {
			cout << "Reverse Polish notation: ";
			m.PrintRPN();
			cout <<endl << endl <<"Result: " <<m.GetResult() << endl;
		}
	}
	cout << "-------------------------------------------------------------" << endl;
	 
    return 0;
}