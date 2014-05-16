#include "elf_process_controller.h"
#include <vector>
#include "pe.h"

using namespace filestructure;

template<typename MappedFileType,
	typename MappedFileLayout>
	virtual std::vector<MappedFileLayout*> &
	  elf_process_controller<MappedFileType, MappedFileLayout>::
	get_header_section(std::vector<MappedFileType *> *mapped_ftype_ptr_vec){
		std::vector<MappedFileLayout*> mapf_layout_vec;
		return mapf_layout_vec;
	}


template<typename MappedFileType,
	typename MappedFileLayout>
	virtual MappedFileLayout &
	elf_process_controller<MappedFileType, MappedFileLayout>::
	retrive_offset(MappedFileType * map_ftype_ptr,
	MappedFileLayout * map_flayout_header){

	}

template<typename MappedFileType,
	typename MappedFileLayout>
	virtual std::vector<MappedFileLayout *>  
	elf_process_controller<MappedFileType, MappedFileLayout>::
	retrive_offset_lite(
	std::vector<MappedFileType *>   map_ftype_ptr_vec,
	std::vector<MappedFileLayout *> map_flayout_ptr_vec){

	}

template<typename MappedFileType,
	typename MappedFileLayout> 
	bool elf_process_controller<MappedFileType, MappedFileLayout>::get_file_support(){ return true; }


#if LINUX
template class elf_process_controller<struct MAPPED_FILE_PE, struct MAPPED_FILE_PE>;
#endif // !LINUX