#include "addstereoimage.h"
#include "ui_addstereoimage.h"

#include "MSVRStereoImage.h"

#include <QString>
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>

using namespace ip;
using namespace msvr;


AddStereoImage::AddStereoImage(MainWindow *_parent) :
    QDialog(_parent),

    leftImageLoaded (false),
    rightImageLoaded(false),
    calibDataLoaded (false),

    ui(new Ui::AddStereoImage),
    parent(_parent)

{
    ui->setupUi(this);
}

AddStereoImage::~AddStereoImage()
{
    delete ui;
}

void AddStereoImage::on_openLeftStreamButton_clicked()
{
    //Get current dir
    QFileInfo currFile(ui->leftStreamFileName->text());
    QDir currDir(currFile.exists() ? currFile.absoluteDir() : QDir());

    QString fname = QFileDialog::getOpenFileName(this,tr("Open left stream"),currDir.dirName());
    ui->leftStreamFileName->setText(fname);

    if(QFile(fname).exists()) {
        ui->leftStreamPanel->openFile(fname);
        leftImageLoaded = true;
    }
}

void AddStereoImage::on_openRightStreamButton_clicked()
{
    //Get current dir
    QFileInfo currFile(ui->rightStreamFileName->text());
    QDir currDir(currFile.exists() ? currFile.absoluteDir() : QDir());

    QString fname = QFileDialog::getOpenFileName(this,tr("Open right stream"),currDir.dirName());
    ui->rightStreamFileName->setText(fname);

    if(QFile(fname).exists()) {
        ui->rightStreamPanel->openFile(fname);
        rightImageLoaded = true;
    }
}

void AddStereoImage::on_buttonBox_accepted()
{
    if(m_stream.get() != NULL) {

        //Invoke main window method, that will update UI as well
        parent->addStream(m_stream);

        this->accept();

    } else {
        //TODO: issue an error message
    }
}


void AddStereoImage::on_openCalibDirButton_clicked()
{

    QFileInfo currFile(ui->calibDirName->text());
    QDir currDir(currFile.exists() ? currFile.absoluteDir() : QDir());

    QString dir = QFileDialog::getExistingDirectory(this,tr("Open calibration directory"),currDir.dirName());
    ui->calibDirName->setText(dir);

    try {
        //TODO: Here we assume a Stereo Image stream
        this->m_stream = std::shared_ptr<MSVRStream>(new MSVRStereoImage(dir.toStdString()));
        calibDataLoaded = true;
    } catch(const std::exception& e) {
        QMessageBox msgBox(this);
        msgBox.setText(QString(e.what()));
        msgBox.exec();
    }
}

void AddStereoImage::on_procStreamButton_clicked()
{
    if(leftImageLoaded && rightImageLoaded && calibDataLoaded) {
        //Process Left and Right images and create Color and Depth
        static_cast<MSVRStereoImage*>(m_stream.get())->process(
                    ui->leftStreamFileName->text().toStdString(),
                    ui->rightStreamFileName->text().toStdString() );

        //Show depth
        ui->depthPanel->showImage(m_stream->nextImage()
                                  .depth().nativeImage<cv::Mat>());

    } else {
        QMessageBox msgBox(this);
        msgBox.setText(tr("Must load necessary files first!"));
        msgBox.exec();
    }
}



