#include "streamintegrationdialog.h"
#include "ui_streamintegrationdialog.h"

StreamIntegrationDialog::StreamIntegrationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StreamIntegrationDialog),
    m_matchType(NOT_CHOSEN)
{
    ui->setupUi(this);
}

StreamIntegrationDialog::~StreamIntegrationDialog()
{
    delete ui;
}
