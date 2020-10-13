#ifndef QBITMAPBUTTON_H
#define QBITMAPBUTTON_H

#include <QObject>
#include <QPushButton>
class QBitmapButton : public QPushButton
{
    Q_OBJECT
private:
    QString normal, over, down;
public:
    QBitmapButton();
    QBitmapButton(QString normal, QString over, QString down);
    void setStyle(QString normal, QString over, QString down);
protected:
    bool event(QEvent * e);
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
};

#endif // QBITMAPBUTTON_H
