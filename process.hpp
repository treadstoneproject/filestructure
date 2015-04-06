#ifndef FILESTRUCTURE_PROCESS_HPP
#define FILESTRUCTURE_PROCESS_HPP

struct MEMORY_BLOCK {
    unsigned char          *data;
    size_t                  size;
    size_t                  base;
    struct MEMORY_BLOCK   *next;
};


#endif /* FILESTRUCTURE_PROCESS_HPP */
