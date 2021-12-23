#include <cxbqn/rt_native.hpp>

namespace cxbqn::rt_native::r0 {

// let select = (x,w) => {
//  let s=x.sh, k=s.length, f=x.fill, t=w.sh, c=1;
//  if (k!==1) {for(let i=1;i<k;i++)c*=s[i];t=t.concat(s.slice(1));}
//  let r=Array(w.length*c);
//  let j=0;
//  w.forEach(i=>{for(let k=0;k<c;k++)r[j++]=x[i*c+k];});
//  return arr(r,t,f);
//}
O<Value> Select::call(u8 nargs, Args &args) {
  const auto x = dyncast<Array>(args[1]), w = dyncast<Array>(args[2]);
  const auto &xsh = x->shape;
  auto retsh = w->shape;
  const auto xrank = xsh.size();
  uz c = 1;

  if (1 != xrank) {
    for (int i = 0; i < xrank; i++)
      c *= xsh[i];
    std::copy(xsh.begin() + 1, xsh.end(), std::back_inserter(retsh));
  }

  auto ret = CXBQN_NEW(Array, w->N() * c);
  ret->shape = std::move(retsh);

  uz j = 0;
  for (const auto e : w->values) {
    const auto i = static_cast<uz>(dyncast<Number>(e)->v);
    for (int k = 0; k < c; k++) {
      const auto xv = dyncast<Number>(x->values[i * c + k])->v;
      ret->values[j++] = CXBQN_NEW(Number, xv);
    }
  }

  return ret;
}

} // namespace cxbqn::rt_native::r0
