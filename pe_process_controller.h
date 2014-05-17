#ifndef FILESTRUCTURE_PE_PROCESS_CONTROLLER_H
#define FILESTRUCTURE_PE_PROCESS_CONTROLLER_H

//external library
#include "boost/shared_ptr.hpp"

#include "filetypes.h"

//standard lib
#include <vector>
#include <map>

//internal lib.
#include "pe.h"

namespace filestructure{


	template<typename MappedFileType, typename MappedFileLayout>
	class pe_process_controller : public flietypes<MappedFileType, MappedFileLayout>  {

	public:

		virtual std::vector<MappedFileLayout*> &
		get_header_section(std::vector<MappedFileType *> *mapped_ftype_ptr_vec) = 0;

		virtual MappedFileLayout &
			retrive_offset(MappedFileType * map_ftype_ptr,
			MappedFileLayout * map_flayout_header) = 0;

		virtual std::vector<MappedFileLayout *>
			retrive_offset_lite(
			std::vector<MappedFileType *>   map_ftype_ptr_vec,
			std::vector<MappedFileLayout *> map_flayout_ptr_vec) = 0;


	private:
		MappedFileLayout *image_nt_header;

		std::vector<boost::shared_ptr<std::vector<MappedFileLayout *> > > pe_header_vec_shared;
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


