#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QMap>

#include "matchnewstreamdialog.h"

#include "MultiStreamVREnvironment.h"

#include "opencv2/opencv.hpp"

#include <list>
#include <map>
#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Q_PROPERTY(const msvr::MultiStreamVREnvironment& environment READ environment)

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    ///Add a new 3D stream
    void addStream(std::shared_ptr<msvr::MSVRStream> newStream);

    ///Returns the reference to the environment
    const msvr::MultiStreamVREnvironment& environment() const
    {
        return m_env;
    }

private:
    Ui::MainWindow *ui;
    QMap<QString,QSharedPointer<QDialog> > m_streamSelector;
    QSharedPointer<MatchNewStreamDialog> m_matchNewStreamDialogPtr;

    msvr::MultiStreamVREnvironment m_env;
    std::list<msvr::MSVRStream* > m_linkedStreams;
    std::list<msvr::MSVRStream* >::iterator m_streamIterator;
    std::unique_ptr<msvr::MSVRCamera> m_camera;

private slots:
    void on_actionLeft_Stream_triggered();
    void on_actionRight_Stream_triggered();
    void refreshStreamView();
    void on_add3dStreamButton_clicked();
    void on_prevStreamButton_clicked();
    void on_nextStreamButton_clicked();
    void on_closerButton_clicked();
    void on_furtherButton_clicked();
    void on_rollRightButton_clicked();
    void on_rollLeftButton_clicked();
    void on_moveRightButton_clicked();
    void on_moveLeftButton_clicked();
    void on_upButton_clicked();
    void on_downButton_clicked();
    void on_turnLeftButton_clicked();
    void on_turnRightButton_clicked();
    void on_turnUpButton_clicked();
    void on_turnDownButton_clicked();
};

#endif // MAINWINDOW_H
