// Copyright (c) 2020, NVIDIA CORPORATION.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <example_native_module/example_class.hpp>

#include <napi.h>

namespace node_example_native_module {

// Declare the static ExampleClass constructor
Napi::FunctionReference ExampleClass::constructor;

Napi::Object ExampleClass::Init(Napi::Env env, Napi::Object exports) {
  // Create the ExampleClass constructor and prototype
  Napi::Function ctor = DefineClass(env,
                                    "ExampleClass",
                                    {
                                      InstanceAccessor("exampleProperty",
                                                       &ExampleClass::GetExampleProperty,
                                                       &ExampleClass::SetExampleProperty,
                                                       napi_enumerable),
                                      InstanceMethod("exampleMethod", &ExampleClass::ExampleMethod),
                                    });

  // Assign the constructor to the static property
  ExampleClass::constructor = Napi::Persistent(ctor);
  // Ensure the function isn't garbage-collected by the VM
  ExampleClass::constructor.SuppressDestruct();

  // Set the constructor as a property on the exports object so it's available to JS
  exports.Set("ExampleClass", ctor);

  return exports;
}

ExampleClass::ExampleClass(Napi::CallbackInfo const& info) : Napi::ObjectWrap<ExampleClass>(info) {}

Napi::Value ExampleClass::ExampleMethod(Napi::CallbackInfo const& info) {
  return info.Env().Undefined();
}

Napi::Value ExampleClass::GetExampleProperty(Napi::CallbackInfo const& info) {
  return Napi::Number::New(info.Env(), this->example_property_);
}

void ExampleClass::SetExampleProperty(Napi::CallbackInfo const& info, Napi::Value const& value) {
  this->example_property_ = value.As<Napi::Number>().Uint32Value();
}

}  // namespace node_example_native_module
