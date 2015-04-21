#include "OptionPage.h"
#include "Sequence.h"
#include <vector>
#include <sstream>
#include <string>

void OptionPage::updateLabel()
{

    vector<int> dummy;
    vector<string> dummyString;
    Sequence S(field("newRecursion").toString().toStdString(), dummy, dummy, dummyString, false, 1);

    QString newLabel = field("newRecursion").toString();

    QStringList parameters = field("paraList").toString().split("@@");
    int position = 0;

    qDebug() << "Recursion = " << newLabel << " paras " << field("paraList").toString();

    /* Replaces each parameter with its value */
    for (uint i = 0; i < S.c.parameter.size(); i++)
    {

        QString converter;
        QChar charConverter;

        qDebug() << "An Item: " + converter.fromStdString(S.c.parameter[i]);
        //if (S.c.parameter[i] == "^" || S.c.parameter[i] == "i") continue;

        //QString val = converter.fromStdString(S.c.parameter[i]);
        //QChar cVal = charConverter.fromAscii(parameters[position]);
        QString varName = converter.fromStdString(S.c.parameter[i]);
        QString varVal = parameters[i];


        //qDebug() << "running " << i << ": " << varName << " replace: " << value << " pos : " << position;

        int index = newLabel.indexOf(varName);
        while(index >= 0){
            newLabel.remove(index, varName.length());
            //newLabel.insert(index, varVal);
            //todo: put each value range in parentheses.
            //for some reason, this messes up the evaluation. why?
            newLabel.insert(index, "{" + varVal + "}");
            index = newLabel.indexOf(varName);
        }

        position++; // jump ahead two positions, params seperated by @@

    }
    qDebug() << "Recursion2 = " << newLabel;


    if(run == 0){
        updatedRecursion = new QLineEdit;
        updatedRecursion->setFont(QFont("Verdana", 12,QFont::Bold));
        updatedRecursion->setText(newLabel);

        registerField("updatedRecursion", updatedRecursion);
        run = 1; // toggle run once
    }else{
        QVariant  v(newLabel);
        setField("updatedRecursion",v);
               // qDebug() << "NO MORE!!!D";
    }

    qDebug() << " And now...." << field("updatedRecursion").toString();
  //   registerField(tr("showSequenceCheckBox"), showSequenceCheckBox);

}

void OptionPage::updateGS(int noIC)
{
    //int noIC = ICSpinBox->value();
    GSGlobalLineEdit->setText(tr(""));

    int row = GSTable->rowCount();

    if (noIC > row){
        for (int i = row; i < noIC; i++){
            GSTable->setRowCount(i + 1);

            QTableWidgetItem *GSItem = new QTableWidgetItem(tr("M(%1)").arg(i+1));
            GSItem->setFlags(Qt::ItemIsEditable);
            GSTable->setItem(i, 0, GSItem);

            QTableWidgetItem *GSValue = new QTableWidgetItem(tr("1"));
            GSTable->setItem(i, 1, GSValue);
        }
    } else {
        GSTable->setRowCount(noIC);
        updateGSLineEdit();
    }
    GSTable->resizeRowsToContents();
}

//TODO: R is not used
void OptionPage::updateGSLineEdit(int r, int c)
{
    QString GSString;
    if (c != 0){
        for (int i = 0; i < GSTable->rowCount(); i++){
            GSString += GSTable->item(i,1)->text();

            if (i != GSTable->rowCount()-1)
                GSString += "@@";
        }
        GSGlobalLineEdit->setText(GSString);
    }
}


void OptionPage::initializePage()
{
    updateLabel();
    recursionLabel->setText(tr("R(n) = ") + field("updatedRecursion").toString());
}

OptionPage::OptionPage(QWidget *parent): QWizardPage(parent)
{
   // updateLabel(1);
 //   recursionLabel->setText(tr("R(n) = ") + field("updatedRecursion").toString());

    setFont(QFont("Verdana,18"));

    // Set the recursion box
    QGroupBox * recursionGroupBox = new QGroupBox(tr("Recursion"));

    //create a label
    recursionLabel = new QLabel();
    recursionLabel->setFont(QFont("Verdana",12, QFont::Bold));


    //setup the layout
    QHBoxLayout *recursionLayout2 = new QHBoxLayout;
    recursionLayout2->addWidget(recursionLabel);
    recursionGroupBox->setLayout(recursionLayout2);

    /*******************************
     *                             *
     *           Summary           *
     *                             *
     *******************************/

     QCheckBox *showSequenceCheckBox = new QCheckBox(tr("Sequence"));
     QCheckBox *showDeathTimeCheckBox = new QCheckBox(tr("Death Time"));
     QCheckBox *showFirstNotSlowCheckBox = new QCheckBox(tr("1st Index Not Slow"));
     QCheckBox *showSlowPropCheckbox = new QCheckBox(tr("Overall Slow Proportion"));
     QCheckBox *showSlowPropGenCheckbox = new QCheckBox(tr("Slow Proportion by Generation"));

     QSpinBox *summaryInterval = new QSpinBox();
     summaryInterval->setMinimum(0);
     summaryInterval->setMaximum(2147483647);
     summaryInterval->setValue(10000);
     QCheckBox *showSlowPropIntCheckbox = new QCheckBox(tr("Slow Proportion by Interval"));
     QHBoxLayout *summaryLayout_0 = new QHBoxLayout;
     summaryLayout_0->addWidget(showSlowPropIntCheckbox);
     summaryLayout_0->addWidget(summaryInterval);

     QCheckBox *showGenStructCheckbox = new QCheckBox(tr("Generational Structure"));
     QCheckBox *showIsSlowCheckbox = new QCheckBox(tr("Slow / Not Slow"));
     QCheckBox *showDoesDieCheckbox = new QCheckBox(tr("Die / Not Die"));
     QCheckBox *showAverageCheckbox = new QCheckBox(tr("R(n)/n"));
     QCheckBox *show2RnCheckbox = new QCheckBox(tr("2R(n)-n"));
     QCheckBox *showDiffCheckbox = new QCheckBox(tr("R(n)-R(n-1)"));
     QCheckBox *showFreqCheckbox = new QCheckBox(tr("Frequency"));
     QCheckBox *showAdditionalCheckbox = new QCheckBox(tr("Additional Expression :"));

     showSequenceCheckBox->setCheckState(Qt::Checked);
     showDeathTimeCheckBox->setCheckState(Qt::Checked);
     showSlowPropCheckbox->setCheckState(Qt::Checked);
     showIsSlowCheckbox->setCheckState(Qt::Checked);
     showDoesDieCheckbox->setCheckState(Qt::Checked);


     QLineEdit *summaryLineEdit_0 = new QLineEdit;
     QHBoxLayout *summaryLayout_1 = new QHBoxLayout;
     //summaryLineEdit_0->setFixedSize(20, summaryLineEdit_0->size().height());
     summaryLayout_1->addWidget(showAdditionalCheckbox);
     summaryLayout_1->addWidget(summaryLineEdit_0);
     summaryLayout_1->addStretch();

     QGridLayout *summaryLayout = new QGridLayout;
     summaryLayout->addWidget(showSequenceCheckBox, 0, 0);
     summaryLayout->addWidget(showDeathTimeCheckBox, 0, 1);
     summaryLayout->addWidget(showFirstNotSlowCheckBox, 0, 2);
     summaryLayout->addWidget(showSlowPropCheckbox, 1, 0);
     summaryLayout->addWidget(showSlowPropGenCheckbox, 1, 1);

     summaryLayout->addLayout(summaryLayout_0, 1, 2);
     summaryLayout->addWidget(showGenStructCheckbox, 2, 0);
     summaryLayout->addWidget(showIsSlowCheckbox, 2, 1);
     summaryLayout->addWidget(showDoesDieCheckbox, 2, 2);
     summaryLayout->addWidget(showAverageCheckbox, 3, 0);
     summaryLayout->addWidget(show2RnCheckbox, 3, 1);
     summaryLayout->addWidget(showDiffCheckbox, 3, 2);
     summaryLayout->addWidget(showFreqCheckbox, 4, 0);
     summaryLayout->addLayout(summaryLayout_1, 4, 1,1,2);

     QGroupBox *summaryGroupBox = new QGroupBox(tr("Summary"));
     summaryGroupBox->setLayout(summaryLayout);

     registerField(tr("showSequenceCheckBox"), showSequenceCheckBox);
     registerField(tr("showDeathTimeCheckBox"), showDeathTimeCheckBox);
     registerField(tr("showFirstNotSlowCheckBox"), showFirstNotSlowCheckBox);
     registerField(tr("showSlowPropCheckbox"), showSlowPropCheckbox);
     registerField(tr("showSlowPropGenCheckbox"), showSlowPropGenCheckbox);
     registerField(tr("showSlowPropIntCheckbox"), showSlowPropIntCheckbox);
     registerField(tr("showGenStructCheckbox"), showGenStructCheckbox);
     registerField(tr("showIsSlowCheckbox"), showIsSlowCheckbox);
     registerField(tr("showDoesDieCheckbox"), showDoesDieCheckbox);
     registerField(tr("showAverageCheckbox"), showAverageCheckbox);
     registerField(tr("show2RnCheckbox"), show2RnCheckbox);
     registerField(tr("showDiffCheckbox"), showDiffCheckbox);
     registerField(tr("showFreqCheckbox"), showFreqCheckbox);
     registerField(tr("showAdditionalCheckbox"), showAdditionalCheckbox);
     registerField(tr("summaryExpression"), summaryLineEdit_0);
     registerField(tr("summaryInterval"), summaryInterval);

    /*******************************
     *                             *
     *    Generational Structure   *
     *                             *
     *******************************/

     QLabel *GSLabel_0 = new QLabel(tr("No. of ICs : "));
     GSSpinBox = new QSpinBox;
     QHBoxLayout *GSLayout_0 = new QHBoxLayout;
     GSLayout_0->addWidget(GSLabel_0);
     GSLayout_0->addWidget(GSSpinBox);

     GSTable = new QTableWidget(0,2);
     GSTable->setHorizontalHeaderLabels(QStringList() << "M-ICs" << "Values");

     GSTable->horizontalHeader()->setStretchLastSection(true);
     GSTable->verticalHeader()->hide();

     QVBoxLayout *GSLayout_1 = new QVBoxLayout;
     GSLayout_1->addLayout(GSLayout_0);
     GSLayout_1->addWidget(GSTable);


     QGroupBox *GSGroupBox = new QGroupBox(tr("Generational Structure"));
     GSGroupBox->setLayout(GSLayout_1);

     GSGlobalLineEdit = new QLineEdit();
     registerField(tr("GSList"), GSGlobalLineEdit);


     connect(GSSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateGS(int)));
     GSGlobalLineEdit->setText(tr(""));
     connect(GSTable, SIGNAL(cellChanged(int, int)), this, SLOT(updateGSLineEdit(int, int)));

     // Summary + GS
     QHBoxLayout *summaryGSLayout = new QHBoxLayout;
     summaryGSLayout->addWidget(summaryGroupBox);
     summaryGSLayout->addWidget(GSGroupBox);

     //  outputGroupBox->setLayout(  //  outputGroupBox->setLayout(outputLayout);


     // Output
     QGroupBox *outputGroupBox = new QGroupBox(tr("Output"));
     QComboBox *outputComboBox = new QComboBox();
     outputComboBox->addItems(QStringList() << "On Screen Display" << "Microsoft Excel File" << "Text File");
     QLabel *outputLabel_0 = new QLabel(tr("Generate until term:"));
     QLabel *outputLabel_1 = new QLabel(tr("Output to:"));
     QSpinBox *termination = new QSpinBox;
     termination->setMinimum(0);
     termination->setMaximum(2147483647);
     termination->setValue(10000);

     QHBoxLayout *outputLayout = new QHBoxLayout;
     outputLayout->addWidget(outputLabel_0);
     outputLayout->addWidget(termination);
 //    outputLayout->addStretch();
 //   outputLayout->addStretch();
     outputLayout->addWidget(outputLabel_1);
     outputLayout->addWidget(outputComboBox);
 //    outputLayout->addStretch();

    outputGroupBox->setLayout(outputLayout);

    registerField(tr("termination"), termination);
    registerField(tr("output"), outputComboBox);

    QVBoxLayout *layout = new QVBoxLayout;
      layout->addWidget(recursionGroupBox);
       layout->addWidget(outputGroupBox);
       layout->addLayout(summaryGSLayout);

    setLayout(layout);

    /* disabled these until they can be implemented */
    // todo: enable these when completed
    showSlowPropGenCheckbox->setEnabled(false);
    showGenStructCheckbox->setEnabled(false);
    showSlowPropIntCheckbox->setEnabled(false);
}
