#@+leo-ver=5-thin
#@+node:gcross.20101205182001.1312: * @file CMakeLists.txt
install (
    DIRECTORY .
    DESTINATION ${HEADER_INSTALLATION_DIRECTORY}
    PATTERN "CMakeLists.txt" EXCLUDE
    PATTERN "boost/*" EXCLUDE
)
#@-leo
