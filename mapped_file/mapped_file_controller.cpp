

#include "mapped_file_controller.h"

#include "logger/logging.h"
#include <stdexcept>
#include <exception>


#include <fcntl.h> 
#include <io.h> 
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>


#define S_ISREG(B) ((B)&_S_IFREG)
#define S_ISDIR(B) ((B)&_S_IFDIR)




using namespace filestructure;

template<typename MAPPED_FILE>
mapped_file_controller< MAPPED_FILE>::mapped_file_controller(){

}

template< typename MAPPED_FILE>
bool mapped_file_controller<MAPPED_FILE>::get_file_status()
{

	return false;
}



template<typename MAPPED_FILE>
bool mapped_file_controller<MAPPED_FILE>::file_read()
{

	if (stat(file_path, &file_status) != 0 || S_ISDIR(file_status.st_mode)) {
		throw std::runtime_error("File cannot check status");
		return false;
	}
	errno_t err;
	err = fopen_s(&p_file, file_path, "r");

	if (p_file == NULL) {
		throw std::runtime_error("File cannot open");
		return false;
	}

	return true;
}

template<typename MAPPED_FILE>
bool mapped_file_controller<MAPPED_FILE>::fread_mapped()
{
	
	if (stat(file_path, &file_status) != 0 || S_ISDIR(file_status.st_mode)) {
		throw std::runtime_error("File cannot check status");
		return false;
	}

	_sopen_s(&p_open_file, file_path, O_RDONLY, _SH_DENYNO, _S_IREAD | _S_IWRITE);

	if (p_open_file == NULL) {
		throw std::runtime_error("File cannot open");
		return false;
	}

	return true;
}

template<typename MAPPED_FILE>
typename int &
mapped_file_controller<MAPPED_FILE>::get_popen_file()
{
	return p_open_file;
}



/*
template<typename FileType, typename MAPPED_FILE>
struct stat    *mapped_file_controller<FileType, MAPPED_FILE>::get_file_status() {
return &file_status;
}
*/


template< typename MAPPED_FILE>
bool mapped_file_controller<MAPPED_FILE>::set_filepath(char const *file_path)
{
	this->file_path = file_path;

	if (this->file_path != NULL)
		return true;

	return false;
}

template<typename MAPPED_FILE>
FILE *mapped_file_controller<MAPPED_FILE>::get_file() const
{
	return p_file;
}

template<typename MAPPED_FILE>
bool mapped_file_controller<MAPPED_FILE>::close_file()
{
	_close(p_open_file);
	return true;
}

template<typename MAPPED_FILE>
bool  mapped_file_controller<MAPPED_FILE>::
mapped_file(std::vector<const char*> file_name_vec,
std::vector<MAPPED_FILE *> mapped_vec){

	std::vector<const char*>::iterator iter_files;

	mapped_vec_shared = boost::make_shared<std::vector<MAPPED_FILE * > >();

	const char *file_names;
	std::string s_file_name;
	MAPPED_FILE *mapped_file_ptr;

	if (!file_name_vec.size() || !mapped_vec.size()) {
		LOG(INFO) << "Not data on file_name or mapped file";
		return false;
	}

	for (iter_files = file_name_vec.begin();
		iter_files != file_name_vec.end();
		++iter_files) {

		try {
			s_file_name = *iter_files;

			if (s_file_name.empty())
				LOG(ERROR) << "[** File is null **]";


			LOG(INFO) << "File path for mmaped " << s_file_name;

			//Set file name to mapped structure

			file_names = s_file_name.c_str();

		}
		catch (std::exception & offset_excep) {
			LOG(INFO) << "Error, file offset";
			continue;
		}

		if (set_filepath(file_names)) {

			if (!fread_mapped()) {
				LOG(INFO) << "[** File cannot open path **]";
			}

			mapped_file_ptr = mapped_vec.at(std::distance(file_name_vec.begin(), iter_files));
			try {
				if (mapped_file_ptr == NULL) {
					LOG(INFO) << "[** Mapped pointer is null. **]";
				}

				//struct stat *file_status_s = &file_status;// file_offset_object.get_file_status();
				LOG(INFO) << "File size : " << file_status.st_size;
				mapped_file_ptr->size = file_status.st_size;

				mapped_file_ptr->file = get_popen_file();

				LOG(INFO) << "Mapped file ptr size  " << mapped_file_ptr->size;

				LOG(INFO) << "Mapped file ptr name  " << mapped_file_ptr->file;

				if (mapped_file_ptr->size == 0 || mapped_file_ptr->file == -1) {
					LOG(INFO) << "[** File size don't get status **]";
				}
				//allocated size of file name. 
				mapped_file_ptr->file_name = (char*)malloc(sizeof(char*)* s_file_name.size());
				//insert file name path.
				mapped_file_ptr->file_name = s_file_name.c_str();

				close_file();

				//read file map.
				boost::iostreams::mapped_file_params mf_params(s_file_name);
				mf_source.open(mf_params);
				if (mf_source.is_open()){
					LOG(ERROR) << "Cannot open file with mapped_file_source";
				}
				mapped_file_ptr->data = (uint8_t*)mf_source.data();

			}
			catch(std::exception ex) {
				LOG(INFO) << "Error, Mapped file" << ex.what();
				continue;

			}
		}
	}
	file_name_vec.clear(); // clear file name on list
	return true;


}



template class mapped_file_controller<struct MAPPED_FILE_PE>;
