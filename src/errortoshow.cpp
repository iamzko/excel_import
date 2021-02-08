#include "errortoshow.h"

ErrorToShow::ErrorToShow(int row,
                         int col,
                         QString filed_name,
                         QString standard_format,
                         QString actual_content,
                         QString error_reason)
{
    error_content = std::make_tuple<QString,QString,QString,QString,QString,QString>(QString::number(row),QString::number(col),QString(filed_name),QString(standard_format),QString(actual_content),QString(error_reason));
}
