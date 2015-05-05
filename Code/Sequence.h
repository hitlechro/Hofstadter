#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "Calculator.h"
#include "FilterOptions.h"
#include "SummaryOptions.h"

#include <QObject>

using namespace std;
typedef vector<int> Vector;

class Sequence {
    protected:
        /** ??? */
        vector<string> constraint_list;
    public:
        /** The Calculator being used to evaluate this sequence */
        Calculator c;
        /* Holds the index of the first IC */
        signed int startIndex;

        /** If anchor is true, then when the n < startIndex, R(n)=anchorValues*/
        bool anchor;
        int anchorValue;
        /* todo: document me */
        Vector R, twoRnMinusn, rnMinusRn;
                Vector M, genStart, genEnd, frequency, addition;
        /* todo: document me */
        vector<double> slowPropInterval, slowPropGeneration;
        /** Stores R(n)/n */
        vector<double> RnDivn;
        /* todo: document me */
        string form, spot;
        /** Whether the sequence is slow or not */
        bool slow;
        /** Whether the sequence is slow past a certain point */
        bool slowEventually;
        /** Whether the sequence dies */
        bool die;
        /* todo: document me */
        bool liveUntil, dieBefore, overlapping, containSubstring, containSubsequence, frequencyMatch;
        /* todo: document me */
        int firstNotSlow, deathTime;
        /* todo: document me */
        int largestGeneration;
        /** The proportion of iterations that are slow: R(n) - R(n-1) <= 1*/
        double slowProportion;
        /* We want to give a message about the result of the Sequence computation */
        QString message;

        /* Documented in Sequence.cpp */
        Sequence(string sform, Vector& paraValue, Vector& IC, vector<string>& sconstraint_list, bool sAnchor, int sAnchorValue, signed int sStartIndex);
        Sequence(string sform, Vector& paraValue, Vector& IC, vector<string>& sconstraint_list, bool sAnchor, int sAnchorValue);
        void init(string sform, Vector& IC);
        void setDefault(void); /* Can be moved to private. */
        bool compute(const int n); // generate the sequence up to n
        void print(void);
        bool satisfiedConstraint(void);
        bool dieImmediately(void);
        void analyse(Vector& MIC, int interval, string expression, FilterOptions& fo, SummaryOptions& so);
        void computeSlowness(int interval);
        void computeGeneration(Vector& IC);
        bool checkContainSubstring(Vector substring);
        bool checkContainSubsequence(Vector subsequence);
        bool checkFrequencyMatch(Vector frequencyMatch);
        void computeAddition(string pression);
        void computeRnDivn();
        void computetwoRnMinusn();
        void computefrequency();
        int getIndexInR(int i);
};

#endif // SEQUENCE_H
