#ifndef CALCULATOR_H
#define CALCULATOR_H

/*#include <QtGui>
#include <QVariant>
#include <QRegExp>*/

#include <map>
#include <string>
#include <vector>

using namespace std;

/**
  * Used to parse and evaluate each R expression.
  */
class Calculator {

    protected:
        /** The string representing the current expression */
        string form;
        /** Stores the value of each parameter. The index of a given parameter
          is found in paraID. */
        vector<int> paraValue;
    public:
        /** Stores the parameters */
        vector<string> parameter;
        /** A parameter -> index map, for the variable's index in paraValue */
        map<string, int> paraID;
        /** A parameter -> value map */
        static vector<string> paraNames;    /* todo: paramap */
        static map<string, int> paraMap;    /* todo: paramap */

        /* Functions, defined in .cpp file */
        Calculator(vector<int> paraValue) : paraValue(paraValue) { }
        static bool isOperator(string s);
        static vector<string> tokenize(string s);
        static bool isNumber(string s);
        int parseOperand(string s);
        static int _parseOperand(string s); /* todo: paramap*/
        static int toNumber(string s);
        int evaluate(int n, vector<int>& R, vector<string> s, signed int n_0);
        int evaluate(int n, vector<int>& R, vector<string> s);
        int stringEvaluate(int n, vector<int>& R, string expression, signed int n_0);
        int algebraEvaluate(string expression);
        static string toString(int n);
        /*static*/ void saveParameters(string s);
        static string stripSpaces(string s);
        static void createMap(vector<int> v);
        static void init();
        static vector<string> getParameterNames(string s);

};

#endif // CALCULATOR_H
