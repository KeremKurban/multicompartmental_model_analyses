#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;
#if defined(__cplusplus)
extern "C" {
#endif

extern void _ichan2_reg(void);
extern void _kaprox_reg(void);
extern void _kdrca1_reg(void);
extern void _na3n_reg(void);

void modl_reg() {
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");
    fprintf(stderr, " \"ichan2.mod\"");
    fprintf(stderr, " \"kaprox.mod\"");
    fprintf(stderr, " \"kdrca1.mod\"");
    fprintf(stderr, " \"na3n.mod\"");
    fprintf(stderr, "\n");
  }
  _ichan2_reg();
  _kaprox_reg();
  _kdrca1_reg();
  _na3n_reg();
}

#if defined(__cplusplus)
}
#endif
