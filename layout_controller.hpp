#ifndef FILESTRUCTURE_LAYOUT_CONTROLLER_HPP
#define FILESTRUCTURE_LAYOUT_CONTROLLER_HPP

template<typename HeaderFile, typename MappedFileLayout>
class layout_controller{

	public:

			virtual std::map<uint64_t, HeaderFile> 
				get_header(std::vector<MappedFileLayout *> *mapped_file_vec) = 0;

			virtual std::vector<MappedFileLayout *> &   
				get_offset(std::vector<MappedFileLayout *> *mapped_file_vec) = 0;

			virtual std::vector<MappedFileLayout *> &
				pre_scan_layout(std::vector<MappedFileLayout *> *mapped_file_vec)  = 0;	
};

#endif /* FILESTRUCTURE_LAYOUT_HPP */
