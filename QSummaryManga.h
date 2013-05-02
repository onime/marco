#ifndef Q_SUM_MANGA
#define Q_SUM_MANGA

#include "QSummary.h"

using namespace std;

class QSummaryManga : public QSummary
{
public:
    
    QSummaryManga(QWidget *parent=0);
    QSummaryManga(string manga,QWidget *parent=0);
    QSummaryManga(string manga,int chap,QWidget *parent=0);
    
    void setName(const string & name);
    void setChap(const int & chap);

protected:
    void add_summary();
    void find_summary();

private:

    QLineEdit *lscan;
    QLineEdit *lchap;

    QVBoxLayout* createLayoutScan();
    
};

#endif
