#ifndef FILESTRUCTURE_ELF_LAYOUT_CONTROLLER_H
#define FILESTRUCTURE_ELF_LAYOUT_CONTROLLER_H

#include "elf.h"
//#include "filetypes.h"
#include <vector>
namespace filestructure{

	template<typename MappedFileType,typename MappedFileLayout>
	class elf_layout_controller : public flietypes<MappedFileType, MappedFileLayout>  {

	public:
		
		virtual std::vector<MappedFileLayout*> &
			get_header_section(std::vector<MappedFileType *> *mapped_ftype_ptr_vec); 

		virtual MappedFileLayout &
			retrive_offset(MappedFileType * map_ftype_ptr,
			MappedFileLayout * map_flayout_header);

		virtual std::vector<MappedFileLayout *>
			retrive_offset_lite(
			std::vector<MappedFileType *>   map_ftype_ptr_vec,
			std::vector<MappedFileLayout *> map_flayout_ptr_vec);
	     
		bool get_file_support();

	};

}
#endif // !FILESTRUCTURE_ELF_LAYOUT_CONTROLLER_H
