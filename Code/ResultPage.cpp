#include "Kernel.cpp"
#include "filteroptions.h"
#include "summaryoptions.h"
#include "ResultPage.h"
#include <set>
#include <vector>
#include <iostream>
#include <limits>
#include "Sequence.h"

#include <QDebug>

typedef set<int> Set;

using namespace std;

class CopyTableWidget : public QTableWidget {

    public:
        //CopyTableWidget(QWidget *parent = 0);
        CopyTableWidget(int rows, int cols, QWidget* parent = 0);
        //~CopyTableWidget();
    protected:
        virtual void keyPressEvent(QKeyEvent * event);

};

CopyTableWidget::CopyTableWidget(int rows, int cols, QWidget* parent) :
    QTableWidget(rows, cols, parent){
        //this->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
}

//CopyTableWidget::~CopyTableWidget(){}

void CopyTableWidget::keyPressEvent(QKeyEvent * event){
    if(event->key() == Qt::Key_C && event->modifiers() & Qt::ControlModifier)
    {
        //popDebug("yo");
        QByteArray mByteArray;
        QList<QTableWidgetSelectionRange> selection = selectedRanges();
        for (int k = 0; k < selection.size(); k++){
            for (int i = selection[k].topRow(); i <= selection[k].bottomRow(); i++){
                for (int j = selection[k].leftColumn(); j <= selection[k].rightColumn(); j++){
                    mByteArray.append(item(i, j)->text() + tr("\t"));
                }
                mByteArray.append(tr("\r\n"));
            }
        }
        //popDebug(tr("%1 %2").arg(i).arg(j));
        QMimeData * mimeData = new QMimeData();
        mimeData->setData("text/plain",mByteArray);
        QApplication::clipboard()->setMimeData(mimeData);
    }

}

/** Given 3 booleans, it indicates which one is true.\n
  This is used with radio buttons, to determine which option to use.
  @param r0 The first boolean
  @param r1 The second boolean
  @param r2 The third boolean
  @return The number of the first true argument
  @example boolsToNumber(1,0,0) returns 0
  @example boolsToNumber(0,0,1) returns 2 */
int ResultPage::boolsToNumber(bool r0, bool r1, bool r2){
    if (r2) return 2;
    if (r1) return 1;
    if (r0) return 0;

    exit(0);
}

/**
 * Given the name of 3 field names, it indicates which one corresponsds to a
 * checked radio button.
 * @param s1 The first field name
 * @param s2 The second field name
 * @param s3 The third field name
 * @return 0 if s1's button is checked,  1 if s2's button is checked,
 * 2 if s3's button is checked. Returns -1 if none are checked, but this
 * should never happen.
 *
 **/
int ResultPage::getButtonPressed(QString s1, QString s2, QString s3){
    if(field(s1).toBool()){
        return 0;
    }else if(field(s2).toBool()){
        return 1;
    }else if(field(s3).toBool()){
        return 2;
    }else{
        return -1;
    }
}


/** Create a popup with a message
  @param s The message to display */
void popDebug(QString s){
    QMessageBox x;
    x.setText(s);
    x.exec();
}

//todo: comment me
/** Generate a cell in the summary table for a given sequence
  @param r The row in the table
  @param c The column in the table */
void ResultPage::showSequence(int r, int c){

    /* If that column is one of the "simple" summary options */
    if (headers[c] == "Sequence" || headers[c] == "2R(n)-n"
            || headers[c] == "R(n)-R(n-1)" || headers[c] == "Frequency"
            || headers[c] == summaryExpression){

        /* V is the vector that the output will be stored in. The vectors that
        contain the data are created when the page is initialized */
        vector<vector<int> > V;

        /* If the header is sequence, set V to the result vector
          If the heder is 2R(n)-n, set V to that vector
          etc */
        /* if <headerName> = <name>, V = <relevant vector> */
        if (headers[c] == "Sequence"){
            V = sequenceVector;
        } else if (headers[c] == "2R(n)-n"){
            V = twoRnMinusnVector;
        } else if (headers[c] == "R(n)-R(n-1)"){
            V = rnMinusRnVector;
        } else if (headers[c] == "Frequency"){
            V = frequencyVector;
        } else if (headers[c] == summaryExpression){
            V = additionVector;
        }

        QDialog *sequenceDialog = new QDialog(this);
        //todo: fix header
        QLabel *title = new QLabel(headers[c] + tr((multiplePara)?" - Parameters : ":" - IC : ")+ICParaList[r]);
        title->setFont(QFont("Verdana", 10, QFont::Bold));

        QListWidget *rangeList = new QListWidget;
        for (int i = 0; i < (int)(V[r].size() / 10000); i++){
            new QListWidgetItem(tr("%1 - %2").arg(i * 10000 + 1).arg((i+1) * 10000), rangeList);
        }

        //rangeList->setSectionResizeMode(QListView::Adjust);
        CopyTableWidget *SequenceTable = new CopyTableWidget(ceil((double)(V[r].size()-1) / 10), 10);
        SequenceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        QStringList verticalHeader;

        for (int i = 1; i < (int)V[r].size(); i++){
            QTableWidgetItem *sequenceValue = new QTableWidgetItem(tr("%1").arg(V[r][i]));
            SequenceTable->setItem((i-1) / 10, (i-1) % 10, sequenceValue);
            verticalHeader << tr("%1 + n").arg((i-1)*10);
        }
        SequenceTable->setVerticalHeaderLabels(verticalHeader);
        SequenceTable->resizeColumnsToContents();
        SequenceTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        QSizePolicy sizeP;
        SequenceTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        //rangeList->setMaximumWidth(100);


        QVBoxLayout *dialogLayout = new QVBoxLayout;
        //dialogLayout->addWidget(rangeList);
        dialogLayout->addWidget(title);
        dialogLayout->addWidget(SequenceTable);
        sequenceDialog->setLayout(dialogLayout);
        sequenceDialog->resize(400, 400);

        sequenceDialog->show();


    } else if (headers[c] == "Slow % I"){
        QDialog *generationDialog = new QDialog(this);
        QLabel *title = new QLabel(tr("Slow Proportion by Interval - ") + tr((multiplePara)?"Parameters:":"IC:")+ICParaList[r]);
        title->setFont(QFont("Verdana", 10, QFont::Bold));

        QVBoxLayout *dialogLayout = new QVBoxLayout;

        if (slowPropIntervalVector[r].size() < 2){
            QLabel *errorLabel = new QLabel(
                        tr("ERROR: The Slow Propotion cannot be calculated for ")
                        + tr((multiplePara)?"parameters:":"IC:")
                        + ICParaList[r] + tr("."));
            dialogLayout->addWidget(errorLabel);
        } else {

            //rangeList->setSectionResizeMode(QListView::Adjust);
            CopyTableWidget *SlowTable = new CopyTableWidget(slowPropIntervalVector[r].size() - 2, 3);
            QStringList verticalHeader;

            for (int i = 0; i < (int)slowPropIntervalVector[r].size(); i++){
                QTableWidgetItem *StartValue = new QTableWidgetItem(tr("%1").arg(i * summaryInterval + 1));

                if (i == 0) StartValue->setText(tr("%1").arg(2));

                QTableWidgetItem *EndValue = new QTableWidgetItem(tr("%1").arg((i + 1) * summaryInterval));
                QTableWidgetItem *slowPropIntervalValue = new QTableWidgetItem(tr("%1").arg(slowPropIntervalVector[r][i]));
                SlowTable->setItem((i), 0, StartValue);
                SlowTable->setItem((i), 1, EndValue);
                SlowTable->setItem((i), 2, slowPropIntervalValue);
                verticalHeader << tr("%1").arg(i);
            }
            SlowTable->setVerticalHeaderLabels(verticalHeader);
            SlowTable->resizeColumnsToContents();
            SlowTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            QSizePolicy sizeP;
            SlowTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            dialogLayout->addWidget(title);
            dialogLayout->addWidget(SlowTable);
        }

        generationDialog->setLayout(dialogLayout);
        generationDialog->resize(400, 400);

        generationDialog->show();
    } else if (headers[c] == "Generation" || headers[c] == "Slow % G"){
        QDialog *generationDialog = new QDialog(this);
        QLabel *title = new QLabel(
                    tr("Generational Structure - ")
                    + tr((multiplePara)?"Parameters:":"IC:")
                    + ICParaList[r]);

        title->setFont(QFont("Verdana", 10, QFont::Bold));

        QVBoxLayout *dialogLayout = new QVBoxLayout;

        if (genEndVector[r].size() < 2){
            QLabel *errorLabel = new QLabel(
                        tr("ERROR: The Generational Structure cannot be calculated for ")
                        + tr((multiplePara)?"parameters:":"IC:")
                        + ICParaList[r]+tr("."));

            dialogLayout->addWidget(errorLabel);
        } else {

            //rangeList->setSectionResizeMode(QListView::Adjust);
            CopyTableWidget *GenerationTable = new CopyTableWidget(genEndVector[r].size() - 2, 3);
            QStringList verticalHeader;

            for (int i = 1; i < (int)genEndVector[r].size() - 1; i++){
                QTableWidgetItem *genStartValue = new QTableWidgetItem(tr("%1").arg(genStartVector[r][i]));
                QTableWidgetItem *genEndValue = new QTableWidgetItem(tr("%1").arg(genEndVector[r][i]));
                QTableWidgetItem *slowPropGenerationValue = new QTableWidgetItem(tr("%1").arg(slowPropGenerationVector[r][i]));
                GenerationTable->setItem((i-1), 0, genStartValue);
                GenerationTable->setItem((i-1), 1, genEndValue);
                GenerationTable->setItem((i-1), 2, slowPropGenerationValue);
                verticalHeader << tr("%1").arg(i);
            }

            GenerationTable->setVerticalHeaderLabels(verticalHeader);
            GenerationTable->resizeColumnsToContents();
            GenerationTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            QSizePolicy sizeP;
            GenerationTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            GenerationTable->setHorizontalHeaderLabels(QStringList() << "Start" << "End" << "Slow Proportion");


            dialogLayout->addWidget(title);
            dialogLayout->addWidget(GenerationTable);
        }

        generationDialog->setLayout(dialogLayout);
        generationDialog->resize(400, 400);

        generationDialog->show();
    } else if (headers[c] == "R(n)/n"){
        vector<vector<double> > V;

        V = RnDivnVector;

        QDialog *sequenceDialog = new QDialog(this);
        QLabel *title = new QLabel(headers[c] + tr((multiplePara)?" - Parameters : ":" - IC : ")+ICParaList[r]);
        title->setFont(QFont("Verdana", 10, QFont::Bold));

        QListWidget *rangeList = new QListWidget;
        for (int i = 0; i < (int)(V[r].size() / 10000); i++){
            new QListWidgetItem(tr("%1 - %2").arg(i * 10000 + 1).arg((i+1) * 10000), rangeList);
        }

        //rangeList->setSectionResizeMode(QListView::Adjust);
        CopyTableWidget *SequenceTable = new CopyTableWidget(ceil((double)(V[r].size()-1) / 10), 10);
        QStringList verticalHeader;

        for (int i = 1; i < (int)V[r].size(); i++){
            QTableWidgetItem *sequenceValue = new QTableWidgetItem(tr("%1").arg(V[r][i]));
            SequenceTable->setItem((i-1) / 10, (i-1) % 10, sequenceValue);
            verticalHeader << tr("%1 + n").arg((i-1)*10);
        }
        SequenceTable->setVerticalHeaderLabels(verticalHeader);
        SequenceTable->resizeColumnsToContents();
        SequenceTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        QSizePolicy sizeP;
        SequenceTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        //rangeList->setMaximumWidth(100);


        QVBoxLayout *dialogLayout = new QVBoxLayout;
        //dialogLayout->addWidget(rangeList);
        dialogLayout->addWidget(title);
        dialogLayout->addWidget(SequenceTable);
        sequenceDialog->setLayout(dialogLayout);
        sequenceDialog->resize(600, 400);

        sequenceDialog->show();
    }
}

void ResultPage::initializePage(){
    qDebug() << "Result Page Initialization";

    /* Clears all data from the last time this page was used */
    //todo: move to cleanup method??
    sequenceVector.clear();
    ICParaList.clear();
    genEndVector.clear();
    genStartVector.clear();
    rnMinusRnVector.clear();
    slowPropGenerationVector.clear();
    slowPropIntervalVector.clear();
    twoRnMinusnVector.clear();
    additionVector.clear();
    ICSizeVector.clear();
    frequencyVector.clear();
    headers.clear();

    /* Imports the summary options from that page */
    importOptionsPage();

    qDebug() << " Terminate at:"  << termination;

    /*******************************
     *       Recursion Title       *
     *******************************/

    QGroupBox *recursionGroupBox = new QGroupBox(tr("Recursion"));
    QString newRecursion;

    createRecursionBox(recursionGroupBox, &newRecursion);

    /*******************************
     *            Options          *
     *******************************/

    QVBoxLayout *optionListLayout = new QVBoxLayout;

    /******************************
     *           paraList         *
     ******************************/

    paraList = field(tr("paraList")).toString();
    paraNameList = field(tr("paraNameList")).toString();
    paraConstraintList = field(tr("paraConstraintList")).toString();

    QStringList paraListSplit = paraList.split("@@");
    QStringList paraNameListSplit = paraNameList.split("@@");

    QLabel *paraLabel = new QLabel(tr("Parameters:"));
    paraLabel->setFont(QFont("Verdana", 10, QFont::Bold));
    QStringList paraConstraintListSplit = paraConstraintList.split("@@");

    CopyTableWidget *paraTable = new CopyTableWidget(paraListSplit.size(),2);
    paraTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //paraTable->setHorizontalHeaderLabels(QStringList() << "Parameters" << "Values");

    for (int i = 0; i < paraListSplit.size(); i++){
        QTableWidgetItem *paraItem = new QTableWidgetItem(paraNameListSplit[i]);
        paraItem->setFlags(Qt::ItemIsEditable);
        paraTable->setItem(i, 0, paraItem);
        QTableWidgetItem *paraValue = new QTableWidgetItem(paraListSplit[i]);
        paraTable->setItem(i, 1, paraValue);
    }
    paraTable->horizontalHeader()->setStretchLastSection(true);
    paraTable->resizeRowsToContents();
    paraTable->resizeColumnsToContents();
    paraTable->verticalHeader()->hide();
    paraTable->horizontalHeader()->hide();
    paraTable->setMaximumWidth(100);

    optionListLayout->addWidget(paraLabel);
    optionListLayout->addWidget(paraTable);

    QLabel *paraConstraintLabel = new QLabel(tr("Constraints:"));
    qDebug() << paraConstraintListSplit.size();


    if (paraConstraintListSplit[0] != "") {
        optionListLayout->addWidget(paraConstraintLabel);
        paraConstraintLabel->setFont(QFont("Verdana", 10, QFont::Bold));
        for (int i = 0; i < paraConstraintListSplit.size(); i++){
            optionListLayout->addWidget(new QLabel(paraConstraintListSplit[i]));
        }
    }



    /******************************
     *              IC            *
     ******************************/

    ICList = field(tr("ICList")).toString();
    ICRadios = getButtonPressed("ICOnesButton", "ICTwoButton", "ICCustomButton");
            //boolsToNumber(field("ICOnesButton").toBool(), field("ICTwoButton").toBool(), field("ICCustomButton").toBool());

    /* Gets the index of the first IC  */
    startIndex = field("startIndex").toInt();

    /* Gets the index of the first IC  */
    bool anchor = field(tr("ICAnchorButton")).toBool();
    int anchorValue = field(tr("anchorValue")).toInt();

    QLabel *ICLabel = new QLabel(tr("ICs:"));
    ICLabel->setFont(QFont("Verdana", 10, QFont::Bold));
    optionListLayout->addWidget(ICLabel);

    if (ICRadios == 0){
        QLabel *ICLabel_0 = new QLabel(tr("All Ones"));
        optionListLayout->addWidget(ICLabel_0);
    } else if (ICRadios == 1){
        QLabel *ICLabel_1 = new QLabel(tr("All Ones followed by a Two"));
        optionListLayout->addWidget(ICLabel_1);
    } else {
        QStringList ICListSplit = ICList.split("@@");

        CopyTableWidget *ICTable = new CopyTableWidget(ICListSplit.size(),2);
        ICTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        for (int i = 0; i < ICListSplit.size(); i++){
            QTableWidgetItem *ICItem = new QTableWidgetItem(tr("R(%1)").arg(i+startIndex));
            ICItem->setFlags(Qt::ItemIsEditable);
            ICTable->setItem(i, 0, ICItem);

            QTableWidgetItem *ICValue = new QTableWidgetItem(ICListSplit[i]);
            ICTable->setItem(i, 1, ICValue);
        }

        ICTable->horizontalHeader()->setStretchLastSection(true);
        ICTable->verticalHeader()->hide();
        ICTable->resizeRowsToContents();
        ICTable->resizeColumnsToContents();
        ICTable->horizontalHeader()->hide();
        ICTable->setMaximumWidth(100);
        optionListLayout->addWidget(ICTable);
    }

    /******************************
     *            GS-IC           *
     ******************************/

    GSList = field(tr("GSList")).toString();

    QLabel *GSLabel = new QLabel(tr("Generational Structure:"));
    GSLabel->setWordWrap(true);
    GSLabel->setFont(QFont("Verdana", 10, QFont::Bold));
    optionListLayout->addWidget(GSLabel);

    QStringList GSListSplit = GSList.split("@@");

    CopyTableWidget *GSTable = new CopyTableWidget(GSListSplit.size(),2);

    for (int i = 0; i < GSListSplit.size(); i++){
        QTableWidgetItem *GSItem = new QTableWidgetItem(tr("M(%1)").arg(i+1));
        GSItem->setFlags(Qt::ItemIsEditable);
        GSTable->setItem(i, 0, GSItem);

        QTableWidgetItem *GSValue = new QTableWidgetItem(GSListSplit[i]);
        GSTable->setItem(i, 1, GSValue);
    }

    GSTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    GSTable->horizontalHeader()->setStretchLastSection(true);
    GSTable->verticalHeader()->hide();
    GSTable->resizeRowsToContents();
    GSTable->resizeColumnsToContents();
    GSTable->horizontalHeader()->hide();
    GSTable->setMaximumWidth(100);
    optionListLayout->addWidget(GSTable);

    /******************************
     *          Filtering         *
     ******************************/

    QLabel *filterLabel = new QLabel(tr("Filtering:"));
    filterLabel->setFont(QFont("Verdana", 10, QFont::Bold));
    optionListLayout->addWidget(filterLabel);

    importFilterOptions();
    configFilterOptions(optionListLayout);



    /*******************************
     *                             *
     *       MAIN MAIN PROGRAM     *
     *                             *
     *******************************/

    string Parameters = paraList.toStdString();

        QString converter;
        qDebug() << "try " << converter.fromStdString(Parameters);

    string InitialConditions = ICList.toStdString();
    string GSInitialConditions = GSList.toStdString();
    //string Constraint = "a+d = b+c";
    string Constraint = paraConstraintList.toStdString();

    FilterOptions fo(filterRadios_0, filterRadios_1, filterRadios_2,
            filterRadios_3, filterRadios_4, filterRadios_5,
            filterRadios_6, filterRadios_7, filterRadios_8, filterLiveUntil,
            filterDieBefore, filterSlowProportionLT, filterSlowProportionGT,
            filterContainSubstring.toStdString(), filterNotContainSubstring.toStdString(),
            filterContainSubsequence.toStdString(), filterNotContainSubsequence.toStdString(),
            filterFrequencyMatch.toStdString(), filterFrequencyNotMatch.toStdString());

    SummaryOptions so(showSequenceToggle, showDeathTimeToggle, showFirstNotSlowToggle,
            showSlowPropToggle, showSlowPropGenToggle, showSlowPropIntToggle,
            showGenStructToggle, showIsSlowToggle, showDoesDieToggle,
            showAverageToggle, show2RnToggle, showDiffToggle,showFreqToggle,
            showAdditionalToggle, termination, summaryExpression.toStdString());

    //todo: make sure using the field instead of "updatedRecursion"
    //doesn't break anything.
    string recursion = field("newRecursion").toString().toStdString();//newRecursion.toStdString();
    int IC_option = ICRadios;

    //Vector temp;
    vector<Vector> IC_list, para_list, GS_list;
    multiplePara = false;
    //bool multipleIC = false;


    /************************
     *      parameters      *
     ************************/

    vector<Set> paraValues; /* The set  of values for each parameter */
    /* Parameters is the list of parameter names */
    while (Parameters.find(" ") != string::npos){
        Parameters.erase(Parameters.find(" "), 1);
    }

    /* Takes the parameter string (range_1@@range_2@@etc) and split it into a vector,
     * delimited by the @@
     * eg: "1-4,6@@7-9@@3" --> {1-4,6;7-9;3}
     */
    while (Parameters.length() != 0 && Parameters.find("@@") != string::npos){
        paraValues.push_back( parseRanges( Parameters.substr(0, Parameters.find("@@")) ) );
        Parameters.erase(0, Parameters.find("@@") + 2);
    }
    paraValues.push_back(parseRanges(Parameters));

    /* If any of the parameters have more than 1 value, then
     * set multiplePara to true */
    for (int i = 0; i < (int)paraValues.size(); i++){
        if (paraValues[i].size() > 1){
            multiplePara = true;
            break;
        }
    }

    /* Takes the parameter values, and 2 empty arrays
     * Puts all possible parameter combinations into para_list */
    generateParaList(paraValues, para_list);


    /************************
     *  Constraint on para  *
     ************************/

    vector<string> constraintList;
    while (Constraint.find(" ") != string::npos)
        Constraint.erase(Constraint.find(" "), 1);

    while (Constraint.length() != 0 && Constraint.find("@@") != string::npos){
        constraintList.push_back( Constraint.substr(0, Constraint.find("@@")) );
        Constraint.erase(0, Constraint.find("@@") + 2);
    }
    if (Constraint.length() != 0) constraintList.push_back( Constraint );

    /*for (int i = 0; i < constraintList.size(); i++){
        cout << constraintList[i] << endl;
    }*/

    /************************
     *  InitialConditions   *
     ************************/

    vector<Set> IC_Vs;

//    for (int i = 0; i != ICListSplit.size(); i++) {
//        set<int> IC = parseRanges(ICListSplit.at(i));
//        IC_Vs.push_back(IC);
//    }
    while (InitialConditions.find(" ") != string::npos){
        InitialConditions.erase(InitialConditions.find(" "), 1);
    }

    while (InitialConditions.length() != 0 && InitialConditions.find("@@") != string::npos){
        IC_Vs.push_back( parseRanges( InitialConditions.substr(0, InitialConditions.find("@@")) ) );
        InitialConditions.erase(0, InitialConditions.find("@@") + 2);
    }

    if (InitialConditions.length() != 0){
        IC_Vs.push_back( parseRanges( InitialConditions ) );
    }

    generateICList(IC_Vs, IC_list);

    /************************
     * GS InitialConditions *
     ************************/

    vector<Set> GS_Vs;
    cout << "GSINIT: " << GSInitialConditions << endl;
    while (GSInitialConditions.find(" ") != string::npos)
        GSInitialConditions.erase(GSInitialConditions.find(" "), 1);

    while (GSInitialConditions.length() != 0 && GSInitialConditions.find("@@") != string::npos){
        GS_Vs.push_back( parseRanges( GSInitialConditions.substr(0, GSInitialConditions.find("@@")) ) );
        GSInitialConditions.erase(0, GSInitialConditions.find("@@") + 2);
    }
    if (GSInitialConditions.length() != 0) GS_Vs.push_back( parseRanges( GSInitialConditions ) );

    generateICList(GS_Vs, GS_list);

    /* Adds the table headers */
    createHeaders(so);

    CopyTableWidget *mainTable = new CopyTableWidget(0,headers.size());
    mainTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //mainTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    //mainTable->setHorizontalHeaderLabels(headers);
    //mainTable->horizontalHeader()->setStretchLastSection(true);

    int numEvals = 1;
    if (multiplePara) { numEvals *= para_list.size();}
    if (IC_option != 0 && IC_option != 1) { numEvals *= IC_list.size(); }

    QProgressDialog progress(tr("Enumerating expressions"), "Cancel", 0, 1, this);
    progress.setWindowModality(Qt::WindowModal);

    QLabel *progressLabel = new QLabel(tr("Generating approximately %1 sequences up to N = %2").arg(numEvals).arg(termination));
    progress.setLabel(progressLabel);
    progress.setRange(0, numEvals);


    int row = 0;
    // new code starts
    for (uint i = 0; i < para_list.size(); i++){
        bool usingCustomIC = false; //is true if the IC should be updated on each iteration (multiple IC configurations)
        if (progress.wasCanceled()){
            break;
        }

        vector<int> currentIC;
        bool undefined = false;

        if(IC_option == 0 || IC_option == 1){
            progress.setValue(i);
            currentIC.push_back(IC_option + 1); // if all 1s, push a 1, if 1..2, push a 2
            Sequence testSequence = Sequence(recursion, para_list[i], currentIC, constraintList, anchor, anchorValue);
            unsigned int firstIndexAfterIC = 2;
            while(testSequence.compute(firstIndexAfterIC)){
                // changes the last 2 to a 1 if IC_opt == 1
                if (IC_option == 1) {
                    currentIC[currentIC.size()-1] = 1; // does nothing if IC_options = 0
                } currentIC.push_back(IC_option + 1);
                testSequence.R.push_back(IC_option + 1);
                /* If too many terms are invalid, just say that
                    the sequence is invalid */
                //todo: this could be smarter: user defined, based on rec, etc.
                if (currentIC.size() > 100) {
                    undefined = true;
                    break;
                }

                firstIndexAfterIC += 1;
            }
        } else {
            //todo: find a way to use all ICs
            /* IC was set to custom ICs, so just use that list */
            usingCustomIC = true;
        }

        if (undefined){
            continue;
        }

        if(!usingCustomIC){
            progress.setValue(i);
            Sequence S = Sequence(recursion, para_list[i], currentIC, constraintList, anchor, anchorValue);
            if(analyzeSequence(&S, so, fo, GS_list)){
                addToTable(S, para_list[i], currentIC, mainTable, row, so);
                row++;
            }
        }else{
            for(uint j = 0; j < IC_list.size(); j++){
                progress.setValue(IC_list.size()*i + j);
                Sequence S = Sequence(recursion, para_list[i], IC_list.at(j), constraintList, anchor, anchorValue, startIndex);
                if(analyzeSequence(&S, so, fo, GS_list)){
                    addToTable(S, para_list[i], IC_list.at(j), mainTable, row, so);
                    row++;
                }
            }
        }
    }
    // new code ends


    /* Configures the column width, etc for the table*/
    configMainTableHeaders(mainTable);
    progress.setValue(numEvals);    //todo: why is this needed?
    // if it's sorted while rows are being added, they'll be overwritten.
    mainTable->setSortingEnabled(true);


    /*******************************
     *                             *
     *         FINAL LAYOUT        *
     *                             *
     *******************************/

    QVBoxLayout *tableLayout = new QVBoxLayout;
    tableLayout->addWidget(mainTable);

    QHBoxLayout *minorLayout = new QHBoxLayout;
    minorLayout->addLayout(optionListLayout);
    minorLayout->addLayout(tableLayout);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(recursionGroupBox);
    mainLayout->addLayout(minorLayout);
    mainLayout->dumpObjectTree();

    setLayout(mainLayout);
}

//todo: what should be cleaned up?
/**
 * Cleans up the page after the user pressed the back button.
 */
void ResultPage::cleanupPage(){
    QList<QObject*> L = children();
    for (int i = 0; i < L.size(); i++){
        //qDebug() << L[i];
        delete L[i];
    }
    delete layout();
}

//todo: what does this go?
/* Is this the result page constructor? */
    ResultPage::ResultPage(QWidget *parent)
:QWizardPage(parent){
    qDebug() << "Result Page Construction";
    debug = new QLineEdit;
}


/**
 * Imports data from the options page so it can be used by the main method
 */
void ResultPage::importOptionsPage(){

    /* Sets the toggles for the summaries to the appropriate value,
      depending on the corresponding checkbox on the options page */
    showSequenceToggle = field("showSequenceCheckBox").toBool();
    showDeathTimeToggle = field("showDeathTimeCheckBox").toBool();
    showFirstNotSlowToggle = field("showFirstNotSlowCheckBox").toBool();
    showSlowPropToggle = field("showSlowPropCheckbox").toBool();
    showSlowPropGenToggle = field("summaryCheckBox_11").toBool();
    showSlowPropIntToggle = field("ShowSlowPropIntCheckbox").toBool();
    showGenStructToggle = field("ShowGenStructCheckbox").toBool();
    showIsSlowToggle = field("showIsSlowCheckbox").toBool();
    showDoesDieToggle = field("showDoesDieCheckbox").toBool();
    showAverageToggle = field("showAverageCheckbox").toBool();
    show2RnToggle = field("show2RnCheckbox").toBool();
    showDiffToggle = field("showDiffCheckbox").toBool();
    showFreqToggle = field("showFreqCheckbox").toBool();
    showAdditionalToggle = field("showAdditionalCheckbox").toBool();

    /* Sets the additional expression and interval size based on the
      entry fields in the options page */
    summaryExpression = field("summaryExpression").toString();
    summaryInterval = field("summaryInterval").toInt();

    /* Sets the max value for n, and the output method*/
    termination = field("termination").toInt();
    output = field("output").toInt();

    debug->setText(tr("%1").arg(filterSlowProportionGT));// ???
}

/**
 * Creates the headers for the restults table based on the summary options
 * selected in the options page
 * @param so The SummaryOptions object that contains the summary options to
 * be used.
 */
void ResultPage::createHeaders(SummaryOptions so){
    /* QString tqstring; */
    //headers << ((multiplePara) ? "Para" : "IC");
    headers << "Para";
    headers << "IC";

    /* if <header-was-checked> { headers << <header_name>;} */
    if (so.sequence){ headers << "Sequence";}
    if (so.deathTime){ headers << "DT";}
    if (so.firstIndex){ headers << "1st Not Slow";}
    if (so.slowProportionGeneral){ headers << "Slow % O";}
    if (so.slowProportionByGeneration){ headers << "Slow % G";}
    if (so.slowProportionByInterval){ headers << "Slow % I";}
    if (so.generation){ headers << "Generation";}
    if (so.slow){ headers << "Slow";}
    if (so.die){ headers << "Die";}
    if (so.RnDivn){ headers << "R(n)/n";}
    if (so.twoRnMinusn){ headers << "2R(n)-n";}
    if (so.rnMinusRn){ headers << "R(n)-R(n-1)";}
    if (so.frequency){ headers << "Frequency";}
    if (so.additional){ headers << /*tqstring*/(* new QString).fromStdString(so.expression);}
}

/**
 * If the squence S violates any of the filter options, then return true,
 * otherwise return false.
 * @param fo The FilterOptions that contains the filters to use
 * @param S The sequence being tested for filter violations
 * @return true iff S violates at least 1 filter
 */
bool ResultPage::violatesFilter(FilterOptions fo, Sequence S){
    /* Note: 0 indicated one option, 1 indicates another, and 2 indicates neither
        --> Both 1 and 2 are values, so you can't just use if(fo.slow), etc */
    return (fo.slow == 0 && !S.slow)
        || (fo.slow == 1 && S.slow)
        || (fo.slowEventually == 0 && !S.slowEventually)
        || (fo.slowEventually == 1 && S.slowEventually)

        || (fo.die == 0 && !S.die)
        || (fo.die == 1 && S.die)

        || (fo.liveUntil == 0 && S.deathTime < fo.liveUntilValue)
        || (fo.liveUntil == 1 && S.deathTime > fo.dieBefore)

        || (fo.overlapping == 0 && !S.overlapping)
        || (fo.overlapping == 1 && S.overlapping)

        || (fo.slowProportion == 0 && S.slowProportion > fo.slowProportionLTValue)
        || (fo.slowProportion == 1 && S.slowProportion < fo.slowProportionGTValue)

        /* todo: how do these next 3 work? */
        || (fo.containSubstring == 0 && !S.checkContainSubstring( split(fo.containSubstringValue)) )
        || (fo.containSubstring == 1 && S.checkContainSubstring( split(fo.notContainSubstringValue)) )

        || (fo.containSubsequence == 0 && !S.checkContainSubsequence( split(fo.containSequenceValue)) )
        || (fo.containSubsequence == 1 && S.checkContainSubsequence( split(fo.notContainSequenceValue)) )

        || (fo.frequencyMatch == 0 && !S.checkFrequencyMatch( split(fo.frequencyMatchValue)) )
        || (fo.frequencyMatch == 1 && S.checkFrequencyMatch( split(fo.frequencyNotMatchValue)) );
}

/**
 * Imports the filter values from the filter options page.
 */
void ResultPage::importFilterOptions(){
    /* Imports values from radio buttons */
    filterRadios_0 = getButtonPressed("filterRadioButton_00","filterRadioButton_01","filterRadioButton_02");
            //boolsToNumber(field("filterRadioButton_00").toBool(), field("filterRadioButton_01").toBool(), field("filterRadioButton_02").toBool());
    filterRadios_1 = getButtonPressed("filterRadioButton_10","filterRadioButton_11","filterRadioButton_12");
    filterRadios_2 = getButtonPressed("filterRadioButton_20","filterRadioButton_21","filterRadioButton_22");
    filterRadios_3 = getButtonPressed("filterRadioButton_30","filterRadioButton_31","filterRadioButton_32");
    filterRadios_4 = getButtonPressed("filterRadioButton_40","filterRadioButton_41","filterRadioButton_42");
    filterRadios_5 = getButtonPressed("filterRadioButton_50","filterRadioButton_51","filterRadioButton_52");
    filterRadios_6 = getButtonPressed("filterRadioButton_60","filterRadioButton_61","filterRadioButton_62");
    filterRadios_7 = getButtonPressed("filterRadioButton_70","filterRadioButton_71","filterRadioButton_72");
    filterRadios_8 = getButtonPressed("filterRadioButton_80","filterRadioButton_81","filterRadioButton_82");

    /* Imports all number values */
    filterLiveUntil = field("filterLiveUntil").toInt();
    filterDieBefore = field("filterDieBefore").toInt();
    filterSlowProportionLT = field("filterSlowProportionLT").toDouble();
    filterSlowProportionGT = field("filterSlowProportionGT").toDouble();

    /* Imports the substring/subsequence to match/not match */
    filterContainSubstring = field("filterContainSubstring").toString();
    filterNotContainSubstring = field("filterNotContainSubstring").toString();
    filterContainSubsequence = field("filterContainSubsequence").toString();
    filterNotContainSubsequence = field("filterNotContainSubsequence").toString();

    /* Imports frequency to match/not match */
    filterFrequencyMatch = field("filterFrequencyMatch").toString();
    filterFrequencyNotMatch = field("filterFrequencyNotMatch").toString();
}

/**
 * Configures the filter options based on the imported values.
 * Can only be called once importFilterOptions() has been called.
 */
void ResultPage::configFilterOptions(QVBoxLayout* optionListLayout){
    if (filterRadios_0 == 0){
        QLabel *filterLabel_0 = new QLabel(tr("Slow"));
        optionListLayout->addWidget(filterLabel_0);
    } else if (filterRadios_0 == 1){
        QLabel *filterLabel_0 = new QLabel(tr("Not Slow"));
        optionListLayout->addWidget(filterLabel_0);
    }

    if (filterRadios_1 == 0){
        QLabel *filterLabel_1 = new QLabel(tr("Slow Eventually"));
        optionListLayout->addWidget(filterLabel_1);
    } else if (filterRadios_1 == 1){
        QLabel *filterLabel_1 = new QLabel(tr("Not Slow Eventually"));
        optionListLayout->addWidget(filterLabel_1);
    }

    if (filterRadios_2 == 0){
        QLabel *filterLabel_2 = new QLabel(tr("Die"));
        optionListLayout->addWidget(filterLabel_2);
    } else if (filterRadios_2 == 1){
        QLabel *filterLabel_2 = new QLabel(tr("Not Die"));
        optionListLayout->addWidget(filterLabel_2);
    }

    if (filterRadios_3 == 0){
        QLabel *filterLabel_3 = new QLabel(tr("Live Until %1").arg(filterLiveUntil));
        optionListLayout->addWidget(filterLabel_3);
    } else if (filterRadios_3 == 1){
        QLabel *filterLabel_3 = new QLabel(tr("Die before %1").arg(filterDieBefore));
        optionListLayout->addWidget(filterLabel_3);
    }

    if (filterRadios_4 == 0){
        QLabel *filterLabel_4 = new QLabel(tr("Overlapping"));
        optionListLayout->addWidget(filterLabel_4);
    } else if (filterRadios_4 == 1){
        QLabel *filterLabel_4 = new QLabel(tr("No Overlapping"));
        optionListLayout->addWidget(filterLabel_4);
    }

    if (filterRadios_5 == 0){
        QLabel *filterLabel_5 = new QLabel(tr("Slow Proportion < %1").arg(filterSlowProportionLT));
        optionListLayout->addWidget(filterLabel_5);
    } else if (filterRadios_5 == 1){
        QLabel *filterLabel_5 = new QLabel(tr("Slow Proportion > %1").arg(filterSlowProportionGT));
        optionListLayout->addWidget(filterLabel_5);
    }

    if (filterRadios_6 == 0){
        QLabel *filterLabel_6 = new QLabel(tr("Contain Substring:"));
        filterContainSubstring.remove(QChar(' '));
        filterContainSubstring.replace(QString(","), QString(", "));
        QLabel *filterLabel_61 = new QLabel(filterContainSubstring);
        filterLabel_6->setWordWrap(true);
        filterLabel_61->setWordWrap(true);
        optionListLayout->addWidget(filterLabel_6);
        optionListLayout->addWidget(filterLabel_61);
    } else if (filterRadios_6 == 1){
        QLabel *filterLabel_6 = new QLabel(tr("Not Contain Substring:"));
        filterNotContainSubstring.remove(QChar(' '));
        filterNotContainSubstring.replace(QString(","), QString(", "));
        QLabel *filterLabel_61 = new QLabel(filterNotContainSubstring);
        filterLabel_6->setWordWrap(true);
        filterLabel_61->setWordWrap(true);
        optionListLayout->addWidget(filterLabel_6);
        optionListLayout->addWidget(filterLabel_61);
    }

    if (filterRadios_7 == 0){
        QLabel *filterLabel_7 = new QLabel(tr("Contain Subsequence:"));
        filterContainSubsequence.remove(QChar(' '));
        filterContainSubsequence.replace(QString(","), QString(", "));
        QLabel *filterLabel_71 = new QLabel(filterContainSubsequence);
        filterLabel_7->setWordWrap(true);
        filterLabel_71->setWordWrap(true);
        optionListLayout->addWidget(filterLabel_7);
        optionListLayout->addWidget(filterLabel_71);
    } else if (filterRadios_7 == 1){
        QLabel *filterLabel_7 = new QLabel(tr("Not Contain Subsequence:"));
        filterNotContainSubsequence.remove(QChar(' '));
        filterNotContainSubsequence.replace(QString(","), QString(", "));
        QLabel *filterLabel_71 = new QLabel(filterNotContainSubsequence);
        filterLabel_7->setWordWrap(true);
        filterLabel_71->setWordWrap(true);
        optionListLayout->addWidget(filterLabel_7);
        optionListLayout->addWidget(filterLabel_71);
    }

    if (filterRadios_8 == 0){
        QLabel *filterLabel_8 = new QLabel(tr("Frequency Matches:"));
        filterFrequencyMatch.remove(QChar(' '));
        filterFrequencyMatch.replace(QString(","), QString(", "));
        QLabel *filterLabel_81 = new QLabel(filterFrequencyMatch);
        filterLabel_8->setWordWrap(true);
        filterLabel_81->setWordWrap(true);
        optionListLayout->addWidget(filterLabel_8);
        optionListLayout->addWidget(filterLabel_81);
    } else if (filterRadios_8 == 1){
        QLabel *filterLabel_8 = new QLabel(tr("Frequency Does Not Match:"));
        filterFrequencyNotMatch.remove(QChar(' '));
        filterFrequencyNotMatch.replace(QString(","), QString(", "));
        QLabel *filterLabel_81 = new QLabel(filterFrequencyNotMatch);
        filterLabel_8->setWordWrap(true);
        filterLabel_81->setWordWrap(true);
        optionListLayout->addWidget(filterLabel_8);
        optionListLayout->addWidget(filterLabel_81);
    }

    optionListLayout->addStretch();
}

/**
 * Imports and configures the text for the recursion box
 * @param recursionGroupBox The QGroupBox that everything should be added to
 * @param newRecursion The QString that will contain the recursion text when
 * this finishes executing.
 */
void ResultPage::createRecursionBox(QGroupBox* recursionGroupBox, QString* newRecursion){
    *newRecursion = field("updatedRecursion").toString();
    QLabel *recursionLabel = new QLabel(tr("R(n) = ") + *newRecursion);
    recursionLabel->setFont(QFont("Verdana", 12,QFont::Bold));
    QHBoxLayout *recursionLayout = new QHBoxLayout;
    recursionLayout->addWidget(recursionLabel);
    recursionGroupBox->setLayout(recursionLayout);
}

/*todo: this really inserts a row. change the signature/name to match that and
move all code relevant to that row into this method */
void ResultPage::configOutputTable(SummaryOptions so, Sequence S, int row, int startCol, QTableWidget* mainTable){
    int column = startCol;
    /* If sequence is checked, add a cell with "Click" in it, and push the resulting
     * sequence onto the sequence vector */
    if (so.sequence) {
        QTableWidgetItem *sequenceCell = new QTableWidgetItem(tr("Click"));
        mainTable->setItem(row, column++, sequenceCell);
        sequenceVector.push_back(static_cast<vector<int> >(S.R));
    }
    if (so.deathTime) {
        QTableWidgetItem *deathTimeCell = new QTableWidgetItem(tr("%1").arg(S.deathTime));
        mainTable->setItem(row, column++, deathTimeCell);
    }
    if (so.firstIndex) {
        QTableWidgetItem *firstNotSlowCell = new QTableWidgetItem(tr("%1").arg(S.firstNotSlow));
        mainTable->setItem(row, column++, firstNotSlowCell);
        //cout << S.firstNotSlow << "\t";
    }
    if (so.slowProportionGeneral) {
        QTableWidgetItem *slowProportionCell = new QTableWidgetItem(tr("%1").arg(S.slowProportion));
        mainTable->setItem(row, column++, slowProportionCell);
        //cout << S.slowProportion << "\t";
    }
    if (so.slowProportionByGeneration) {
        QTableWidgetItem *slowProportionByGenerationCell = new QTableWidgetItem(tr("Click"));
        mainTable->setItem(row, column++, slowProportionByGenerationCell);
        genStartVector.push_back(static_cast<vector<int> >(S.genStart));
        genEndVector.push_back(static_cast<vector<int> >(S.genEnd));
        slowPropGenerationVector.push_back(static_cast<vector<double> >(S.slowPropGeneration));
    }
    if (so.slowProportionByInterval) {
        QTableWidgetItem *slowProportionByIntervalCell = new QTableWidgetItem(tr("Click"));
        mainTable->setItem(row, column++, slowProportionByIntervalCell);
        slowPropIntervalVector.push_back(static_cast<vector<double> >(S.slowPropInterval));
    }
    if (so.generation) {
        QTableWidgetItem *generationCell = new QTableWidgetItem(tr("Click"));
        mainTable->setItem(row, column++, generationCell);
        genStartVector.push_back(static_cast<vector<int> >(S.genStart));
        genEndVector.push_back(static_cast<vector<int> >(S.genEnd));
        slowPropGenerationVector.push_back(static_cast<vector<double> >(S.slowPropGeneration));
    }
    if (so.slow) {
        QTableWidgetItem *slowCell = new QTableWidgetItem(tr(((S.slow)?"Slow":"Not Slow")));
        mainTable->setItem(row, column++, slowCell);
        //cout << ((S.slow)?"True":"False") << "\t";
    }
    if (so.die) {
        QTableWidgetItem *dieCell = new QTableWidgetItem(tr(((S.die)?"Die":"Not Die")));
        mainTable->setItem(row, column++, dieCell);
        //cout << ((S.die)?"True":"False") << "\t";
    }
    if (so.RnDivn) {
        QTableWidgetItem *RnDivnCell = new QTableWidgetItem(tr("Click"));
        mainTable->setItem(row, column++, RnDivnCell);
        vector<double> s;
        RnDivnVector.push_back(S.RnDivn);
    }
    if (so.twoRnMinusn) {
        QTableWidgetItem *twoRnMinusnCell = new QTableWidgetItem(tr("Click"));
        mainTable->setItem(row, column++, twoRnMinusnCell);
        twoRnMinusnVector.push_back(static_cast<vector<int> >(S.twoRnMinusn));
    }
    if (so.rnMinusRn) {
        QTableWidgetItem *rnMinusRnCell = new QTableWidgetItem(tr("Click"));
        mainTable->setItem(row, column++, rnMinusRnCell);
        rnMinusRnVector.push_back(static_cast<vector<int> >(S.rnMinusRn));
    }
    if (so.frequency) {
        QTableWidgetItem *frequencyCell = new QTableWidgetItem(tr("Click"));
        mainTable->setItem(row, column++, frequencyCell);
        frequencyVector.push_back(static_cast<vector<int> >(S.frequency));
    }
    if (so.additional) {
        QTableWidgetItem *additionalCell = new QTableWidgetItem(tr("Click"));
        mainTable->setItem(row, column++, additionalCell);
        additionVector.push_back(static_cast<vector<int> >(S.addition));
    }

    //*newColumnValue = column;
}

/**
 * Configures the column width and sizing rules for the table
 * @param mainTable The table that's being customized
 */
void ResultPage::configMainTableHeaders(QTableWidget* mainTable){
    mainTable->setHorizontalHeaderLabels(headers);
    mainTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    mainTable->horizontalHeader()->setStretchLastSection(true);
    mainTable->resizeColumnsToContents();
    mainTable->resizeColumnToContents(0);
    QSizePolicy sizeP;
    mainTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(mainTable, SIGNAL(cellClicked(int, int)), this, SLOT(showSequence(int, int)));
}

bool ResultPage::analyzeSequence(Sequence* S, SummaryOptions so, FilterOptions fo, vector<vector<int> > GS_list){

    if(S->dieImmediately()) {return false;}
    if(!S->satisfiedConstraint()) {return false;}

    S->compute(termination);
    /*todo: what is GS_list[0]??*/
    S->analyse(GS_list[0], summaryInterval, summaryExpression.toStdString(), fo, so);

    /* If one of the filter checks fails, return false */
    if(violatesFilter(fo, *S)){ return false; }

    return true;
}

void ResultPage::addToTable(Sequence S, vector<int> para_list, vector<int> currentIC, QTableWidget* mainTable, int row, SummaryOptions so){
    //this appends either the parameters or IC to the front of the row.
    //todo: update this to show BOTH (if applicable)
    QString paraValueString;
    QString ICValueString;
    /*int upperBound = multiplePara ? para_list.size() : currentIC.size();
    Vector valueList = multiplePara ? para_list : currentIC;
    for(int j = 0; j < upperBound; j++){
        valueString += tr("%1").arg(valueList[j]);
        if(j != upperBound - 1){
            valueString += tr(",");
        }
    }
    ICParaList << valueString;
    QTableWidgetItem *valueCell = new QTableWidgetItem(valueString);*/
    mainTable->setRowCount(row + 1);
    int col = 0;

    /* Adds the column with the parameter info */
    for(uint i = 0; i < para_list.size(); i++){
        paraValueString += tr("%1").arg(para_list.at(i));
        if(i != para_list.size() - 1){
            paraValueString += tr(",");
        }
    }
    QTableWidgetItem *paraValueCell = new QTableWidgetItem(paraValueString);
    ICParaList << paraValueString;
    mainTable->setItem(row, col++, paraValueCell);


    /* Adds the column with the initial condition info */
    for(uint i = 0; i < currentIC.size(); i++){
        ICValueString += tr("%1").arg(currentIC.at(i));
        if(i != currentIC.size() - 1){
            ICValueString += tr(",");
        }
    }
    QTableWidgetItem *ICValueCell = new QTableWidgetItem(ICValueString);
    //ICParaList << paraValueString;
    /* Sets the param/IC column, and then the rest of the row */
    mainTable->setItem(row, col++, ICValueCell);

    /* Adds the rest of the row*/
    configOutputTable(so, S, row, col, mainTable);
}
