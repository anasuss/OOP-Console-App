package managementOfStudentAbsences;


import java.util.ArrayList;

import java.sql.*;

import java.util.Date;

public class StudentManger {
	private Student currentStudent ; 
	StudentManger(){
		currentStudent = new Student() ; 
	}
	public Student getCurrentStudent() {
		return this.currentStudent ; 
	}
	private Student LoadDataBase(int id) {
		Student student = new Student() ; 
		try {
			DBConnection instance = new DBConnection() ; 
			Connection con = instance.getConnection() ; 
			Statement statement = con.createStatement() ; 
			ResultSet rs = statement.executeQuery("Select nom,prenom,login,pwd,classID from Etudiant where id_etudiant = "+id) ; 
			if (!rs.next())
				return null ; 
			student.setId(id); 
			student.setName(rs.getString("nom"));
			student.setSurname(rs.getString("prenom"));
			student.setUsername(rs.getString("login"));
			student.setPassword(rs.getString("pwd"));
			int idOfClass = rs.getInt("classID") ; 
			ResultSet getClass = statement.executeQuery("select filière,libelle,niveau from Classe where id_classe = "+idOfClass) ; 
			if(getClass.next()) {
				String filière = getClass.getString("filière") ;
				String name = getClass.getString("libelle") ; 
				String level = getClass.getString("niveau") ; 
				ResultSet getStudents = statement.executeQuery("Select * from Etudiant where classID = "+ idOfClass) ;
				ArrayList<Student> students = new ArrayList<Student>() ;
				while(getStudents.next()) {
					int idOfstudent = getStudents.getInt("id_etudiant") ; 
					String Name = getStudents.getString("nom") ; 
					String surname = getStudents.getString("prenom") ; 
					String username = getStudents.getString("login") ; 
					String password = getStudents.getString("pwd") ; 
					Student stud = new Student(idOfstudent,new ArrayList<Absence>() ,Name,surname,username,password) ; 
					students.add(stud) ; 
				}
				Classe c = new Classe((int)idOfClass,name,level,filière,students) ;
				student.setClass(c);
			}
			ResultSet getAbsences = statement.executeQuery("Select id_matière , date from Absence where id_etudiant = "+currentStudent.getId()) ;
			while(getAbsences.next()) {
				int idMatiere = getAbsences.getInt("id_matière") ; 
				Date d = getAbsences.getDate("date") ; 
				Statement statement1 = con.createStatement() ; 
				ResultSet getSubject = statement1.executeQuery("select libelle from Matière where id_matière = "+idMatiere) ; 
				if (getSubject.next()) {
					Subject s = new Subject(idMatiere,getSubject.getString("libelle")) ; 
					Absence a = new Absence(d,s) ;
					student.AddAbsence(a);
				}
			}
			statement.close(); 
			instance.close();
		}catch (SQLException e) {
			e.printStackTrace();
		}
		return student ; 
	}
	private boolean DoLogin() {
		while(true) {	
			System.out.print("Enter Id or -1 to cancel : ");
			currentStudent.setId(Main.in.nextInt());
			if (currentStudent.getId() == -1)
				return false ; 
			Student student = LoadDataBase(currentStudent.getId()) ; 
			if (student == null) {
				System.out.println("Invalide Id , please Try again ...");
				continue ;  
			}
			System.out.print("Enter userName : ");
			currentStudent.setUsername(Main.in.next());
			System.out.print("Enter password : ");
			currentStudent.setPassword(Main.in.next());
			if (!student.getPassword().equals(currentStudent.getPassword()) ||!student.getUsername().equals(currentStudent.getUsername())) {
				System.out.println("Invalid password or userName Try again ..") ; 
				continue ;   
			}
			currentStudent = student;
			return true ; 
		}
	}
	public boolean AccessSystem(){
		int choix = Menu.ShowReadMenu(Menu.list());
		if (choix == 1) {
			if (!DoLogin())
				return false ; 
		}else 
			return false ;
		return true ; 
	}
}
