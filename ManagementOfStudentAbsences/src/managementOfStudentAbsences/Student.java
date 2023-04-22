package managementOfStudentAbsences;

import java.util.ArrayList;

public class Student extends Person{
	private int id ; 
	private Classe classe;
	private ArrayList<Absence> absences;
	Student(){
		super() ; 
		this.absences = new ArrayList<Absence>() ;
		id = 0 ; 
	}
	Student(int id ,ArrayList<Absence> absences , String name, String surname, String username , String password) {
		super(name, surname, username,password);
		this.id = id ; 
		this.absences = absences ;
		// TODO Auto-generated constructor stub
	}
	public int getId() {
		return id ; 
	}
	public void setId(int id) {
		this.id = id ; 
	}
	public void AddAbsence(Absence a) {
		this.absences.add(a);
	}
	public Classe getClasse() {
		return this.classe ; 
	}
	public void setClass(Classe classe) {
		this.classe = classe ; 
	}
	public void printAbsences() {
		if (absences.isEmpty()) {
			System.out.println("You don't have any absence") ; 
			return ; 
		}
		System.out.println("You are absent in :") ; 
		for(Absence a : absences) {
			System.out.println("\tSubject : "+a.getSubject().getName()+"\t Date :"+a.getDate().toString());
		}
	}
}
