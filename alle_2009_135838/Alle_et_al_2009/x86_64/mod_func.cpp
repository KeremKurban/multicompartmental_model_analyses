#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;
#if defined(__cplusplus)
extern "C" {
#endif

extern void _GCa_reg(void);
extern void _GK_reg(void);
extern void _GNa_reg(void);
extern void _peak_reg(void);

void modl_reg() {
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");
    fprintf(stderr, " \"GCa.mod\"");
    fprintf(stderr, " \"GK.mod\"");
    fprintf(stderr, " \"GNa.mod\"");
    fprintf(stderr, " \"peak.mod\"");
    fprintf(stderr, "\n");
  }
  _GCa_reg();
  _GK_reg();
  _GNa_reg();
  _peak_reg();
}

#if defined(__cplusplus)
}
#endif
