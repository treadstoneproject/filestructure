#ifndef FILESTRUCTURE_PE_PROCESS_CONTROLLER_H
#define FILESTRUCTURE_PE_PROCESS_CONTROLLER_H

#include "boost/shared_ptr.hpp"

#include <vector>
#include <map>

#include "pe.h"

namespace filestructure{


	template<typename MAPPED_FILE ,typename MappedFileLayout>
	class pe_process_controller  {


	public:
		std::vector<struct IMAGE_NT_HEADERS *>& get_pe_header(std::vector<MAPPED_FILE *> *mapped_file_vec){ }

		uint8_t  retrive_offset_lite(
			std::vector<MAPPED_FILE *> pe_map_vec_ptr,
			std::vector<struct IMAGE_NT_HEADERS *> pe_header){}

		struct IMAGE_NT_HEADERS_EXT& retrive_offset(
			MAPPED_FILE *pe_map_ptr,
			IMAGE_NT_HEADERS *pe_header)const{}




	private:
		IMAGE_NT_HEADERS *image_nt_header;

		std::vector<boost::shared_ptr<std::vector<struct IMAGE_NT_HEADERS *> > > pe_header_vec_shared;
		//retrive_offset_lite
		boost::shared_ptr<std::vector<struct IMAGE_NT_HEADERS_EXT *> > pe_offset_vec_shared_ptr;
		// file buffer
		std::vector<uint8_t> file_buffer_vec;

		// add buffer and address of file.
		//std::vector<uint8_t*> file_buff_addr_vec;
		std::map<uint8_t*, size_t> file_buff_addr_map;

		//kernel file path
		std::string * kernel_file_path_ptr;

	};


}

#endif


