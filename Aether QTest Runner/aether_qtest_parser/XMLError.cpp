#include "XMLError.h"

XMLError::XMLError(const QString& xml_filename) : m_xml_filename(xml_filename)
{
}

const QString& XMLError::XMLFilename() const
{
	return m_xml_filename;
}

const QString& XMLError::ErrorMessage() const
{
	return m_error_message;
}

void XMLError::SetErrorMessage(const QString& error_message)
{
	m_error_message = error_message;
}

int XMLError::ErrorLine() const
{
	return m_error_line;
}

void XMLError::SetErrorLine(int error_line)
{
	m_error_line = error_line;
}

int XMLError::ErrorColumn() const
{
	return m_error_column;
}

void XMLError::SetErrorColumn(int error_column)
{
	m_error_column = error_column;
}
