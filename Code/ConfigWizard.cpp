#include <QtGui>
#include <QVariant>
#include <QRegExp>
//#include <iostream>
//#include "kernel.cpp"
#include "configwizard.h"
#include "ConfigPage.h"
#include "OptionPage.h"
#include "SelectPage.h"
#include "ResultPage.h"


/** Creates a new configuration wizard
  @param parent A pointer to the parent of this wizard */
ConfigWizard::ConfigWizard(QWidget *parent)
    :QWizard(parent)
{

     this->addPage(new SelectPage(this));
     this->addPage(new ConfigPage(this));
     OptionPage * newCP2 = new OptionPage(this);
     newCP2->run = 0; //set run variable to zero, controls updating the labels

     this->addPage(newCP2);
     this->addPage(new ResultPage);
     setWindowTitle(tr("Configurations"));
}


/** Goes to the next page in the wizard */
void ConfigWizard::accept(){
     QDialog::accept();
}

