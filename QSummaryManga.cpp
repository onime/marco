#include "QSummaryManga.h"

QSummaryManga::QSummaryManga(QWidget *parent) : QSummary(parent)
{
    createWidget(createLayoutScan());
}

QSummaryManga::QSummaryManga(string name,QWidget *parent)  : QSummary(parent)
{
    createWidget(createLayoutScan());
    lscan->setText(Easylast::stoqs(name));
}

QSummaryManga::QSummaryManga(string name,int chap,QWidget *parent)  : QSummary(parent)
{
    createWidget(createLayoutScan());
    lscan->setText(Easylast::stoqs(name));
    lchap->setText(Easylast::stoqs(Easylast::itos(chap)));
    
    find_summary();
}

void QSummaryManga::setName(const string & name)
{
    lscan->setText(Easylast::stoqs(name));
}

void QSummaryManga::setChap(const int & chap)
{
    lchap->setText(Easylast::stoqs(Easylast::itos(chap)));
    find_summary();
}

QVBoxLayout* QSummaryManga::createLayoutScan()
{
    QHBoxLayout *layout_name = new QHBoxLayout;
    QHBoxLayout *layout_chap = new QHBoxLayout;
    QVBoxLayout *layout_main = new QVBoxLayout;

    QLabel * label_scan = new QLabel("Scan :");
    QLabel * label_chap = new QLabel("Chap :");

    QSizePolicy policy_edit(QSizePolicy::Maximum,QSizePolicy::Maximum);

    lscan = new QLineEdit;
    lchap = new QLineEdit;

    connect(lscan,SIGNAL(returnPressed()),this,SLOT(find_summary()));
    connect(lchap,SIGNAL(returnPressed()),this,SLOT(find_summary()));

    label_chap->setFixedWidth(60);
    label_scan->setFixedWidth(60);
    label_scan->setMargin(0);
    label_chap->setMargin(0);
              
    lscan->setSizePolicy(policy_edit);
    lscan->setMaximumWidth(200);

    lchap->setSizePolicy(policy_edit);
    lchap->setMaxLength(3);
    lchap->setMaximumWidth(40);

    layout_name->addWidget(label_scan,Qt::AlignLeft);
    layout_name->addWidget(lscan,Qt::AlignLeft);
    layout_name->addStretch();

    layout_chap->addWidget(label_chap,Qt::AlignLeft);
    layout_chap->addWidget(lchap,Qt::AlignLeft);
    layout_chap->addStretch();

    layout_main->addLayout(layout_name);
    layout_main->addLayout(layout_chap);

    return layout_main;
}

void QSummaryManga::find_summary()
{
    string summ = Easylast::find_summary(lscan->text().toStdString(),atoi(lchap->text().toStdString().c_str()));
    cout << summ <<endl;
    lsummary->setText(Easylast::stoqs(summ));

}

void QSummaryManga::add_summary()
{
    string textScan = lscan->text().toStdString();
    string textChap = lchap->text().toStdString();
    string textSumm = lsummary->toPlainText().toStdString();
    string cmd;

    if( textScan!= "" && textChap !="" &&  textSumm != "")
    {
	if( isNumber(textChap))
	{
	    cout << textSumm<<endl;
	    if(Easylast::find_summary(textScan,atoi(textChap.c_str())) == "" )
		cmd = "client_last --as -t \""+textScan+"\" -n "+textChap+" -s \""+textSumm+"\"";
	    else
		cmd = "client_last --us -t \""+textScan+"\" -n "+textChap+" -s \""+textSumm+"\"";
	    

	    if(system(cmd.c_str()) == 0)
	    {
	    	displayBox("Summary added");
		lsummary->setText("");
		lchap->setText("");
	    }
	}
	else
	    displayBox("Chap not a number");
    }
    else
	displayBox("A text is empty");
}
