public class MarksReport {
	
	public static void main(String[] args) {
		
		StudentDatabase database = new StudentDatabase(StudentDatabase.readStudentsFromFile(args[0]));
		Student[] students = StudentDatabase.readStudentsFromFile(args[0]);
		System.out.println("There are "+database.totalStudents(students)+" students.");
		System.out.println("The average mark is "+database.averageMark(students)+".");
		System.out.println("The best student is "+ database.highest(students)+ " with a mark of " +database.highestMark(students) +".");
		System.out.println("The worst student is "+ database.lowest(students)+ " with a mark of " +database.lowestMark(students) +".");
		

	}
	
}
