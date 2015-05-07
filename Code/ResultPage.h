#ifndef RESULTPAGE_H
#define RESULTPAGE_H

#include "ClassDefs.h"
#include "SummaryOptions.h"
#include "Sequence.h"
#include <QtWidgets/QWizardPage>

#include <QtWidgets/QApplication>

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QListWidgetItem>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QProgressDialog>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QComboBox>
#include <QKeyEvent>
#include <QMimeData>
#include <QClipboard>
#include <QFileDialog>

class ResultPage : public QWizardPage
{
    Q_OBJECT

public:
    ResultPage(QWidget *parent=0);
    int boolsToNumber(bool r0, bool r1, bool r2);
    int getButtonPressed(QString s1, QString s2, QString s3);
    void cleanupPage();

    QString paraList;
    QString paraNameList;
    QStringList paraListSplit;
    QString paraConstraintList;
    QString ICList;
    QString GSList;
    int ICRadios;
    int filterRadios_0;
    int filterRadios_1;
    int filterRadios_2;
    int filterRadios_3;
    int filterRadios_4;
    int filterRadios_5;
    int filterRadios_6;
    int filterRadios_7;
    int filterRadios_8;
    int filterLiveUntil;
    int filterDieBefore;
    double filterSlowProportionLT;
    double filterSlowProportionGT;
    QString filterContainSubstring;
    QString filterNotContainSubstring;
    QString filterContainSubsequence;
    QString filterNotContainSubsequence;
    QString filterFrequencyMatch;
    QString filterFrequencyNotMatch;

    /** Holds the index of the first IC */
    signed int startIndex;

    //comments denote position in original code, in case something
    //stops working and needs to be fixed
    /** Toggle for displaying the sequence */
    bool showSequenceToggle;      // _00
    /** Toggle for displaying time of death */
    bool showDeathTimeToggle;     // _01
    /** Toggle for showing the first non-slow iteration */
    bool showFirstNotSlowToggle;  // _02
    /** Toggle for showing total proportion of slow iterations */
    bool showSlowPropToggle;      // _10
    /** Toggle for showing proportion of slow iterations by generation */
    bool showSlowPropGenToggle;   // _11
    /** Toggle for showing proportion of slow iterations by interval */
    bool showSlowPropIntToggle;   // _12
    /** Toggle for showing generational structure */
    bool showGenStructToggle;     // _20
    /** Toggle for showing whether the sequence is slow */
    bool showIsSlowToggle;        // _21
    /** Toggle for showing whether the sequence dies */
    bool showDoesDieToggle;       // _22
    /** Toggle for showing the average value, R(n)/n */
    bool showAverageToggle;       // _30
    /** Toggle for showing 2R(n)-n */
    bool show2RnToggle;           // _31
    /** Toggle for showing the difference in each iteration, R(n)-R(n-1) */
    bool showDiffToggle;          // _32
    /** Toggle for showing the frequency of each value */
    bool showFreqToggle;          // _40
    /** Toggle for showing the result of the additional expression */
    bool showAdditionalToggle;    // _41

    /** The interval size used in the summary */
    int summaryInterval;

    /** The additional expression to evaluate in the summary */
    QString summaryExpression;

    QStringList headers;
    QStringList ICParaList;

    std::vector<std::vector<int> > sequenceVector, genStartVector, genEndVector;

    std::vector<std::vector<int> > twoRnMinusnVector, rnMinusRnVector,  frequencyVector;
    std::vector<std::vector<double> > RnDivnVector, additionVector, slowPropIntervalVector, slowPropGenerationVector;
    std::vector<int> ICSizeVector;

    //std::vector<std::string > ICParaVector;

    /** The upper bound for n */
    int termination;
    /** The output method */ //todo: what does each value mean?
    int output;
    /** Used to indicate whether at least one parameter has multiple values */
    bool multiplePara;

    QLineEdit *debug;

public slots:
    void showSequence(int r, int c);


protected:
    void initializePage();
private:
    void importOptionsPage();
    void createHeaders(SummaryOptions so);
    bool violatesFilter(FilterOptions fo, Sequence S);
    void importFilterOptions();
    void configFilterOptions(QVBoxLayout *optionListLayout);
    void createRecursionBox(QGroupBox *recursionGroupBox, QString *newRecursion);
    void configOutputTable(SummaryOptions so, Sequence S, int row, int startCol,
                           QTableWidget* table);
    void configMainTableHeaders(QTableWidget* table);
    bool analyzeSequence(Sequence* S, SummaryOptions so, FilterOptions fo, vector<vector<int> > GS_list);
    void addToTable(Sequence S, vector<int> para_list, vector<int> currentIC, QTableWidget* mainTable, int row, SummaryOptions so);
};

#endif // RESULTPAGE_H
