#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Sequence.h"
#include "errors.h"
#include "Calculator.h"

Sequence::Sequence(string sform, Vector& paraValue, Vector& IC,
                   vector<string>& sconstraint_list, bool sAnchor, int sAnchorValue,
                   signed int sStartIndex) :
    constraint_list(sconstraint_list), c(paraValue), anchor(sAnchor), anchorValue(sAnchorValue), startIndex(sStartIndex) {
    init(sform, IC);
}

Sequence::Sequence(string sform, Vector& paraValue, Vector& IC,
                   vector<string>& sconstraint_list, bool sAnchor, int sAnchorValue) :
    constraint_list(sconstraint_list), c(paraValue), anchor(sAnchor), anchorValue(sAnchorValue), startIndex(1) {
    init(sform, IC);
}

void Sequence::init(string sform, Vector& IC) {

    Calculator::getParameterNames(sform);
    form = sform;
    R.push_back(-1);
    for (int i = 0; i < IC.size(); i++){
        R.push_back(IC[i]);
    }
    c.saveParameters(form); // initialize and "save" the parameters

    setDefault();
}

void Sequence::setDefault(void) {
    slow = true;
    slowEventually = true;
    slowProportion = 0;
    firstNotSlow = -1;
    deathTime = -1;
    die = false;
    largestGeneration = 0;
    containSubstring = false;
    containSubsequence = false;
    frequencyMatch = false;
    message = "Sequence computed successfully.";
}

/**
  Determines if the current sequence will die on the next iteration
  This appears to be useless, but it's not a priority to decide if
  I should delete this, yet.

  @return true if it dies immediately, false otherwise
  */
bool Sequence::dieImmediately(void){
    return false;
}

/**
  Computes the first n iterations of the recursion and puts them into the
  return vector.
  @param n The number of iterations to calculate
  returns false if no problems occured (no news is good news)
  */
bool Sequence::compute(const int n){
    setDefault();
    int e;
    vector<string> tokenForm = c.tokenize(form);

    /* e == ESYNTAX if there was a syntax error
       e == EINDEX if the index is out of bounds (too high or < startIndex)
       otherwise e is the resulting value */
    for (int i = R.size()-(1-startIndex); i <= n; i++){                     //cout << "n=" << i;
        try{
            e = c.evaluate(i, R, tokenForm, anchor, anchorValue, startIndex);
            R.push_back(e);
        }catch(int E){
            die = true;
            deathTime = i;
            if (E == EUINDEX) {// we need to explain what type of index problem occured
                message = QObject::tr("R(%1) tried to call R(n) for n < %2.").arg(deathTime).arg(startIndex);
            } else if (E == EOINDEX) {// we need to explain what type of index problem occured
                message = QObject::tr("R(%1) tried to call R(n) for n >= %1.").arg(deathTime);
            } else if (E == ESYNTAX){
                message = QObject::tr("This recursion has a bad syntax, making it uncomputable.").arg(deathTime);
            } else if (E == EFLOW) { // we only check overflows for now
                message = QObject::tr("Overflow Error occured when computing R(%1).").arg(deathTime);
            }
            break; // INCLUDE A MESSAGE OR SOME INDICATION
        }
    }

    return die;
}

/**
  Prints the result vector, with 10 entries in a row
  */
void Sequence::print(void){

    for (int i = 0; i < R.size(); i++){
        std::cout << R[i] << "\t";
        if (i % 10 == 0)
            std::cout << endl;
    }
    std::cout << endl;
}

//bool satisfiedConstraint(Vector para, vector<string> constraint_list){
//todo: fix this part!
bool Sequence::satisfiedConstraint(void){

    bool satisfied = true;
    //return true;  // todo: remove this line
    for (int i = 0; i < constraint_list.size(); i++){

        string constraint = constraint_list[i];
        string lhs, rhs;

        /* removes whitespace */
        while (constraint.find(" ") != string::npos){
            constraint.erase(constraint.find(" "), 1);
        }

        /* Splits the expression into 2 parts based on the equality operator
         * Then, it evaluates both parts of the expression, and checks to see
         * if the equality holds. If it does, nothing happens and satisfied
         * remains true. Otherwise, satisfied is set to false
         */
        if(constraint.find(">=") != string::npos){
            lhs = constraint.substr(0, constraint.find(">="));
            rhs = constraint.substr(constraint.find(">=") + 2, constraint.length() - constraint.find(">=") - 2);
            if(c.algebraEvaluate(lhs) < c.algebraEvaluate(rhs)){
                satisfied = false;
            }
        }else if(constraint.find("<=") != string::npos){
            lhs = constraint.substr(0, constraint.find("<="));
            rhs = constraint.substr(constraint.find("<=") + 2, constraint.length() - constraint.find(">=") - 2);
            if(c.algebraEvaluate(lhs) > c.algebraEvaluate(rhs)){
                satisfied = false;
            }
        }else if (constraint.find("!=") != string::npos) {
            lhs = constraint.substr(0, constraint.find("!="));
            rhs = constraint.substr(constraint.find("!=") + 2, constraint.length() - constraint.find("<") - 1);

            if (c.algebraEvaluate(lhs) == c.algebraEvaluate(rhs)) {
                satisfied = false;
            }
        }else if (constraint.find("=") != string::npos) {
            lhs = constraint.substr(0, constraint.find("="));
            rhs = constraint.substr(constraint.find("=") + 1, constraint.length() - constraint.find("=") - 1);

            if (c.algebraEvaluate(lhs) != c.algebraEvaluate(rhs)) {
                satisfied = false;
            }
        } else if (constraint.find(">") != string::npos) {
            lhs = constraint.substr(0, constraint.find(">"));
            rhs = constraint.substr(constraint.find(">") + 1, constraint.length() - constraint.find(">") - 1);

            if (c.algebraEvaluate(lhs) <= c.algebraEvaluate(rhs)) {
                satisfied = false;
            }
        } else if (constraint.find("<") != string::npos) {
            lhs = constraint.substr(0, constraint.find("<"));
            rhs = constraint.substr(constraint.find("<") + 1, constraint.length() - constraint.find("<") - 1);

            if (c.algebraEvaluate(lhs) >= c.algebraEvaluate(rhs)) {
                satisfied = false;
            }
        }
    }

    return satisfied;
}

void Sequence::analyse(Vector& MIC, int interval, string expression,
                       FilterOptions& fo, SummaryOptions& so){
    /*
    Vector MIC;
    MIC.push_back(-1);
    MIC.push_back(1);
    MIC.push_back(1);
    MIC.push_back(1);
    MIC.push_back(1);
    */
    cout << "generating MIC" << endl;
    cout << "MIC: ";
    for(int i = 0; i < MIC.size(); i++) {cout << MIC[i];}
    cout << endl;

    if (fo.overlapping != 2 || so.slowProportionByGeneration ||
            so.slowProportionByInterval || so.generation)
        computeGeneration(MIC);
    cout << "MIC generated" << endl;

    //checkContainSubstring(temp);
    //checkContainSubsequence(temp);

    /* so.FLAG is true if that flag is set to true */
    if (so.slow) computeSlowness(interval);
    if (so.frequency) computefrequency();
    if (so.twoRnMinusn) computetwoRnMinusn();
    if (so.RnDivn) computeRnDivn();
    if (so.additional) computeAddition(expression);
}

void Sequence::computeSlowness(int interval){
    rnMinusRn.push_back(-1);
    rnMinusRn.push_back(-1);
    int slowTerm = 0;
    /* Determines the index of the first non-slow iteration (if it exists, or
       else it stays at -1. It sets 'slow' to false as soon as one of those
       terms is encountered.
       For each slow iteration, it increments slowTerm
       */
    for (int i = 2; i < R.size(); i++){
        rnMinusRn.push_back(R[i] - R[i - 1]);
        if (R[i] - R[i - 1] != 0 && R[i] - R[i - 1] != 1){
            if (firstNotSlow == -1) firstNotSlow = i;
            slow = false;
        } else {
            slowTerm++;
        }
    }

    /* slowProportaion is the number of slow elements divided by the number
      of iterations, which is R.size()-2 */
    slowProportion = (double)slowTerm / (R.size()-2);


    /* set slowEventually to true if the 2nd half of the iterations of R(n)
       are slow.
       It checks each element and as soon as a non-slow element is encountered,
       the flag is set to false */
    for (int i = rnMinusRn.size() - 1; i >= rnMinusRn.size() / 2; i--){
        if (R[i] - R[i - 1] != 0 && R[i] - R[i - 1] != 1){
            slowEventually = false;
        }
    }
    //todo: document me
    slowPropGeneration.push_back(0);
    for (int i = 1; i < largestGeneration; i++){
        int slow = 0;
        for (int j = genStart[i]; j <= genEnd[i]; j++){
            if (rnMinusRn[j+1] == 0 || rnMinusRn[j+1] == 1) {
                slow++;
            }
        }
        slowPropGeneration.push_back((double)slow / (genEnd[i] - genStart[i] + 1));
    }

    //todo: document me
    int slow = 0;
    for (int i = 1; i < R.size(); i++){
        if (rnMinusRn[i] == 0 || rnMinusRn[i] == 1) {
            slow++;
        }

        if (i % interval == 0){
            if (i == interval)
                slowPropInterval.push_back((double)slow / (interval - 1));
            else
                slowPropInterval.push_back((double)slow / interval);
            slow = 0;
        }
    }
}

//todo: document me
// I don't know what this is supposed to do, but it doesn't do it.
void Sequence::computeGeneration(Vector& IC){
    int l = form.find("R(");
    int bracket = 1;

    for (int i = l + 2; i < form.size(); i++){
        if (form[i] == '('){
            bracket++;
        }
        if (form[i] == ')'){
            bracket--;
            if (bracket == 0){
                spot = form.substr(l + 2, i - (l + 2));
                break;
            }
        }
    }

    //int largestGeneration = 0;

    M.push_back(0);
    for (int i = 0; i < IC.size(); i++){
        M.push_back(IC[i]);
    }

    int v = 0;
    int tmp;
    for (int i = IC.size()+1; i < R.size(); i++){
        try{
            tmp = c.evaluate(i, R, c.tokenize(spot), anchor, anchorValue, startIndex);
            if(tmp < 0){
                break;
            }
        }catch(int e){
            break;
        }

        v = M[tmp] + 1;
        M.push_back(v);
        if (v > largestGeneration){
            largestGeneration = v;
        }

    }
    //Vector start(v), end(v);
    for (int i = 0; i <= largestGeneration; i++){
        genStart.push_back(2147483647);
        genEnd.push_back(0);
    }
    //cout << "largestGen" << largestGeneration << endl;
    for (int i = 1; i < M.size(); i++){
        if (i > genEnd[M[i]])   genEnd[M[i]] = i;
        if (i < genStart[M[i]]) genStart[M[i]] = i;
        }

    overlapping = false;

    for (int i = 2; i < largestGeneration; i++){
        //cout << "i = " << i << endl;
        if (genStart[i] < genEnd[i - 1])
            overlapping = true;
    }
}

/**
  Returns true iff the sequence contains a given substring
  @param substring The substring to look for
  @return true iff the substring is contained in the sequence
  */
//todo: how does this work?
bool Sequence::checkContainSubstring(Vector substring){
    Vector::iterator t = search(R.begin(), R.end(), substring.begin(), substring.end());
    //containSubstring = (t != R.end());
    return (t != R.end());
}

/**
    Check whether the frequency list matches the frequency list given by
    the seqeuence. If there are more terms generated than there are terms in the
    passed vector, then only the terms in the vector are checked. The rest of the
    terms in the sequence are ignored.
    @param fm The frequency list to compare against
    @return true iff the the frequency list matches the sequence's frequencies
    */
bool Sequence::checkFrequencyMatch(Vector fm){
    for (int i = 0; i < fm.size(); i++){
        if (fm[i] != frequency[i+1]){
            return false;
        }
    }
    return true;
}

/**
    Checks to see if a given subsequence is in the recursion sequence
    @param subsequence The subsequence to check for
    @return true iff the subsequence is contained in the sequence
    */
bool Sequence::checkContainSubsequence(Vector subsequence){
    int j = 1;
//	bool flag = false;
    /* compares element i of the sequence to element j of the subsequence
       if they don't match, j is increased by 1. */
    for (int i = 0; i < subsequence.size(); i++){
        while (R[j] != subsequence[i] && j < R.size()){
            j++;
        }
    }

    /* returns true if all of the subsequence is iterated over, which means
    that all elements are in the sequence */
    return (j != R.size());
    //cout << containSequence << endl;
}

//todo: document me
//todo: error handling
void Sequence::computeAddition(string pression){
    addition.push_back(-1);
    for (int i = startIndex, j = 1; j < R.size(); i++, j++) {
        double val;
        try {
            val = c.evaluate(i, R, c.tokenize(pression), anchor, anchorValue, startIndex);
        } catch (int E) {
            val = INT_MAX;
        }
        addition.push_back(val);
    }
}

/**
  * Stores R(n)/n in RnDivn, one for each iteration
  */
void Sequence::computeRnDivn(){
    /* used to increase the size, since i > 0 */ //--> todo: why?
    RnDivn.push_back(-1);
    /* for each element in R, store R(n)/n in RnDivn */
    for (int i = startIndex, j = 1; j < R.size(); i++, j++) {
        if (i!=0) { // we need to ensure that we're not dividing by zero
            RnDivn.push_back((double)R[j] / i);
        } else {
            RnDivn.push_back(INT_MAX);
        }
    }
}

/**
  * Stores 2*R(n)-n in twoRnMinusn, one per iteration
  */
void Sequence::computetwoRnMinusn(){
    /* used to increase the size, since i > 0 */ //--> todo: why?
    twoRnMinusn.push_back(-1);
    /* for each element in R, store 2*R(n)-n in twoRnMinusn */
    for (int i = startIndex, j = 1; j < R.size(); i++, j++) {
        twoRnMinusn.push_back(2 * R[j] - i);
    }
}

/**
  Stores the frequencies of the value in the sequence in frequency
  @example (1, 1, 2, 3, 3, 5) --> {2, 1, 2, 0, 1}
  */
void Sequence::computefrequency(){
    // we want to start after the first index because there's a -1 there
    int min = *std::min_element(R.begin()+1, R.end());
    int max = *std::max_element(R.begin()+1, R.end());
    int len = (max - min) + 1; // max-min inclusive

    for (int i = 0; i < len+1; i++) frequency.push_back(0);
    // the plus one accounts for the fact that we need an extra
    // placeholder for the zero'th element which is ignored

    frequency.at(0) = min;
    // this will be useful when showing the sequence

    /* Increases the value of frequency[x] by 1 for each
       occurence of x in R */
    /* eg: (1, 1, 2, 3, 3, 5) & {0, 0, 0, 0, 0, 0} --> {0, 2, 1, 2, 0, 1} */
    for (int i = startIndex, j = 1; j < R.size(); i++, j++) {
        int ind = (R[j] - min) + 1; // this returns the proper index for R[i]
        frequency[ind]++;
    }
}

/**
  Returns the index in the recursion to which "i" is mapped.
  @example If the first base case is R(-3), then R[1] will reference the -3'rd term.
  @example Moreover, R[5] will reference the 5th term in the sequence, that is, R(1).
  */
int Sequence::getIndexInR(int i) {
    int map = i + (1-startIndex);
    return map;
}
