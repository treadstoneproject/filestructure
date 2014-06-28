/*
* Copyright 2014 MTSec, Inc.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/*  Titles			                                          Authors	         Date
 * -Intial support PE flie type.                          R.Chatsiri       27/06/2014
 */

#include "boost/make_shared.hpp"
#include "filestructure/pe_layout_controller.hpp"

using namespace filestructure;

template<typename HeaderFile, typename MappedFileLayout>
std::map<uint64_t, IMAGE_NT_HEADERS *>& pe_layout_controller<HeaderFile, MappedFileLayout>::
get_header(std::vector<MappedFileLayout *> *mapped_ftype_ptr_vec)
{
    LOG(INFO) << "Intial PE header, pe_file_controller<MAPPED_FILE>::get_pe_header...";
    LOG(INFO) << "get_pe_header, vector_size : " << mapped_ftype_ptr_vec->size();

    typedef std::pair<uint64_t, struct IMAGE_NT_HEADERS *>  hmap_pair;
    PIMAGE_DOS_HEADER dos_header;
    PIMAGE_NT_HEADERS nt_header;
    size_t headers_size = 0;
    typename std::vector<MappedFileLayout *>::iterator iter_mf_vec;
    MappedFileLayout *mapped_file_ptr;

    for (iter_mf_vec = mapped_ftype_ptr_vec->begin();
            iter_mf_vec != mapped_ftype_ptr_vec->end();
            ++iter_mf_vec) {

        mapped_file_ptr = *iter_mf_vec;
        uint64_t fmd5 = mapped_file_ptr->file_map_md5;

        nt_header = new IMAGE_NT_HEADERS;

        if (*mapped_file_ptr->data < sizeof(struct IMAGE_DOS_HEADER)) {
            LOG(INFO) << "Mappper data < IMAGE_DOS_HEADER";
            continue;
        }

        dos_header = (PIMAGE_DOS_HEADER)mapped_file_ptr->data;

        if (dos_header->e_magic != IMAGE_DOS_SIGNATURE) {
            LOG(INFO) << "Mapper e_mage != IMAGE_DOS_SIGNATURE";
            header_file_map.insert(hmap_pair(fmd5, nt_header));

            continue;
        }

        if (dos_header->e_lfanew < 0) {
            LOG(INFO) << "Mapper e_lfanew < 0";
            header_file_map.insert(hmap_pair(fmd5, nt_header));

            continue;
        }

        headers_size = dos_header->e_lfanew + sizeof(nt_header->Signature) + sizeof(IMAGE_FILE_HEADER);

        LOG(INFO) << "Step 1) header size" << headers_size;

        if (mapped_file_ptr->size < headers_size) {
            LOG(INFO) << "Mapper size < headers_size";
            header_file_map.insert(hmap_pair(fmd5, nt_header));
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
            header_file_map.insert(hmap_pair(fmd5, nt_header));
            LOG(INFO) << "push back completed";
        }

    }

    LOG(INFO) << "Header_file_map return header file contains in vector size :" << header_file_map.size();
    return header_file_map;
}


template<typename HeaderFile, typename MappedFileLayout>
std::vector<HeaderFile *>&
pe_layout_controller<HeaderFile, MappedFileLayout>::
get_offset(std::vector<MappedFileLayout *> *pe_map_vec_ptr)
{
    LOG(INFO) << "Start Get offset file for checking post infected file.";

    int count_offset;
    int count_section;

    PIMAGE_SECTION_HEADER section;
    PIMAGE_NT_HEADERS  nt_header;
    struct IMAGE_NT_HEADERS_EXT *nt_headers_ext;
    MappedFileLayout *pe_map_ptr;

    typename std::vector<IMAGE_NT_HEADERS *>::iterator iter_pe_header;
    //calculate rva
    uint64_t rva_block_;
    size_t   buffer_length_;

    typename std::vector<MappedFileLayout *>::iterator iter_pe_map_vptr;

    for(iter_pe_map_vptr = pe_map_vec_ptr->begin();
            iter_pe_map_vptr != pe_map_vec_ptr->end();
            ++iter_pe_map_vptr) {
        pe_map_ptr  = *iter_pe_map_vptr;

        if(pe_map_ptr->file_map_md5 == 0) {
            LOG(INFO) << "File not initial MD5 of file in pre scanning";
        }

				pe_offset_vec_sptr = boost::make_shared<std::vector<HeaderFile *> >(pe_map_vec_ptr->size());
        //File Map MD5 for
        std::map<uint64_t, IMAGE_NT_HEADERS *>::iterator iter_header_file =
                header_file_map.find(pe_map_ptr->file_map_md5);
        std::pair<uint64_t, IMAGE_NT_HEADERS *>  header_file_pair = *iter_header_file;

        if(header_file_pair.second) {
            nt_header = header_file_pair.second;

            rva_block_     = nt_header->OptionalHeader.AddressOfEntryPoint;
            buffer_length_ = pe_map_ptr->size -((uint8_t *)&nt_header - pe_map_ptr->data);

            LOG(INFO) << "PE rva_block_ : " << rva_block_;
            LOG(INFO) << "PE buffer_length_ : " << buffer_length_;

            nt_headers_ext = new struct IMAGE_NT_HEADERS_EXT;
            nt_headers_ext->rva_block  = rva_block_;
            nt_headers_ext->size_block = buffer_length_;

            section = IMAGE_FIRST_SECTION(nt_header);
            count_offset = 0;
						DWORD section_rva;

            while(count_offset < MIN(nt_header->FileHeader.NumberOfSections, 60)) {
                if((uint8_t *)&section -
                        (uint8_t *)&nt_header + sizeof(IMAGE_SECTION_HEADER) < pe_map_ptr->size) {

                    if(nt_headers_ext->rva_block >= section->VirtualAddress &&
                       section_rva < section->VirtualAddress) {

												nt_headers_ext->section_rva    = section->VirtualAddress;
												nt_headers_ext->section_offset = section->PointerToRawData;
 
                        nt_headers_ext->data_offset = pe_map_ptr->data;// Data str from file.
                        nt_headers_ext->size        = pe_map_ptr->size;// Size of file.

                        pe_offset_vec_sptr->push_back(	nt_headers_ext );

												LOG(INFO) << "PointerToRawData: " <<  nt_headers_ext->section_offset;
												LOG(INFO) << "VirtualAddress  : " << nt_headers_ext->section_rva;
                        LOG(INFO) << "Offset data  : "  << nt_headers_ext->data_offset;
                        LOG(INFO) << "Size of data : "  << nt_headers_ext->size;
												break;
                    }//if
										section++;
                    count_offset++;
                }//if

            }//while

        } else {
            LOG(INFO) << "File name : " << pe_map_ptr->file_name <<", Not MD5 initial part. ";
        }//else
    }// for

}

template<typename HeaderFile, typename MappedFileLayout>
bool pe_layout_controller<HeaderFile, MappedFileLayout>::
pre_scan_layout(std::vector<MappedFileLayout *> *mapped_file_vec)
{

    return true;
}


//Why compile pass.
template class pe_layout_controller<struct IMAGE_NT_HEADERS_EXT, struct MAPPED_FILE_PE>;
