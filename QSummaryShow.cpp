#include "QSummaryShow.h"

QSummaryShow::QSummaryShow(QWidget *parent) : QSummary(parent)
{
    createWidget(createLayoutShow());
}

QSummaryShow::QSummaryShow(string pname,QWidget *parent)  : QSummary(parent)
{   
    createWidget(createLayoutShow());
    lshow->setText(Easylast::stoqs(pname));

}

QSummaryShow::QSummaryShow(string pname,int pseason,int pepisode,QWidget *parent)  : QSummary(parent)
{
    createWidget(createLayoutShow());
    lshow->setText(Easylast::stoqs(pname));
    lseason->setText(Easylast::stoqs(Easylast::itos(pseason)));
    lepisode->setText(Easylast::stoqs(Easylast::itos(pepisode)));
}

QVBoxLayout* QSummaryShow::createLayoutShow()
{

    QHBoxLayout *layout_name = new QHBoxLayout;
    QHBoxLayout *layout_season = new QHBoxLayout;
    QHBoxLayout *layout_episode = new QHBoxLayout;
    QVBoxLayout *layout_main = new QVBoxLayout;

    QLabel * label_show = new QLabel("Show :");
    QLabel * label_season = new QLabel("Season :");
    QLabel * label_episode = new QLabel("Episode :");
   
    QSizePolicy policy_edit(QSizePolicy::Maximum,QSizePolicy::Maximum);

    lshow = new QLineEdit;
    lseason = new QLineEdit;
    lepisode = new QLineEdit;
   
    label_season->setFixedWidth(60);
    label_episode->setFixedWidth(60);
    label_show->setFixedWidth(60);
    label_show->setMargin(0);
    label_season->setMargin(0);
    label_episode->setMargin(0);
           
    lshow->setSizePolicy(policy_edit);
    lshow->setMaximumWidth(200);

    lseason->setSizePolicy(policy_edit);
    lseason->setMaxLength(3);
    lseason->setMaximumWidth(40);
   
    lepisode->setSizePolicy(policy_edit);
    lepisode->setMaxLength(3);
    lepisode->setMaximumWidth(40);

    layout_name->addWidget(label_show,Qt::AlignLeft);
    layout_name->addWidget(lshow,Qt::AlignLeft);
    layout_name->addStretch();

    layout_season->addWidget(label_season,Qt::AlignLeft);
    layout_season->addWidget(lseason,Qt::AlignLeft);
    layout_season->addStretch();

    layout_episode->addWidget(label_episode,Qt::AlignLeft);
    layout_episode->addWidget(lepisode,Qt::AlignLeft);
    layout_episode->addStretch();

    layout_main->addLayout(layout_name);
    layout_main->addLayout(layout_season);
    layout_main->addLayout(layout_episode);
    
    return layout_main;
}

void QSummaryShow::add_summary()
{
    string textShow = lshow->text().toStdString();
    string textSea = lseason->text().toStdString();
    string textEp = lepisode->text().toStdString();
    string textSumm = lsummary->toPlainText().toStdString();


    if( textSea != "" && textEp !="" &&  textSumm != "" && textShow != "")
    {
	if( isNumber(textEp) && isNumber(textSea))
	{
	    string cmd = "client_last --as -t \""+textShow+"\" -n "+textSea+"x"+textEp+" -s \""+textSumm+"\"";
	    if(system(cmd.c_str()) == 0)
	    {
	    	displayBox("Summary added");
		lsummary->setText("");
	    }
	}
	else
	    displayBox("Season or Episode is not a number");
    }
    else
	displayBox("A text is empty");
}
