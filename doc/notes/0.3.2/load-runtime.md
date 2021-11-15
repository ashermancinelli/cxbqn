```
--------------------------------------------------------------------------------
Command:            ./test/test_runtime
Massif arguments:   --threshold=0.01 --xtree-memory=allocs
ms_print arguments: ../doc/notes/0.3.2/load-runtime.massif
--------------------------------------------------------------------------------


    MB
6.327^                                                                       #
     |                                              @@::::@@::@::::@:::::::::#
     |                                     ::@::::::@ ::::@ : @::: @:::: : ::#
     |                                     : @:: : :@ ::::@ : @::: @:::: : ::#
     |                                     : @:: : :@ ::::@ : @::: @:::: : ::#
     |     ::::: ::::::::@@:::::::::::::@::: @:: : :@ ::::@ : @::: @:::: : ::#
     | ::@@:: : :: : ::: @ :: :: :::: : @: : @:: : :@ ::::@ : @::: @:::: : ::#
     | ::@ :: : :: : ::: @ :: :: :::: : @: : @:: : :@ ::::@ : @::: @:::: : ::#
     | ::@ :: : :: : ::: @ :: :: :::: : @: : @:: : :@ ::::@ : @::: @:::: : ::#
     | ::@ :: : :: : ::: @ :: :: :::: : @: : @:: : :@ ::::@ : @::: @:::: : ::#
     | ::@ :: : :: : ::: @ :: :: :::: : @: : @:: : :@ ::::@ : @::: @:::: : ::#
     | ::@ :: : :: : ::: @ :: :: :::: : @: : @:: : :@ ::::@ : @::: @:::: : ::#
     | ::@ :: : :: : ::: @ :: :: :::: : @: : @:: : :@ ::::@ : @::: @:::: : ::#
     | ::@ :: : :: : ::: @ :: :: :::: : @: : @:: : :@ ::::@ : @::: @:::: : ::#
     | ::@ :: : :: : ::: @ :: :: :::: : @: : @:: : :@ ::::@ : @::: @:::: : ::#
     | ::@ :: : :: : ::: @ :: :: :::: : @: : @:: : :@ ::::@ : @::: @:::: : ::#
     | ::@ :: : :: : ::: @ :: :: :::: : @: : @:: : :@ ::::@ : @::: @:::: : ::#
     | ::@ :: : :: : ::: @ :: :: :::: : @: : @:: : :@ ::::@ : @::: @:::: : ::#
     | ::@ :: : :: : ::: @ :: :: :::: : @: : @:: : :@ ::::@ : @::: @:::: : ::#
     | ::@ :: : :: : ::: @ :: :: :::: : @: : @:: : :@ ::::@ : @::: @:::: : ::#
   0 +----------------------------------------------------------------------->Gi
     0                                                                   424.4

Number of snapshots: 54
 Detailed snapshots: [3, 13, 23, 26, 31, 36, 38, 42, 52, 53 (peak)]

--------------------------------------------------------------------------------
  n        time(i)         total(B)   useful-heap(B) extra-heap(B)    stacks(B)
--------------------------------------------------------------------------------
  0              0                0                0             0            0
  1  8,939,276,558        4,883,176        4,690,843       192,333            0
  2 15,547,222,310        4,897,896        4,704,953       192,943            0
  3 24,292,105,166        4,971,144        4,773,654       197,490            0
96.03% (4,773,654B) (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
->67.24% (3,342,744B) 0x4BEF44: spdlog::details::thread_pool::thread_pool(unsigned long, unsigned long, std::function<void ()>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->67.24% (3,342,744B) 0x4BF6B9: spdlog::details::thread_pool::thread_pool(unsigned long, unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->67.24% (3,342,744B) 0x46E0DC: std::shared_ptr<spdlog::async_logger> spdlog::async_factory_impl<(spdlog::async_overflow_policy)0>::create<spdlog::sinks::basic_file_sink<std::mutex>, char const (&) [16]>(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, char const (&) [16]) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->67.24% (3,342,744B) 0x46C15C: cxbqn::vm::run(std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::BlockDef, std::allocator<cxbqn::types::BlockDef> >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       ->67.24% (3,342,744B) 0x43DFC2: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|         ->67.24% (3,342,744B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|           ->67.24% (3,342,744B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|             
->06.72% (334,080B) 0x443A6F: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->06.72% (334,080B) in 66+ places, all below ms_print's threshold (01.00%)
| 
->03.92% (194,880B) 0x443A21: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->03.92% (194,880B) in 64+ places, all below ms_print's threshold (01.00%)
| 
->01.87% (92,820B) 0x432F04: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.87% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.87% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     
->01.87% (92,820B) 0x43DF4C: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.87% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.87% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     
->01.87% (92,820B) 0x48334F: cxbqn::types::Scope::root_scope(std::vector<cxbqn::types::Block, std::allocator<cxbqn::types::Block> >, std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.87% (92,820B) 0x46CBCD: cxbqn::vm::run(std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::BlockDef, std::allocator<cxbqn::types::BlockDef> >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.87% (92,820B) 0x43DFC2: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->01.87% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       ->01.87% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|         
->01.68% (83,520B) 0x443ACF: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.68% (83,520B) in 54+ places, all below ms_print's threshold (01.00%)
| 
->01.46% (72,704B) 0x50FE189: _GLOBAL__sub_I_eh_alloc.cc (in /share/gcc/11.2.0/lib64/libstdc++.so.6.0.29)
| ->01.46% (72,704B) 0x400FAB9: call_init.part.0 (in /lib64/ld-2.26.so)
|   ->01.46% (72,704B) 0x400FBC5: _dl_init (in /lib64/ld-2.26.so)
|     ->01.46% (72,704B) 0x4000ED9: ??? (in /lib64/ld-2.26.so)
|       
->01.12% (55,680B) 0x443C3A: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.12% (55,680B) in 45+ places, all below ms_print's threshold (01.00%)
| 
->08.28% (411,586B) in 57+ places, all below ms_print's threshold (01.00%)

--------------------------------------------------------------------------------
  n        time(i)         total(B)   useful-heap(B) extra-heap(B)    stacks(B)
--------------------------------------------------------------------------------
  4 35,847,497,241        4,976,144        4,777,402       198,742            0
  5 44,098,890,915        4,977,968        4,779,178       198,790            0
  6 55,975,729,029        4,981,896        4,782,821       199,075            0
  7 65,226,906,147        4,974,944        4,775,248       199,696            0
  8 75,626,497,422        5,087,576        4,877,110       210,466            0
  9 84,216,902,487        5,113,664        4,902,009       211,655            0
 10 96,905,514,081        5,148,960        4,936,936       212,024            0
 11 104,835,896,165        5,094,000        4,882,206       211,794            0
 12 113,559,299,451        5,141,184        4,929,296       211,888            0
 13 125,465,539,435        5,223,808        5,013,500       210,308            0
95.97% (5,013,500B) (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
->63.99% (3,342,744B) 0x4BEF44: spdlog::details::thread_pool::thread_pool(unsigned long, unsigned long, std::function<void ()>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->63.99% (3,342,744B) 0x4BF6B9: spdlog::details::thread_pool::thread_pool(unsigned long, unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->63.99% (3,342,744B) 0x46E0DC: std::shared_ptr<spdlog::async_logger> spdlog::async_factory_impl<(spdlog::async_overflow_policy)0>::create<spdlog::sinks::basic_file_sink<std::mutex>, char const (&) [16]>(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, char const (&) [16]) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->63.99% (3,342,744B) 0x46C15C: cxbqn::vm::run(std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::BlockDef, std::allocator<cxbqn::types::BlockDef> >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       ->63.99% (3,342,744B) 0x43DFC2: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|         ->63.99% (3,342,744B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|           ->63.99% (3,342,744B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|             
->06.40% (334,080B) 0x443A6F: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->06.40% (334,080B) in 66+ places, all below ms_print's threshold (01.00%)
| 
->03.73% (194,880B) 0x443A21: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->03.73% (194,880B) in 63+ places, all below ms_print's threshold (01.00%)
| 
->02.19% (114,435B) 0x46D661: fmt::v8::basic_memory_buffer<char, 500ul, std::allocator<char> >::grow(unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->02.19% (114,435B) 0x46EAC8: fmt::v8::appender fmt::v8::detail::copy_str_noinline<char, char const*, fmt::v8::appender>(char const*, char const*, fmt::v8::appender) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->02.19% (114,435B) 0x47C989: void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   | ->02.19% (114,435B) 0x47D1D9: decltype (({parm
|   |   ->02.19% (114,435B) 0x47D51A: void fmt::v8::detail::value<fmt::v8::basic_format_context<fmt::v8::appender, char> >::format_custom_arg<cxbqn::types::Value, fmt::v8::formatter<cxbqn::types::Value, char, void> >(void const*, fmt::v8::basic_format_parse_context<char, fmt::v8::detail::error_handler>&, fmt::v8::basic_format_context<fmt::v8::appender, char>&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |     ->02.19% (114,435B) 0x47C95B: void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       ->02.19% (114,435B) 0x484BC1: void fmt::v8::detail::value<fmt::v8::basic_format_context<fmt::v8::appender, char> >::format_custom_arg<std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, fmt::v8::formatter<std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, char, void> >(void const*, fmt::v8::basic_format_parse_context<char, fmt::v8::detail::error_handler>&, fmt::v8::basic_format_context<fmt::v8::appender, char>&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       | ->02.19% (114,435B) 0x47C4D5: char const* fmt::v8::detail::parse_replacement_field<char, void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref)::format_handler&>(char const*, char const*, void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref)::format_handler&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |   ->02.19% (114,435B) 0x47C897: void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |     ->02.19% (114,435B) 0x4849AD: void fmt::v8::detail::value<fmt::v8::basic_format_context<fmt::v8::appender, char> >::format_custom_arg<cxbqn::types::Scope, fmt::v8::formatter<cxbqn::types::Scope, char, void> >(void const*, fmt::v8::basic_format_parse_context<char, fmt::v8::detail::error_handler>&, fmt::v8::basic_format_context<fmt::v8::appender, char>&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |       ->02.19% (114,435B) 0x47C95B: void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |         ->02.19% (114,435B) 0x4C557A: fmt::v8::vformat[abi:cxx11](fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<fmt::v8::appender, char> >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           ->02.19% (114,435B) 0x481E53: cxbqn::types::Scope::get_nth_parent(unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | ->02.19% (114,435B) 0x497F6D: cxbqn::vm::instructions::varo(std::span<int const, 18446744073709551615ul>, unsigned long&, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | | ->02.19% (114,435B) 0x46B968: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   ->02.19% (114,435B) 0x49FB15: cxbqn::types::BlockInst::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | ->02.19% (114,435B) 0x49DFC0: cxbqn::types::Md1Deferred::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | ->02.19% (114,435B) 0x49D57D: cxbqn::types::Fork::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | ->02.19% (114,435B) 0x48BA35: cxbqn::provides::Valence::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | | ->02.19% (114,435B) 0x49E4E8: cxbqn::types::Md2Deferred::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | |   ->02.19% (114,435B) 0x49D8E3: cxbqn::types::Fork::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | |   | ->02.19% (114,435B) 0x493BD4: cxbqn::vm::instructions::fn2o(std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | |   | | ->02.19% (114,435B) 0x46BB0B: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | |   | |   ->02.19% (114,435B) 0x49FB15: cxbqn::types::BlockInst::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | |   | |     ->02.19% (114,435B) 0x49E4E8: cxbqn::types::Md2Deferred::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | |   | |       ->02.19% (114,435B) 0x49640A: cxbqn::vm::instructions::fn1c(std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | |   | |       | ->02.19% (114,435B) 0x46BB53: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | |   | |       |   ->02.19% (114,435B) 0x49FB15: cxbqn::types::BlockInst::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | |   | |       |     ->02.19% (114,435B) 0x49640A: cxbqn::vm::instructions::fn1c(std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | |   | |       |     | ->02.19% (114,435B) 0x46BB53: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | |   | |       |     |   
|   |       |           | |   | | | |   | |       |     ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | | | |   | |       |     
|   |       |           | |   | | | |   | |       ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | | | |   | |       
|   |       |           | |   | | | |   | ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | | | |   | 
|   |       |           | |   | | | |   ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | | | |   
|   |       |           | |   | | | ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | | | 
|   |       |           | |   | | ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | | 
|   |       |           | |   | ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | 
|   |       |           | |   ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   
|   |       |           | ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | 
|   |       |           ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           
|   |       ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       
|   ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   
->01.82% (94,848B) 0x441991: cxbqn::types::Value::Value() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.82% (94,848B) in 7+ places, all below ms_print's threshold (01.00%)
| 
->01.78% (92,820B) 0x432F04: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.78% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.78% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     
->01.78% (92,820B) 0x43DF4C: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.78% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.78% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     
->01.78% (92,820B) 0x48334F: cxbqn::types::Scope::root_scope(std::vector<cxbqn::types::Block, std::allocator<cxbqn::types::Block> >, std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.78% (92,820B) 0x46CBCD: cxbqn::vm::run(std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::BlockDef, std::allocator<cxbqn::types::BlockDef> >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.78% (92,820B) 0x43DFC2: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->01.78% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       ->01.78% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|         
->01.60% (83,520B) 0x443ACF: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.60% (83,520B) in 53+ places, all below ms_print's threshold (01.00%)
| 
->01.39% (72,704B) 0x50FE189: _GLOBAL__sub_I_eh_alloc.cc (in /share/gcc/11.2.0/lib64/libstdc++.so.6.0.29)
| ->01.39% (72,704B) 0x400FAB9: call_init.part.0 (in /lib64/ld-2.26.so)
|   ->01.39% (72,704B) 0x400FBC5: _dl_init (in /lib64/ld-2.26.so)
|     ->01.39% (72,704B) 0x4000ED9: ??? (in /lib64/ld-2.26.so)
|       
->01.07% (55,680B) 0x443C3A: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.07% (55,680B) in 45+ places, all below ms_print's threshold (01.00%)
| 
->08.46% (442,149B) in 56+ places, all below ms_print's threshold (01.00%)

--------------------------------------------------------------------------------
  n        time(i)         total(B)   useful-heap(B) extra-heap(B)    stacks(B)
--------------------------------------------------------------------------------
 14 134,716,889,535        5,089,064        4,878,451       210,613            0
 15 142,646,646,189        5,106,536        4,895,748       210,788            0
 16 153,219,658,000        5,141,008        4,929,410       211,598            0
 17 162,471,010,270        5,141,320        4,930,293       211,027            0
 18 173,044,015,074        5,147,880        4,935,880       212,000            0
 19 180,973,765,750        5,147,896        4,935,921       211,975            0
 20 188,903,493,107        5,147,032        4,935,063       211,969            0
 21 196,040,922,028        5,150,008        4,937,719       212,289            0
 22 205,557,488,613        5,181,296        4,968,264       213,032            0
 23 217,453,235,375        5,158,216        4,945,604       212,612            0
95.88% (4,945,604B) (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
->64.80% (3,342,744B) 0x4BEF44: spdlog::details::thread_pool::thread_pool(unsigned long, unsigned long, std::function<void ()>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->64.80% (3,342,744B) 0x4BF6B9: spdlog::details::thread_pool::thread_pool(unsigned long, unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->64.80% (3,342,744B) 0x46E0DC: std::shared_ptr<spdlog::async_logger> spdlog::async_factory_impl<(spdlog::async_overflow_policy)0>::create<spdlog::sinks::basic_file_sink<std::mutex>, char const (&) [16]>(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, char const (&) [16]) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->64.80% (3,342,744B) 0x46C15C: cxbqn::vm::run(std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::BlockDef, std::allocator<cxbqn::types::BlockDef> >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       ->64.80% (3,342,744B) 0x43DFC2: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|         ->64.80% (3,342,744B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|           ->64.80% (3,342,744B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|             
->06.48% (334,080B) 0x443A6F: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->06.48% (334,080B) in 66+ places, all below ms_print's threshold (01.00%)
| 
->03.78% (194,880B) 0x443A21: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->03.78% (194,880B) in 63+ places, all below ms_print's threshold (01.00%)
| 
->01.96% (100,992B) 0x441991: cxbqn::types::Value::Value() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.96% (100,992B) in 7+ places, all below ms_print's threshold (01.00%)
| 
->01.80% (92,820B) 0x432F04: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.80% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.80% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     
->01.80% (92,820B) 0x43DF4C: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.80% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.80% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     
->01.80% (92,820B) 0x48334F: cxbqn::types::Scope::root_scope(std::vector<cxbqn::types::Block, std::allocator<cxbqn::types::Block> >, std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.80% (92,820B) 0x46CBCD: cxbqn::vm::run(std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::BlockDef, std::allocator<cxbqn::types::BlockDef> >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.80% (92,820B) 0x43DFC2: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->01.80% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       ->01.80% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|         
->01.62% (83,520B) 0x443ACF: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.62% (83,520B) in 53+ places, all below ms_print's threshold (01.00%)
| 
->01.41% (72,704B) 0x50FE189: _GLOBAL__sub_I_eh_alloc.cc (in /share/gcc/11.2.0/lib64/libstdc++.so.6.0.29)
| ->01.41% (72,704B) 0x400FAB9: call_init.part.0 (in /lib64/ld-2.26.so)
|   ->01.41% (72,704B) 0x400FBC5: _dl_init (in /lib64/ld-2.26.so)
|     ->01.41% (72,704B) 0x4000ED9: ??? (in /lib64/ld-2.26.so)
|       
->01.08% (55,680B) 0x443C3A: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.08% (55,680B) in 45+ places, all below ms_print's threshold (01.00%)
| 
->09.35% (482,544B) in 57+ places, all below ms_print's threshold (01.00%)

--------------------------------------------------------------------------------
  n        time(i)         total(B)   useful-heap(B) extra-heap(B)    stacks(B)
--------------------------------------------------------------------------------
 24 226,969,814,328        5,171,696        4,960,143       211,553            0
 25 239,795,694,371        6,193,304        5,816,378       376,926            0
 26 248,425,959,791        6,270,360        5,890,824       379,536            0
93.95% (5,890,824B) (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
->53.31% (3,342,744B) 0x4BEF44: spdlog::details::thread_pool::thread_pool(unsigned long, unsigned long, std::function<void ()>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->53.31% (3,342,744B) 0x4BF6B9: spdlog::details::thread_pool::thread_pool(unsigned long, unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->53.31% (3,342,744B) 0x46E0DC: std::shared_ptr<spdlog::async_logger> spdlog::async_factory_impl<(spdlog::async_overflow_policy)0>::create<spdlog::sinks::basic_file_sink<std::mutex>, char const (&) [16]>(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, char const (&) [16]) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->53.31% (3,342,744B) 0x46C15C: cxbqn::vm::run(std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::BlockDef, std::allocator<cxbqn::types::BlockDef> >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       ->53.31% (3,342,744B) 0x43DFC2: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|         ->53.31% (3,342,744B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|           ->53.31% (3,342,744B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|             
->10.66% (668,160B) 0x443A6F: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.14% (71,424B) 0x4459E9: std::__shared_ptr<cxbqn::types::Array, (__gnu_cxx::_Lock_policy)2>::__shared_ptr<std::allocator<cxbqn::types::Array>, char32_t const (&) [32]>(std::_Sp_alloc_shared_tag<std::allocator<cxbqn::types::Array> >, char32_t const (&) [32]) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| | ->01.14% (71,424B) in 24+ places, all below ms_print's threshold (01.00%)
| | 
| ->09.52% (596,736B) in 99+ places, all below ms_print's threshold (01.00%)
| 
->06.22% (389,760B) 0x443A21: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->06.22% (389,760B) in 93+ places, all below ms_print's threshold (01.00%)
| 
->02.96% (185,640B) 0x48334F: cxbqn::types::Scope::root_scope(std::vector<cxbqn::types::Block, std::allocator<cxbqn::types::Block> >, std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->02.96% (185,640B) 0x46CBCD: cxbqn::vm::run(std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::BlockDef, std::allocator<cxbqn::types::BlockDef> >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.48% (92,820B) 0x43DFC2: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   | ->01.48% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |   ->01.48% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |     
|   ->01.48% (92,820B) 0x457634: cxbqn::provides::get_runtime() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->01.48% (92,820B) 0x43199C: _DOCTEST_ANON_FUNC_10() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       ->01.48% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|         ->01.48% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|           
->02.66% (167,040B) 0x443ACF: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->02.66% (167,040B) in 72+ places, all below ms_print's threshold (01.00%)
| 
->02.29% (143,520B) 0x441991: cxbqn::types::Value::Value() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->02.29% (143,520B) in 7+ places, all below ms_print's threshold (01.00%)
| 
->01.78% (111,360B) 0x443C3A: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.78% (111,360B) in 61+ places, all below ms_print's threshold (01.00%)
| 
->01.48% (92,820B) 0x4575B7: cxbqn::provides::get_runtime() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.48% (92,820B) 0x43199C: _DOCTEST_ANON_FUNC_10() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.48% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->01.48% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       
->01.48% (92,820B) 0x4577D9: cxbqn::provides::get_runtime() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.48% (92,820B) 0x43199C: _DOCTEST_ANON_FUNC_10() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.48% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->01.48% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       
->01.16% (72,704B) 0x50FE189: _GLOBAL__sub_I_eh_alloc.cc (in /share/gcc/11.2.0/lib64/libstdc++.so.6.0.29)
| ->01.16% (72,704B) 0x400FAB9: call_init.part.0 (in /lib64/ld-2.26.so)
|   ->01.16% (72,704B) 0x400FBC5: _dl_init (in /lib64/ld-2.26.so)
|     ->01.16% (72,704B) 0x4000ED9: ??? (in /lib64/ld-2.26.so)
|       
->01.07% (66,784B) 0x46584F: std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >::_M_default_append(unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.07% (66,784B) in 4+ places, all below ms_print's threshold (01.00%)
| 
->01.02% (64,176B) 0x49734C: cxbqn::vm::instructions::md2c(std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.02% (64,176B) 0x46B97B: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.02% (64,176B) in 3+ places, all below ms_print's threshold (01.00%)
|   
->07.87% (493,296B) in 52+ places, all below ms_print's threshold (01.00%)

--------------------------------------------------------------------------------
  n        time(i)         total(B)   useful-heap(B) extra-heap(B)    stacks(B)
--------------------------------------------------------------------------------
 27 257,942,540,250        6,257,240        5,874,762       382,478            0
 28 265,079,952,856        6,246,080        5,865,000       381,080            0
 29 274,596,519,634        6,279,504        5,897,375       382,129            0
 30 286,295,475,482        6,276,216        5,893,660       382,556            0
 31 297,012,172,844        6,401,216        6,011,538       389,678            0
93.91% (6,011,538B) (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
->52.22% (3,342,744B) 0x4BEF44: spdlog::details::thread_pool::thread_pool(unsigned long, unsigned long, std::function<void ()>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->52.22% (3,342,744B) 0x4BF6B9: spdlog::details::thread_pool::thread_pool(unsigned long, unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->52.22% (3,342,744B) 0x46E0DC: std::shared_ptr<spdlog::async_logger> spdlog::async_factory_impl<(spdlog::async_overflow_policy)0>::create<spdlog::sinks::basic_file_sink<std::mutex>, char const (&) [16]>(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, char const (&) [16]) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->52.22% (3,342,744B) 0x46C15C: cxbqn::vm::run(std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::BlockDef, std::allocator<cxbqn::types::BlockDef> >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       ->52.22% (3,342,744B) 0x43DFC2: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|         ->52.22% (3,342,744B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|           ->52.22% (3,342,744B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|             
->10.44% (668,160B) 0x443A6F: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.12% (71,424B) 0x4459E9: std::__shared_ptr<cxbqn::types::Array, (__gnu_cxx::_Lock_policy)2>::__shared_ptr<std::allocator<cxbqn::types::Array>, char32_t const (&) [32]>(std::_Sp_alloc_shared_tag<std::allocator<cxbqn::types::Array> >, char32_t const (&) [32]) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| | ->01.12% (71,424B) in 24+ places, all below ms_print's threshold (01.00%)
| | 
| ->09.32% (596,736B) in 99+ places, all below ms_print's threshold (01.00%)
| 
->06.09% (389,760B) 0x443A21: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->06.09% (389,760B) in 93+ places, all below ms_print's threshold (01.00%)
| 
->02.90% (185,640B) 0x48334F: cxbqn::types::Scope::root_scope(std::vector<cxbqn::types::Block, std::allocator<cxbqn::types::Block> >, std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->02.90% (185,640B) 0x46CBCD: cxbqn::vm::run(std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::BlockDef, std::allocator<cxbqn::types::BlockDef> >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.45% (92,820B) 0x43DFC2: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   | ->01.45% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |   ->01.45% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |     
|   ->01.45% (92,820B) 0x457634: cxbqn::provides::get_runtime() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->01.45% (92,820B) 0x43199C: _DOCTEST_ANON_FUNC_10() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       ->01.45% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|         ->01.45% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|           
->02.77% (177,024B) 0x441991: cxbqn::types::Value::Value() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.13% (72,192B) 0x4973C1: cxbqn::vm::instructions::md2c(std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| | ->01.13% (72,192B) 0x46B97B: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| |   ->01.13% (72,192B) in 3+ places, all below ms_print's threshold (01.00%)
| |   
| ->01.64% (104,832B) in 6+ places, all below ms_print's threshold (01.00%)
| 
->02.61% (167,040B) 0x443ACF: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->02.61% (167,040B) in 72+ places, all below ms_print's threshold (01.00%)
| 
->01.74% (111,360B) 0x443C3A: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.74% (111,360B) in 61+ places, all below ms_print's threshold (01.00%)
| 
->01.45% (92,820B) 0x4575B7: cxbqn::provides::get_runtime() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.45% (92,820B) 0x43199C: _DOCTEST_ANON_FUNC_10() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.45% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->01.45% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       
->01.45% (92,820B) 0x4577D9: cxbqn::provides::get_runtime() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.45% (92,820B) 0x43199C: _DOCTEST_ANON_FUNC_10() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.45% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->01.45% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       
->01.32% (84,224B) 0x49734C: cxbqn::vm::instructions::md2c(std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.32% (84,224B) 0x46B97B: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.32% (84,224B) in 3+ places, all below ms_print's threshold (01.00%)
|   
->01.19% (76,290B) 0x46D661: fmt::v8::basic_memory_buffer<char, 500ul, std::allocator<char> >::grow(unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.19% (76,290B) 0x46EAC8: fmt::v8::appender fmt::v8::detail::copy_str_noinline<char, char const*, fmt::v8::appender>(char const*, char const*, fmt::v8::appender) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.19% (76,290B) 0x47C989: void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   | ->01.19% (76,290B) 0x47D1D9: decltype (({parm
|   |   ->01.19% (76,290B) 0x47D51A: void fmt::v8::detail::value<fmt::v8::basic_format_context<fmt::v8::appender, char> >::format_custom_arg<cxbqn::types::Value, fmt::v8::formatter<cxbqn::types::Value, char, void> >(void const*, fmt::v8::basic_format_parse_context<char, fmt::v8::detail::error_handler>&, fmt::v8::basic_format_context<fmt::v8::appender, char>&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |     ->01.19% (76,290B) 0x47C95B: void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       ->01.19% (76,290B) 0x484BC1: void fmt::v8::detail::value<fmt::v8::basic_format_context<fmt::v8::appender, char> >::format_custom_arg<std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, fmt::v8::formatter<std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, char, void> >(void const*, fmt::v8::basic_format_parse_context<char, fmt::v8::detail::error_handler>&, fmt::v8::basic_format_context<fmt::v8::appender, char>&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       | ->01.19% (76,290B) 0x47C4D5: char const* fmt::v8::detail::parse_replacement_field<char, void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref)::format_handler&>(char const*, char const*, void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref)::format_handler&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |   ->01.19% (76,290B) 0x47C897: void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |     ->01.19% (76,290B) 0x4849AD: void fmt::v8::detail::value<fmt::v8::basic_format_context<fmt::v8::appender, char> >::format_custom_arg<cxbqn::types::Scope, fmt::v8::formatter<cxbqn::types::Scope, char, void> >(void const*, fmt::v8::basic_format_parse_context<char, fmt::v8::detail::error_handler>&, fmt::v8::basic_format_context<fmt::v8::appender, char>&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |       ->01.19% (76,290B) 0x47C95B: void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |         ->01.19% (76,290B) 0x4C557A: fmt::v8::vformat[abi:cxx11](fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<fmt::v8::appender, char> >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           ->01.19% (76,290B) 0x481E53: cxbqn::types::Scope::get_nth_parent(unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | ->01.19% (76,290B) 0x497F6D: cxbqn::vm::instructions::varo(std::span<int const, 18446744073709551615ul>, unsigned long&, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | | ->01.19% (76,290B) 0x46B968: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   ->01.19% (76,290B) 0x49FB15: cxbqn::types::BlockInst::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | ->01.19% (76,290B) 0x49487D: cxbqn::vm::instructions::md1c(std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | ->01.19% (76,290B) 0x46BA83: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | |   ->01.19% (76,290B) 0x46CEA5: cxbqn::vm::run(std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::BlockDef, std::allocator<cxbqn::types::BlockDef> >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | |   | ->01.19% (76,290B) 0x457634: cxbqn::provides::get_runtime() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | |   | | ->01.19% (76,290B) 0x43199C: _DOCTEST_ANON_FUNC_10() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | |   | |   ->01.19% (76,290B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | |   | |     ->01.19% (76,290B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | |   | |       
|   |       |           | |   | |   | ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | |   | 
|   |       |           | |   | |   ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | |   
|   |       |           | |   | ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | 
|   |       |           | |   ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   
|   |       |           | ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | 
|   |       |           ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           
|   |       ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       
|   ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   
->01.18% (75,584B) 0x46584F: std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >::_M_default_append(unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.18% (75,584B) in 4+ places, all below ms_print's threshold (01.00%)
| 
->01.14% (72,704B) 0x50FE189: _GLOBAL__sub_I_eh_alloc.cc (in /share/gcc/11.2.0/lib64/libstdc++.so.6.0.29)
| ->01.14% (72,704B) 0x400FAB9: call_init.part.0 (in /lib64/ld-2.26.so)
|   ->01.14% (72,704B) 0x400FBC5: _dl_init (in /lib64/ld-2.26.so)
|     ->01.14% (72,704B) 0x4000ED9: ??? (in /lib64/ld-2.26.so)
|       
->07.43% (475,368B) in 54+ places, all below ms_print's threshold (01.00%)

--------------------------------------------------------------------------------
  n        time(i)         total(B)   useful-heap(B) extra-heap(B)    stacks(B)
--------------------------------------------------------------------------------
 32 307,157,585,479        6,399,944        6,004,530       395,414            0
 33 314,098,233,676        6,391,712        5,996,563       395,149            0
 34 321,038,890,246        6,439,808        6,044,351       395,457            0
 35 327,979,542,525        6,437,960        6,042,766       395,194            0
 36 334,920,204,853        6,425,968        6,030,371       395,597            0
93.84% (6,030,371B) (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
->52.02% (3,342,744B) 0x4BEF44: spdlog::details::thread_pool::thread_pool(unsigned long, unsigned long, std::function<void ()>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->52.02% (3,342,744B) 0x4BF6B9: spdlog::details::thread_pool::thread_pool(unsigned long, unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->52.02% (3,342,744B) 0x46E0DC: std::shared_ptr<spdlog::async_logger> spdlog::async_factory_impl<(spdlog::async_overflow_policy)0>::create<spdlog::sinks::basic_file_sink<std::mutex>, char const (&) [16]>(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, char const (&) [16]) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->52.02% (3,342,744B) 0x46C15C: cxbqn::vm::run(std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::BlockDef, std::allocator<cxbqn::types::BlockDef> >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       ->52.02% (3,342,744B) 0x43DFC2: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|         ->52.02% (3,342,744B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|           ->52.02% (3,342,744B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|             
->10.40% (668,160B) 0x443A6F: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.11% (71,424B) 0x4459E9: std::__shared_ptr<cxbqn::types::Array, (__gnu_cxx::_Lock_policy)2>::__shared_ptr<std::allocator<cxbqn::types::Array>, char32_t const (&) [32]>(std::_Sp_alloc_shared_tag<std::allocator<cxbqn::types::Array> >, char32_t const (&) [32]) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| | ->01.11% (71,424B) in 24+ places, all below ms_print's threshold (01.00%)
| | 
| ->09.29% (596,736B) in 99+ places, all below ms_print's threshold (01.00%)
| 
->06.07% (389,760B) 0x443A21: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->06.07% (389,760B) in 93+ places, all below ms_print's threshold (01.00%)
| 
->03.00% (192,960B) 0x441991: cxbqn::types::Value::Value() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.23% (79,296B) 0x4973C1: cxbqn::vm::instructions::md2c(std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| | ->01.23% (79,296B) 0x46B97B: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| |   ->01.23% (79,296B) in 3+ places, all below ms_print's threshold (01.00%)
| |   
| ->01.77% (113,664B) in 6+ places, all below ms_print's threshold (01.00%)
| 
->02.89% (185,640B) 0x48334F: cxbqn::types::Scope::root_scope(std::vector<cxbqn::types::Block, std::allocator<cxbqn::types::Block> >, std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->02.89% (185,640B) 0x46CBCD: cxbqn::vm::run(std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::BlockDef, std::allocator<cxbqn::types::BlockDef> >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.44% (92,820B) 0x43DFC2: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   | ->01.44% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |   ->01.44% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |     
|   ->01.44% (92,820B) 0x457634: cxbqn::provides::get_runtime() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->01.44% (92,820B) 0x43199C: _DOCTEST_ANON_FUNC_10() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       ->01.44% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|         ->01.44% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|           
->02.60% (167,040B) 0x443ACF: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->02.60% (167,040B) in 72+ places, all below ms_print's threshold (01.00%)
| 
->01.73% (111,360B) 0x443C3A: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.73% (111,360B) in 61+ places, all below ms_print's threshold (01.00%)
| 
->01.44% (92,820B) 0x4575B7: cxbqn::provides::get_runtime() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.44% (92,820B) 0x43199C: _DOCTEST_ANON_FUNC_10() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.44% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->01.44% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       
->01.44% (92,820B) 0x4577D9: cxbqn::provides::get_runtime() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.44% (92,820B) 0x43199C: _DOCTEST_ANON_FUNC_10() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.44% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->01.44% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       
->01.44% (92,512B) 0x49734C: cxbqn::vm::instructions::md2c(std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.44% (92,512B) 0x46B97B: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.44% (92,512B) in 3+ places, all below ms_print's threshold (01.00%)
|   
->01.25% (80,592B) 0x46584F: std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >::_M_default_append(unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.25% (80,592B) in 4+ places, all below ms_print's threshold (01.00%)
| 
->01.13% (72,704B) 0x50FE189: _GLOBAL__sub_I_eh_alloc.cc (in /share/gcc/11.2.0/lib64/libstdc++.so.6.0.29)
| ->01.13% (72,704B) 0x400FAB9: call_init.part.0 (in /lib64/ld-2.26.so)
|   ->01.13% (72,704B) 0x400FBC5: _dl_init (in /lib64/ld-2.26.so)
|     ->01.13% (72,704B) 0x4000ED9: ??? (in /lib64/ld-2.26.so)
|       
->08.42% (541,259B) in 56+ places, all below ms_print's threshold (01.00%)

--------------------------------------------------------------------------------
  n        time(i)         total(B)   useful-heap(B) extra-heap(B)    stacks(B)
--------------------------------------------------------------------------------
 37 341,860,973,632        6,424,056        6,028,723       395,333            0
 38 354,779,843,569        6,532,296        6,137,704       394,592            0
93.96% (6,137,704B) (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
->51.17% (3,342,744B) 0x4BEF44: spdlog::details::thread_pool::thread_pool(unsigned long, unsigned long, std::function<void ()>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->51.17% (3,342,744B) 0x4BF6B9: spdlog::details::thread_pool::thread_pool(unsigned long, unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->51.17% (3,342,744B) 0x46E0DC: std::shared_ptr<spdlog::async_logger> spdlog::async_factory_impl<(spdlog::async_overflow_policy)0>::create<spdlog::sinks::basic_file_sink<std::mutex>, char const (&) [16]>(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, char const (&) [16]) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->51.17% (3,342,744B) 0x46C15C: cxbqn::vm::run(std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::BlockDef, std::allocator<cxbqn::types::BlockDef> >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       ->51.17% (3,342,744B) 0x43DFC2: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|         ->51.17% (3,342,744B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|           ->51.17% (3,342,744B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|             
->10.23% (668,160B) 0x443A6F: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.09% (71,424B) 0x4459E9: std::__shared_ptr<cxbqn::types::Array, (__gnu_cxx::_Lock_policy)2>::__shared_ptr<std::allocator<cxbqn::types::Array>, char32_t const (&) [32]>(std::_Sp_alloc_shared_tag<std::allocator<cxbqn::types::Array> >, char32_t const (&) [32]) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| | ->01.09% (71,424B) in 24+ places, all below ms_print's threshold (01.00%)
| | 
| ->09.14% (596,736B) in 99+ places, all below ms_print's threshold (01.00%)
| 
->05.97% (389,760B) 0x443A21: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->05.97% (389,760B) in 93+ places, all below ms_print's threshold (01.00%)
| 
->02.98% (194,400B) 0x441991: cxbqn::types::Value::Value() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.24% (80,832B) 0x4973C1: cxbqn::vm::instructions::md2c(std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| | ->01.24% (80,832B) 0x46B97B: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| |   ->01.24% (80,832B) in 3+ places, all below ms_print's threshold (01.00%)
| |   
| ->01.74% (113,568B) in 6+ places, all below ms_print's threshold (01.00%)
| 
->02.84% (185,640B) 0x48334F: cxbqn::types::Scope::root_scope(std::vector<cxbqn::types::Block, std::allocator<cxbqn::types::Block> >, std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->02.84% (185,640B) 0x46CBCD: cxbqn::vm::run(std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::BlockDef, std::allocator<cxbqn::types::BlockDef> >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.42% (92,820B) 0x43DFC2: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   | ->01.42% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |   ->01.42% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |     
|   ->01.42% (92,820B) 0x457634: cxbqn::provides::get_runtime() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->01.42% (92,820B) 0x43199C: _DOCTEST_ANON_FUNC_10() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       ->01.42% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|         ->01.42% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|           
->02.56% (167,040B) 0x443ACF: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->02.56% (167,040B) in 72+ places, all below ms_print's threshold (01.00%)
| 
->01.75% (114,435B) 0x46D661: fmt::v8::basic_memory_buffer<char, 500ul, std::allocator<char> >::grow(unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.75% (114,435B) 0x46EAC8: fmt::v8::appender fmt::v8::detail::copy_str_noinline<char, char const*, fmt::v8::appender>(char const*, char const*, fmt::v8::appender) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.75% (114,435B) 0x47C989: void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   | ->01.75% (114,435B) 0x47D1D9: decltype (({parm
|   |   ->01.75% (114,435B) 0x47D51A: void fmt::v8::detail::value<fmt::v8::basic_format_context<fmt::v8::appender, char> >::format_custom_arg<cxbqn::types::Value, fmt::v8::formatter<cxbqn::types::Value, char, void> >(void const*, fmt::v8::basic_format_parse_context<char, fmt::v8::detail::error_handler>&, fmt::v8::basic_format_context<fmt::v8::appender, char>&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |     ->01.75% (114,435B) 0x47C95B: void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       ->01.75% (114,435B) 0x484BC1: void fmt::v8::detail::value<fmt::v8::basic_format_context<fmt::v8::appender, char> >::format_custom_arg<std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, fmt::v8::formatter<std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, char, void> >(void const*, fmt::v8::basic_format_parse_context<char, fmt::v8::detail::error_handler>&, fmt::v8::basic_format_context<fmt::v8::appender, char>&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       | ->01.75% (114,435B) 0x47C4D5: char const* fmt::v8::detail::parse_replacement_field<char, void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref)::format_handler&>(char const*, char const*, void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref)::format_handler&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |   ->01.75% (114,435B) 0x47C897: void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |     ->01.75% (114,435B) 0x4849AD: void fmt::v8::detail::value<fmt::v8::basic_format_context<fmt::v8::appender, char> >::format_custom_arg<cxbqn::types::Scope, fmt::v8::formatter<cxbqn::types::Scope, char, void> >(void const*, fmt::v8::basic_format_parse_context<char, fmt::v8::detail::error_handler>&, fmt::v8::basic_format_context<fmt::v8::appender, char>&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |       ->01.75% (114,435B) 0x47C95B: void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |         ->01.75% (114,435B) 0x4C557A: fmt::v8::vformat[abi:cxx11](fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<fmt::v8::appender, char> >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           ->01.75% (114,435B) 0x481E53: cxbqn::types::Scope::get_nth_parent(unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | ->01.75% (114,435B) 0x497F6D: cxbqn::vm::instructions::varo(std::span<int const, 18446744073709551615ul>, unsigned long&, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | | ->01.75% (114,435B) 0x46B968: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   ->01.75% (114,435B) 0x49FB15: cxbqn::types::BlockInst::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | ->01.75% (114,435B) 0x49E4E8: cxbqn::types::Md2Deferred::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | ->01.75% (114,435B) 0x48DEEA: cxbqn::provides::Table::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | ->01.75% (114,435B) 0x49DFC0: cxbqn::types::Md1Deferred::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | |   ->01.75% (114,435B) 0x49640A: cxbqn::vm::instructions::fn1c(std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | |     ->01.75% (114,435B) 0x46BB53: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | |       ->01.75% (114,435B) 0x49FB15: cxbqn::types::BlockInst::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | |         ->01.75% (114,435B) 0x493CEB: cxbqn::vm::instructions::fn2o(std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | |         | ->01.75% (114,435B) 0x46BB0B: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | |         |   ->01.75% (114,435B) 0x49FB15: cxbqn::types::BlockInst::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | |         |     ->01.75% (114,435B) 0x49E4E8: cxbqn::types::Md2Deferred::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | |         |       ->01.75% (114,435B) 0x489318: cxbqn::provides::FillBy::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | |         |       | ->01.75% (114,435B) 0x49E4E8: cxbqn::types::Md2Deferred::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | |         |       |   ->01.75% (114,435B) 0x4936F7: cxbqn::vm::instructions::fn2c(std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | |         |       |   | ->01.75% (114,435B) 0x46BB3B: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | |         |       |   |   
|   |       |           | |   | | |         |       |   ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | | |         |       |   
|   |       |           | |   | | |         |       ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | | |         |       
|   |       |           | |   | | |         ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | | |         
|   |       |           | |   | | ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | | 
|   |       |           | |   | ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | 
|   |       |           | |   ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   
|   |       |           | ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | 
|   |       |           ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           
|   |       ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       
|   ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   
->01.70% (111,360B) 0x443C3A: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.70% (111,360B) in 61+ places, all below ms_print's threshold (01.00%)
| 
->01.44% (94,304B) 0x49734C: cxbqn::vm::instructions::md2c(std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.44% (94,304B) 0x46B97B: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.44% (94,304B) in 3+ places, all below ms_print's threshold (01.00%)
|   
->01.42% (92,820B) 0x4575B7: cxbqn::provides::get_runtime() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.42% (92,820B) 0x43199C: _DOCTEST_ANON_FUNC_10() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.42% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->01.42% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       
->01.42% (92,820B) 0x4577D9: cxbqn::provides::get_runtime() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.42% (92,820B) 0x43199C: _DOCTEST_ANON_FUNC_10() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.42% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->01.42% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       
->01.23% (80,672B) 0x46584F: std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >::_M_default_append(unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.23% (80,672B) in 4+ places, all below ms_print's threshold (01.00%)
| 
->01.11% (72,704B) 0x50FE189: _GLOBAL__sub_I_eh_alloc.cc (in /share/gcc/11.2.0/lib64/libstdc++.so.6.0.29)
| ->01.11% (72,704B) 0x400FAB9: call_init.part.0 (in /lib64/ld-2.26.so)
|   ->01.11% (72,704B) 0x400FBC5: _dl_init (in /lib64/ld-2.26.so)
|     ->01.11% (72,704B) 0x4000ED9: ??? (in /lib64/ld-2.26.so)
|       
->08.13% (530,845B) in 56+ places, all below ms_print's threshold (01.00%)

--------------------------------------------------------------------------------
  n        time(i)         total(B)   useful-heap(B) extra-heap(B)    stacks(B)
--------------------------------------------------------------------------------
 39 361,720,520,021        6,416,128        6,021,331       394,797            0
 40 372,131,501,186        6,424,896        6,029,816       395,080            0
 41 379,072,159,390        6,395,832        6,000,789       395,043            0
 42 389,483,140,132        6,502,528        6,103,775       398,753            0
93.87% (6,103,775B) (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
->51.41% (3,342,744B) 0x4BEF44: spdlog::details::thread_pool::thread_pool(unsigned long, unsigned long, std::function<void ()>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->51.41% (3,342,744B) 0x4BF6B9: spdlog::details::thread_pool::thread_pool(unsigned long, unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->51.41% (3,342,744B) 0x46E0DC: std::shared_ptr<spdlog::async_logger> spdlog::async_factory_impl<(spdlog::async_overflow_policy)0>::create<spdlog::sinks::basic_file_sink<std::mutex>, char const (&) [16]>(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, char const (&) [16]) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->51.41% (3,342,744B) 0x46C15C: cxbqn::vm::run(std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::BlockDef, std::allocator<cxbqn::types::BlockDef> >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       ->51.41% (3,342,744B) 0x43DFC2: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|         ->51.41% (3,342,744B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|           ->51.41% (3,342,744B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|             
->10.28% (668,160B) 0x443A6F: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.10% (71,424B) 0x4459E9: std::__shared_ptr<cxbqn::types::Array, (__gnu_cxx::_Lock_policy)2>::__shared_ptr<std::allocator<cxbqn::types::Array>, char32_t const (&) [32]>(std::_Sp_alloc_shared_tag<std::allocator<cxbqn::types::Array> >, char32_t const (&) [32]) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| | ->01.10% (71,424B) in 24+ places, all below ms_print's threshold (01.00%)
| | 
| ->09.18% (596,736B) in 99+ places, all below ms_print's threshold (01.00%)
| 
->05.99% (389,760B) 0x443A21: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->05.99% (389,760B) in 93+ places, all below ms_print's threshold (01.00%)
| 
->03.02% (196,128B) 0x441991: cxbqn::types::Value::Value() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.24% (80,928B) 0x4973C1: cxbqn::vm::instructions::md2c(std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| | ->01.24% (80,928B) 0x46B97B: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| |   ->01.24% (80,928B) in 3+ places, all below ms_print's threshold (01.00%)
| |   
| ->01.77% (115,200B) in 6+ places, all below ms_print's threshold (01.00%)
| 
->02.85% (185,640B) 0x48334F: cxbqn::types::Scope::root_scope(std::vector<cxbqn::types::Block, std::allocator<cxbqn::types::Block> >, std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->02.85% (185,640B) 0x46CBCD: cxbqn::vm::run(std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::BlockDef, std::allocator<cxbqn::types::BlockDef> >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.43% (92,820B) 0x43DFC2: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   | ->01.43% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |   ->01.43% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |     
|   ->01.43% (92,820B) 0x457634: cxbqn::provides::get_runtime() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->01.43% (92,820B) 0x43199C: _DOCTEST_ANON_FUNC_10() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       ->01.43% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|         ->01.43% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|           
->02.57% (167,040B) 0x443ACF: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->02.57% (167,040B) in 72+ places, all below ms_print's threshold (01.00%)
| 
->01.71% (111,360B) 0x443C3A: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.71% (111,360B) in 61+ places, all below ms_print's threshold (01.00%)
| 
->01.45% (94,416B) 0x49734C: cxbqn::vm::instructions::md2c(std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.45% (94,416B) 0x46B97B: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.45% (94,416B) in 3+ places, all below ms_print's threshold (01.00%)
|   
->01.43% (92,820B) 0x4575B7: cxbqn::provides::get_runtime() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.43% (92,820B) 0x43199C: _DOCTEST_ANON_FUNC_10() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.43% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->01.43% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       
->01.43% (92,820B) 0x4577D9: cxbqn::provides::get_runtime() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.43% (92,820B) 0x43199C: _DOCTEST_ANON_FUNC_10() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.43% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->01.43% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       
->01.29% (83,648B) 0x46584F: std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >::_M_default_append(unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.29% (83,648B) in 6+ places, all below ms_print's threshold (01.00%)
| 
->01.12% (72,704B) 0x50FE189: _GLOBAL__sub_I_eh_alloc.cc (in /share/gcc/11.2.0/lib64/libstdc++.so.6.0.29)
| ->01.12% (72,704B) 0x400FAB9: call_init.part.0 (in /lib64/ld-2.26.so)
|   ->01.12% (72,704B) 0x400FBC5: _dl_init (in /lib64/ld-2.26.so)
|     ->01.12% (72,704B) 0x4000ED9: ??? (in /lib64/ld-2.26.so)
|       
->01.06% (68,661B) 0x46D661: fmt::v8::basic_memory_buffer<char, 500ul, std::allocator<char> >::grow(unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.06% (68,661B) 0x46EAC8: fmt::v8::appender fmt::v8::detail::copy_str_noinline<char, char const*, fmt::v8::appender>(char const*, char const*, fmt::v8::appender) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.06% (68,661B) 0x47C989: void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   | ->01.06% (68,661B) 0x47D1D9: decltype (({parm
|   |   ->01.06% (68,661B) 0x47D51A: void fmt::v8::detail::value<fmt::v8::basic_format_context<fmt::v8::appender, char> >::format_custom_arg<cxbqn::types::Value, fmt::v8::formatter<cxbqn::types::Value, char, void> >(void const*, fmt::v8::basic_format_parse_context<char, fmt::v8::detail::error_handler>&, fmt::v8::basic_format_context<fmt::v8::appender, char>&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |     ->01.06% (68,661B) 0x47C95B: void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       ->01.06% (68,661B) 0x484BC1: void fmt::v8::detail::value<fmt::v8::basic_format_context<fmt::v8::appender, char> >::format_custom_arg<std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, fmt::v8::formatter<std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, char, void> >(void const*, fmt::v8::basic_format_parse_context<char, fmt::v8::detail::error_handler>&, fmt::v8::basic_format_context<fmt::v8::appender, char>&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       | ->01.06% (68,661B) 0x47C4D5: char const* fmt::v8::detail::parse_replacement_field<char, void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref)::format_handler&>(char const*, char const*, void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref)::format_handler&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |   ->01.06% (68,661B) 0x47C897: void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |     ->01.06% (68,661B) 0x4849AD: void fmt::v8::detail::value<fmt::v8::basic_format_context<fmt::v8::appender, char> >::format_custom_arg<cxbqn::types::Scope, fmt::v8::formatter<cxbqn::types::Scope, char, void> >(void const*, fmt::v8::basic_format_parse_context<char, fmt::v8::detail::error_handler>&, fmt::v8::basic_format_context<fmt::v8::appender, char>&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |       ->01.06% (68,661B) 0x47C95B: void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |         ->01.06% (68,661B) 0x4C557A: fmt::v8::vformat[abi:cxx11](fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<fmt::v8::appender, char> >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           ->01.06% (68,661B) 0x481E53: cxbqn::types::Scope::get_nth_parent(unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | ->01.06% (68,661B) 0x497F6D: cxbqn::vm::instructions::varo(std::span<int const, 18446744073709551615ul>, unsigned long&, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | | ->01.06% (68,661B) 0x46B968: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   ->01.06% (68,661B) 0x49FB15: cxbqn::types::BlockInst::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | ->01.06% (68,661B) 0x49E4E8: cxbqn::types::Md2Deferred::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | ->01.06% (68,661B) 0x49D7A8: cxbqn::types::Fork::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | ->01.06% (68,661B) 0x49E94E: cxbqn::types::Atop::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | | ->01.06% (68,661B) 0x48DEEA: cxbqn::provides::Table::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | |   ->01.06% (68,661B) 0x49DFC0: cxbqn::types::Md1Deferred::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | |     ->01.06% (68,661B) 0x49640A: cxbqn::vm::instructions::fn1c(std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | |       ->01.06% (68,661B) 0x46BB53: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | |         ->01.06% (68,661B) 0x49FB15: cxbqn::types::BlockInst::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | |           ->01.06% (68,661B) 0x49DFC0: cxbqn::types::Md1Deferred::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | |             ->01.06% (68,661B) 0x49EA91: cxbqn::types::Atop::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | |             | ->01.06% (68,661B) 0x49640A: cxbqn::vm::instructions::fn1c(std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | |             | | ->01.06% (68,661B) 0x46BB53: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | |             | |   ->01.06% (68,661B) 0x49FB15: cxbqn::types::BlockInst::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | |             | |     ->01.06% (68,661B) 0x49487D: cxbqn::vm::instructions::md1c(std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | | |             | |       
|   |       |           | |   | | | |             | ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | | | |             | 
|   |       |           | |   | | | |             ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | | | |             
|   |       |           | |   | | | ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | | | 
|   |       |           | |   | | ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | | 
|   |       |           | |   | ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | 
|   |       |           | |   ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   
|   |       |           | ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | 
|   |       |           ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           
|   |       ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       
|   ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   
->08.27% (537,874B) in 56+ places, all below ms_print's threshold (01.00%)

--------------------------------------------------------------------------------
  n        time(i)         total(B)   useful-heap(B) extra-heap(B)    stacks(B)
--------------------------------------------------------------------------------
 43 396,423,807,590        6,406,808        6,011,113       395,695            0
 44 403,364,459,339        6,465,408        6,070,055       395,353            0
 45 410,305,122,504        6,447,232        6,051,772       395,460            0
 46 417,245,768,250        6,432,192        6,036,417       395,775            0
 47 427,656,736,983        6,457,088        6,060,518       396,570            0
 48 438,067,724,894        6,482,888        6,086,600       396,288            0
 49 448,478,699,279        6,418,976        6,022,424       396,552            0
 50 450,791,691,884        6,424,568        6,028,394       396,174            0
 51 453,104,679,545        6,440,264        6,044,023       396,241            0
 52 455,417,670,605        6,466,888        6,071,342       395,546            0
93.88% (6,071,342B) (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
->51.69% (3,342,744B) 0x4BEF44: spdlog::details::thread_pool::thread_pool(unsigned long, unsigned long, std::function<void ()>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->51.69% (3,342,744B) 0x4BF6B9: spdlog::details::thread_pool::thread_pool(unsigned long, unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->51.69% (3,342,744B) 0x46E0DC: std::shared_ptr<spdlog::async_logger> spdlog::async_factory_impl<(spdlog::async_overflow_policy)0>::create<spdlog::sinks::basic_file_sink<std::mutex>, char const (&) [16]>(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, char const (&) [16]) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->51.69% (3,342,744B) 0x46C15C: cxbqn::vm::run(std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::BlockDef, std::allocator<cxbqn::types::BlockDef> >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       ->51.69% (3,342,744B) 0x43DFC2: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|         ->51.69% (3,342,744B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|           ->51.69% (3,342,744B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|             
->10.33% (668,160B) 0x443A6F: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.10% (71,424B) 0x4459E9: std::__shared_ptr<cxbqn::types::Array, (__gnu_cxx::_Lock_policy)2>::__shared_ptr<std::allocator<cxbqn::types::Array>, char32_t const (&) [32]>(std::_Sp_alloc_shared_tag<std::allocator<cxbqn::types::Array> >, char32_t const (&) [32]) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| | ->01.10% (71,424B) in 24+ places, all below ms_print's threshold (01.00%)
| | 
| ->09.23% (596,736B) in 99+ places, all below ms_print's threshold (01.00%)
| 
->06.03% (389,760B) 0x443A21: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->06.03% (389,760B) in 93+ places, all below ms_print's threshold (01.00%)
| 
->03.11% (200,832B) 0x441991: cxbqn::types::Value::Value() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.29% (83,136B) 0x4973C1: cxbqn::vm::instructions::md2c(std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| | ->01.29% (83,136B) 0x46B97B: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| |   ->01.29% (83,136B) in 3+ places, all below ms_print's threshold (01.00%)
| |   
| ->01.82% (117,696B) in 6+ places, all below ms_print's threshold (01.00%)
| 
->02.87% (185,640B) 0x48334F: cxbqn::types::Scope::root_scope(std::vector<cxbqn::types::Block, std::allocator<cxbqn::types::Block> >, std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->02.87% (185,640B) 0x46CBCD: cxbqn::vm::run(std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::BlockDef, std::allocator<cxbqn::types::BlockDef> >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.44% (92,820B) 0x43DFC2: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   | ->01.44% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |   ->01.44% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |     
|   ->01.44% (92,820B) 0x457634: cxbqn::provides::get_runtime() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->01.44% (92,820B) 0x43199C: _DOCTEST_ANON_FUNC_10() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       ->01.44% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|         ->01.44% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|           
->02.58% (167,040B) 0x443ACF: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->02.58% (167,040B) in 72+ places, all below ms_print's threshold (01.00%)
| 
->01.72% (111,360B) 0x443C3A: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.72% (111,360B) in 61+ places, all below ms_print's threshold (01.00%)
| 
->01.50% (96,992B) 0x49734C: cxbqn::vm::instructions::md2c(std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.50% (96,992B) 0x46B97B: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.50% (96,992B) in 3+ places, all below ms_print's threshold (01.00%)
|   
->01.44% (92,820B) 0x4575B7: cxbqn::provides::get_runtime() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.44% (92,820B) 0x43199C: _DOCTEST_ANON_FUNC_10() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.44% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->01.44% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       
->01.44% (92,820B) 0x4577D9: cxbqn::provides::get_runtime() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.44% (92,820B) 0x43199C: _DOCTEST_ANON_FUNC_10() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.44% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->01.44% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       
->01.31% (85,024B) 0x46584F: std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >::_M_default_append(unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.31% (85,024B) in 4+ places, all below ms_print's threshold (01.00%)
| 
->01.12% (72,704B) 0x50FE189: _GLOBAL__sub_I_eh_alloc.cc (in /share/gcc/11.2.0/lib64/libstdc++.so.6.0.29)
| ->01.12% (72,704B) 0x400FAB9: call_init.part.0 (in /lib64/ld-2.26.so)
|   ->01.12% (72,704B) 0x400FBC5: _dl_init (in /lib64/ld-2.26.so)
|     ->01.12% (72,704B) 0x4000ED9: ??? (in /lib64/ld-2.26.so)
|       
->01.06% (68,661B) 0x46D661: fmt::v8::basic_memory_buffer<char, 500ul, std::allocator<char> >::grow(unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.06% (68,661B) 0x46EAC8: fmt::v8::appender fmt::v8::detail::copy_str_noinline<char, char const*, fmt::v8::appender>(char const*, char const*, fmt::v8::appender) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.06% (68,661B) 0x47C989: void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   | ->01.06% (68,661B) 0x47D1D9: decltype (({parm
|   |   ->01.06% (68,661B) 0x47D51A: void fmt::v8::detail::value<fmt::v8::basic_format_context<fmt::v8::appender, char> >::format_custom_arg<cxbqn::types::Value, fmt::v8::formatter<cxbqn::types::Value, char, void> >(void const*, fmt::v8::basic_format_parse_context<char, fmt::v8::detail::error_handler>&, fmt::v8::basic_format_context<fmt::v8::appender, char>&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |     ->01.06% (68,661B) 0x47C95B: void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       ->01.06% (68,661B) 0x484BC1: void fmt::v8::detail::value<fmt::v8::basic_format_context<fmt::v8::appender, char> >::format_custom_arg<std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, fmt::v8::formatter<std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, char, void> >(void const*, fmt::v8::basic_format_parse_context<char, fmt::v8::detail::error_handler>&, fmt::v8::basic_format_context<fmt::v8::appender, char>&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       | ->01.06% (68,661B) 0x47C4D5: char const* fmt::v8::detail::parse_replacement_field<char, void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref)::format_handler&>(char const*, char const*, void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref)::format_handler&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |   ->01.06% (68,661B) 0x47C897: void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |     ->01.06% (68,661B) 0x4849AD: void fmt::v8::detail::value<fmt::v8::basic_format_context<fmt::v8::appender, char> >::format_custom_arg<cxbqn::types::Scope, fmt::v8::formatter<cxbqn::types::Scope, char, void> >(void const*, fmt::v8::basic_format_parse_context<char, fmt::v8::detail::error_handler>&, fmt::v8::basic_format_context<fmt::v8::appender, char>&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |       ->01.06% (68,661B) 0x47C95B: void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |         ->01.06% (68,661B) 0x4C557A: fmt::v8::vformat[abi:cxx11](fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<fmt::v8::appender, char> >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           ->01.06% (68,661B) 0x481E53: cxbqn::types::Scope::get_nth_parent(unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | ->01.06% (68,661B) 0x497F6D: cxbqn::vm::instructions::varo(std::span<int const, 18446744073709551615ul>, unsigned long&, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | | ->01.06% (68,661B) 0x46B968: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   ->01.06% (68,661B) 0x49FB15: cxbqn::types::BlockInst::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | ->01.06% (68,661B) 0x49640A: cxbqn::vm::instructions::fn1c(std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | ->01.06% (68,661B) 0x46BB53: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | |   ->01.06% (68,661B) 0x46CEA5: cxbqn::vm::run(std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::BlockDef, std::allocator<cxbqn::types::BlockDef> >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | |   | ->01.06% (68,661B) 0x457634: cxbqn::provides::get_runtime() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | |   | | ->01.06% (68,661B) 0x43199C: _DOCTEST_ANON_FUNC_10() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | |   | |   ->01.06% (68,661B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | |   | |     ->01.06% (68,661B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | |   | |       
|   |       |           | |   | |   | ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | |   | 
|   |       |           | |   | |   ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | |   
|   |       |           | |   | ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | 
|   |       |           | |   ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   
|   |       |           | ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | 
|   |       |           ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           
|   |       ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       
|   ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   
->07.68% (496,785B) in 55+ places, all below ms_print's threshold (01.00%)

--------------------------------------------------------------------------------
  n        time(i)         total(B)   useful-heap(B) extra-heap(B)    stacks(B)
--------------------------------------------------------------------------------
 53 455,650,239,763        6,634,448        6,238,938       395,510            0
94.04% (6,238,938B) (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
->50.38% (3,342,744B) 0x4BEF44: spdlog::details::thread_pool::thread_pool(unsigned long, unsigned long, std::function<void ()>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->50.38% (3,342,744B) 0x4BF6B9: spdlog::details::thread_pool::thread_pool(unsigned long, unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->50.38% (3,342,744B) 0x46E0DC: std::shared_ptr<spdlog::async_logger> spdlog::async_factory_impl<(spdlog::async_overflow_policy)0>::create<spdlog::sinks::basic_file_sink<std::mutex>, char const (&) [16]>(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, char const (&) [16]) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->50.38% (3,342,744B) 0x46C15C: cxbqn::vm::run(std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::BlockDef, std::allocator<cxbqn::types::BlockDef> >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       ->50.38% (3,342,744B) 0x43DFC2: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|         ->50.38% (3,342,744B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|           ->50.38% (3,342,744B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|             
->10.07% (668,160B) 0x443A6F: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.08% (71,424B) 0x4459E9: std::__shared_ptr<cxbqn::types::Array, (__gnu_cxx::_Lock_policy)2>::__shared_ptr<std::allocator<cxbqn::types::Array>, char32_t const (&) [32]>(std::_Sp_alloc_shared_tag<std::allocator<cxbqn::types::Array> >, char32_t const (&) [32]) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| | ->01.08% (71,424B) in 24+ places, all below ms_print's threshold (01.00%)
| | 
| ->08.99% (596,736B) in 99+ places, all below ms_print's threshold (01.00%)
| 
->05.87% (389,760B) 0x443A21: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->05.87% (389,760B) in 93+ places, all below ms_print's threshold (01.00%)
| 
->03.19% (211,817B) 0x46D661: fmt::v8::basic_memory_buffer<char, 500ul, std::allocator<char> >::grow(unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->03.19% (211,817B) 0x46EAC8: fmt::v8::appender fmt::v8::detail::copy_str_noinline<char, char const*, fmt::v8::appender>(char const*, char const*, fmt::v8::appender) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->03.19% (211,817B) 0x47C989: void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   | ->03.19% (211,817B) 0x47D1D9: decltype (({parm
|   |   ->03.19% (211,817B) 0x47D51A: void fmt::v8::detail::value<fmt::v8::basic_format_context<fmt::v8::appender, char> >::format_custom_arg<cxbqn::types::Value, fmt::v8::formatter<cxbqn::types::Value, char, void> >(void const*, fmt::v8::basic_format_parse_context<char, fmt::v8::detail::error_handler>&, fmt::v8::basic_format_context<fmt::v8::appender, char>&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |     ->03.19% (211,817B) 0x47C95B: void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       ->03.19% (211,817B) 0x484BC1: void fmt::v8::detail::value<fmt::v8::basic_format_context<fmt::v8::appender, char> >::format_custom_arg<std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, fmt::v8::formatter<std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, char, void> >(void const*, fmt::v8::basic_format_parse_context<char, fmt::v8::detail::error_handler>&, fmt::v8::basic_format_context<fmt::v8::appender, char>&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       | ->03.19% (211,817B) 0x47C4D5: char const* fmt::v8::detail::parse_replacement_field<char, void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref)::format_handler&>(char const*, char const*, void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref)::format_handler&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |   ->03.19% (211,817B) 0x47C897: void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |     ->03.19% (211,817B) 0x4849AD: void fmt::v8::detail::value<fmt::v8::basic_format_context<fmt::v8::appender, char> >::format_custom_arg<cxbqn::types::Scope, fmt::v8::formatter<cxbqn::types::Scope, char, void> >(void const*, fmt::v8::basic_format_parse_context<char, fmt::v8::detail::error_handler>&, fmt::v8::basic_format_context<fmt::v8::appender, char>&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |       ->03.19% (211,817B) 0x47C95B: void fmt::v8::detail::vformat_to<char>(fmt::v8::detail::buffer<char>&, fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<std::conditional<std::is_same<fmt::v8::type_identity<char>::type, char>::value, fmt::v8::appender, std::back_insert_iterator<fmt::v8::detail::buffer<fmt::v8::type_identity<char>::type> > >::type, fmt::v8::type_identity<char>::type> >, fmt::v8::detail::locale_ref) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |         ->03.19% (211,817B) 0x4C557A: fmt::v8::vformat[abi:cxx11](fmt::v8::basic_string_view<char>, fmt::v8::basic_format_args<fmt::v8::basic_format_context<fmt::v8::appender, char> >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           ->03.19% (211,817B) 0x481E53: cxbqn::types::Scope::get_nth_parent(unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | ->03.19% (211,817B) 0x497F6D: cxbqn::vm::instructions::varo(std::span<int const, 18446744073709551615ul>, unsigned long&, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | | ->03.19% (211,817B) 0x46B968: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   ->03.19% (211,817B) 0x49FB15: cxbqn::types::BlockInst::call(unsigned char, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | ->03.19% (211,817B) 0x49640A: cxbqn::vm::instructions::fn1c(std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | | ->03.19% (211,817B) 0x46BB53: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | |   ->03.19% (211,817B) 0x46CEA5: cxbqn::vm::run(std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::BlockDef, std::allocator<cxbqn::types::BlockDef> >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | |   | ->03.19% (211,817B) 0x457634: cxbqn::provides::get_runtime() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | |   | | ->03.19% (211,817B) 0x43199C: _DOCTEST_ANON_FUNC_10() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | |   | |   ->03.19% (211,817B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | |   | |     ->03.19% (211,817B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |       |           | |   | |   | |       
|   |       |           | |   | |   | ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | |   | 
|   |       |           | |   | |   ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | |   
|   |       |           | |   | ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   | 
|   |       |           | |   ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | |   
|   |       |           | ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           | 
|   |       |           ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       |           
|   |       ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   |       
|   ->00.00% (0B) in 1+ places, all below ms_print's threshold (01.00%)
|   
->03.03% (200,832B) 0x441991: cxbqn::types::Value::Value() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.25% (83,136B) 0x4973C1: cxbqn::vm::instructions::md2c(std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| | ->01.25% (83,136B) 0x46B97B: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| |   ->01.25% (83,136B) in 3+ places, all below ms_print's threshold (01.00%)
| |   
| ->01.77% (117,696B) in 6+ places, all below ms_print's threshold (01.00%)
| 
->02.80% (185,640B) 0x48334F: cxbqn::types::Scope::root_scope(std::vector<cxbqn::types::Block, std::allocator<cxbqn::types::Block> >, std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->02.80% (185,640B) 0x46CBCD: cxbqn::vm::run(std::vector<int, std::allocator<int> >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<cxbqn::types::BlockDef, std::allocator<cxbqn::types::BlockDef> >, std::vector<cxbqn::types::Body, std::allocator<cxbqn::types::Body> >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.40% (92,820B) 0x43DFC2: _DOCTEST_ANON_FUNC_8() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   | ->01.40% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |   ->01.40% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   |     
|   ->01.40% (92,820B) 0x457634: cxbqn::provides::get_runtime() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->01.40% (92,820B) 0x43199C: _DOCTEST_ANON_FUNC_10() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       ->01.40% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|         ->01.40% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|           
->02.52% (167,040B) 0x443ACF: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->02.52% (167,040B) in 72+ places, all below ms_print's threshold (01.00%)
| 
->01.68% (111,360B) 0x443C3A: cxbqn::types::Array::Array(std::__cxx11::basic_string<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > const&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.68% (111,360B) in 58+ places, all below ms_print's threshold (01.00%)
| 
->01.46% (96,992B) 0x49734C: cxbqn::vm::instructions::md2c(std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >&) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.46% (96,992B) 0x46B97B: cxbqn::vm::vm(std::span<int const, 18446744073709551615ul>, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >, std::shared_ptr<cxbqn::types::Scope>) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.46% (96,992B) in 3+ places, all below ms_print's threshold (01.00%)
|   
->01.40% (92,820B) 0x4575B7: cxbqn::provides::get_runtime() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.40% (92,820B) 0x43199C: _DOCTEST_ANON_FUNC_10() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.40% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->01.40% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       
->01.40% (92,820B) 0x4577D9: cxbqn::provides::get_runtime() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.40% (92,820B) 0x43199C: _DOCTEST_ANON_FUNC_10() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|   ->01.40% (92,820B) 0x4311FA: doctest::Context::run() (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|     ->01.40% (92,820B) 0x418E1E: main (in /home/asher/workspace/cxbqn/build/test/test_runtime)
|       
->01.28% (85,024B) 0x46584F: std::vector<std::shared_ptr<cxbqn::types::Value>, std::allocator<std::shared_ptr<cxbqn::types::Value> > >::_M_default_append(unsigned long) (in /home/asher/workspace/cxbqn/build/test/test_runtime)
| ->01.28% (85,024B) in 4+ places, all below ms_print's threshold (01.00%)
| 
->01.10% (72,704B) 0x50FE189: _GLOBAL__sub_I_eh_alloc.cc (in /share/gcc/11.2.0/lib64/libstdc++.so.6.0.29)
| ->01.10% (72,704B) 0x400FAB9: call_init.part.0 (in /lib64/ld-2.26.so)
|   ->01.10% (72,704B) 0x400FBC5: _dl_init (in /lib64/ld-2.26.so)
|     ->01.10% (72,704B) 0x4000ED9: ??? (in /lib64/ld-2.26.so)
|       
->07.86% (521,225B) in 56+ places, all below ms_print's threshold (01.00%)

```
