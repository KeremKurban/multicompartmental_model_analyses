#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;
#if defined(__cplusplus)
extern "C" {
#endif

extern void _fna_reg(void);
extern void _ichan2_reg(void);
extern void _kdr_reg(void);
extern void _nmdanetGR_reg(void);

void modl_reg() {
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");
    fprintf(stderr, " \"fna.mod\"");
    fprintf(stderr, " \"ichan2.mod\"");
    fprintf(stderr, " \"kdr.mod\"");
    fprintf(stderr, " \"nmdanetGR.mod\"");
    fprintf(stderr, "\n");
  }
  _fna_reg();
  _ichan2_reg();
  _kdr_reg();
  _nmdanetGR_reg();
}

#if defined(__cplusplus)
}
#endif
