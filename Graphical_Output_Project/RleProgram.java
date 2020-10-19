import java.util.Scanner;

public class RleProgram {

    public static String toHexString (byte[] data) {  //turns array data into a string of hexadecimals
        String hexString = "";
        for (byte element : data) { //iterates through each element in the array
            hexString += Integer.toHexString(element); //turns each element into a hexadecimal
        }
        return hexString;
    }

    public static int countRuns(byte[] flatData) { //counts the number of runs in the data set
        byte previousElement = flatData[0];
        int numRuns = 1;
        int numInRow = 0;
        for (byte element : flatData) { //iterates through each element in the data set
            if ((element != previousElement) || (numInRow >= 15)) { /* starts a new run if the current element is different
                                                                   from the previous one or 15 elements in a row have
                                                                   been counted */
                numRuns += 1;
                previousElement = element; //because the previous element was different this value must be changed
                numInRow = 0;
            }
            numInRow++; //otherwise the number in a row is incremented by one
        }
        return numRuns;
    }

    public static byte[] encodeRle(byte[] flatData) { //creates encoded data from raw data that is passed in
        int arrayLength = 2 * countRuns(flatData); /* for each run, two spots in the array are needed: one for the
                                                      number itself and one for its frequency */
        byte[] rleVersion = new byte[arrayLength];
        byte previousElement = flatData[0];
        int currentIndex = 0; //the index in the flat data that will be changed (have a byte added) next
        byte numFreq = 0; //how many times in a row the byte appears

        for (int i  = 0; i < flatData.length; i++) { //iterates through the flat data
            byte element = flatData[i];
            if (element != previousElement) {
                rleVersion[currentIndex] = numFreq;
                rleVersion[currentIndex + 1] = previousElement;
                numFreq = 0; //resets the frequency of the element
                previousElement = element; //resets which element is being examined
                currentIndex += 2;
            }
            if (numFreq < 15) {
                numFreq += 1;
            }
            else { //if the number has shown up 15 times, a new run should be started
                rleVersion[currentIndex] = numFreq;
                rleVersion[currentIndex + 1] = previousElement;
                numFreq = 1;
                currentIndex += 2;
            }
        }
        //once the iteration is complete, the last two spots in the array are set to the last element and its frequency
        rleVersion[currentIndex] = numFreq;
        rleVersion[currentIndex + 1] = previousElement;
        
        return rleVersion;
    }

    public static int getDecodedLength(byte[] relData) { //determines the size of RLE data
        int totalLength = 0;
        //adds every other element (these are the number frequencies)
        for (int i = 0; i < relData.length; i += 2) {
            byte element = relData[i];
            totalLength += element;
        }
        return totalLength;
    }

    public static byte[] decodeRle(byte[] rleData) { //decodes RLE data that is encoded
        int arrayLength = getDecodedLength(rleData);
        byte[] decodedArray = new byte[arrayLength];
        int currentPlace = 0;
        for (int i = 0; i < rleData.length; i += 2) { //iterates through every two elements in the data set
            byte numFreq = rleData[i]; //the first of those two elements represents the frequency of the number
            byte element = rleData[i + 1]; //the second of these two elements represents the number itself
            for (int j = 0; j < numFreq; j++) {
                decodedArray[currentPlace + j] = element; //adds the number to the decoded array numFreq times
            }
            currentPlace += numFreq; //moves the place in the array forward by numFreq
        }
        return decodedArray;
    }

    public static byte[] stringToData(String dataString) { //turns a hexadecimal string into a decimal array
        byte[] dataArray = new byte[dataString.length()];
        for (int i = 0; i < dataString.length(); i++) { 
            char currentChar = dataString.charAt(i); //iterates through the characters of the string
            dataArray[i] = (byte) Character.getNumericValue(currentChar); /* translates characters from hexadecimal to
                                                                             decimal and adds them to the array */
        }
        return dataArray;
    }

    public static String toRleString(byte[] rleData) { //turns RLE data into a human-readable string (with delimiters)
        String rleString = "";
        for (int i = 0; i < rleData.length; i += 2) {  //iterates through every two elements in the array parameter
            String numFreqString = String.valueOf(rleData[i]); /* turns the first element (the number frequency) into a 
                                                                  string */
            String hexNumString = Integer.toHexString(rleData[i + 1]); /* turns the second element (the number itself)
                                                                          into a hexadecimal string */
            rleString += (numFreqString + hexNumString + ":");
        }
        rleString = rleString.substring(0, (rleString.length()- 1)); //removes the last ":"
        return rleString;
    }

    public static byte[] stringToRle(String rleString) {

        //Count how many times ":" appears in the string
        int delimCount = 0;
        for (int i = 0; i < rleString.length(); i++) {
            if (rleString.charAt(i) == ':') {
                delimCount ++;
            }
        }

        int arrayLength = (delimCount * 2) + 2; /* for each delimiter, there is a number and its frequency before it,
                                                   and there is an extra number and its frequency at the end; each must
                                                    be in the array */
        byte[] rleArray = new byte[arrayLength];
        int arrayIndex = 0; //keeps track of where you are in the array
        int delimiterIndex = 0; //initializing to zero allows the following code to run
        
        while (delimiterIndex != -1) {
            String priorString = ""; //will hold the part of the string before the first colon found
            delimiterIndex = rleString.indexOf(":"); //finds the next occurrence of a colon

            if (delimiterIndex != -1) {
                priorString = rleString.substring(0, delimiterIndex); /* holds the part of the string before the colon */
            }
            else { //there was no colon in the string
                priorString = rleString;
            }
            
            char hexChar = priorString.charAt(priorString.length() - 1);  //hexChar is the last character in priorString
            byte hexValue = (byte) Character.getNumericValue(hexChar); /* turn the hexadecimal to a decimal and casts to
                                                                          a byte */
            String freqString = priorString.substring(0, priorString.length() - 1); /* freqString is string representing
                                                                                       the number frequency, which is 
                                                                                       all but the last two character of
                                                                                       priorString */
            byte freqValue = Byte.parseByte(freqString); //turn freqString into a byte
            
            //add freqValue and hexValue to the next two slots in the array
            rleArray[arrayIndex] = freqValue;
            arrayIndex++;
            rleArray[arrayIndex] = hexValue;
            arrayIndex++;
            
            if (delimiterIndex != -1) { //as long as there are colons left
                rleString = rleString.substring(delimiterIndex + 1); /* set rleString to be the part of the string after 
                                                                        the colon */
            }
        }
        return rleArray;
    }

    public static void main(String[] args) {

        Scanner scnr = new Scanner(System.in);

        int menuOption = -1;
        byte[] decodedImage = { }; //an array that holds the decoded image data

        System.out.println("Welcome to the RLE image encoder!");
        System.out.println("");
        System.out.println("Displaying Spectrum Image:");
        ConsoleGfx.displayImage(ConsoleGfx.testRainbow);
        System.out.println("");

        while (menuOption != 0) { //this menu option quits the program

            System.out.println("");
            System.out.println("RLE Menu");
            System.out.println("--------");
            System.out.println("0. Exit");
            System.out.println("1. Load File");
            System.out.println("2. Load Test Image");
            System.out.println("3. Read RLE String");
            System.out.println("4. Read RLE Hex String");
            System.out.println("5. Read Data Hex String");
            System.out.println("6. Display Image");
            System.out.println("7. Display RLE String");
            System.out.println("8. Display Hex RLE Data");
            System.out.println("9. Display Hex Flat Data");
            System.out.println("");

            System.out.print("Select a Menu Option: ");
            menuOption = scnr.nextInt(); //stores the option chosen by the user

            switch (menuOption) { //a different case occurs for each menu option chosen

                case 0: //quits the program by exiting the switch case and then making the while loop false
                    break;

                case 1: //loads the file
                    System.out.print("Enter name of file to load: ");
                    String fileName = scnr.next();
                    decodedImage = ConsoleGfx.loadFile(fileName);
                    break;

                case 2: //loads the test image
                    decodedImage = ConsoleGfx.testImage;
                    System.out.println("Test image data loaded.");
                    break;

                case 3: //reads the RLE string
                    System.out.print("Enter an RLE string to be decoded: ");
                    String rleString = scnr.next();
                    decodedImage = decodeRle(stringToRle(rleString)); /* turns the string with delimiters into a decimal
                                                                         array then decodes it */
                    break;

                case 4: //reads the RLE hex string and decodes it
                    System.out.print("Enter the hex string holding RLE data: ");
                    String rawRleString = scnr.next();
                    decodedImage = decodeRle(stringToData(rawRleString)); /* turns the string without delimiters into a
                                                                             decimal array then decodes it */
                    break;

                case 5: //reads the data hex string and decodes it
                    System.out.print("Enter the hex string holding flat data: ");
                    String flatHexString = scnr.next();
                    decodedImage = stringToData(flatHexString); //turns the hexadecimal string into a decimal array
                    break;

                case 6: //displays the image
                    System.out.println("Displaying image...");
                    if (decodedImage.length != 0) {
                        ConsoleGfx.displayImage(decodedImage);
                    } else {
                        System.out.println("(no data)");
                    }
                    break;

                case 7: //displays the RLE string
                    System.out.print("RLE representation: ");
                    if (decodedImage.length != 0) {
                        System.out.println(toRleString(encodeRle(decodedImage))); /* encodes the array and turns it into
                                                                                     a hexadecimal string with
                                                                                     delimiters */
                    } else {
                        System.out.println("(no data)");
                    }
                    break;

                case 8: //displays the hex RLE data
                    System.out.print("RLE hex values: ");
                    if (decodedImage.length != 0) {
                        System.out.println(toHexString(encodeRle(decodedImage))); /* encodes the array and turns it into
                                                                                     a hexadecimal string without
                                                                                     delimiters */
                    } else {
                        System.out.println("(no data)");
                    }
                    break;

                case 9: //displays the hex flat data
                    System.out.print("Flat hex values: ");
                    if (decodedImage.length != 0) {
                        System.out.println(toHexString(decodedImage)); /* turns the array into a hexadecimal string */
                    } else {
                        System.out.println("(no data)");
                    }
                    break;

                default: //if the user inputs anything else
                    System.out.println("Error! Invalid input.");
            }

        }
    }
}
