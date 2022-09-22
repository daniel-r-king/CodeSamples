package kingcs4700p1;
import java.util.*;
import java.io.*;

public class Relation {
    private String name;
    private ArrayList<Object> attributes;
    private ArrayList<ArrayList<Object>> records;
    
    public Relation() {
        name = "";
        attributes = new ArrayList<Object>();
        records = new ArrayList<ArrayList<Object>>();
    }

    public Relation(String name, ArrayList<Object> attributes) {
        this.name = name;
        this.attributes = attributes;
        this.records = new ArrayList<ArrayList<Object>>();
    }
    
    
    public void printRelation() {
        for (int i = 0; i < attributes.size(); i++) {
            System.out.print(attributes.get(i) + " ");
        }
        for (int i = 0; i < records.size(); i++) {
            System.out.println();
            for (int j = 0; j < records.get(i).size(); j++) {
                System.out.print(records.get(i).get(j) + " ");
            }
        }
    }
    
    public void writeRelation(BufferedWriter bwriter) {
        try {
            for (int i = 0; i < attributes.size(); i++) {
                bwriter.append(attributes.get(i) + ", ");
            }
            for (int i = 0; i < records.size(); i++) {
                bwriter.append("\n");
                for (int j = 0; j < records.get(i).size(); j++) {
                    bwriter.append(records.get(i).get(j) + ", ");
                }
            }
            bwriter.append("\n\n");
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    public void addRecord(ArrayList<Object> record) {
        if (attributes.size() == record.size()) {
            records.add(record);
        }
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setAttributes(ArrayList<Object> attributes) {
        this.attributes = attributes;
    }

    public String getName() {
        return name;
    }

    public ArrayList<Object> getAttributes() {
        return attributes;
    }
    
    public ArrayList<ArrayList<Object>> getRecords() {
        return records;
    }

    public void addAttribute(String attributeToBeAdded) {
        boolean found = false;
        for (int i = 0; i < attributes.size(); i++) {
            if (attributes.get(i).toString().matches(attributeToBeAdded)) {
                found = true;
            }
        }
        if (!found) {
            attributes.add(attributeToBeAdded.trim());
            System.out.println("Attribute " + attributeToBeAdded + " added successfully.");
        } 
        else {
            System.out.println("Attribute already exists in relation.");
        }
    }

    public void removeAttribute(String elementToBeRemoved) {
        boolean found = false;
        for (int i = 0; i < attributes.size(); i++) {
            if (attributes.get(i).toString().matches(elementToBeRemoved)) {
                attributes.remove(i);
                found = true;
            }
        }
        if (found) {
            System.out.println(elementToBeRemoved + "successfully removed.");
        } else {
            System.out.println("ERROR: attribute " + elementToBeRemoved + " not found.");
        }
    }
    
    public void removeRecord(ArrayList<Object> elementToBeRemoved) {
        boolean found = false;
        for (int i = 0; i < records.size(); i++) {
            if (records.get(i) == elementToBeRemoved) {
                found = true;
                records.remove(i);
            }
        }
        if (found) {
            System.out.println("Element removed successfully.");
        }
        else {
            System.out.println("ERROR: Element was not found.");
        }
    }
}