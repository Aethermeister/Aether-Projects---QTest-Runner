#include "TestReport.h"

#include <numeric>

void TestReport::SetTitle(const QString& title)
{
	m_title = title;
}

const QString& TestReport::Title() const
{
	return m_title;
}

void TestReport::AddTestSuite(const TestSuite& test_suite)
{
	m_test_suites.append(test_suite);
}

const QVector<TestSuite>& TestReport::TestSuites() const
{
	return m_test_suites;
}

void TestReport::AddError(const XMLError& xml_error)
{
	m_parser_errors.append(xml_error);
}

int TestReport::TestSuiteCount() const
{
	return m_test_suites.count();
}

int TestReport::TestCaseCount() const
{
	return std::accumulate(m_test_suites.begin(), m_test_suites.end(), 0, [](int count, const TestSuite& test_suite) { return count + test_suite.TestCaseCount(); });
}

int TestReport::PassedTestCaseCount() const
{
	return std::accumulate(m_test_suites.begin(), m_test_suites.end(), 0, [](int count, const TestSuite& test_suite) { return count + test_suite.PassedTestCaseCount(); });
}

int TestReport::FailedTestCaseCount() const
{
	return std::accumulate(m_test_suites.begin(), m_test_suites.end(), 0, [](int count, const TestSuite& test_suite) { return count + test_suite.FailedTestCaseCount(); });
}

double TestReport::TestRunDurationMs() const
{
	return std::accumulate(m_test_suites.begin(), m_test_suites.end(), 0.0, [](double duration, const TestSuite& test_suite) { return duration + test_suite.TestSuiteRunDurationMs(); });
}
