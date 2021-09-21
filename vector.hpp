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
			typedef T & reference;
			typedef T const & const_reference;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef std::ptrdiff_t difference_type;
			
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

			explicit vector(
				size_type count,
				T const & value = T(),
				Allocator const & alloc = Allocator()
			): _allocator(alloc), _capacity(count * 2), _data(_allocator.allocate(_capacity)), _length(count)
			{
				for (size_type i = 0; i != _length; ++i) {
					_data[i] = value;
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
			
			reference operator[](size_type index)
			{
				return _data[index];
			}
	};
}

#endif
