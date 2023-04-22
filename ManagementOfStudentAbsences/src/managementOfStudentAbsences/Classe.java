package managementOfStudentAbsences;

import java.util.ArrayList;

public class Classe {
	  private String name;
	  private String level;
	  private int id ; 
	  private String filière ; 
	  private ArrayList<Student> students;
	  Classe(int id , String name, String level ,String filière ,ArrayList<Student> students) {
	    this.name = name;
	    this.level = level;
	    this.id = id ; 
	    this.filière = filière ; 
	    this.students = students;
	  }
	  public int getId() {
		  return id ; 
	  }
	  public String getName() {
	    return name;
	  }

	  public String getLevel() {
	    return level;
	  }
	  
	  public String getFilere() {
		  return this.filière ; 
	  }

	  public ArrayList<Student> getStudents() {
	    return students;
	  }

	  public void addStudent(Student student) {
	    students.add(student);
	  }
}