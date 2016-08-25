#ifndef __RKTreeWidget_h
#define __RKTreeWidget_h 1

#include <QTreeWidget>
#include <QList>

class RKTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    RKTreeWidget(QWidget *parent=0);

    QList<QTreeWidgetItem *> getTopLevelItems();
};
#endif
