cmake_minimum_required(VERSION 2.8)

project(libzmath C)
# project(<project_name> [language_name1 language_name2 ...])
# 这条指令隐式定义了两个变量，并分别赋值:
# <project_name>_BINARY_DIR
# <project_name>_SOURCE_DIR


# 生成的库名
set(ZMATH_LIB_NAME zmath)

# 设置版本号
set(ZMATH_MAJOR 2)
set(ZMATH_MINOR 0)
set(ZMATH_RELEASE 1)
set(ZMATH_VERSION ${ZMATH_MAJOR}.${ZMATH_MINOR}.${ZMATH_RELEASE})

# 编译控制选项
option(ZMATH_SHARED "Build shared lib" ON)
option(ZMATH_STATIC "Build static lib" ON)
option(ZMATH_TESTS "Build tests" ON)


# 编译选项
add_definitions(-DSOME_MACRO)
set(CMAKE_C_FLAGS_DEBUG "-g -Wall -DZMATH_DEBUG=1")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-exceptions -std=c11")

set(ZMATH_PUBLIC_HEADERS
    src/zmath.h
)

set(ZMATH_LIB_SOURCES
    ${ZMATH_PUBLIC_HEADERS}
    src/add.c
    src/subtract.c
    src/multiply.c
    src/divide.c
)

set(ZMATH_TEST_SOURCES
    src/ztest.c
)

# 构建静态库
if(ZMATH_STATIC)
    set(ZMATH_LIB_NAME_STATIC ${ZMATH_LIB_NAME}_static)
    add_library(${ZMATH_LIB_NAME_STATIC} STATIC
        ${ZMATH_LIB_SOURCES}
    )
    set_target_properties(${ZMATH_LIB_NAME_STATIC} PROPERTIES
        OUTPUT_NAME ${ZMATH_LIB_NAME}
        CLEAN_DIRECT_OUTPUT 1
    )
endif()

# 构建共享库
if(ZMATH_SHARED)
    set(ZMATH_LIB_NAME_SHARED ${ZMATH_LIB_NAME}_shared)
    add_library(${ZMATH_LIB_NAME_SHARED} SHARED
        ${ZMATH_LIB_SOURCES}
    )
    set_target_properties(${ZMATH_LIB_NAME_SHARED} PROPERTIES
        VERSION ${ZMATH_VERSION}
        SOVERSION ${ZMATH_MAJOR}
        CLEAN_DIRECT_OUTPUT 1
        OUTPUT_NAME ${ZMATH_LIB_NAME}
    )
endif()

# 构建测试代码　
if(ZMATH_TESTS)
    # 测试静态库
    set(ZMATH_TESTS_NAME_STATIC ${ZMATH_LIB_NAME}_test_static)
    add_executable(${ZMATH_TESTS_NAME_STATIC}
        ${ZMATH_TEST_SOURCES}
    )
    set_target_properties(${ZMATH_TESTS_NAME_STATIC} PROPERTIES
        OUTPUT_NAME zmath_test_static
    )
    target_link_libraries(${ZMATH_TESTS_NAME_STATIC} ${ZMATH_LIB_NAME_STATIC})

    # 测试动态库，结果比较奇怪，但是由于动态库的特性，一般不直接引用
    # 下面的例子，默认使用了rpath
    set(ZMATH_TESTS_NAME_SHARED ${ZMATH_LIB_NAME}_test_shared)
    add_executable(${ZMATH_TESTS_NAME_SHARED}
        ${ZMATH_TEST_SOURCES}
    )
    set_target_properties(${ZMATH_TESTS_NAME_SHARED} PROPERTIES
        OUTPUT_NAME zmath_test_shared
    )
    target_link_libraries(${ZMATH_TESTS_NAME_SHARED} ${ZMATH_LIB_NAME_SHARED})
endif()


# 安装库
install(TARGETS ${ZMATH_LIB_NAME_STATIC} ARCHIVE DESTINATION lib)
install(TARGETS ${ZMATH_LIB_NAME_SHARED} LIBRARY DESTINATION lib)
install(TARGETS ${ZMATH_TESTS_NAME_STATIC} RUNTIME DESTINATION bin)
install(FILES ${ZMATH_PUBLIC_HEADERS} DESTINATION  include)
