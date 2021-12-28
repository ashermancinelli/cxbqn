## Precompiled BQN Values

The files in this directory are precompiled BQN sources, consumable by CXBQN.

* `c`: precompiled compiler
* `f`: precompiled formatter
* `r`: precompiled full runtime
* `r0`: precompiled inner runtime
* `r1`: precompiled outter runtime

To update these values, you may use the utility script in the build directory, `ccx-wrapper.sh`:

```console
for i in c f r r0 r1; do
  ./ccx-wrapper $i > "../include/cxbqn/__/${i}"
done
```

You may also edit the wrapper script to use the BQN executable from CXBQN, or to use CBQN's BQN (the faster option).
