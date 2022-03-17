#include "calculator.h"
#include "ui_calculator.h"

double calcVal = 0.0;
double memVal =0.0;
bool divTrigger = false;
bool multTrigger = false;
bool subTrigger = false;
bool addTrigger = false;
bool dotTrigger = false;
bool eqTrigger = false;
Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for (int i=0; i<10; ++i){
        QString butName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);//SEARCH FOR WIDGET BY NAME
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
    connect(ui->Add, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Times, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Equals, SIGNAL(released()), this,
            SLOT(EqualButtonPressed()));
    connect(ui->ChangeSign, SIGNAL(released()), this,
            SLOT(ChangeNumberSign()));
    connect(ui->Clear, SIGNAL(released()), this,
            SLOT(ClearButtonPressed()));
    connect(ui->MemAdd, SIGNAL(released()), this,
            SLOT(MemoryButtonPressed()));
    connect(ui->MemClear, SIGNAL(released()), this,
            SLOT(MemoryButtonPressed()));
    connect(ui->MemGet, SIGNAL(released()), this,
            SLOT(MemoryButtonPressed()));
    connect(ui->Dot, SIGNAL(released()), this,
            SLOT(DotButtonPressed()));
    connect(ui->Square, SIGNAL(released()), this,
            SLOT(SquareButtonPressed()));
    connect(ui->Cube, SIGNAL(released()), this,
            SLOT(CubeButtonPressed()));
    connect(ui->SquareRoot, SIGNAL(released()), this,
            SLOT(SqrtButtonPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    if (eqTrigger==true){
        calcVal=0.0;
        ui->Display->setText(QString::number(calcVal));
        eqTrigger=false;
    }
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if (((displayVal.toDouble()==0)||((displayVal.toDouble()==0.0)))&&dotTrigger==false){
        ui->Display->setText(butVal);
    }
    else if (((displayVal.toDouble()==0)||((displayVal.toDouble()==0.0)))&&dotTrigger==true){
        displayVal.append(butVal);
        ui->Display->setText(displayVal);
    }
    else{
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal,'g',16));
    }
}


void Calculator::MathButtonPressed(){
    divTrigger=false;
    multTrigger=false;
    addTrigger=false;
    subTrigger=false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button ->text();
    if (QString::compare(butVal, "/", Qt::CaseInsensitive)==0){
        divTrigger = true;
    } else if (QString::compare(butVal, "*", Qt::CaseInsensitive)==0){
        multTrigger = true;
    } else if (QString::compare(butVal, "+", Qt::CaseInsensitive)==0){
        addTrigger = true;
    } else {
        subTrigger = true;
    }
    ui->Display->setText("");
}
void Calculator::EqualButtonPressed(){
    eqTrigger=false;
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if(addTrigger || subTrigger || multTrigger || divTrigger){
        if(addTrigger){
            solution = calcVal+dblDisplayVal;
        } else if(subTrigger){
            solution = calcVal-dblDisplayVal;
        } else  if(multTrigger){
            solution = calcVal*dblDisplayVal;
        } else {
            solution = calcVal/dblDisplayVal;
        }
    }
    eqTrigger = true;
    ui->Display->setText(QString::number(solution));
}
void Calculator::ChangeNumberSign(){
    QString displayVal = ui->Display->text();
    QRegularExpression reg("[-+]?[0-9.]*");
    QRegularExpressionMatch match = reg.match((displayVal));
    if(match.hasMatch()){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 *dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayValSign));
    }
}
void Calculator::MemoryButtonPressed(){

    //bool MemATrigger = false;
    //bool MemGTrigger = false;
    //bool MemCTrigger = false;

    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button ->text();
    if (QString::compare(butVal, "M+", Qt::CaseInsensitive)==0){
        //MemATrigger = true;
        memVal = dblDisplayVal;
        ui->Display->setText("");
    }else if (QString::compare(butVal, "M", Qt::CaseInsensitive)==0){
        //MemGTrigger = true;
        ui->Display->setText(QString::number(memVal));
    }else if(QString::compare(butVal, "M-", Qt::CaseInsensitive)==0){
        //MemCTrigger=true;
        memVal = 0.0;
    }

}
void Calculator::ClearButtonPressed(){
    calcVal=0.0;
    ui->Display->setText(QString::number(calcVal));
}
void Calculator::DotButtonPressed(){
    dotTrigger = false;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if(displayVal.contains(".")){}
    if(dblDisplayVal==0||dblDisplayVal==0.0){
        ui->Display->setText("0.");
        dotTrigger = true;
    }
    else{
        displayVal.append(".");
        ui->Display->setText(displayVal);
    }
}


void Calculator::SquareButtonPressed(){
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    double result = dblDisplayVal*dblDisplayVal;
    ui->Display->setText(QString::number(result));

}
void Calculator::CubeButtonPressed(){
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    double result = dblDisplayVal*dblDisplayVal*dblDisplayVal;
    ui->Display->setText(QString::number(result));

}
void Calculator::SqrtButtonPressed(){

    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    double result = sqrt(dblDisplayVal);
    ui->Display->setText(QString::number(result));
}
