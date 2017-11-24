/*
This contains the header file and implementation for methods of Selection class.
The following methods are implemented in this file: constructors, mutators, accessors, and helper functions.
*/
//
#ifndef SELECTION_H
#define SELECTION_H
#include <fstream>

#include <iostream>
#include <vector>
#include <limits>
#include <assert.h>
#include <math.h>
using namespace std;

template <class Type>
class Selection {
private:
	int HEAPSIZE;
	vector<vector<Type> > master_data; // copied the input vector of vectors to be able to access data

	typedef typename vector<Type>::iterator It;
	vector<It> its;     // iterators for each vector
	vector<int> data;   // Heap, containing indexes for iterators and master_data
	vector<Type> run;   // a vector to be used for output

	int size; // size of heap

			  //-- Support methods --//
			  /**  \fn int l_child(int)
			  *    \brief gets the index of the left child
			  *    \param  n is an int for the index
			  *    \pre the parameter should be entered as an int
			  *    \post the index of the left child is returned
			  */
	int l_child(int); // index of left child: general version

					  /**  \fn int r_child(int)
					  *    \brief gets the index of the right child
					  *    \param  n is an int for the index
					  *    \pre the parameter should be entered as an int
					  *    \post the index of the right child is returned
					  */
	int r_child(int); // index of right child: general version

					  /**  \fn int parent(int)
					  *    \brief gets the index of the parent node
					  *    \param n is an int for the index
					  *    \pre the parameter should be entered as an int
					  *    \post the index of the parent node is returned
					  */
	int parent(int); // index of parent node: general version

					 /**  \fn bool exist_l_child(int)
					 *    \brief verifies whether there is a left child
					 *    \param n is an int for the index
					 *    \pre the parameter should be entered as an int
					 *    \post the index of the left child is returned
					 */

	bool exist_l_child(int);

	/**  \fn bool exist_r_child(int)
	*    \brief verifies whether there is a right child
	*    \param n is an int for the index
	*    \pre the parameter should be entered as an int
	*    \post the index of the right child is returned
	*/

	bool exist_r_child(int);

	/**  \fn bool exist_parent(int)
	*    \brief verifies whether there is a parent node
	*    \param n is an int for the index
	*    \pre the parameter should be entered as an int
	*    \post the index of the parent node is returned
	*/

	bool exist_parent(int);

	/**	 \fn void push(int)
	*    \brief pushes the new item onto the heap
	*    \param index is int for the index of the item pushed
	*    \pre there should be items to push
	*    \post the new item is inserted into the heap and the size of heap incremented
	*/

	void push(int); // will increments size

					/**	 \fn Type pop()
					*    \brief pops an item from the heap
					*	 \pre there should be items to pop
					*    \post the item is popped from the heap and the size of heap decremented
					*/

	Type pop();    // pop from heap. If the vector pointed by the popped item reaches at the end of the vector, pop the item from the heap. otherwise, don't remove it, just increment the iterator of vector and do heapify_down

				   /**	 \fn int next(int)
				   *    \brief gets the next index from heap
				   *    \param n is an int for the index
				   *    \pre the parameter should be entered as an int
				   *    \post the next index for heap is returned
				   */

	int next(int);     // next index for  heap

					   /**	 \fn int head()
					   *    \brief gets the head of heap
					   *    \pre there should be a head
					   *    \post the head of heap is returned
					   */
	int head();    // head of heap

				   /**	 \fn int tail()
				   *    \brief gets the tail of heap
				   *    \pre there should be a tail
				   *    \post the tail of heap is returned
				   */

	int tail();    // tail of heap

				   /**	 \fn void heapify_up(int)
				   *    \brief heapifies up a node in heap
				   *	 \param  n is an int for the index
				   *    \pre checks whether the item in heap's head is the root
				   *    \post a node is heapified up in heap
				   */

	void heapify_up(int);      // heapify up a node in heap

							   /**	 \fn void heapify_down(int)
							   *    \brief heapifies down a node in heap
							   *	 \param  n is an int for the index
							   *    \pre checks whether the root has children
							   *    \post a node is heapified down in heap
							   */

	void heapify_down(int);    // heapify down a node in heap

public:
	/** Default constructor */
	Selection();
	/** Copy constructor */
	Selection(vector<vector<Type> >);

	/**	 \fn void init(vector<vector<Type> >)
	*    \brief initialize a vector of items
	*	 \param  items is a vector of vectors to hold items
	*    \pre the elements of the vector items should be vectors
	*    \post a vector of vectors containing items is returned
	*/

	void init(vector<vector<Type> >);

	/**	 \fn void sort()
	*    \brief sorts each list
	*    \pre the list to be sorted should not be empty
	*    \post each list is sorted
	*/

	void sort();

	/**	 \fn vector<Type> retrieve()
	*    \brief returns list of sorted items
	*    \pre there should some items in the list
	*    \post the sorted list is returned
	*/

	vector<Type> retrieve();   // returns list of sorted items

							   /**	 \fn void logFile(ofstream& )
							   *    \brief generates logfile
							   *	 \param logfile is of type ofstream for a pointer
							   *    \pre the argument should be a pointer
							   *    \post the logfile is returned
							   */

	void logFile(ofstream&);
};
#endif
