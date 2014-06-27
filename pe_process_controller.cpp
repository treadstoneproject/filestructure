#include "boost/make_shared.hpp"

#include "common.h"
#include "pe_process_controller.h"
#include "logger/logging.h"



using namespace filestructure;


template<typename MappedFileType,
	typename MappedFileLayout>
	std::vector<MappedFileLayout*> &
	pe_process_controller<MappedFileType, MappedFileLayout>::
	get_header_section(std::vector<MappedFileType *> *mapped_ftype_ptr_vec){
		LOG(INFO) << "Intial PE header, pe_file_controller<MAPPED_FILE>::get_pe_header...";
		LOG(INFO) << "get_pe_header, vector_size : " << mapped_ftype_ptr_vec->size();

		// PE Header conntained vector. Controller pointer by shared_ptr
		boost::shared_ptr<std::vector<MappedFileLayout *> > mapped_vec_shared
			= boost::make_shared<std::vector<MappedFileLayout * > >();
		pe_header_vec_shared.push_back(mapped_vec_shared);

		PIMAGE_DOS_HEADER dos_header;
		PIMAGE_NT_HEADERS nt_header;
		size_t headers_size = 0;
		typename std::vector<MappedFileType *>::iterator iter_mf_vec;
		MappedFileType *mapped_file_ptr;

		for (iter_mf_vec = mapped_ftype_ptr_vec->begin();
			iter_mf_vec != mapped_ftype_ptr_vec->end();
			++iter_mf_vec) {
			mapped_file_ptr = *iter_mf_vec;

			if (*mapped_file_ptr->data < sizeof(struct IMAGE_DOS_HEADER)) {
				LOG(INFO) << "Mappper data < IMAGE_DOS_HEADER";
				continue;
			}

			dos_header = (PIMAGE_DOS_HEADER)mapped_file_ptr->data;

			if (dos_header->e_magic != IMAGE_DOS_SIGNATURE) {
				LOG(INFO) << "Mapper e_mage != IMAGE_DOS_SIGNATURE";
				mapped_vec_shared->push_back(nt_header);
				continue;
			}

			if (dos_header->e_lfanew < 0) {
				LOG(INFO) << "Mapper e_lfanew < 0";
				mapped_vec_shared->push_back(nt_header);
				continue;
			}

			headers_size = dos_header->e_lfanew + sizeof(nt_header->Signature) + sizeof(IMAGE_FILE_HEADER);

			LOG(INFO) << "Step 1) header size" << headers_size;

			if (mapped_file_ptr->size < headers_size) {
				LOG(INFO) << "Mapper size < headers_size";
				mapped_vec_shared->push_back(nt_header);
				continue;
			}

			// completed type get header
			nt_header = (PIMAGE_NT_HEADERS)(mapped_file_ptr->data + dos_header->e_lfanew);

			headers_size += nt_header->FileHeader.SizeOfOptionalHeader;

			LOG(INFO) << "header size" <<headers_size;

			LOG(INFO) << "mapped_file_ptr->size" << mapped_file_ptr->size;

			LOG(INFO) << "Signature" << nt_header->Signature;

			if (nt_header->Signature == IMAGE_NT_SIGNATURE &&
				nt_header->FileHeader.Machine == IMAGE_FILE_MACHINE_I386 &&
				mapped_file_ptr->size > headers_size) {
				mapped_vec_shared->push_back(nt_header);

				LOG(INFO) << "push back completed";
			}

		}

		LOG(INFO) << "return mapped_vec_shared" << mapped_vec_shared->size();

		return *mapped_vec_shared;
	}


template<typename MappedFileType,
	typename MappedFileLayout>
	MappedFileLayout &
	pe_process_controller<MappedFileType, MappedFileLayout>::
	retrive_offset(MappedFileType * map_ftype_ptr,
	MappedFileLayout * map_flayout_header){
		return *map_flayout_header;
	}

template<typename MappedFileType,
	typename MappedFileLayout>
	std::vector<MappedFileLayout *>
	pe_process_controller<MappedFileType, MappedFileLayout>::
	retrive_offset_lite(
	std::vector<MappedFileType *>   map_ftype_ptr_vec,
	std::vector<MappedFileLayout *> map_flayout_ptr_vec){
		return map_flayout_ptr_vec;
	}

 
//Why compile pass.
template class pe_process_controller<struct MAPPED_FILE_PE, struct IMAGE_NT_HEADERS>;