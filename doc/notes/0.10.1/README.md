
```console
$ uname -a
Darwin WE40281 19.6.0 Darwin Kernel Version 19.6.0: Thu Sep 16 20:58:47 PDT 2021; root:xnu-6153.141.40.1~1/RELEASE_X86_64 x86_64
$ time ../build/BQN -e 2+2

real	0m0.047s
user	0m0.038s
sys	0m0.007s
```

```console
$ uname -a
Linux hpz400 5.3.18-lp152.87-default #1 SMP Sun Aug 8 21:53:57 UTC 2021 (44d702a) x86_64 x86_64 x86_64 GNU/Linux
# Build RelWithDebInfo, no deepchecks
$ perf record ./BQN -e 2+2
  18.63%  BQN      libc-2.26.so         [.] _int_malloc
  11.91%  BQN      [unknown]            [k] 0xffffffffba600ae7
   9.36%  BQN      libc-2.26.so         [.] malloc
   6.60%  BQN      BQN                  [.] cxbqn::vm::vm
   5.73%  BQN      libstdc++.so.6.0.29  [.] __dynamic_cast
   2.91%  BQN      [unknown]            [k] 0xffffffffba600163
   2.82%  BQN      BQN                  [.] cxbqn::rt_native::r0::Before::call
   2.51%  BQN      libc-2.26.so         [.] __memmove_sse2_unaligned_erms
   2.26%  BQN      libstdc++.so.6.0.29  [.] __cxxabiv1::__si_class_type_info::__do_dyncast
   2.24%  BQN      libc-2.26.so         [.] __strcmp_sse2_unaligned
   2.11%  BQN      libc-2.26.so         [.] _int_free
   2.10%  BQN      BQN                  [.] cxbqn::types::BlockInst::call
   1.82%  BQN      BQN                  [.] cxbqn::provides::Mul::call
   1.41%  BQN      BQN                  [.] std::vector<cxbqn::types::Value*, std::allocator<cxbqn::types::Value*> >::_M_default_append
   1.41%  BQN      BQN                  [.] cxbqn::types::Fork::call
   1.41%  BQN      BQN                  [.] cxbqn::vm::instructions::varo
   1.41%  BQN      BQN                  [.] std::vector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >
   1.40%  BQN      BQN                  [.] cxbqn::rt_native::r0::After::call
   1.39%  BQN      libc-2.26.so         [.] cfree@GLIBC_2.2.5
   1.23%  BQN      libstdc++.so.6.0.29  [.] __cxxabiv1::__vmi_class_type_info::__do_dyncast
   1.12%  BQN      BQN                  [.] cxbqn::provides::eq_recursive
   1.11%  BQN      BQN                  [.] cxbqn::types::Number::t
   1.08%  BQN      BQN                  [.] cxbqn::provides::Plus::call
   0.81%  BQN      BQN                  [.] cxbqn::provides::Minus::call
   0.71%  BQN      BQN                  [.] cxbqn::provides::FNE::call
   0.71%  BQN      BQN                  [.] cxbqn::vm::instructions::md1c
   0.71%  BQN      libc-2.26.so         [.] tcache_put
   0.71%  BQN      BQN                  [.] cxbqn::provides::Scan::call
   0.71%  BQN      BQN                  [.] std::vector<cxbqn::types::Value*, std::allocator<cxbqn::types::Value*> >::operator=
   0.71%  BQN      libc-2.26.so         [.] __memset_sse2_unaligned_erms
   0.71%  BQN      BQN                  [.] operator new@plt
   0.71%  BQN      BQN                  [.] cxbqn::types::Array::Array
   0.71%  BQN      BQN                  [.] cxbqn::provides::Pick::call
   0.70%  BQN      BQN                  [.] cxbqn::rt_native::r0::Fold::call
   0.70%  BQN      BQN                  [.] cxbqn::rt_native::r0::SelfSwap::call
```
