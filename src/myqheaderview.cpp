#include "myqheaderview.h"
#include <QDebug>
MyQHeaderView::MyQHeaderView(Qt::Orientation orientation, QWidget *parent):QHeaderView::QHeaderView(orientation,parent)
{
//    connect(this, SIGNAL(sectionResized(int, int, int)), this,

//            SLOT(handleSectionResized(int)));

//    connect(this, SIGNAL(sectionMoved(int, int, int)), this,

//            SLOT(handleSectionMoved(int, int, int)));
}

//void MyQHeaderView::handleSectionResized(int i)
//{
//    for(int j = visualIndex(i);j < count();++j)
//    {
//        int logical = logicalIndex(j);
//        m_checkboxs[logical]->setGeometry(sectionViewportPosition(logical),0,sectionSize(logical),height());
//    }
//}

//void MyQHeaderView::handleSectionMoved(int logical, int oldVisualIndex, int newVisualIndex)
//{
//    for(int i = qMin(oldVisualIndex,newVisualIndex);i < count(); ++i)
//    {
//        int logical = logicalIndex(i);
//        m_checkboxs[logical]->setGeometry(sectionViewportPosition(logical),0,sectionSize(logical),height());
//    }
//}

void MyQHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->save();
    QHeaderView::paintSection(painter,rect,logicalIndex);
    QStyleOptionButton option;
//    if(logicalIndex == 0)
//    {
        //option.rect = QRect(10,10,10,10);
        if(m_check_box_states.count(logicalIndex))
        {
            if(m_check_box_states[logicalIndex])
            {
                option.state = QStyle::State_On;
            }
            else
            {
                option.state = QStyle::State_Off;
            }
        }
        else
        {
            option.state = QStyle::State_Off;
        }
        option.rect = rect;
        option.rect.setLeft(rect.x()+10);

//        if(isOn)
//        {
//            option.state = QStyle::State_On;
//        }
//        else
//        {
//            option.state = QStyle::State_Off;
//        }
//        this->style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option,painter);
        style()->drawControl(QStyle::CE_CheckBox,&option,painter);

//    }
    painter->restore();

}

void MyQHeaderView::mousePressEvent(QMouseEvent *event)
{
    auto index = this->logicalIndexAt(event->pos().x(),event->pos().y());
    qDebug() << "press:" << index;
    if(m_check_box_states[index])
    {
        m_check_box_states[index] = false;
    }
    else
    {
        m_check_box_states[index] = true;
    }
    emit select_index(index);
    updateSection(index);

    QHeaderView::mousePressEvent(event);
}


bool MyQHeaderView::getState(int index)
{
    if(index >= 0)
    {
        return m_check_box_states[index];
    }
    return false;
}

bool MyQHeaderView::SetState(int index, bool state)
{
    if(index >= 0)
    {
        m_check_box_states.insert(index,state);
    }
    return m_check_box_states.contains(index);
}

QVector<int> MyQHeaderView::getAllSelected()
{
    QVector<int> result;
    for(auto it =m_check_box_states.begin();it != m_check_box_states.end(); ++it)
    {
        if(it.value())
        {
            result.push_back(it.key());
        }
    }
    return result;
}

QVector<int> MyQHeaderView::getAllNotSlected()
{
    QVector<int> result;
    for(auto it =m_check_box_states.begin();it != m_check_box_states.end(); ++it)
    {
        if(!it.value())
        {
            result.push_back(it.key());
        }
    }
    return result;

}

void MyQHeaderView::setAllSlected()
{
    setAllState(true);
}

void MyQHeaderView::setAllNotSlected()
{
    setAllState(false);
}

void MyQHeaderView::clearAllStates()
{
    m_check_box_states.clear();
}

void MyQHeaderView::setAllState(bool state)
{
    if(m_check_box_states.size() != count())
    {
        clearAllStates();
        for(int i = 0; i < count(); ++i)
        {
            m_check_box_states[i] = state;
        }
    }
    else
    {
        QMutableMapIterator<int,bool> it(m_check_box_states);
        while (it.hasNext())
        {
            it.next();
            it.setValue(state);
        }

    }
    for(int i = 0; i < count();++i)
    {
        updateSection(i);
    }

}

void MyQHeaderView::on_process_row_state(int row)
{
    if(row>=0)
    {
        if(m_check_box_states[row])
        {
            m_check_box_states[row] = false;
        }
        else
        {
            m_check_box_states[row] = true;
        }
        updateSection(row);


    }
}

void MyQHeaderView::showEvent(QShowEvent *event)
{
    QHeaderView::showEvent(event);
}

