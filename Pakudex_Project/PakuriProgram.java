import java.util.InputMismatchException;
import java.util.Scanner;

public class PakuriProgram {
    public static void main(String[] args) {
        Scanner scnr = new Scanner(System.in);
        int capacity = 0; //how many Pakuri the Pakudex holds; inputted from the user
        boolean hasExited = false; //assigned to true when the user exits the program
        int menuResponse = 0; //the menu option chosen by the user

        System.out.println("Welcome to Pakudex: Tracker Extraordinaire!");
        while (true) { //keep asking the user for input until they enter a valid integer for the capacity
            System.out.print("Enter max capacity of the Pakudex: ");
            try {
                capacity = scnr.nextInt();
                if (capacity >= 0) {
                    break;
                }
                else {
                    System.out.println("Please enter a valid size.");
                }
            }
            catch(InputMismatchException e) {
                System.out.println("Please enter a valid size.");
                scnr.next(); //removes the exception
                continue;
            }
        }

        Pakudex pakudex = new Pakudex(capacity); //create a new instance of a Pakudex with this capacity
        System.out.println("The Pakudex can hold " + capacity + " species of Pakuri.");
        System.out.println("");

        while (!hasExited) {
            System.out.println("Pakudex Main Menu");
            System.out.println("-----------------");
            System.out.println("1. List Pakuri");
            System.out.println("2. Show Pakuri");
            System.out.println("3. Add Pakuri");
            System.out.println("4. Evolve Pakuri");
            System.out.println("5. Sort Pakuri");
            System.out.println("6. Exit");
            System.out.println("");
            System.out.print("What would you like to do? ");

            try { //the user may not enter a valid integer for the menu response
                menuResponse = scnr.nextInt();
            }
            catch (InputMismatchException e) {
                menuResponse = 0; //this will make the following switch go to its default (look below)
                scnr.next();
            }


            switch (menuResponse) {
                case 1: //list Pakuri

                    if (pakudex.getSize() != 0) { //if the size was zero, there would be no Pakuri to list
                        System.out.println("Pakuri In Pakudex:");
                        String[] speciesArray = pakudex.getSpeciesArray();
                        for (int i = 0; i < pakudex.getSize(); i++) {
                            String speciesName = speciesArray[i];
                            System.out.println((i + 1) + (". " + speciesName)); //prints a numerical list with the names
                        }
                    }
                    else {
                        System.out.println("No Pakuri in Pakudex yet!");
                    }

                    System.out.println("");

                    break;

                case 2: //show Pakuri
                    System.out.print("Enter the name of the species to display: ");
                    String species = scnr.next();

                    int[] statsArray = pakudex.getStats(species); //holds the attack, defense, and speed, respectively

                    if (statsArray != null) { //the array would be null if the Pakuri did not exist
                        System.out.println("");
                        System.out.println("Species: " + species);
                        System.out.println("Attack: " + statsArray[0]);
                        System.out.println("Defense: " + statsArray[1]);
                        System.out.println("Speed: " + statsArray[2]);
                    }
                    else {
                        System.out.println("Error: No such Pakuri!");
                    }
                    System.out.println("");
                    break;

                case 3: //add Pakuri
                    if (pakudex.getSize() != pakudex.getCapacity()) { //the Pakudex is not at max capacity
                        System.out.print("Enter the name of the species to add: ");
                        String speciesName = scnr.next();

                        if (pakudex.addPakuri(speciesName)) { //returns true if the Pakuri was added
                            System.out.println("Pakuri species " + speciesName + " successfully added!");
                        }
                        else {
                            System.out.println("Error: Pakudex already contains this species!");
                        }
                    }

                    else {
                        System.out.println("Error: Pakudex is full!");
                    }

                    System.out.println("");
                    break;

                case 4: //evolve Pakuri
                    System.out.print("Enter the name of the species to evolve: ");
                    String speciesToEvolve = scnr.next();
                    if (pakudex.evolveSpecies(speciesToEvolve)) { //returns true if the species has evolved
                        System.out.println(speciesToEvolve + " has evolved!");
                    }
                    else {
                        System.out.println("Error: No such Pakuri!");
                    }
                    System.out.println("");
                    break;

                case 5: //sort Pakuri
                    pakudex.sortPakuri(); //sorts the Pakudex alphabetically (by species name)
                    System.out.println("Pakuri have been sorted!");
                    System.out.println("");
                    break;

                case 6: //exit
                    System.out.println("Thanks for using Pakudex! Bye!");
                    hasExited = true; //will exit the while loop and end the program
                    break;

                default:
                    System.out.println("Unrecognized menu selection!");
                    System.out.println("");
            }
        }
    }
}
