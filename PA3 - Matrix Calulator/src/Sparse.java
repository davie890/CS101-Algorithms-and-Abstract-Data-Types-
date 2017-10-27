/**
 * Davie Truong
 * dtruong8@ucsc.edu
 * 2/5/2017
 * CMPS 101 Algorithms and Abstract Data Types - Patrick Tantalo
 * Programming Assignment 3 - Sparse Client Implementation File
 */

import java.io.*;
import java.util.InputMismatchException;
import java.util.Scanner;

public class Sparse {

    public static void main(String [] args){
        if(args.length != 2){   // check to see if the user inputted two command line args
            System.err.println("You must open Sparse.java with two file arguments, input.txt and output.txt");
            System.exit(0);
        }

        String inputFile = args[0];
        String outputFile = args[1];

        Scanner in = null;
        PrintWriter out = null;
        String line;
        String [] token;
        int lineNumber = 0;
        int linesInA, linesInB;

        //String inputFile = "inp1.txt";
        //String outputFile = "otp1.txt";

        try {
            in = new Scanner(new File(inputFile));
        } catch (FileNotFoundException e) {
            System.out.println("File Opening Error");
        }
        try {
            out = new PrintWriter(new FileWriter(outputFile));
        } catch (IOException e) {
            e.printStackTrace();
        }

        // get the first line of the file so initialization can take place
        line = in.nextLine()+" ";             // get the data of the line
        token = line.split("\\s+");     // the line splits by using the empty space
        lineNumber++;                         // incrementL

        Matrix A = new Matrix(Integer.parseInt(token[0]));  // make a new matrix with the size given
        Matrix B = new Matrix(Integer.parseInt(token[0]));
        linesInA = Integer.parseInt(token[1]);              // set the number of entries of each matrix
        linesInB = Integer.parseInt(token[2]);

        while(in.hasNextLine()){
            line = in.nextLine()+" ";             // get the data of the line
            token = line.split("\\s+");     // the line splits by using the empty space
            lineNumber++;                         // increment to keep track of the position in the file
            // Assigns the values to entries in the matrix
            if(lineNumber > 2 && lineNumber <= linesInA + 2){
                A.changeEntry(Integer.parseInt(token[0]), Integer.parseInt(token[1]), Double.parseDouble(token[2]));
            }
            if(lineNumber > linesInA + 3 && lineNumber <= linesInA + 3 + linesInB){
                B.changeEntry(Integer.parseInt(token[0]), Integer.parseInt(token[1]), Double.parseDouble(token[2]));
            }
        }
        in.close();

        // Matrix Operations
        out.println("A has " + A.getNNZ() + " non-zero entries:");
        out.println(A);
        out.println("B has " + B.getNNZ() + " non-zero entries:" );
        out.println(B);
        out.println("(1.5)*A =");
        out.println(A.scalarMult(1.5));
        out.println("A+B =");
        out.println(A.add(B));
        out.println("A+A =");
        out.println(A.add(A));
        out.println("B-A =");
        out.println(B.sub(A));
        out.println("A-A =");
        out.println(A.sub(A));
        out.println("Transpose(A) =");
        out.println(A.transpose());
        out.println("A*B =");
        out.println(A.mult(B));
        out.println("B*B =");
        out.println(B.mult(B));
        out.close();
    }
}
