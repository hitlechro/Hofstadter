#include "SelectPage.h"


/** Appends the current recursion (in the entry field) to the file */
void SelectPage::saveRecursion(){
    /* try to open the file containing the recursions.
    if it fails, just skip it */
    QFile file(RECURSION_FILE);
    if (!file.open(QIODevice::Append | QIODevice::Text))
        return;
    //todo: error message on failure

    /* Saves the current recursion in the text box in the file */
    QTextStream out(&file);
    out << newRecursion->text() << "\n";
    new QListWidgetItem(newRecursion->text(), recursionList);
    file.close();
}

/** Removes the current recursion (in the list) from the list and file */
void SelectPage::removeRecursion(){
    /* try to open the file containing the recursions.
    if it fails, just skip it */
    QFile file(RECURSION_FILE);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    //todo: error message on failure

    /* Removes the currently selected item from the list,
    and then saves the list, removing the item from the file */
    recursionList->takeItem(recursionList->currentRow());
    QTextStream out(&file);
    for (int i = 0; i < recursionList->count(); i++){
        out << recursionList->item(i)->text() << "\n";
    }

    file.close();
}

/** Sets the text field's text to the selected item's text */
void SelectPage::updateLineEdit(QListWidgetItem * item){
    newRecursion->setText(item->text());
}

/** Creates a selection page (to select a recursion to use) with a
  given parent.
  @param parent The object that this will be a child of */
SelectPage::SelectPage(QWidget *parent)
    :QWizardPage(parent) {

    /* Defines the page header */
    setTitle(tr("Select a Recursion"));
    label = new QLabel(tr("Please enter a recursion:"));
    label->setWordWrap(true);

    /* Defines the label and text field for entering a recursion */
    RnLabel = new QLabel(tr("R(n) = "));
    RnLabel->setFont(QFont("Verdana", 12,QFont::Bold));
    newRecursion = new QLineEdit;
    newRecursion->setFont(QFont("Verdana", 12,QFont::Bold));
    RnLabel->setBuddy(newRecursion); // redirects focus for keyboard shortcuts, why?

    /* Defined the buttons for saving and deleting recursions, and
      adds event listeners to them */
    QPushButton *PushButton_1 = new QPushButton(tr("&Save"));
    QPushButton *PushButton_2 = new QPushButton(tr("&Remove"));
    connect(PushButton_1, SIGNAL(clicked()), this, SLOT(saveRecursion()));
    connect(PushButton_2, SIGNAL(clicked()), this, SLOT(removeRecursion()));
    /* Binds the name "newRecursion" to the new recursion text field */
    registerField("newRecursion", newRecursion);
    /* Adds the buttons and text fields to the window */
    QHBoxLayout *recursionLayout = new QHBoxLayout;
    recursionLayout->addWidget(RnLabel);
    recursionLayout->addWidget(newRecursion);
    recursionLayout->addWidget(PushButton_1);
    recursionLayout->addWidget(PushButton_2);

    /* Defines the label and list for selecting a saved recursion */
    QLabel *selectLabel_2 = new QLabel(tr("or select a recursion from below:"));
    recursionList = new QListWidget;

    /* Opens the text file with the saved recursions for reading */
    QFile file(RECURSION_FILE);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        /* While it's not empty,add one line from the file at a time */
        QTextStream in(&file);
        while (!in.atEnd()) {
           QString line = in.readLine();
           new QListWidgetItem(line, recursionList);
        }
    }
    //todo: error if file can't be opened

    /* Sets the list's format and attaches an event listener */
    recursionList->setFont(QFont("Verdana", 12, QFont::Bold));
    recursionList->setGridSize(QSize(100, 30));
    connect(recursionList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(updateLineEdit(QListWidgetItem*)));
    QVBoxLayout *layout = new QVBoxLayout;

    /* adds the list to the window */
    layout->addWidget(label);
    layout->addLayout(recursionLayout);
    layout->addWidget(selectLabel_2);
    layout->addWidget(recursionList);
    setLayout(layout);

    qDebug() << "Select page Construction done";
}
