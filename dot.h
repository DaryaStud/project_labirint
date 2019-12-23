#ifndef DOT_H
#define DOT_H

class dot {
    bool right, dawn, top, left;
public:
    dot() {
        right = 0;
        dawn = 0;
        top = 0;
        left = 0;
    }
    void ungo_dawn() {
        dawn = 0;
    }
    void ungo_left() {
        left = 0;
    }
    void ungo_top() {
        top = 0;
    }
    void ungo_right() {
        right = 0;
    }
    void go_dawn() {
        dawn = 1;
    }
    void go_left() {
        left = 1;
    }
    void go_top() {
        top = 1;
    }
    void go_right() {
        right = 1;
    }
    bool get_right() {
        return right;
    }
    bool get_top() {
        return top;
    }
    bool get_left() {
        return left;
    }
    bool get_dawn() {
        return dawn;
    }
};

#endif // DOT_H


