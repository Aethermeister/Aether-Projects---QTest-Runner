#pragma once
#include "TestCaseMessage.h"

#include <QtCore/QVector>

/**
 * @brief The TestCase class wraps the test case related information
*/
class TestCase
{
public:
	explicit TestCase() = default;
	explicit TestCase(const QString& name, const QString& test_suite_name);
	virtual ~TestCase() = default;

	/**
	 * @brief Getter of the test case name
	 * 
	 * @return The name of the test case
	*/
	const QString& Name() const;
	/**
	 * @brief Getter of the test suite name of this test case
	 *
	 * @return The name of the test suite of this test case
	*/
	const QString& TestSuiteName() const;
	/**
	 * @brief Add general message related to the test case. The test case can have multiple message
	 * 
	 * @param message The message object which has to be added to the test case
	*/
	void AddMessage(const TestCaseMessage& message);
	/**
	 * @brief Set the fail/pass test case message as the incident
	 * 
	 * @param message The message object which describes the overall test case state
	*/
	void SetIncident(const TestCaseMessage& message);
	/**
	 * @brief Set the duration of the test case
	 * 
	 * @param duration The test case duration
	*/
	void SetDurationMs(const QString& duration);
	/**
	 * @brief Double type getter of the duration
	 * 
	 * @return The duration as a double type variable
	*/
	double DurationMs() const;
	/**
	 * @brief String type getter of the duration
	 *
	 * @return The duration as a QString type variable
	*/
	const QString& DurationMsString() const;

	/**
	 * @brief Resturns the passed state of the test case
	 * 
	 * @return True if the test case is passed
	*/
	bool IsPassed() const;

private:
	/**
	 * @brief The name of the test case
	*/
	QString m_name;
	/**
	 * @brief The name of the test suite of this test case
	*/
	QString m_test_suite_name;
	/**
	 * @brief Flag to indicate test case success state
	*/
	bool m_is_test_case_passed = true;
	/**
	 * @brief The list of general test case messages
	*/
	QVector<TestCaseMessage> m_messages;
	/**
	 * @brief The incident test case message which describes the state of the test case
	*/
	TestCaseMessage m_incident_message;
	/**
	 * @brief The duration of the test case
	*/
	QString m_duration_ms;
};

