#include <bits/stdc++.h>

using namespace std;

vector<string> readfileline(string path){
    vector<string> lines ;
    fstream file_handler(path.c_str()) ;

    if (file_handler.fail()){
		cout << "\n\nERROR: Can't open the file\n\n";
        return lines ;
    }
    string line ;
    while(getline(file_handler,line)){
        if (line.size() == 0)
            continue ;
        lines.push_back(line) ;
    }
    file_handler.close() ;
    return lines ;
}

void WriteFileLines(string path , vector<string> lines , bool append = true ){
    auto status = ios::in | ios::out | ios:: app ;
    if (!append)
        status = ios::in | ios :: out | ios :: trunc ;
    fstream file_handler(path.c_str(),status) ;
    if (file_handler.fail()){
        cout << "\n\nERROR: Can't open the file\n\n";
        return ;
    }
    for (string &line : lines)
        file_handler << line << "\n" ;
    file_handler.close() ;
}

int ToInt(string s){
    istringstream ss(s) ;
    int x ;
    ss >> x ;
    return x;
}

vector<string> Split_string(string line , string delemiter = ","){
    int pos = 0 ;
    vector<string> words ;
    while((pos = (int)line.find(delemiter)) != -1){
        string s = line.substr(0,pos) ;
        words.push_back(s);
        line.erase(0,pos+1) ;
    }
    words.push_back(line) ;
    return words ;
}

int ReadChoice(int low , int heigh){
	cout << "\nEnter number in range " << low << " - " << heigh << ": ";
    int x ;
    cin >> x ;
    if (x>=low && x<=heigh){
        return x ;
    }
	cout << "ERROR: invalid number...Try again\n";
    return ReadChoice(low,heigh) ;
}

int ShowMenu(vector<string> choices){
	cout << "\nMenu:\n";
	for (int i = 0; i < choices.size(); ++i) {
		cout << "\t" << i + 1 << ": " << choices[i] << "\n";
	}
	return ReadChoice(1, choices.size());
}


class User{
private :
    int id_user ;
    string user_name ;
    string password ;
    string name ;
    string email ;
    int allow_anonymous_questions ;
    vector<int> IdQuestionFromMe ;
    map<int,vector<int>> IdquestionToMe ;
public :
    User(){
        id_user = allow_anonymous_questions = -1 ;
    }
    User(string line){
        vector<string> words = Split_string(line) ;
        assert(words.size() == 6) ;
        id_user = ToInt(words[0]) ;
        user_name = words[1] ;
        password = words[2] ;
        name = words[3] ;
        email = words[4] ;
        allow_anonymous_questions = ToInt(words[5]) ;
    }
	void ResetToQuestions(const vector<int> &to_questions) {
		IdQuestionFromMe.clear();

		for (const auto & question_id : to_questions)
			IdQuestionFromMe.push_back(question_id);
	}
	void ResetFromQuestions(const vector<pair<int, int>> &to_questions) {
		IdquestionToMe.clear();

		for (const auto & id_pair : to_questions)
			IdquestionToMe[id_pair.first].push_back(id_pair.second);
	}
    string Tostring(){
        ostringstream ss ;
        ss << id_user << "," << user_name << "," << password << "," << name << "," << email << "," << allow_anonymous_questions ;
        return ss.str() ;
    }
    int GetUserId() const {
        return id_user ;
    }
    void SetUserId(int Id){
        id_user = Id ;
    }
    const int& Isallow_anonymous_questions () const {
        return allow_anonymous_questions ;
    }
    void SetAllow_anonymous_questions(int x){
        allow_anonymous_questions = x ;
    }
    const string& GetUserName()const{
        return user_name ;
    }
    void SetUserName(const string& s){
        user_name = s ;
    }
    const string& GetEmail() const {
        return email ;
    }
    void SetEmail(const string& s){
        email = s ;
    }
    const string& GetName ()const{
        return name;
    }
    void SetName(const string& s){
        name = s ;
    }
    const string& GetPassword () const {
        return password ;
    }
    void SetPassword(const string& s){
        password = s ;
    }
    const vector<int>& GetIdQuestionFromMe() const{
        return IdQuestionFromMe ;
    }
    const map<int,vector<int>>& GetIdQuestionToMe() const{
        return IdquestionToMe ;
    }
    void ReadUser(string &userName , int id){
        SetUserName(userName);
        SetUserId(id);
        string s ;
        int n;
		cout << "Enter password: ";
		cin >> s;
        SetPassword(s) ;
		cout << "Enter name: ";
		cin >> s ;
        SetName(s) ;
		cout << "Enter email: ";
		cin >> s ;
		SetEmail(s) ;
		cout << "Allow anonymous questions? (0 or 1): ";
		cin >> n;
        SetAllow_anonymous_questions(n);
    }

};


class UsersManager{
private :
    map<string,User> Users ;
    int last_id ;
    User currentUser ;
public :
    UsersManager(){
        last_id = 0 ;
    }
    void LoadDataBase(){
        last_id = 0 ;
        Users.clear() ;
        vector<string> lines = readfileline("users.txt") ;
        for (string &l : lines){
            User U(l) ;
            const string& s = U.GetUserName() ;
            Users[U.GetUserName()] = U ;
            last_id = max(last_id,U.GetUserId()) ;
        }
        return ;
    }
    void LogIn(){
        LoadDataBase() ;
        while(true){
            string userName,password ;
            cout << "\nEnter user name & password: ";
            cin >> userName >> password ;
            currentUser.SetUserName(userName) ;
            currentUser.SetPassword(password);
            if (!Users.count(currentUser.GetUserName())){
				cout << "\nInvalid user name or password. Try again\n\n";
				continue ;
            }
            const User &user = Users[currentUser.GetUserName()] ;
            if (user.GetPassword() != currentUser.GetPassword()){
				cout << "\nInvalid user name or password. Try again\n\n";
				continue ;
            }
            currentUser = user;
            break ;
        }
        return ;
    }
    void Access_system(){
        int choice = ShowMenu({"LogIn","Sign Up"}) ;
        if (choice == 1){
            LogIn() ;
        }else{
            SignUp() ;
        }
    }
    void UpdateDatabase(){
        string s = currentUser.Tostring() ;
        WriteFileLines("users.txt",{s}) ;
    }
    void SignUp(){
        while(true){
            string userName ;
            cout << "\nEnter user name : (no spaces)" ;
            cin >> userName ;
            if (Users.count(userName)){
                cout << "\nAlready used try again" ;
                continue ;
            }

            currentUser.ReadUser(userName,++last_id) ;
            break ;
        }
		Users[currentUser.GetUserName()] = currentUser;
		UpdateDatabase();
        return ;
    }
    void listSystemUser() const{
        for (auto &p : Users){
            const User& u = p.second ;
			cout << "ID: " << u.GetUserId() << "\t\tName: " << u.GetName() << "\n";
        }
    }
    pair<int,int> ReadId(){
        int id ;
        cout << "\nEnter Id or -1 to cancel: " ;
        cin >> id ;
        if (id == -1){
            return {-1,-1} ;
        }
        for (auto &it : Users){
            User &user = it.second ;
            if (user.GetUserId() == id)
                return {user.GetUserId(),user.Isallow_anonymous_questions()} ;
        }

        return ReadId() ;
    }

	void ResetToQuestions(const vector<int> &to_questions) {
		currentUser.ResetToQuestions(to_questions);
	}

	void ResetFromQuestions(const vector<pair<int, int>> &to_questions) {
		currentUser.ResetFromQuestions(to_questions);
	}
	const User& GetCurrentUser() const {
		return currentUser;
	}
};

class Question{
private :
    int id_question ;
    int parent_question ;
    int from_user ;
    int to_user ;
	int is_anonymous_questions;
    string question ;
    string answer ;
public :
    Question():id_question(-1),parent_question(-1) ,
        from_user(-1),
        to_user(-1) ,
        is_anonymous_questions(1){
    }
    Question(string line){
        vector<string> words = Split_string(line) ;
        id_question = ToInt(words[0]) ;
        parent_question = ToInt(words[1]) ;
        from_user = ToInt(words[2]) ;
        to_user = ToInt(words[3]) ;
        is_anonymous_questions = ToInt(words[4]) ;
        question = words[5] ;
        answer = words[6] ;
    }
    const string& GetAnswer()const{
        return answer ;
    }
    void SetAnswer(const string& s){
        answer = s ;
    }
    const string& GetQuestion() const{
        return question ;
    }
    void SetQuestion(const string& s){
        question = s ;
    }
    int IsAnonymousQuestion() const {
        return is_anonymous_questions ;
    }
    void SetAnonymousQuestion(int a){
        is_anonymous_questions = a ;
    }
    int GetToUser() const{
        return to_user ;
    }
    void SetToUser(int id){
        to_user = id ;
    }
    int GetFromUser() const{
        return from_user ;
    }
    void SetFromUser(int id){
        from_user = id ;
    }
    int GetIdParentQuestion()const{
        return id_question ;
    }
    void SetIdParentQuestion(int id){
        parent_question = id ;
    }
    int GetIdQuestion() const{
        return id_question ;
    }
    void SetIdQuestion(int id){
        id_question = id ;
    }
    string ToString() const {
        ostringstream ss ;
        ss << id_question << "," << parent_question << "," << from_user << "," << to_user << "," << is_anonymous_questions << "," << question << "," << answer << "," ;
        return ss.str() ;
    }
    void PrintToQuestion() const {
		string prefix = "";

		if (parent_question != -1)
			prefix = "\tThread: ";

		cout << prefix << "Question Id (" << id_question << ")";
		if (!is_anonymous_questions)
			cout << " from user id(" << from_user << ")";
		cout << "\t Question: " << question << "\n";

		if (answer != "")
			cout << prefix << "\tAnswer: " << answer << "\n";
		cout << "\n";
	}

	void PrintFromQuestion() const {
		cout << "Question Id (" << id_question << ")";
		if (!is_anonymous_questions)
			cout << " !AQ";

		cout << " to user id(" << to_user << ")";
		cout << "\t Question: " << question;

		if (answer != "")
			cout << "\tAnswer: " << answer << "\n";
		else
			cout << "\tNOT Answered YET\n";
	}

	void PrintFeedQuestion() const {
		if (parent_question != -1)
			cout << "Thread Parent Question ID (" << parent_question << ") ";

		cout << "Question Id (" << id_question << ")";
		if (!is_anonymous_questions)
			cout << " from user id(" << from_user << ")";

		cout << " To user id(" << to_user << ")";

		cout << "\t Question: " << question << "\n";
		if (answer != "")
			cout << "\tAnswer: " << answer <<"\n";
	}

};

class QuestionManager{
private :
  map<int,vector<int>> QuestionIDsThreads ;
  map<int,Question> Questions ;
  int last_id ;
public :
  QuestionManager() : last_id(0){
  }
  void LoadDataBase(){
    last_id = 0 ;
    QuestionIDsThreads.clear() ;
    Questions.clear() ;
    vector<string> lines = readfileline("questions.txt") ;
    for (string &l : lines){
        Question q(l) ;
        last_id = max(last_id,q.GetIdQuestion()) ;
        Questions[q.GetIdQuestion()] = q ;
        if (q.GetIdParentQuestion() == -1)
            QuestionIDsThreads[q.GetIdQuestion()].push_back(q.GetIdQuestion()) ;
        else
            QuestionIDsThreads[q.GetIdParentQuestion()].push_back(q.GetIdQuestion()) ;
    }
    return ;
  }
	vector<int> GetUserToQuestions(const User &user) const {
		vector<int> question_ids;

		for (const auto &pair : QuestionIDsThreads) {
			for (const auto &question_id : pair.second) {

				const Question &question = Questions.find(question_id)->second;

				if (question.GetFromUser() == user.GetUserId())
					question_ids.push_back(question.GetIdQuestion());
			}
		}
		return question_ids;
	}

	vector<pair<int, int>> GetUserFromQuestions(const User &user) const {
		vector<pair<int, int>> question_ids;

		for (const auto &pair : QuestionIDsThreads) {
			for (const auto &question_id : pair.second) {
				const Question &question = Questions.find(question_id)->second;

				if (question.GetToUser() == user.GetUserId()) {
					if (question.GetIdParentQuestion() == -1)
						question_ids.push_back(make_pair(question.GetIdQuestion(), question.GetIdQuestion()));
					else
						question_ids.push_back(make_pair(question.GetIdParentQuestion(), question.GetIdQuestion()));
				}
			}
		}
		return question_ids;
	}
	void PrintUserToQuestions(const User &user) const {
		cout << "\n";

		if (user.GetIdQuestionToMe().size() == 0)
			cout << "No Questions";

		for (const auto &pair : user.GetIdQuestionToMe()) {
			for (const auto &question_id : pair.second) {
				const Question &question = Questions.find(question_id)->second;
				question.PrintToQuestion();
			}
		}
		cout << "\n";
	}

	void PrintUserFromQuestions(const User &user) const {
		cout << "\n";
		if (user.GetIdQuestionFromMe().size() == 0)
			cout << "No Questions";

		for (const auto &question_id : user.GetIdQuestionFromMe()) {
			const Question &question = Questions.find(question_id)->second;
			question.PrintFromQuestion();
		}
		cout << "\n";
	}
  int ReadThreadQ(){
    int id ;
    cout << "\nFor Thread question : Enter question id or -1 for new question" ;
    cin >> id ;
    if (id == -1)
        return id ;
    if (Questions.count(id))
        return id ;
    return ReadThreadQ() ;
  }
  int ReadIdQ(int id_user){
    int id ;
    cout << "Enter Question Id or -1 to cancel : " ;
    cin >> id ;
    if (id == -1)
        return id ;
    if (!Questions.count(id)){
        cout << "\nERROR: No question with such ID. Try again\n\n";
        return ReadIdQ(id_user) ;
    }
    if (Questions[id].GetToUser() != id_user){
        cout << "\nERROR: Invalid question ID. Try again\n\n";
        return ReadIdQ(id_user) ;
    }
    return id ;
  }

  void DeleteQ(const User &u){
    int id = ReadIdQ(u.GetUserId()) ;
    if (id == -1)
        return ;
    vector<int> idsToRemove ;
    if (QuestionIDsThreads.count(id)){
        idsToRemove = QuestionIDsThreads[id] ;
        QuestionIDsThreads.erase(id) ;
    }else{
        idsToRemove.push_back(id) ;
        for (auto &it : QuestionIDsThreads){
            vector<int> &v = it.second ;
            bool found = false ;
            for (int i = 0 ; i<v.size() ; i++){
                if (v[i] == id){
                    v.erase(v.begin()+i) ;
                    found = true ;
                    break ;
                }
            }
            if (found)
                break ;
        }
    }
    for (int i : idsToRemove)
        Questions.erase(i) ;
  }
  void AnsewerQ(const User &u){
     int id = ReadIdQ(u.GetUserId()) ;
     if (id == -1)
        return ;
    if (Questions[id].GetAnswer() != ""){
        cout << "\nWarning: Already answered. Answer will be updated\n";
    }
    cout << "Enter Answer : " ;
    string answer ;
    Question &q = Questions[id] ;
    cin.ignore() ;
    getline(cin,answer) ;
    q.SetAnswer(answer) ;
  }
  void ASK(const User &user , pair<int,int> Id){
      Question q ;
      if (Id.second == -1)
        return ;
      if (Id.second == 0){
        cout << "\nNote : Anonymous questions are not allowed for this user" ;
        q.SetAnonymousQuestion(0) ;
      }else{
        cout << "\nIs anonymous Question (0 or 1) ?  : " ;
        int x ;
        cin >> x ;
        q.SetAnonymousQuestion(x) ;
      }
      q.SetIdQuestion(++last_id) ;
      q.SetIdParentQuestion(ReadThreadQ()) ;
      q.SetFromUser(user.GetUserId()) ;
      q.SetToUser(Id.first) ;
      cout << "\nEnter Question : " ;
      string s ;
      cin.ignore() ;
      getline(cin,s) ;
      q.SetQuestion(s) ;
      Questions[q.GetIdQuestion()] = q ;
      if (q.GetIdParentQuestion() == -1)
        QuestionIDsThreads[q.GetIdQuestion()].push_back(q.GetIdQuestion()) ;
      else
        QuestionIDsThreads[q.GetIdParentQuestion()].push_back(q.GetIdQuestion()) ;
    return ;
  }
  void ListFeed() const {
    for (const auto &pair : Questions) {
        const Question &question = pair.second;
        if (question.GetAnswer() == "")
            continue;
        question.PrintFeedQuestion();
    }
  }
  void UpadateDatabase(){
      vector<string> lines ;
      for (auto &it : Questions){
        Question &q = it.second ;
        lines.push_back(q.ToString()) ;
      }
      WriteFileLines("questions.txt",lines,false) ;
  }
};

class AskFm{
private :
    UsersManager u ;
    QuestionManager q ;
    void LoadDataBase(bool fill_user_question = false){
        u.LoadDataBase() ;
        q.LoadDataBase() ;
        if (fill_user_question)
            ResetCurrentUserQuestions() ;
    }
	void ResetCurrentUserQuestions() {
		const User& user = u.GetCurrentUser();

		const auto &to_questions = q.GetUserToQuestions(user);
		u.ResetToQuestions(to_questions);

		const auto &from_questions = q.GetUserFromQuestions(user);
		u.ResetFromQuestions(from_questions);
	}
public :
    void run(){
		LoadDataBase();
		u.Access_system();
		ResetCurrentUserQuestions();
		vector<string> menu;
		menu.push_back("Print Questions To Me");
		menu.push_back("Print Questions From Me");
		menu.push_back("Answer Question");
		menu.push_back("Delete Question");
		menu.push_back("Ask Question");
		menu.push_back("List System Users");
		menu.push_back("Feed");
		menu.push_back("Logout");
		while(true){
            LoadDataBase(true) ;
            int choice = ShowMenu(menu) ;
            if (choice == 1){
                q.PrintUserToQuestions(u.GetCurrentUser()) ;
            }
            else if (choice == 2){
                q.PrintUserFromQuestions(u.GetCurrentUser()) ;
            }
            else if (choice == 3){
                q.AnsewerQ(u.GetCurrentUser()) ;
                q.UpadateDatabase() ;
            }
            else if (choice == 4){
                q.DeleteQ(u.GetCurrentUser()) ;
                ResetCurrentUserQuestions() ;
                q.UpadateDatabase() ;
            }
            else if (choice == 5){
                pair<int,int> p = u.ReadId() ;
                q.ASK(u.GetCurrentUser(),p) ;
                q.UpadateDatabase() ;
            }
            else if (choice == 6){
                u.listSystemUser() ;
            }
            else if (choice == 7){
                q.ListFeed() ;
            }else{
                break ;
            }
		}
        run() ;
    }
};

int main()
{
    AskFm A ;
    A.run() ;
    return 0;
}
