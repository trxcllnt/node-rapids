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

import CUDF from './addon';
import {Column} from './column';

interface TableConstructor {
  readonly prototype: Table;
  new(props: {columns?: ReadonlyArray<Column>|null}): Table;
}

export interface Table {
  readonly numColumns: number;
  readonly numRows: number;
  getColumnByIndex(index: number): Column;
}

// eslint-disable-next-line @typescript-eslint/no-redeclare
export const Table: TableConstructor = CUDF.Table;
