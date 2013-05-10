#ifndef QT_VIEWER
#define QT_VIEWER

#define PATH_SCANS "/media/Data/Scans/"

#include <iostream>
#include <string>
#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QScrollArea>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QFocusEvent>
#include <QCloseEvent>
#include <QListWidget>
#include <QListWidgetItem>
#include "LineNumPage.h"
#include "QSummaryManga.h"
#include "Easylast.h"

using namespace std;

class Qtviewer : public QWidget
{

Q_OBJECT

public:

Qtviewer(QWidget *parent = NULL);
Qtviewer(string name_scan,int num_page,QWidget *parent = NULL);
void setQSummary(QSummaryManga *sum);
void setScan(string name,int num);

protected:
//method reimplemented

void keyPressEvent(QKeyEvent * event);
void resizeEvent(QResizeEvent * event);

signals:
void nextScan(string name_cur,int chap_cur);


public slots:

void btn_next_page();
void btn_prev_page();
void btn_first_page();
void btn_last_page();
void txt_go_page();
void list_go_scan();
void list_go_page();

private:

//attribute
string path_scan;
string name_scan;
int num_scan;
int curr_page;
int nb_page;
vector<string> pages_scan;

int height_for_img;
int width_for_img;

LineNumPage *num_page;
QLineEdit *ql_num_scan;
QLabel *image_current;
QLabel *label_cur_scan;
QListWidget *list_dir_scan;
QListWidget *list_dir_page;
QSummaryManga *SummManga;
//method

void clear_lists();
void fill_list_page();
void fill_lists();
void display_image(const string & path_img);
void display_image_curr();
void update_label();

};


#endif
