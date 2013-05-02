#include "QSummary.h"
#include <iostream>

using namespace std;

QSummary::QSummary(QWidget *parent) : QWidget(parent){}

void QSummary::add_summary(){}
void QSummary::find_summary(){}


void QSummary::setSummary(const string & sum)
{
    lsummary->setText(Easylast::stoqs(sum));
}

void QSummary::createWidget(QVBoxLayout *layout_main)
{
    QPushButton *valid = new QPushButton("Enter");    
    QLabel *label_summary = new QLabel("Summary :");
    
    lsummary = new QTextEdit;
//    lsummary->setFixedWidth(250);
    valid->setFixedWidth(100);
    
    connect(valid, SIGNAL(clicked()), this, SLOT(add_summary()));
    
    layout_main->addWidget(label_summary);
    layout_main->addWidget(lsummary);    
    layout_main->addWidget(valid,Qt::AlignLeft);    

    setLayout(layout_main);
}

void QSummary::displayBox(const string & msg)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Message");
    msgBox.setText(Easylast::stoqs(msg));
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.exec();
} 

bool QSummary::isNumber(const string & str) 
{
    return (atoi(str.c_str())); 
}

