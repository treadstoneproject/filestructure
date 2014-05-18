#ifndef FILESTRUCTURE_MAPPED_FILE_CONTROLLER_H
#define FILESTRUCTURE_MAPPED_FILE_CONTROLLER_H


#include "boost/iostreams/device/mapped_file.hpp"

//external
#include "boost/shared_ptr.hpp"
#include "boost/make_shared.hpp"

#include <list>
#include <vector>

#include "pe.h"



namespace filestructure{

	struct common_filetype;
	struct common_openfile_type;

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

	/*
	template<typename StructFileType, typename PointerType>
	struct common_stream_filetype {
		typedef StructFileType s_filetype;
		typedef std::streampos s_position;
		typedef PointerType file_ptr;
	};
	*/

	template<typename MAPPED_FILE>
	class mapped_file_controller{

	public:
		typedef std::vector<MAPPED_FILE *> map_file_vec;
		typedef boost::shared_ptr<map_file_vec> mapped_vec_ptr;

		
		mapped_file_controller();
		
		bool  mapped_file(std::vector<const char*> file_name_vec,
		std::vector<MAPPED_FILE *> mapped_vec);

		bool file_read();
		bool fread_mapped();
		bool set_filepath(char const *file_path);
		FILE *get_file() const;
		
		//struct stat *get_file_status();

		int & get_popen_file();
		bool close_file();
		

		bool get_file_status();

	private:

		//file handler
		
		FILE *p_file;
		int p_open_file;
		struct stat  file_status;
		const char *file_path;

		//mapped file handler
		mapped_vec_ptr mapped_vec_shared;

		MAPPED_FILE *mapped_file_ptr;

		boost::iostreams::mapped_file_source  mf_source;// (mf_params);

		

	};
}


#endif // !FILESTRUCTURE_MAPPED_FILE_CONTROLLER_H
