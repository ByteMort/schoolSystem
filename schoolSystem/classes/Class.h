class Class{
private:
    string name;
    Database db;
public:
    Class(){

    }
    ~Class(){

    }
    void setName(string name){
        this->name = name;
    }
    string getName(){
        return name;
    }

    void classOptions(){
        while(true){
            string input;
            cout << "Add Class(ac), List Classes(la), Remove Class(ra), Back(b)" << endl;
            cin >> input;

            if(input == "b"){
                break;
            }

            if(input == "ac"){
                addClasses();
            }

            if(input == "la"){
                listClasses();
            }

            if(input == "ra"){
                removeClass();
            }
        }

    }

    void addClasses(){

        while(true){
            cout << "Enter class name that u want to add (Back:b): ";
            cin >> name;

            if(name == "b"){
                break;
            }

            bool checkName = false;
            Connection *conn = db.dbConnection();

            string listQuery = "SELECT name FROM tbl_class;";
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
                cout << "You have already this class name on your database." << endl;
            }else{
                Connection *conn = db.dbConnection();

                string addQuery = "INSERT INTO tbl_class (name) VALUE (?);";
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

    void listClasses(){
        cout << "*****List of Classes*****" << endl;
        Connection *conn = db.dbConnection();

        string listQuery = "SELECT name FROM tbl_class;";
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

    void removeClass(){
        while(true){
            cout << "Enter name of class that u want to remove (Back:b): ";
            cin >> name;

            if(name == "b"){
                break;
            }

            bool checkName = false;
            Connection *conn = db.dbConnection();

            string listQuery = "SELECT name FROM tbl_class;";
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

                string deleteQuery = "DELETE FROM tbl_class WHERE name=?;";
                PreparedStatement *pstmt = conn->prepareStatement(deleteQuery);
                pstmt->setString(1, name);

                pstmt->execute();
                delete pstmt;
                conn->close();
                delete conn;
                break;
            }else{
                cout << "There isn't any class with this name." << endl;
            }
        }
    }

};
