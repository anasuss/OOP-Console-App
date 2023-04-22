 package managementOfStudentAbsences;

import java.util.ArrayList;
import java.sql.*;

public class Teacher extends Person{
	private ArrayList<Classe> classes;
	private int id ; 
	Teacher(){
		super() ; 
		classes = new ArrayList<Classe>() ; 
		id = 0 ; 
	}
	Teacher(int id , String name, String surname, String username,String password){
		super(name,surname,username,password) ; 
		this.id = id ; 
	}
	Teacher(int id , String name, String surname, String username,String password,ArrayList<Classe>classes) {
		super(name, surname, username,password);
		this.id = id ; 
		this.classes = classes ; 
	}
	public void setID(int id) {
		this.id = id ; 
	}
	public int getId() {
		return this.id ; 
	}
	public void addClass(Classe x) {
		classes.add(x) ; 
	}
	public ArrayList<Classe> getListOfclasses(){
		return this.classes ; 
	}
	public void menu() throws SQLException {
		ArrayList<String> arr = new ArrayList<String>() ; 
		arr.add("Show Subject That I Teach") ; 
		arr.add("register Absence") ; 
		arr.add("Exit") ; 
		while(true) {
			int choix = Menu.ShowReadMenu(arr) ; 
			if (choix == 1)
				showSubject(true) ; 
			else if (choix == 2)
				setAbsence() ; 
			else 
				return ; 
		} 
	}
	private int showSubject(boolean b) throws SQLException {
		DBConnection db = new DBConnection() ; 
		Connection con = db.getConnection() ; 
		Statement statement = con.createStatement() ; 
		ResultSet rs1 = statement.executeQuery("select id_matière from Correspondance where id_enseignant = "+this.id); 
		Statement stmt = con.createStatement() ; 
		ArrayList<Subject> subjects = new ArrayList<Subject>() ; 
		while(rs1.next()) {
			ResultSet rs2 = stmt.executeQuery("select libelle from Matière where id_matière = "+rs1.getInt("id_matière")) ;
			if (rs2.next()) {
				String nameM = rs2.getString("libelle") ; 
				int idMatiere = rs1.getInt("id_matière") ; 
				subjects.add(new Subject(idMatiere,nameM)) ; 
			}
		}
		return Menu.ShowReadMenuS(subjects,b) ; 
	}
	private void setAbsence() throws SQLException{
		int choice = Menu.ShowReadMenuC(classes,0) ; 
		if (choice == -1) {
			return ; 
		}
		Classe classe = classes.get(choice-1) ; 
		if (classe.getStudents().isEmpty()) {
			System.out.print("\nEmpty Class");
			setAbsence() ; 
			return ; 
		}
		Menu.ShowMenu(classe.getStudents());
		DBConnection db = new DBConnection() ; 
		Connection con = db.getConnection() ; 
		Statement statement = con.createStatement();
		System.out.println("Register Absence Of Student : ");
		System.out.print("Enter ID of Student or -1 to Cancel : ");
		int idOfStudent = Main.in.nextInt() ; 
		if(idOfStudent == -1) {
			statement.close(); 
			db.close(); 
			return ; 
		}  
		System.out.println("In Which Subject") ; 
		int IdMatiere = showSubject(false); 
		System.out.print("Enter Year :");
		int year = Main.in.nextInt() ;
		System.out.print("Enter Month : ");
		int month = Main.in.nextInt() ; 
		System.out.print("Enter day : ");
		int day = Main.in.nextInt() ;
		String date = "'"+Integer.toString(year)+"-"+Integer.toString(month)+"-"+Integer.toString(day)+"'" ;
		String sql = "insert into Absence values ("+idOfStudent+","+this.id+","+IdMatiere+","+date+")" ; 
		statement.executeUpdate(sql);
	}
}
