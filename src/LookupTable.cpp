#include "LookupTable.h"
#include "Constants.h"
#include <cassert>
#include <cstdint>

int32_t LookupTable::table_idx_to_tang_pos(int32_t table_idx) {
  return table_idx - (det_per_ring / 2) + 1;
};

int32_t LookupTable::tang_pos_to_table_idx(int32_t tang_pos_num) {
  return tang_pos_num + (det_per_ring / 2) - 1;
};

const DetectorPair &LookupTable::lookup(int32_t angle_num,
                                        int32_t tang_pos_num) {
  int32_t tang_pos_idx = tang_pos_to_table_idx(tang_pos_num);
  return (*table)[angle_num][tang_pos_idx];
};

void LookupTable::initialize_table() {
  for (int32_t ang_pos_num = 0; ang_pos_num < det_per_ring / 2; ang_pos_num++) {
    for (int32_t tang_pos_num = min_tang_pos_num, tang_arr_idx;
         tang_pos_num <= max_tang_pos_num; tang_pos_num++) {

      tang_arr_idx = tang_pos_to_table_idx(tang_pos_num);

      (*table)[ang_pos_num][tang_arr_idx].det_idx_1 =
          (ang_pos_num + tang_pos_num / 2 + det_per_ring) % det_per_ring;

      (*table)[ang_pos_num][tang_arr_idx].det_idx_2 =
          (ang_pos_num - (tang_pos_num + 1) / 2 + det_per_ring / 2) %
          det_per_ring;
    };
  };
};
