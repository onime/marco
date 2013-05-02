#include "LineNumPage.h"

LineNumPage::LineNumPage(QWidget *parent):QLineEdit(parent){}

void LineNumPage::focusInEvent(QFocusEvent *event)
{
    QWidget::focusInEvent(event);
    selectAll();

}

void LineNumPage::mousePressEvent( QMouseEvent * event )
{
    QWidget::mousePressEvent(event);
    selectAll();

}
