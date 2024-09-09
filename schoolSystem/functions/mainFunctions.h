void mainLoop(){
    string whoAmI;

    while(true){
        cout << "Who are you logging in as?" << endl;
        cout << "Like Admin(a), like Teacher(t), like Student(s), Exit(e)" << endl;
        cin >> whoAmI;

        if(whoAmI == "a"){
            Admin admin;
            string adminName = admin.login();
            cout << endl << "Welcome "<< adminName << endl;
            admin.adminOptions();
        }

        if(whoAmI == "t"){
            TeacherL teacher;
            teacher.login();
        }

        if(whoAmI == "s"){
            StudentL student;
            student.login();
        }

        if(whoAmI == "e"){
            exit(1);
            break;
        }

        cout << endl;
    }
}
