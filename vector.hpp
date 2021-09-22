#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <memory>
# include <iostream>
# include <stdexcept>

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
					for (size_type i = 0; i != capacity() && i != rhs.size(); ++i) {
						if (i >= size()) {
							_allocator.construct(_data + i, rhs._data[i]);
						} else {
							_data[i] = rhs._data[i];
						}
					}

					if (size() < rhs.size()) {
						if (capacity() < rhs.size()) {
							reserve(rhs.size() * 2);
						}
						for (size_type i = size(); i != rhs.size(); ++i) {
							_allocator.construct(_data + i, rhs._data[i]);
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

			void reserve(size_type newCapacity)
			{
				if (capacity() >= newCapacity) {
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
				if (index < size()) {
					throw std::out_of_range("vector: index out of range");
				}

				return operator[](index);
			}
	};
}

#endif
