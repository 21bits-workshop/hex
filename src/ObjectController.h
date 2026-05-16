#ifndef OBJECT_CONTROLLER_H
#define OBJECT_CONTROLLER_H

class ObjectController {
public:
    virtual ~ObjectController() = default;
    virtual void update() {}
};

#endif // OBJECT_CONTROLLER_H
