#include "include.h"

int main()
{
    cout << "*****SCHOOL SYSTEM*****" << endl;
    Database db;
    Connection *conn = db.dbConnection();


    mainLoop();



    conn->close();
    delete conn;
    return 0;
}
