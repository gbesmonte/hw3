#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot){
	if (head == nullptr){
		//just in case there is garbage and it is not null
		smaller = nullptr;
		larger = nullptr;
    return;
  }
	
	if (head->val <= pivot){
		Node* temp = head->next;
		split(temp, smaller, larger);
		if (smaller == nullptr){
			head->next = nullptr;
			smaller = head;
			head = temp;
		}
		else{
			head->next = smaller;
			smaller = head;
			head = temp;
		}
	}
	else if (head->val > pivot){
		Node* temp = head->next;
		split(temp, smaller, larger);
		if (larger == nullptr){
			head->next = nullptr;
			larger = head;
			head = temp;
		}
		else{
			head->next = larger;
			larger = head;
			head = temp;
		}
	}
}