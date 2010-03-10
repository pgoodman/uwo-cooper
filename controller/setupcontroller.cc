
#include "controller/setupcontroller.h"

SetupController::SetupController() { }
SetupController::~SetupController() { }

int SetupController::install() {
    SetupView setup;
    return setup.exec();
}

/**
 * Load the data from a file given the file name.
 */
bool SetupController::loadData(QString filename) {
    QMessageBox msgBox;
    ifstream myfile(filename.toStdString().c_str());

    if (!myfile.is_open()) {
        msgBox.setText("Unable to open file.");
        msgBox.exec();
        return false;
    }

    bool ret(parseFile(myfile, msgBox));
    myfile.close();
    return ret;
}

/**
 * Parse a file with unit data.
 */
bool SetupController::parseFile(ifstream &myfile, QMessageBox &msgBox) {
    QString qAddress;
    string userInfo;
    int unitNo(0);
    string address = "";
    int noOfRooms(0);
    string tenantSurname = "";

    if (!myfile.is_open()) {
        msgBox.setText("Unable to open file.");
        msgBox.exec();
        return false;
    }

    while(!myfile.eof()) {
        locale loc; // For digit checking
        string information = ""; // Hold the next piece of info
        getline (myfile, userInfo); // Get next line
        int whichInfo = 0;
        if(userInfo.size()!=0){
            // Keeps track of which information we're parsing out
            for (unsigned int i = 0; i <= userInfo.size(); i++) {

                if ((i != userInfo.size()) && (userInfo.substr(i,1) != ",")) {

                    // If were checking for digits and we don't see a digit
                    if(((whichInfo == 0) || (whichInfo == 2))
                    && !isdigit(userInfo[i], loc)) {
                        msgBox.setText("Error parsing: Invalid number entered");
                        msgBox.exec();
                        return false;
                    }

                    // Else, we have valid info so far
                    information += userInfo.at(i);
                    continue;
                }

                switch (whichInfo) {

                    case 0:
                        if (information == "") {
                            msgBox.setText("Error parsing: No unit number given");
                            msgBox.exec();
                            return false;
                        }
                        unitNo = atoi(information.c_str());
                        break;

                    case 1:
                        if (information == "") {
                            msgBox.setText("Error parsing: No address given");
                            msgBox.exec();
                            return false;
                        }
                        address = information;
                        break;

                    case 2:
                        if (information == "") {
                            msgBox.setText("Error parsing: No rooms given");
                            msgBox.exec();
                            return false;
                        }

                        noOfRooms = atoi(information.c_str());
                        if ((noOfRooms == 0) || (noOfRooms > 3)) {
                            msgBox.setText(
                                "Error parsing: Invalid number of rooms! "
                                "(1, 2, or 3)"
                            );
                            msgBox.exec();
                            return false;
                        }
                        break;

                    case 3:
                        tenantSurname = information;
                        break;
                }
                qAddress = QString(address.c_str());
                whichInfo++;
                information = "";
            }

            UnitModel::create(qAddress, noOfRooms, unitNo);
        }
    }
    return true;
}
