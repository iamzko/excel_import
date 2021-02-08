#ifndef SHEETMODEL_H
#define SHEETMODEL_H
#include <QAbstractTableModel>
#include "xlsxglobal.h"
#include "xlsxworksheet.h"


class Worksheet;
class SheetModelPrivate;

class SheetModel:public QAbstractTableModel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(SheetModel)
public:
    explicit SheetModel(QXlsx::Worksheet *sheet, QObject *parent = 0);
    ~SheetModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QXlsx::Worksheet *sheet() const;
private:
    SheetModelPrivate *const d_ptr;
};

#endif // SHEETMODEL_H
