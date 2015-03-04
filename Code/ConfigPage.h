#ifndef CONFIGPAGE_H
#define CONFIGPAGE_H

#include "ClassDefs.h"
#include <QWizardPage>

class ConfigPage : public QWizardPage
{
    Q_OBJECT

public:
    ConfigPage(QWidget *parent=0);

private:
    QLabel *recursionLabel;

    QListWidget *paraConstraintList;
    /** The text field for entering parameter constraints */
    QLineEdit *constraintLineEdit;
    /** The text containing the parameter names */
    QLineEdit *paraNameGlobalLineEdit;
    /** The text containing the parameter values */
    QLineEdit *paraGlobalLineEdit;
    QLineEdit *paraConstraintGlobalLineEdit;
    QTableWidget *paraTable;



    QSpinBox *ICSpinBox;
    QTableWidget *ICTable;
    QLineEdit *ICGlobalLineEdit;
    QSpinBox *GSSpinBox;
    /** The string containing the default parameter values */
    QString paraDefault;

    void updateConstraintLineEdit();

protected:
    void initializePage();

public slots:
    void addExtraConstraint();
    void removeExtraConstraint();

    void updateIC(int noIC);
    void updateParaLineEdit();
    void updateICLineEdit(int r=0, int c=1);


};
#endif // CONFIGPAGE_H
