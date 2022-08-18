#pragma once
#include "TestCase.h"

#include <QtCore/QMap>
#include <QtCore/QVector>

/**
 * @brief The TestSuite class holds the related TestCase objects and additional test run related information
*/
class TestSuite
{
public:
	explicit TestSuite(const QString& name);
	virtual ~TestSuite() = default;

	/**
	 * @brief Add the test suite related configuration information
	 * 
	 * @param config_key The name of the configuration data
	 * @param config_value The value of the configuration data
	*/
	void AddConfiguration(const QString& config_key, const QString& config_value);
	/**
	 * @brief Add test case to the test suite
	 * 
	 * @param test_case The TestCase object which relates to the test suite
	*/
	void AddTestCase(const TestCase& test_case);
	/**
	 * @brief Setter of the summarized test run duration of the test suite
	 * 
	 * @param duration The new duration of the test suite in ms
	*/
	void SetDurationMs(const QString& duration);
	/**
	 * @brief Getter of the duration of the test suite
	 * 
	 * @return Double type duration of the test suite in ms
	*/
	double TestSuiteRunDurationMs() const;
	/**
	 * @brief Getter of the duration of the test suite
	 *
	 * @return QString type duration of the test suite in ms
	*/
	const QString& TestSuiteRunDurationMsString() const;

	/**
	 * @brief Getter of the test suite name
	 * 
	 * @return The name of the test suite
	*/
	const QString& Name() const;
	/**
	 * @brief Returns the number of test cases of the test suite
	 *
	 * @return The test case count in the test suite
	*/
	int TestCaseCount() const;
	/**
	 * @brief Returns the number of passed test cases of the test suite
	 *
	 * @return The passed test case count in the test suite
	*/
	int PassedTestCaseCount() const;
	/**
	 * @brief Returns the number of failed test cases of the test suite
	 *
	 * @return The failed test case count in the test suite
	*/
	int FailedTestCaseCount() const;

	/**
	 * @brief Getter of the test cases
	 * 
	 * @return The test cases in the test suite
	*/
	const QVector<TestCase>& TestCases() const;

private:
	/**
	 * @brief The name of the test suite
	*/
	QString m_name;
	/**
	 * @brief The overall duration of the test suite
	*/
	QString m_duration_ms;
	/**
	 * @brief The configurations of the test suite
	*/
	QMap<QString, QString> m_configurations;
	/**
	 * @brief The test suite related TestCase objects
	*/
	QVector<TestCase> m_test_cases;
};

