#ifndef STREAMINTEGRATIONDIALOG_H
#define STREAMINTEGRATIONDIALOG_H

#include <QDialog>

namespace Ui {
class StreamIntegrationDialog;
}

class StreamIntegrationDialog : public QDialog
{
    Q_OBJECT

public:

    enum MatchType {
        NOT_CHOSEN,
        CAMERA_AT_ORIGIN,
        FIXED_CAMERA,
        MATCH_NOW,
        MATCH_ALWAYS
    };


    explicit StreamIntegrationDialog(QWidget *parent = 0);
    ~StreamIntegrationDialog();

    MatchType matchType() const { return m_matchType; }

private:
    Ui::StreamIntegrationDialog *ui;
    MatchType m_matchType;
};

#endif // STREAMINTEGRATIONDIALOG_H
