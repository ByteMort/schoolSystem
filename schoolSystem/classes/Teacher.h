class Teacher{
private:
    string name, lastName, userName, pass, country, city, postCode, street, className, lessonName;
    int classId, lessonId, lastTId, deleteTeacherID;
    Database db;
public:
    Teacher(){

    }
    ~Teacher(){

    }

    void teacherOptions(){
        while(true){
            string input;
            cout << "Add Teacher(at), Add Class for Teacher(ac), Add Lesson for Teacher(al), List Teacher(lt), Show Teacher Info(si), Remove Teacher(rt), Back(b)" << endl;
            cin >> input;

            if(input == "b"){
                break;
            }

            if(input == "at"){
                addTeacher();
            }

            if(input == "lt"){
                listTeachers();
            }

            if(input == "si"){
                showTeacherInfo();
            }

            if(input == "ac"){
                addClassT();
            }

            if(input == "al"){
                addLessonT();
            }

            if(input == "rt"){
                removeTeacher();
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
        string selectQuery = "SELECT id, userName FROM tbl_teacher;";
        Statement *stmt = conn->createStatement();

        ResultSet *rset = stmt->executeQuery(selectQuery);

        while(rset->next()){
            if(rset->getString("userName") == userName){
                checkUserName = true;
                deleteTeacherID = rset->getInt("id");
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

            cout << "Enter the teacher's class (Back:b): ";
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

            cout << "Enter the teacher's lesson (Back:b): ";
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

    void saveTeacher(){

        Connection *conn = db.dbConnection();

        string saveQuery = "INSERT INTO tbl_teacher(name, lastName, userName, pass, country, city, postCode, street) VALUES(?, ?, ?, ?, ?, ?, ?, ?);";
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

        string lastTID = "SELECT MAX(id) as last_teacher_id FROM tbl_teacher;";
        Statement *stmt = conn->createStatement();

        ResultSet *rset = stmt->executeQuery(lastTID);

        if(rset->next()){
            lastTId = rset->getInt("last_teacher_id");
        }

        delete stmt;
        delete rset;
        conn->close();
        delete conn;

    }

    void addTeacher(){
        while(true){
            cin.ignore();
            if(!getInput("Enter the teacher's name (Back:b): ", name)){
                break;
            }

            if(!getInput("Enter the teacher's lastname (Back:b): ", lastName)){
                break;
            }

            while(true){
                if(!getInput("Enter the teacher's username (Back:b): ", userName)){
                break;
                }else{
                    if(checkUsername()){
                        cout << "This username is already exist in database." << endl;
                    }else{
                        break;
                    }
                }
            }

            if(!getInput("Enter the teacher's password (Back:b): ", pass)){
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

            saveTeacher();
            cout << "Successful!" << endl;
            break;

        }
    }

    void listTeachers(){
        cout << endl << "*****List of Teachers*****" << endl;

        Connection *conn = db.dbConnection();

        string selectQuery = "SELECT name, lastName, userName, pass, country, city, postCode, street FROM tbl_teacher;";
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

    void removeTeacher(){
        while(true){
            listTeachers();
            cout << "Enter the teacher's username that u want to remove (Back:b): ";
            cin >> userName;

            if(userName == "b"){
                break;
            }

            if(checkUsername()){
                Connection *conn = db.dbConnection();

                string deleteQuery = "DELETE FROM mm_class_teacher WHERE fk_teacher=?;";
                PreparedStatement *pstmt = conn->prepareStatement(deleteQuery);
                pstmt->setInt(1, deleteTeacherID);
                pstmt->execute();

                string deleteQuery2 = "DELETE FROM mm_lesson_teacher WHERE fk_teacher=?;";
                PreparedStatement *pstmt2 = conn->prepareStatement(deleteQuery2);
                pstmt2->setInt(1, deleteTeacherID);
                pstmt2->execute();

                string deleteQuery3 = "DELETE FROM tbl_teacher WHERE userName=?;";

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

    void addClassT(){
        while(true){
            listTeachers();
            cout << endl << "Enter an username that u want to add class for this teacher(Back:b): ";
            cin >> userName;

            if(userName=="b"){
                break;
            }

            if(checkUsername()){
                if(chooseClass()){
                    Connection *conn = db.dbConnection();
                    string saveTClass = "INSERT INTO mm_class_teacher(fk_class, fk_teacher, startDate) VALUES(?, ?, ?);";
                    PreparedStatement *pstmt = conn->prepareStatement(saveTClass);

                    pstmt->setInt(1, classId);
                    pstmt->setInt(2, deleteTeacherID);
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

    void addLessonT(){
        while(true){
            listTeachers();
            cout << endl << "Enter an username that u want to add class for this teacher(Back:b): ";
            cin >> userName;

            if(userName=="b"){
                break;
            }

            if(checkUsername()){
                if(chooseLesson()){
                    Connection *conn = db.dbConnection();
                    string saveTLesson = "INSERT INTO mm_lesson_teacher(fk_lesson, fk_teacher) VALUES(?, ?);";
                    PreparedStatement *pstmt = conn->prepareStatement(saveTLesson);

                    pstmt->setInt(1, lessonId);
                    pstmt->setInt(2, deleteTeacherID);

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

    void showTeacherInfo(){
        while(true){
            listTeachers();
            cout << "Enter username that u want to see(Back:b): ";
            cin >> userName;
            if(userName == "b"){
                break;
            }

            if(checkUsername()){

                Connection *conn = db.dbConnection();
                string checkClass = "SELECT tbl_class.name as ClassName FROM mm_class_teacher JOIN tbl_class ON tbl_class.id = mm_class_teacher.fk_class WHERE mm_class_teacher.fk_teacher = ?;";
                PreparedStatement *pstmt = conn->prepareStatement(checkClass);
                pstmt->setInt(1, deleteTeacherID);
                ResultSet *rset = pstmt->executeQuery();
                cout << "Classes of Teacher: " << endl;
                while(rset->next()){
                    cout << "\t" << rset->getString("ClassName");
                    cout << endl;
                }
                delete pstmt;
                delete rset;
                cout << endl;

                string checkLesson = "SELECT tbl_lesson.name as LessonName FROM mm_lesson_teacher JOIN tbl_lesson ON tbl_lesson.id = mm_lesson_teacher.fk_lesson WHERE mm_lesson_teacher.fk_teacher = ?;";
                PreparedStatement *pstmt2 = conn->prepareStatement(checkLesson);
                pstmt2->setInt(1, deleteTeacherID);
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
