package managementOfStudentAbsences;


import java.util.Date;

public class Absence {
	  private Date date;
	  private Subject subject ; 
	  public Absence(Date date, Subject subject) {
	    this.date = date ;
	    this.subject = subject ;
	  }
	  public Date getDate() {
	    return date;
	  }
	  public Subject getSubject() {
		  return this.subject ; 
	  }
}
