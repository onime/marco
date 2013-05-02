#ifndef LINE_PAGE
#define LINE_PAGE

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QFocusEvent>
#include <iostream>
#include <QMouseEvent>

using namespace std;

class LineNumPage : public QLineEdit
{
Q_OBJECT

public:
LineNumPage(QWidget *parent = NULL);

protected:
void mousePressEvent( QMouseEvent * event );
void focusInEvent(QFocusEvent *event);
};

#endif
