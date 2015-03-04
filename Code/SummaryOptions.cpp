#include "SummaryOptions.h"

/**
 Sets the options the user selected
 @param Psequence Displays the sequence if true
 @param PdeathTime Indicates when the recursion dies if true (-1 if it does not die)
 @param PfirstIndex Indicates the first index where it is not slow
 @param PslowProportionGeneral ???
 @param PslowProportionByGeneration ???
 @param PslowProportionByInterval ???
 @param Pgeneration ???
 @param Pslow Indicates whether the recursion is slow if true
 @param Pdie Indicates whether the recursion dies if true
 @param PRnDivn Displays R(n)/n if true
 @param PtwoRnMinusn Displays 2*R(n)-n if true
 @param PrnMinusRn Displays R(n)-R(n-1) if true
 @param Padditional Displays a user entered expression if true
 @param Pfrequency Displays the frequency of each value if true
 @param Pinterval ???
 @param Pexpression ???
*/
SummaryOptions::SummaryOptions(bool Psequence, bool PdeathTime, bool PfirstIndex,
        bool PslowProportionGeneral, bool PslowProportionByGeneration,
        bool PslowProportionByInterval, bool Pgeneration, bool Pslow,
        bool Pdie, bool PRnDivn, bool PtwoRnMinusn, bool PrnMinusRn,
        bool Pfrequency, bool Padditional, int Pinterval, string Pexpression){
    sequence = Psequence;
    deathTime = PdeathTime;
    firstIndex = PfirstIndex;
    slowProportionGeneral = PslowProportionGeneral;
    slowProportionByGeneration = PslowProportionByGeneration;
    slowProportionByInterval = PslowProportionByInterval;
    generation = Pgeneration;
    slow = Pslow;
    die = Pdie;
    RnDivn = PRnDivn;
    twoRnMinusn = PtwoRnMinusn;
    rnMinusRn = PrnMinusRn;
    additional = Padditional;
    frequency = Pfrequency;
    interval = Pinterval;
    expression = Pexpression;
}

