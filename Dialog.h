#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
QT_END_NAMESPACE

//! [0]
class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog();

private:
    void createMenu();
    void createHorizontalGroupBox();
    void createGridGroupBox();
    void createFormGroupBox();
    void createVerticalGroupBox();
    enum { NumGridRows = 3, NumButtons = 4 };

    QMenuBar* menuBar;
    QGroupBox* horizontalGroupBox;
    QGroupBox* gridGroupBox;
    QGroupBox* gridGroupBoxTwo;
    QGroupBox* formGroupBox;
    QTextEdit* smallEditor;
    QTextEdit* smallEditorTwo;
    QTextEdit* bigEditor;
    QLabel* labels[NumGridRows];
    QLineEdit* lineEdits[NumGridRows];
    QPushButton* buttons[NumButtons];
    QDialogButtonBox* buttonBox;

    QMenu* fileMenu;
    QAction* exitAction;
};
//! [0]

#endif // DIALOG_H