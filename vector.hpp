#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <memory>
# include <iostream>
# include <stdexcept>
# include "iterator.hpp"

namespace ft
{
	namespace
	{
		float static const vectorGrowthFactor = 2.0;
		size_t static const vectorBaseCapacity = 10;
	}

	template <
		class T,
		class Allocator = std::allocator<T>
	> class vector
	{

		public:
			typedef size_t size_type;
			typedef T value_type;
			typedef Allocator allocator_type;
			typedef vector<T> & reference;
			typedef vector<T> const & const_reference;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef std::ptrdiff_t difference_type;
			typedef ft::iterator<T, std::random_access_iterator_tag> iterator;
			typedef ft::iterator<T const, std::random_access_iterator_tag, true> const_iterator;
			
		private:
			Allocator _allocator;
			size_type _capacity;
			T * _data;
			size_type _length;

		public:
			// CTORS
			vector(void): _allocator(Allocator()), _capacity(vectorBaseCapacity), _data(_allocator.allocate(_capacity)), _length(0)
			{
			}

			explicit vector(
				size_type count,
				T const & value = T(),
				Allocator const & alloc = Allocator()
			): _allocator(alloc), _capacity(count * 2), _data(_allocator.allocate(_capacity)), _length(count)
			{
				for (size_type i = 0; i != _length; ++i) {
					_allocator.construct(_data + i, value);
				}
			}

			/**
			 * Construct a vector from another one, by coping rhs's elements into the constructed one.
			 * All the RESERVED memory is *constructed*.
			 */

			vector(const_reference rhs): _allocator(Allocator()), _capacity(rhs.size() * 2), _data(_allocator.allocate(_capacity)), _length(rhs.size())
			{
				for (size_type i = 0; i != capacity(); ++i) {
					_allocator.construct(_data + i, i < size() ? rhs._data[i] : T());
				}
			}

			reference operator=(const_reference rhs)
			{
				if (this != &rhs) {
					/* Copy elements from rhs to *this up to its capacity */
					for (size_type i = 0; i != capacity() && i != rhs.size(); ++i) {
						_data[i] = rhs._data[i];
					}

					/* if *this has less elements than rhs, that means we could not copy everything, due to a lack of capacity */
					if (size() < rhs.size()) {
						if (capacity() < rhs.size()) {
							reserve(rhs.size() * 2);
						}
						for (size_type i = size(); i != rhs.size(); ++i) {
							_data[i] = rhs._data[i];
						}
					}

					_length = rhs._length;
				}

				return *this;
			}

			// DTOR

			~vector(void)
			{
				_allocator.deallocate(_data, _capacity);
			}

			// Getters
			
			allocator_type get_allocator(void) const
			{
				return _allocator;
			}
			
			size_type size(void) const
			{
				return _length;
			}

			size_type capacity(void) const
			{
				return _capacity;
			}

			size_type max_size(void) const
			{
				return _allocator.max_size();
			}

			bool empty(void) const
			{
				return size() == 0;
			}

			/**
			 * Reserve memory to reach the passed newCapacity.
			 * Nothing is done if newCapacity <= oldCapacity.
			 * All the memory is constructed by value.
			 */

			void reserve(size_type newCapacity)
			{
				if (capacity() >= newCapacity) {
					return ;
				}

				if (newCapacity >= max_size()) {
					throw std::length_error("newCapacity is greater than max_size");
				}

				T * newData = _allocator.allocate(newCapacity);
				
				for (size_type i = 0; i != newCapacity; ++i) {
					_allocator.construct(newData + i, i < _length ? _data[i] : T());
				}

				_allocator.deallocate(_data, _capacity);
				_data = newData;
				_capacity = newCapacity;
			}	

			void push_back(value_type const & value)
			{
				if (_length == _capacity) {
					reserve(capacity() * vectorGrowthFactor);
				}

				_allocator.construct(_data + _length++, value);
			}

			// element access
			value_type & operator[](size_type index)
			{
				return _data[index];
			}

			value_type & at(size_type index)
			{
				if (index >= size()) {
					throw std::out_of_range("vector: index out of range");
				}

				return operator[](index);
			}

			value_type & front(void)
			{
				return *begin();
			}

			value_type & back(void)
			{
				return *(end() - 1);
			}

			// assign
			// TODO: fix template overload issue. assign(size_type, T const &) tries
			// to use the template which is definitely not to be expected.

			template <typename InputIt>
			void assign(InputIt begin, InputIt end)
			{
				_length = 0;
				
				while (begin != end) {
					push_back(*begin++);
				}
			}
			
			void assign(size_type count, T const & value)
			{
				_length = 0;

				for (size_type i = 0; i != count; ++i) {
					push_back(value);
				}
			}

			// ITERATORS
			
			iterator begin(void)
			{
				iterator tmp(_data);

				return tmp;
			}

			const_iterator begin(void) const
			{
				const_iterator tmp(_data);

				return tmp;
			}

			iterator end(void)
			{
				iterator tmp(_data + size());

				return tmp;
			}

			const_iterator end(void) const
			{
				const_iterator tmp(_data + size());

				return tmp;
			}

			// MANIPULATORS
			
			void clear(void)
			{
				_length = 0;
			}

			template <class InputIt>
			iterator insert(iterator pos, InputIt begin, InputIt end)
			{
				size_type n = end - begin;
				size_type ipos = pos - this->begin();

				// not enough space, reallocate
				if (n + size() > capacity()) {
					reserve((n + size()) * vectorGrowthFactor);
				}

				for (size_type i = size(); i != ipos;) {
					--i;
					_data[i + n] = _data[i];
				}

				for (size_type i = ipos; i != ipos + n; ++i, ++begin) {
					_data[i] = *begin;
				}

				_length += n;

				return this->begin() + ipos;
			}


			/**
			 * Insert value before pos, triggering a resize if size() + 1 >= capacity()
			 */

			iterator insert(iterator pos, T const & value)
			{
				size_type ipos = pos - begin();

				push_back(0);

				std::cout << "size: " << size() << "\n";
				std::cout << "ipos: " << ipos << "\n";

				for (size_type i = end() - begin() - 1; i != ipos; --i) {
					_data[i] = _data[i - 1];
				}
				
				_data[ipos] = value;

				return begin() + ipos;
			}
	};
}

#endif
