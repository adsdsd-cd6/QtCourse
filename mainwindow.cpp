#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnnum0,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnnum1,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnnum2,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnnum3,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnnum4,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnnum5,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnnum6,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnnum7,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnnum8,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnnum9,SIGNAL(clicked()),this,SLOT(btnNumClicked()));

    connect(ui->btnJia,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnJian,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnCheng,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnChu,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));

    connect(ui->btnPercentage,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnDao,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnErcifang,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnGen,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::calculation(bool *ok)
{
    double result=0;
    if(operands.size()==2 && opcodes.size()>0)
    {
        //取操作数
        double operand1 = operands.front().toDouble();
        operands.pop_front();
        double operand2 = operands.front().toDouble();
        operands.pop_front();

        //取操作符
        QString op = opcodes.front();
        opcodes.pop_front();

        if(op == "+")
        {
            result = operand1 + operand2;
        }
        else if(op == "-")
        {
            result = operand1 - operand2;
        }
        else if(op == "×")
        {
            result = operand1 * operand2;
        }
        else if(op == "/")
        {
            result = operand1 / operand2;
        }

        operands.push_back(QString::number(result));
    }
    return QString::number(result);
}

void MainWindow::btnNumClicked()
{
    QString digit = qobject_cast<QPushButton*>(sender())->text();

    if(digit=="0"&&operand=="0")
        digit="";

    if(operand=="0"&&digit!="0")
        operand="";

    operand += digit;

    ui->display->setText(operand);

}



void MainWindow::on_btnDian_clicked()
{
    if(!operand.contains("."))
        operand +=qobject_cast<QPushButton*>(sender())->text();
    ui->display->setText(operand);
}


void MainWindow::on_btnDel_clicked()
{
    operand=operand.left(operand.length()-1);
    ui->display->setText(operand);
}


void MainWindow::on_btnC_clicked()
{
    operand.clear();
    ui->display->setText(operand);
}

void MainWindow::btnBinaryOperatorClicked()
{
    QString opcode = qobject_cast<QPushButton*>(sender())->text();


    if(operand != "")
    {
        operands.push_back(operand);
        operand="";

        opcodes.push_back(opcode);
    }

    QString result = calculation();

    ui->display->setText(result);
}

void MainWindow::btnUnaryOperatorClicked()
{
    if(operand != "")
    {
        double result = operand.toDouble();
        operand="";

        QString op = qobject_cast<QPushButton*>(sender())->text();

        if(op == "%")
            result /= 100.0;
        else if(op == "1/x")
            result = 1/result;
        else if(op == "x^2")
            result = result * result;
        else if(op == "√")
            result = sqrt(result);

        ui->display->setText(QString::number(result));
    }
}

void MainWindow::on_btnDeng_clicked()
{
    if(operand != "")
    {
        operands.push_back(operand);
        operand="";
    }
    QString result = calculation();
    ui->display->setText(result);
}
//1
