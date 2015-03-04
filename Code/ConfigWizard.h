#ifndef CONFIGWIZARD_H
#define CONFIGWIZARD_H

#include <QWizard>
#include "ClassDefs.h"


class ConfigWizard : public QWizard
{
    Q_OBJECT

public:
    ConfigWizard(QWidget *parent=0);

    void accept();
};


#endif // CONFIGWIZARD_H
