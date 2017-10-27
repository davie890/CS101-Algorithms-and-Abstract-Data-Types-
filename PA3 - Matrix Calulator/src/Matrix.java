/**
 * Davie Truong
 * dtruong8@ucsc.edu
 * 2/4/2017
 * CMPS 101 Algorithms and Abstract Data Types - Patrick Tantalo
 * Programming Assignment 3 - Matrix ADT File
 */

// Matrix ADT
public class Matrix {

    // private inner class that encapsulates the column and value information
    // corresponding to a matrix entry
    private class Entry{
        // Fields
        int col;
        double value;

        // Constructor
        Entry(int inputCol, double inputValue){
            this.col = inputCol;                // creates the entry object with the user's data
            this.value = inputValue;
        }

        // OverRide of the equals method
        public boolean equals(Object x){
            boolean similarState = false;   // initialize the bool value to false
            if(x instanceof  Entry) {
                if (this.value == ((Entry) x).value && this.col == ((Entry) x).col) {
                    similarState = true;    // compares the fields of the two entries
                }                           // sets similarState to true if they are the same
            }
            return similarState;
        }

        // OverRide the toString methid
        public String toString() {
            return "(" + col + ", " + value + ')';
        }
    }

    private List [] row;    // Declares the list of row so methods can access it
    private int NNZ;
    private int size;

    // Constructor
    // Makes a new n x n matrix     // PreCond: n>=1
    Matrix(int n){
        if(n < 1){
            throw new RuntimeException("Matrix Creation Error: the size of the matrix has to be greater than 0");
        }
        row = new List[n+1];  // initializes the array list of rows with size given by user
        NNZ = 0;            // Number of non zero entries is 0 since there are no entries
        size = n;           // the size of the matrix is given by the user input
        for(int i = 1; i <= n; i++){
            row[i] = new List();             // makes a list in each row
        }
    }

    // Access Functions
    // returns n, the number of rows of the matrix
    int getSize(){
        return size;
    }
    // Returns the number of non-zero entries in this Matrix
    int getNNZ(){
        NNZ = 0;
        for(int i = 1; i <= this.size; i++){    // iterate through every row of the list
            NNZ += row[i].length();           // add to count the length of each row
        }
        return NNZ;
    }
    // Overrides Object's equals method
    public boolean equals(Object x){
        if(!(x instanceof  Matrix)){
            return false;
        }
        if(this.getSize() != ((Matrix) x).getSize()){   // checks to see if the matrix have the same size
            return false;
        }
        for(int i = 1; i <= getSize(); i++){    // for the length of number of rows in the matrix
            if(!(this.row[i].equals(((Matrix) x).row[i]))){  // check to see if the contents of each row are not similar
                return false;
            }
        }
       return true;
    }

    // Manipulation Procedures
    // Sets this matrix to the zero state
    void makeZero(){
        for(int i = 1; i <= this.size; i++){    // iterate through every row of the list
            row[i].clear();                     // uses the list manipulation method to clear the pointers
        }
        this.NNZ = 0;
    }
    // Returns a new matrix having the same entries as this matrix
    Matrix copy(){
        Matrix cloneMatrix = new Matrix(this.getSize());    // creates a new matrix that will store the copied data
        for(int i = 1; i <= this.size; i++){                // loops all the rows
            row[i].moveFront();                     // moves the cursor to the front entry of the row
            while(row[i].index() != -1){            // while the cursor is still on the list
                Entry temp = (Entry) row[i].get();
                Entry inputEntry = new Entry(temp.col, temp.value);
                cloneMatrix.row[i].append(inputEntry);
                row[i].moveNext();
            }
        }
        cloneMatrix.NNZ = this.NNZ;
        return cloneMatrix;
    }
    // Changes ith row, jth column of this matrix to x
    // PreCond: 1<=i<=size, 1<=j<=size
    void changeEntry(int i,int j,double x){
        if(i < 1 || j < 1 || i > size || j > size){
            throw new RuntimeException("changeEntry error: invalid location given");
        }
        row[i].moveFront();     //set the cursor to the front of the list
        if(x == 0.0) {          // if the user is trying to delete an entry
            while (row[i].index() != -1) {    // runs until the cursor falls off the list
                Entry currentEntry = (Entry) row[i].get();  // gets the entry at the current position and stores it
                if (currentEntry.col == j) {      //if the positions match
                    row[i].delete();
                    NNZ -= 1;           // 1 less Number of Non Zero
                    return;
                } else {
                    row[i].moveNext();      // continue with next position until found or falls off the list
                }
            }
        }
        if(x != 0.0){           // if the user is trying to add an entry
            if(row[i].index() == -1 || ((Entry) row[i].back()).col < j ){// if the list is empty or the last col is < j
                row[i].append(new Entry(j,x));      // add it to the end of the list
                NNZ += 1;
                return;
            }
            else {   // need to loop through the list to see where to insert
                while (row[i].index() != -1) {    // runs until the cursor falls off the list
                    Entry currentEntry = (Entry) row[i].get();  // gets the entry of the current position
                    if (currentEntry.col == j) {      // if the row and columns are the same
                        currentEntry.value = x;
                        return;
                    }
                    if (currentEntry.col > j) {        // if the column is greater than our desired position
                        row[i].insertBefore(new Entry(j, x));    // the while loop should put the inserted value before
                        NNZ += 1;
                        return;                                 // current position because loop stops when col > j
                    }
                    row[i].moveNext();
                }
            }
        }
    }
    // Returns a new matrix that is the scalar product of this matrix with x
    Matrix scalarMult(double x){
        Matrix result = this.copy();            // creates a copy of the current matrix
        for(int i = 1; i <= this.size; i++){    // iterates every row
            result.row[i].moveFront();          // sets the cursor to the front of the current row
            while(result.row[i].index() != -1){     // runs until every column of the row has been touched
                Entry currentEntry = (Entry) result.row[i].get();   // stores the current entry into a temp location
                result.changeEntry(i, currentEntry.col, currentEntry.value * x);    //updates the value at the given location
                result.row[i].moveNext();       // move to the next value
            }
        }
        return result;
    }
    // Returns a new Matrix that is the sum of this Matrix with M
    // PreCond: getSize() == M.getSize()
    Matrix add(Matrix M){
        if(this.size != M.getSize()){
            throw new RuntimeException("Add error: Unable to add matrices of different sizes");
        }
        if(this == M){                 // for when the matrices are the same
            return this.copy().scalarMult(2);       // multiply it by two
        }
        Matrix result = new Matrix(this.size);
        int count = 0;
        for(int i = 1; i <= this.size; i++){
            result.row[i] = AddorSub(row[i], M.row[i], 1);
            count += result.row[i].length();        // keeps track of the NNZ since entries could have changed
        }
        result.NNZ = count;     // updates the NNZ in the final results
        return result;
    }
    // Returns a new Matrix that is the difference of this matrix with M
    // PreCond: getSize() == M.getSize()
    Matrix sub(Matrix M){
        if(this.size != M.getSize()){
            throw new RuntimeException("Subtraction error: Unable to add matrices of different sizes");
        }
        if(this == M){                  // for when the matrices are the same
            return new Matrix(this.size);       // return a new empty matrix
        }
        Matrix result = new Matrix(this.size);
        int count = 0;
        for(int i = 1; i <= this.size; i++){
            result.row[i] = AddorSub(row[i], M.row[i], -1);
            count += result.row[i].length();        // keeps track of the NNZ since entries could have changed
        }
        result.NNZ = count;     // updates the NNZ in the final results
        return result;
    }
    // Returns a new Matrix that is the transpose of this matrix
    Matrix transpose(){
        Matrix result = new Matrix(this.size);
        for(int i = 1; i <= this.size; i++){
            row[i].moveFront();
            while(row[i].index() != -1) {
                result.changeEntry(((Entry) row[i].get()).col, i, ((Entry) row[i].get()).value);
                row[i].moveNext();
            }
        }
        result.NNZ = this.NNZ;
        return result;
    }
    // Returns a new matrix that is the product of this Matrix with M
    // PreCond: getSize() == M.getSize()
    Matrix mult(Matrix M) {
        if (this.size != M.getSize()) {
            throw new RuntimeException("Multiplication error: Unable to add matrices of different sizes");
        }
        Matrix result = new Matrix(this.size);  // used to store the resulting product
        Matrix temp = M.transpose();            // transpose of M make it easier to find the multi
        int count = 0;
        for (int i = 1; i <= this.size; i++) {        // loops through the first list
            for (int j = 1; j <= temp.size; j++){     // loops through the transposed list
                result.changeEntry(i, j, dot(row[i], temp.row[j]));     // stores the dot product of each list into the
            }                                                           // the new matrix
            count += result.row[i].length();    // gets the count NNZ for the current row before we move on to the next
        }
        result.NNZ = count;     // updates the result's NNZ count before giving back to the user
        return result;
    }

    // Other functions
    // Overrides object's toString() method
    public String toString(){
         String output = new String();
         for(int i = 1; i <= this.size; i++){
             if(row[i].length() != 0) {         // condition used so empty lines don't get printed
                 output += i + ": " + row[i] + "\r\n";
             }
         }
         return output;
    }

    private List AddorSub(List a, List b, int decision){
        List result = new List();       // makes a new list that will store the result of the two lists
        a.moveFront();      // start at the beginning of the list
        b.moveFront();
        while(a.index() >= 0 || b.index() >= 0){       // runs until both are -1
            if(a.index() != -1 && b.index() != -1) {      // if there are entries on both lists
                Entry left = (Entry) a.get();   // stores the entries of both current positions
                Entry right = (Entry) b.get();
                if (left.col < right.col) {       // if the cols are not equal that means the value is missing
                    result.append(new Entry(left.col, left.value)); // add that missing value to the list
                    a.moveNext();
                } else if (left.col > right.col) {  // checks both cases when the col are not equal to add and iterate the right
                    if(decision == -1){         // checks to see if the decision was to do subtraction, which turns the b value neg
                        result.append(new Entry(right.col, -1 *right.value));
                    }
                    else{
                        result.append(new Entry(right.col, right.value));       // adds the result to the list
                    }
                    b.moveNext();
                } else {   // the col equal, we can do the decision
                    if (decision == 1) {      // we do addition
                        double sum = left.value + right.value;          // do the addition
                        if (sum != 0) {                                 // check if the value is not zero
                            result.append(new Entry(left.col, sum));    // add to the list
                        }
                    }
                    if (decision == -1) {     // we do subtraction
                        double difference = left.value - right.value;       // do the subtraction
                        if (difference != 0) {                              // check if the value is not zero
                            result.append(new Entry(left.col, difference)); // add to the list
                        }
                    }
                    a.moveNext();       // iterate to the next entries
                    b.moveNext();
                }
            }
            else if(a.index() != -1 && b.index() == -1){     // if list b ran out of entries continue with list a
                Entry left = (Entry) a.get();               // stores the entry so it can be accessed
                result.append(new Entry(left.col, left.value)); // append it because no matter what the values will be positive
                a.moveNext();
            }
            else{   // the list of a ran out while b still had more entries
                Entry right = (Entry) b.get();
                if(decision == -1){         // checks to see if the decision was to do subtraction, which turns the b value neg
                    result.append(new Entry(right.col, -1 *right.value));
                }
                else{
                    result.append(new Entry(right.col, right.value));       // adds the result to the list
                }
                b.moveNext();
            }
        }
        return result;
    }
    private static double dot(List a, List b){
        double dotProduct = 0.0;
        a.moveFront();
        b.moveFront();
        while(a.index() != -1 && b.index() != -1){
            Entry left = (Entry) a.get();   // stores the entries of both current positions
            Entry right = (Entry) b.get();
            if(left.col < right.col){       // list a is behind
                a.moveNext();
            }
            else if(left.col > right.col){  // list b is is behind
                b.moveNext();
            }
            else{   // both entries are on the same column
                dotProduct += (left.value * right.value);
                a.moveNext();
                b.moveNext();
            }
        }
        return dotProduct;
    }
}
