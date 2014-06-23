#ifndef FILESTRUCTURE_PE_LAYOUT_CONTROLLER_HPP
#define FILESTRUCTURE_PE_LAYOUT_CONTROLLER_HPP

namespace filestructure{

template<typename MAPPED_FILE>
class pe_layout_controller : layout_controller<IMAGE_NT_HEADERS, MAPPED_FILE>
{

    public:

        virtual std::map<uint64_t, HeaderFile>
        get_header(std::vector<MAPPED_FILE *> *mapped_file_vec) = 0;

        virtual std::vector<MAPPED_FILE *>&
        get_offset(std::vector<MAPPED_FILE *> *mapped_file_vec) = 0;

        /**
        * @brief Pre scan pe flie layout before send to post scanning.
        * Layout set status on MAPPED_FILE structure in order to found/not found infected file.
        *
        * @param mapped_file_vec MAPPED_FILE structure of file type.
        *
        * @return bool for check all file completed or not.
        */
        virtual bool pre_scan_layout(std::vector<MAPPED_FILE *> *mapped_file_vec)  = 0;


    private:

        std::vector<MAPPED_FILE *> * mapped_file_vec_;

};



}



#endif /* FILESTRUCTURE_PE_LAYOUT_CONTROLLER_HPP */
