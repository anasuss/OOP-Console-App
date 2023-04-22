package managementOfStudentAbsences;

import java.sql.SQLException;

public class ManagementOfStudentAbsences {

	public static void run() throws SQLException {
	    while(true){
			int choix = Menu.ShowReadMenu(Menu.MainMenu()) ;
			if (choix == 1) {
				ResponsibleManger ResponsibleManger = new ResponsibleManger() ;  
				if (ResponsibleManger.AccessSystem())
					Responsible.menu();
			}
			else if (choix == 2) {
				TeacherManger teacherManger = new TeacherManger()  ; 
				if (teacherManger.AccessSystem()) {
					Teacher teacher = teacherManger.getCurrentTeacher() ;
					teacher.menu();
				}
			}
			else if (choix == 3) {
				StudentManger studentManger = new StudentManger()  ; 
				if (studentManger.AccessSystem()) {
					Student s = studentManger.getCurrentStudent() ; 
					s.printAbsences();
				}
			}
			else 
				break ; 
		}
	}

}