/**
 * Davie Truong
 * dtruong8@ucsc.edu
 * 1/15/2017
 * CMPS 101 Algorithms and Abstract Data Types - Patrick Tantalo
 * Programming Assignment 1 - ListClient.java
 */
//-----------------------------------------------------------------------------
//  ListClient.java
//  A test client for the List ADT. Use this to test your list module.
//-----------------------------------------------------------------------------

public class ListClient{
    public static void main(String[] args){
        List A = new List();
        List B = new List();

        for(int i=1; i<=20; i++){
            A.append(i);
            B.prepend(i);
        }
        System.out.println(A);
        System.out.println(B);

        for(A.moveFront(); A.index()>=0; A.moveNext()){
            System.out.print(A.get()+" ");
        }
        System.out.println();
        for(B.moveBack(); B.index()>=0; B.movePrev()){
            System.out.print(B.get()+" ");
        }
        System.out.println();

        List C = A.copy();
        System.out.println(A.equals(B));
        System.out.println(B.equals(C));
        System.out.println(C.equals(A));

        A.moveFront();
        for(int i=0; i<5; i++) A.moveNext(); // at index 5
        A.insertBefore(-1);                  // at index 6
        for(int i=0; i<9; i++) A.moveNext(); // at index 15
        A.insertAfter(-2);
        for(int i=0; i<5; i++) A.movePrev(); // at index 10
        A.delete();
        System.out.println(A);
        System.out.println(A.length());
        A.clear();
        System.out.println(A.length());
    }
}