/**
 * Davie Truong
 * dtruong8@ucsc.edu
 * 2/5/2017
 * CMPS 101 Algorithms and Abstract Data Types - Patrick Tantalo
 * Programming Assignment 3 - Matrix ADT Test File
 */
//-----------------------------------------------------------------------------
//  MatrixTest.java
//  A test client for the Matrix ADT. Use this to test Matrix module.
//-----------------------------------------------------------------------------
public class MatrixTest{
    public static void main(String[] args){
        int n=3;
        Matrix A = new Matrix(n);
        Matrix B = new Matrix(n);

        A.changeEntry(1,1,1); B.changeEntry(1,1,1);
        A.changeEntry(1,2,2); B.changeEntry(1,2,0);
        A.changeEntry(1,3,3); B.changeEntry(1,3,1);
        A.changeEntry(2,1,4); B.changeEntry(2,1,0);
        A.changeEntry(2,2,5); B.changeEntry(2,2,1);
        A.changeEntry(2,3,6); B.changeEntry(2,3,0);
        A.changeEntry(3,1,7); B.changeEntry(3,1,1);
        A.changeEntry(3,2,8); B.changeEntry(3,2,1);
        A.changeEntry(3,3,9); B.changeEntry(3,3,1);

        System.out.println("A has " + A.getNNZ() + " non-zero entries:");
        System.out.println("A has the Sie: " + A.getSize());
        System.out.println(A);

        System.out.println("B has " + B.getNNZ() + " non-zero entries:" );
        System.out.println(B);

        System.out.println("(1.5)*A");
        Matrix C = A.scalarMult(1.5);
        System.out.println(C);

        System.out.println("A+B=");
        Matrix D = A.add(B);
        System.out.println(D);

        System.out.println("A+A=");
        Matrix E = A.add(A);
        System.out.println(E);

        System.out.println("B-A");
        Matrix F = B.sub(A);
        System.out.println(F);

        System.out.println("A-A");
        Matrix G = A.sub(A);
        System.out.println(G);

        System.out.println("Transpose(A)");
        Matrix H = A.transpose();
        System.out.println(H);

        System.out.println("A*B");
        Matrix I = A.mult(B);
        System.out.println(I);

        System.out.println("B*B");
        Matrix J = B.mult(B);
        System.out.println(J);

        System.out.println("Printing a copy of A");
        Matrix K = A.copy();
        System.out.println(K);

        System.out.println("Does A = B");
        System.out.println(A.equals(B));
        System.out.println("Does A = A");
        System.out.println(A.equals(A));

        System.out.println("Clearing out Matrix A");
        System.out.println("Values in A: " + A.getNNZ());
        A.makeZero();
        System.out.println("Values after clearing A: " + A.getNNZ());
        System.out.println("Printing A: ");
        System.out.println(A);

    }
}