#include <cmath>
#include <cxbqn/comp_utils.hpp>
#include <cxbqn/sys.hpp>
#include <cxbqn/debug.hpp>

namespace cxbqn::provides {
O<types::Array> get_provides() {
  CXBQN_DEBUG("provides::get_provides");
  auto prov = make_shared<Array>(23);

  prov->values[0] = bi_Type();
  prov->values[1] = bi_Fill();
  prov->values[2] = bi_Log();
  prov->values[3] = bi_GroupLen();
  prov->values[4] = bi_GroupOrd();
  prov->values[5] = bi_Assert();
  prov->values[6] = bi_Plus();
  prov->values[7] = bi_Minus();
  prov->values[8] = bi_Mul();
  prov->values[9] = bi_Div();
  prov->values[10] = bi_Power();
  prov->values[11] = bi_Floor();
  prov->values[12] = bi_EQ();
  prov->values[13] = bi_LE();
  prov->values[14] = bi_FNE();
  prov->values[15] = bi_Deshape();
  prov->values[16] = bi_Pick();
  prov->values[17] = bi_Range();
  prov->values[18] = bi_Table();
  prov->values[19] = bi_Scan();
  prov->values[20] = bi_FillBy();
  prov->values[21] = bi_Valence();
  prov->values[22] = bi_Catch();

  return prov;
}

static O<Array> rt = nullptr;
O<Array> get_runtime_cached() {
  if (nullptr != rt)
    return rt;
  rt = get_runtime();
  return get_runtime_cached();
}

O<Array> get_runtime() {
  CXBQN_DEBUG("provides::get_runtime");

  const auto provide = provides::get_provides()->values;
  static CompileParams p(
#include <cxbqn/__/compiled_runtime>
  );
  auto ret = vm::run(p.bc, p.consts.to_arr(), p.blk_defs, p.bodies);
  auto runtime_ret = std::dynamic_pointer_cast<Array>(ret.v);

  return std::dynamic_pointer_cast<Array>(runtime_ret->values[0]);
}

static O<Array> rtsp = nullptr;
O<Array> get_runtime_setprims_cached() {
  if (nullptr != rtsp)
    return rtsp;
  rtsp = get_runtime_setprims();
  return get_runtime_setprims_cached();
}

O<Array> get_runtime_setprims() {
  CXBQN_DEBUG("provides::get_runtime_setprims");

  // First we run the runtime to get the original output
  const auto provide = provides::get_provides()->values;
  static CompileParams p(
#include <cxbqn/__/compiled_runtime>
  );
  auto ret = vm::run(p.bc, p.consts.to_arr(), p.blk_defs, p.bodies);

  // Decompose the result to get the array with just the runtime
  auto runtime_ret = std::dynamic_pointer_cast<Array>(ret.v);
  auto runtime_raw = std::dynamic_pointer_cast<Array>(runtime_ret->values[0]);

  auto setprims = runtime_ret->values[1];

  // Inform the two latter builtins of the runtime so they can refer to it
  auto decompose = make_shared<Decompose>(runtime_raw);
  auto primind = make_shared<PrimInd>(runtime_raw);

  setprims->call(1, {setprims, O<Array>(new Array({decompose, primind})), bi_Nothing()});

  return runtime_raw;
}

O<Array> get_runtime_bionly() {
  CXBQN_DEBUG("provides::get_runtime_bionly");
  auto rt = make_shared<Array>(60);

  rt->values[0] = bi_Plus();
  rt->values[1] = bi_Minus();
  rt->values[2] = bi_Mul();
  rt->values[3] = bi_Div();
  rt->values[4] = bi_Power();
  rt->values[5] = bi_Root();
  rt->values[6] = bi_Floor();
  rt->values[7] = bi_Ceil();
  rt->values[8] = bi_Stile();
  rt->values[9] = bi_Not();
  rt->values[10] = bi_And();
  rt->values[11] = bi_Or();
  rt->values[12] = bi_LT();
  rt->values[13] = bi_GT();
  rt->values[14] = bi_NE();
  rt->values[15] = bi_EQ();
  rt->values[16] = bi_LE();
  rt->values[17] = bi_GE();
  rt->values[18] = bi_FEQ();
  rt->values[19] = bi_FNE();
  rt->values[20] = bi_Ltack();
  rt->values[21] = bi_Rtack();
  rt->values[22] = bi_Deshape();
  rt->values[27] = bi_Range();
  rt->values[36] = bi_Pick();
  rt->values[47] = bi_Table();
  rt->values[51] = bi_Scan();

  return rt;
}

#define BI_DEF(T)                                                              \
  O<Value> bi_##T() {                                                          \
    static T v;                                                                \
    return std::shared_ptr<T>(&v, [](T *) {});                                 \
  }
BI_DEF(Plus);
BI_DEF(Minus);
BI_DEF(Mul);
BI_DEF(Div);
BI_DEF(Power);
BI_DEF(Root);
BI_DEF(Floor);
BI_DEF(Ceil);
BI_DEF(Stile);
BI_DEF(Not);
BI_DEF(And);
BI_DEF(Or);
BI_DEF(LT);
BI_DEF(GT);
BI_DEF(NE);
BI_DEF(EQ);
BI_DEF(LE);
BI_DEF(GE);
BI_DEF(FEQ);
BI_DEF(FNE);
BI_DEF(Ltack);
BI_DEF(Rtack);
BI_DEF(ArrayDepth);
BI_DEF(Type);
BI_DEF(Table);
BI_DEF(Fill);
BI_DEF(Log);
BI_DEF(Assert);
BI_DEF(Range);
BI_DEF(Pick);
BI_DEF(Shape);
BI_DEF(Deshape);
BI_DEF(Scan);
BI_DEF(GroupLen);
BI_DEF(GroupOrd);
BI_DEF(FillBy);
BI_DEF(Valence);
BI_DEF(Catch);
// BI_DEF(Decompose);
// BI_DEF(PrimInd);

} // namespace cxbqn::provides
