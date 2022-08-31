# Aether-Projects---QTest-Runner

QTest Runner is an easy to use utility tool for testing Qt applications. It generates a summarized test report from the Qt test executable created xml results. Additionally code coverage can be also measured for the tested application.




# Architectural requirements

The Qt test application has to be implemented so it executes every contained test case when calling the executable file from comman line. The test output has to be xml and either each test case has to have a unique xml test result file. Refer to the dummy_qtests project.



# Third-party requirements

QTest Runner provides an option to measure the code coverage of the target Qt application. To measure code coverage and generate a readable report from it OpenCppCoverage is used as third-party tool but it has to be manually installed and added to the PATH environment variable.
