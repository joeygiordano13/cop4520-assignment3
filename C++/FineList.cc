#include <iostream>
#include <thread>
#include <mutex>

class Node {
    public:
        unsigned int value;
        Node *next;
        std::mutex lock; // lock each node
        
        Node(int val) {
            value = val;
            next = NULL;
            lock.unlock();
        }
};

class FineList {
    private:
        Node *head;
        std::mutex lock;
    public:
        // Constructor
        FineList() {
            head = NULL;
            lock.unlock();
        }
        // Insert method
        void insert(unsigned int val) {
            // Create new node
            Node *newNode = new Node(val);
            // Check if list is empty
            if (isEmpty()) {
                lock.lock();
                head = newNode;
                lock.unlock();
                return;
            }
            // Start @ head
            Node *prev, *cur; 
            prev = head;
            cur = head->next;
            // Lock entire list
            lock.lock();
            // Lock first node
            prev->lock.lock();
            // Unlock list
            lock.unlock();
            // Lock cur if exists
            if (cur) {
                cur->lock.lock();
            }

            // Move through list until insertion
            // point found, or reached list end.
            while (cur) {
                // Reached insertion point
                if (cur->value > val)
                    break;

                Node *old_prev = prev;
                prev = cur;
                cur = cur->next;
                // Deal with locks
                old_prev->lock.unlock();
                // If the new curNode isn't 
                // end of list, lock it.
                if (cur) {
                    cur->lock.lock();
                }
            }
            // Found insertion point
            newNode->next = cur;
            prev->next = newNode;
            // Deal with locks
            prev->lock.unlock();
            if (cur) {
                cur->lock.unlock();
            }
        }
        // Remove method
        void remove(unsigned int val) {
            // Start @ head
            Node *prev, *cur; 
            prev = head;
            cur = head->next;
            // Lock entire list
            lock.lock();
            // Lock first node
            prev->lock.lock();
            // Unlock list
            lock.unlock();
            // Lock cur if exists
            if (cur) {
                cur->lock.lock();
            }

            // Move through list until removal
            // point found, or reached list end.
            while (cur) {
                // Reached insertion point
                if (cur->value == val) {
                    prev->next = cur->next;
                    prev->lock.unlock();
                    cur->lock.unlock();
                    delete cur;
                    return;
                }

                Node *old_prev = prev;
                prev = cur;
                old_prev->lock.unlock();
                if (cur) {
                    cur->lock.lock();
                }
            }
            // Reached end of list, 
            // nothing removed
            prev->lock.unlock();
        }
        // isEmpty method
        bool isEmpty() {
            // Lock list, check head, and unlock.
            lock.lock();
            bool listEmpty = head == NULL;
            lock.unlock();
            return listEmpty;
        }
        // Contains method, equivalent to removal, 
        // but only need a single pointer & lock.
        bool contains(int val) {
            // Check if list is empty
            if (isEmpty()) {
                return false;
            }
            // Start @ head
            Node *cur = head;
            // Place lock on cur
            if (cur) {
                cur->lock.lock();
            }
            // Loop through list, 
            // checking for value
            while (cur) {
                if (cur->value == val) {
                    // Release lock
                    cur->lock.unlock();
                    return true;
                }
            }
            // Value not found in 
            // list, release lock
            cur->lock.unlock();
            return false;
        }
};