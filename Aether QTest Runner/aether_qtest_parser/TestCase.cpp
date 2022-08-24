#include "TestCase.h"

TestCase::TestCase(const QString& name, const QString& test_suite_name) : m_name(name), m_test_suite_name(test_suite_name)
{
}

const QString& TestCase::Name() const
{
	return m_name;
}

const QString& TestCase::TestSuiteName() const
{
	return m_test_suite_name;
}

void TestCase::AddMessage(const TestCaseMessage& message)
{
	m_messages.append(message);
}

const QVector<TestCaseMessage>& TestCase::Messages() const
{
	return m_messages;
}

void TestCase::SetIncident(const TestCaseMessage& message)
{
	m_is_test_case_passed = false;
	m_incident_message = message;
}

const TestCaseMessage& TestCase::Incident() const
{
	return m_incident_message;
}

void TestCase::SetDurationMs(const QString& duration)
{
	m_duration_ms = duration;
}

double TestCase::DurationMs() const
{
	return m_duration_ms.toDouble();
}

const QString& TestCase::DurationMsString() const
{
	return m_duration_ms;
}

bool TestCase::IsPassed() const
{
	return m_is_test_case_passed;
}
