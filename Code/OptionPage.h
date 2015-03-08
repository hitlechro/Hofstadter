#ifndef CONFIGPAGE2_H
#define CONFIGPAGE2_H

#include "ClassDefs.h"
#include <QtWidgets/QWizardPage>

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

#include <QDebug>

class OptionPage: public QWizardPage
{
    Q_OBJECT;

public:
    OptionPage(QWidget * parent = 0);
    int run;

private:
    QLabel * recursionLabel;
    QSpinBox *GSSpinBox;
    QTableWidget *GSTable;
    QLineEdit *GSGlobalLineEdit;
    /** Contains the updated recursion (with the parameters) */
    QLineEdit *updatedRecursion;


protected:
    void initializePage();
    void updateLabel();

public slots:
    void updateGS(int noIC);
    void updateGSLineEdit(int r=0, int c=1);

};

#endif // CONFIGPAGE2_H
