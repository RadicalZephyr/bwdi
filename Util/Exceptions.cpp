#include "Exceptions.h"
//----------------------------------------------- CONSTRUCTOR ------------------------------------------------
GeneralException::GeneralException(const std::string &message)
:message(message)
{
}
//----------------------------------------------- GET MESSAGE ------------------------------------------------
const char* GeneralException::getMessage(void)
{
  return this->message.c_str();
}
//----------------------------------------------- APPEND -----------------------------------------------------
void GeneralException::append(const std::string& str)
{
  this->message += " < ";
  this->message += str;
}
//----------------------------------------------- CONSTRUCTOR ------------------------------------------------
FileException::FileException(const std::string &message) : GeneralException(message)
{
}
//----------------------------------------------- CONSTRUCTOR ------------------------------------------------
ConfigException::ConfigException(const std::string &message) : GeneralException(message)
{
}
//----------------------------------------------- CONSTRUCTOR ------------------------------------------------
XmlException::XmlException(const std::string& message, const std::string& fileName, const long lineNumber) 
:GeneralException(message)
,fileName(fileName)
,lineNumber(lineNumber)
{
}
//----------------------------------------------- CONSTRUCTOR ------------------------------------------------
ParseException::ParseException(const std::string& message)
:GeneralException(message)
{
}
//------------------------------------------------------------------------------------------------------------
