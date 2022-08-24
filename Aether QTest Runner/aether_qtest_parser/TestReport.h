#pragma once
#include "aether_qtest_parser_global.h"
#include "TestSuite.h"
#include "XMLError.h"

#include <QtCore/QVector>

/**
 * @brief The TestReport class holds all information about a test run. Its parts are one or more test suites
*/
class AETHER_QTEST_PARSER_EXPORT TestReport
{
public:
	explicit TestReport() = default;
	virtual ~TestReport() = default;

	/**
	 * @brief Setter of the test report title
	 * 
	 * @param title The new title of the test report
	*/
	void SetTitle(const QString& title);
	/**
	 * @brief Getter of the test report title
	 * 
	 * @return The title of the test report
	*/
	const QString& Title() const;
	/**
	 * @brief Add a TestSuite object to the test report
	 * 
	 * @param test_suite The TestSuite object which has to be added to the test report
	*/
	void AddTestSuite(const TestSuite& test_suite);
	/**
	 * @brief Getter of the test suites
	 * 
	 * @return The test suites in the test report
	*/
	const QVector<TestSuite>& TestSuites() const;

	/**
	 * @brief Add an XML error to the test report
	 * 
	 * @param xml_error The XML error which describes the occured issue
	*/
	void AddError(const XMLError& xml_error);
	
	/**
	 * @brief Returns the number of test suites of the test report
	 * 
	 * @return The test suite count in the test report
	*/
	int TestSuiteCount() const;
	/**
	 * @brief Returns the number of test cases of the test report
	 *
	 * @return The test case count in the test report
	*/
	int TestCaseCount() const;
	/**
	 * @brief Returns the number of passed test cases of the test report
	 *
	 * @return The passed test case count in the test report
	*/
	int PassedTestCaseCount() const;
	/**
	 * @brief Returns the number of failed test cases of the test report
	 *
	 * @return The failed test case count in the test report
	*/
	int FailedTestCaseCount() const;
	/**
	 * @brief Returns the overall duration of the test run
	 * 
	 * @return The duration of the test run in ms
	*/
	double TestRunDurationMs() const;

private:
	/**
	 * @brief The (displayed) title of the test report
	*/
	QString m_title;
	/**
	 * @brief The list of TestSuite objects in the test report
	*/
	QVector<TestSuite> m_test_suites;
	/**
	 * @brief List of xml parser errors
	*/
	QVector<XMLError> m_parser_errors;
};

