#ifndef QT_VIEWER
#define QT_VIEWER

#define PATH_SCANS "/media/Data/Scans/"

#include <iostream>
#include <string>
#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QScrollArea>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QFocusEvent>
#include <QCloseEvent>
#include "LineNumPage.h"
#include "QSummaryManga.h"
#include "Easylast.h"

using namespace std;

class Qtviewer : public QWidget
{

Q_OBJECT

public:

Qtviewer(string name_scan,int num_page,QWidget *parent = NULL);
void setQSummary(QSummaryManga *sum);

protected:

//method reimplemented

void closeEvent(QCloseEvent *event);
void keyPressEvent(QKeyEvent * event);
void resizeEvent(QResizeEvent * event);

public slots:

void go_next_page();
void go_prev_page();
void go_first_page();
void go_last_page();
void go_to_page();

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
QLabel *image_current;

QSummaryManga *SummManga;
//method

void new_scan();
void display_image(const string & path_img);
void display_image_curr();
void update_label();

};


#endif
