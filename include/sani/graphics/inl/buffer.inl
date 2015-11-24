#include "sani/graphics/buffer.hpp"

namespace sani {

	namespace graphics {

		template<typename T>
		Buffer<T>::Buffer(const uint32 initialSize, const BufferSizing bufferSizing) : bufferSizing(bufferSizing),
																					   bufferPointer(0),
																					   size(initialSize) {
			memory.resize(size);
		}

		template<typename T>
		void Buffer<T>::checkSize(const uint32 offset) {
			if (bufferSizing == BufferSizing::Static) {
				if (bufferPointer + offset > size) throw std::runtime_error("Buffer overflow");
			} else if (bufferSizing == BufferSizing::Dynamic) {
				if (bufferPointer + offset > size) {
					size *= 2;

					memory.resize(size);
				}
			}
		}

		/// Returns the type of the buffer. 
		template<typename T>
		BufferSizing Buffer<T>::getBufferSizing() const {
			return bufferSizing;
		}

		/// Push a given element to the buffer.
		template<typename T>
		void Buffer<T>::push(T element) {
			checkSize(1);
			
			memory[bufferPointer] = element;

			bufferPointer++;
		}
		/// Push given elements to the buffer.
		/// @param [in] elements elements to push
		/// @param [in] count count of elements to push
		template<typename T>
		void Buffer<T>::push(const T* elements, const uint32 count) {
			checkSize(count);

			for (uint32 i = 0; i < count; i++) memory[i + bufferPointer] = elements[i];

			bufferPointer += count;
		}

		/// Applies given offset to this buffer.
		template<typename T>
		void Buffer<T>::offset(const uint32 offset) {
			checkSize(offset);

			bufferPointer += offset;
		}

		/// Returns the size of this buffer.
		template<typename T>
		uint32 Buffer<T>::getSize() const {
			return size;
		}
		/// Returns the location of the buffer pointer.
		template<typename T>
		uint32 Buffer<T>::getElementsCount() const {
			return bufferPointer;
		}

		/// Copies the contents of another buffer to this buffer.
		template<typename T>
		void Buffer<T>::copy(Buffer<T>& other) {
			checkSize(other.getBufferPointerLocation());

			push(other.data(), other.getBufferPointerLocation());
		}

		/// Returns pointer to the beginning of the buffer.
		template<typename T>
		T* Buffer<T>::data() {
			return memory.data();
		}

		/// Sets the buffer pointers value to zero.
		template<typename T>
		void Buffer<T>::resetBufferPointer() {
			bufferPointer = 0;
		}

		template<typename T>
		Buffer<T>::~Buffer() {
		}
	}
}