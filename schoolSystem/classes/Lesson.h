class Lesson{
private:
    string name;
    Database db;
public:
    Lesson(){

    }
    ~Lesson(){

    }
    void setName(string name){
        this->name = name;
    }
    string getName(){
        return name;
    }

    void lessonOptions(){
        while(true){
            string input;
            cout << "Add Lesson(al), List Lessons(ll), Remove Lesson(rl), Back(b)" << endl;
            cin >> input;

            if(input == "b"){
                break;
            }

            if(input == "al"){
                addLessons();
            }

            if(input == "ll"){
                listLessons();
            }

            if(input == "rl"){
                removeLesson();
            }
        }

    }

    void addLessons(){

        while(true){
            cout << "Enter lesson name that u want to add (Back:b): ";
            cin >> name;

            if(name == "b"){
                break;
            }

            bool checkName = false;
            Connection *conn = db.dbConnection();

            string listQuery = "SELECT name FROM tbl_lesson;";
            Statement *stmt = conn->createStatement();

            ResultSet *rset = stmt->executeQuery(listQuery);
            while(rset->next()){
                if(name == rset->getString("name")){
                    checkName = true;
                    break;
                }
            }

            delete stmt;
            delete rset;
            conn->close();
            delete conn;

            if(checkName){
                cout << "You have already this lesson name on your database." << endl;
            }else{
                Connection *conn = db.dbConnection();

                string addQuery = "INSERT INTO tbl_lesson (name) VALUE (?);";
                PreparedStatement *pstmt = conn->prepareStatement(addQuery);
                pstmt->setString(1, name);

                pstmt->execute();

                delete pstmt;
                conn->close();
                delete conn;
                break;
            }
        }
    }

    void listLessons(){
        cout << "*****List of Lessons*****" << endl;
        Connection *conn = db.dbConnection();

        string listQuery = "SELECT name FROM tbl_lesson;";
        Statement *stmt = conn->createStatement();

        ResultSet *rset = stmt->executeQuery(listQuery);
        while(rset->next()){
            cout << "\t" << rset->getString("name") << endl;
        }

        delete stmt;
        delete rset;
        conn->close();
        delete conn;
    }

    void removeLesson(){
        while(true){
            cout << "Enter name of lesson that u want to remove (Back:b): ";
            cin >> name;

            if(name == "b"){
                break;
            }

            bool checkName = false;
            Connection *conn = db.dbConnection();

            string listQuery = "SELECT name FROM tbl_lesson;";
            Statement *stmt = conn->createStatement();

            ResultSet *rset = stmt->executeQuery(listQuery);
            while(rset->next()){
                if(name == rset->getString("name")){
                    checkName = true;
                    break;
                }
            }

            delete stmt;
            delete rset;
            conn->close();
            delete conn;


            if(checkName){
                Connection *conn = db.dbConnection();

                string deleteQuery = "DELETE FROM tbl_lesson WHERE name=?;";
                PreparedStatement *pstmt = conn->prepareStatement(deleteQuery);
                pstmt->setString(1, name);

                pstmt->execute();
                delete pstmt;
                conn->close();
                delete conn;
                break;
            }else{
                cout << "There isn't any lesson with this name." << endl;
            }
        }
    }

};
