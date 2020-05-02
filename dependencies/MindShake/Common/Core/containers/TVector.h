#pragma once

//-------------------------------------
// Copyright (c) 2010 - now - Carlos Aragonés @ Lucera Project 
//-------------------------------------
// Permission is hereby granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software"), to deal 
// in the Software without restriction, including without limitation the rights 
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
// copies of the Software, and/to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in 
// all copies or substantial portions of the Software.
//-------------------------------------
// Version 0.2: C++11 (beta)
// Version 0.1: C++98
//-------------------------------------

//-------------------------------------
#include <cstdint>
#include <vector>
#include <algorithm>
#include <functional>
//-------------------------------------

using std::function;

//-------------------------------------
namespace MindShake
{

    //---------------------------------
    template <typename Type>
    class TVector
    {
        public:
            typedef std::vector<Type>                       vector;
            typedef TVector<Type>                           tvector;

            typedef typename vector::value_type             value_type;

            typedef typename vector::pointer                pointer;
            typedef typename vector::const_pointer          const_pointer;

            typedef typename vector::reference              reference;
            typedef typename vector::const_reference        const_reference;

            typedef typename vector::iterator               iterator;
            typedef typename vector::const_iterator         const_iterator;

            typedef typename vector::reverse_iterator       reverse_iterator;
            typedef typename vector::const_reverse_iterator const_reverse_iterator;

            typedef typename vector::size_type              size_type;

            // short names
            typedef typename vector::iterator               it;
            typedef typename vector::const_iterator         c_it;

            typedef typename vector::reverse_iterator       r_it;
            typedef typename vector::const_reverse_iterator c_r_it;

            typedef typename vector::reference              ref;
            typedef typename vector::const_reference        c_ref;

        public:
            inline              TVector() noexcept                              : mData()            { }
            inline explicit     TVector(size_type size)                         : mData(size)        { }
            inline              TVector(size_type size, const Type &vec)        : mData(size, vec)   { }
            inline              TVector(c_it first, c_it last)                  : mData(first, last) { }

            inline              TVector(const tvector &vec)                     : mData(vec.mData)   { }
            inline              TVector(const vector &vec)                      : mData(vec.mData)   { }

            inline              TVector(TVector &&vec) noexcept                 : mData(std::move(vec.mData)) { }
            inline              TVector(vector  &&vec) noexcept                 : mData(std::move(vec))       { }

            inline              TVector(std::initializer_list<Type> list)       : mData(list)        { }

            virtual             ~TVector()                                      { }

            inline tvector &    operator =(const tvector &vec)                  { mData = vec.mData; return *this;  }
            inline tvector &    operator =(const vector &vec)                   { mData = vec;       return *this;  }

            inline tvector &    operator =(const tvector &&vec) noexcept        { mData = std::move(vec.mData); return *this; }
            inline tvector &    operator =(const vector  &&vec) noexcept        { mData = std::move(vec);       return *this; }

            inline tvector &    operator =(std::initializer_list<Type> list)    { mData = list; return *this;       }

            inline tvector &    assign(c_it first, c_it last)                   { mData.assign(first, last); return *this;  }
            inline tvector &    assign(size_type size, const Type &value)       { mData.assign(size, value); return *this;  }
            inline tvector &    assign(std::initializer_list<Type> list)        { mData.assign(list);        return *this;  }

            // Comparators
            inline bool         operator ==(const tvector &vec) const           { return mData == vec.mData;    }
            inline bool         operator ==(const vector  &vec) const           { return mData == vec;          }
            inline bool         operator !=(const tvector &vec) const           { return mData != vec.mData;    }
            inline bool         operator !=(const vector  &vec) const           { return mData != vec;          }
            inline bool         operator < (const tvector &vec) const           { return mData <  vec.mData;    }
            inline bool         operator < (const vector  &vec) const           { return mData <  vec;          }
            inline bool         operator <=(const tvector &vec) const           { return mData <= vec.mData;    }
            inline bool         operator <=(const vector  &vec) const           { return mData <= vec;          }
            inline bool         operator > (const tvector &vec) const           { return mData >  vec.mData;    }
            inline bool         operator > (const vector  &vec) const           { return mData >  vec;          }
            inline bool         operator >=(const tvector &vec) const           { return mData >= vec.mData;    }
            inline bool         operator >=(const vector  &vec) const           { return mData >= vec;          }

            // Iterators
            inline it           begin()                                         { return mData.begin();         }
            inline c_it         begin()   const                                 { return mData.begin();         }
            inline c_it         cbegin()  const                                 { return mData.cbegin();        }

            inline it           end()                                           { return mData.end();           }
            inline c_it         end()     const                                 { return mData.end();           }
            inline c_it         cend()    const                                 { return mData.cend();          }

            inline r_it         rbegin()                                        { return mData.rbegin();        }
            inline c_r_it       rbegin()  const                                 { return mData.rbegin();        }
            inline c_r_it       crbegin() const                                 { return mData.crbegin();       }

            inline r_it         rend()                                          { return mData.rend();          }
            inline c_r_it       rend()    const                                 { return mData.rend();          }
            inline c_r_it       crend()   const                                 { return mData.crend();         }

            // Element access
            inline ref          at(size_type idx)                               { return mData.at(idx);         }
            inline c_ref        at(size_type idx) const                         { return mData.at(idx);         }

            inline ref          operator [](size_type idx)                      { return mData[idx];            }
            inline c_ref        operator [](size_type idx) const                { return mData[idx];            }

            inline ref          front()                                         { return mData.front();         }
            inline c_ref        front() const                                   { return mData.front();         }

            inline ref          back()                                          { return mData.back();          }
            inline c_ref        back()  const                                   { return mData.back();          }

            inline Type *       data()                                          { return (mData.size() > 0) ? &mData[0] : 0x0;  }
            inline const Type * data() const                                    { return (mData.size() > 0) ? &mData[0] : 0x0;  }

            // Capacity
            inline bool         empty()    const                                { return mData.empty();         }
            inline size_type    size()     const                                { return mData.size();          }
            inline size_type    max_size() const                                { return mData.max_size();      }
            inline size_type    capacity() const                                { return mData.capacity();      }

            inline tvector &    reserve(size_type size)                         { mData.reserve(size);      return *this;   }

            inline tvector &    resize(size_type size)                          { mData.resize(size);       return *this;   }
            inline tvector &    resize(size_type size, const Type &vec)         { mData.resize(size, vec);  return *this;   }

            inline tvector &    shrink_to_fit()                                 { mData.shrink_to_fit();    return *this;   }

            // Modifiers
            inline tvector &    clear()                                         { mData.clear();            return *this;   }

            template <class... Args>
            inline it           emplace(c_it pos, Args &&... args)              { mData.emplace(pos, std::forward<Args>(args)...);  }

            inline it           insert(c_it pos, const Type &value = Type())          { return mData.insert(pos, value);        }
            inline it           insert(c_it pos, Type &&value)                        { return mData.insert(pos, value);        }
            inline it           insert(c_it pos, size_type size, const Type &value)   { return mData.insert(pos, size, vec);    }
            inline it           insert(c_it pos, c_it first, c_it last)               { return mData.insert(pos, first, last);  }
            inline it           insert(c_it pos, std::initializer_list<Type> list)    { return mData.insert(pos, list);         }

            inline it           erase(c_it pos, size_type size = 1)             { return mData.erase(pos, pos + size);  }
            inline it           erase(c_it first, c_it last)                    { return mData.erase(first, last);      }

            inline tvector &    push_back(const Type &value = Type())           { mData.push_back(value);            return *this;  }
            inline tvector &    push_back(const Type &&value)                   { mData.push_back(std::move(value)); return *this;  }

            inline tvector &    pop_back()                                      { mData.pop_back();                  return *this;  }

            template <class... Args>
            inline tvector &    emplace_back(Args &&... args)                   { mData.emplace_back(std::forward<Args>(args)...);  return *this; }

            inline tvector &    swap(tvector &vec)                              { return mData.swap(vec.mData); return *this;   }
            inline tvector &    swap(vector &vec)                               { return mData.swap(vec);       return *this;   }

            //-------------------------
            // Non standard methods
            //-------------------------
            inline              operator const vector & () const                { return mData;                 }
            inline              operator vector & ()                            { return mData;                 }

            //inline Type *       getPointer()                                    { return (mData.size() > 0) ? &mData[0] : 0x0;  }
            //inline const Type * getPointer() const                              { return (mData.size() > 0) ? &mData[0] : 0x0;  }

            inline tvector &    push_back(const Type *buf, size_type _size);
            inline bool         push_back_if_new(const Type &value);

            inline tvector &    insert(size_type idx, const Type &value)        { mData.insert(mData.begin() + idx, value); return *this;   }

            // Erase methods
            inline tvector &    eraseIndex(size_type idx)                       { mData.erase(mData.begin() + idx); return *this;           }
            inline tvector &    eraseIndexQuick(size_type idx);     // Changes element order

            inline bool         erase(const Type &value)                        { return eraseIfExists(value);                 }
            inline bool         eraseIfExists(const Type &value);
            inline bool         eraseQuick(const Type &value);      // Changes element order
            inline int32_t      erase(function<bool(const Type &)> func);

            // Swap indexes
            inline tvector &    swapIndex(size_type idx1, size_type idx2);

            // algorithms
            inline bool         contains(const Type &value) const               { return std::find(mData.begin(), mData.end(), value) != mData.end(); }

            inline int32_t      find(const Type &value) const;
            inline int32_t      find(const Type &value, function<bool(const Type &, const Type &)> func) const;
            inline int32_t      find(function<bool(const Type &)> func) const;

            inline tvector &    for_each(function<void(Type &)> func)           { return for_each(mData.begin(), mData.end(), func);        }
            inline tvector &    for_each(size_type first, size_type last, function<void(Type &)> func);
            inline tvector &    for_each(it first, it last, function<void(Type &)> func);

            inline tvector      filter(function<bool(const Type &)> func) const { return filter(mData.begin(), mData.end(), func);          }
            inline tvector      filter(size_type first, size_type last, function<bool(const Type &)> func) const;
            inline tvector      filter(c_it first, c_it last, function<bool(const Type &)> func) const;

            inline tvector      filter(function<bool(const Type &)> func, tvector &dst) const   { return filter(mData.begin(), mData.end(), func, dst); }
            inline tvector      filter(size_type first, size_type last, function<bool(const Type &)> func, tvector &dst) const;
            inline tvector      filter(c_it first, c_it last, function<bool(const Type &)> func, tvector &dst) const;

            inline Type         evaluate(function<Type(const Type &, const Type &)> func, const Type &init = {0}) const    { return evaluate(mData.begin(), mData.end(), func, init); }
            inline Type         evaluate(size_type first, size_type last, function<Type(const Type &, const Type &)> func, const Type &init = {0}) const;
            inline Type         evaluate(c_it first, c_it last, function<Type(const Type &, const Type &)> func, const Type &init = {0}) const;

            inline size_type    count(function<bool(const Type &)> func) const         { return count(mData.begin(), mData.end(), func); }
            inline size_type    count(size_type first, size_type last, function<bool(const Type &)> func) const;
            inline size_type    count(c_it first, c_it last, function<bool(const Type &)> func) const;

            inline bool         all_of(function<bool(const Type &)> func) const        { return all_of(mData.begin(), mData.end(), func);          }
            inline bool         all_of(size_type first, size_type last, function<bool(const Type &)> func) const;
            inline bool         all_of(c_it first, c_it last, function<bool(const Type &)> func) const;

            inline bool         none_of(function<bool(const Type &)> func) const       { return none_of(mData.begin(), mData.end(), func);          }
            inline bool         none_of(size_type first, size_type last, function<bool(const Type &)> func) const;
            inline bool         none_of(c_it first, c_it last, function<bool(const Type &)> func) const;

            inline bool         any_of(function<bool(const Type &)> func) const        { return any_of(mData.begin(), mData.end(), func);          }
            inline bool         any_of(size_type first, size_type last, function<bool(const Type &)> func) const;
            inline bool         any_of(c_it first, c_it last, function<bool(const Type &)> func) const;

            inline tvector &    reverse()                                       { std::reverse(mData.begin(), mData.end());        return *this; }
                                                                                
            // Sort methods                                                     
            inline tvector &    sort()                                          { std::sort(mData.begin(), mData.end());           return *this; }
            inline tvector &    stable_sort()                                   { std::stable_sort(mData.begin(), mData.end());    return *this; }

            inline tvector &    qsort(int (*func)(const void *, const void *))  { qsort(data(), mData.size(), sizeof(Type), func); return *this; }

            // Use operator '>'
            //inline tvector &    insertionSort()                                                 { InsertionSort(data(), mData.size());              return *this; }
            //inline tvector &    insertionSort(int (*funcCompare)(const void *, const void *))   { InsertionSort(data(), mData.size(), funcCompare); return *this; }
            //inline tvector &    insertionSort(bool (*funcGreater)(const Type &, const Type &))  { InsertionSort(data(), mData.size(), funcGreater); return *this; }

        protected:
            vector   mData;
    };

    //---------------------------------
    template <typename Type>
    inline int32_t
    TVector<Type>::find(const Type &value) const {
        c_it  it = std::find(mData.begin(), mData.end(), value);

        return (it != mData.end()) ? int32_t(it - mData.begin()) : -1;
    }

    //---------------------------------
    template <typename Type>
    inline int32_t
    TVector<Type>::find(const Type &value, function<bool(const Type &, const Type &)> func) const {
        size_type size = mData.size();
        for (size_type i = 0; i < size; ++i) {
            if (func(mData[i], value))
                return int32_t(i);
        }
        return -1;
    }

    //---------------------------------
    template <typename Type>
    inline int32_t
    TVector<Type>::find(function<bool(const Type &)> func) const {
        size_type size = mData.size();
        for (size_type i = 0; i < size; ++i) {
            if (func(mData[i]))
                return int32_t(i);
        }
        return -1;
    }

    //---------------------------------
    template <typename Type>
    inline typename TVector<Type>::size_type
    TVector<Type>::count(size_type first, size_type last, function<bool(const Type &)> func) const {
        return count(mData.begin() + first, mData.begin() + end, func);
    }

    //---------------------------------
    template <typename Type>
    inline typename TVector<Type>::size_type
    TVector<Type>::count(c_it first, c_it last, function<bool(const Type &)> func) const {
        size_type count = 0;
        for (; first != last; ++first) {
            if(func(*first))
                ++count;
        }
        return count;
    }

    //---------------------------------
    template <typename Type>
    inline TVector<Type> &
    TVector<Type>::for_each(size_type first, size_type last, function<void(Type &)> func) {
        return for_each(mData.begin() + first, mData.begin() + end, func);
    }

    //---------------------------------
    template <typename Type>
    inline TVector<Type> &
    TVector<Type>::for_each(it first, it last, function<void(Type &)> func) {
        for (; first != last; ++first) {
            func(*first);
        }
        return *this;
    }

    //---------------------------------
    template <typename Type>
    TVector<Type>
    TVector<Type>::filter(size_type first, size_type last, function<bool(const Type &)> func) const {
        return filter(mData.begin() + first, mData.begin() + end, func);
    }

    //---------------------------------
    template <typename Type>
    TVector<Type>
    TVector<Type>::filter(c_it first, c_it last, function<bool(const Type &)> func) const {
        TVector<Type>   result;
        for (; first != last; ++first) {
            if(func(*first))
                result.emplace_back(*first);
        }
        return result;
    }

    //---------------------------------
    template<typename Type>
    inline TVector<Type> 
    TVector<Type>::filter(size_type first, size_type last, function<bool(const Type &)> func, tvector &dst) const {
        return filter(mData.begin() + first, mData.begin() + end, func, dst);
    }

    //---------------------------------
    template<typename Type>
    inline TVector<Type> 
    TVector<Type>::filter(c_it first, c_it last, function<bool(const Type &)> func, tvector &dst) const {
        for (; first != last; ++first) {
            if (func(*first))
                dst.emplace_back(*first);
        }
        return dst;
    }

    //---------------------------------
    template <typename Type>
    inline Type
    TVector<Type>::evaluate(size_type first, size_type last, function<Type(const Type &, const Type &)> func, const Type &init) const {
        return evaluate(mData.begin() + first, mData.begin() + last, func, init);
    }

    //---------------------------------
    template <typename Type>
    inline Type
    TVector<Type>::evaluate(c_it first, c_it last, function<Type(const Type &, const Type &)> func, const Type &init) const {
        Type value(init);
        for (; first != last; ++first) {
            value = func(value, *first);
        }
        return value;
    }

    //---------------------------------
    template <typename Type>
    inline bool 
    TVector<Type>::all_of(size_type first, size_type last, function<bool(const Type &)> func) const {
        return all_of(mData.begin() + first, mData.begin() + end, func);
    }

    //---------------------------------
    template <typename Type>
    inline bool 
    TVector<Type>::all_of(c_it first, c_it last, function<bool(const Type &)> func) const {
        for (; first != last; ++first) {
            if (func(*first) == false)
                return false;
        }
        return true;
    }

    //---------------------------------
    template <typename Type>
    inline bool 
    TVector<Type>::none_of(size_type first, size_type last, function<bool(const Type &)> func) const {
        return none_of(mData.begin() + first, mData.begin() + end, func);
    }

    //---------------------------------
    template <typename Type>
    inline bool 
    TVector<Type>::none_of(c_it first, c_it last, function<bool(const Type &)> func) const {
        for (; first != last; ++first) {
            if (func(*first) == true)
                return false;
        }
        return true;
    }

    //---------------------------------
    template <typename Type>
    bool 
    TVector<Type>::any_of(size_type first, size_type last, function<bool(const Type &)> func) const {
        return any_of(mData.begin() + first, mData.begin() + end, func);
    }

    //---------------------------------
    template <typename Type>
    bool 
    TVector<Type>::any_of(c_it first, c_it last, function<bool(const Type &)> func) const {
        for (; first != last; ++first) {
            if (func(*first) == true)
                return true;
        }
        return false;
    }

    //---------------------------------
    template <typename Type>
    inline TVector<Type> &
    TVector<Type>::eraseIndexQuick(size_type idx) {
        std::swap(*(mData.begin() + idx), mData.back());
        mData.pop_back();

        return *this;
    }

    //---------------------------------
    template <typename Type>
    inline bool
    TVector<Type>::eraseIfExists(const Type &value) {
        c_it    it = std::find(mData.begin(), mData.end(), value);
        if (it != mData.end()) {
            mData.erase(it);
            return true;
        }

        return false;
    }

    //---------------------------------
    template <typename Type>
    inline bool
    TVector<Type>::eraseQuick(const Type &value) {
        c_it    it = std::find(mData.begin(), mData.end(), value);
        if (it != mData.end()) {
            std::swap(*it, mData.back());
            mData.pop_back();

            return true;
        }

        return false;
    }

    //---------------------------------
    template<typename Type>
    inline int32_t 
    TVector<Type>::erase(function<bool(const Type &)> func) {
        int32_t erased = 0;
        int32_t idx    = find(func);
        if (idx != -1) {
            erased = 1;
            it next = mData.begin() + idx;
            for (it i = next; ++i != mData.end(); ) {
                if (!func(*i)) {
                    *next = std::move(*i);
                    ++next;
                }
                else {
                    ++erased;
                }
            }
            mData.resize(mData.size() - erased);
        }
        return erased;
    }

    //---------------------------------
    template <typename Type>
    inline TVector<Type> &
    TVector<Type>::push_back(const Type *buf, size_type size) {
        if (buf != 0x0) {
            for (size_type i = 0; i < size; ++i) {
                mData.push_back(buf[i]);
            }
        }
        return *this;
    }

    //---------------------------------
    template <typename Type>
    inline bool
    TVector<Type>::push_back_if_new(const Type &value) {
        c_it  it = std::find(mData.begin(), mData.end(), value);
        if (it == mData.end()) {
            mData.push_back(value);
            return true;
        }

        return false;
    }

    //---------------------------------
    template <typename Type>
    inline TVector<Type> &
    TVector<Type>::swapIndex(size_type idx1, size_type idx2) {
        size_type  max = mData.size();
        if (idx1 < max && idx2 < max && idx1 != idx2) {
            std::swap(mData[idx1], mData[idx2]);
        }
        return *this;
    }

} // end of namespace
