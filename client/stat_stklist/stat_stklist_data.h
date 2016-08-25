#ifndef __stat_stklist_data_h
#define __stat_stklist_data_h 1
#include <QString>

struct ItemData {
    QString stk;
    QString vnr;
    QString vtxt;
    void clear() {
        stk.clear();
        vnr.clear();
        vtxt.clear();
    };
};

#endif
