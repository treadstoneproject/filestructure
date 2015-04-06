// test_fs.cpp : Defines the entry point for the console application.
//
#if _WIN32
#include "stdafx.h"
#endif

#include <iostream>
#include "gtest/gtest.h"

#include "environment_test.hpp"

#include "filestructure/logger/logging.hpp"
#include "filestructure/logger/stringprintf.hpp"

#if   _WIN32
#include "filestructure/test_fs/test_pe_layout_controller.hpp"
#elif __linux__
#include "test_fs/test_pe_layout_controller.hpp"
#endif







TEST(MappedFileController, TestIntial)
{
	 LOG(INFO)<<" Test Filestructure ";
}


void initial_logging(std::string filename_prefix)
{

    InitializeLogger(StringPrintf("%s.INFO", filename_prefix.c_str()),
            StringPrintf("%s.WARN", filename_prefix.c_str()),
            StringPrintf("%s.ERROR", filename_prefix.c_str()));
}

int _tmain(int argc, char  **argv)
{
    testing::InitGoogleTest(&argc, argv);
    testing::AddGlobalTestEnvironment( new SystemTestingEnvironment(argc, argv));
    return RUN_ALL_TESTS();
}


