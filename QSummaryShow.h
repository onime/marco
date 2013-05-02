#ifndef Q_SUM_SHOW
#define Q_SUM_SHOW

#include "QSummary.h"

using namespace std;

class QSummaryShow : public QSummary
{
public:
    
    QSummaryShow(QWidget *parent=0);
    QSummaryShow(string show,QWidget *parent=0);
    QSummaryShow(string show,int season,int episode,QWidget *parent=0);

protected:
    void add_summary();

private:
    string name;
    int season;
    int episode;

    QLineEdit *lshow;
    QLineEdit *lepisode;
    QLineEdit *lseason;

    QVBoxLayout* createLayoutShow();
    
};

#endif
