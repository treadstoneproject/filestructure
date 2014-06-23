#ifndef FILESTRUCTURE_LAYOUT_CONTROLLER_HPP
#define FILESTRUCTURE_LAYOUT_CONTROLLER_HPP

template<typename HeaderFile, typename MAPPED_FILE>
class layout_controller{

	public:

			virtual std::map<uint64_t, HeaderFile> 
				get_header(std::vector<MAPPED_FILE *> *mapped_file_vec) = 0;

			virtual std::vector<MAPPED_FILE *> &   
				get_offset(std::vector<MAPPED_FILE *> *mapped_file_vec) = 0;

			virtual std::vector<MAPPED_FILE *> &
				pre_scan_layout(std::vector<MAPPED_FILE *> *mapped_file_vec)  = 0;	
};

#endif /* FILESTRUCTURE_LAYOUT_HPP */
