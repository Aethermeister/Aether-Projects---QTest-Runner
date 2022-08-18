#pragma once

#include <QtCore/QString>

/**
 * @brief Message class to handle additional test case information
*/
class TestCaseMessage
{
public:
	explicit TestCaseMessage() = default;
	explicit TestCaseMessage(const QString& type, const QString& message, const QString& source_file, const QString& source_line);
	virtual ~TestCaseMessage() = default;

	/**
	 * @brief Getter for the message type
	 * 
	 * @return The type of the message
	*/
	const QString& Type() const;
	/**
	 * @brief Getter for the message text
	 *
	 * @return The text of the message
	*/
	const QString& Message() const;
	/**
	 * @brief Getter for the message source file
	 *
	 * @return The source file of the message
	*/
	const QString& SourceFile() const;
	/**
	 * @brief Getter for the message source line
	 *
	 * @return The source line of the message
	*/
	const QString& SourceLine() const;

private:
	/**
	 * @brief The type of the message
	*/
	QString m_type = "-";
	/**
	 * @brief The text of the message
	*/
	QString m_message = "-";
	/**
	 * @brief The source file of the message
	*/
	QString m_source_file = "-";
	/**
	 * @brief The source line of the message
	*/
	QString m_source_line = "-";
};

