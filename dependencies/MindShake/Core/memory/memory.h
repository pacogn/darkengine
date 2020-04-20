#pragma once

#include <cstddef>
#include <cstdint>

//-------------------------------------
namespace MindShake {

    void *Malloc(size_t size);
    void Free(void *ptr);

    // align must be a power of 2
    void *AlignedMalloc(size_t size, size_t align);

    template <typename T> 
    void AlignedFree(T *&ptr) {
        if (ptr != nullptr) {
            Free(((void **) ptr)[-1]);
            ptr = nullptr;
        }
    }

} // end of namespace
