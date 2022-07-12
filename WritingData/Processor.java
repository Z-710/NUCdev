import java.util.function.Function;
import java.util.function.IntUnaryOperator;
import java.util.*;
import java.io.*;

public class Processor {

    public static <O> void mapData(String inputFilename, String outputFilename, Function<Integer, O> map) {
        // Stuff goes here
        try{
        PrintWriter pw = new PrintWriter(outputFilename);
        Scanner fs = new Scanner(new File(inputFilename));
        int s = fs.nextInt();
        while (fs.hasNextInt())
        {
           pw.println(map.apply(s));
           s = fs.nextInt();
           try {
            while (!fs.hasNextInt()){
                fs.nextLine();
                }
            }
            catch(Exception e) {}
        }

        pw.println(map.apply(s));
        pw.close();
        }
        catch (FileNotFoundException e) {
            System.err.println("No File");
        }
    }

    public static void main(String[] args) {
         mapData("inputTest.txt", "outputTest.txt", Function.<Integer>identity());
    }
}
