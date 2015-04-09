#ifndef FILESTRUCTURE_ELF_LAYOUT_CONTROLLER_HPP
#define FILESTRUCTURE_ELF_LAYOUT_CONTROLLER_HPP

#if   _WIN32
#include "pe.hpp"
#include "elf.hpp"
#include "layout_controller.hpp"
#include "logger/logging.hpp"
#elif __linux__
#include "filestructure/elf.h"
#include "filestructure/pe.h"
#include "filestructure/layout_controller.hpp"
#include "filestructure/logger/logging.hpp"
#endif

#include <vector>
#include <map>

namespace filestructure{

	template<typename HeaderFile,typename MappedFileLayout>
	class elf_layout_controller : public layout_controller<HeaderFile, MappedFileLayout>  {

	public:

		elf_layout_controller(std::vector<MappedFileLayout *> *mapped_file_vec);

		std::map<uint64_t,struct IMAGE_NT_HEADERS *> &
			get_header(std::vector<MappedFileLayout *> *mapped_file_vec);

		virtual std::vector<HeaderFile *>&
			get_offset(std::vector<MappedFileLayout *> *mapped_file_vec);

		/**
		* @brief Pre scan pe flie layout before send to post scanning.
		* Layout set status on MappedFileLayout structure in order to found/not found infected file.
		*
		* @param mapped_file_vec MappedFileLayout structure of file type.
		*
		* @return bool for check all file completed or not.
		*/
		virtual bool pre_scan_layout(std::vector<MappedFileLayout *> *mapped_file_vec);

	private:

		//retrive_offset_lite
		std::vector<HeaderFile *> elf_offset_vec;
		// file buffer

		std::map<uint64_t, struct IMAGE_NT_HEADERS* > header_file_map;

	};

}
#endif // !FILESTRUCTURE_ELF_LAYOUT_CONTROLLER_H
