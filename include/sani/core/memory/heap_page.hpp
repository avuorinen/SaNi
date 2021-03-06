#pragma once

#include "sani/core/memory/heap_block.hpp"
#include "sani/core/memory/memory.hpp"
#include "sani/types.hpp"
#include <algorithm>
#include <list>
#include <queue>

namespace sani {

	/*
		Allocate with pp till we hit the end.
		Then start to use the released blocks.
	*/
	
	/// @class HeapPage heap_page.hpp "sani/core/memory/heap_page.hpp"
	/// @author voidbab
	///
	/// Dynamically allocated chunk of memory that is used 
	/// by the heap.
	class HeapPage {
	private:
		const uint32 size;
		char* memory;

		// Bytes missed when we have tried to allocate.
		uint32 missedBytes;
		// Fragmentation in percents.
		// missedBytes / size.
		float32 fragmentation;

		std::priority_queue<HeapBlock> releasedBlocks;
		std::list<HeapBlock> blocks;

		uint32 bytesUsed;
		uint32 pagepointer;

		void joinBlocks(std::list<HeapBlock> &newReleasedBlocks, std::list<HeapBlock> &newBlocks);
		void freeBlocks(std::list<HeapBlock>& newBlocks, std::list<HeapBlock>& newReleasedBlocks);
		void generateNewReleasedQueue(std::list<HeapBlock>& newReleasedBlocks);

		inline bool internalDeallocate(char* const handle);
	public:
		HeapPage(const uint32 size);

		float32 getFragmentation() const;

		bool canAllocate(const uint32 size);

		bool isInAddressSpace(const IntPtr address);

		/// Allocates new element of type T with given amount of bytes
		/// to reserve for storage. This value can contain padding
		/// to keep the size of the chunk in word boundaries.
		template<class T> 
		inline T* allocate();
		template<class T>
		inline T* allocate(const uint32 lenght);

		template<class T>
		inline bool deallocate(T* element);
		template<class T>
		inline bool deallocate(T* elements, const uint32 length);

		bool shouldDefragment() const;
		bool fragmented() const;
		void defragment();

		uint32 getBytesUsed() const;

		~HeapPage();

		HeapPage(HeapPage& other) = delete;
		HeapPage(HeapPage&& other) = delete;

		HeapPage& operator =(HeapPage& other) = delete;
		HeapPage& operator =(HeapPage&& other) = delete;
	};
}

#include "sani/core/memory/impl/heap_page.hpp"