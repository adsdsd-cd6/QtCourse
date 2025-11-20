#include "replacedialog.h"
#include "ui_replacedialog.h"
#include "QMessageBox"

ReplaceDialog::ReplaceDialog(QWidget *parent, QPlainTextEdit * textEdit)
    : QDialog(parent)
    , ui(new Ui::ReplaceDialog)
{
    ui->setupUi(this);
    ptextEdit = textEdit;
    ui->rbDown->setChecked(true);
}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}

void ReplaceDialog::on_btnFindNex_clicked()
{
    QString target = ui->searchText->text();

    if(target == "" || ptextEdit == nullptr){
        return;
    }

    QString text = ptextEdit->toPlainText();
    QTextCursor c = ptextEdit->textCursor();
    int index = -1;

    if(ui->rbDown->isChecked()){

        index = text.indexOf(target,c.position(), ui->ubCaseSensetive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if(index >= 0){
            c.setPosition(index);
            c.setPosition(index +target.length() , QTextCursor::KeepAnchor);

            ptextEdit->setTextCursor(c);
        }
    }
    else if(ui->rbUp->isChecked()){
        index = text.lastIndexOf(target, c.position()- text.length() - 1,
                                 ui->ubCaseSensetive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if(index >= 0){
            c.setPosition(index +target.length());
            c.setPosition(index, QTextCursor::KeepAnchor);

            ptextEdit->setTextCursor(c);
        }
    }

    if(index < 0){
        QMessageBox msg(this);
        msg.setWindowTitle("记事本");
        msg.setText("找不到 "+target);
        msg.setWindowFlags(Qt::Drawer);
        msg.setIcon(QMessageBox::Information);
        msg.setStandardButtons(QMessageBox::Ok);
        msg.exec();
    }
}


void ReplaceDialog::on_btnReplace_clicked()
{
    QString target = ui->searchText->text();
    QString to = ui->ReplaceEdit->text();

    if((ptextEdit !=nullptr)&&(target !="")&&(to!="")){
        QString selText = ptextEdit->textCursor().selectedText();

        if(selText == target){
            ptextEdit->insertPlainText(to);
        }
        on_btnFindNex_clicked();
    }

}


void ReplaceDialog::on_btnReplaceAll_clicked()
{
    QString target = ui->searchText->text();
    QString to = ui->ReplaceEdit->text();

    if((ptextEdit !=nullptr)&&(target !="")&&(to!="")){
        QString text = ptextEdit->toPlainText();

        text.replace(target, to, ui->ubCaseSensetive->isChecked() ? Qt::CaseSensitive :
                                     Qt::CaseInsensitive);

        ptextEdit->clear();

        ptextEdit->insertPlainText(text);
    }
}


void ReplaceDialog::on_btnCancel_clicked()
{
    accept();
}

