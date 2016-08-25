#include "k-j_data.h"
#include "tab_rma_mwin.h"

MWin::MWin(Conn*,QWidget*)
{
}

void MWin::log(const QString &str)
{
}

KData *
MWin::getCusData()
{
    return new KData;
}
