
#include "controller/setupcontroller.h"

SetupController::SetupController() { }
SetupController::~SetupController() { }

int SetupController::install() {
    SetupView setup;
    return setup.exec();
}

bool SetupController::error(const char *text) {
    QMessageBox box;
    box.setText(text);
    box.exec();
    return false;
}

/**
 * Load the data from a file given the file name.
 */
bool SetupController::loadData(QString filename) {
    ifstream myfile(filename.toStdString().c_str());

    if (!myfile.is_open()) {
        return error("Unable to open file.");
    }

    bool ret(parseFile(myfile));
    myfile.close();

    // clear out any units added to the db and any members added to the db
    // as a result of the unit load
    if(!ret) {
        UnitModel::removeAll();
        MemberModel::removeAll("is_coordinator=0");
    }

    return ret;
}

/**
 * Parse a file with unit data.
 */
bool SetupController::parseFile(ifstream &myfile) {
    string userInfo;
    int unitNo(0);
    string address = "";
    int noOfRooms(0);
    string tenantSurname = "";

    if (!myfile.is_open()) {
        return error("Unable to open file.");
    }

    // main parse
    for(bool on_first_line(true); !myfile.eof(); on_first_line = false) {
        locale loc; // For digit checking
        string information = ""; // Hold the next piece of info
        getline (myfile, userInfo); // Get next line
        int whichInfo = 0;

        if(0 == userInfo.size()) {
            if(on_first_line) {
                return error(
                    "The file was empty; please specify a nonempty file "
                    "for loading the units."
                );
            }
            break;
        }

        // Keeps track of which information we're parsing out
        for (unsigned int i = 0; i <= userInfo.size(); i++) {

            if ((i != userInfo.size()) && (userInfo.substr(i,1) != ",")) {

                // If were checking for digits and we don't see a digit
                if(((whichInfo == 0) || (whichInfo == 2))
                && !isdigit(userInfo[i], loc)) {
                    return error("Error parsing: Invalid number entered");
                }

                // Else, we have valid info so far
                information += userInfo.at(i);
                continue;
            }

            switch (whichInfo) {

                case 0:
                    if (information == "") {
                        return error("Error parsing: No unit number given");
                    }
                    unitNo = atoi(information.c_str());
                    break;

                case 1:
                    if (information == "") {
                        return error("Error parsing: No address given");
                    }
                    address = information;
                    break;

                case 2:
                    if (information == "") {
                        return error("Error parsing: No rooms given");
                    }

                    noOfRooms = atoi(information.c_str());
                    if ((noOfRooms == 0) || (noOfRooms > 3)) {
                        return error(
                            "Error parsing: Invalid number of rooms! "
                            "(valid numbers: 1, 2, or 3)"
                        );
                    }
                    break;

                case 3:
                    tenantSurname = information;
                    break;
            }
            whichInfo++;
            information = "";
        }

        /*cout << "address: " << address
             << "; rooms: " << noOfRooms
             << "; number: " << unitNo
             << "; surname: " << tenantSurname
             << endl;*/

        UnitModel *unit(UnitModel::findById(unitNo));
        if(0 == unit) {
            unit = UnitModel::create(
                QString(address.c_str()),
                noOfRooms,
                unitNo
            );
        }

        // unexpected error
        if(0 == unit) {
            stringstream ss;
            ss << "Unable to create unit " << unitNo << " at address "
               << address << ".";
            return error(ss.str().c_str());
        }

        if(!tenantSurname.empty()) {
            MemberModel::createIncomplete(
                QString(tenantSurname.c_str()), unit
            );
        }
    }

    return true;
}
