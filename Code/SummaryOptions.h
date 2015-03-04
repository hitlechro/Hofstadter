#ifndef SUMMARYOPTIONS_H
#define SUMMARYOPTIONS_H

#include <string>

using namespace std;

/**
  Used to record the options selected by the user to configure the output.
  */
class SummaryOptions {
    public:
        /* Documented in SummaryOptions.cpp */
        SummaryOptions(bool Psequence, bool PdeathTime, bool PfirstIndex,
                bool PslowProportionGeneral, bool PslowProportionByGeneration,
                bool PslowProportionByInterval, bool Pgeneration, bool Pslow,
                bool Pdie, bool PRnDivn, bool PtwoRnMinusn, bool PrnMinusRn,
                bool Pfrequency, bool Padditional, int Pinterval, string Pexpression);

        /** Flag to display the sequence in the result window */
        bool sequence;
        /** Flag to display the index where the recursion dies (or -1 if it lives)
            in the result window */
        bool deathTime;
        /** Flag to display the first non-slow index in the result window */
        bool firstIndex;
        /** ??? */
        bool slowProportionGeneral;
        /** ??? */
        bool slowProportionByGeneration;
        /** ??? */
        bool slowProportionByInterval;
        /** ??? */
        bool generation;
        /** Flag to indicate whether the sequence is slow in the result window */
        bool slow;
        /** Flag to indicate whether the sequence dies in the result window */
        bool die;
        /** Flag to display R(n)/n in the result window */
        bool RnDivn;
        /** Flag to display 2*R(n)-n in the result window */
        bool twoRnMinusn;
        /** Flag to display R(n)-R(n-1) in the result window */
        bool rnMinusRn;
        /** Flag to display the frequency in the result window */
        bool frequency;
        /** Flag to display a user-entered expression in the result window */
        bool additional;
        /** The number of intervals to iterate over */
        int interval;
        /** The expression that will be evaluated */
        string expression;
};


#endif // SUMMARYOPTIONS_H
