class TeacherL{
private:
    string userName, pass, userId;
    Database db;
public:
    TeacherL(){

    }
    ~TeacherL(){

    }

    bool userNameCheck(){
        bool checkUser = false;
        Connection *conn = db.dbConnection();
        string selectQuery = "SELECT id, userName FROM tbl_teacher;";
        Statement *stmt = conn->createStatement();

        ResultSet *rset = stmt->executeQuery(selectQuery);
        while(rset->next()){
            if(rset->getString("userName") == userName){
                checkUser = true;
                userId = rset->getString("id");
                break;
            }
        }

        delete stmt;
        delete rset;
        conn->close();
        delete conn;

        return checkUser;
    }

    bool passCheck(){
        bool checkPass = false;
        Connection *conn = db.dbConnection();
        string selectQuery = "SELECT pass FROM tbl_teacher;";
        Statement *stmt = conn->createStatement();

        ResultSet *rset = stmt->executeQuery(selectQuery);
        while(rset->next()){
            if(rset->getString("pass") == pass){
                checkPass = true;
                break;
            }
        }

        delete stmt;
        delete rset;
        conn->close();
        delete conn;

        return checkPass;
    }

    void options(){
        string input;
        while(true){
            cout << "Show ur Classes(sc), Show ur Lessons(sl), Back(b): " << endl;
            cin >> input;
            if(input == "b"){
                break;
            }
            if(input == "sc"){
                showClass();
            }
            if(input == "sl"){
                showLessons();
            }
        }
    }

    void showClass(){
        Connection *conn = db.dbConnection();
        string selectQuery = "SELECT tbl_class.name as ClassName FROM tbl_teacher JOIN mm_class_teacher ON mm_class_teacher.fk_teacher = ? JOIN tbl_class ON mm_class_teacher.fk_class = tbl_class.id;";
        PreparedStatement *pstmt = conn->prepareStatement(selectQuery);

        pstmt->setString(1, userId);

        ResultSet *rset = pstmt->executeQuery();
        cout << "Classes:" << endl;
        while(rset->next()){
            cout << "\t" << rset->getString("ClassName") << endl;
        }

        delete pstmt;
        delete rset;
        conn->close();
        delete conn;
    }

    void showLessons(){
        Connection *conn = db.dbConnection();
        string selectQuery = "SELECT tbl_lesson.name as LessonName FROM tbl_teacher JOIN mm_lesson_teacher ON mm_lesson_teacher.fk_teacher = ? JOIN tbl_lesson ON mm_lesson_teacher.fk_lesson = tbl_lesson.id;";
        PreparedStatement *pstmt = conn->prepareStatement(selectQuery);

        pstmt->setString(1, userId);

        ResultSet *rset = pstmt->executeQuery();
        cout << "Lessons:" << endl;
        while(rset->next()){
            cout << "\t" << rset->getString("LessonName") << endl;
        }

        delete pstmt;
        delete rset;
        conn->close();
        delete conn;
    }

    void login(){
        while(true){
            cout << "Enter ur username(Back:b): ";
            cin >> userName;
            if(userName == "b"){
                    break;
            }
            if(userNameCheck()){
                cout << "Enter ur pass(Back:b): ";
                cin >> pass;
                if(pass == "b"){
                    break;
                }
                if(passCheck()){
                    cout << "Login successful." << endl;
                    options();
                }else{
                    cout << "Your password is incorrect." << endl;
                }
            }else{
                cout << "There is no such user." << endl;
            }
        }
    }
};
