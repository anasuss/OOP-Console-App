package managementOfStudentAbsences;

import java.util.ArrayList;

import java.sql.*;

public class TeacherManger {
	private Teacher currentTeacher ; 
	TeacherManger(){
		currentTeacher = new Teacher() ; 
	}
	public Teacher getCurrentTeacher() {
		return this.currentTeacher ; 
	}
	private Teacher LoadDataBase(int id) {
		Teacher teacher = new Teacher() ; 
		try {
			DBConnection instance = new DBConnection() ; 
			Connection con = instance.getConnection() ; 
			Statement statement = con.createStatement() ; 
			ResultSet rs = statement.executeQuery("Select nom,prenom,login,pwd from Enseignant where id_enseignant = "+id) ; 
			if (!rs.next())
				return null ; 
			teacher.setID(id); 
			teacher.setName(rs.getString("nom"));
			teacher.setSurname(rs.getString("prenom"));
			teacher.setUsername(rs.getString("login"));
			teacher.setPassword(rs.getString("pwd"));
			ResultSet rs1 = statement.executeQuery("select id_matière,id_classe from Correspondance where id_enseignant = "+id); 
			ArrayList<Integer> idOfClasses = new ArrayList<Integer>() ; 
			while(rs1.next()) {
				int idOfClass = rs1.getInt("id_classe") ;
				idOfClasses.add(idOfClass);
			}
			for (Integer idOfClass : idOfClasses) {
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
						Student student = new Student(idOfstudent,new ArrayList<Absence>() ,Name,surname,username,password) ; 
						students.add(student) ; 
					}
					Classe c = new Classe((int)idOfClass,name,level,filière,students) ;
					teacher.addClass(c);
				}
			}
			statement.close();
			instance.close();
		}catch (SQLException e) {
			e.printStackTrace();
		}
		return teacher ;	
	}
	private boolean TeacherExist(int id) {
		DBConnection instance = new DBConnection() ; 
		try {
			Connection con = instance.getConnection() ; 
			Statement statement = con.createStatement() ; 
			ResultSet rs = statement.executeQuery("Select id_enseignant from Enseignant where id_enseignant = "+id) ; 
			if (!rs.next())
				return false ; 
			statement.close(); 
			instance.close();
		}catch (SQLException e) {
			e.printStackTrace();
		}
		return true ; 
	}
	private boolean DoLogin() {
		while(true) {
			System.out.print("Enter Id or -1 to cancel : ");
			currentTeacher.setID(Main.in.nextInt());
			if (currentTeacher.getId() == -1)
				return false; 
			if (!TeacherExist(currentTeacher.getId()) ) {
				System.out.println("Invalide Id , please Try again ...");
				continue ; 
			}
			Teacher teacher = LoadDataBase(currentTeacher.getId()) ; 
			System.out.print("Enter userName : ");
			currentTeacher.setUsername(Main.in.next());
			System.out.print("Enter password : ");
			currentTeacher.setPassword(Main.in.next());
			if (!teacher.getPassword().equals(currentTeacher.getPassword()) ||!teacher.getUsername().equals(currentTeacher.getUsername())) {
				System.out.println("Invalid password or userName Try again ..") ; 
				continue ; 
			}
			currentTeacher = teacher;	
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
