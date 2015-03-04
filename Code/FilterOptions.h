#ifndef FILTEROPTIONS_H
#define FILTEROPTIONS_H

#include<string>

using namespace std;

class FilterOptions
{
public:
    /* Documented in FilterOptions.cpp */
    FilterOptions(int Pslow, int PslowEventually, int Pdie,
                  int PliveUntil, int Poverlapping,
                  int PslowProportion, int PcontainSubstring,
                  int PcontainSubsequence, int PfrequencyMatch,
                  int PliveUntilValue, int PdieBefore,
                  double PslowProportionLTValue,
                  double PslowProportionGTValue,
                  string PcontainSubstringValue,
                  string PnotContainSubstringValue,
                  string PcontainSequenceValue,
                  string PnotContainSequenceValue,
                  string PfrequencyMatchValue,
                  string PfrequencyNotMatchValue);

    /** Flag for filtering slow sequences */
    int slow;
    /** Flag for filtering sequences that are eventually slow */
    int slowEventually;
    /** Flag for filtering sequences that die */
    int die;
    /** Flag for filtering sequences that life until a set iteration */
    int liveUntil;
    /** ??? */
    int overlapping;
    /** Flag for filtering sequences that have a given proportion of slow iterations */
    int slowProportion;
    /** Flag for filtering sequences that contain a given substring (???)*/
    int containSubstring;
    /** Flag for filtering sequences that contain a given subsequence */
    int containSubsequence;
    /** Flag for filtering sequences with a given frequency */
    int frequencyMatch;

    /** The iteration that sequences must live until, used with liveUntil */
    int liveUntilValue;
    /** The iteration that sequences must die before, used with liveUntil */
    int dieBefore;
    /** Lower bound for the proporation of slow iterations, used with slowProporation */
    double slowProportionLTValue;
    /** Upper bound for the proporation of slow iterations, used with slowProporation */
    double slowProportionGTValue;
    /** Substraing contained by the sequence, used with containSubstring */
    string containSubstringValue;
    /** Substraing not contained by the sequence, used with containSubstring */
    string notContainSubstringValue;
    /** Subsequence contained by the sequence, used with containSubsequence */
    string containSequenceValue;
    /** Subsequence not contained by the sequence, used with containSubsequence */
    string notContainSequenceValue;
    /** Frequency the sequence must match, used with FrequencyMatch */
    string frequencyMatchValue;
    /** Frequency the sequence must not match, used with FrequencyMatch */
    string frequencyNotMatchValue;
};

#endif // FILTEROPTIONS_H
