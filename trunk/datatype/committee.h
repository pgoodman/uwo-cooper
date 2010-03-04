#ifndef COMMITTEE_H
#define COMMITTEE_H

#include "permission.h"

class Committee
{

public:
    Committee();
    int getId(void) { return 0; }
    //static Committee *load(int id) { (void) id; return 0; }
   /* Permission getPermissions(Member member);
    void addMember(Member member);
    void removeMember(Member member);
   // void addTask(Task task);
   // void removeTask(Task task);

private:
    //name: std::string
    bool can_delete;
    Member chair;
    Member secretary;
    Permission chair_perms;
    Permission member_perms;
    */
};

#endif // COMMITTEE_H
