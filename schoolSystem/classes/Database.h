class Database{
public:
    Database(){

    }
    ~Database(){

    }

    Connection* dbConnection(){
        try{
            mysql::MySQL_Driver *driver = mysql::get_mysql_driver_instance();
            Connection *conn = driver->connect("localhost", "root", "20055002mM!M");
            conn->setSchema("schoolSystem");
            //cout << "Connection successful" << endl;
            return conn;
        }catch(SQLException &e){
            cerr << "Error Code: " << e.getErrorCode() << ", Error Message: " << e.what() << endl;
            return nullptr;
        }
    }
};
