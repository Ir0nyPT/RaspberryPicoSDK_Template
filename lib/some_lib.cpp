#include "some_lib.hpp"

some_lib::some_lib(int value) : value_{value} {
  std::cout << __func__ << ": Constructor running" << std::endl;
}

some_lib::~some_lib() {
  std::cout << __func__ << ": Desctructor running" << std::endl;
}

void some_lib::Set_value(int value) { value_ = value; }

int some_lib::Get_value() { return value_; }
