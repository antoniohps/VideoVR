#ifndef ADDCOLORDEPTHIMAGE_H
#define ADDCOLORDEPTHIMAGE_H

#include <QDialog>

namespace Ui {
class AddColorDepthImage;
}

class AddColorDepthImage : public QDialog
{
    Q_OBJECT

public:
    explicit AddColorDepthImage(QWidget *parent = 0);
    ~AddColorDepthImage();

private:
    Ui::AddColorDepthImage *ui;
};

#endif // ADDCOLORDEPTHIMAGE_H
