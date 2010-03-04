#include "committee.h"
#include "permission.h"
#include "member.h"
#include <string>
#include <list>

/*
string name;
//name std::string[1]
bool can_delete;
Member chair;
Member secretary;
Permission chair_perms;
Permission member_perms;
list<Member> memberList;
*/

Committee::Committee() {
}

/*
Committee::Committee(string committeeName, Member committeeChair, Member committeeSecretary)
{
        name = committeeName;
        chair = committeeChair;
        secretary = committeeSecretary;
        memberList = new list<Member>;
        // Initiate chair perms and member perms
}
*/

int getId(void) {
    // UNSURE WHAT THIS IS RETURNING EXACTLY
    return 0;
}

static Committee *load(int id) {
    (void) id; return 0;
}

/*
Permission Committee::getPermissions(Member member) {
    if (member.getID() == chair.getID()) {
        return chair_perms;
    }
    else
        return member_perms;
}

void Committee::addMember(Member member) {
    //Add a member to the committees member list.
    // NOTE: USING LIST AS EXAMPLE, DONT KNOW HOW WERE GOING TO STORE THIS!!!

    memberList.insert(member);
}

void Committee::removeMember(Member member) {
    // Remove a member from a committees member list.
    //NOTE: USING LIST AS EXAMPLE, DONT KNOW HOW WERE GOING TO STORE THIS!!!

    memberList.remove(member);
}

//void Committee::addTask(Task task);
//void Committee::removeTask(Task task);
*/
