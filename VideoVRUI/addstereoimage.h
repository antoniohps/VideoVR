#ifndef ADDCOLORDEPTHIMAGE_H
#define ADDCOLORDEPTHIMAGE_H

#include "mainwindow.h"
#include "MultiStreamVREnvironment.h"
#include "StereoDepth.h"


#include <QDialog>

#include <memory>

namespace Ui {
class AddStereoImage;
}

class AddStereoImage : public QDialog
{
    Q_OBJECT

public:
    explicit AddStereoImage(MainWindow *parent = 0);
    ~AddStereoImage();

private:

    bool leftImageLoaded;
    bool rightImageLoaded;
    bool calibDataLoaded;

    Ui::AddStereoImage *ui;
    MainWindow* parent;
    std::shared_ptr<msvr::MSVRStream> m_stream;

private slots:
    void on_openLeftStreamButton_clicked();
    void on_openRightStreamButton_clicked();
    void on_buttonBox_accepted();
    void on_procStreamButton_clicked();
    void on_openCalibDirButton_clicked();
};

#endif // ADDCOLORDEPTHIMAGE_H
