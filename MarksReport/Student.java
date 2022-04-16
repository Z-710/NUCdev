public class Student {
	private String name;
	private int mark;
	
	public Student(String name, int mark) {
		this.name = name;
		this.mark = mark;
	}
		public String studentName() {
		return this.name;
	}
		public int currentMark() {
		return (int)this.mark;
	}


}
