/**
 * Davie Truong
 * dtruong8@ucsc.edu
 * 2/4/2017
 * CMPS 101 Algorithms and Abstract Data Types - Patrick Tantalo
 * Programming Assignment 3 - List ADT File
 */

// A list ADT
class List {

    // Inner Node Of the List (contains the client data)
    private class Node{
        // Fields
        Object data;                       // client's data
        Node next;                      // points to the next node on the list
        Node prev;                      // points to the previous node on the list
        // Constructor
        Node(Object inputData) {           // constructs a new node with given inputData
            this.data = inputData;      // updates the node with the client's data
            this.next = null;           // next pointer assigned null until position is determined
            this.prev = null;           // previous pointer assigned null until position is determined
        }
        Node(Object inputData, Node prev, Node next){  // constructs a new node with all data given
            this.data = inputData;      // assigns the node with the given input data
            this.prev = prev;           // points the node's prev arrow to given input location
            this.next = next;           // points the node's next arrow to the given input location
        }
        // Equals operation used to override
        public boolean equals(Object x){
            boolean similar = false;
            if(x instanceof Node){      // first checks to see if x is a subclass of node
                similar = this.data.equals(x);  // compares if the two data are the same
            }
            return similar;
        }

        // toString overRide for the data which calls the Matrix's toString
        public String toString(){
            return data.toString();
        }
    }

    // Fields
    private Node front;     //  First Node on the list
    private Node back;      //  Last Node on the list
    private Node cursor;   //  Cursor Node (Node that cursor and index are currently at)
    private int length;     //  The current length of the list
    private int index;      //  the position of the cursor relative to the list

    // Constructor
    // constructs an empty list
    List(){
        front = back = cursor = null;   // assigns the default nodes to null, since there is nothing to point to
        length = 0;                     // length of the list is empty
        index = -1;                     // there is no index to store because there is no node
    }

    // Access Functions
    // Returns the number of elements in the list
    int length(){
        return length;
    }
    // Returns the index of the cursor element (PreCond: the cursor is defined) -1 otherwise
    int index(){
        if(cursor != null) {        // if the cursor is pointing to something return the index position
            return index;
        }else {
            return -1;              // else give the index -1 because the cursor is off the list
        }
    }
    // Returns the front element (Front Node data) (PreCond: length()> 0)
    Object front(){
        if(this.length() <= 0){
            throw new RuntimeException("Retrieval Error: getFront() called on an empty List");
        }
        return front.data;      // sends back the data of the front node if it exist
    }
    // Returns the back element (Back Node data) (PreCond: length()> 0)
    Object back(){
        if(this.length() <= 0){
            throw new RuntimeException("Retrieval Error: getBack() called on an empty List");
        }
        return back.data;       // sends back the data of the rear node if it exist
    }
    // Returns the Cursor Element (Cursor Node data) (PreCond: Length() > 0, index() >=0)
    Object get(){
        if(this.length() <= 0){
            throw new RuntimeException("Retrieval Error: getCursor() called on an empty List");
        }
        if(this.index() < 0){
            throw new RuntimeException("Retrieval Error: getCursor called on invalid Index");
        }
        return cursor.data;
    }
    // Returns true (PreCond: the List and userInput L are the same Integer Sequence)
    // The cursor is ignored in both lists.
    boolean equals(List L){
        if(this.length() != L.length()) {      // If the length of the two list are not equal
            return false;                      // automatically  invalidates their equality
        }
        Node clientFront = L.front;    // makes a new node that has the same data as the front node of User's list
        Node thisFront = this.front;   // makes a new node that has the same data as the front node of "this" list
        while(clientFront.next != null && thisFront.next != null){  // stops iterating when the comparing nodes are null
            if(!(clientFront.data.equals(thisFront.data)))      // compares the data of both nodes
                return false;
            clientFront = clientFront.next;         // iterates the comparing nodes
            thisFront = thisFront.next;
        }
        return true;
    }

    // Manipulation Procedures
    // Resets The list to its original empty state
    void clear(){
        front = back = cursor = null;   // sets the list data all to null so it is not pointing to any node
        this.length = 0;                // list has no more nodes so length is assigned 0
        this.index = -1;                // there is no cursor or index to keep track of so assign -1
    }
    // Places the cursor under the front element (PreCond: the list is not empty), if it is empty do nothing
    void moveFront(){
        if(this.length() >= 1){         // checks that the list is not empty
            this.cursor = this.front;   // assigns the cursor to point at the front element
            this.index = 0;             // index gets updated 0
        }
    }
    // Places the cursor under the back element (PreCond: the list is not empty), if it is empty do nothing
    void moveBack(){
        if(this.length() >= 1){         // checks that the list is not empty
            this.cursor = this.back;            // assigns the cursor to point at the back element
            this.index = this.length() - 1;     // the index gets assigned the the last index of the list
        }
    }
    // Moves cursor one step towards front of the list when (PreCond: Cursor is defined and not at front)
    // Cursor becomes undefined (PreCond: cursor is defined and at the front of the list)
    // Do nothing (PreCond: cursor is undefined)
    void movePrev(){
        if(this.cursor != null && this.index != 0){
            this.cursor = this.cursor.prev;
            this.index -= 1;
        }else if(this.cursor != null && this.index == 0){
            this.cursor = null;
            this.index -= 1;
        }
    }
    // Moves cursor one step towards back of the list (PreCond: cursor is defined and not at back)
    // Cursor becomes undefined (PreCond: if cursor is defined and at the back)
    // Do nothing (PreCond: cursor is undefined)
    void moveNext(){
        if(this.cursor != null && this.index != this.length() - 1){
            cursor = cursor.next;
            index += 1;
        }else if(this.cursor != null && this.index == this.length() - 1){
            cursor = null;
            index = -1;
        }
    }
    // Insert new element into list. If list is not empty insertion takes place before front node
    void prepend(Object data){
        Node newNode = new Node(data, null, front); // Creates node with user data and assigns front to null or
        if(this.front == null){ // if list is empty     // current front depending if list is empty or not
            this.back = newNode;    // the new node is now the back
        }else{                  // if the list is not empty
            this.front.prev = newNode;  // the prev pointer of the front node now points toward newNode
        }
        this.front = newNode;   // front is assigned newNode no matter the situation
        this.length += 1;
    }
    // Insert new Node into list. If the list is not empty insertion take places after back node
    void append(Object data){
        Node newNode = new Node(data, back, null);  // makes a new node
        if(this.front == null){
            this.front = newNode;
        }else{
            this.back.next = newNode;
        }
        this.back = newNode;
        this.length += 1;
    }
    // Insert new Node before cursor (PreCond: length() > 0, index() >= 0)
    void insertBefore(Object data){
        if(this.length() <= 0){
            throw new RuntimeException("Insertion Error: Unable to Insert an empty list, try append or prepend");
        }
        if(this.index() < 0){
            throw new RuntimeException("Insertion Error: Index out of bounds");
        }
        Node newNode = new Node(data, this.cursor.prev, this.cursor);
        if(this.cursor.prev != null){
            this.cursor.prev.next = newNode;
        } else{
            this.front = newNode;
        }
        this.cursor.prev = newNode;
        this.length += 1;
    }
    // Insert new Node After cursor (PreCond: length() > 0, index() >= 0)
    void insertAfter(Object data){
        if(this.length() <= 0) {
            throw new RuntimeException("Insertion Error: Unable to Insert an empty list, try append or prepend");
        }
        if(this.index() < 0) {
            throw new RuntimeException("Insertion Error: Index out of bounds");
        }
        Node newNode = new Node(data, this.cursor, this.cursor.next);
        if(this.cursor.next != null){
            this.cursor.next.prev = newNode;
        }else{
            back = newNode;
        }
        this.cursor.next = newNode;
        this.length += 1;
    }
    // Deletes the front element (PreCond: length() > 0)
    void deleteFront(){
        if(this.length() <= 0) {
            throw new RuntimeException("Deletion Error: Unable to delete from an empty List");
        }
        if(this.length() == 1){  // When there is only 1 element in the list
            this.front = this.back = this.cursor = null;
            this.length -= 1;
            this.index = -1;
        }
        this.front = this.front.next;
        this.front.prev = null;
        this.length -= 1;
    }
    // Delete the back element (PreCond: length() > 0)
    void deleteBack(){
        if(this.length() <= 0) {
            throw new RuntimeException("Deletion Error: Unable to delete from an empty List");
        }
        if(this.length() == 1) {  // When there is only 1 element in the list
            this.front = this.back = this.cursor = null;
            this.length -= 1;
            this.index = -1;
        }
        this.back = this.back.prev;
        this.back.next = null;
        this.length -= 1;
    }
    // Deletes Cursor element, making cursor undefined (PreCond: length() > 0, index() >= 0)
    void delete(){
        if(this.length() <= 0) {
            throw new RuntimeException("Deletion Error: Unable to delete from an empty List");
        }
        if(this.index < 0){
            throw new RuntimeException("Deletion Error: Cursor at invalid location");
        }
        if(this.cursor == this.front){  // if the cursor is at the front element
            deleteFront();
        }else if(this.cursor == this.back){     // if the cursor is at the back
            deleteBack();
        }else {                                 // if the cursor is in between 2 elements
            this.cursor.prev.next = this.cursor.next;   // reassign pointers and updates the list data
            this.cursor.next.prev = this.cursor.prev;
            this.cursor = null;
            this.index = -1;
            this.length -= 1;
        }

    }

    // Other Methods
    // Overrides Object's toString Method
    // Returns a String representation of the list consisting of a space separated
    // sequence of integers, with front on left
    public String toString(){
        String output = new String();           // creates a string object to store the list of data
        Node CurrentNode = this.front;          // gets the front of the list
        while(CurrentNode != null){             // runs until the end of the list
            output +=  CurrentNode.data + " ";
            CurrentNode = CurrentNode.next;
        }
        return output;
    }
}