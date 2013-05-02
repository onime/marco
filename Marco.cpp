#include "Marco.h"
#include "Easylast.h"
#include "QSummaryManga.h"
#include "Qtviewer.h"

Marco::Marco(QWidget *parent)
{
    QHBoxLayout *layout_main = new QHBoxLayout;
    QVBoxLayout *layout_infos = new QVBoxLayout;
    QList<QString> header ;

    header << "Name" << "Next" << "Status";

    table_infos_scans = new QTableWidget(0,3);
    table_infos_shows = new QTableWidget(0,3);

    QSummaryManga *sum_manga = new QSummaryManga;
    viewer = new Qtviewer("Bleach",98);

    map<string,string> infos = Easylast::parse_info("VU");
   
    table_infos_scans->setHorizontalHeaderLabels(QStringList(header));
    table_infos_scans->verticalHeader()->hide();
    
    table_infos_scans->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_infos_scans->setSelectionMode(QAbstractItemView::SingleSelection);
    table_infos_scans->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table_infos_shows->setHorizontalHeaderLabels(QStringList(header));
    table_infos_shows->verticalHeader()->hide();
    
    table_infos_shows->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_infos_shows->setSelectionMode(QAbstractItemView::SingleSelection);
    table_infos_shows->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    connect(table_infos_scans, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(double_clicked_scans(int,int)));
    connect(table_infos_shows, SIGNAL(cellClicked(int,int)), this, SLOT(simple_clicked_shows()));
    connect(table_infos_scans, SIGNAL(cellClicked(int,int)), this, SLOT(simple_clicked_scans()));

    fill_table(infos);
    
    layout_infos->addWidget(table_infos_shows);
    layout_infos->addWidget(table_infos_scans);
    layout_infos->addWidget(sum_manga);
    layout_main->addItem(layout_infos);
    layout_main->addWidget(viewer);

    setLayout(layout_main);
    
}
	    
void Marco::fill_table(map<string,string> infos)
{
    int c_scan = 0,c_show = 0;
    string name,info;
	    
    for(map<string,string>::iterator i=infos.begin();i!=infos.end();i++)
    {
	name = i->first;
	info = i->second;
	if(info[0] == 'S')
	{
	    table_infos_shows->insertRow(c_show);
	    table_infos_shows->setItem(c_show,0,new QTableWidgetItem(Easylast::stoqs(name)));
	    table_infos_shows->setItem(c_show,1,new QTableWidgetItem(Easylast::stoqs(info)));
	    c_show++;
	}
	else
	{
	    table_infos_scans->insertRow(c_scan);
	    table_infos_scans->setItem(c_scan,0,new QTableWidgetItem(Easylast::stoqs(name)));
	    table_infos_scans->setItem(c_scan,1,new QTableWidgetItem(Easylast::stoqs(info)));
	    c_scan++;
	}
	
    }
}

void Marco::simple_clicked_shows()
{
    table_infos_scans->selectionModel()->clear();
}

void Marco::simple_clicked_scans()
{
    table_infos_shows->selectionModel()->clear();
}

void Marco::double_clicked_shows(int row,int column)
{
    cout << table_infos_shows->item(row,0)->text().toStdString() <<endl;
}

void Marco::double_clicked_scans(int row,int column)
{
    
}
