#include "TestCaseMessage.h"

TestCaseMessage::TestCaseMessage(const QString& type, const QString& message, const QString& source_file, const QString& source_line)
	: m_type(type), m_message(message)
{
	source_file.isEmpty() ? m_source_file = "-" : m_source_file = source_file;
	(source_line.isEmpty() || source_line == "0") ? m_source_line = "-" : m_source_line = source_line;
}

const QString& TestCaseMessage::Type() const
{
	return m_type;
}

const QString& TestCaseMessage::Message() const
{
	return m_message;
}

const QString& TestCaseMessage::SourceFile() const
{
	return m_source_file;
}

const QString& TestCaseMessage::SourceLine() const
{
	return m_source_line;
}
