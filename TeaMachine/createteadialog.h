#ifndef CREATETEADIALOG_H
#define CREATETEADIALOG_H

#include <QDialog>

namespace Ui {
class CreateTeaDialog;
}

class Tea;

class CreateTeaDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CreateTeaDialog(QWidget *parent = nullptr);
    ~CreateTeaDialog() override;

signals:
    void teaCreated(Tea *tea);

public slots:
    void accept() override;
    void dataCheck();

private:
    Ui::CreateTeaDialog *ui;
};

#endif // CREATETEADIALOG_H
