#include <cmath>
#include <cxbqn/debug.hpp>
#include <cxbqn/provides.hpp>

namespace cxbqn::provides {
types::Array *get_provides() {
  CXBQN_DEBUG("provides::get_provides");
  static Array prov(23);

  prov.values[0] = bi_type();
  prov.values[1] = bi_fill();
  prov.values[2] = bi_log();
  prov.values[3] = bi_grouplen();
  prov.values[4] = bi_groupord();
  prov.values[5] = bi_assert();
  prov.values[6] = bi_plus();
  prov.values[7] = bi_minus();
  prov.values[8] = bi_mul();
  prov.values[9] = bi_div();
  prov.values[10] = bi_power();
  prov.values[11] = bi_floor();
  prov.values[12] = bi_eq();
  prov.values[13] = bi_le();
  prov.values[14] = bi_fne();
  prov.values[15] = bi_deshape();
  prov.values[16] = bi_pick();
  prov.values[17] = bi_range();
  prov.values[18] = bi_table();
  prov.values[19] = bi_scan();
  prov.values[20] = bi_fillby();
  prov.values[21] = bi_catch();
  
  return &prov;
}

types::Array *get_runtime() {
  CXBQN_DEBUG("provides::get_runtime");
  static Array rt;
  rt.values.resize(60);
  rt.values[0] = bi_plus();
  rt.values[1] = bi_minus();
  rt.values[2] = bi_mul();
  rt.values[3] = bi_div();
  rt.values[4] = bi_power();
  rt.values[5] = bi_root();
  rt.values[6] = bi_floor();
  rt.values[7] = bi_ceil();
  rt.values[8] = bi_stile();
  rt.values[9] = bi_not();
  rt.values[10] = bi_and();
  rt.values[11] = bi_or();
  rt.values[12] = bi_lt();
  rt.values[13] = bi_gt();
  rt.values[14] = bi_ne();
  rt.values[15] = bi_eq();
  rt.values[16] = bi_le();
  rt.values[17] = bi_ge();
  rt.values[18] = bi_feq();
  rt.values[19] = bi_fne();
  rt.values[20] = bi_ltack();
  rt.values[21] = bi_rtack();
  rt.values[22] = bi_deshape();
  rt.values[27] = bi_range();
  rt.values[47] = bi_table();
  rt.values[51] = bi_scan();
  return &rt;
}

Value *bi_plus() {
  static Plus p;
  return &p;
}
Value *bi_minus() {
  static Minus m;
  return &m;
}
Value *bi_mul() {
  static Mul m;
  return &m;
}
Value *bi_div() {
  static Div d;
  return &d;
}
Value *bi_power() {
  static Power x;
  return &x;
}
Value *bi_root() {
  static Root r;
  return &r;
}
Value *bi_floor() {
  static Floor f;
  return &f;
}
Value *bi_ceil() {
  static Ceil c;
  return &c;
}
Value *bi_stile() {
  static Stile s;
  return &s;
}
Value *bi_not() {
  static Not f;
  return &f;
}
Value *bi_and() {
  static And f;
  return &f;
}
Value *bi_or() {
  static Or f;
  return &f;
}
Value *bi_lt() {
  static LT f;
  return &f;
}
Value *bi_gt() {
  static GT f;
  return &f;
}
Value *bi_ne() {
  static NE f;
  return &f;
}
Value *bi_eq() {
  static EQ f;
  return &f;
}
Value *bi_le() {
  static LE f;
  return &f;
}
Value *bi_ge() {
  static GE f;
  return &f;
}
Value *bi_feq() {
  static FEQ f;
  return &f;
}
Value *bi_fne() {
  static FNE f;
  return &f;
}
Value *bi_ltack() {
  static Ltack lt;
  return &lt;
}
Value *bi_rtack() {
  static Rtack rt;
  return &rt;
}
Value *bi_arraydepth() {
  static ArrayDepth f;
  return &f;
}
Value *bi_type() {
  static Type t;
  return &t;
}
Value *bi_table() {
  static Table t;
  return &t;
}
Value *bi_fill() {
  static Fill v;
  return &v;
}
Value *bi_log() {
  static Log v;
  return &v;
}
Value *bi_assert() {
  static Assert v;
  return &v;
}
Value *bi_range() {
  static Range v;
  return &v;
}
Value *bi_pick() {
  static Pick v;
  return &v;
}
Value *bi_shape() {
  static Shape v;
  return &v;
}
Value *bi_deshape() {
  static Deshape v;
  return &v;
}
Value* bi_scan() {
  static Scan v;
  return &v;
}
Value* bi_grouplen() {
  static GroupLen g;
  return &g;
}
Value *bi_groupord() {
  static GroupOrd g;
  return &g;
}
Value *bi_fillby() {
  static FillBy fb;
  return &fb;
}
Value *bi_catch() {
  static Catch c;
  return &c;
}

} // namespace cxbqn::provides
