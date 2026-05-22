/* ObjectController.h
 * ObjectController is an abstract class from which all the specific controllers
 * which handle AI routines and user input will inherit.
 */
#ifndef OBJECT_CONTROLLER_H
#define OBJECT_CONTROLLER_H

class ObjectController {
public:
  virtual ~ObjectController() = default;
  virtual void update() {
  } // Update is to be run once per controller, per game loop.
};

#endif // OBJECT_CONTROLLER_H
