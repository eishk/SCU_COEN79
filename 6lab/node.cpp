// FILE: node.cpp
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t

using namespace std;

namespace coen79_lab6
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
		const node *cursor;
		size_t answer;

		answer = 0;
		for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
			++answer;

		return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
    	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	const node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, source_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr->link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    source_ptr = source_ptr->link( );
    	}
    }

    void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr) {
		head_ptr = NULL;
        tail_ptr = NULL;

		// return if starting point is null or equal to ending pointer
		if (start_ptr == NULL || start_ptr == end_ptr) {
            return;
        }
        
		// loop through part of original LinkedList and inserting the nodes into new Linkedlist
		while (start_ptr != NULL &&  start_ptr != end_ptr) {
            // insert first node into the new linkedlist if new head is null, otherwise append to the tail
			if (head_ptr == NULL) {
                list_head_insert(head_ptr,  start_ptr->data());
                tail_ptr = head_ptr;
            } else {
                list_insert(tail_ptr,  start_ptr->data());
                tail_ptr = tail_ptr->link();
            }

            start_ptr =  start_ptr->link();
        }
	}
    
	size_t list_occurrences(node* head_ptr, const node::value_type& target) {
		size_t count = 0;
        
		// looping through linkedlist and counting number of nodes that has target
		while (head_ptr != NULL) {
			// increment count when current node matches target
            if (head_ptr->data() == target) {
                count++;
            }

            head_ptr = head_ptr->link();
        }
        
		return count;
	}
    
	void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position) {
		assert(position > 0 && position <= list_length(head_ptr) + 1);
        
		// insert at head if position is 1
		if (position == 1) {
            list_head_insert(head_ptr, entry);
            return;
        }
        
		node* temp = list_locate(head_ptr, position - 1);
        list_insert(temp, entry);
	}
    
	node::value_type list_remove_at(node*& head_ptr, size_t position) {
		assert(position > 0 && position <= list_length(head_ptr));
        
		// delete the first node (head) in the linkedlist
		if (position == 1) {
            node* temp = head_ptr->link();
            list_head_remove(head_ptr);
            return temp->data();
        }
        
		node* prev = list_locate(head_ptr, position - 1);
        node* temp = prev->link();
        list_remove(prev);
        return temp->data();
	}
    
	node* list_copy_segment(node* head_ptr, size_t start, size_t finish) {
		assert((1 <= start) && (start <= finish) && (finish <= list_length(head_ptr)));
        
		node* newHead = NULL;
        node* tmp = head_ptr;
        
		// move starting tmp cursor to the start position's node of the original LinkedList
		for (size_t i = 1; i < start; i++) {
            tmp = tmp->link();
        }
        
		list_head_insert(newHead, tmp->data());
        tmp = tmp->link();
        node* cursor = newHead;
        
		// insert one by one each node into new linkedlist til the ending position
		for (size_t i = start; i < finish; i++) {
            list_insert(cursor, tmp->data());
            tmp = tmp->link();
            cursor = cursor->link();
        }

        return newHead;
	}
    
	void list_print(const node* head_ptr) {
		// looping through linkedlist and printing contents of each node
		while (head_ptr != NULL) {
            
			/* last element, print data without comma or whitespace, 
			   otherwise print data and then comma along with whitespace after*/
			if (head_ptr->link() == NULL) {
				cout << head_ptr->data();
				break;
			} else {
				cout << head_ptr->data() << ", ";
			}

			head_ptr = head_ptr->link();
        }
        cout << "\n";
	}
    
	void list_remove_dups(node* head_ptr) {
		node* cursor = head_ptr;
		node* runner;

		// loop through each node one by one
        while (cursor != NULL) {
			
			runner = cursor;

           // stop at one node and traverse through the rest of linkedlist to find dups
		   while (runner->link() != NULL) {
                // found duplicated delete node, otherwise traverse to next node
				if (runner->link()->data() == cursor->data()) {
					list_remove(runner);
                } else {
					runner = runner->link();
                }
            }

            cursor = cursor->link();
        }
	}
    
	node* list_detect_loop(node* head_ptr) {
		node* slow_ptr = head_ptr;
        node* fast_ptr = head_ptr;

		// looping through list and stops when loop is detected
		while (fast_ptr != NULL && fast_ptr->link() != NULL){
            slow_ptr = slow_ptr->link();
            fast_ptr = fast_ptr->link()->link();
            
			// loop detected and break
			if(fast_ptr == slow_ptr){
                break;
            }
        }
        
		// return null if empty list or end of list without loops (if at the tail)
		if (fast_ptr == NULL || fast_ptr->link() == NULL){
            return NULL;
        }

        slow_ptr = head_ptr;
        
		// loop to find the node that starts the loop
		while (slow_ptr != fast_ptr) {
            slow_ptr = slow_ptr->link();
            fast_ptr = fast_ptr->link();
        }
        
		return slow_ptr;
    }
    
}
