class Student{
private:
    string name, lastName, userName, pass, country, city, postCode, street, className, lessonName;
    int classId, lessonId, lastSId, deleteStudentID;
    Database db;
public:
    Student(){

    }
    ~Student(){

    }

    void studentOptions(){
        while(true){
            string input;
            cout << "Add Student(as), Add Class for Student(ac), Add Lesson for Student(al), List Students(ls), Show Student Info(si), Remove Student(rs), Back(b)" << endl;
            cin >> input;

            if(input == "b"){
                break;
            }

            if(input == "as"){
                addStudent();
            }

            if(input == "ls"){
                listStudents();
            }

            if(input == "si"){
                showStudentInfo();
            }

            if(input == "ac"){
                addClassS();
            }

            if(input == "al"){
                addLessonS();
            }

            if(input == "rs"){
                removeStudent();
            }

        }
    }

    bool getInput(const string& prompt, string& input){
        cout << prompt;
        getline(cin, input);
        return input != "b";
    }

    bool checkUsername(){

        Connection *conn = db.dbConnection();

        bool checkUserName = false;
        string selectQuery = "SELECT id, userName FROM tbl_student;";
        Statement *stmt = conn->createStatement();

        ResultSet *rset = stmt->executeQuery(selectQuery);

        while(rset->next()){
            if(rset->getString("userName") == userName){
                checkUserName = true;
                deleteStudentID = rset->getInt("id");
                break;
            }
        }

        delete stmt;
        delete rset;
        conn->close();
        delete conn;

        return checkUserName;
    }

    bool chooseClass(){
        while(true){

            Class clss;
            clss.listClasses();

            cout << "Enter the student's class (Back:b): ";
            cin >> className;

            if(className == "b"){
                return false;
                break;
            }

            Connection *conn = db.dbConnection();

            bool checkClassName = false;
            string selectQuery = "SELECT id, name FROM tbl_class;";
            Statement *stmt = conn->createStatement();

            ResultSet *rset = stmt->executeQuery(selectQuery);

            while(rset->next()){
                if(rset->getString("name") == className){
                    checkClassName = true;
                    classId = rset->getInt("id");
                    break;
                }
            }

            delete stmt;
            delete rset;
            conn->close();
            delete conn;

            if(checkClassName){
                return true;
            }else{
                cout << "Please check the list of classes!" << endl;
            }

        }
    }

    bool chooseLesson(){
        while(true){

            Lesson lesson;
            lesson.listLessons();

            cout << "Enter the student's lesson (Back:b): ";
            cin >> lessonName;

            if(lessonName == "b"){
                return false;
                break;
            }

            Connection *conn = db.dbConnection();

            bool checkLessonName = false;
            string selectQuery = "SELECT id, name FROM tbl_lesson;";
            Statement *stmt = conn->createStatement();

            ResultSet *rset = stmt->executeQuery(selectQuery);

            while(rset->next()){
                if(rset->getString("name") == lessonName){
                    checkLessonName = true;
                    lessonId = rset->getInt("id");
                    break;
                }
            }

            delete stmt;
            delete rset;
            conn->close();
            delete conn;

            if(checkLessonName){
                return true;
            }else{
                cout << "Please check the list of lessons!" << endl;
            }

        }
    }

    void saveStudent(){

        Connection *conn = db.dbConnection();

        string saveQuery = "INSERT INTO tbl_student(name, lastName, userName, pass, country, city, postCode, street) VALUES(?, ?, ?, ?, ?, ?, ?, ?);";
        PreparedStatement *pstmt = conn->prepareStatement(saveQuery);

        pstmt->setString(1, name);
        pstmt->setString(2, lastName);
        pstmt->setString(3, userName);
        pstmt->setString(4, pass);
        pstmt->setString(5, country);
        pstmt->setString(6, city);
        pstmt->setString(7, postCode);
        pstmt->setString(8, street);

        pstmt->execute();

        delete pstmt;

        string lastSID = "SELECT MAX(id) as last_student_id FROM tbl_student;";
        Statement *stmt = conn->createStatement();

        ResultSet *rset = stmt->executeQuery(lastSID);

        if(rset->next()){
            lastSId = rset->getInt("last_student_id");
        }

        delete stmt;
        delete rset;
        conn->close();
        delete conn;

    }

    void addStudent(){
        while(true){
            cin.ignore();
            if(!getInput("Enter the student's name (Back:b): ", name)){
                break;
            }

            if(!getInput("Enter the student's lastname (Back:b): ", lastName)){
                break;
            }

            while(true){
                if(!getInput("Enter the student's username (Back:b): ", userName)){
                break;
                }else{
                    if(checkUsername()){
                        cout << "This username is already exist in database." << endl;
                    }else{
                        break;
                    }
                }
            }

            if(!getInput("Enter the student's password (Back:b): ", pass)){
                break;
            }

            if(!getInput("Enter the country (Back:b): ", country)){
                break;
            }

            if(!getInput("Enter the city (Back:b): ", city)){
                break;
            }

            if(!getInput("Enter the postcode (Back:b): ", postCode)){
                break;
            }

            if(!getInput("Enter the street (Back:b): ", street)){
                break;
            }

            saveStudent();
            cout << "Successful!" << endl;
            break;

        }
    }

    void listStudents(){
        cout << endl << "*****List of Students*****" << endl;

        Connection *conn = db.dbConnection();

        string selectQuery = "SELECT name, lastName, userName, pass, country, city, postCode, street FROM tbl_student;";
        Statement *stmt = conn->createStatement();

        ResultSet *rset = stmt->executeQuery(selectQuery);

        while(rset->next()){
            cout << rset->getString("name") << "\t";
            cout << rset->getString("lastName") << "\t";
            cout << rset->getString("userName") << "\t";
            cout << rset->getString("pass") <<  "\t";
            cout << rset->getString("country") << "\t";
            cout << rset->getString("city") << "\t";
            cout << rset->getString("postCode") << "\t";
            cout << rset->getString("street");
            cout << endl;
        }

        delete stmt;
        delete rset;
        conn->close();
        delete conn;

    }

    void removeStudent(){
        while(true){
            listStudents();
            cout << "Enter the student's username that u want to remove (Back:b): ";
            cin >> userName;

            if(userName == "b"){
                break;
            }

            if(checkUsername()){
                Connection *conn = db.dbConnection();

                string deleteQuery = "DELETE FROM mm_class_student WHERE fk_student=?;";
                PreparedStatement *pstmt = conn->prepareStatement(deleteQuery);
                pstmt->setInt(1, deleteStudentID);
                pstmt->execute();

                string deleteQuery2 = "DELETE FROM mm_lesson_student WHERE fk_student=?;";
                PreparedStatement *pstmt2 = conn->prepareStatement(deleteQuery2);
                pstmt2->setInt(1, deleteStudentID);
                pstmt2->execute();

                string deleteQuery3 = "DELETE FROM tbl_student WHERE userName=?;";

                PreparedStatement *pstmt3 = conn->prepareStatement(deleteQuery3);
                pstmt3->setString(1, userName);
                pstmt3->execute();

                delete pstmt;
                delete pstmt2;
                delete pstmt3;
                conn->close();
                delete conn;
                break;
            }else{
                cout << "There is no such username." << endl;
            }
        }
    }

    void addClassS(){
        while(true){
            listStudents();
            cout << endl << "Enter an username that u want to add class for this student(Back:b): ";
            cin >> userName;

            if(userName=="b"){
                break;
            }


            if(checkUsername()){
                Connection *conn = db.dbConnection();
                string checkClass = "SELECT * FROM mm_class_student WHERE fk_student=?;";
                PreparedStatement *pstmt = conn->prepareStatement(checkClass);
                pstmt->setInt(1, deleteStudentID);

                ResultSet *rset = pstmt->executeQuery();
                if(rset->next()){
                    cout << "This student has already a class." << endl;
                    break;
                }

                delete pstmt;
                delete rset;
                conn->close();
                delete conn;

                if(chooseClass()){
                    Connection *conn = db.dbConnection();
                    string saveSClass = "INSERT INTO mm_class_student(fk_class, fk_student, startDate) VALUES(?, ?, ?);";
                    PreparedStatement *pstmt = conn->prepareStatement(saveSClass);

                    pstmt->setInt(1, classId);
                    pstmt->setInt(2, deleteStudentID);
                    pstmt->setString(3, "2024-09-01");

                    pstmt->execute();

                    delete pstmt;
                    conn->close();
                    delete conn;
                    break;
                }
            }else{
                cout << "This username doesn't exist." << endl;
            }

        }
    }

    void addLessonS(){
        while(true){
            listStudents();
            cout << endl << "Enter an username that u want to add class for this student(Back:b): ";
            cin >> userName;

            if(userName=="b"){
                break;
            }

            if(checkUsername()){
                if(chooseLesson()){
                    Connection *conn = db.dbConnection();
                    string saveSLesson = "INSERT INTO mm_lesson_student(fk_lesson, fk_student) VALUES(?, ?);";
                    PreparedStatement *pstmt = conn->prepareStatement(saveSLesson);

                    pstmt->setInt(1, lessonId);
                    pstmt->setInt(2, deleteStudentID);

                    pstmt->execute();

                    delete pstmt;
                    conn->close();
                    delete conn;
                    break;
                }
            }else{
                cout << "This username doesn't exist." << endl;
            }

        }
    }

    void showStudentInfo(){
        while(true){
            listStudents();
            cout << "Enter username that u want to see(Back:b): ";
            cin >> userName;
            if(userName == "b"){
                break;
            }

            if(checkUsername()){

                Connection *conn = db.dbConnection();
                string checkClass = "SELECT tbl_class.name as ClassName FROM mm_class_student JOIN tbl_class ON tbl_class.id = mm_class_student.fk_class WHERE mm_class_student.fk_student = ?;";
                PreparedStatement *pstmt = conn->prepareStatement(checkClass);
                pstmt->setInt(1, deleteStudentID);
                ResultSet *rset = pstmt->executeQuery();
                if(rset->next()){
                    cout << "Class of Student: " << rset->getString("ClassName");
                }
                delete pstmt;
                delete rset;
                cout << endl;

                string checkLesson = "SELECT tbl_lesson.name as LessonName FROM mm_lesson_student JOIN tbl_lesson ON tbl_lesson.id = mm_lesson_student.fk_lesson WHERE mm_lesson_student.fk_student = ?;";
                PreparedStatement *pstmt2 = conn->prepareStatement(checkLesson);
                pstmt2->setInt(1, deleteStudentID);
                ResultSet *rset2 = pstmt2->executeQuery();
                cout << "Lessons: " << endl;
                while(rset2->next()){
                    cout << "\t" << rset2->getString("LessonName");
                    cout << endl;
                }
                delete pstmt2;
                delete rset2;

                conn->close();
                delete conn;
                cout << endl;
                break;

            }else{
                cout << "This username doesn't exist." << endl;
            }

        }
    }
};
