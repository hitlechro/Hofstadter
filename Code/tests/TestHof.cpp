#include <QtTest/QtTest>
#include "../Calculator.h"
#include <Vector>
#include "../Errors.h"
#include <iostream>

class TestHof: public QObject{
	Q_OBJECT
private slots:
	void Calculator_isOperator();
	void Calculator_isNumber();
	void Calculator_toNumber();
	/*void Calculator_evaluate();
	void Calculator_stringEvaluate();
	void Calculator_algebraEvaluate();
	void Calculator_saveParameters();*/
	void Calculator_getParameterNames();
	void Calculator_createMap();
	/*void Calculator_toString();
	void Calculator_tokenize();
	void Calculator_parseOperand();
	void Calculator_stripSpaces();
	
	void Sequence_compute();
	void Sequence_print();
	void Sequence_satisfiedConstraint();
	void Sequence_dieImmediately();
	void Sequence_analyse();
	void Sequence_computeSlowness();
	void Sequence_computeGeneration();
	void Sequence_checkContainSubstring();
	void Sequence_checkContainSubsequence();
	void Sequence_checkFrequencyMatch();
	void Sequence_computeAddition();
	void Sequence_computeRnDivN();
	void Sequence_computeTwoRnMinusN();
	void Sequence_computeFrequency();*/

};

void TestHof::Calculator_isOperator(){	
	QCOMPARE(true, Calculator::isOperator("+"));
	QCOMPARE(true, Calculator::isOperator("-"));
	QCOMPARE(true, Calculator::isOperator("*"));
	QCOMPARE(true, Calculator::isOperator("/"));

	QCOMPARE(false, Calculator::isOperator("1"));
	QCOMPARE(false, Calculator::isOperator("Q"));
	QCOMPARE(false, Calculator::isOperator(" "));
	QCOMPARE(false, Calculator::isOperator("+-"));
	QCOMPARE(false, Calculator::isOperator("\\"));
	QCOMPARE(false, Calculator::isOperator(string()));
}
void TestHof::Calculator_isNumber(){
	QCOMPARE(true, Calculator::isNumber("12456"));
	QCOMPARE(true, Calculator::isNumber("0"));
	QCOMPARE(true, Calculator::isNumber("-157"));

	QCOMPARE(false, Calculator::isNumber(""));
	QCOMPARE(false, Calculator::isNumber("A"));
	QCOMPARE(false, Calculator::isNumber("A1"));
	QCOMPARE(false, Calculator::isNumber("+"));
	QCOMPARE(false, Calculator::isNumber("0x1"));
	QCOMPARE(false, Calculator::isNumber(string()));
}
void TestHof::Calculator_toNumber(){
	QCOMPARE(4, Calculator::toNumber("4"));
	QCOMPARE(-8, Calculator::toNumber("-8"));
	try{
		Calculator::toNumber("");
	}catch(int e){
		QCOMPARE(e, ESTRING);
	}
	
	try{
		Calculator::toNumber("cake");
	}catch(int e){
		QCOMPARE(e, ESTRING);
	}
	
	try{
		Calculator::toNumber(string());
	}catch(int e){
		QCOMPARE(e, ESTRING);
	}
}
/*void TestHof::Calculator_evaluate(){
	QCOMPARE(true, false);
}
void TestHof::Calculator_stringEvaluate(){
	QCOMPARE(true, false);
}
void TestHof::Calculator_algebraEvaluate(){
	QCOMPARE(true, false);
}
void TestHof::Calculator_saveParameters(){
	QCOMPARE(true, false);
}
*/
void TestHof::Calculator_getParameterNames(){
	string s = "R(n-a)+R(n-b)";
	vector<string> e = vector<string>();
	e.push_back("a");
	e.push_back("b");
	QCOMPARE(Calculator::getParameterNames(s), e);
	
	s = "R(n-1)+R(n-b)";
	e = vector<string>();
	e.push_back("b");
	QCOMPARE(Calculator::getParameterNames(s), e);
	
	s = "R(n-R(n-a))";
	e = vector<string>();
	e.push_back("a");
	QCOMPARE(Calculator::getParameterNames(s), e);
	
	s = "";
	e = vector<string>();
	QCOMPARE(Calculator::getParameterNames(s), e);
	
	s = "R(n-R(n-a))";
	e = vector<string>();
	e.push_back("a");
	QCOMPARE(Calculator::getParameterNames(s), e);

	s = "R(n-R(n-a_1)) - R(n-R(n-a1)) * R(n-R(n-b_1))";
	e = vector<string>();
	e.push_back("a_1");
	e.push_back("a1");
	e.push_back("b_1");
	QCOMPARE(Calculator::getParameterNames(s), e);
	
	s = "R(n-R(n-1)) - R(n-R(n-2))";
	e = vector<string>();
	QCOMPARE(Calculator::getParameterNames(s), e);

}

void TestHof::Calculator_createMap(){
	vector<string> v_0 = vector<string>();
	v_0.push_back("a");
	v_0.push_back("b");
	v_0.push_back("c");
	
	vector<string> v_1 = vector<string>();
	v_0.push_back("a");
	
	vector<string> v_2 = vector<string>();
}

/*
void TestHof::Calculator_toString(){
	QCOMPARE(true, false);
}
void TestHof::Calculator_tokenize(){
	QCOMPARE(true, false);
}
void TestHof::Calculator_parseOperand(){
	QCOMPARE(true, false);
}
void TestHof::Calculator_stripSpaces(){
	QCOMPARE(true, false);
}
 
void TestHof::Sequence_compute(){
	QCOMPARE(true, false);
}
void TestHof::Sequence_print(){
	QCOMPARE(true, false);
}
void TestHof::Sequence_satisfiedConstraint(){
	QCOMPARE(true, false);
}
void TestHof::Sequence_dieImmediately(){
	QCOMPARE(true, false);
}
void TestHof::Sequence_analyse(){
	QCOMPARE(true, false);
}
void TestHof::Sequence_computeSlowness(){
	QCOMPARE(true, false);
}
void TestHof::Sequence_computeGeneration(){
	QCOMPARE(true, false);
}
void TestHof::Sequence_checkContainSubstring(){
	QCOMPARE(true, false);
}
void TestHof::Sequence_checkContainSubsequence(){
	QCOMPARE(true, false);
}
void TestHof::Sequence_checkFrequencyMatch(){
	QCOMPARE(true, false);
}
void TestHof::Sequence_computeAddition(){
	QCOMPARE(true, false);
}
void TestHof::Sequence_computeRnDivN(){
	QCOMPARE(true, false);
}
void TestHof::Sequence_computeTwoRnMinusN(){
	QCOMPARE(true, false);
}
void TestHof::Sequence_computeFrequency(){
	QCOMPARE(true, false);
}
 */

QTEST_MAIN(TestHof)
#include "TestHof.moc"