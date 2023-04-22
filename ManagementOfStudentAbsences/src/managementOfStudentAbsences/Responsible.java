package managementOfStudentAbsences;

import java.util.ArrayList;
import java.sql.*;

public class Responsible extends Person{
	private int id ; 
	ArrayList<Teacher> teachers ; 
	public Responsible() {
		this.id = 0 ; 
		teachers = new ArrayList<Teacher>() ; 
	}
	public Responsible(int id , String name, String surname,String password,String username) {
		super(name,surname,username,password) ;
		this.id = id ; 
	}
	public void setId(int id) {
		this.id = id ; 
	}
	public String getName() {
		return name;
	}
	public int getId() {
		return id ; 
	}
	public String getSurname() {
		return surname;
	}
	public void addTeacher(Teacher teacher) {
		teachers.add(teacher) ; 
	}
	static public void menu() throws SQLException {
		ArrayList<String> choices = new ArrayList<String>() ; 
		choices.add("Add Student") ; 
		choices.add("Add Teacher") ; 
		choices.add("Delete Absences") ; 
		choices.add("Show All absences") ; 
		choices.add("Show All Student") ; 
		choices.add("Show All Teacher") ; 
		choices.add("Add Classe To Teacher") ; 
		choices.add("Exit") ; 
		while(true) {
			int choice = Menu.ShowReadMenu(choices) ;
			if (choice == 1)
				registerStudent() ; 
			else if (choice == 2)
				registerTeacher() ;
			else if (choice == 3)
				deleteAbsence() ;
			else if (choice == 4)
				GetListOfAbsence() ; 
			else if (choice == 5) {
				ShowAll("Etudiant") ; 
			}else if (choice == 6) {
				ShowAll("Enseignant") ; 
			}else if (choice == 7){
				addClass() ; 
			}else { 
				break ; 
			}
		}
	}
	static void addClass() throws SQLException {
		System.out.println("Enter ID of Teacher : ") ; 
		int id = Main.in.nextInt() ; 
		DBConnection db = new DBConnection() ; 
		Connection con = db.getConnection() ; 
		Statement statement = con.createStatement() ; 
		ResultSet rs = statement.executeQuery("select id_enseignant as id from Enseignant where id_enseignant = "+id ); 
		if (!rs.next()) {
			System.out.println("There Is No Teacher With This ID") ; 
			return ; 
		}
		int idClasse = choseClasse(false) ;
		int idMatiere = choseMatiere() ;
		//System.out.println("ID ="+id+" IDM = "+idMatiere+" IDC = "+idClasse) ; 
		String sql = "insert into Correspondance values("+id+","+idMatiere+","+idClasse+")" ;  
		statement.executeUpdate(sql);
		db.close();
	}
	static private void ShowAll(String table) throws SQLException {
		ArrayList<Student> students = new ArrayList<Student>() ;
		ArrayList<Teacher> teachers = new ArrayList<Teacher>() ; 
		DBConnection instance = new DBConnection() ; 
		Connection con = instance.getConnection() ; 
		Statement statement = con.createStatement() ; 
		ResultSet res = statement.executeQuery("Select * from "+table) ;
		while(res.next()) {
			int id = 0 ;  
			String Name = res.getString("nom") ; 
			String surname = res.getString("prenom") ; 
			String username = res.getString("login") ; 
			String password = res.getString("pwd") ; 
			if (table.equals("Etudiant")) {
				id = res.getInt("id_etudiant") ; 
				Student student = new Student(id,new ArrayList<Absence>() ,Name,surname,username,password) ; 
				students.add(student) ; 
			}else {
				id = res.getInt("id_enseignant") ; 
				Teacher teacher = new Teacher(id,Name,surname,username,password) ;
				teachers.add(teacher);  
			}
		}
		if (table.equals("Enseignant")) {
			if (teachers.isEmpty()) {
				System.out.println("There Is No Teachers") ; 
				return ; 
			}
			Menu.ShowMenuT(teachers);
		}else {
			if (students.isEmpty()) {
				System.out.println("There Is No Students") ; 
				return ; 
			}
			Menu.ShowMenu(students);
		}
		return ; 
	}
	static private int choseClasse(boolean student) throws SQLException {
		  DBConnection db = new DBConnection() ; 
		  Connection con = db.getConnection() ; 
		  Statement statement = con.createStatement() ;
		  ArrayList<Classe> classes = new ArrayList<Classe>() ;
		  ResultSet getClass = statement.executeQuery("select id_classe,filière,libelle,niveau from Classe") ; 
		  while(getClass.next()) {
			  	int idOfClasse = getClass.getInt("id_classe") ; 
				String filière = getClass.getString("filière") ;
				String name = getClass.getString("libelle") ; 
				String level = getClass.getString("niveau") ;
				Classe c = new Classe((int)idOfClasse,name,level,filière,null) ;
				classes.add(c);
		 }
		  statement.close();  
		  db.close();
		  if (student)
			  return Menu.ShowReadMenuC(classes,1);
		  return Menu.ShowReadMenuC(classes,2);
	}
	static private void add(String table) throws SQLException {
	  DBConnection db = new DBConnection() ; 
	  Connection con = db.getConnection() ; 
	  Statement statement = con.createStatement() ; 
	  System.out.print("Enter Name : ");
	  String name = Main.in.next() ; 
	  System.out.print("Enter Surname : ");
	  String surname = Main.in.next() ;
	  System.out.print("Enter username : ");
	  String username = Main.in.next() ;
	  System.out.print("Enter Password : ");
	  String password = Main.in.next() ;
	  String sql = "insert into "+table+" values ('"+name+"','"+surname+"','"+username+"','"+password+"'" ; 
	  if (table.equals("Etudiant")) {
		  int choix = choseClasse(true);
		  sql = sql+",'"+choix+"'" ; 
	  }
	  sql = sql+")" ; 
	  statement.executeUpdate(sql);
	  if(table.equals("Enseignant")) {
		  // to be continue ;
		  ResultSet rs = statement.executeQuery("select max(id_enseignant) as id from Enseignant"); 
		  int idTeacher = 0 ; 
		  if (rs.next())
			  idTeacher = rs.getInt("id") ; 
		  int idClasse = choseClasse(false) ;
		  int idMatiere = choseMatiere() ;
		  sql = "insert into Correspondance values("+idTeacher+","+idMatiere+","+idClasse+")" ;  
		  statement.executeUpdate(sql);
	  }
	  statement.close(); 
	  db.close();
	}
	static public int choseMatiere() throws SQLException {
		DBConnection db = new DBConnection() ; 
		Connection con = db.getConnection() ; 
		Statement stmt = con.createStatement() ;
		ResultSet rs = stmt.executeQuery("select id_matière,libelle from Matière") ;
		System.out.print("Chose Subject of Teaher : ") ; 
		ArrayList<Subject> arr = new ArrayList<Subject>() ; 
		while(rs.next()) {
			int id = rs.getInt("id_matière"); 
			String libelle = rs.getString("libelle") ; 
			arr.add(new Subject(id,libelle)) ; 
		}
		stmt.close(); 
		db.close();
		return Menu.ShowReadMenuS(arr,false);
	}
	static public void registerStudent() throws SQLException {
		add("Etudiant") ; 
	}
	static public void registerTeacher() throws SQLException {  
		add("Enseignant") ; 		
	}
	private static boolean GetListOfAbsence() throws SQLException{
		ArrayList<String> list = new ArrayList<String>() ; 
		DBConnection db = new DBConnection() ; 
		Connection con = db.getConnection() ; 
		Statement statement = con.createStatement() ; 
		ResultSet res = statement.executeQuery("select id_etudiant,id_enseignant,id_matière,numseance,date from Absence") ; 
		while(res.next()) {
			int idTeacher = res.getInt("id_enseignant") ;
			int idSubject = res.getInt("id_matière") ; 
			String Student = null,Teacher = null,Matiere = null,Seance=null ; 
			Statement stmt1 = con.createStatement() ; 
			ResultSet rs1 = stmt1.executeQuery("select nom , prenom from Etudiant where id_etudiant = "+res.getString("id_etudiant")) ;
			if(rs1.next()) {
				Student = "ID = "+res.getInt("id_etudiant")+" Name = "+rs1.getString("nom")+" Surname = "+rs1.getString("prenom") ; 
			}
			rs1 = stmt1.executeQuery("select nom , prenom from Enseignant where id_enseignant = "+idTeacher) ;
			if (rs1.next()) {
				Teacher = "ID = "+idTeacher+" Name ="+rs1.getString("nom")+" Surname = "+rs1.getString("prenom") ; 	
			}
			rs1 = stmt1.executeQuery("select libelle from Matière where id_matière = "+idSubject) ;
			if (rs1.next()) {
				Matiere = "ID = "+idSubject+" Name = "+rs1.getString("libelle") ;
			}
			Seance = "IdSeance = "+res.getInt("numseance") ; 
			String s = "\tSeance : "+Seance +"\n\tStudent : "+Student+ "\n\tTeacher :"+Teacher+"\n\tSubject :"+Matiere+"\n----------------------------------------------------------------";
			stmt1.close(); 
			list.add(s) ;
		}
		if (list.isEmpty()) {
			System.out.println("There is No absences") ; 
			return false ; 
		}
		System.out.println("List of Absences : ") ; 
		for(String s : list) {
			System.out.println(s);
		}
		statement.close(); 
		db.close() ; 		
		return  true ; 
	}
	public static void deleteAbsence() throws SQLException {
		DBConnection db = new DBConnection() ; 
		Connection con = db.getConnection() ; 
		Statement statement = con.createStatement() ; 
		while(true) {
			if (!GetListOfAbsence()){
				return ; 
			}
			System.out.print("Enter 0 to Exit or 1 to continue : ");
			int exit = Main.in.nextInt() ; 
			if (exit == 0)
				break ; 
			System.out.print("Enter Id Of Seance : ");
			int idSeance = Main.in.nextInt() ; 
			System.out.print("Enter Id Of Student : ");
			int idStudent = Main.in.nextInt() ; 
			System.out.print("Enter Id Of Teacher : ");
			int idTeacher = Main.in.nextInt() ; 
			System.out.print("Enter Id Of Matiere : ");
			int idMatiere = Main.in.nextInt() ;
			statement.executeUpdate("delete from Absence where id_etudiant = "+idStudent+ " and id_enseignant = "+idTeacher+" and id_matière = "+idMatiere+ "and numseance = "+idSeance) ; 
		}
		statement.close();
		db.close() ; 
	}
}
