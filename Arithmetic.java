import java.util.Scanner;

public class Arithmetic {
	
	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		System.out.print("Enter the value for a: ");
		int a = sc.nextInt();
		System.out.print("Enter the value for b: ");
		int b = sc.nextInt();
		
		//Add your code starting here.
		int c = a + b;
		int d = a - b;
		int e = a*b;
		int f = a/b;
		int g = a%b;
		System.out.println(a+"+"+b+"="+c);
		System.out.println(a+"-"+b+"="+d);
		System.out.println(a+"*"+b+"="+e);
		System.out.println(a+"/"+b+"="+f);
		System.out.println(a+"%"+b+"="+g);


	}
	
}
