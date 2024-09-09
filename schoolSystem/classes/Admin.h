class Admin{
private:
    string userName, pass;
    Database db;
public:
    Admin(){

    }
    ~Admin(){

    }
    string login(){
        while(true){
            cout << endl << "Enter admin's username: " << endl;
            cin >> userName;

            Connection *conn = db.dbConnection();

            string query = "SELECT name, pass FROM tbl_admin;";
            Statement *stmt = conn->createStatement();

            ResultSet *res = stmt->executeQuery(query);
            bool userFound, correctPass;

            while(res->next()){
                if(userName == res->getString("name")){
                    userFound = true;
                    cout << "Enter admin's password: " << endl;
                    cin >> pass;

                    if(pass == res->getString("pass")){
                        correctPass = true;
                        break;
                    }else{
                        correctPass = false;
                        break;
                    }
                }else{
                    userFound = false;
                }
            }

            if(userFound == false){
                cout << "There is no such user." << endl;
            }else{
                if(correctPass == false){
                    cout << "Password is incorrect." << endl;
                }else{
                    delete stmt;
                    delete res;
                    conn->close();
                    delete conn;
                    return userName;
                }
            }

            delete stmt;
            delete res;
            conn->close();
            delete conn;
        }
    }

    void adminOptions(){
        string input;
        while(true){
            cout << "Teacher Options(to), Student Options(so), Class Options(co), Lesson Options(lo), Back(b)" << endl;
            cin >> input;
            if(input == "to"){
                Teacher teacher;
                teacher.teacherOptions();
            }

            if(input == "so") {
                Student student;
                student.studentOptions();
            }

            if(input == "co"){
                Class cls;
                cls.classOptions();
            }

            if(input == "lo") {
                Lesson lesson;
                lesson.lessonOptions();
            }

            if(input == "b"){
                break;
            }

        }
    }

};
