# Taken from BQN/test/cases/bytecode.bqn
⟨
  5  ‿ "5                       "                       #  0 PUSH,  7 RETN
  3  ‿ "4⋄3                     "               #  6 POPS
  5  ‿ "a←5                     "               # 33 VARM, 48 SETN
  4  ‿ "a←5⋄a↩4                 " # 49 SETU
  2  ‿ "a←2⋄b←3⋄a               " # 32 VARO
  1  ‿ "a←1⋄A 4                 "       # 16 FN1C
  2  ‿ "a←2⋄3 A 4               "       # 17 FN2C
  6  ‿ "{𝕩}6                    "           #  1 DFND
  3  ‿ "A←{𝕨}⋄3 A 4             " #    dyadic block function
  7  ‿ "a‿b←7‿2⋄a               " # 11 ARRO, 12 ARRM
  2  ‿ "·‿b←7‿2⋄b               " # 36 VARN
  2  ‿ "0{𝕨𝕏1}2                 " # 19 FN2O (doesn't test call type)
  5  ‿ "{({𝕨}𝕨)𝕏𝕩}5             " # 18 FN1O not called
  8  ‿ "{𝕩{a‿b←𝕨}𝕨,𝕩}8          " # 19 FN2O not called
  4  ‿ "4{𝔽}                    "           # 26 MD1C
  6  ‿ "4{𝔽⋄𝕩}6                 " #    deferred modifier
  1  ‿ "3{𝔾}{𝕩} 1               " # 27 MD2C
  2  ‿ "(2{𝔽}{𝕩})3              " # 20 TR2D
  3  ‿ "3({a‿b←𝕩⋄a}{𝕨‿𝕩})4      " #    dyadic 2-train
  4  ‿ "4({𝕨‿𝕩}{𝕩}{𝕨})5         " # 21 TR3D
  2  ‿ "a‿b←(2{𝕨‿𝕩}{𝕩})5⋄a      " #    monadic, data in left branch
  2  ‿ "({a↩2⋄𝕩}{𝕩⋄a}{a↩3⋄𝕩})a←4" # ordering
  8  ‿ "a←3⋄a{𝕩}↩8⋄a            " # 50 SETM
  5  ‿ "a←4⋄a{𝕨⋄5}↩6            " #    returns new value
  1  ‿ "a←3⋄a{𝕩⋄1}↩⋄a           " # 51 SETC
  4  ‿ "a‿b←2‿1⋄a‿b{𝕩‿𝕨}↩4⋄a    " #    lists

  # Call type tests; can also replace {a←𝕩⋄{a↩𝕩}𝕨⋄a} with {𝕩;𝕨}
  7  ‿ "     {𝕨{a←𝕩⋄{a↩𝕩}𝕨⋄a}𝕩}7"  # 19 FN2O call type
  3  ‿ "    3{𝕨{a←𝕩⋄{a↩𝕩}𝕨⋄a}𝕩}7"  # 19 FN2O call type
  7  ‿ "{𝕏0} {𝕨{a←𝕩⋄{a↩𝕩}𝕨⋄a}𝕏}7"  # 23 TR3O call type
  3  ‿ "{𝕏0}3{𝕨{a←𝕩⋄{a↩𝕩}𝕨⋄a}𝕏}7"  # 23 TR3O call type

  # Further tests for lexical scoping
  1  ‿ "a←1⋄{a←2}⋄a"
  2  ‿ "a←1⋄{a↩2}⋄a"
  6  ‿ "f‿g←{a←2⋄{a↩𝕩}‿{𝕩⋄a}}⋄F 6⋄G 0"
  5  ‿ "L←{𝕩{𝕏𝕗}}⋄{𝕏𝕤}L L L 5"
  3  ‿ "_l←{𝕩{𝕏𝕗} 𝔽}⋄{𝕏𝕤} {𝕩}_l 3 _l 5"
  1  ‿ "1{𝕨}{𝔽{𝕩𝔽𝕨}𝔾𝔽}{𝕩}0    # 0≠1 via Church booleans"
  2  ‿ "0‿(0‿{𝕩}){{a‿b←𝕩⋄t←𝕤⋄{𝕤⋄T↩{𝕤⋄{a‿b←𝕩⋄a}}}{B𝕗}0⋄(T b){a‿b←𝕩⋄𝔽b}}𝕗} 0‿(1‿(2‿(3‿(4‿{𝕩}))))"
⟩
