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

const ENN = (() => {
    let ENN: any, types = ['Release'];
    if (process.env.NODE_DEBUG !== undefined || process.env.NODE_ENV === 'debug') {
        types.push('Debug');
    }
    for (let type; type = types.pop();) {
        try {
            if (ENN = require(`../${type}/node_example_native_module.node`)) {
                break;
            }
        } catch (e) { console.error(e); continue; }
    }
    if (ENN) return ENN.init();
    throw new Error('node_example_native_module not found');
})();

export { ENN };

export interface ENN {
    ExampleClass: ExampleClassConstructor;
}

export interface ExampleClassConstructor {
    readonly prototype: ExampleClass;
    new(): ExampleClass;
}

export interface ExampleClass {
    exampleMethod(): void;
    exampleProperty: number;
}

export const ExampleClass: ExampleClassConstructor = ENN.ExampleClass;
