package managementOfStudentAbsences;

public class Subject {
	  private String name;
	  private int id ; 
	  public Subject() {
		  id = 0 ; 
	  }
	  public Subject(int id , String name) {
	    this.id = id ; 
		this.name = name;
	  }

	  public String getName() {
	    return name;
	  }
	  public int getId() {
		  return this.id ; 
	  }
}
