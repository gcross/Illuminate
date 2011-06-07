#@+leo-ver=5-thin
#@+node:gcross.20101205182001.1312: * @file CMakeLists.txt
install (
    DIRECTORY .
    DESTINATION include/illuminate-${version}
    PATTERN "CMakeLists.txt" EXCLUDE
)
#@-leo
