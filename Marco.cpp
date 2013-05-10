#include "Marco.h"


Marco::Marco(QWidget *parent)
{

    QHBoxLayout *layout_main = new QHBoxLayout;
    QVBoxLayout *layout_infos = new QVBoxLayout;
    
    QList<QString> header ;
    
    sum_manga = new QSummaryManga;
    sum_show = new QSummaryShow;
    
    header << "Name" << "Last" << "Next";

    table_infos_scans = new QTableWidget(0,3);
    table_infos_shows = new QTableWidget(0,3);       

    infos_vu = Easylast::parse_info("VU");
    infos_dl = Easylast::parse_info("DL");

    viewer = new Qtviewer;
    
    //viewer = new Qtviewer("Bleach",Easylast::stoi(infos_vu["Bleach"]));
    viewer->setQSummary(sum_manga);
    QSizePolicy sizePol(QSizePolicy::Expanding,QSizePolicy::Expanding);
    viewer->setSizePolicy(sizePol);
    
    table_infos_scans->setHorizontalHeaderLabels(QStringList(header));
    table_infos_scans->verticalHeader()->hide();
    
    table_infos_scans->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_infos_scans->setSelectionMode(QAbstractItemView::SingleSelection);
    table_infos_scans->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QSize size_table(table_infos_scans->sizeHint());

    table_infos_scans->setMinimumSize(QSize(size_table.width()+48,size_table.height()));
    table_infos_scans->setMaximumSize(QSize(size_table.width()+48,size_table.height()));

    size_table = table_infos_shows->sizeHint();
    table_infos_shows->setMinimumSize(QSize(size_table.width()+48,size_table.height()));
    table_infos_shows->setMaximumSize(QSize(size_table.width()+48,size_table.height()));

    table_infos_shows->setHorizontalHeaderLabels(QStringList(header));
    table_infos_shows->verticalHeader()->hide();

    table_infos_shows->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_infos_shows->setSelectionMode(QAbstractItemView::SingleSelection);
    table_infos_shows->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(table_infos_scans, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(double_clicked_scans(int,int)));
    connect(table_infos_shows, SIGNAL(cellClicked(int,int)), this, SLOT(simple_clicked_shows()));
    connect(table_infos_scans, SIGNAL(cellClicked(int,int)), this, SLOT(simple_clicked_scans()));
    connect(viewer, SIGNAL(nextScan(string,int)), this, SLOT(set_new_scan(string,int)));

    fill_table(infos_vu);
   
    layout_infos->addWidget(table_infos_shows,1);
    layout_infos->addWidget(table_infos_scans,1);
   
    layout_infos->addWidget(sum_manga);

    layout_main->addLayout(layout_infos);
    // Le stretch est pour que le viewer utilise tout l'espace
    layout_main->addWidget(viewer,1);

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

	    set_row_scan(c_scan,name,Easylast::stoi(info));
	    c_scan++;
	}
    }	
}

void Marco::set_row_scan(int row,string name_scan,int num_scan)
{
    table_infos_scans->setItem(row,1,new QTableWidgetItem(Easylast::itoqs(num_scan)));
    
    if(num_scan+1 <= Easylast::stoi(infos_dl[name_scan]))
	table_infos_scans->setItem(row,2,new QTableWidgetItem(Easylast::itoqs(num_scan+1)+" Ready"));
    else
	table_infos_scans->setItem(row,2,new QTableWidgetItem(Easylast::itoqs(num_scan+1)+" Not Ready"));
}

void Marco::set_new_scan(string scan_cur,int num_cur)
{
    string cmd = "client_last --VU --inc -t "+scan_cur;
    int row_count = table_infos_scans->rowCount();
              
    sum_manga->setName(scan_cur);
    sum_manga->setChap(num_cur);

    summary = sum_manga;

    if(num_cur > Easylast::stoi(infos_vu[scan_cur]))
    {
	for(int i = 0;i<table_infos_scans->rowCount();i++)
	    
	    if(table_infos_scans->item(i,0)->text().toStdString() == scan_cur)
		set_row_scan(i,scan_cur,num_cur);

        system(cmd.c_str());
    }

    if(num_cur < Easylast::stoi(infos_dl[scan_cur]))	
	viewer->setScan(scan_cur,num_cur+1);
    else
    {	   
	int curr_row = table_infos_scans->currentRow();
	if(curr_row < row_count)
	{
	    string new_name = table_infos_scans->item(curr_row+1,0)->text().toStdString();
	    int new_num = Easylast::stoi(table_infos_scans->item(curr_row+1,1)->text().toStdString());
	    table_infos_scans->setCurrentCell(curr_row+1,0);
	    viewer->setScan(new_name,new_num);
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
}

void Marco::double_clicked_scans(int row,int column)
{
    string name = table_infos_scans->item(row,0)->text().toStdString();
    int num = atoi(table_infos_scans->item(row,1)->text().toStdString().c_str());
    viewer->setScan(name,num);
}
