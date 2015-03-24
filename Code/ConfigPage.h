#ifndef CONFIGPAGE_H
#define CONFIGPAGE_H

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
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QButtonGroup>

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


    QSpinBox *ICStartSpinBox;
    QSpinBox *ICFinishSpinBox;
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

    void updateICStart(int startIndex);
    void updateICFinish(int endIndex);
    void setNewRowValues(int rowInd, int arg);
    void updateParaLineEdit();
    void updateICLineEdit(int r=0, int c=1);


};
#endif // CONFIGPAGE_H
