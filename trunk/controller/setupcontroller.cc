
#include <iostream>
#include <QString>
#include <fstream>
#include <string>
#include <locale>
#include <QMessageBox>

#include "setupcontroller.h"

SetupController::SetupController()
{
}

SetupController::~SetupController(){
}

int SetupController::addCoordinator() {
    return 0;
}

int SetupController::loadData(QString filename) {
        QMessageBox msgBox;
        string userInfo;
        int unitNo;
        string address = "";
        int noOfRooms;
        string tenantSurname = "";
        ifstream myfile(filename.toStdString().c_str());

        if (myfile.is_open()) {
                while(!myfile.eof()) {
                        locale loc;                     // For digit checking
                        string information = "";        // Hold the next piece of info
                        getline (myfile, userInfo);             // Get next line
                        int whichInfo = 0;                      // Keeps track of which information were parsing out
                        for (unsigned int i = 0; i <= userInfo.size(); i++) {
                                if ((i == userInfo.size()) || (userInfo.substr(i,1) == ",")) {
                                        switch (whichInfo) {
                                                case 0: if (information == "") {
                                                                msgBox.setText("Error parsing: No unit number given");
                                                                msgBox.exec();
                                                                return 0;
                                                        }
                                                        unitNo = atoi(information.c_str());
                                                        break;

                                                case 1:  if (information == "") {
                                                                msgBox.setText("Error parsing: No address given");
                                                                msgBox.exec();
                                                                return 0;
                                                        }
                                                        address = information;
                                                        break;

                                                case 2:  if (information == "") {
                                                                msgBox.setText("Error parsing: No rooms given");
                                                                msgBox.exec();
                                                                return 0;
                                                        }

                                                        noOfRooms = atoi(information.c_str());
                                                        if ((noOfRooms == 0) || (noOfRooms > 3)) {
                                                                msgBox.setText("Error parsing: Invalid number of rooms! (1, 2, or 3)");
                                                                msgBox.exec();
                                                                return 0;
                                                        }
                                                        break;

                                                case 3: tenantSurname = information;
                                                        break;
                                        }
                                        whichInfo++;
                                        information = "";
                                }
                                else {
                                        if ((whichInfo == 0) || (whichInfo == 2)) {             // If were checking for digits
                                                if (!isdigit(userInfo[i], loc)) {               // If its not a digit
                                                        msgBox.setText("Error parsing: Invalid number entered");
                                                        msgBox.exec();
                                                        return 0;
                                                }
                                        }
                                        information += userInfo.at(i);                          // Else, we have valid info so far
                                }
                        }

                        // KEEP TRACK OF THEM IN A LIST??
                        cout << unitNo << "," << address << "," << noOfRooms << "," << tenantSurname << endl;
                }
                myfile.close();
        }

        else {
                cout << "Unable to open file";
        }

    return 0;
}