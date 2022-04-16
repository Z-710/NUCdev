import java.util.Scanner;
public class ReadingStuff {
	
	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter a string:");
	    	String a = sc.nextLine();
	    	System.out.println("Enter a float:");
		float b = sc.nextFloat();
		//Concatenate the two things.
		String c = a+b;
		//Print it out.
		System.out.println("Merged String:");
		System.out.println(c);
	}
	
}
