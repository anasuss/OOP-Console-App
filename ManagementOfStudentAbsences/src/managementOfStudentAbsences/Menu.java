package managementOfStudentAbsences;

import java.util.ArrayList;

public class Menu {
	static int ReadInt(int low, int high) {
		System.out.print("\nEnter number in range " + low + " - " + high + ": ") ; 
		int value = Main.in.nextInt();
		if (low <= value && value <= high)
			return value;
		System.out.print("ERROR: invalid number...Try again\n") ;
		return ReadInt(low, high);
	}
	static int ShowReadMenu(ArrayList<String> choices) {
		System.out.print("\nMenu:\n") ; 
		for (int ch = 0; ch < (int) choices.size(); ++ch) {
			System.out.print("\t" + (ch + 1) + ": " + choices.get(ch) + "\n") ; 
		}
		return ReadInt(1, choices.size());
	}
	static int ShowReadMenuS(ArrayList<Subject> choices , boolean teacher) {
		System.out.print("\nMenu:\n") ; 
		for (int ch = 0; ch < (int) choices.size(); ++ch) {
			System.out.print("\t" + (ch + 1) + ": ID = " + choices.get(ch).getId() +"\tLibelle = "+choices.get(ch).getName()+ "\n") ; 
		}
		if (teacher)
			return 0 ; 
		int choix = ReadInt(1, choices.size());  
		return choices.get(choix-1).getId();
	}
	static int ShowReadMenuC(ArrayList<Classe> choices,int choix) {
		if (choix == 0) {
			System.out.print("\nChoose  Classe:") ; 
			System.out.print("\nList Of Classes That You Teach:\n") ; 
		}else if (choix == 1 ) 
			System.out.print("\nChoose  Classe of Student:\n") ;
		else if (choix == 2)
			System.out.print("\nChoose  Classe of Teacher :\n") ;
		
		for (int ch = 0; ch < (int) choices.size(); ++ch) {
			System.out.print("\t" + (ch + 1) + ": " + choices.get(ch).getName()+"\t"+choices.get(ch).getFilere()+"\t"+choices.get(ch).getLevel()+ "\n") ; 
		}
		if (choix == 0) {
			System.out.print("\t" + (choices.size()+1) + ": " + "Exit\n") ; 
			int choice = ReadInt(1, choices.size()+1);
			if (choice == choices.size()+1) {
				return -1 ; 
			}
			return choice ; 
		}
		int choice = ReadInt(1, choices.size());
		return choices.get(choice-1).getId() ; 
	}
	static void ShowMenu(ArrayList<Student> choices) {
		System.out.print("\nList Of Students:\n") ; 
		for (int ch = 0; ch < (int) choices.size(); ++ch) {
			System.out.print("\t" + (ch + 1) + ": ID = " + choices.get(ch).getId()+"\t Name = "+choices.get(ch).getName()+"\t Surname = "+choices.get(ch).getSurname()+ "\n") ; 
		}
		return ; 
	}
	static void ShowMenuT(ArrayList<Teacher> choices) {
		System.out.print("\nList Of Teacher:\n") ; 
		for (int ch = 0; ch < (int) choices.size(); ++ch) {
			System.out.print("\t" + (ch + 1) + ": ID = " + choices.get(ch).getId()+"\t Name = "+choices.get(ch).getName()+"\t Surname = "+choices.get(ch).getSurname()+ "\n") ; 
		}
		return ; 
	}
	public static ArrayList<String> list() {
		ArrayList<String> list = new ArrayList<>() ; 
		list.add("Login");
		list.add("Exit") ; 
		return list ; 
	}
	public static ArrayList<String> MainMenu() {
		ArrayList<String> list = new ArrayList<>() ; 
		list.add("Responsible") ;
		list.add("Teacher") ; 
		list.add("Student") ; 
		list.add("Exit") ; 
		return list ; 	
	}

}

