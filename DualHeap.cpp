#include "DualHeap.h"
// ------------------------------
// Definition of DualHeap Class
// ------------------------------
//-- Public Methods --//

template <class Type>
DualHeap<Type>::DualHeap() {
	/** \code */
	// Default heapsize is 5
	HEAPSIZE = 5;
	data.reserve(HEAPSIZE);
	data.resize(HEAPSIZE);
	direction = true;
	current_size = 0;
	pending_size = 0;
	/** \endcode */
}

template <class Type>
DualHeap<Type>::DualHeap(int heapsize) {
	/** \code */
	HEAPSIZE = heapsize;
	data.reserve(HEAPSIZE);
	data.resize(HEAPSIZE);
	direction = true;
	current_size = 0;
	pending_size = 0;
	/** \endcode */
}

// DONE
template <class Type>
void DualHeap<Type>::put(Type item) {
	/** \code */
	if (fullwith_pending()) { // full of pending items => push a run to buffer
		buffer.push_back(run);
		run = vector<Type>(); // empty output run
		direction = !direction;
		assert(current_size == 0);
		current_size = pending_size;
		pending_size = 0;
	}
	if (!full()) { // exists a spot for new item
		current_heap_push(item);
	}
	else { // full of active and pending items
		maxmin = current_heap_pop();    // pop from active
		if (maxmin > item) { // item goes to pending
			run.push_back(maxmin);          // popped item goes to run
			pending_heap_push(item);        // push to pending heap
		}
		else { // item goes to active
			run.push_back(maxmin);          // popped item goes to run
			current_heap_push(item);        // push to active heap
		}
	}
	/** \endcode */
}

// DONE
template <class Type>
vector<vector<Type> > DualHeap<Type>::retrieve() {
	/** \code */
	finalize();
	return buffer;
	/** \endcode */
}

// DONE
template <class Type>
void DualHeap<Type>::finalize() {
	/** \code */
	Type tempitem;
	int heapsize = current_size;
	for (int i = 0; i < heapsize; i++) {
		tempitem = current_heap_pop();
		run.push_back(tempitem);
	}
	if (run.size() > 0) {
		buffer.push_back(run);
		run = vector<Type>();
		direction = !direction;
		current_size = pending_size;
		pending_size = 0;
	}
	heapsize = current_size;
	for (int i = 0; i < heapsize; i++) {
		run.push_back(current_heap_pop());
	}
	if (run.size() > 0) {
		buffer.push_back(run);
		run = vector<Type>();
		direction = !direction;
		current_size = 0;
		//setmaxmin = false;
	}
	/** \endcode */
}


//---- Support Methods ----//
//-- Private Methods --//

//-- Index Getter --//
// DONE
template <class Type>
int DualHeap<Type>::l_child(int n) {
	/** \code */
	return 2 * n + 1;
	/** \endcode */
}

// DONE
template <class Type>
int DualHeap<Type>::r_child(int n) {
	/** \code */
	return 2 * (n + 1);
	/** \endcode */
}

// DONE
template <class Type>
int DualHeap<Type>::parent(int n) {
	/** \code */
	return (n - 1) / 2;
	/** \endcode */
}

// DONE
template <class Type>
int DualHeap<Type>::current_l_child(int n) {
	/** \code */
	if (direction) {
		return l_child(n);
	}
	else {
		return (HEAPSIZE - 1) - l_child((HEAPSIZE - 1) - n);
	}
	/** \endcode */
}

// DONE
template <class Type>
int DualHeap<Type>::current_r_child(int n) {
	/** \code */
	if (direction) {
		return r_child(n);
	}
	else {
		return (HEAPSIZE - 1) - r_child((HEAPSIZE - 1) - n);
	}
	/** \endcode */
}

// DONE
template <class Type>
int DualHeap<Type>::current_parent(int n) {
	/** \code */
	if (direction) {
		return parent(n);
	}
	else {
		return (HEAPSIZE - 1) - parent((HEAPSIZE - 1) - n);
	}
	/** \endcode */
}

// DONE
template <class Type>
int DualHeap<Type>::pending_l_child(int n) {
	/** \code */
	if (!direction) {
		return l_child(n);
	}
	else {
		return (HEAPSIZE - 1) - l_child((HEAPSIZE - 1) - n);
	}
	/** \endcode */
}

// DONE
template <class Type>
int DualHeap<Type>::pending_r_child(int n) {
	/** \code */
	if (!direction) {
		return r_child(n);
	}
	else {
		return (HEAPSIZE - 1) - r_child((HEAPSIZE - 1) - n);
	}
	/** \endcode */
}

// DONE
template <class Type>
int DualHeap<Type>::pending_parent(int n) {
	/** \code */
	if (!direction) {
		return parent(n);
	}
	else {
		return (HEAPSIZE - 1) - parent((HEAPSIZE - 1) - n);
	}
	/** \endcode */
}

// DONE
template <class Type>
int DualHeap<Type>::current_next(int n) {
	/** \code */
	return (direction) ? n + 1 : n - 1;
	/** \endcode */
}

// DONE
template <class Type>
int DualHeap<Type>::pending_next(int n) {
	/** \code */
	return (direction) ? n - 1 : n + 1;
	/** \endcode */
}

// DONE
template <class Type>
int DualHeap<Type>::current_head() {
	/** \code */
	return (direction) ? 0 : (HEAPSIZE - 1);
	/** \endcode */
}

// DONE
template <class Type>
int DualHeap<Type>::pending_head() {
	/** \code */
	return (!direction) ? 0 : (HEAPSIZE - 1);
	/** \endcode */
}

// DONE
template <class Type>
int DualHeap<Type>::current_tail() {
	/** \code */
	return (direction) ? (current_size - 1) : (HEAPSIZE - current_size);
	/** \endcode */
}

// DONE
template <class Type>
int DualHeap<Type>::pending_tail() {
	/** \code */
	return (!direction) ? (pending_size - 1) : (HEAPSIZE - pending_size);
	/** \endcode */
}


//-- Existence Checker --//

// DONE
template <class Type>
bool DualHeap<Type>::exist_current_parent(int n) {
	/** \code */
	if (direction) {
		return current_parent(n) >= 0;
	}
	else {
		return (HEAPSIZE - 1) >= current_parent(n);
	}
	/** \endcode */
}

// DONE
template <class Type>
bool DualHeap<Type>::exist_current_l_child(int n) {
	/** \code */
	if (direction) {
		return current_l_child(n) < current_size;
	}
	else {
		return (HEAPSIZE - current_size) <= current_l_child(n);
	}
	/** \endcode */
}

// DONE
template <class Type>
bool DualHeap<Type>::exist_current_r_child(int n) {
	/** \code */
	if (direction) {
		return current_r_child(n) < current_size;
	}
	else {
		return (HEAPSIZE - current_size) <= current_r_child(n);
	}
	/** \endcode */
}


// DONE
template <class Type>
bool DualHeap<Type>::exist_pending_parent(int n) {
	/** \code */
	if (!direction) {
		return pending_parent(n) >= 0;
	}
	else {
		return (HEAPSIZE - 1) >= pending_parent(n);
	}
	/** \endcode */
}

// DONE
template <class Type>
bool DualHeap<Type>::exist_pending_l_child(int n) {
	/** \code */
	if (!direction) {
		return pending_l_child(n) < current_size;
	}
	else {
		return (HEAPSIZE - current_size) <= pending_l_child(n);
	}
	/** \endcode */
}

// DONE
template <class Type>
bool DualHeap<Type>::exist_pending_r_child(int n) {
	/** \code */
	if (!direction) {
		return pending_r_child(n) < current_size;
	}
	else {
		return (HEAPSIZE - current_size) <= pending_r_child(n);
	}
	/** \endcode */
}


//-- Heap Operations --//
// DONE
template <class Type>
bool DualHeap<Type>::current_heap_push(Type item) {
	/** \code */
	if (full()) {
		return false;
	}
	data[current_next(current_tail())] = item;
	current_size++;
	current_heapify_up(current_tail());
	return true;
	/** \endcode */
}

// DONE
template <class Type>
bool DualHeap<Type>::pending_heap_push(Type item) {
	/** \code */
	if (full()) {
		return false;
	}
	data[pending_next(pending_tail())] = item;
	pending_size++;
	pending_heapify_up(pending_tail());
	return true;
	/** \endcode */
}

// DONE
template <class Type>
Type DualHeap<Type>::current_heap_pop() {
	/** \code */
	Type returndata = data[current_head()];
	data[current_head()] = data[current_tail()];
	current_size--;
	current_heapify_down(current_head());
	return returndata;
	/** \endcode */
}


// DONE
template <class Type>
bool DualHeap<Type>::full() {
	/** \code */
	return (current_size + pending_size) == HEAPSIZE;
	/** \endcode */
}

// DONE
template <class Type>
bool DualHeap<Type>::fullwith_pending() {
	/** \code */
	return (pending_size) == HEAPSIZE;
	/** \endcode */
}

// DONE
template <class Type>
void DualHeap<Type>::current_heapify_up(int n) {
	/** \code */
	if (n == current_head()) // at root
		return;
	if (data[current_parent(n)] > data[n]) { // need swap
		Type tempdata = data[current_parent(n)];
		data[current_parent(n)] = data[n];
		data[n] = tempdata;
		current_heapify_up(current_parent(n)); // recursive call to parent node
	}
	/** \endcode */
}

template <class Type>
void DualHeap<Type>::current_heapify_down(int n) {
	/** \code */
	// check if child exists
	if (!exist_current_l_child(n)) { // both children not exist
									 // stop heapifying
		return;
	}
	else if (!exist_current_r_child(n)) { // only left exist
		if (data[current_l_child(n)] < data[n]) { // need swap
			Type tempdata = data[current_l_child(n)];
			data[current_l_child(n)] = data[n];
			data[n] = tempdata;
			current_heapify_down(current_l_child(n));
		}
		return;
	}
	else // both exist
		 // if left child is smaller than right
		if (data[current_l_child(n)] < data[current_r_child(n)]) {
			if (data[current_l_child(n)] < data[n]) { // need swap
				Type tempdata = data[current_l_child(n)];
				data[current_l_child(n)] = data[n];
				data[n] = tempdata;
				current_heapify_down(current_l_child(n));
			}
		}
	// if right child is smaller
		else {
			if (data[current_r_child(n)] < data[n]) { // need swap
				Type tempdata = data[current_r_child(n)];
				data[current_r_child(n)] = data[n];
				data[n] = tempdata;
				current_heapify_down(current_r_child(n));
			}
		}
		return;
		/** \endcode */
}

template <class Type>
void DualHeap<Type>::pending_heapify_up(int n) {
	/** \code */
	if (n == pending_head()) // at root
		return;
	if (data[pending_parent(n)] > data[n]) { // need swap
		Type tempdata = data[pending_parent(n)];
		data[pending_parent(n)] = data[n];
		data[n] = tempdata;
		pending_heapify_up(pending_parent(n)); // recursive call to parent node
	}
	/** \endcode */
}
