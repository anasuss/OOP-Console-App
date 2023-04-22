package managementOfStudentAbsences;

public class Person {
	protected String name;
	protected String surname; 
	protected String username ; 
	protected String password ; 
	Person(){
		
	}
	Person(String name , String surname , String username, String password){
		this.name = name ; 
		this.surname = surname ; 
		this.username = username ; 
		this.password = password ; 
	}
	protected void setPassword(String password) {
		this.password = password ; 
	}
	protected String getPassword() {
		return this.password ; 
	}
	protected void setName(String name) {
		this.name = name ; 
	}
	protected String getName() {
		return name ; 
	}
	protected void setSurname(String surname) {
		this.surname = surname ; 
	}
	protected String getSurname() {
		return surname ; 
	}
	protected void setUsername(String username) {
		this.username = username ; 
	}
	protected String getUsername() {
		return username ; 
	}
}

