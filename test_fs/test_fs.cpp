// test_fs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "gtest/gtest.h"

#include "mapped_file/mapped_file_controller.h"

//#include "elf_process_controller.h"
#include "pe.h"

#include "logger/logging.h"
#include "logger/stringprintf.h"





TEST(MappedFileController, TestIntial){
	filestructure::mapped_file_controller<struct MAPPED_FILE_PE>
		mfc;
	std::vector<const char*> char_vec;
	//Support Win32 : const char * file_name = "E:\\Dropbox\\reversing_engineer\\reversing_files_test\\clam_ISmsi_ext.exe";
	const char * file_name = "";// file read for check pe
	char_vec.push_back(file_name);
	
	MAPPED_FILE_PE * file_pe = new MAPPED_FILE_PE();
	std::vector<MAPPED_FILE_PE*>  mapped_ptr_vec;
	mapped_ptr_vec.push_back(file_pe);
	mfc.mapped_file(char_vec, mapped_ptr_vec);
	std::vector<MAPPED_FILE_PE*>::iterator iter_mfv;
	for (iter_mfv = mapped_ptr_vec.begin(); iter_mfv != mapped_ptr_vec.end(); ++iter_mfv){
		MAPPED_FILE_PE  * mf_pe = *iter_mfv;
		LOG(INFO) << "Mapped_file PE size : " << mf_pe->size;
		LOG(INFO) << "Mapped_file PE starts buffer : " << mf_pe->data[0];
	}

}

/*
TEST(ElfProcessController, TestInitial){

	filestructure::elf_process_controller<struct MAPPED_FILE_PE, struct MAPPED_FILE_PE> elf_pc;
	EXPECT_TRUE(elf_pc.get_file_support());
}
*/


void initial_logging(std::string filename_prefix){

	InitializeLogger(StringPrintf("%s.INFO", filename_prefix.c_str()),
		StringPrintf("%s.WARN", filename_prefix.c_str()),
		StringPrintf("%s.ERROR", filename_prefix.c_str()));
}

int _tmain(int argc, _TCHAR* argv[])
{
	 initial_logging("/home/chatsiri/workspacecpp/pthread_sync_ocl/log");
	//Support Win32:initial_logging("E:\\workspacecpp\\filestructure\\log");
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	return 0;
}


