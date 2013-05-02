#ifndef MARCO
#define MARCO

#include <iostream>
#include <QWidget>
#include <QString>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <QList>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QRadioButton>
#include <map>
#include "QSummary.h"
#include "QSummaryManga.h"
#include "QSummaryShow.h"
#include "Qtviewer.h"
#include "Easylast.h"



using namespace std;

class Marco : public QWidget
{

Q_OBJECT

public:
Marco(QWidget *parent = 0);


protected slots:

void set_new_scan(string scan_cur,int num_cur);
void simple_clicked_shows();
void simple_clicked_scans();
void double_clicked_shows(int row,int column);
void double_clicked_scans(int row,int column);

private:
map<string,string> infos_vu;
map<string,string> infos_dl;

QRadioButton *button_circular;
QRadioButton *button_normal;
QTableWidget *table_infos_scans;
QTableWidget *table_infos_shows;
Qtviewer *viewer;
QSummary *summary;
QSummaryManga *sum_manga;
QSummaryShow *sum_show;

void fill_table(map<string,string> infos);
};

#endif
