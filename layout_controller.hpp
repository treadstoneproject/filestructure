#ifndef FILESTRUCTURE_LAYOUT_CONTROLLER_HPP
#define FILESTRUCTURE_LAYOUT_CONTROLLER_HPP

template<typename HeaderFile, typename MappedFileLayout>
class layout_controller{

	public:

			virtual std::vector<HeaderFile *> &   
				get_offset(std::vector<MappedFileLayout *> *mapped_file_vec) = 0;

			virtual bool
				pre_scan_layout(std::vector<MappedFileLayout *> *mapped_file_vec)  = 0;	
};

#endif /* FILESTRUCTURE_LAYOUT_HPP */
