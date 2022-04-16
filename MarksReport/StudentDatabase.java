import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.util.stream.Collectors;
import java.util.List;

public class StudentDatabase {
	
	private Student[] students;
	
	public StudentDatabase(Student[] students) {
		this.students = students;
	}
	
	public static Student[] readStudentsFromFile(String filename) {
		
		try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
			
			List<String> rawData = reader.lines().collect(Collectors.toList());
			Student[] students = new Student[rawData.size()];
			
			for (int i = 0; i < students.length; ++i) {
				String[] splitData = rawData.get(i).split(" ");
				students[i] = new Student(splitData[0].trim(), Integer.parseInt(splitData[1]));
			}
			
			return students;
		}
		catch (FileNotFoundException e) {
			System.err.println("The input file does not exist.");
			System.err.println(e.getMessage());
		}
		catch (IOException e) {
			System.err.println("Something went wrong trying to read the file.");
			System.err.println(e.getMessage());
		}
		
		return null;
	}
	public static String highest(Student[] students) {
		Student highest = students[0];
		
		for (Student student : students) {
			if (student.currentMark() > highest.currentMark())
				highest = student;
		}
		
		return highest.studentName();
	}
		public static int highestMark(Student[] students) {
		Student highestMark = students[0];
		
		for (Student student : students) {
			if (student.currentMark() > highestMark.currentMark())
				highestMark = student;
		}
		
		return highestMark.currentMark();
	}
		public static String lowest(Student[] students) {
		Student lowest = students[0];
		
		for (Student student : students) {
			if (student.currentMark() < lowest.currentMark())
				lowest = student;
		}
		
		return lowest.studentName();
	}
			public static int lowestMark(Student[] students) {
		Student lowestMark = students[0];
		
		for (Student student : students) {
			if (student.currentMark() < lowestMark.currentMark())
				lowestMark = student;
		}
		
		return lowestMark.currentMark();
	}
	public static int totalStudents(Student[] students){
		int total = 0;
		return total = students.length;

	}
	public static float averageMark(Student[] students){
		float average = 0;
		float totalMark = 0;
		int i = 0;
		while (i < students.length){
			totalMark = totalMark + students[i].currentMark();
			i++;
		}
		return average = (totalMark/students.length);

	}
}
