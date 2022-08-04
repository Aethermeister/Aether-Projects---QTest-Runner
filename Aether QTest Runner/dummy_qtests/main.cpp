#include "PassingTestClass.h"
#include "FailingTestClass.h"
#include "MixingTestClass.h"
#include "CrashingTestClass.h"

#include <QtCore/QCoreApplication>
#include <QtTest/QTest>

#include <vector>
#include <functional>

int PassingTestClassFunction()
{
	PassingTestClass passing_test_class;
	return QTest::qExec(&passing_test_class, { QCoreApplication::arguments().at(0), "-o", "TestResults//PassingTestClassReport.xml,xml" });
}

int FailingTestClassFunction()
{
	FailingTestClass failing_test_class;
	return QTest::qExec(&failing_test_class, { QCoreApplication::arguments().at(0), "-o", "TestResults//FailingTestClass.xml,xml" });
}

int MixingTestClassFunction()
{
	MixingTestClass mixing_test_class;
	return QTest::qExec(&mixing_test_class, { QCoreApplication::arguments().at(0), "-o", "TestResults//MixingTestClass.xml,xml" });
}

int CrashingTestClassFunction()
{
	CrashingTestClass crashing_test_class;
	return QTest::qExec(&crashing_test_class, { QCoreApplication::arguments().at(0), "-o", "TestResults//CrashingTestClass.xml,xml" });
}

const std::vector<std::function<int()>> test_class_collection
{
	PassingTestClassFunction,
	FailingTestClassFunction,
	MixingTestClassFunction,
	CrashingTestClassFunction
};

int main(int argc, char* argv[])
{
	QCoreApplication app(argc, argv);

	for (auto it = test_class_collection.begin(); it != test_class_collection.end(); ++it)
	{
		(*it)();
	}

	return 0;
}
