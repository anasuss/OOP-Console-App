package managementOfStudentAbsences;

import java.sql.*;

import java.util.ArrayList;

public class ResponsibleManger {
	private Responsible currentResponsible ;
	ResponsibleManger(){
		this.currentResponsible = new Responsible() ; 
	}
	public Responsible getCurrentResponsible() {
		return this.currentResponsible ; 
	}
	private boolean ExistResponsable(int id) throws SQLException {
		DBConnection instance = new DBConnection() ; 
		Connection con = instance.getConnection() ; 
		Statement statement = con.createStatement() ; 
		ResultSet rs = statement.executeQuery("Select * from Responsable where id_responsable = "+id) ; 
		if (rs.next()) {
			instance.close(); 
			return true ; 
		}
		instance.close(); 
		return false ; 
	}
	private void LoadDataBase(int id) {
		try {
			DBConnection instance = new DBConnection() ; 
			Connection con = instance.getConnection() ; 
			Statement statement = con.createStatement() ; 
			ResultSet rs = statement.executeQuery("Select nom,prenom,login,pwd from Responsable where id_responsable = "+id) ; 
			if (rs.next()) {
				currentResponsible.setId(id); 
				currentResponsible.setName(rs.getString("nom"));
				currentResponsible.setSurname(rs.getString("prenom"));
				currentResponsible.setUsername(rs.getString("login"));
				currentResponsible.setPassword(rs.getString("pwd"));
			}
			rs = statement.executeQuery("Select id_enseignant,nom,prenom,login,pwd from Enseignant") ;
			while(rs.next()) {
				Teacher teacher = new Teacher() ; 
				teacher.setID(rs.getInt("id_enseignant")) ; 
				teacher.setName(rs.getString("nom"));
				teacher.setSurname(rs.getString("prenom"));
				teacher.setUsername(rs.getString("login"));
				teacher.setPassword(rs.getString("pwd"));
				Statement stmt = con.createStatement() ;  
				ResultSet rs1 = stmt.executeQuery("select id_classe from Correspondance where id_enseignant = "+id); 
				ArrayList<Integer> idOfClasses = new ArrayList<Integer>() ; 
				while(rs1.next()) {
					int idOfClass = rs1.getInt("id_classe") ;
					idOfClasses.add(idOfClass);
				}
				for (Integer idOfClass : idOfClasses) {
					ResultSet getClass = stmt.executeQuery("select filière,libelle,niveau from Classe where id_classe = "+idOfClass) ; 
					if(getClass.next()) {
						String filière = getClass.getString("filière") ;
						String name = getClass.getString("libelle") ; 
						String level = getClass.getString("niveau") ; 
						ResultSet getStudents = stmt.executeQuery("Select * from Etudiant where classID = "+ idOfClass) ;
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
				currentResponsible.addTeacher(teacher) ; 
			}
			statement.close();  
			instance.close();
		}catch (SQLException e) {
			e.printStackTrace();
		}
	}
	private boolean DoLogin() throws SQLException {
		while(true) {
			System.out.print("Enter Id or -1 to cancel : ");
			currentResponsible.setId(Main.in.nextInt());
			if (currentResponsible.getId() == -1)
				return false ; 
			if (!ExistResponsable(currentResponsible.getId())){
				System.out.println("Invalide Id , please Try again ...");
				continue ; 
			}
			LoadDataBase(currentResponsible.getId()) ; 
			System.out.print("Enter userName : ");
			String username = Main.in.next() ; 
			System.out.print("Enter password : ");
			String password = Main.in.next() ; 
			if (!password.equals(currentResponsible.getPassword()) ||!username.equals(currentResponsible.getUsername())) {
				System.out.println("Invalid password or userName Try again ..") ; 
				continue ; 
			}
			return true ; 
		}
	}
	public boolean AccessSystem() throws SQLException{
		int choix = Menu.ShowReadMenu(Menu.list());
		if (choix == 1) {
			if (!DoLogin())
				return false ; 
		}else 
			return false;
		return true ; 
	}
}
