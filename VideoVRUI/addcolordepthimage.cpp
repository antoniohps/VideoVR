#include "addcolordepthimage.h"
#include "ui_addcolordepthimage.h"

AddColorDepthImage::AddColorDepthImage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddColorDepthImage)
{
    ui->setupUi(this);
}

AddColorDepthImage::~AddColorDepthImage()
{
    delete ui;
}
