/*
 *
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License Agreement
 * that you accepted before downloading this file.
 *
 * This header forms part of the Software but may be included and used unaltered
 * in derivative works.
 *
 * For more information, please visit www.OVPworld.org or www.imperas.com
 */

#ifndef VMI_TYPEREFS_H
#define VMI_TYPEREFS_H

#include "hostapi/typeMacros.h"

DEFINE_CS(vmiSymbolFile     );
DEFINE_CS(vmiSymbol         );
DEFINE_CS(vmiFileLine       );
DEFINE_S( vmiFlags          );
DEFINE_S( vmiIASAttr        );
DEFINE_S( vmiLabel          );
DEFINE_S( vmiProcessor      );
DEFINE_S( vmiModelTimer     );
DEFINE_S( vmiVcdEntry       );
DEFINE_S( vmiConnInput      );
DEFINE_S( vmiConnOutput     );
DEFINE_S( vmiRangeEntry     );
DEFINE_S( vmiRangeTable     );
DEFINE_S( vmiWatchHandle    );
DEFINE_S( vmiViewObject     );
DEFINE_S( vmiViewEvent      );

DEFINE_S( vmiDocNode        );

DEFINE_CS(vmiosAttr         );
DEFINE_CS(vmiosInterceptDesc);
DEFINE_S( vmiosObject       );
DEFINE_S( vmiosStatBuf      );
DEFINE_S( vmiosTimeBuf      );

DEFINE_CS(vmiFlags          );
DEFINE_CS(vmiIASAttr        );
DEFINE_CS(vmiRegGroup       );
DEFINE_S( vmiRegGroup       );
DEFINE_CS(vmiRegInfo        );
DEFINE_S( vmiRegInfo        );

DEFINE_S( vmiBusPort        );
DEFINE_S( vmiFifoPort       );
DEFINE_S( vmiNetPort        );
DEFINE_S( vmiEnumParameter  );
DEFINE_S( vmiParameter      );

DEFINE_S( vmiProcessorInfo  );
DEFINE_CS(vmiProcessorInfo  );

DEFINE_CS(vmiExceptionInfo  );
DEFINE_S( vmiExceptionInfo  );
DEFINE_CS(vmiModeInfo       );
DEFINE_S( vmiModeInfo       );

DEFINE_S( memDomain         );
DEFINE_S( memRegion         );
DEFINE_S( memMRUSet         );

DEFINE_CS(vmimmcAttr        );
DEFINE_S( vmimmcComponent   );
DEFINE_S( vmimmcPort        );

DEFINE_S( vmidDecodeTable   );

DEFINE_S( vmiFPArg          );
DEFINE_U( vmiFPFlags        );
DEFINE_CS(vmiFPConfig       );
DEFINE_S( vmiFPConfig       );

DEFINE_S( vmiSaveContext    );
DEFINE_S( vmiRestoreContext );

DEFINE_S( vmiSharedDataHandle);
DEFINE_S( vmiDLHandle       );

#endif /*VMI_TYPEREFS_H*/
