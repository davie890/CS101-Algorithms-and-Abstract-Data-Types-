/**
 * Davie Truong
 * dtruong8@ucsc.edu
 * 2/4/2017
 * CMPS 101 Algorithms and Abstract Data Types - Patrick Tantalo
 * Programming Assignment 3 - ListTest.java
 */
//-----------------------------------------------------------------------------
//  ListTest.java
//  A test client for the List ADT. Use this to test list module.
//-----------------------------------------------------------------------------

public class ListTest{
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

        System.out.println(A.equals(B));

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