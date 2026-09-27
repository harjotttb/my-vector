
#include <assert.h>
#include <iostream>
#include <string>
#include <stdexcept>

namespace CPSC131::MyVector
{

	//
	template <typename T>
	class MyVector
	{
		public:
			
			/*******************
			 * Static constants
			 ******************/
			
			/// Default capacity
			static constexpr size_t DEFAULT_CAPACITY = 64;
			
			/// Minimum capacity
			static constexpr size_t MINIMUM_CAPACITY = 8;
			
			/*****************************
			 * Constructors / Destructors
			 ****************************/
			
			/// Normal constructor
			MyVector(size_t capacity = MyVector::DEFAULT_CAPACITY)
			{
				if (capacity < MyVector::MINIMUM_CAPACITY){
					capacity = MyVector::MINIMUM_CAPACITY;
				}
				capacity_ = capacity;
				size_ = 0;
				elements_ = new T[capacity_];
			}
			
			/// Copy constructor
			MyVector(const MyVector& other)
			{
				capacity_ = other.capacity_;
				size_ = other.size_;

				if (capacity_ > 0){
					elements_ = new T[capacity_];
					for (size_t i = 0; i < size_; i++){
						elements_[i] = other.elements_[i];
					}
				}
				else {
					elements_ = nullptr;
				}
			}
			
			/**
			 * Destructor
			 * Cleanup here.
			 */
			~MyVector()
			{
				delete[] elements_;
				elements_ = nullptr;
				size_ = 0;
				capacity_ = 0;
			}
			
			/************
			 * Operators
			 ************/
			
			///	Assignment operator
			MyVector& operator=(const MyVector& rhs)
			{
				if (this != &rhs){
					T* newElements = nullptr;
					if (rhs.capacity_ > 0){
						newElements = new T[rhs.capacity_];
						for (size_t i = 0; i < rhs.size_; i++){
							newElements[i] = rhs.elements_[i];
						}
					  }

					
					delete[] elements_;
					elements_ = newElements;
					capacity_ = rhs.capacity_;
					size_ = rhs.size_;
				}
				
				return *this;
			}
			
			/// Operator overload to at()
			T& operator[](size_t index) const
			{
				if (index >= size_){
					throw std::out_of_range("Index isn't in range");
				}
				return elements_[index];
			}
			
			/************
			 * Accessors
			 ************/
			
			/// Return a raw pointer to the elements_ array
			T* elements()
			{
				return elements_;
			}
			
			/// Return the number of valid elements in our data
			size_t size() const
			{
				return size_;
			}
			
			/// Return the capacity of our internal array
			size_t capacity() const
			{
				return capacity_;
			}
			
			/**
			 * Check whether our vector is empty
			 * Return true if we have zero elements in our array (regardless of capacity)
			 * Otherwise, return false
			 */
			bool empty() const
			{
				return (size_ == 0);
			}
			
			/// Return a reference to the element at an index
			T& at(size_t index) const
			{
				if (index >= size_){
					throw std::out_of_range("Index isn't in range");
				}
				return elements_[index];
			}
			
			/***********
			 * Mutators
			 ***********/

			void reserve(size_t capacity)
			{
				if (capacity < size_){
					throw std::invalid_argument("Capacity is less than size");
				}
				if (capacity < MyVector::MINIMUM_CAPACITY){
					capacity = MyVector::MINIMUM_CAPACITY;
				}
				if (capacity <= capacity_){
					return;
				}
				T* newElements = new T[capacity];
				for (size_t i = 0; i < size_; i++){
					newElements[i] = elements_[i];
				}
				delete[] elements_;

				elements_ = newElements;
				capacity_ = capacity;
			}
			
			/**
			 * Set an element at an index.
			 * Throws range error if outside the size boundary.
			 * Returns a reference to the newly set element (not the original)
			 */
			T& set(size_t index, const T& element)
			{
				if (index >= size_){
					throw std::out_of_range("index is out of range");
				}
				elements_[index] = element;

				return elements_[index];
			}
			
			/**
			 * Add an element onto the end of our vector.
			 * Returns a reference to the newly inserted element.
			 */
			T& push_back(const T& element)
			{
				if (size_ >= capacity_){
					size_t newCapacity = (capacity_ == 0) ? MyVector::MINIMUM_CAPACITY : (capacity_ * 2);
					reserve(newCapacity);
				}
				elements_[size_] = element;
				size_++;
				return elements_[size_-1];
			}
			
			/**
			 * Remove the last element in our vector.
			 * Should throw std::range_error if the vector is already empty.
			 * Returns a copy of the element removed.
			 */
			T pop_back()
			{
				if(empty()){
					throw std::underflow_error("empty vector");
				}
				   T temp = elements_[size_ - 1];
                   --size_;
				   if (size_ == 0){
				       if (capacity_ != MyVector::MINIMUM_CAPACITY){
                           delete[] elements_;
                           capacity_ = MyVector::MINIMUM_CAPACITY;
                           elements_ = new T[capacity_];
                       }
                   }
                   else {

					size_t newCapacity = capacity_;

					while (size_ < (newCapacity / 3) && (newCapacity / 2) >= MyVector::MINIMUM_CAPACITY){
						newCapacity = (newCapacity / 2);
					}
					if (newCapacity != capacity_){
						T* newElements = new T[newCapacity];

						for (size_t i = 0; i < size_; i++){
							newElements[i] = elements_[i];
						}
                      
                       delete[] elements_;
                       elements_ = newElements;
                       capacity_ = newCapacity;
					}
                   }
                  
                   return temp;
               return T();

			}
			
			/**
			 * Insert an element at some index in our vector
			 */
			T& insert(size_t index, const T& element)
			{
				if (size_ >= capacity_){
					size_t newCapacity = (capacity_ == 0) ? MyVector::MINIMUM_CAPACITY : (capacity_ * 2);
					reserve(newCapacity);
				}
				if (index > size_){
					throw std::out_of_range("Index isn't in range");
				}

				for (size_t i = size_; i > index; i--){
					elements_[i] = elements_[i - 1];
				}

				elements_[index] = element;
				size_++;

				return elements_[index];
			}
			
			/**
			 * Erase one element in our vector at the specified index
			 */
			T erase(size_t index)
			{
				if (index >= size_){
				throw std::out_of_range("index is out of range");
				}
			    T temp = elements_[index];
			    for (size_t i = index; i + 1 < size_; i++){
			         elements_[i] = elements_[i + 1];
			    }
			
			    size_--;

				if (size_ == 0){
					if (capacity_ != MyVector::MINIMUM_CAPACITY){
					delete[] elements_;
					elements_ = new T[capacity_];
					}
				}
				else {
					size_t newCapacity = capacity_;
					while (size_ < (newCapacity / 3) && (newCapacity / 2) >= MyVector::MINIMUM_CAPACITY){
						newCapacity = (newCapacity / 2);
					}
					if (newCapacity != capacity_){
						T* newElements = new T[newCapacity];
						for (size_t i = 0; i < size_; i++){
							newElements[i] = elements_[i];
						}
						delete[] elements_;
						elements_ = newElements;
						capacity_ = newCapacity;
					}
				}
			    return temp;
			}
			
			/**
			 * Removes all elements (i.e., size=0 and DTORs called.
			*/
			void clear()
			{
				while (!empty()){
					pop_back();
				}
				if (capacity_ != MyVector::DEFAULT_CAPACITY){
					delete[] elements_;
					capacity_ = MyVector::DEFAULT_CAPACITY;
					elements_ = new T[capacity_]; 
				}
			}
		
		/**
		 * Begin private members and methods.
		 * You may add your own private helpers here, if you wish.
		*/
		private:
			
			/// Number of valid elements currently in our vector
			size_t size_ = 0;
			
			/// Capacity of our vector; The actual size of our internal array
			size_t capacity_ = 0;
			
			/**
			 * Our internal array of elements of type T.
			 * Starts off as a null pointer.
			 */
			T* elements_ = nullptr;
	};

}

