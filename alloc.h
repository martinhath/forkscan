/*
Copyright (c) 2015 Forkscan authors.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

/* Module Description:
   Allocate/deallocate and track memory used by Forkscan in a centralized
   location.
 */

#ifndef _ALLOC_H_
#define _ALLOC_H_

#include <stddef.h>

typedef struct mem_range_t mem_range_t;

/** Metadata for a block of memory.
 */
struct mem_range_t {
    size_t low;
    size_t high;
};

/**
 * mmap() for the Forkscan system.  This call never fails.  But you should
 * only ever ask for big chunks in multiples of the page size.
 * @return The allocated memory.
 */
void *forkscan_alloc_mmap (size_t size, const char *reason);

/**
 * mmap() for the Forkscan system.  This call never fails.  But you should
 * only ever ask for big chunks in multiples of the page size.  The mmapped
 * memory is marked as shared among processes.
 * @return The allocated memory.
 */
void *forkscan_alloc_mmap_shared (size_t size, const char *reason);

/**
 * munmap() for the Forkscan system.
 */
void forkscan_alloc_munmap (void *ptr);

/**
 * Given a *big_range, return the first chunk of it that doesn't contain
 * memory that belongs to Forkscan.  *big_range is modified to show the
 * remaining portion of the range.  This is not thread-safe.
 *
 * @return A chunk of memory that does not overlap with memory owned by
 * Forkscan.  This chunk may have zero length if no such chunk could be
 * found in *big_range.
 */
mem_range_t forkscan_alloc_next_subrange (mem_range_t *big_range);

#endif // !defined _ALLOC_H_
