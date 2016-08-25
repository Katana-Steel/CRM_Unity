#include <qglobal.h>
#include "RKTreeWidget.h"

RKTreeWidget::RKTreeWidget(QWidget *parent)
    : QTreeWidget(parent)
{}

QList<QTreeWidgetItem*>
RKTreeWidget::getTopLevelItems()
{
    int tli = this->topLevelItemCount();

    QList<QTreeWidgetItem*> items;
    for(int i = 0; i < tli; i++)
        items.append(this->topLevelItem(i));
    return items;
}
