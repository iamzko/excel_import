#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>

namespace Ui {
class HelpDialog;
}

class HelpDialog : public QDialog {
    Q_OBJECT

public:
    static HelpDialog* instance(QWidget* parent = nullptr);
    ~HelpDialog();

private:
    void set_help_info();
    static HelpDialog* help_handle;
    explicit HelpDialog(QWidget* parent = nullptr);
    Ui::HelpDialog* ui;
};

#endif // HELPDIALOG_H
