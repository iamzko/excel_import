#ifndef MYQHEADERVIEW_H
#define MYQHEADERVIEW_H

#include <QHeaderView>
#include <QPainter>
#include <QMouseEvent>
#include <QMap>
#include <QVector>


class MyQHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    MyQHeaderView(Qt::Orientation orientation, QWidget *parent = nullptr);
    bool getState(int index);
    bool SetState(int index,bool state);
    QVector<int> getAllSelected();
    QVector<int> getAllNotSlected();
    void setAllSlected();
    void setAllNotSlected();
    void clearAllStates();
private:
    void setAllState(bool state);


signals:
    void select_index(int row);
public slots:
    void on_process_row_state(int row);
protected:
    void paintSection(QPainter *painter,const QRect &rect, int logicalIndex) const;
    void mousePressEvent(QMouseEvent *event);
    void showEvent(QShowEvent *event);
private:
    QMap<int,bool> m_check_box_states;
    bool isOn;
};

#endif // MYQHEADERVIEW_H
