#ifndef SHEETMODELPRIVATE_H
#define SHEETMODELPRIVATE_H
#include "sheetmodel.h"

class SheetModelPrivate
{
    Q_DECLARE_PUBLIC(SheetModel)
public:
    SheetModelPrivate(SheetModel *p);
    QXlsx::Worksheet *sheet;
    SheetModel *q_ptr;
};

#endif // SHEETMODELPRIVATE_H
