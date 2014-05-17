#include "mapped_file_controller.h"
#include "logger/logging.h"

#include <stdio.h>
#include <errno.h>

using namespace filestructure;

template<typename FileType, typename MAPPED_FILE>
bool mapped_file_controller<FileType, MAPPED_FILE>::file_read()
{

	if (stat(file_path, &file_status) != 0 || S_ISDIR(file_status.st_mode)) {
		throw std::runtime_error("File cannot check status");
		return false;
	}

	p_file = fopen(file_path, "r");

	if (p_file == NULL) {
		throw std::runtime_error("File cannot open");
		return false;
	}

	return true;
}

template<typename FileType, typename MAPPED_FILE>
bool mapped_file_controller<FileType, MAPPED_FILE>::file_read_mapped()
{

	if (stat(file_path, &file_status) != 0 || S_ISDIR(file_status.st_mode)) {
		throw std::runtime_error("File cannot check status");
		return false;
	}

	p_open_file = open(file_path, O_RDONLY);

	if (p_open_file == NULL) {
		throw std::runtime_error("File cannot open");
		return false;
	}

	return true;
}

template<typename FileType, typename MAPPED_FILE>
typename FileType::file_open_ptr &
mapped_file_controller<FileType, MAPPED_FILE>::get_popen_file()
{
	return p_open_file;
}

/*
template<typename FileType, typename MAPPED_FILE>
struct stat    *mapped_file_controller<FileType, MAPPED_FILE>::get_file_status() {
return &file_status;
}
*/


template<typename FileType, typename MAPPED_FILE>
bool mapped_file_controller<FileType, MAPPED_FILE>::set_filepath(char const *file_path)
{
	this->file_path = file_path;

	if (this->file_path != NULL)
		return true;

	return false;
}

template<typename FileType, typename MAPPED_FILE>
typename FileType::file_ptr *mapped_file_controller<FileType, MAPPED_FILE>::get_file() const
{
	return p_file;
}

template<typename FileType, typename MAPPED_FILE>
bool mapped_file_controller<FileType, MAPPED_FILE>::close_file()
{
	close(p_open_file);
	return true;
}

template<typename FileType, typename MAPPED_FILE>
bool  mapped_file_controller<FileType, MAPPED_FILE>::
mapped_file(std::list<std::string> file_name,
std::vector<MAPPED_FILE *> mapped_vec,
mapped_file_controller<FileType, MAPPED_FILE>& file_offset_object){

	std::vector<const char*>::iterator iter_files;

	mapped_vec_shared = boost::make_shared<std::vector<MAPPED_FILE * > >();

	const char *file_name;
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
				throw file_system_excep::offset_exception("[** File is null **]");


			LOG(INFO) << "File path for mmaped " << s_file_name;

			//Set file name to mapped structure

			file_name = s_file_name.c_str();

		}
		catch (file_system_excep::offset_exception& offset_excep) {
			LOG(INFO) << "Error, file offset",
				<< offset_excep.message_error_file_is_null();
			continue;
		}

		if (file_offset_object.set_filepath(file_name)) {

			if (!file_offset_object.file_read_mapped()) {
				throw file_system_excep
					::offset_exception("[** File cannot open path **]");
			}

			mapped_file_ptr = mapped_vec.at(std::distance(file_name_vec.begin(), iter_files));
			try {
				if (mapped_file_ptr == NULL) {
					throw file_system_excep
						::offset_exception("[** Mapped pointer is null. **]");
				}

				struct stat *file_status = file_status;// = file_offset_object.get_file_status();

				mapped_file_ptr->size = file_status->st_size;

				mapped_file_ptr->file = file_offset_object.get_popen_file();

				LOG(INFO) << "Mapped file ptr size  " << mapped_file_ptr->size;

				LOG(INFO) << "Mapped file ptr name  " << mapped_file_ptr->file;

				if (mapped_file_ptr->size == 0 || mapped_file_ptr->file == -1) {
					throw file_system_excep::offset_exception("[** File size don't get status **]");
				}
				//allocated size of file name. 
				mapped_file_ptr->file_name = (char*)malloc(sizeof(char*)* s_file_name.size());
				//insert file name path.
				mapped_file_ptr->file_name = s_file_name.c_str();

				mapped_file_ptr->data = (uint8_t *)mmap(0,
					mapped_file_ptr->size,
					PROT_READ,
					MAP_SHARED,// MAP_PRIVED, it's not changed/shared.
					mapped_file_ptr->file,
					0);

				mapped_vec_shared->push_back(mapped_file_ptr);

				if (mapped_file_ptr->data == MAP_FAILED) {
					throw file_system_excep
						::offset_exception("[** File cannot map **]");
					file_offset_object.close_file();
				}

			}
			catch (file_system_excep::offset_exception& offset_excep) {
				LOG(INFO) << "Error, Mapped file" <<
					offset_excep.message_error_file_is_null();
				continue;

			}
		}
	}
	file_name_vec.clear(); // clear file name on list
	return true;


}
