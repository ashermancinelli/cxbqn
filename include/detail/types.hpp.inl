namespace cxbqn::types {

// default impl, worst case scenario.
template<typename T> bool is(Value* v) {
  return !(nullptr == dynamic_cast<T*>(v));
}

template<typename OS>
OS &operator<<(OS& os, Number* n) {
  return os << "N";
}

template<typename OS>
OS &operator<<(OS& os, Function* f) {
  return os << "F";
}

template<typename OS>
OS &operator<<(OS& os, Builtin* bi) {
  return os << "BI";
}

template<typename OS, typename T>
OS &operator<<(OS& os, Array* ar) {
  os << "A";
  return os;
}

template<typename OS, typename ValueType>
OS &operator<<(OS& os, ValueType* v) {
  os << "V";
  return os;
}

}
