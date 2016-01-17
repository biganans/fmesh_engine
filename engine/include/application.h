#ifndef _APPLICATION_H_
#define _APPLICATION_H_

class application
{
private:
    application();
    application(const application&);
    application& operator=(const application&);
public:
    application(int argc, const char **argv);
    int run();
    virtual ~application();
};


#endif
