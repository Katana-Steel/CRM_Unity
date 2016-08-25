#ifndef __stat_totsalg_data_h
#define __stat_totsalg_data_h

class SalgData
{
public:
    QString id;
    QString salg;
    QString bytte;
    QString total;
    void clear() {
        id.clear();
        salg.clear();
        bytte.clear();
        total.clear();
    };
};

class Salger 
{
public:
    SalgData name;
    QVector<SalgData> orders;
    void clear() {
        name.clear();
        orders.clear();
    };
};

#endif
