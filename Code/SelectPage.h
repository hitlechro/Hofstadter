#ifndef SELECTPAGE_H
#define SELECTPAGE_H

#include "ClassDefs.h"
#include <QWizardPage>

class SelectPage : public QWizardPage
{
    Q_OBJECT

public:
    SelectPage(QWidget *parent=0);

private:
    /** The label for the text field */
    QLabel *label;
    ///** */
    //QLabel *label_config;/
    /** The label for the recursion list */
    QLabel *RnLabel;
    /** The entry field for new recursions */
    QLineEdit *newRecursion;
    /** The list of saved recursions */
    QListWidget *recursionList;

public slots:
    // documented in SelectPage.cpp
    void saveRecursion();
    void removeRecursion();
    void updateLineEdit(QListWidgetItem * item);
};

#endif // SELECTPAGE_H
