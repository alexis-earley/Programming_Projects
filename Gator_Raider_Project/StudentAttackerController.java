package edu.ufl.cise.cs1.controllers;

import game.controllers.AttackerController;
import game.models.*;
import java.util.ArrayList;
import java.util.List;

public final class StudentAttackerController implements AttackerController
{

    public void init(Game game) {
    }

    public void shutdown(Game game) { }

    public int update(Game game,long timeDue)
    {
        List<Integer> possibleDirs = game.getAttacker().getPossibleDirs(true);
        if (possibleDirs.size() != 0) {

            Attacker attacker = game.getAttacker();
            Node currentLoc = attacker.getLocation();
            Defender nearestGhost = getNearestDefender(game);

            if (nearestGhost != null) { //if not all ghosts are in the lair; prevents a nullPointerException
                int distToNearGhost = currentLoc.getPathDistance(nearestGhost.getLocation());
                boolean reallyCloseGhost = false; //is the nearest ghost too close?
                if (distToNearGhost <= 5){
                    reallyCloseGhost = true;
                }

                if (nearestGhost.isVulnerable()) {
                    if ((distToNearGhost <= 25 && nearestGhost.getVulnerableTime() >= 45) ||
                            (reallyCloseGhost && nearestGhost.getVulnerableTime() >= 10)) {
                        //if you are close to the ghost and it will still be vulnerable for some time
                        //or the ghost is really close and it will still be vulnerable for a little time
                        //(numerical values were chosen after simulating different values to see what worked best)
                        return attacker.getNextDir(nearestGhost.getLocation(), true); //chase the ghost
                    }
                }

                else { //if the nearest ghost is not vulnerable
                    if (reallyCloseGhost) {

                        //the following few lines of code sends the attacker in search of the nearest pill
                        //if he is at a junction and this will not make him run into the ghost
                        //this prevents the attacker from getting stuck in loops until a ghost kills him, an issue during trial runs
                        if (currentLoc.isJunction()) {
                            Node pillLoc = getNearestNode(game, game.getPillList());
                            if (pillLoc != null) {
                                if (attacker.getNextDir(pillLoc, true) != attacker.getNextDir(nearestGhost.getLocation(), true)) {
                                    return attacker.getNextDir(pillLoc, true); //go in search of the nearest pill
                                }
                            }
                        }
                        return attacker.getNextDir(nearestGhost.getLocation(), false); //otherwise just flee the ghost
                    }
                }
            }

            if (currentLoc.isJunction()) { //if you are at a junction
                Node bestGoal = findBestGoal(game); //set the best junction to go to (essentially the one with the most pills)
                if (bestGoal != null) { //if at least one path has some pills
                    return attacker.getNextDir(bestGoal, true);
                    //consider the two closest junctions and take the path that has more pills
                }
            }

            Node pillLoc = getNearestNode(game, game.getPillList());
            if (pillLoc != null) {
                return attacker.getNextDir(pillLoc, true); //send the pac man in search of the nearest pill
            }
        }
        return -1;
    }

    //Supporting methods
    private Defender getNearestDefender(Game game) { //finds the defender nearest to the attacker
        List<Defender> Defenders = game.getDefenders();
        int oldDistance =1000;
        int newDistance = 1001;
        Defender bestGhost = null;
        for (Defender defender : Defenders) {
            //iterate through each defender, marking each as the bestGhost if their distance to the attacker is the shortest so far
            if (defender.getLairTime() != 0) { //if the defender is in the lair, don't consider it
                continue;
            }
            newDistance = game.getAttacker().getLocation().getPathDistance(defender.getLocation());
            //how far away the attacker is from the defender
            if (newDistance < oldDistance) {
                oldDistance = newDistance;
                bestGhost = defender;
            }
        }
        return bestGhost;
    }

    private Node getNearestNode(Game game, List<Node> Nodes) { //finds the node nearest the attacker from the given list
        Node bestNode = null;
        int oldDistance =1000;
        int newDistance = 1001;
        for (Node node : Nodes) {
            //iterates through the nodes and marks each as the best if their distance is the shortest so far
            newDistance = game.getAttacker().getLocation().getPathDistance(node);
            //this is the distance between the attacker and this node
            if (newDistance < oldDistance) {
                oldDistance = newDistance;
                bestNode = node;
            }
        }
        return bestNode;
    }

    private Node findBestGoal(Game game) {
        //this method will find the two closest junctions and will return which has more pills on the way
        ArrayList<Node> junctionArrayList = new ArrayList();
        List<Node> listOfJunctions = game.getCurMaze().getJunctionNodes(); //generate a list of all junctions
        //create an ArrayList with these junctions so some can be subtracted and added
        for (Node node : listOfJunctions) {
            junctionArrayList.add(node);
        }

        Node currentJunction = getNearestNode(game, junctionArrayList);
        junctionArrayList.remove(currentJunction);
        Node closestJunction = getNearestNode(game, junctionArrayList); //this is the nearest junction, not including the current one
        junctionArrayList.remove(closestJunction);
        //currentJunction and closestJunction have been removed so you can find the closest of the remaining junctions

        Node nextJunction = null; //this will store the closest junction that is not in the same direction as the current junction
        while (junctionArrayList != null) {
            //keep going until the closest junction sends the attacker in a different direction or the list becomes empty
            nextJunction = getNearestNode(game, junctionArrayList);
            int dirToClosest = game.getAttacker().getNextDir(closestJunction, true);
            int dirToOther = game.getAttacker().getNextDir(nextJunction, true);
            if (dirToClosest != dirToOther) {
                break;
            }
            junctionArrayList.remove(nextJunction);
        }


        if ((numPillsTo(closestJunction, game) == 0) && (numPillsTo(nextJunction, game) == 0)) { //if neither path has pills
            return null; //if null is returned, the main just sends the attacker in search of the nearest pill
        }

        //return which has more pills
        if (numPillsTo(closestJunction, game) >= numPillsTo(nextJunction, game)) {
            return closestJunction;
        }
        else {
            return nextJunction;
        }
    }

    private int numPillsTo(Node junction, Game game) { //returns the number of pills the attacker would get heading to this junction
        int numPills = 0;
        for (Node location : game.getAttacker().getPathTo(junction)) { //for each location on this path to the junction
            if (game.checkPill(location)) {
                numPills += 1;
            }
        }
        return numPills;
    }
}