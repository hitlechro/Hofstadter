/*#include <QtGui>
#include <QVariant>
#include <QRegExp>*/
#include <string>
#include <iostream>
#include <sstream>
#include "Calculator.h"
#include "errors.h"
#include <math.h>
#include <stdlib.h>
#include <QStringList>

using namespace std;

typedef vector<int> Vector;

vector<string> Calculator::paraNames = vector<string>();
map<string, int> Calculator::paraMap = map<string, int>();

/**
 * Returns true iff s is a operator: + - * / ( ) ^ [ ] R SUM
 * @param s The string to check
 * @returns true iff s is one of the above operators
 */
bool Calculator::isOperator(string s){
    return (s == "+" || s == "-" || s == "*" || s == "/" || s == "^");
            /*s == "SUM" || s == "[" || s == "]"*/ // FIXME
} 

/**
  * Tokenizes a given string, returning a vector of the results
  * @param s The string to tokenize.
  * @return A vector containing all tokens in s (operators and R expressions).
  */
vector<string> Calculator::tokenize(string s) {
    vector<string> V;
    int pdepth = 0;
    int j = 0;
    bool inparen = 0;

    s = stripSpaces(s);

    while(j < s.length()){

        string sub = s.substr(0, j);
        string next = s.substr(j, 1);
        if(s.substr(j, 2) == "R("){
            inparen = true;
            j++;
            pdepth++;
        }else if(s.substr(j, 1) == "("){
            pdepth++;
            inparen = true;
        }else if(s.substr(j, 1) == ")"){
            pdepth--;
        }

        /* If you just finished a bracketed section, push it and start again*/
        if(pdepth == 0){
            if(inparen){
                V.push_back(s.substr(0, j+1));
                s.erase(0, j+1);
                j = 0;
                inparen = false;
                continue;
            }
            /* If you're not in a bracket and the next char is an operator, push it */
            else if(isOperator(s.substr(0, 1))){
                V.push_back(s.substr(0, 1));
                s.erase(0, 1);
                continue;
            }

            else{
                int endPoint = 0;
                while(endPoint <= s.length() && !isOperator(s.substr(endPoint++, 1)));

                V.push_back(s.substr(0, endPoint-1));
                s.erase(0, endPoint-1);
                j = 0;
            }

        }else{
            j++;
        }
    }
    if(!s.empty()){
        V.push_back(s);
    }
    return V;
}

/**
  * Returns true iff s represents a decimal integer
  * Returns false for the empty string
  * @param s The string to check
  * @return true iff s contains only numbers
  */
bool Calculator::isNumber(string s){
    if (s.length() == 0)
        return false;

    for (int i = 0; i < s.length(); i++){
        if (!isdigit(s[i]) && !(i == 0 && s[i] == '-'))
			return false;
    }
    return true;
}

/**
  * Returns the value that s represents.\n
  * If s is a number, that value it returned.\n
  * Otherwise s is treated as a variable and its value is returned.
  * @param s The value to parse
  * @return An int containing the value that s represents
  */
int Calculator::parseOperand(string s){
	if (isNumber(s)){
        return toNumber(s);
    } else if (s != " "){
        //return paraMap[s];
        return paraValue[paraID[s]]; // ???
    } else {
        throw ESTRING;
    }
}

/**
  * Returns an int containing the value represented by a string
  * @param s The string containing the value
  * @return The value contained in s
  */
int Calculator::toNumber(string s){
    if(isNumber(s)){
        int t;
        stringstream ss(s);
        ss >> t;
        return t;
    }else{
        throw ESTRING;
    }
}

/**
  * Evaluates a tokenized expression
  * @param n The value to use for n
  * @param R A vector containing all values R(x), x < n
  * @param s The tokenized expression
  * @return The value the expression evaluates to
  */
int Calculator::evaluate(int n, vector<int>& R, vector<string> s){
    evaluate(n, R, s, 0, 1, 1);
}

/**
  * Evaluates a tokenized expression
  * @param n The value to use for n
  * @param R A vector containing all values R(x), x < n
  * @param s The tokenized expression
  * @param n_0 The index of the first IC.
  * @return The value the expression evaluates to
  */
int Calculator::evaluate(int n, vector<int>& R, vector<string> s, bool anchor, int anchorValue, signed int n_0){

    /* if n is one of the IC, return R(n) */
    /* if n is a negative index, return an error */

    int index = n+(1-n_0);
    if(n < n_0){
        if (anchor) {
            return anchorValue;
        } else {
            throw EINDEX;
        }
    }else if(index < R.size()) {
        return R.at(index);
    }	 // todo: is this reliable?

    // used later in the function.
    //bool isParameter = s.size() == 1
    //        && paraID.find(s[0]) != paraID.end();

    /* Evaluates all algebraic expressions in the vector.
    This is recursive, so all subexpressions are evaluated as well. */
    //int ret = 0;
    if(s.size() == 1){
        s[0] = toString(stringEvaluate(n, R, s[0], anchor, anchorValue, n_0));
    }else{
        for (int i = 0; i < s.size(); i++){
            /* If s[i] is a variable, treat it as one */
            if(!isOperator(s[i]) && !isNumber(s[i])){
                if(s[i] == "n"){
                    s[i] = toString(n);
                }else {
                    int eval = evaluate(n, R, tokenize(s[i]), anchor, anchorValue, n_0);
                    s[i] = toString(eval);
                }
            }
        }
    }

    //todo: use algebraEvaluate for this part?
    /* The following 3 sections follow the order of operations:
        ^, then * /, then + -
        Other operations (such as brackets or functions) can be added
        later as long as they are inserted in the correct place, and
        use the same basic format:
        for(...) { if(s[i] == token) { ... } ... }
        */

    /* Performs all exponent operations */
    for(int i = 0; i < s.size(); i++){
        if(s[i] == "^"){
            if (exponentiation_is_safe(toNumber(s[i-1]), toNumber(s[i+1]))) {
                s[i-1] = toString((double) pow(toNumber(s[i-1]), (double) toNumber(s[i+1])));
                s.erase(s.begin()+i, s.begin()+i+2);
                i-=2;
            } else {
                throw EFLOW;
            }
        }
    }

    /* Performs all multiplication and division */
    for(int i = 0; i < s.size(); i++){
        if(s[i] == "*"){
            if (multiplication_is_safe(toNumber(s[i-1]), toNumber(s[i+1]))) {
                s[i-1] = toString(toNumber(s[i-1]) * toNumber(s[i+1]));
                s.erase(s.begin()+i, s.begin()+i+2);
                i-=2;
            } else {
                throw EFLOW;
            }
        }else if(s[i] == "/"){
            //todo: check for 0!
            s[i-1] = toString(toNumber(s[i-1]) / toNumber(s[i+1]));
            s.erase(s.begin()+i, s.begin()+i+2);		/* erasing i..i+2 removes the operator and 2nd operand */
            i-=2;
        }
    }

    /* Performs addition and subtraction. Because these are the last operations
    that will happen, we just use an int to store the results of them, then
    return that int */
    for(int i = 0; i < s.size(); i++){
        if(s[i] == "+"){
            if (addition_is_safe(toNumber(s[i-1]), toNumber(s[i+1]))) {
                s[i-1] = toString(toNumber(s[i-1]) + toNumber(s[i+1]));
                s.erase(s.begin()+i, s.begin()+i+2);
                i-=2;
            } else {
                throw EFLOW;
            }
        } else if(s[i] == "-") {
            s[i-1] = toString(toNumber(s[i-1]) - toNumber(s[i+1]));
            s.erase(s.begin()+i, s.begin()+i+2);
            i-=2;
        }
    }

    // todo: ECODE
    // handle bad syntax
    if (s.size() != 1){
        throw ESYNTAX;
    }

    // return the last remaining value (which will be the solution)
    return toNumber(s[0]);
}


/**
  * Evaluates a given string, but one that does not contain algebraic expressions.\n
  * If an initalized variable is passed (including n), then that variable's
  * value is returned.\n
  * If a number is passed, that number is returned as an int.\n
  * If an R expression (eg: R(n-2), R(R(n-1))) is passed, it is evaluated and
  * that value is returned.
  * If an algebraic expression is passed (eg: 4*3+2), an error will occur.
  * @param s The string to evaluate
  * @param n The value of n
  * @param n_0 The index of the first IC
  * @return The value that s evaluates too
  */
int Calculator::stringEvaluate(int n, vector<int> &R, string s, bool anchor, int anchorValue, signed int n_0){
    if (s == "n"){
        return n;
    }else if(s.substr(0, 1) == "R"){
        string sub = s.substr(2, s.length()-3);
        int index = evaluate(n, R, tokenize(sub), anchor, anchorValue, n_0) + (1-n_0); // the 2nd term returns the correct index
        if (index < 1 && anchor) {
            return anchorValue;
        } else if (index < 1 || index >= R.size()){
            throw EINDEX;  // why not throw it?
        } else {
            return R.at(index); //getR(toString(index));
        }
    }else {
        return parseOperand(s);
    }
}

/**
 * Evaluates a simple algebraic expression.\n
 * Supports "simple" operations (^, *, /, +, -) and parameters that have
 * been saved by the program.\n
 * Does not support parentheses.
 * @example algebraEvaluate("1+4*2") --> 9
 * @example algebraEvaluate("a+3") (if a = 2) --> 5
 * @param s The string to evaluate
 * @return The value that s is evaluated to
 */
int Calculator::algebraEvaluate(string s){

    if(isNumber(s)){
        return toNumber(s);
    }


    vector<string> expression = tokenize(s);
    //todo: error handling on invalid bounds
    /* Imports variable values */
    for(int i = 0; i < expression.size(); i++){
        if(!isOperator(expression[i]) && !isNumber(expression[i])){
            expression[i] = toString(parseOperand(expression[i]));
        }
    }

    /* Exponents */
    for(int i = 0; i < expression.size(); i++){
        if(expression[i] == "^"){
            int base = algebraEvaluate(expression[i-1]);
            int exponent = algebraEvaluate(expression[i+1]);
            expression.erase(expression.begin()+i, expression.begin()+i+2);
            expression[i-1] = toString(pow((double) base, (double) exponent));
            i -= 2;
        }
    }

    /* Multiplication and division */
    for(int i = 0; i < expression.size(); i++){
        if(expression[i] == "*"){
            int num1 = algebraEvaluate(expression[i-1]);
            int num2 = algebraEvaluate(expression[i+1]);
            expression.erase(expression.begin()+i, expression.begin()+i+2);
            expression[i-1] = toString(num1 * num2);
            i -= 2;
        }else if(expression[i] == "/"){
            int num1 = algebraEvaluate(expression[i-1]);
            int num2 = algebraEvaluate(expression[i+1]);
            expression.erase(expression.begin()+i, expression.begin()+i+2);
            if(num2 == 0) {
                throw ENUMBER;
            }else{
                expression[i-1] = toString(num1 / num2);
            }
            i -= 2;
        }
    }

    /* Addition and subtraction */
    for(int i = 0; i < expression.size(); i++){
        if(expression[i] == "+"){
            int num1 = algebraEvaluate(expression[i-1]);
            int num2 = algebraEvaluate(expression[i+1]);
            expression.erase(expression.begin()+i, expression.begin()+i+2);
            expression[i-1] = toString(num1 + num2);
            i -= 2;
        }else if(expression[i] == "-"){
            int num1 = algebraEvaluate(expression[i-1]);
            int num2 = algebraEvaluate(expression[i+1]);
            expression.erase(expression.begin()+i, expression.begin()+i+2);
            expression[i-1] = toString(num1 - num2);
            i -= 2;
        }
    }

    if(expression.size() != 1){
        throw ESYNTAX;
    }

    return toNumber(expression[0]);
}

/**
  * Converts an integer to a string
  * @param n The integer to convert
  * @return The corresponsing string
  */
string Calculator::toString(int n){
    stringstream ss;
    ss << n;
    return ss.str();
}

/**
  * Creates a variable represented by s. \n
  * s must be a one-character string for it to be used as a parameter. This
  * will be updated in future revisions.
  * Nothing happens if s is "n".
  * @param s The variable to initialize.
  * @return void
  */
void Calculator::saveParameters(string s){
    //todo: add support for a1, a_1, etc
    /* s is a parameter if:
       s != "n"
       s is not a number
       s is not an operator or bracket
       s is not the substring R( */
    // todo: optimize parameters!
    s = stripSpaces(s); // this can probably be removed to speed it up a bit

    /* Removes all delimiting characters: R(, ), +, -, *, /, ^ */
    while(s.find("R(") != string::npos){
        s.replace(s.find("R("), 2, " ");
    }

    while(s.find("(") != string::npos){
        s.replace(s.find("("), 1, " ");
    }

    while(s.find(")") != string::npos){
        s.replace(s.find(")"), 1, " ");
    }

    while(s.find("+") != string::npos){
        s.replace(s.find("+"), 1, " ");
    }

    while(s.find("-") != string::npos){
        s.replace(s.find("-"), 1, " ");
    }

    while(s.find("^") != string::npos){
        s.replace(s.find("^"), 1, " ");
    }

    while(s.find("*") != string::npos){
        s.replace(s.find("*"), 1, " ");
    }

    while(s.find("/") != string::npos){
        s.replace(s.find("/"), 1, " ");
    }

    /* Push the remaining parameters (not-n and non-spaces) into a vector */
    /* todo: This can probably be optimized by adding the parameters directly instead
     * of adding it to a vector first */
    vector<string> parameterString;
    map<string, int> parameterMap;
    int nextSpace = s.find(" ");
    string nextStr = " ";
    while(nextSpace != string::npos){
        nextStr = s.substr(0, nextSpace);
        if(nextStr != "n" && nextStr != " " && nextStr != "" && !isNumber(nextStr)){
            parameterMap[nextStr] = 1;
        }
        s.erase(0, nextSpace + 1);
        nextSpace = s.find(" ");
    }
    if(s != "" && !isNumber(s)){
        parameterMap[s] = 1;
    }

    for (map<string, int>::iterator it = parameterMap.begin();
         it != parameterMap.end(); it++){
        parameterString.push_back(it->first);
    }

    /* Stores all the parameters */
    for(int i = 0; i < parameterString.size(); i++){
        //paraNames.push_back(parameterString[i]);
        parameter.push_back(parameterString[i]);
        paraID[parameterString[i]] = parameter.size() - 1;
    }
}

/**
  * Returns a string without any whitespace
  * @param s The string to remove whitespace from
  * @return The original string, without the whitepace
  */
string Calculator::stripSpaces(string s){
    //qDebug() << "stripping: " << s << endl;
    for(int i = 0; i < s.length(); i++){
        if(s.substr(i, 1) == " "){
            s.erase(i, 1);
            i--;
        }
    }
    // cout << "stripped: " << s << endl;
    return s;
}

/**
 * @brief Calculator::createMap
 * @param values a vector containing the parameter values.
 * Creates a mapping from the ith element of paraNames to the
 * ith element of values, and stores the resulting map as paraMap.
 */
void Calculator::createMap(vector<int> values){
    if(values.size() != paraNames.size()){
        return;
    }

    paraMap.clear();
    for(int i = 0; i < paraNames.size(); i++){
        paraMap[paraNames[i]] = values[i];
    }
}

/**
 * @brief getParameterNames
 * @param s the string containing the recursion
 * @return the vector containing the parameter names
 */
vector<string> Calculator::getParameterNames(string s){
    string str = string(s);
    str = stripSpaces(str); // this can probably be removed to speed it up a bit

    /* Removes all delimiting characters: R(, ), +, -, *, /, ^ */
    while(str.find("R(") != string::npos){
        str.replace(str.find("R("), 2, " ");
    }

    while(str.find("(") != string::npos){
        str.replace(str.find("("), 1, " ");
    }

    while(str.find(")") != string::npos){
        str.replace(str.find(")"), 1, " ");
    }

    while(str.find("+") != string::npos){
        str.replace(str.find("+"), 1, " ");
    }

    while(str.find("-") != string::npos){
        str.replace(str.find("-"), 1, " ");
    }

    while(str.find("^") != string::npos){
        str.replace(str.find("^"), 1, " ");
    }

    while(str.find("*") != string::npos){
        str.replace(str.find("*"), 1, " ");
    }

    while(str.find("/") != string::npos){
        str.replace(str.find("/"), 1, " ");
    }

    vector<string> names = vector<string>();
    QStringList qsl = QString::fromStdString(str).split(" ");
    for (int i = 0; i < qsl.length(); i++){
        if(qsl[i] != "" && qsl[i] != "n" && !Calculator::isNumber(qsl[i].toStdString())){
            names.push_back(qsl[i].toStdString());
        }
    }
    paraNames = names;
    return names;
}

bool Calculator::addition_is_safe(int a, int b) {
    if ((a>=0)&&(b>=0)) {
        size_t a_bits=log(a), b_bits=log(b);
        return (a_bits<31 && b_bits<31);
    } else {
        return true;
    }
}

bool Calculator::multiplication_is_safe(long a, long b) {
    if ((a>=0)&&(b>=0)) {
        size_t a_bits=log(a), b_bits=log(b);
        return (a_bits+b_bits<=62);
    } else {
        return true;
    }
}

bool Calculator::exponentiation_is_safe(long a, long b) {
    if (a>=0) {
        size_t a_bits=log(a);
        return (a_bits*b<=62);
    } else {
        return true;
    }
}

size_t Calculator::log(long a) {
    size_t bits=0;
    while (a!=0) {
        ++bits;
        a>>=1;
    };
    return bits;
}
