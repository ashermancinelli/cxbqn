#pragma once

namespace cxbqn::value_types {

template<ValueType VT>
struct Value {
  uint64_t decode() {
    return VT::decode();
  }
};

struct Scalar {

};

struct BlockInst {

};

struct Array {

};

struct Function {

};

struct Train2 {

};

struct Train3 {

};

}
