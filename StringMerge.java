import java.util.Scanner;

public class StringMerge {
	
	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter first string:");
		String s = sc.nextLine();
		System.out.println("Enter second string:");
		String t = sc.nextLine();
		
		String u = s + t;
		System.out.println("Merged string:");
		System.out.println(u);

		
	}
	
}
