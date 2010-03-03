#ifndef COMMITTEE_H
#define COMMITTEE_H

class Committee
{
public:
    Committee();
    int getId(void) { return 0; }
    static Committee *load(int id) { (void) id; return 0; }
};

#endif // COMMITTEE_H
