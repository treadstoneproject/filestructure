#ifndef FILESTRUCTURE_MAPPED_FILE_CONTROLLER_H
#define FILESTRUCTURE_MAPPED_FILE_CONTROLLER_H

//external
#include "boost/shared_ptr.hpp"

#include <list>
#include <vector>

#include <sys/types.h>
#include <sys/stat.h>

namespace filestructure{

	struct common_filetype {
		typedef FILE file_ptr;
		typedef int  file_open_ptr;
		typedef const char  const_char;
		typedef struct binary_type binary;
	};

	struct common_openfile_type{
		typedef int    file_ptr;
		typedef const char  const_char;
		typedef struct binary_type binary;
	};


	template<typename StructFileType, typename PointerType>
	struct common_stream_filetype {
		typedef StructFileType s_filetype;
		typedef std::streampos s_position;
		typedef PointerType file_ptr;
	};

	template<typename FileType = struct common_filetype,
		typename MAPPED_FILE = struct MAPPED_FILE_PE>
	class mapped_file_controller{
	public:
		typedef std::vector<MAPPED_FILE *> map_file_vec;
		typedef boost::shared_ptr<map_file_vec> mapped_vec_ptr;


		bool  mapped_file(std::list<std::string> file_name,
		std::vector<MAPPED_FILE *> mapped_vec,
		mapped_file_controller<FileType, MAPPED_FILE>& file_offset_object);

		bool file_read();
		bool file_read_mapped();
		bool set_filepath(char const *file_path);
		typename FileType::file_ptr *get_file() const;
		
		//struct stat *get_file_status();

		typename FileType::file_open_ptr & get_popen_file();
		bool close_file();

	private:

		//file handler
		typename FileType::file_ptr *p_file;
		typename FileType::file_open_ptr p_open_file;
		struct stat  file_status;
		const char *file_path;

		//mapped file handler
		mapped_vec_ptr mapped_vec_shared;

		MAPPED_FILE *mapped_file_ptr;



	};
}


#endif // !FILESTRUCTURE_MAPPED_FILE_CONTROLLER_H
