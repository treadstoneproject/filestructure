
#include "gtest/gtest.h"

#include "elf_process_controller.h"
#include "pe.h"

TEST(ElfProcessController, ELFPC){

	filestructure::elf_process_controller<struct MAPPED_FILE_PE, struct MAPPED_FILE_PE> elf_pc;
	EXPECT_TRUE(elf_pc.get_file_support());

}