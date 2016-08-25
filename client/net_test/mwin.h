#include <QWidget>
#include <QTextStream>

class Conn;
class QNetworkReply;
class QVBoxLayout;
class QProgressBar;

class MWin : public QWidget
{
    Q_OBJECT
public:
    MWin(QWidget *parent=0);
public slots:
    void show();
    void setVisible(bool);
private slots:
    void done();
    void ready(QNetworkReply*);
    void updateBar(qint64 v, qint64 t);
    void readNet();
    void sslErr();
    void err();
private:
    QTextStream cout;
    QVBoxLayout *lay;
    QProgressBar *pgb;
    QNetworkReply* reply;
    Conn *conn;
};
