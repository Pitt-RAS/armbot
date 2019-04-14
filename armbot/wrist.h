#ifndef WRIST_H
#define WRIST_H

// look at the flicka da wrist

class Wrist
{
public:
    Wrist();
    ~Wrist();

    void attach(int, int);
    void poll();

private:
    int clk;
    int data;
};

#endif /* WRIST_H */
