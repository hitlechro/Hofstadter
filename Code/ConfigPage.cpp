#include "ConfigPage.h"
#include "Sequence.h"
#include <vector>

#include <iostream> //todo: remove this

ConfigPage::ConfigPage(QWidget *parent)
    :QWizardPage(parent)
{
    /* Sets the font for this page */
    setFont(QFont("Verdana", 8));
    //setCommitPage(true);

    /* Box containing the recursion */
    QGroupBox *recursionGroupBox = new QGroupBox(tr("Recursion"));
    recursionLabel = new QLabel();
    recursionLabel->setFont(QFont("Verdana", 12,QFont::Bold));

    QHBoxLayout *recursionLayout = new QHBoxLayout;
    recursionLayout->addWidget(recursionLabel);
    recursionGroupBox->setLayout(recursionLayout);

    /******************************
    *                             *
    *          Parameters         *
    *                             *
    *******************************/

    /* Creates a 1x2 table with the headers "Parameters" and "Values" */
    paraTable = new QTableWidget(1,2);
    //QStringList paraTableHeader();
    paraTable->setHorizontalHeaderLabels(QStringList() << "Parameters" << "Values");
    /* is this needed?
    QTableWidgetItem *paraItem_0 = new QTableWidgetItem(tr(""));
    paraItem_0->setFlags(Qt::ItemIsEditable);
    paraTable->setItem(0, 0, paraItem_0); */

    /* ??? */
    paraGlobalLineEdit = new QLineEdit();

    /* Sets the column widths in the parameter table */
    paraTable->horizontalHeader()->setStretchLastSection(true);
    paraTable->resizeRowsToContents();
    //paraTable->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    /*??? */
    //QLabel *paraLabel_1 = new QLabel(tr("Extra Constraints"));
    QVBoxLayout *constraintBox = new QVBoxLayout;
    //QVBoxLayout *paraLayout_2 = new QVBoxLayout;

    /* Add & Remove buttons and text fields for parameter constraints */
    QPushButton *addConstraintButton = new QPushButton(tr("&Add"));
    QPushButton *removeConstraintButton = new QPushButton(tr("&Remove"));
    QHBoxLayout *constraintButtonBox = new QHBoxLayout;
    constraintLineEdit = new QLineEdit;
    constraintButtonBox->addWidget(constraintLineEdit);
    constraintButtonBox->addWidget(addConstraintButton);
    constraintButtonBox->addWidget(removeConstraintButton);

    /* Creates constraint list for parameter constraints */
    paraConstraintList = new QListWidget;
    paraConstraintList->setResizeMode(QListView::Adjust);
    constraintBox->addLayout(constraintButtonBox);
    constraintBox->addWidget(paraConstraintList);

    /* Adds the parameter table and constraint panel to a single panel */
    QHBoxLayout *paraLayout = new QHBoxLayout;
    paraLayout->addWidget(paraTable);
    paraLayout->addLayout(constraintBox);

    /* Adds the entire parameter & constraint panel to a single group */
    QGroupBox *paraGroupBox = new QGroupBox(tr("Parameters and Extra Constraints"));
    paraGroupBox->setLayout(paraLayout);

    /* ??? */
    paraConstraintGlobalLineEdit = new QLineEdit;
    paraNameGlobalLineEdit = new QLineEdit;

    /* Connects the buttons to listeners, and connects the parameter table to an update function */
    connect(addConstraintButton, SIGNAL(clicked()), this, SLOT(addExtraConstraint()));
    connect(removeConstraintButton, SIGNAL(clicked()), this, SLOT(removeExtraConstraint()));
    connect(paraTable, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(updateParaLineEdit())); // should this happen after it's populated?

    /* Registers the parameter data to the various fields */
    registerField(tr("paraList"), paraGlobalLineEdit);
    registerField(tr("paraNameList"), paraNameGlobalLineEdit);
    registerField(tr("paraConstraintList"), paraConstraintGlobalLineEdit);


   /*******************************
    *                             *
    *      Initial Conditions     *
    *                             *
    *******************************/

    /* ??? what are these for? */
    QLabel *ICLabel = new QLabel(tr("Define initial conditions:"));
    //QLabel *ICLabel_0 = new QLabel(tr("For Multiple Sets of Parameters:"));
    //QLabel *ICLabel_1 = new QLabel(tr("For Single Set of Parameters:"));

    /* Creates the radio buttons and makes "All ones" the default */
    QRadioButton *ICOnesButton = new QRadioButton(tr("All Ones"));
    QRadioButton *ICTwoButton= new QRadioButton(tr("All Ones followed by a Two"));
    QRadioButton *ICCustomButton = new QRadioButton(tr("No. of ICs : "));

    /* Set default radio button selected */
    ICOnesButton->setChecked(true);

    /* Creates the text field for custom IC list */
    ICStartSpinBox = new QSpinBox;
    ICFinishSpinBox = new QSpinBox;
    QHBoxLayout *ICCustomLayout = new QHBoxLayout;
    ICCustomLayout->addWidget(ICCustomButton);
    ICCustomLayout->addWidget(ICStartSpinBox);
    ICCustomLayout->addWidget(ICFinishSpinBox);

    /* Set spinbox range */
    ICStartSpinBox->setRange(-32767, 32767);
    ICFinishSpinBox->setRange(-32767, 32767);

    /* Set default spinbox selected */
    ICStartSpinBox->setValue(0);
    ICFinishSpinBox->setValue(0);

    /* Groups all radio buttons into a single group */
    QButtonGroup *ICButtonGroup = new QButtonGroup;
    ICButtonGroup->addButton(ICOnesButton);
    ICButtonGroup->addButton(ICTwoButton);
    ICButtonGroup->addButton(ICCustomButton);

    /* Creates the table for the IC, and sets the headers and dimensions */
    ICTable = new QTableWidget(0,2);
    ICTable->setHorizontalHeaderLabels(QStringList() << "ICs" << "Values");
    ICTable->horizontalHeader()->setStretchLastSection(true);
    ICTable->verticalHeader()->hide();

    /* Puts the button group into a layout */
    QVBoxLayout *ICButtonlayout = new QVBoxLayout;
    ICButtonlayout->addWidget(ICLabel);
    ICButtonlayout->addWidget(ICOnesButton);
    ICButtonlayout->addWidget(ICTwoButton);
    ICButtonlayout->addLayout(ICCustomLayout);

    /* Puts the button layout and the table into a single layout */
    QHBoxLayout *ICLayout = new QHBoxLayout;
    ICLayout->addLayout(ICButtonlayout);
    ICLayout->addStretch();
    ICLayout->addWidget(ICTable);
    //ICLayout_1->addStretch();

    /* Puts the IC layout into a group (with a caption) */
    QGroupBox *ICGroupBox = new QGroupBox(tr("Initial Conditions"));
    ICGroupBox->setLayout(ICLayout);

    /* Adds listeners to the IC spinbox and table */
    ICGlobalLineEdit = new QLineEdit();
    connect(ICStartSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateICStart(int)));
    connect(ICFinishSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateICFinish(int)));
    ICGlobalLineEdit->setText(tr(""));
    connect(ICTable, SIGNAL(cellChanged(int, int)), this, SLOT(updateICLineEdit(int, int)));

    /* Register the IC buttons */
    registerField(tr("ICList"), ICGlobalLineEdit);
    registerField(tr("ICOnesButton"), ICOnesButton);
    registerField(tr("ICTwoButton"), ICTwoButton);
    registerField(tr("ICCustomButton"), ICCustomButton);

    registerField(tr("startIndex"), ICStartSpinBox);

    /* Merges the parameters and IC into a single layout */
    QHBoxLayout *paraICLayout = new QHBoxLayout;
    paraICLayout->addWidget(paraGroupBox);
    paraICLayout->addWidget(ICGroupBox);


   /*******************************
    *                             *
    *          Filtering          *
    *                             *
    *******************************/

    QGridLayout *filterLayout = new QGridLayout;

    /******** SLOW SEQUENCE ********/
    QRadioButton *radioSlow = new QRadioButton(tr("Slow"));
    QRadioButton *radioSlowNot = new QRadioButton(tr("Not Slow"));
    QRadioButton *radioSlowBoth = new QRadioButton(tr("Both"));
    radioSlowBoth->setChecked(true);

    filterLayout->addWidget(radioSlow,0,0);
    filterLayout->addWidget(radioSlowNot,0,1);
    filterLayout->addWidget(radioSlowBoth,0,2);

    QButtonGroup *radioSlowGroup = new QButtonGroup;
    radioSlowGroup->addButton(radioSlow);
    radioSlowGroup->addButton(radioSlowNot);
    radioSlowGroup->addButton(radioSlowBoth);


    /******** SLOWS EVENTUALLY ********/
    QRadioButton *radioSlowEventual = new QRadioButton(tr("Slow Eventually"));
    QRadioButton *radioSlowEventualNot = new QRadioButton(tr("Not Slow Eventually"));
    QRadioButton *radioSlowEventualBoth = new QRadioButton(tr("Both"));
    radioSlowEventualBoth->setChecked(true);

    filterLayout->addWidget(radioSlowEventual,1,0);
    filterLayout->addWidget(radioSlowEventualNot,1,1);
    filterLayout->addWidget(radioSlowEventualBoth,1,2);

    QButtonGroup *radioSlowEventualGroup = new QButtonGroup;
    radioSlowEventualGroup->addButton(radioSlowEventual);
    radioSlowEventualGroup->addButton(radioSlowEventualNot);
    radioSlowEventualGroup->addButton(radioSlowEventualBoth);


    /******** SEQUENCE DEATH ********/
    QRadioButton *radioDie = new QRadioButton(tr("Die"));
    QRadioButton *radioDieNot = new QRadioButton(tr("Not Die"));
    QRadioButton *radioDieBoth = new QRadioButton(tr("Both"));
    radioDieBoth->setChecked(true);

    filterLayout->addWidget(radioDie,2,0);
    filterLayout->addWidget(radioDieNot,2,1);
    filterLayout->addWidget(radioDieBoth,2,2);

    QButtonGroup *radioDieGroup = new QButtonGroup;
    radioDieGroup->addButton(radioDie);
    radioDieGroup->addButton(radioDieNot);
    radioDieGroup->addButton(radioDieBoth);

    /******** SEQUENCE LIFETIME ********/
    QRadioButton *radioLiveUntil = new QRadioButton(tr("Live until"));
    QRadioButton *radioDieBefore = new QRadioButton(tr("Die before"));
    QRadioButton *radioLiveUntilBoth = new QRadioButton(tr("Both"));
    radioLiveUntilBoth->setChecked(true);
    QSpinBox *liveUntilValue = new QSpinBox;
    QSpinBox *dieBeforeValue = new QSpinBox;

    /* Sets the  values for the lifetime */
    liveUntilValue->setMinimum(0);
    liveUntilValue->setMaximum(2147483647);
    liveUntilValue->setValue(1000);

    dieBeforeValue->setMinimum(0);
    dieBeforeValue->setMaximum(2147483647);
    dieBeforeValue->setValue(1000);

    /* Adds the liveUntil fields to the row */
    QHBoxLayout *liveUntilLayout = new QHBoxLayout;
    liveUntilLayout->addWidget(radioLiveUntil);
    liveUntilLayout->addWidget(liveUntilValue);
    liveUntilLayout->addStretch();
    filterLayout->addLayout(liveUntilLayout,3,0);

    /* Adds the dieBefore fields to the row */
    QHBoxLayout *dieBeforeLayout = new QHBoxLayout;
    dieBeforeLayout->addWidget(radioDieBefore);
    dieBeforeLayout->addWidget(dieBeforeValue);
    dieBeforeLayout->addStretch();
    filterLayout->addLayout(dieBeforeLayout,3,1);

    /* Adds the Both button */
    filterLayout->addWidget(radioLiveUntilBoth,3,2);

    /* Groups all the lifetime buttons */
    QButtonGroup *radioLiveUntilGroup = new QButtonGroup;
    radioLiveUntilGroup->addButton(radioLiveUntil);
    radioLiveUntilGroup->addButton(radioDieBefore);
    radioLiveUntilGroup->addButton(radioLiveUntilBoth);

    /****** todo: overlapping? ******/
    QRadioButton *radioOverlap = new QRadioButton(tr("Overlapping"));
    QRadioButton *radioOverlapNot = new QRadioButton(tr("No Overlapping"));
    QRadioButton *radioOverlapBoth = new QRadioButton(tr("Both"));
    radioOverlapBoth->setChecked(true);
    filterLayout->addWidget(radioOverlap,4,0);
    filterLayout->addWidget(radioOverlapNot,4,1);
    filterLayout->addWidget(radioOverlapBoth,4,2);
    QButtonGroup *radioOverlapGroup = new QButtonGroup;
    radioOverlapGroup->addButton(radioOverlap);
    radioOverlapGroup->addButton(radioOverlapNot);
    radioOverlapGroup->addButton(radioOverlapBoth);

    /* Radio buttons for slow proportion */
    QRadioButton *radioSlowPropLT = new QRadioButton(tr("Slow Proportion <"));
    QRadioButton *radioSlowPropGT = new QRadioButton(tr("Slow Proportion >"));
    QRadioButton *radioSlowPropBoth = new QRadioButton(tr("Both"));
    radioSlowPropBoth->setChecked(true);
    QDoubleSpinBox *slowPropLTValue = new QDoubleSpinBox;
    QDoubleSpinBox *slowPropGTValue = new QDoubleSpinBox;

    /* Sets the values for the slow proportion spinbox*/
    slowPropLTValue->setMinimum(0);
    slowPropLTValue->setValue(0.5);
    slowPropLTValue->setSingleStep(0.1);
    slowPropLTValue->setMaximum(1);

    slowPropGTValue->setMinimum(0);
    slowPropGTValue->setValue(0.5);
    slowPropGTValue->setSingleStep(0.1);
    slowPropGTValue->setMaximum(1);

    /* Add the slow proprtion LT to the row */
    QHBoxLayout *slowPropLTLayout = new QHBoxLayout;
    slowPropLTLayout->addWidget(radioSlowPropLT);
    slowPropLTLayout->addWidget(slowPropLTValue);
    slowPropLTLayout->addStretch();
    filterLayout->addLayout(slowPropLTLayout,5,0);

    /* Add the slow proprtion GT to the row */
    QHBoxLayout *slowProprGTLayout = new QHBoxLayout;
    slowProprGTLayout->addWidget(radioSlowPropGT);
    slowProprGTLayout->addWidget(slowPropGTValue);
    slowProprGTLayout->addStretch();
    filterLayout->addLayout(slowProprGTLayout,5,1);

    /* Adds the both button */
    filterLayout->addWidget(radioSlowPropBoth,5,2);

    /* Groups the slow proportion buttons */
    QButtonGroup *radioSlowPropGroup = new QButtonGroup;
    radioSlowPropGroup->addButton(radioSlowPropLT);
    radioSlowPropGroup->addButton(radioSlowPropGT);
    radioSlowPropGroup->addButton(radioSlowPropBoth);

    /******** SUBSTRING ********/
    QRadioButton *radioHasSubstring = new QRadioButton(tr("Contain Substring :"));
    QRadioButton *radioHasSubstringNot = new QRadioButton(tr("Not Contain Substring :"));
    QRadioButton *radioHasSubstringBoth = new QRadioButton(tr("Both"));
    radioHasSubstringBoth->setChecked(true);
    QLineEdit *substringToHave = new QLineEdit;
    QLineEdit *substringToNotHave = new QLineEdit;

    /* Adds the substring to have to the row */
    QHBoxLayout *substringHaveLayout = new QHBoxLayout;
    substringHaveLayout->addWidget(radioHasSubstring);
    substringHaveLayout->addWidget(substringToHave);
    substringHaveLayout->addStretch();
    filterLayout->addLayout(substringHaveLayout,6,0);

    /* Adds the substring to not have to the row */
    QHBoxLayout *substringNotHaveLayout = new QHBoxLayout;
    substringNotHaveLayout->addWidget(radioHasSubstringNot);
    substringNotHaveLayout->addWidget(substringToNotHave);
    substringNotHaveLayout->addStretch();
    filterLayout->addLayout(substringNotHaveLayout,6,1);

    filterLayout->addWidget(radioHasSubstringBoth,6,2);
    QButtonGroup *radioSubstringGroup = new QButtonGroup;
    radioSubstringGroup->addButton(radioHasSubstring);
    radioSubstringGroup->addButton(radioHasSubstringNot);
    radioSubstringGroup->addButton(radioHasSubstringBoth);

    /******** SUBSEQUENCE ********/
    QRadioButton *radioHasSubsequence = new QRadioButton(tr("Contain Subsequence :"));
    QRadioButton *radiohasSubsequenceNot = new QRadioButton(tr("Not Contain Subsequence :"));
    QRadioButton *radioHasSubsequenceBoth = new QRadioButton(tr("Both"));
    radioHasSubsequenceBoth->setChecked(true);

    QLineEdit *subsequenceToHave = new QLineEdit;
    QLineEdit *subsequenceToNotHave = new QLineEdit;

    /* Adds the subsequence to have to the row */
    QHBoxLayout *subsequenceHaveLayout = new QHBoxLayout;
    subsequenceHaveLayout->addWidget(radioHasSubsequence);
    subsequenceHaveLayout->addWidget(subsequenceToHave);
    subsequenceHaveLayout->addStretch();
    filterLayout->addLayout(subsequenceHaveLayout,7,0);

    /* Adds the subsequence to not have to the row */
    QHBoxLayout *subsequenceNotHaveLayout = new QHBoxLayout;
    subsequenceNotHaveLayout->addWidget(radiohasSubsequenceNot);
    subsequenceNotHaveLayout->addWidget(subsequenceToNotHave);
    subsequenceNotHaveLayout->addStretch();
    filterLayout->addLayout(subsequenceNotHaveLayout,7,1);

    filterLayout->addWidget(radioHasSubsequenceBoth,7,2);

    /* Groups the subsequence buttons */
    QButtonGroup *radioSubsequenceGroup = new QButtonGroup;
    radioSubsequenceGroup->addButton(radioHasSubsequence);
    radioSubsequenceGroup->addButton(radiohasSubsequenceNot);
    radioSubsequenceGroup->addButton(radioHasSubsequenceBoth);

    //todo: finish fixing variables
    QRadioButton *radioFreqMatch = new QRadioButton(tr("Frequency Matches :"));
    QRadioButton *radioFreqMatchNot = new QRadioButton(tr("Frequency does not match :"));
    QRadioButton *radioFreqMatchBoth = new QRadioButton(tr("Both"));
    radioFreqMatchBoth->setChecked(true);
    QLineEdit *freqToMatch = new QLineEdit;
    QLineEdit *freqToNotMatch = new QLineEdit;

    QHBoxLayout *freqMatchLayout = new QHBoxLayout;
    freqMatchLayout->addWidget(radioFreqMatch);
    freqMatchLayout->addWidget(freqToMatch);
    freqMatchLayout->addStretch();
    filterLayout->addLayout(freqMatchLayout,8,0);

    QHBoxLayout *freqMatchNotLayout = new QHBoxLayout;
    freqMatchNotLayout->addWidget(radioFreqMatchNot);
    freqMatchNotLayout->addWidget(freqToNotMatch);
    freqMatchNotLayout->addStretch();
    filterLayout->addLayout(freqMatchNotLayout,8,1);

    filterLayout->addWidget(radioFreqMatchBoth,8,2);
    QButtonGroup *radioFreqGroup = new QButtonGroup;
    radioFreqGroup->addButton(radioFreqMatch);
    radioFreqGroup->addButton(radioFreqMatchNot);
    radioFreqGroup->addButton(radioFreqMatchBoth);

    //QVBoxLayout *filterLayout_main = new QVBoxLayout;
    //filterLayout_main->addLayout(filterLayout);

    QGroupBox *filterGroupBox = new QGroupBox(tr("Filtering"));
    filterGroupBox->setLayout(filterLayout);

    // [filter] Register
    //todo: name these
    registerField(tr("filterRadioButton_00"), radioSlow);
    registerField(tr("filterRadioButton_01"), radioSlowNot);
    registerField(tr("filterRadioButton_02"), radioSlowBoth);
    registerField(tr("filterRadioButton_10"), radioSlowEventual);
    registerField(tr("filterRadioButton_11"), radioSlowEventualNot);
    registerField(tr("filterRadioButton_12"), radioSlowEventualBoth);
    registerField(tr("filterRadioButton_20"), radioDie);
    registerField(tr("filterRadioButton_21"), radioDieNot);
    registerField(tr("filterRadioButton_22"), radioDieBoth);
    registerField(tr("filterRadioButton_30"), radioLiveUntil);
    registerField(tr("filterRadioButton_31"), radioDieBefore);
    registerField(tr("filterRadioButton_32"), radioLiveUntilBoth);
    registerField(tr("filterRadioButton_40"), radioOverlap);
    registerField(tr("filterRadioButton_41"), radioOverlapNot);
    registerField(tr("filterRadioButton_42"), radioOverlapBoth);
    registerField(tr("filterRadioButton_50"), radioSlowPropLT);
    registerField(tr("filterRadioButton_51"), radioSlowPropGT);
    registerField(tr("filterRadioButton_52"), radioSlowPropBoth);
    registerField(tr("filterRadioButton_60"), radioHasSubstring);
    registerField(tr("filterRadioButton_61"), radioHasSubstringNot);
    registerField(tr("filterRadioButton_62"), radioHasSubstringBoth);
    registerField(tr("filterRadioButton_70"), radioHasSubsequence);
    registerField(tr("filterRadioButton_71"), radiohasSubsequenceNot);
    registerField(tr("filterRadioButton_72"), radioHasSubsequenceBoth);
    registerField(tr("filterRadioButton_80"), radioFreqMatch);
    registerField(tr("filterRadioButton_81"), radioFreqMatchNot);
    registerField(tr("filterRadioButton_82"), radioFreqMatchBoth);

    registerField(tr("filterLiveUntil"), liveUntilValue);
    registerField(tr("filterDieBefore"), dieBeforeValue);

    registerField(tr("filterSlowProportionLT"), slowPropLTValue, "value");
    registerField(tr("filterSlowProportionGT"), slowPropGTValue, "value");

    registerField(tr("filterContainSubstring"), substringToHave);
    registerField(tr("filterNotContainSubstring"), substringToNotHave);
    registerField(tr("filterContainSubsequence"), subsequenceToHave);
    registerField(tr("filterNotContainSubsequence"), subsequenceToNotHave);
    registerField(tr("filterFrequencyMatch"), freqToMatch);
    registerField(tr("filterFrequencyNotMatch"), freqToNotMatch);

    // All Together
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(recursionGroupBox);
    layout->addLayout(paraICLayout);
    layout->addWidget(filterGroupBox);

 //   layout->addLayout(summaryGSLayout);
    //layout->addWidget(outputGroupBox);
    setLayout(layout);
    parent->resize(0,0);
    parent->updateGeometry();
//    parent->updateGeometry();



}

void ConfigPage::initializePage(){
    recursionLabel->setText(tr("R(n) = ") + field("newRecursion").toString());

    vector<int> dummy;
    vector<string> dummyString;
    Sequence S(field("newRecursion").toString().toStdString(), dummy, dummy, dummyString);

    QString paraName;   // The string with the parameter names
    /* Update the parameter table to contain the parameter names and default values (1) */
    if (S.c.parameter.size() == 0) {
        paraTable->setRowCount(0);
    }else {
        int row = 1;
        for (uint i = 0; i < S.c.parameter.size(); i++)
        {
            QString converter;
            //cout << "Param i: " << S.c.parameter[i] << endl;
            //if (S.c.parameter[i] == "^" || S.c.parameter[i] == "i") continue; //todo: ???
            paraTable->setRowCount(row);

            /* Set the size of the table (increases each iteration) */
            /* Get the parameter name from the sequence's calculator, and add it to the table */
            QTableWidgetItem *paraValue_0 = new QTableWidgetItem(tr("1"));
            QTableWidgetItem *paraItem_0 = new QTableWidgetItem(converter.fromStdString(S.c.parameter[i]));
            paraTable->setItem(row-1, 1, paraValue_0);
            paraTable->setItem(row-1, 0, paraItem_0);
            paraItem_0->setFlags(Qt::ItemIsEditable);

            /* Add the name and value (1) to paraName and paraDefault */
            paraName += converter.fromStdString(S.c.parameter[i]);
            paraDefault += "1";
            if (i != S.c.parameter.size() - 1) {
                paraName += "@@";
                paraDefault += "@@";
            }
            row++;
        }
    }
    paraGlobalLineEdit->setText(paraDefault);
    paraNameGlobalLineEdit->setText(paraName);
}

/** Adds the current constraint to the list and clear the text field.
    Sets the focus to the text field. */
void ConfigPage::addExtraConstraint()
{
    //todo: make this react to the enter key
    /* Stores the current constraint, and clears the text field */
     QString para = constraintLineEdit->text();
     constraintLineEdit->clear();
     /* Gives focus back to the text field */
     constraintLineEdit->setFocus(Qt::OtherFocusReason);
     /* If a constraint was entered, store it */
     if (para != ""){
        paraConstraintList->addItem(para);
     }
     /* Update the list with the added constraint */
     updateConstraintLineEdit();
}

/** Remove the selected constraint from the list */
void ConfigPage::removeExtraConstraint()
{
    /* Get the selected row and then remove it from the list */
    paraConstraintList->takeItem(paraConstraintList->currentIndex().row());
    updateConstraintLineEdit();
}

/** Update the number of initial conditions.
 * @param finishIndex The largest index
 * function finishes executing
 */
void ConfigPage::updateICFinish(int finishIndex)
{
    //int finishIndex = ICSpinBox->value();
    ICGlobalLineEdit->setText(tr(""));

    int currMaxInd;
    int row = ICTable->rowCount();
    if (row == 0) {
        currMaxInd = 0;
    } else {
        currMaxInd = ICTable->item(row-1,0)->text().split("(")[1].split(")")[0].toInt();
    }

    /* If the number of ICs increases... */
    if (finishIndex > currMaxInd){

        /* we need to know how many rows we're adding*/
        int rowsToAdd = finishIndex-currMaxInd;

        /* Increase the number of rows */
        for (int i = row; i < row+rowsToAdd; i++){

            ICTable->insertRow(i);
            setNewRowValues(i, (currMaxInd+1)+(i-row));

        }
    } else {
        /* we need to know how many rows we're removing*/
        int currMinInd = ICTable->item(0,0)->text().split("(")[1].split(")")[0].toInt();
        int rowsNeeded = finishIndex-currMinInd+1;
        int rowsToRemove = row - rowsNeeded;

        for (int i = 0; i < rowsToRemove; i++){
            ICTable->removeRow(rowsNeeded);
        }
        updateICLineEdit();
    }
    /* Resize the table */
    ICTable->resizeRowsToContents();
}

/** Update the number of initial conditions.
 * @param finishIndex The smallest index
 * function finishes executing
 */
void ConfigPage::updateICStart(int startIndex)
{
    //int startIndex = ICSpinBox->value();
    ICGlobalLineEdit->setText(tr(""));

    int currMinInd = ICTable->item(0,0)->text().split("(")[1].split(")")[0].toInt();

    /* If the number of ICs increases... */
    if (startIndex < currMinInd){

        /* we need to know how many rows we're adding*/
        int rowsToAdd = currMinInd-startIndex;

        /* we need to insert newRows rows to the beginning starting at currMindInd-1,
         * currMinInd-2, ..., currMinInd-newRows */
        for (int i = currMinInd; i > currMinInd-rowsToAdd; i--){

            /* Append an item to the table, make it editable */
            ICTable->insertRow(0);
            setNewRowValues(0, i-1);

        }
    } else {

        /* we need to know how many rows we're removing*/
        int rowsToRemove = startIndex-currMinInd;

        for (int i = currMinInd; i > currMinInd-rowsToRemove; i--){
            ICTable->removeRow(0);
        }
        updateICLineEdit();
    }

    /* Resize the table */
    ICTable->resizeRowsToContents();
}

void ConfigPage::setNewRowValues(int rowInd, int arg)
{
    QTableWidgetItem *ICItem = new QTableWidgetItem(tr("R(%1)").arg(arg)); // create a row with string R(i+1)
    ICItem->setFlags(Qt::ItemIsEditable);
    ICTable->setItem(rowInd, 0, ICItem);

    /* Set the value of that IC to 1 */
    QTableWidgetItem *ICValue = new QTableWidgetItem(tr("1"));
    ICTable->setItem(rowInd, 1, ICValue);
}

void ConfigPage::updateParaLineEdit()
{
    QString paraString;
    for (int i = 0; i < paraTable->rowCount(); i++){
        paraString += paraTable->item(i,1)->text();
        if (i != paraTable->rowCount()-1)
            paraString += "@@";
    }


    paraGlobalLineEdit->setText(paraString);

}


void ConfigPage::updateConstraintLineEdit()
{
    QString constraintString;
    for (int i = 0; i < paraConstraintList->count(); i++){
        constraintString += paraConstraintList->item(i)->text();
        if (i != paraConstraintList->count()-1)
            constraintString += "@@";
    }
    paraConstraintGlobalLineEdit->setText(constraintString);
}

//TODO: R is not used
void ConfigPage::updateICLineEdit(int r, int c)
{
    QString ICString;
    if (c != 0){
        for (int i = 0; i < ICTable->rowCount(); i++){
            ICString += ICTable->item(i,1)->text();

            if (i != ICTable->rowCount()-1)
                ICString += "@@";
        }
        ICGlobalLineEdit->setText(ICString);
    }
}
