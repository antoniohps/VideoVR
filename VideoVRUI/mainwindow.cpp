#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "addstereoimage.h"
#include "matchnewstreamdialog.h"
#include "streamintegrationdialog.h"

#include "MSVRPinholeCamera.h"

#include <QFileDialog>

enum StreamType {
    STEREO_IMAGE = 0
};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_env(),
    m_camera(new msvr::MSVRPinholeCamera(1092.0,640,480))

{
    ui->setupUi(this);
    m_streamIterator = m_linkedStreams.begin();

    //Fill stream selector vector
    m_streamSelector["Stereo Image"] = QSharedPointer<QDialog>(new AddStereoImage(this));

    //Fill stream selector combo
    for(auto& key : m_streamSelector.keys()) {
        ui->streamTypeComboBox->addItem(key);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//TODO
void MainWindow::addStream(std::shared_ptr<msvr::MSVRStream> newStream)
{
    //1. Match new stream with previous ones
    //1.1 Launch dialog

    StreamIntegrationDialog* form = new StreamIntegrationDialog();
    form->exec();



    delete form;



    //1. Add to environment
    this->m_env.addStream(newStream);
    //2. Add to list
    m_streamIterator = this->m_linkedStreams.insert(m_linkedStreams.end(),newStream.get());

    //3. Refresh view
    refreshStreamView();

}

void MainWindow::on_add3dStreamButton_clicked()
{
    //Check what type of Color Depth stream is selected
    QString selection = ui->streamTypeComboBox->currentText();
    QDialog* form = m_streamSelector[selection].data();

    form->setModal(true);
    form->setAttribute( Qt::WA_DeleteOnClose, false ); //we don't want it to be deleted
    form->exec(); //instead of show
}

void MainWindow::on_actionLeft_Stream_triggered()
{
    QDir directory;

    QString path = QFileDialog::getOpenFileName(this,tr("Open Left Image"),directory.path(),tr("*.jpg"));
    if ( path.isNull() == false )
    {
        directory.setPath(path);
    }
}

void MainWindow::on_actionRight_Stream_triggered()
{
    QDir directory;

    QString path = QFileDialog::getExistingDirectory (this, tr("Directory"), directory.path());
    if ( path.isNull() == false )
    {
        directory.setPath(path);
    }
}

void MainWindow::refreshStreamView()
{
    //1. Check of current stream iterator is the first or the last
    //   and activate controls accordingly
    if(m_streamIterator == m_linkedStreams.begin()) {
        ui->prevStreamButton->setEnabled(false);
    } else {
        ui->prevStreamButton->setEnabled(true);
    }

    if(m_streamIterator == m_linkedStreams.end() || m_streamIterator == --m_linkedStreams.end()) {
        ui->nextStreamButton->setEnabled(false);
    } else {
        ui->nextStreamButton->setEnabled(true);
    }

    if(m_streamIterator != m_linkedStreams.end()) {

        //2. Display color image
        ui->colorWidget->showImage((*m_streamIterator)->nextImage().color());

        //3. Display depth image
        ui->depthWidget->showImage((*m_streamIterator)->nextImage().depth());

        //4. Display point cloud
        ip::Image img;
        m_env.showPoints(*this->m_camera,img);
        ui->pointCloudWidget->showImage(img);
    }



    ui->xLine->setText(QString::number(m_camera->x()));
    ui->yLine->setText(QString::number(m_camera->y()));
    ui->zLine->setText(QString::number(m_camera->z()));
    ui->psiLine->setText(QString::number(m_camera->psi()*180.0/3.1416));
    ui->phiLine->setText(QString::number(m_camera->phi()*180.0/3.1416));
    ui->thetaLine->setText(QString::number(m_camera->theta()*180.0/3.1416));

}

void MainWindow::on_prevStreamButton_clicked()
{
    if(m_streamIterator != m_linkedStreams.begin()) {
        m_streamIterator--;
    }
    refreshStreamView();
}

void MainWindow::on_nextStreamButton_clicked()
{
    if(m_streamIterator != m_linkedStreams.end()) {
        m_streamIterator++;
    }
    refreshStreamView();
}

void MainWindow::on_closerButton_clicked()
{
    m_camera->moveForth(20);
    refreshStreamView();
}

void MainWindow::on_furtherButton_clicked()
{
    m_camera->moveForth(-20);
    refreshStreamView();
}

void MainWindow::on_rollRightButton_clicked()
{
    m_camera->roll(5.0*3.141592/180);
    refreshStreamView();
}

void MainWindow::on_rollLeftButton_clicked()
{
    m_camera->roll(-5.0*3.141592/180);
    refreshStreamView();
}

void MainWindow::on_moveRightButton_clicked()
{
    m_camera->moveLeft(-20);
    refreshStreamView();
}

void MainWindow::on_moveLeftButton_clicked()
{
    m_camera->moveLeft(20);
    refreshStreamView();
}

void MainWindow::on_upButton_clicked()
{
    m_camera->moveUp(20);
    refreshStreamView();
}

void MainWindow::on_downButton_clicked()
{
    m_camera->moveUp(-20);
    refreshStreamView();

}

void MainWindow::on_turnLeftButton_clicked()
{
    m_camera->turnLeft(5.0*3.141592/180);
    refreshStreamView();
}

void MainWindow::on_turnRightButton_clicked()
{
    m_camera->turnLeft(-5.0*3.141592/180);
    refreshStreamView();
}

void MainWindow::on_turnUpButton_clicked()
{
    m_camera->turnUp(5.0*3.141592/180);
    refreshStreamView();
}

void MainWindow::on_turnDownButton_clicked()
{
    m_camera->turnUp(-5.0*3.141592/180);
    refreshStreamView();
}
