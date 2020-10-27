public class Pakuri {
    private String species;
    private int attack, defense, speed;

    public Pakuri(String species) {
        this.species = species;
        attack = (species.length() * 7) + 9;
        defense = (species.length() * 5) + 17;
        speed = (species.length() * 6) + 13;
    }

    public String getSpecies() { //returns species of critter
        return species;
    } //this and the following variables are private

    public int getAttack() {
        return attack;
    }

    public int getDefense() {
        return defense;
    }

    public int getSpeed() {
        return speed;
    }

    public void setAttack(int newAttack) {
        attack = newAttack;
    }

    public void evolve() {
        attack *= 2;
        defense *= 4;
        speed *= 3;
    }
}
