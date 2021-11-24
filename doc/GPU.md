## Enabling GPU Execution

***NOTE: These are my chicken-scratch notes on what enabling GPU execution would look like. It's not a technical specification.***

The API would probably be in the form of a one-modifier that executes a function on the GPU after decomposing it.
Example use case:
```console
   ⊢ •_CUDAForAll ↕10
⟨ 0 1 2 3 4 5 6 7 8 9 ⟩
```

This would take the function and apply it to each element of the array `𝕩`.
Using a combination of `•Decompose` and `•PrimInd`, a given function could be
broken down into primitives and data values, which may all be copied over to
the GPU device.
There would also exist another version of the runtime compiled for GPU.

An example Thrust implementation of `•_CUDAForAll` that only modifies primitves
might look like this:

```cpp
O<Value> CUDAForAll::call(u8 nargs, std::vector<O<Value>> args) {

  // 𝕩 must be an array
  auto x = dynamic_pointer_cast<Array>(args[1]);

  auto f = args[4];

  // Copy BQN array to the device vector
  auto h_vals = thrust::host_vector<f64>(x->N());
  for (int i=0; i<x->N(); i++)
    h_vals[i] = dynamic_pointer_cast<Number>(x->values[i])->v;
  auto d_vals = thrust::device_vector<f64>(h_vals);

  // 𝕗 must be a primitive, since we're using device implementations of runtime
  // primitives on the GPU
  auto it = std::find(runtime.begin(), runtime.end(), f);
  if (it == runtime.end())
    throw std::runtime_error("•_CUDAForAll: 𝕗 must be a primitive");

  // Find the corresponding GPU-enabled version of the given runtime primitive 𝕗
  auto kernel = gpu_runtime[std::distance(runtime.begin(), it)];

  // Execute kernel in-place on device
  thrust::transform(d_vals.begin(), d_vals.end(), d_vals.begin(), kernel);

  // Copy data back to host
  h_vals = d_vals;

  // Wrap the return values into a BQN value
  auto ret = make_shared<Array>(x->N());
  for (int i=0; i<x->N(); i++)
    ret->values[i] = make_shared<Number>(h_vals[i]);
    
  return ret;
}
```

A similar approach may be taken for enabling OMP/threaded execution.
