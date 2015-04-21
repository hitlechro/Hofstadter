//#include <QtGui>
//#include <QVariant>
//#include <QRegExp>
#include <iostream>

#include <vector>
#include <string>
#include <sstream>
//#include <algorithm>
//#include <map>
#include <set>

//#include "calculator.h"
//#include "summaryoptions.h"
//#include "filteroptions.h"
//#include "sequence.h"
//#include "kernel.h"
using namespace std;

typedef vector<int> Vector;
typedef set<int> Set;
typedef unsigned int uint;

//todo: make a header for this


/**
 * @brief Takes a list of list of initial conditions, and generates a list of
 * all combinations of those values.
 * @param IC_values The list containing all values for each initial condition
 * (R(1), R(2), ..., R(n)).
 * @param IC_list A pointer to  the vector that will contain the list of all
 * possible parameter value combinations when this function is finished
 * executing.
 * @example para_values = {[1, 2, 3], [4, 5]} --> IC_list = {[1, 4], [1, 5],
 * [2, 4], [2, 5], [3, 4], [3, 5]}
 */
void generateICList(vector<Set>& IC_values, vector<Vector>& IC_list, Vector& IC = (* new Vector)){
    /* See generateParaList for explanation of the code */
	int layer;
    cout << "generating IC list" << endl;
    cout << "IC_values.size() = " << IC_values.size() << endl;
	layer = IC.size();
	if (IC.size() == IC_values.size()){
        IC_list.push_back(IC);
        //todo: modify the program so this works: IC_list.push_back(IC[0]);
	} else {
		for (Set::iterator i = IC_values[layer].begin(); i != IC_values[layer].end(); i++){
			IC.push_back(*i);

            generateICList(IC_values, IC_list, IC);

			IC.pop_back();
		}
	}
}

/**
 * @brief Takes a list of list of parameter values, and generates a list of
 * all combinations of parameter values.
 * @param para_values The list containing all values for each parameter (in
 * the order in which they appear in the equation).
 * @param para_list A pointer to  the vector that will contain the list of all
 * possible parameter value combinations when this function is finished
 * executing.
 * @example para_values = {[1, 2, 3], [4, 5]} --> para_list = {[1, 4], [1, 5],
 * [2, 4], [2, 5], [3, 4], [3, 5]}
 */
void generateParaList(vector<Set>& para_values, vector<Vector>& para_list, Vector& para = (* new Vector)){
    //todo: can this be redesigned and made more readable/efficient?
    /* NB: This was designed by the original developer. I don't know why
     * it was doe like this, but I don't know how easily it could be
     * redesigned.
     */
    /*
     * para is used to keep track of how many of the free variables have been set
     * eg. if we have [a, b, c], then [1, 4, _] has a "layer" of 2.
     * When layer equals 3 (in this example), then all variables are set,
     * and we can add them to para_list, and move on to the next iteration.
     */
    int layer = para.size();
	if (para.size() == para_values.size()){
		para_list.push_back(para);
	} else {
        /*
         * If we haven't set all variables, then push the next value for that
         * variable, and iterate recursively.
         * eg. if we have [a, b, c], and layer = 2, then we need to iterate
         * over the b values (and each iteration over the b values means that
         * we iterate over all c values as well.
         *
         * We remove it from para after we calculate its combinations so that in
         * the next iteration, we can replace that value with the next one.
         */
		for (Set::iterator i = para_values[layer].begin(); i != para_values[layer].end(); i++){
			para.push_back(*i);
            generateParaList(para_values, para_list, para);
			para.pop_back();
		}
	}
}

/**
  Converts a string s into a number
  @param s The string to convert
  @return The value represented by s
  */
static int toNumber(string s){
	int t;
	stringstream ss(s);
	ss >> t;
	return t;
}

/**
  Returns a Set containing the value ranges given in s\n
  @example (a, b) --> {a, b}
  @example (a-b, c) --> {a, ..., b, c}
  @param s The string containing the ranges
  @return A set<int> containing all numbers in the range indicated by s
  */
static set<int> parseRanges(string ranges){
    set<int> values;            // the set of values to return
    vector<string> tokens;      // the tokens of the comma-delimited string

    /* remove all whitespace */
    while (ranges.find(" ") != string::npos){
        ranges.erase(ranges.find(" "), 1);
    }

    /* put each substring in s into t, delimited by commas
      eg: 1, 2-3, 4-5, 6 ==> {1, 2-3, 4-5, 6} */
    while (ranges.length() != 0 && ranges.find(",") != string::npos){
        tokens.push_back(ranges.substr(0, ranges.find(",")));
        ranges.erase(0, ranges.find(",") + 1);
	}
    tokens.push_back(ranges);

    /* iterate over the set of number-strings */
    for (uint i = 0; i < tokens.size(); i++){
        if (tokens[i].find("-") == string::npos){
            /* if t[i] is a number, add it to S */
            if (tokens[i] == "") {
                // no params were given
                values.insert(values.end(), INT_MIN);
            } else {
                values.insert(values.end(), toNumber(tokens[i]));
            }
		} else {
            if (tokens[i].find("-") == 0){
                /* the hyphen was found at the beginning of the string
                 * this means the string is a negative integer */
                values.insert(values.end(), toNumber(tokens[i]));
            } else {
                /* given a string "a-b" adds all values a..b inclusive to S
                    parse is as "start-end", and add all values from start
                    to end to the set */
                // todo: simpler math?
                int start = toNumber(tokens[i].substr(0, tokens[i].find("-")));
                int end = toNumber(tokens[i].substr(tokens[i].find("-") + 1, tokens[i].size() - tokens[i].find("-") - 1));
                for (int j = start; j <= end; j++){
                    values.insert(values.end(), j);
                }
            }
        }
    }

    /*cout << "Range: " << endl;
    for (set<int>::iterator i = values.begin(); i != values.end(); i++){
        cout << *i << " ";
    }*/

    /* return the set of all numbers in the given range */
    return values;
}


/**
    Takes a string of integers and returns a vector
    that contains those numbers, delimited by commas.\n
    @example "1, 2, 3, 4, 5" --> {1, 2, 3, 4, 5}
    @param s The string of integers
    @return The vector containing those integers. */
Vector split(string s){
	Vector V;
	vector<string> t;

    /* removes all the spaces */
    while (s.find(" ") != string::npos){
        s.erase(s.find(" "), 1);
	}

    /* takes all strings ending in a comma, and puts them into t */
    while (s.length() != 0 && s.find(",") != string::npos){
		t.push_back(s.substr(0, s.find(",")));
		s.erase(0, s.find(",") + 1);
	}
    /* put the last block into t as well */
	t.push_back(s);

    /* converts t into an array of numbers, which it then returns */
    for (uint i = 0; i < t.size(); i++){
		V.push_back(toNumber(t[i]));
	}
	return V;
}


