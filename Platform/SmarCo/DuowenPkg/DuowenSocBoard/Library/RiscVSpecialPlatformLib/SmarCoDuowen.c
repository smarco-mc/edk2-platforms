/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2023, SmarCo Limited. All rights reserved.<BR>
 * Author: Lv Zheng <zhenglv@smart-core.cn>
 *
 * SPDX-License-Identifier: BSD-2-Clause-Patent
 */

#include <Library/RiscVSpecialPlatformLib.h>
#include <sbi_utils/fdt/fdt_helper.h>
#include <sbi_utils/fdt/fdt_fixup.h>

static u64 smarco_duowen_tlbr_flush_limit(const struct fdt_match *match)
{
  return 0;
}

static int smarco_duowen_fdt_fixup(void *fdt, const struct fdt_match *match)
{
  /*
   * Duowen has reserved memory region for DMA CMA usage.
   */
  fdt_reserved_memory_nomap_fixup(fdt);

  return 0;
}

static const struct fdt_match smarco_duowen_match[] = {
  { .compatible = "smarco,duowen" },
  { },
};

const struct platform_override smarco_duowen = {
  .match_table = smarco_duowen_match,
  .tlbr_flush_limit = smarco_duowen_tlbr_flush_limit,
  .fdt_fixup = smarco_duowen_fdt_fixup,
};

const struct platform_override *special_platforms[] = {
  &smarco_duowen,
};
INTN NumberOfPlaformsInArray = array_size(special_platforms);
