FLX is an alternative to C++ Standard Library. It does not use anything from STD. It links against provided CRT.

It differs with STD on these points:
1. FLX does NOT follow The C++ Standard. While I will do my best to follow Standard I will prioritize common sense (e.g. dynamic array will not be named "vector").
2. C++26 and onward.
3. No exceptions throughout the whole lib.
4. Modules over headers. The only header "flx/core.hpp" is left as a header to provide feature macros.
5. FLX treats moved-from objects as "dead", where calling dtor would be a no-op. FLX will omit these dtor calls. Similar to the "relocate" feature that was removed from the C++26 draft.
