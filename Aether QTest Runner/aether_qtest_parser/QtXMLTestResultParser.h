#pragma once
#include "TestCase.h"
#include "TestSuite.h"
#include "TestReport.h"

#include <QtCore/QStringList>
#include <QtXml/QDomDocument>

/**
 * @brief Parser class to handle the Qt generated xml test results
*/
class QtXMLTestResultParser
{
public:
	explicit QtXMLTestResultParser(const QStringList& files);
	virtual ~QtXMLTestResultParser() = default;

	/**
	 * @brief Returns the parsed and unified test report data
	 * 
	 * @return The test report data
	*/
	const TestReport& ParsedTestReport() const;

private:
	/**
	 * @brief The unified test report data created from the Qt generated xml test result(s)
	*/
	TestReport m_test_report;

	/**
	 * @brief Parses the given Qt xml test results
	 * 
	 * @param files The list of Qt xml test result files to be parsed
	*/
	void ParseQtXMLTestResults(const QStringList& files);
	/**
	 * @brief Parses the given Qt xml test result
	 * 
	 * @param file The Qt xml test result file to be parsed
	*/
	void ParseQtXMLTestResult(const QString& file);
	/**
	 * @brief Converts the raw xml to QDomDocument and tries to repair the xml if it is invalid
	 * 
	 * @param file_content The raw xml of a Qt test result file
	 * @param xml_document The xml document object which will be validate and hold the raw xml
	 * 
	 * @return The raw xml validation success
	*/
	bool TryToCreateDomXMLDocument(const QString& file_content, QDomDocument& xml_document, XMLError& xml_error) const;

	/**
	 * @brief Extract the environment/configuration related information from the given xml document and update the given test suit object
	 * 
	 * @param xml_document The xml document which holds the validated Qt test result
	 * @param test_suit The test suite object which handles the test result related data
	*/
	void ExtractEnvironmentData(const QDomDocument& xml_document, TestSuite& test_suit) const;
	/**
	 * @brief Extract the Qt generated test functions from the xml document
	 * 
	 * @param xml_document The xml document which holds the validated Qt test result
	 * @param test_suit The test suite object which handles the test result related data
	*/
	void ExtractTestFunctionData(const QDomDocument& xml_document, TestSuite& test_suit) const;
	/**
	 * @brief Extract the content of the actual Function child node
	 * 
	 * @param xml_element A child xml element of a Function node
	 * @param test_case The test case of the Function data is stored in
	*/
	void ExtractTestFunctionContentData(const QDomElement& xml_element, TestCase& test_case) const;
};

