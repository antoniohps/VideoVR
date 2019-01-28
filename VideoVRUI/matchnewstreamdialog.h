#ifndef MATCHNEWSTREAMDIALOG_H
#define MATCHNEWSTREAMDIALOG_H

#include <QDialog>

namespace Ui {
class MatchNewStreamDialog;
}

class MatchNewStreamDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MatchNewStreamDialog(QWidget *parent = 0);
    ~MatchNewStreamDialog();

private:
    Ui::MatchNewStreamDialog *ui;
};

#endif // MATCHNEWSTREAMDIALOG_H
