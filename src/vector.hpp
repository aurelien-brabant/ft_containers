#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <memory>
# include <iostream>
# include <stdexcept>
# include <iostream>
# include <cstdlib>
# include "iterator.hpp"
# include "type_traits.hpp"

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
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			
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
			
			vector(const_reference rhs): _allocator(Allocator()), _capacity(rhs.size() * 2), _data(_allocator.allocate(_capacity)), _length(rhs.size())
			{
				for (size_type i = 0; i != size(); ++i) {
					_allocator.construct(_data + i, rhs._data[i]);
				}
			}

			reference operator=(const_reference rhs)
			{
				if (this != &rhs) {
					assign(rhs.begin(), rhs.end());
				}

				return *this;
			}

			~vector(void)
			{
				_allocator.deallocate(_data, _capacity);
			}

			allocator_type get_allocator(void) const
			{
				return _allocator;
			}
			
			template <typename InputIt>
			void assign(
					InputIt begin,
					InputIt end,
					typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* p = 0)
			{
				(void)p;

				size_type count = end - begin;

				if (count > capacity()) {
					reserve(count * vectorGrowthFactor);
				}

				for (size_type i = 0; i < count; ++i) {
					if (i < size()) {
						_data[i] = *begin++;
					} else {
						_allocator.construct(_data + i, *begin++);
					}
				}

				/* Destroy excess of element in case there is */
				for (size_type i = count; i < size(); ++i) {
					_allocator.destroy(_data + i);
				}

				_length = count;
			}
			
			void assign(size_type count, T const & value)
			{
				if (count > capacity()) {
					reserve(count * vectorGrowthFactor);
				}

				for (size_type i = 0; i != count; ++i) {
					if (i < size()) {
						_data[i] = value;
					} else {
						_allocator.construct(_data + i, value);
					}
				}

				_length = count;
			}
			
			// capacity {{{

			bool empty(void) const
			{
				return size() == 0;
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

				for (size_type i = 0; i != size(); ++i) {
					_allocator.construct(newData + i, _data[i]);
				}


				_allocator.deallocate(_data, _capacity);
				_data = newData;
				_capacity = newCapacity;
			}

			// }}}

			// element access {{{
			
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

			pointer data(void)
			{
				return _data;
			}

			// }}}

			// iterators {{{
			
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

			reverse_iterator rbegin()
			{
				return reverse_iterator(end());
			}

			reverse_iterator rend()
			{
				return reverse_iterator(begin());
			}

			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(end());
			}

			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(begin());
			}

			// }}}

			// modifiers {{{
			
			void clear(void)
			{
				_length = 0;
			}

			/**
			 * Insert a range of items delimited by two input iterators.
			 * Resize is triggered if (size() + end - begin) > capacity().
			 */

			template <class InputIt>
			iterator insert(iterator pos, InputIt begin, InputIt end)
			{
				size_type n = end - begin;
				size_type ipos = pos - this->begin();

				if (n + size() > capacity()) {
					reserve((n + size()) * vectorGrowthFactor);
				}

				for (size_type i = size(); i != ipos;) {
					--i;
					if (i + n >= size()) {
						_allocator.construct(_data + i + n, _data[i]);
					} else {
						_data[i + n] = _data[i];
					}
				}
				_data[ipos + n] = _data[ipos];

				for (size_type i = ipos; i != ipos + n; ++i, ++begin) {
					if (i >= size()) {
						_allocator.construct(_data + i, *begin);
					} else {
						_data[i] = *begin;
					}
				}

				_length += n;

				return this->begin() + ipos;
			}

			/**
			 * Insert value before pos, triggering a resize if size() + 1 >= capacity().
			 * push_back is used to push a new element in the vector and resize it if
			 * necessary, as this overload only adds one element to the vector.
			 */

			void insert(iterator pos, T const & value)
			{
				size_type ipos = pos - begin();
				
				push_back(value);

				for (size_type i = end() - begin(); i > ipos + 1;) {
					--i;
					_data[i] = _data[i - 1];
				}
				
				_data[ipos] = value;
			}

			void push_back(const value_type& value)
			{
				if (size() == capacity()) {
					reserve(capacity() * vectorGrowthFactor);
				}
				_allocator.construct(_data + _length++, value);
			}

			iterator erase(iterator pos)
			{
				_allocator.destroy(&(*pos));

				iterator it(pos);
				while (it != end() - 1) {
					it[0] = it[1];
					++it;
				}

				--_length;

				return pos;
			}

			// }}}
	};
}

#endif
