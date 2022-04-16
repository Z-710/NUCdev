import java.util.Scanner;

public class Marks {
	public static void main(String[] args) {
		//It all goes in here
		Scanner sc = new Scanner(System.in);
		System.out.print("How many students are there? ");
		int num =  sc.nextInt();
		int i = 0;
		String[] students = new String[num];
		double[] scores = new double[num]; 
		int low = 0;
		int high = 0;
		double lowscore = 0;
		double highscore = 0;
		System.out.print("Enter name of student 1: ");
		students[i] = sc.next()+sc.nextLine();
		System.out.print("Enter mark 1: ");
		scores[i] = sc.nextInt();
		lowscore = scores[i];
		highscore = scores[i];
		i = i + 1;
		while (i < students.length)
		{
			
			System.out.print("Enter name of student "+ (i+1) + ": ");
			students[i] = sc.next()+sc.nextLine();
			System.out.print("Enter mark "+ (i+1) + ": ");
			scores[i] = sc.nextDouble();
			if (scores[i] < lowscore)
			{
				low = i;
				lowscore = scores[i];
			}
			if (scores[i] > highscore)
			{
				high = i;
				highscore = scores[i];
			}
			i = i + 1;
		}
		i=0;
		double Total =0.0;
		double Average =0.0;
		while (i < scores.length)
		{
			Total = Total + scores[i];
			i=i+1;	
		}
		Average = (Total/scores.length);	
		System.out.println("The average mark is: "+Average);
		i=0;
		System.out.println("The best student is "+ students[high]);
		System.out.println("The worst student is "+ students[low]);
	}
}
