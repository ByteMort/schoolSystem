#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

using namespace sql;

#include "classes/Database.h"
#include "classes/Lesson.h"
#include "classes/Class.h"
#include "classes/Student.h"
#include "classes/Teacher.h"
#include "classes/TeacherL.h"
#include "classes/StudentL.h"
#include "classes/Admin.h"


#include "functions/mainFunctions.h"
