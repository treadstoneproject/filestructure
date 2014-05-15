#ifndef FILESTRUCTURE_FILETYPE_H
#define FILESTRUCTURE_FILETYPE_H

namespace filestructure{

	template<typename MappedFileType,
		typename MappedFileLayout>
	class flietypes{
	public:

		virtual std::vector<MappedFileOutput*> &
			get_header_section(std::vector<MappedFileType *> *mapped_ftype_ptr_vec) = 0;

		virtual MappedFileLayout &
			retrive_offset(MappedFileType * map_ftype_ptr,
			MappedFileLayout * map_flayout_header) = 0;

		virtual std::vector<MappedFileLayout *>  retrive_offset_lite(
			std::vector<MappedFileType *>   map_ftype_ptr_vec,
			std::vector<MappedFileLayout *> map_flayout_ptr_vec) = 0;

	};

}


#endif // !FILESTRUCTURE_FILETYPE_H
