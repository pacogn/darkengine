#include "memory.h"
//-------------------------------------
#include <cstdlib>
#include <string.h>

namespace MindShake {

    //---------------------------------
    void *
    Malloc(size_t size) {
        return malloc(size);
    }

    //---------------------------------
    void 
    Free(void *ptr) {
        free(ptr);
    }

    //---------------------------------
    static inline size_t
    NextPowerOfTwo(size_t  _val) {
        _val = _val - 1;
        _val |= (_val >>  1);
        _val |= (_val >>  2);
        _val |= (_val >>  4);
        _val |= (_val >>  8);
        _val |= (_val >> 16);

        return _val + 1;
    }

    //---------------------------------
    void *
    AlignedMalloc(size_t size, size_t align) {
        void        *pOrig;
        void        **pAlign;
        ptrdiff_t   offset;
    
        align = NextPowerOfTwo(align) - 1;
        offset = align + sizeof(void *);
        if ((pOrig = (void *) malloc(size + offset)) == nullptr) {
           return nullptr;
        }

        pAlign = (void **) ((size_t(pOrig) + offset) & ~align);
        pAlign[-1] = pOrig;
    
        return pAlign;
    }

} // end of namespace