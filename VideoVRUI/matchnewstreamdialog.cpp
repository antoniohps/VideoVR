#include "matchnewstreamdialog.h"
#include "ui_matchnewstreamdialog.h"

MatchNewStreamDialog::MatchNewStreamDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MatchNewStreamDialog)
{
    ui->setupUi(this);
}

MatchNewStreamDialog::~MatchNewStreamDialog()
{
    delete ui;
}
