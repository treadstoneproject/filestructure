// test_fs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "gtest/gtest.h"

#include "elf_process_controller.h"
#include "pe.h"

#include "logger/logging.h"
#include "logger/stringprintf.h"

TEST(ElfProcessController, ELFPC){

	filestructure::elf_process_controller<struct MAPPED_FILE_PE, struct MAPPED_FILE_PE> elf_pc;
	EXPECT_TRUE(elf_pc.get_file_support());
}


void initial_logging(std::string filename_prefix){

	InitializeLogger(StringPrintf("%s.INFO", filename_prefix.c_str()),
		StringPrintf("%s.WARN", filename_prefix.c_str()),
		StringPrintf("%s.ERROR", filename_prefix.c_str()));
}

int _tmain(int argc, _TCHAR* argv[])
{
	initial_logging("E:\\workspacecpp\\filestructure\\log");
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	return 0;
}


