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

#pragma once

#include "cuda/utilities/error.hpp"

#include <napi.h>

#include <nv_node/utilities/args.hpp>

#include <cstddef>
#include <cstdint>

namespace nv {

class Device : public Napi::ObjectWrap<Device> {
 public:
  /**
   * @brief Initialize the Device JavaScript constructor and prototype.
   *
   * @param env The active JavaScript environment.
   * @param exports The exports object to decorate.
   * @return Napi::Object The decorated exports object.
   */
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  /**
   * @brief Construct a new Device instance from C++.
   *
   * @param id The CUDA device id.
   */
  static Napi::Object New(int32_t id = current_device_id());

  /**
   * @brief Retrieve the id of the current CUDA device for this thread.
   *
   * @return int32_t The CUDA device id.
   */
  static int32_t current_device_id() {
    int32_t device;
    NODE_CUDA_TRY(cudaGetDevice(&device));
    return device;
  }

  /**
   * @brief Construct a new Device instance from JavaScript.
   *
   * @param args The JavaScript arguments list wrapped in a conversion helper.
   */
  Device(CallbackArgs const& args);

  /**
   * @brief Initialize the Device instance created by either C++ or JavaScript.
   *
   * @param id Size in bytes to allocate in memory.
   */
  void Initialize(int32_t id = current_device_id());

  int32_t id() const { return id_; }
  cudaDeviceProp const& props() const { return props_; }
  std::string const& pci_bus_name() const { return pci_bus_name_; }

 private:
  static Napi::FunctionReference constructor;

  Napi::Value GetId(Napi::CallbackInfo const& info);
  Napi::Value GetName(Napi::CallbackInfo const& info);
  Napi::Value GetPCIBusId(Napi::CallbackInfo const& info);
  Napi::Value GetPCIBusName(Napi::CallbackInfo const& info);

  int32_t id_{};                   ///< The CUDA device id
  cudaDeviceProp props_{};         ///< The CUDA device properties
  std::string pci_bus_name_{127};  ///< The CUDA device PCI bus id string
};

}  // namespace nv
