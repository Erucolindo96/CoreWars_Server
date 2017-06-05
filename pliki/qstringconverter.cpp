#include "qstringconverter.hpp"


std::string QStringConverter::convertQString(QString str)
{
    QByteArray array = str.toAscii();
    return std::string(array.data());

}
