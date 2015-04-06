#ifndef FILESTRUCTURE_LAYOUT_CONTROLLER_HPP
#define FILESTRUCTURE_LAYOUT_CONTROLLER_HPP

namespace filestructure
{

    template<typename HeaderFile, typename MappedFileLayout>
    class layout_controller
    {

        public:

            virtual std::vector<HeaderFile *>&
            get_offset(std::vector<MappedFileLayout *> *mapped_file_vec) = 0;

            virtual bool
            pre_scan_layout(std::vector<MappedFileLayout *> *mapped_file_vec)  = 0;
    };

		template class layout_controller<struct IMAGE_NT_HEADERS_EXT, struct MAPPED_FILE_PE>;

}

#endif /* FILESTRUCTURE_LAYOUT_HPP */
