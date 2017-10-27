/**
 * Davie Truong
 * dtruong8@ucsc.edu
 * 1/15/2017
 * CMPS 101 Algorithms and Abstract Data Types - Patrick Tantalo
 * Programming Assignment 1 - Lex Implementation file
 */

import java.io.*;


public class Lex {

    public static void main(String[] args){
        if(args.length != 2){       // check to see if the user inputted two command line args
            System.err.println("You must open lex.java with two file arguments, input.txt and output.txt");
            System.exit(0);
        }

        String inputFile = args[0];
        String outputFile = args[1];
        int linesInFile = 0;
        String line;

        // Opening the file to get the number of lines in the file
        try{
            BufferedReader input = new BufferedReader(new FileReader(inputFile));
            while((input.readLine()) != null){
                linesInFile += 1;
            }
            input.close();
        }catch(Exception e){
            System.out.println("Input File Not Found");
        }

        // Make a String array with size number of words in the file
        String [] wordArr = new String [linesInFile];
        // Opening the file to put the words into the array
        try{
            BufferedReader input = new BufferedReader(new FileReader(inputFile));
            int i = 0;
            while((line = input.readLine()) != null){
                wordArr[i] = line;
                i++;
            }
            input.close();
        }catch(Exception e){
            System.out.println("Input File Not Found");
        }
        // Gets the array of words and uses the list ADT to sort the array of words in alphabetical order without changing it
        List intList = new List();  // creates an empty list
        intList.append(0);          // append the first word/int to the list so there is a starting point
        for(int i = 1; i < linesInFile; i++){
            intList.moveFront();    // sets the cursor at the front of the list\
            boolean completeInsertion = false;  // used as a loop control to determine if the index gets added
            while(completeInsertion == false)  // if the insertion has not been made
            {
                if(intList.index() < 0){        // checks to see if the cursor fell of the list
                    intList.append(i);     // if the cursor fell of the list it means the data is greatest value of list
                    completeInsertion = true;   // set the loop control to true so it can exit out and start next data
                }else if(wordArr[intList.get()].compareTo(wordArr[i]) > 0){   // checks to see if data is less than current
                intList.insertBefore(i);        // insert before because the data is less then current index data
                completeInsertion = true;       // set loop control to true so it can exit and start on next data
                }else{
                intList.moveNext();   // moves the index next because the data is greater so can't insert before
                }
            }
        }
        // Opens the output file to store the user's words in alphabetical order
        try{
            PrintWriter output = new PrintWriter(outputFile);
            intList.moveFront();
            for(int i = 0; i < linesInFile; i++){
                output.println(wordArr[intList.get()]);
                intList.moveNext();
            }
            output.close();
        }catch(Exception e){
            System.out.println("Output File Not Found");
        }
    }
}

