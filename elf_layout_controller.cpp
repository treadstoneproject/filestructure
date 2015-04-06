

#include <vector>

#include "filestructure/elf_layout_controller.h"

using namespace filestructure;

template<typename MappedFileType,
         typename MappedFileLayout>
std::vector<MappedFileLayout *>&
elf_process_controller<MappedFileType, MappedFileLayout>::
get_header_section(std::vector<MappedFileType *> *mapped_ftype_ptr_vec)
{
    std::vector<MappedFileLayout *> mapf_layout_vec;
    return mapf_layout_vec;
}


template<typename MappedFileType,
         typename MappedFileLayout>
MappedFileLayout&
elf_process_controller<MappedFileType, MappedFileLayout>::
retrive_offset(MappedFileType *map_ftype_ptr,
        MappedFileLayout *map_flayout_header)
{
    return *map_flayout_header;
}

template<typename MappedFileType,
         typename MappedFileLayout>
std::vector<MappedFileLayout *>
elf_process_controller<MappedFileType, MappedFileLayout>::
retrive_offset_lite(
        std::vector<MappedFileType *>   map_ftype_ptr_vec,
        std::vector<MappedFileLayout *> map_flayout_ptr_vec)
{
    return map_flayout_ptr_vec;
}

template<typename MappedFileType,
         typename MappedFileLayout>
bool elf_process_controller<MappedFileType, MappedFileLayout>::get_file_support()
{
    LOG(INFO) << "get_file_support initial \n";
    return true;
}


//Why compile pass.
template class elf_process_controller<struct MAPPED_FILE_PE, struct MAPPED_FILE_PE>;

#if LINUX
template class elf_process_controller<struct MAPPED_FILE_PE, struct MAPPED_FILE_PE>;
#endif // !LINUX
