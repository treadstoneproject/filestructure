


#include "boost/make_shared.hpp"

#include <vector>

#include "filestructure/elf_layout_controller.hpp"

using namespace filestructure;

template<typename HeaderFile, typename MappedFileLayout>
std::map<uint64_t, IMAGE_NT_HEADERS *>& elf_layout_controller<HeaderFile, MappedFileLayout>::
	get_header(std::vector<MappedFileLayout *> *mapped_ftype_ptr_vec)
{
	return header_file_map;
}


template<typename HeaderFile, typename MappedFileLayout>
std::vector<HeaderFile *>&
	elf_layout_controller<HeaderFile, MappedFileLayout>::
	get_offset(std::vector<MappedFileLayout *> *pe_map_vec_ptr)
{
	  
	return elf_offset_vec;
}

template<typename HeaderFile, typename MappedFileLayout>
elf_layout_controller<HeaderFile, MappedFileLayout>::
	elf_layout_controller(std::vector<MappedFileLayout *> *mapped_file_vec)
{

	
}



//Why compile pass.
template class elf_layout_controller<struct MAPPED_FILE_PE, struct MAPPED_FILE_PE>;

#if __linux__
template class elf_layout_controller<struct MAPPED_FILE_PE, struct MAPPED_FILE_PE>;
#endif // !LINUX
