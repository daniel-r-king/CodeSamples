package kingcs4700p1;
import java.util.*;
import java.io.*;
import java.lang.Object;

public class KingCS4700P1 {
    
    public static void main(String[] args) {
        executeFile("RAqueries.txt");
    }
    /**
     * *
     * executeFile executes all queries contained in a file and writes the output
     * @param fileName a file containing relational algebra queries
     * to RAoutput.csv
     */
    public static void executeFile(String fileName) {
        File input = new File(fileName);
        try {
            Scanner scanner = new Scanner(input);
            File output = new File("RAoutput.csv");
            output.delete();
            String str;
            while (scanner.hasNextLine()) {
                BufferedWriter bwriter = new BufferedWriter(new FileWriter("RAoutput.csv", true));
                str = scanner.nextLine();
                bwriter.append(str + ", ");
                bwriter.append("\n");
                Relation rel = executeQuery(str);
                rel.writeRelation(bwriter);
                bwriter.close();
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    /**
     * *
     * executeQuery determines the nature of a supplied query and directs
     * it to the appropriate function to be parsed and executed.
     * @param query a relational algebra query
     * @return the relation resulting from the supplied query
     */
    public static Relation executeQuery(String query) {
        Relation result = new Relation();
        if (query.contains("SELE_") && !query.contains("PROJ_") && !query.contains("\\*") && !query.contains("-") && !query.contains("U")) {
            result = executeSelectStatement(query);
        }
        if (query.contains("PROJ_") && !query.contains("-") && !query.contains("U")) {
            result = executeProjectStatement(query);
        }
        if (query.contains("*") && !query.contains("PROJ_") && !query.contains("SELE_") && !query.contains("-") && !query.contains("U")) {
            result = executeNaturalJoinStatement(query);
        }
        if (query.contains("-")) {
            result = executeExceptStatement(query);
        }
        if (query.contains("U")) {
            result = executeUnionStatement(query);
        }
        return result;
    }
    
    /**
     * executeUnionStatement is part of the query processing pipeline. It
     * parses the union statement into an executable form and passes it to the
     * union function.
     * @param statement a union statement
     * @return the result of the except operation
     */
    public static Relation executeUnionStatement(String statement) {
        Relation result = new Relation();
        Relation rel1 = new Relation();
        Relation rel2 = new Relation();
        
        String subStatement1 = "";
        String subStatement2 = "";
        
        String[] tokens = statement.split("U");
        
        subStatement1 = tokens[0].trim();
        subStatement2 = tokens[1].trim();
        
        if (subStatement1.startsWith("(") && subStatement1.endsWith(")")) {
            subStatement1 = subStatement1.substring(1, subStatement1.length() - 1);
        }
        if (subStatement2.startsWith("(") && subStatement2.endsWith(")")) {
            subStatement2 = subStatement2.substring(1, subStatement2.length() - 1);
        }
        
        rel1 = executeQuery(subStatement1);
        rel2 = executeQuery(subStatement2);
        
        result = union(rel1, rel2);
        
        return result;
    }
    
    /**
     * executeExceptStatement is part of the query processing pipeline. It
     * parses the except statement into an executable form and passes it to the
     * except function.
     * @param statement an except statement
     * @return the result of the except operation
     */
    public static Relation executeExceptStatement(String statement) {
        Relation result = new Relation();
        Relation rel1 = new Relation();
        Relation rel2 = new Relation();
        
        String subStatement1 = "";
        String subStatement2 = "";
        
        String[] tokens = statement.split("-");
        
        subStatement1 = tokens[0].trim();
        subStatement2 = tokens[1].trim();
        
        if (subStatement1.startsWith("(") && subStatement1.endsWith(")")) {
            subStatement1 = subStatement1.substring(1, subStatement1.length() - 1);
        }
        if (subStatement2.startsWith("(") && subStatement2.endsWith(")")) {
            subStatement2 = subStatement2.substring(1, subStatement2.length() - 1);
        }
        
        rel1 = executeQuery(subStatement1);
        rel2 = executeQuery(subStatement2);
        
        result = except(rel1, rel2);
        
        return result;
    }
    
    /**
     * executeSelectStatement is part of the query processing pipeline. It
     * parses the select statement into an executable form and passes it to the
     * select function.
     * @param statement a select statement
     * @return the result of the select operation
     */
    public static Relation executeSelectStatement(String statement) {
        String[] cmdCondRel = statement.split("[\\\\{\\\\}]");
        
        String relName = "";
        String attribute = "";
        String operation = "";
        int value = 0;
        
        for (int i = 0; i < cmdCondRel.length; i++) {
            cmdCondRel[i] = cmdCondRel[i].trim();
        }
        
        if (cmdCondRel[0].contains("SELE")) {
            relName = cmdCondRel[2];
            if (cmdCondRel[1].contains(">")) {
                String[] attributeValue = cmdCondRel[1].split(">");
                attribute = attributeValue[0].trim();
                operation = ">";
                value = Integer.parseInt(attributeValue[1].trim());
            }
            if (cmdCondRel[1].contains("<")) {
                String[] attributeValue = cmdCondRel[1].split("<");
                attribute = attributeValue[0].trim();
                operation = "<";
                value = Integer.parseInt(attributeValue[1].trim());
            }
            if (cmdCondRel[1].contains("=")) {
                String[] attributeValue = cmdCondRel[1].split("=");
                attribute = attributeValue[0].trim();
                operation = "=";
                value = Integer.parseInt(attributeValue[1].trim());
            }
        }
        
        File file = new File(relName + ".txt");
        Relation rel = processCSV(file);
        Relation result = select(rel, attribute, operation, value);
        
        return result;
    }
    
    /**
     * executeProjectStatement is part of the query processing pipeline. It
     * parses the project statement into an executable form and passes it to the
     * project function.
     * @param statement a project statement
     * @return the result of the project operation
     */
    public static Relation executeProjectStatement(String statement) {
        String[] cmdCondRel = statement.split("[\\\\{\\\\}]");
        
        String relName = "";
        ArrayList<String> attributes = new ArrayList<>();
        Relation subResult = new Relation();
        Relation result = new Relation();
        
        if (cmdCondRel[0].contains("PROJ")) {
            String[] attr = cmdCondRel[1].split(",");
            for (int i = 0; i < attr.length; i++) {
                attributes.add(attr[i].trim());
            }
            relName = cmdCondRel[2].trim();
        }
        
        String subStatement = "";
        if (relName.contains("(")) {
            if (relName.contains("*")) {
                String[] tokens = statement.split("[\\\\(\\\\)]");
                subStatement = tokens[1].trim();
                subResult = executeNaturalJoinStatement(subStatement);
            }
            if (relName.contains("SELE_")) {
                String[] tokens = statement.split("[\\\\(\\\\)]");
                subStatement = tokens[1].trim();
                subResult = executeSelectStatement(subStatement);
            }
            result = project(subResult, attributes);
        }
        else {
            result = project(relName, attributes);
        }
        
        return result;
    }
    
    /**
     * executeNaturalJoinStatement is part of the query processing pipeline. It
     * parses the natural join statement into an executable form and passes it to the
     * naturalJoin function.
     * @param statement a natural join statement
     * @return the result of the natural join operation
     */
    public static Relation executeNaturalJoinStatement(String statement) {
        String[] tokens = statement.split("\\*");
        String relName1 = tokens[0].trim();
        String relName2 = tokens[1].trim();
        Relation result = naturalJoin(relName1, relName2);
        return result;
    }
    
    /**
     * union takes two relations and returns their set union, i.e. the 
     * combination of all tuples from both relations sans duplicates.
     * @param rel1 the first of two relations to be processed
     * @param rel2 the second of two relations to be processed
     * @return a relation containing all tuples from both relations sans duplicates
     */
    public static Relation union(Relation rel1, Relation rel2) {
        Relation result = new Relation();
        
        for (int i = 0; i < rel1.getAttributes().size(); i++) {
            result.addAttribute(rel1.getAttributes().get(i).toString());
        }
        
        for (int i = 0; i < rel1.getRecords().size(); i++) {
            result.addRecord(rel1.getRecords().get(i));
        }
        
        for (int i = 0; i < rel2.getRecords().size(); i++) {
            result.addRecord(rel2.getRecords().get(i));
        }
        
        for (int i = 0; i < result.getRecords().size(); i++) {
            for (int j = 0; j < result.getRecords().size(); j++) {
                if (result.getRecords().get(i).equals(result.getRecords().get(j)) && i != j) {
                    result.getRecords().remove(i);
                }
            }
        }
        
        return result;
    }
    
    /**
     * union takes two relations and returns their set union, i.e. the 
     * combination of all tuples from both relations sans duplicates.
     * @param relName1 a file name corresponding to a relation stored in a file
     * @param relName2 a file name corresponding to a relation stored in a file
     * @return a relation containing all tuples from both relations sans duplicates
     */
    public static Relation union(String relName1, String relName2) {
        File file1 = new File(relName1 + ".txt");
        File file2 = new File(relName2 + ".txt");
        
        Relation rel1 = processCSV(file1);
        Relation rel2 = processCSV(file2);
        
        Relation result = new Relation();
        
        for (int i = 0; i < rel1.getAttributes().size(); i++) {
            result.addAttribute(rel1.getAttributes().get(i).toString());
        }
        
        for (int i = 0; i < rel1.getRecords().size(); i++) {
            result.addRecord(rel1.getRecords().get(i));
        }
        
        for (int i = 0; i < rel2.getRecords().size(); i++) {
            result.addRecord(rel2.getRecords().get(i));
        }
        
        for (int i = 0; i < result.getRecords().size(); i++) {
            for (int j = 0; j < result.getRecords().size(); j++) {
                if (result.getRecords().get(i).equals(result.getRecords().get(j)) && i != j) {
                    result.getRecords().remove(i);
                }
            }
        }
        
        return result;
    }
    
    /**
     * except takes two relations, removes all tuples contained in the second
     * from the first, and returns the resulting relation sans duplicates.
     * @param rel1 the first of two relations to be processed
     * @param rel2 the second of two relations to be processed
     * @return a relation containing all tuples in the first relation, except
     * those present in the second relation.
     */
    public static Relation except(Relation rel1, Relation rel2) {
        Relation result = new Relation();
        
        for (int i = 0; i < rel1.getAttributes().size(); i++) {
            result.addAttribute(rel1.getAttributes().get(i).toString());
        }
        
        for (int i = 0; i < rel1.getRecords().size(); i++) {
            boolean found = false;
            for (int j = 0; j < rel2.getRecords().size(); j++) {
                if (rel1.getRecords().get(i).equals(rel2.getRecords().get(j))) {
                    found = true;
                }
            }
            if (!found) {
                result.addRecord(rel1.getRecords().get(i));
            }
        }
        
        for (int i = 0; i < result.getRecords().size(); i++) {
            for (int j = 0; j < result.getRecords().size(); j++) {
                if (result.getRecords().get(i).equals(result.getRecords().get(j)) && i != j) {
                    result.getRecords().remove(i);
                }
            }
        }
        
        return result;
    }
    
    /**
     * except takes two relations, removes all tuples contained in the second
     * from the first, and returns the resulting relation sans duplicates.
     * @param relName1 a file name corresponding to a relation stored in a file
     * @param relName2 a file name corresponding to a relation stored in a file
     * @return a relation containing all tuples in the first relation, except
     * those present in the second relation.
     */
    public static Relation except(String relName1, String relName2) {
        File file1 = new File(relName1 + ".txt");
        File file2 = new File(relName2 + ".txt");
        
        Relation rel1 = processCSV(file1);
        Relation rel2 = processCSV(file2);
        Relation result = new Relation();
        
        for (int i = 0; i < rel1.getAttributes().size(); i++) {
            result.addAttribute(rel1.getAttributes().get(i).toString());
        }
        
        for (int i = 0; i < rel1.getRecords().size(); i++) {
            boolean found = false;
            for (int j = 0; j < rel2.getRecords().size(); j++) {
                if (rel1.getRecords().get(i).equals(rel2.getRecords().get(j))) {
                    found = true;
                }
            }
            if (!found) {
                result.addRecord(rel1.getRecords().get(i));
            }
        }
        
        for (int i = 0; i < result.getRecords().size(); i++) {
            for (int j = 0; j < result.getRecords().size(); j++) {
                if (result.getRecords().get(i).equals(result.getRecords().get(j)) && i != j) {
                    result.getRecords().remove(i);
                }
            }
        }
        
        return result;
    }
    
    /**
     * naturalJoin takes two relations performs a natural join operation.
     * @param relName1 a file name corresponding to a relation stored in a file
     * @param relName2 a file name corresponding to a relation stored in a file
     * @return a relation consisting of the set of all combinations of tuples 
     * from the supplied relations that are equal on their common attribute names
     */
    public static Relation naturalJoin(String relName1, String relName2) {
        File file1 = new File(relName1 + ".txt");
        File file2 = new File(relName2 + ".txt");
        
        Relation rel1 = processCSV(file1);
        Relation rel2 = processCSV(file2);
        Relation tmp = new Relation();
        
        if (rel1.getRecords().size() < rel2.getRecords().size()) {
            tmp = rel2;
            rel2 = rel1;
            rel1 = tmp;
        }
        
        Relation result = new Relation();
        
        boolean fKeyExists = false;
        String fKey = "";
        int fKeyIndex1 = -1;
        int fKeyIndex2 = -1;
        for (int i = 0; i < rel1.getAttributes().size(); i++) {
            for (int j = 0; j < rel2.getAttributes().size(); j++) {
                if (rel1.getAttributes().get(i).equals(rel2.getAttributes().get(j))) {
                    fKeyExists = true;
                    fKey = rel1.getAttributes().get(i).toString();
                }
            }
        }
        
        if (fKeyExists) {
            for (int i = 0; i < rel2.getAttributes().size(); i++) {
                if (rel2.getAttributes().get(i).toString().matches(fKey)) {
                    fKeyIndex2 = i;
                }
            }
        }
        
        for (int i = 0; i < rel1.getAttributes().size(); i++) {
            result.addAttribute(rel1.getAttributes().get(i).toString());
            if (fKeyExists && rel1.getAttributes().get(i).equals(fKey)) {
                fKeyIndex1 = i;
            }
        }
        for (int i = 0; i < rel2.getAttributes().size(); i++) {
            rel1.addAttribute(rel2.getAttributes().get(i).toString());
            result.addAttribute(rel2.getAttributes().get(i).toString());
        }
        
        if (fKeyExists) {
            for (int i = 0; i < rel1.getRecords().size(); i++) {
                for (int j = 0; j < rel2.getRecords().size(); j++) {
                    if (rel2.getRecords().get(j).get(fKeyIndex2).equals(rel1.getRecords().get(i).get(fKeyIndex1))) {
                        for (int k = 0; k < rel2.getAttributes().size() - 1; k++) {
                            if (k != fKeyIndex2) { 
                                rel1.getRecords().get(i).add(rel2.getRecords().get(j).get(k));
                            }
                        }
                    }
                }
            }
        }
        
        for (int i = 0; i < result.getRecords().size(); i++) {
            for (int j = 0; j < result.getRecords().size(); j++) {
                if (result.getRecords().get(i).equals(result.getRecords().get(j)) && i != j) {
                    result.getRecords().remove(i);
                }
            }
        }
        
        return rel1;
    }
    
    /**
     * project filters all columns out of a relation whose attribute name does
     * not match its parameters.
     * @param relName a file name corresponding to a file containing a relation
     * @param attributes the attributes to be projected
     * @return a copy of the supplied relation with only the requested columns
     * and duplicate tuples removed
     */
    public static Relation project(String relName, ArrayList<String> attributes) {
        File file = new File(relName + ".txt");
        Relation rel = processCSV(file);
        ArrayList<Integer> indexes = new ArrayList<>();
        Relation result = new Relation();
        
        for (int i = 0; i < rel.getAttributes().size(); i++) {
            boolean found = false;
            for (int j = 0; j < attributes.size(); j++) {
                if (rel.getAttributes().get(i).toString().matches(attributes.get(j))) {
                    found = true;
                }
            }
            if (found) {
                indexes.add(i);
                result.addAttribute(rel.getAttributes().get(i).toString());
            }
        }
        
        for (int i = 0; i < rel.getRecords().size(); i++) {
            ArrayList<Object> rec = new ArrayList<>();
            for (int j = 0; j < rel.getRecords().get(j).size(); j++) {
                boolean indexValid = false;
                for (int k = 0; k < indexes.size(); k++) {
                    if (j == indexes.get(k)) {
                        indexValid = true;
                    }
                }
                if (indexValid) {
                    rec.add(rel.getRecords().get(i).get(j));
                }
            }
            result.addRecord(rec);
        }
        
        for (int i = 0; i < result.getRecords().size(); i++) {
            for (int j = 0; j < result.getRecords().size(); j++) {
                if (result.getRecords().get(i).equals(result.getRecords().get(j)) && i != j) {
                    result.getRecords().remove(i);
                }
            }
        }
        
        return result;
    }
    
    /**
     * project filters all columns out of a relation whose attribute name does
     * not match its parameters.
     * @param rel the relation from which to project
     * @param attributes the attributes to be projected
     * @return a copy of the supplied relation with only the requested columns
     * and duplicate tuples removed
     */
    public static Relation project(Relation rel, ArrayList<String> attributes) {
        ArrayList<Integer> indexes = new ArrayList<>();
        Relation result = new Relation();
        
        for (int i = 0; i < rel.getAttributes().size(); i++) {
            boolean found = false;
            for (int j = 0; j < attributes.size(); j++) {
                if (rel.getAttributes().get(i).toString().matches(attributes.get(j))) {
                    found = true;
                }
            }
            if (found) {
                indexes.add(i);
                result.addAttribute(rel.getAttributes().get(i).toString());
            }
        }
        
        for (int i = 0; i < rel.getRecords().size(); i++) {
            ArrayList<Object> rec = new ArrayList<>();
            for (int j = 0; j < rel.getRecords().get(j).size(); j++) {
                boolean indexValid = false;
                for (int k = 0; k < indexes.size(); k++) {
                    if (j == indexes.get(k)) {
                        indexValid = true;
                    }
                }
                if (indexValid) {
                    rec.add(rel.getRecords().get(i).get(j));
                }
            }
            result.addRecord(rec);
        }
        
        for (int i = 0; i < result.getRecords().size(); i++) {
            for (int j = 0; j < result.getRecords().size(); j++) {
                if (result.getRecords().get(i).equals(result.getRecords().get(j)) && i != j) {
                    result.getRecords().remove(i);
                }
            }
        }
        
        return result;
    }
    
    /**
     * select selects tuples matching some criteria
     * @param relName a file name corresponding to a file containing a relation
     * @param attribute the attribute to which some condition will be applied
     * @param operation the operation determining the condition
     * @param value the value supplied to the operation
     * @return a relation containing only the tuples meeting the supplied condition
     */
    public static Relation select(String relName, String attribute, String operation, int value) {
        File file = new File(relName + ".txt");
        Relation rel = processCSV(file);
        Relation result = new Relation();
        boolean found = false;
        int colIndex = 0;
        
        for (int i = 0; i < rel.getAttributes().size(); i++) {
            if (rel.getAttributes().get(i).toString().matches(attribute)) {
                found = true;
                colIndex = i;
            }
        }
        
        if (found) {
            for (int i = 0; i < rel.getAttributes().size(); i++) {
                result.addAttribute(rel.getAttributes().get(i).toString());
            }
        }
        else {
            System.out.println("ERROR: Relation " + rel + " does not have attribute " + attribute + ".");
        }
        
        if (found && operation == ">") {
            for (int i = 0; i < rel.getRecords().size(); i++) {
                if (Integer.parseInt(rel.getRecords().get(i).get(colIndex).toString().trim()) > value) {
                    result.addRecord(rel.getRecords().get(i));
                }
            }
        }
        
        if (found && operation == "<") {
            for (int i = 0; i < rel.getRecords().size(); i++) {
                if (Integer.parseInt(rel.getRecords().get(i).get(colIndex).toString().trim()) < value) {
                    result.addRecord(rel.getRecords().get(i));
                }
            }
        }
        
        if (found && operation == "=") {
            for (int i = 0; i < rel.getRecords().size(); i++) {
                if (Integer.parseInt(rel.getRecords().get(i).get(colIndex).toString().trim()) == value) {
                    result.addRecord(rel.getRecords().get(i));
                }
            }
        }
        
        for (int i = 0; i < result.getRecords().size(); i++) {
            for (int j = 0; j < result.getRecords().size(); j++) {
                if (result.getRecords().get(i).equals(result.getRecords().get(j)) && i != j) {
                    result.getRecords().remove(i);
                }
            }
        }
        
        return result;
    }
    
    /**
     * select selects tuples matching some criteria
     * @param rel a relation to be selected from
     * @param attribute the attribute to which some condition will be applied
     * @param operation the operation determining the condition
     * @param value the value supplied to the operation
     * @return a relation containing only the tuples meeting the supplied condition
     */
    public static Relation select(Relation rel, String attribute, String operation, int value) {
        Relation result = new Relation();
        boolean found = false;
        int colIndex = 0;
        
        for (int i = 0; i < rel.getAttributes().size(); i++) {
            if (rel.getAttributes().get(i).toString().matches(attribute)) {
                found = true;
                colIndex = i;
            }
        }
        
        if (found) {
            for (int i = 0; i < rel.getAttributes().size(); i++) {
                result.addAttribute(rel.getAttributes().get(i).toString());
            }
        }
        
        if (found && operation == ">") {
            for (int i = 0; i < rel.getRecords().size(); i++) {
                if (Integer.parseInt(rel.getRecords().get(i).get(colIndex).toString().trim()) > value) {
                    result.addRecord(rel.getRecords().get(i));
                }
            }
        }
        
        if (found && operation == "<") {
            for (int i = 0; i < rel.getRecords().size(); i++) {
                if (Integer.parseInt(rel.getRecords().get(i).get(colIndex).toString().trim()) < value) {
                    result.addRecord(rel.getRecords().get(i));
                }
            }
        }
        
        if (found && operation == "=") {
            for (int i = 0; i < rel.getRecords().size(); i++) {
                if (Integer.parseInt(rel.getRecords().get(i).get(colIndex).toString().trim()) == value) {
                    result.addRecord(rel.getRecords().get(i));
                }
            }
        }
        
        else {
            System.out.println("ERROR: Relation " + rel + " does not have attribute " + attribute + ".");
        }
        
        for (int i = 0; i < result.getRecords().size(); i++) {
            for (int j = 0; j < result.getRecords().size(); j++) {
                if (result.getRecords().get(i).equals(result.getRecords().get(j)) && i != j) {
                    result.getRecords().remove(i);
                }
            }
        }
        
        return result;
    }
    
    /**
     * processCSV takes a file containing comma separated values and converts it
     * to a relation object.
     * @param input a file containing comma separated values
     * @return a relation object.
     */
    public static Relation processCSV(File input) {
        Relation rel = new Relation();
        boolean attributesSet = false;
        try {
            Scanner scanner = new Scanner(input);
            String str;
            while (scanner.hasNextLine()) {
                str = scanner.nextLine();
                ArrayList<Object> rec = new ArrayList<>();
                String[] tokens = str.split(",");
                if (!attributesSet) {
                    for (int i = 0; i < tokens.length; i++) {
                        rel.addAttribute(tokens[i].trim());
                    }  
                    attributesSet = true;
                }
                else {
                    for (int i = 0; i < tokens.length; i++) {
                        rec.add(tokens[i].trim());
                    }
                    rel.addRecord(rec);
                }
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        return rel;
    }
}
