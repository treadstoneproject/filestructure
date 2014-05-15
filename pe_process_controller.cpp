#include "pe_process_controller.h"
#include "boost\make_shared.hpp"
#include "common.h"


template<typename MAPPED_FILE>
std::vector<struct IMAGE_NT_HEADERS *>&
pe_process_controller<MAPPED_FILE>::get_pe_header(std::vector<MAPPED_FILE *> *mapped_file_vec)
{

	LOG(INFO)"Intial PE header, pe_file_controller<MAPPED_FILE>::get_pe_header...";
	LOG(INFO)"pe_file_controller<MAPPED_FILE>::get_pe_header, vector_size : " << boost::lexical_cast<std::string>(mapped_file_vec->size());

	// PE Header conntained vector. Controller pointer by shared_ptr
	boost::shared_ptr<std::vector<struct IMAGE_NT_HEADERS *> > mapped_vec_shared
		= boost::make_shared<std::vector<struct IMAGE_NT_HEADERS * > >();
	pe_header_vec_shared.push_back(mapped_vec_shared);

	PIMAGE_DOS_HEADER dos_header;
	IMAGE_DOS_HEADER * nt_header;
	size_t headers_size = 0;
	typename std::vector<MAPPED_FILE *>::iterator iter_mf_vec;
	MAPPED_FILE *mapped_file_ptr;

	for (iter_mf_vec = mapped_file_vec->begin();
		iter_mf_vec != mapped_file_vec->end();
		++iter_mf_vec) {
		mapped_file_ptr = *iter_mf_vec;

		if (*mapped_file_ptr->data < sizeof(struct IMAGE_DOS_HEADER)) {
			logger->write_info("Mappper data < IMAGE_DOS_HEADER");
			continue;
		}

		dos_header = (PIMAGE_DOS_HEADER)mapped_file_ptr->data;

		if (dos_header->e_magic != IMAGE_DOS_SIGNATURE) {
			logger->write_info("Mapper e_mage != IMAGE_DOS_SIGNATURE");
			mapped_vec_shared->push_back(nt_header);
			continue;
		}

		if (dos_header->e_lfanew < 0) {
			logger->write_info("Mapper e_lfanew < 0");
			mapped_vec_shared->push_back(nt_header);
			continue;
		}

		headers_size = dos_header->e_lfanew + sizeof(nt_header->Signature) + sizeof(IMAGE_FILE_HEADER);

		LOG(INFO) << "pe_file_controller<MAPPED_FILE>::get_pe_header, Step 1) header size"<< boost::lexical_cast<std::string>(headers_size);

		if (mapped_file_ptr->size < headers_size) {
			logger->write_info("Mapper size < headers_size");
			mapped_vec_shared->push_back(nt_header);
			continue;
		}

		// completed type get header
		nt_header = (IMAGE_DOS_HEADER *)(mapped_file_ptr->data + dos_header->e_lfanew);

		headers_size += nt_header->FileHeader.SizeOfOptionalHeader;

		LOG(INFO) << "pe_file_controller<MAPPED_FILE>::get_pe_header, header size" << boost::lexical_cast<std::string>(headers_size);

		LOG(INFO) << "pe_file_controller<MAPPED_FILE>::get_pe_header, mapped_file_ptr->size" << boost::lexical_cast<std::string>(mapped_file_ptr->size);

		LOG(INFO) << "pe_file_controller<MAPPED_FILE>::get_pe_header, Signature" << boost::lexical_cast<std::string>(nt_header->Signature);

		if (nt_header->Signature == IMAGE_NT_SIGNATURE &&
			nt_header->FileHeader.Machine == IMAGE_FILE_MACHINE_I386 &&
			mapped_file_ptr->size > headers_size) {

			mapped_vec_shared->push_back(nt_header);

			logger->write_info_test("pe_file_controller<MAPPED_FILE>::get_pe_header, push back completed");
		}

		//test only
		//mapped_vec_shared->push_back(nt_header);

	}

	LOG(INFO)"pe_file_controller<MAPPED_FILE>::get_pe_header, return mapped_vec_shared" <<
		boost::lexical_cast<std::string>(mapped_vec_shared->size());

	return *mapped_vec_shared;
}


template<typename MAPPED_FILE>
uint8_t pe_file_controller<MAPPED_FILE>::retrive_offset_lite(
	std::vector<MAPPED_FILE *> pe_map_vec_ptr,
	std::vector<struct IMAGE_NT_HEADERS *> pe_header)const
{
	int count_offset;
	int count_section;

	PIMAGE_SECTION_HEADER section;
	PIMAGE_NT_HEADERS nt_header;
	struct IMAGE_NT_HEADERS_EXT *nt_headers_ext;
	MAPPED_FILE *pe_map_ptr;

	typename std::vector<struct IMAGE_NT_HEADERS *>::iterator iter_pe_header;
	//calculate rva
	uint64_t rva_block_;
	size_t buffer_length_;

	for (iter_pe_header = pe_header.begin();
		iter_pe_header != pe_header.end();
		++iter_pe_header) {
		nt_header = *iter_pe_header;

		// pe_map_vec_ptr(File mapped) gurantee size of containing equal pe_header(Header)
		pe_map_ptr = pe_map_vec_ptr.at(std::distance(pe_header.begin(), iter_pe_header));

		rva_block_ = nt_header->OptionalHeader.AddressOfEntryPoint;
		buffer_length_ = pe_map_ptr->size - ((uint8_t *)&nt_header - pe_map_ptr->data);

		nt_headers_ext = new struct IMAGE_NT_HEADERS_EXT;
		nt_headers_ext->rva_block = rva_block_;
		nt_headers_ext->size_block = buffer_length_;

		section = IMAGE_FIRST_SECTION(nt_header);
		count_offset = 0;

		while (count_offset < MIN(nt_header->FileHeader.NumberOfSections, 60)) {
			if ((uint8_t *)&section -
				(uint8_t *)&nt_header + sizeof(IMAGE_SECTION_HEADER) < pe_map_ptr->size) {
				if (nt_headers_ext->rva_block >= section->VirtualAddress &&
					nt_headers_ext->rva_block < section->VirtualAddress +
					section->SizeOfRawData) {
					uint64_t pe_offset_start = section->PointerToRawData + \
						(nt_headers_ext->rva_block - section->VirtualAddress);
					nt_headers_ext->offset = pe_offset_start;
					pe_offset_vec_shared_ptr->push_back(nt_headers_ext);
				}
			}

		}
	}

	if (pe_offset_vec_shared_ptr->size() == 0)
		return 0;

	return 1;
}


template<typename MAPPED_FILE>
struct IMAGE_NT_HEADERS_EXT& pe_file_controller<MAPPED_FILE>::retrive_offset(
	MAPPED_FILE *pe_map_ptr,
	IMAGE_NT_HEADERS *pe_header)const {

	boost::shared_ptr<struct IMAGE_NT_HEADERS_EXT>
		nth_ext_shared_ptr = boost::make_shared<struct IMAGE_NT_HEADERS_EXT>();

	PIMAGE_SECTION_HEADER section;
	//PIMAGE_NT_HEADERS nt_header = pe_header;
	struct IMAGE_NT_HEADERS_EXT *nt_headers_ext;

	int count_offset;
	int count_section;

	section = IMAGE_FIRST_SECTION(pe_header);
	count_offset = 0;


	LOG(INFO) << "pe_file_controller::retrive_offset,pe_header->OptionalHeader32.AddressOfEntryPoint" 
		<<boost::lexical_cast<std::string>(pe_header->OptionalHeader.AddressOfEntryPoint);

	//calculate block
	nth_ext_shared_ptr->rva_block = pe_header->OptionalHeader.AddressOfEntryPoint;
	nth_ext_shared_ptr->size_block = pe_map_ptr->size - ((uint8_t *)pe_header - pe_map_ptr->data);

	LOG(INFO) << "RVA_BLOCK, pe_header->OptionalHeader.AddressOfEntryPoint : " << pe_header->OptionalHeader.AddressOfEntryPoint;


	while (count_offset < MIN(pe_header->FileHeader.NumberOfSections, 60)) {
		if ((uint8_t *)section - \
			(uint8_t *)pe_header + sizeof(IMAGE_SECTION_HEADER) < pe_map_ptr->size) {
			if (nth_ext_shared_ptr->rva_block >= section->VirtualAddress &&
				nth_ext_shared_ptr->rva_block < section->VirtualAddress + section->SizeOfRawData) {
				uint64_t pe_offset_start = section->PointerToRawData +
					(nth_ext_shared_ptr->rva_block - section->VirtualAddress);

				logger->write_info_test("section->PointerToRawData", boost::lexical_cast<std::string>(section->PointerToRawData));
				logger->write_info_test("nth_ext_shared_ptr->rva_block", boost::lexical_cast<std::string>(nth_ext_shared_ptr->rva_block));
				logger->write_info_test("section->VirtualAddress", boost::lexical_cast<std::string>(section->VirtualAddress));

				nth_ext_shared_ptr->offset = pe_offset_start;
				nth_ext_shared_ptr->data_offset = pe_map_ptr->data;
				nth_ext_shared_ptr->size = pe_map_ptr->size;

				logger->write_info("pe_file_controller::retrive_offset, size \n",
					boost::lexical_cast<std::string>(nth_ext_shared_ptr->size));
				logger->write_info("pe_file_controller::retrive_offset, offset \n",
					boost::lexical_cast<std::string>(pe_offset_start));

				return *nth_ext_shared_ptr.get();
			}

			section++;
			count_offset++;
		}
		else {

			break;
		}

	}

	return *nth_ext_shared_ptr.get();
}

