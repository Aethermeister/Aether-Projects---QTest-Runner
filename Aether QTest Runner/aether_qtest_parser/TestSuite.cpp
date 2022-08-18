#include "TestSuite.h"

#include <algorithm>

TestSuite::TestSuite(const QString& name) : m_name(name)
{
}

const QString& TestSuite::Name() const
{
	return m_name;
}

void TestSuite::AddConfiguration(const QString& config_key, const QString& config_value)
{
	m_configurations.insert(config_key, config_value);
}

void TestSuite::AddTestCase(const TestCase& test_case)
{
	m_test_cases.append(test_case);
}

void TestSuite::SetDurationMs(const QString& duration)
{
	m_duration_ms = duration;
}

double TestSuite::TestSuiteRunDurationMs() const
{
	return m_duration_ms.toDouble();
}

const QString& TestSuite::TestSuiteRunDurationMsString() const
{
	return m_duration_ms;
}

int TestSuite::TestCaseCount() const
{
	return m_test_cases.count();
}

int TestSuite::PassedTestCaseCount() const
{
	return std::count_if(m_test_cases.begin(), m_test_cases.end(), [](const TestCase& test_case) { return test_case.IsPassed(); });
}

int TestSuite::FailedTestCaseCount() const
{
	return std::count_if(m_test_cases.begin(), m_test_cases.end(), [](const TestCase& test_case) { return !test_case.IsPassed(); });
}

const QVector<TestCase>& TestSuite::TestCases() const
{
	return m_test_cases;
}
