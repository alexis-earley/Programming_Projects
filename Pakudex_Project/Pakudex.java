public class Pakudex {
    private int capacity; //how many Pakuri the Pakudex can hold
    private int size = 0; //how many Pakuri the Pakudex currently holds
    private Pakuri[] speciesArray; //the array of Pakuri

    public Pakudex() { //constructor if no capacity is inputted
        capacity = 20;
        speciesArray = new Pakuri[capacity];
    }

    public Pakudex(int capacity) { //method overload for constructor; assuming a capacity is passed as an argument
        this.capacity = capacity;
        speciesArray = new Pakuri[capacity];
    }

    public Pakuri searchForPakuri(String speciesName) { //looks in speciesArray for the name specified; returns that Pakuri
        for (int i = 0; i < size; i++) {
            Pakuri currentPakuri = speciesArray[i];
            if (currentPakuri.getSpecies().equals(speciesName)) {
                return currentPakuri;
            }
        }
        return null;
    }

    public int getSize() { //size is a private variable
        return size;
    }

    public int getCapacity() { //capacity is a private variable
        return capacity;
    }

    public String[] getSpeciesArray() { //returns an array with the names of the species in the speciesArray
        if (size > 0) {
            String[] speciesNameArray = new String[size];

            int currentElement = 0;
            for (int i = 0; i < size; i++) {
                Pakuri species = speciesArray[i];
                if (species == null) { //the first empty spot in the species array; no more names need be added
                    break;
                }
                else {
                    speciesNameArray[currentElement] = species.getSpecies();
                    currentElement++;
                }
            }
            return speciesNameArray;
        }
        return null;
    }

    public int[] getStats(String species) { //returns an array with the attack, defense, and speed of the Pakuri
        int[] statsArray = new int[3];
        Pakuri pakuri = searchForPakuri(species); //creates a variable holding the Pakuri with the given name

        if (pakuri != null) {
            statsArray[0] = pakuri.getAttack();
            statsArray[1] = pakuri.getDefense();
            statsArray[2] = pakuri.getSpeed();
            return statsArray;
        }
        return null;
    }

    public void sortPakuri() { //sorts the Pakuri alphabetically by name; based on a bubble sort
        boolean isSorted = false;
        while (!isSorted) { //runs until it can get through one iteration without switching two values
            isSorted = true; //will be set to false if two values are switched, causing the sort to continue
            for (int i = 0; i < getSize() - 1; i++) {
                String name1 = speciesArray[i].getSpecies();
                String name2 = speciesArray[i + 1].getSpecies();
                if (name1.compareTo(name2) > 0) { //the names are out of order
                    Pakuri temp = speciesArray[i];
                    speciesArray[i] = speciesArray[i + 1];
                    speciesArray[i + 1] = temp;
                    isSorted = false;
                }
            }
        }
    }

    public boolean addPakuri(String species) { //adds a Pakuri to speciesArray if it is not already there; otherwise returns false
        Pakuri pakuri = searchForPakuri(species); //looks for the Pakuri with this name
        if (pakuri == null) { //there was no Pakuri found with this name
            speciesArray[size] = new Pakuri(species);
            size++;
            return true;
        }
        return false;
    }

    public boolean evolveSpecies(String species) { //evolves the Pakuri if the Pakrui is in the Pakudex; otherwise returns false
        Pakuri pakuri = searchForPakuri(species); //locates the Pakuri with this name
        if (pakuri != null) { //there was a Pakuri found with this name
            pakuri.evolve();
            return true;
        }
        return false;
    }
}
