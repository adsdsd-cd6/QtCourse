#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QDialog>
#include <QPlaintextedit>

namespace Ui {
class ReplaceDialog;
}

class ReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReplaceDialog(QWidget *parent = nullptr, QPlainTextEdit * textEdit = nullptr);
    ~ReplaceDialog();

private slots:
    void on_btnFindNex_clicked();

    void on_btnReplace_clicked();

    void on_btnReplaceAll_clicked();

    void on_btnCancel_clicked();

private:
    Ui::ReplaceDialog *ui;
    QPlainTextEdit * ptextEdit;
};

#endif // REPLACEDIALOG_H
