namespace cxbqn::types {

// default impl, worst case scenario.
template<typename T> bool is(Value* v) {
  return !(nullptr == dynamic_cast<T*>(v));
}

}
