#ifndef FILESTRUCTURE_PE_LAYOUT_CONTROLLER_HPP
#define FILESTRUCTURE_PE_LAYOUT_CONTROLLER_HPP

//external library
#include "boost/shared_ptr.hpp"

#include "filetypes.h"

//standard lib
#include <vector>
#include <map>

//internal lib.
#include "pe.h"


namespace filestructure
{


    template<typename MappedFileLayout>
    class pe_layout_controller : layout_controller<IMAGE_NT_HEADERS, MappedFileLayout>
    {

        public:

            virtual std::map<uint64_t, HeaderFile>
            get_header(std::vector<MappedFileLayout *> *mapped_file_vec) = 0;

            virtual std::vector<MappedFileLayout *>&
            get_offset(std::vector<MappedFileLayout *> *mapped_file_vec) = 0;

            /**
            * @brief Pre scan pe flie layout before send to post scanning.
            * Layout set status on MappedFileLayout structure in order to found/not found infected file.
            *
            * @param mapped_file_vec MappedFileLayout structure of file type.
            *
            * @return bool for check all file completed or not.
            */
            virtual bool pre_scan_layout(std::vector<MappedFileLayout *> *mapped_file_vec)  = 0;


        private:

            std::vector<MappedFileLayout *> *mapped_file_vec_;

            struct IMAGE_NT_HEADERS *image_nt_header;

            boost::shared_ptr<std::vector<MappedFileLayout *> >  pe_header_vec;
            //retrive_offset_lite
            boost::shared_ptr<std::vector<struct IMAGE_NT_HEADERS_EXT *> > pe_offset_vec_sptr;
            // file buffer
            std::vector<uint8_t> file_buffer_vec;

            // add buffer and address of file.
            std::map<uint8_t *, size_t> file_buff_addr_map;


    };



}



#endif /* FILESTRUCTURE_PE_LAYOUT_CONTROLLER_HPP */
