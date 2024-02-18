#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
	size_t _size = 0;
	int _m;
	PComparator _c;
	std::vector<T> arr;
};

// Add implementation of member functions here

template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c){
	_m = m;
	_c = c;
}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap(){
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item){
	//Step 1: Add to end of list
	arr.push_back(item);
	//Step 2: Put it in the right place
	std::size_t index = arr.size() - 1;
	while (index != 0) {
		std::size_t parent_index = (index - 1) / _m;
		T& current = arr[index];
		T& parent = arr[parent_index];
		//if parent is better, do not need to change
		if (_c(parent, current)) {
			break;
		}
		//if parent is not better, swap
		std::swap(current, parent);
		index = parent_index;
	}
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
		throw std::underflow_error("Cannot call top() on empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
	return arr[0];
}

// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
		throw std::underflow_error("Cannot call pop() on empty heap");
  }
	//Step 1 & 2: Swap with last element and delete
	std::swap(arr[0], arr[arr.size()-1]);
	arr.pop_back();
	//Step 3: Put first element in correct place
	std::size_t index = 0;
	while (index <= arr.size()-1){
		std::size_t left_child_index = (index * _m) + 1;
		std::size_t right_child_index = (index * _m) + 2;
		//checks if there is a left child
		if (left_child_index >= arr.size()){
			break;
		}
		//checks if there is a right child
		if (right_child_index >= arr.size()){
			T& current = arr[index];
			T& left_child = arr[left_child_index];
			//if left child is better than current, swap
			if (_c(left_child, current)){
				std::swap(current, arr[left_child_index]);
			}
			break;
		}
		T& current = arr[index];
		T& left_child = arr[left_child_index];
		T& right_child = arr[right_child_index];
		//finds if left or right child is better
		std::size_t max_index = left_child_index;
		if (_c(left_child, right_child)){
			max_index = right_child_index;
		}
		//if best child is worse than current, do nothing
		if (_c(arr[max_index], current)){
			break;
		}
		//if not, swap
		std::swap(current, arr[max_index]);
		index = max_index;
	}
}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const{
	if (_size == 0){
		return true;
	}
	return false;
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const{
	return _size;
}

#endif

