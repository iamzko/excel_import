#ifndef ERRORTOSHOW_H
#define ERRORTOSHOW_H
#include <tuple>
#include <QString>


class ErrorToShow
{
public:
    ErrorToShow(int row, int col, QString filed_name, QString standard_format, QString actual_content,QString error_reaseon);
    std::tuple<QString,QString,QString,QString,QString,QString> get_error_content() const
    {
        return error_content;
    }
private:
    std::tuple<QString,QString,QString,QString,QString,QString> error_content;
};

#endif // ERRORTOSHOW_H
