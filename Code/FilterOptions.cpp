#include "FilterOptions.h"
//todo: finish documenting this
/**
  Sets the filter options, to determine which sequences will be
  displayed in the results window
  @param Pslow Indicator for which slow filter will be used.
    0 -> Slow, 1 -> Not Slow, 2 -> Either
  @param PslowEventually Indicator for eventual slowness filter.
    0 -> Slows eventually, 1 -> Does not slow eventually, 2-> Either
  @param Pdie Indicator for the sequence death filter to be used.
    0 -> Dies, 1 -> Does not die, 2 -> Either.
  @param PliveUntil ???
  @param Poverlapping ???
  @param PslowProportion ???
  @param PcontainSubstring ???
  @param PcontainSubsequence ???
  @param PfrequencyMatch ???
  @param PliveUntilValue ???
  @param PdieBefore ???
  @param PslowProportionLTValue ???
  @param PslowProportionGTValue ???
  @param PcontainSubstringValue ???
  @param PnotContainSubstringValue ???
  @param PcontainSequenceValue ???
  @param PnotContainSequenceValue ???
  @param PfrequencyMatchValue ???
  @param PfrequencyNotMatchValue ???
  */
FilterOptions::FilterOptions(int Pslow, int PslowEventually, int Pdie,
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
              string PfrequencyNotMatchValue){
    slow = Pslow;
    slowEventually = PslowEventually;
    die = Pdie;
    liveUntil = PliveUntil;
    overlapping = Poverlapping;
    slowProportion = PslowProportion;
    containSubstring = PcontainSubstring;
    containSubsequence = PcontainSubsequence;
    frequencyMatch = PfrequencyMatch;

    liveUntilValue = PliveUntilValue;
    dieBefore = PdieBefore;
    slowProportionLTValue = PslowProportionLTValue;
    slowProportionGTValue = PslowProportionGTValue;
    containSubstringValue = PcontainSubstringValue;
    notContainSubstringValue = PnotContainSubstringValue;
    containSequenceValue = PcontainSequenceValue;
    notContainSequenceValue = PnotContainSequenceValue;
    frequencyMatchValue = PfrequencyMatchValue;
    frequencyNotMatchValue = PfrequencyNotMatchValue;
}
