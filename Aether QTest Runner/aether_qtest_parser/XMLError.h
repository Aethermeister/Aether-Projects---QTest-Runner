#pragma once

#include <QtCore/QString>

/**
 * @brief Class which contains the xml related parsing errors
*/
class XMLError
{
public:
	explicit XMLError(const QString& xml_filename);
	~XMLError() = default;

	/**
	 * @brief Getter of the name of the xml file
	 * 
	 * @return The name of the xml file
	*/
	const QString& XMLFilename() const;

	/**
	 * @brief Getter of the error message text
	 * 
	 * @return The error message text
	*/
	const QString& ErrorMessage() const;
	/**
	 * @brief Set the text of the error message
	 * 
	 * @param error_message The text of the error message
	*/
	void SetErrorMessage(const QString& error_message);

	/**
	 * @brief Getter of the line number of the error
	 * 
	 * @return The line number of the error
	*/
	int ErrorLine() const;
	/**
	 * @brief Set the line number of the error
	 * 
	 * @param error_line The line number of the error
	*/
	void SetErrorLine(int error_line);

	/**
	 * @brief Getter of the column number of the error
	 *
	 * @return The column number of the error
	*/
	int ErrorColumn() const;
	/**
	 * @brief Set the column number of the error
	 *
	 * @param error_line The column number of the error
	*/
	void SetErrorColumn(int error_column);

private:
	/**
	 * @brief The name of the xml file with error
	*/
	QString m_xml_filename;

	/**
	 * @brief The text of the parsing error
	*/
	QString m_error_message;
	/**
	 * @brief The line number of the error
	*/
	int m_error_line = -1;
	/**
	 * @brief The column number of the error
	*/
	int m_error_column = -1;
};

