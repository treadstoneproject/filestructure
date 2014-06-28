#if   _WIN32
#include "filestructure/mapped_file/mapped_file_controller.h"
#elif __linux__
#include "utils/file_offset_handler.hpp"
#define FILE_SIZE 1
#endif

#include "filestructure/pe.hpp"
#include <vector>

using namespace utils;

class PELayoutControllerTest : public ::testing::Test
{

    protected:
        virtual void SetUp() {
#if  _WIN32 

#elif __linux__
						file_sig  = "/home/chatsiri/Dropbox/reversing_engineer/write_sig/signature_trojan.ndb";
            char const *file_name_offset[FILE_SIZE];
            file_name_offset[0] = "/home/chatsiri/sda1/workspacecpp/clamav-devel/test/clam-petite.exe";
						
            for(int count_file = 0; count_file < 	FILE_SIZE; count_file++) {
                file_type_vec.push_back(file_name_offset[count_file]);
                mapped_file_vec.push_back(&s_mapped_fpe[count_file]);

            }
#endif 

        }
#if _WIN32


#elif __linux__
        std::vector<const char*> file_type_vec;
        struct MAPPED_FILE_PE s_mapped_fpe[FILE_SIZE];
        std::vector<MAPPED_FILE_PE *> mapped_file_vec;
				const char * file_sig;
#endif 

};


TEST_F(PELayoutControllerTest, InitialMapFileOffsetHandler)
{
#if _WIN32

    filestructure::mapped_file_controller<struct MAPPED_FILE_PE>
            mfc;
    std::vector<const char *> char_vec;
    const char * file_name = "E:\\Dropbox\\reversing_engineer\\reversing_files_test\\clam_ISmsi_ext.exe";
    char_vec.push_back(file_name);

    MAPPED_FILE_PE *file_pe = new MAPPED_FILE_PE();
    std::vector<MAPPED_FILE_PE *>  mapped_ptr_vec;
    mapped_ptr_vec.push_back(file_pe);
    mfc.mapped_file(char_vec, mapped_ptr_vec);
    std::vector<MAPPED_FILE_PE *>::iterator iter_mfv;

    for (iter_mfv = mapped_ptr_vec.begin(); iter_mfv != mapped_ptr_vec.end(); ++iter_mfv) {
        MAPPED_FILE_PE   *mf_pe = *iter_mfv;
        LOG(INFO) << "Mapped_file PE size : " << mf_pe->size;
        LOG(INFO) << "Mapped_file PE starts buffer : " << mf_pe->data[0];
    }

#elif __linux__

	 LOG(INFO) << "Initial Mapped file type start...";		

		file_offset_handler<struct common_filetype, struct MAPPED_FILE_PE>  fileoffset_h;			

		EXPECT_TRUE(fileoffset_h.mapped_file(file_type_vec, mapped_file_vec, fileoffset_h, file_sig));

    boost::shared_ptr<std::vector<MAPPED_FILE_PE * > > mappedf_vec_ptr =
            fileoffset_h.get_mappedf_vec_ptr();

    std::vector<MAPPED_FILE_PE *> *mapped_file_vec_ptr = mappedf_vec_ptr.get();


		typename std::vector<MAPPED_FILE_PE*>::iterator iter_mapped_file;
		for(iter_mapped_file = mapped_file_vec_ptr->begin(); 
				iter_mapped_file != mapped_file_vec_ptr->end(); 
				++iter_mapped_file)
		{
							MAPPED_FILE_PE * mf_pe = *iter_mapped_file;
							unsigned char * data = mf_pe->data;
							size_t size  = mf_pe->size; 
						  EXPECT_GT(size,0);
							ASSERT_TRUE(*data != NULL);
		}

    EXPECT_TRUE(fileoffset_h.unmapped_file(mapped_file_vec));
#endif 


}
