#ifndef Q_SUM
#define Q_SUM

#include <QMessageBox>
#include <QPushButton>
#include <QWidget>
#include <QObject>
#include <QLineEdit>
#include <QTextEdit>
#include <QSizePolicy>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "Easylast.h"

using namespace std;

class QSummary : public QWidget
{

Q_OBJECT

public:

QSummary(QWidget *parent = 0);
void setSummary(const string & sum);

protected slots:
virtual void add_summary();
virtual void find_summary();

protected:

QTextEdit *lsummary;

bool isNumber(const string & str);
void displayBox(const string & msg);

void createWidget(QVBoxLayout *layout_main);

};

#endif

