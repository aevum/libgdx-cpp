
#ifndef GDXCPP_INPUT_PROCESSOR_H
#define GDXCPP_INPUT_PROCESSOR_H

namespace gdx_cpp {
  
class InputProcessor {
public:
  virtual bool keyDown (int keycode) = 0;
  virtual bool keyUp (int keycode) = 0;
  virtual bool keyTyped (char character) = 0;
  virtual bool touchDown (int x, int y, int pointer, int button) = 0;
  virtual bool touchUp (int x, int y, int pointer, int button) = 0;
  virtual bool touchDragged (int x, int y, int pointer) = 0;
  virtual bool touchMoved (int x, int y) = 0;
  virtual bool scrolled (int amount) = 0;
};

}

#endif //GDXCPP_INPUT_PROCESSOR_H