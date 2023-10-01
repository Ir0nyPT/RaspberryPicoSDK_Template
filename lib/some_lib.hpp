
#include <cstdint>
#include <iostream>

class some_lib final {
public:
  some_lib(int value);
  ~some_lib();

  int Get_value();
  void Set_value(int value);

private:
  int value_{0};
};
