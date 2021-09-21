#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <memory>

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
			typedef reference T &;
			typedef const_reference T const &;
			typedef pointer Allocator::pointer;
			typedef const_pointer Allocator::const_pointer;
			
		private:
			Allocator _allocator;
			size_type _capacity;
			T * _data;
			size_type _length;

			void _grow(void)
			{
				size_type newCapacity = _capacity * vectorGrowthFactor;

				T * newData = _allocator.allocate(newCapacity);
				
				for (size_type i = 0; i != newCapacity; ++i) {
					newData[i] = i < _length ? _data[i] : T();
				}

				_allocator.deallocate(_data, _capacity);
				_data = newData;
				_capacity = newCapacity;
			}

		public:

			// CTORS
			vector(void): _allocator(Allocator()), _capacity(vectorBaseCapacity), _data(_allocator.allocate(_capacity)), _length(0)
			{
			}

			vector(size_type n): _allocator(Allocator()), _capacity(n * 2), _data(_allocator.allocate(_capacity)), _length(n)
			{
				for (size_type i = 0; i != _length; ++i) {
					_data[i] = T();
				}
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

			void push_back(T const & value)
			{
				if (_length == _capacity) {
					_grow();
				}

				_data[_length++] = value;
			}

			// operators
			
			T & operator[](size_type index)
			{
				return _data[index];
			}
	};
}

#endif
