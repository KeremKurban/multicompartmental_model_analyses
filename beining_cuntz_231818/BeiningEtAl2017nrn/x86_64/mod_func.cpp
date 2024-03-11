#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;
#if defined(__cplusplus)
extern "C" {
#endif

extern void _BK_reg(void);
extern void _Cabuffer_reg(void);
extern void _CadepK_reg(void);
extern void _Caold_reg(void);
extern void _Cav12_reg(void);
extern void _Cav13_reg(void);
extern void _Cav22_reg(void);
extern void _Cav32_reg(void);
extern void _HCN_reg(void);
extern void _ichan3_reg(void);
extern void _Kir21_reg(void);
extern void _Kv11_reg(void);
extern void _Kv14_reg(void);
extern void _Kv21_reg(void);
extern void _Kv33_reg(void);
extern void _Kv34_reg(void);
extern void _Kv42b_reg(void);
extern void _Kv42_reg(void);
extern void _Kv723_reg(void);
extern void _na8st_reg(void);
extern void _SK2_reg(void);

void modl_reg() {
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");
    fprintf(stderr, " \"lib_mech//BK.mod\"");
    fprintf(stderr, " \"lib_mech//Cabuffer.mod\"");
    fprintf(stderr, " \"lib_mech//CadepK.mod\"");
    fprintf(stderr, " \"lib_mech//Caold.mod\"");
    fprintf(stderr, " \"lib_mech//Cav12.mod\"");
    fprintf(stderr, " \"lib_mech//Cav13.mod\"");
    fprintf(stderr, " \"lib_mech//Cav22.mod\"");
    fprintf(stderr, " \"lib_mech//Cav32.mod\"");
    fprintf(stderr, " \"lib_mech//HCN.mod\"");
    fprintf(stderr, " \"lib_mech//ichan3.mod\"");
    fprintf(stderr, " \"lib_mech//Kir21.mod\"");
    fprintf(stderr, " \"lib_mech//Kv11.mod\"");
    fprintf(stderr, " \"lib_mech//Kv14.mod\"");
    fprintf(stderr, " \"lib_mech//Kv21.mod\"");
    fprintf(stderr, " \"lib_mech//Kv33.mod\"");
    fprintf(stderr, " \"lib_mech//Kv34.mod\"");
    fprintf(stderr, " \"lib_mech//Kv42b.mod\"");
    fprintf(stderr, " \"lib_mech//Kv42.mod\"");
    fprintf(stderr, " \"lib_mech//Kv723.mod\"");
    fprintf(stderr, " \"lib_mech//na8st.mod\"");
    fprintf(stderr, " \"lib_mech//SK2.mod\"");
    fprintf(stderr, "\n");
  }
  _BK_reg();
  _Cabuffer_reg();
  _CadepK_reg();
  _Caold_reg();
  _Cav12_reg();
  _Cav13_reg();
  _Cav22_reg();
  _Cav32_reg();
  _HCN_reg();
  _ichan3_reg();
  _Kir21_reg();
  _Kv11_reg();
  _Kv14_reg();
  _Kv21_reg();
  _Kv33_reg();
  _Kv34_reg();
  _Kv42b_reg();
  _Kv42_reg();
  _Kv723_reg();
  _na8st_reg();
  _SK2_reg();
}

#if defined(__cplusplus)
}
#endif
