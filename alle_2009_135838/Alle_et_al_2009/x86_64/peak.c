/* Created by Language version: 7.7.0 */
/* VECTORIZED */
#define NRN_VECTORIZED 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mech_api.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__pk
#define _nrn_initial _nrn_initial__pk
#define nrn_cur _nrn_cur__pk
#define _nrn_current _nrn_current__pk
#define nrn_jacob _nrn_jacob__pk
#define nrn_state _nrn_state__pk
#define _net_receive _net_receive__pk 
#define check check__pk 
 
#define _threadargscomma_ _p, _ppvar, _thread, _nt,
#define _threadargsprotocomma_ double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt,
#define _threadargs_ _p, _ppvar, _thread, _nt
#define _threadargsproto_ double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 /* Thread safe. No static _p or _ppvar. */
 
#define t _nt->_t
#define dt _nt->_dt
#define tmin _p[0]
#define tmin_columnindex 0
#define vmin _p[1]
#define vmin_columnindex 1
#define tpeak _p[2]
#define tpeak_columnindex 2
#define vpeak _p[3]
#define vpeak_columnindex 3
#define dvdt _p[4]
#define dvdt_columnindex 4
#define d2vdt2 _p[5]
#define d2vdt2_columnindex 5
#define tdvdtpeak _p[6]
#define tdvdtpeak_columnindex 6
#define dvdtpeak _p[7]
#define dvdtpeak_columnindex 7
#define td2vdt2peak _p[8]
#define td2vdt2peak_columnindex 8
#define d2vdt2peak _p[9]
#define d2vdt2peak_columnindex 9
#define v1 _p[10]
#define v1_columnindex 10
#define v2 _p[11]
#define v2_columnindex 11
#define v3 _p[12]
#define v3_columnindex 12
#define t1 _p[13]
#define t1_columnindex 13
#define t2 _p[14]
#define t2_columnindex 14
#define t3 _p[15]
#define t3_columnindex 15
#define initflag _p[16]
#define initflag_columnindex 16
#define v _p[17]
#define v_columnindex 17
#define _g _p[18]
#define _g_columnindex 18
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  -1;
 static Datum* _extcall_thread;
 static Prop* _extcall_prop;
 /* external NEURON variables */
 /* declaration of user functions */
 static void _hoc_check(void);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static const char* nmodl_file_text;
static const char* nmodl_filename;
extern void hoc_reg_nmodl_text(int, const char*);
extern void hoc_reg_nmodl_filename(int, const char*);
#endif

 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _extcall_prop = _prop;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_pk", _hoc_setdata,
 "check_pk", _hoc_check,
 0, 0
};
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "tmin_pk", "ms",
 "vmin_pk", "mV",
 "tpeak_pk", "ms",
 "vpeak_pk", "mV",
 "dvdt_pk", "mV/ms",
 "d2vdt2_pk", "mV/ms2",
 "tdvdtpeak_pk", "ms",
 "dvdtpeak_pk", "mV/ms",
 "td2vdt2peak_pk", "ms",
 "d2vdt2peak_pk", "mV/ms2",
 0,0
};
 static double delta_t = 1;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(NrnThread*, _Memb_list*, int);
static void nrn_state(NrnThread*, _Memb_list*, int);
 static void nrn_cur(NrnThread*, _Memb_list*, int);
static void  nrn_jacob(NrnThread*, _Memb_list*, int);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"pk",
 "tmin_pk",
 "vmin_pk",
 0,
 "tpeak_pk",
 "vpeak_pk",
 "dvdt_pk",
 "d2vdt2_pk",
 "tdvdtpeak_pk",
 "dvdtpeak_pk",
 "td2vdt2peak_pk",
 "d2vdt2peak_pk",
 0,
 0,
 0};
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 19, _prop);
 	/*initialize range parameters*/
 	tmin = 0;
 	vmin = 0;
 	_prop->param = _p;
 	_prop->param_size = 19;
 
}
 static void _initlists();
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _peak_reg() {
	int _vectorized = 1;
  _initlists();
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 19, 0);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 pk /home/kurban/Documents/neuron_examples/alle_2009_135838/Alle_et_al_2009/peak.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "peak.mod";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int check(_threadargsproto_);
 
static int  check ( _threadargsproto_ ) {
   if ( v > vpeak ) {
     tpeak = t ;
     vpeak = v ;
     }
   v1 = v2 ;
   v2 = v3 ;
   v3 = v ;
   t1 = t2 ;
   t2 = t3 ;
   t3 = t ;
   if ( t3 - t2 > 0.0 ) {
     dvdt = ( v3 - v2 ) / ( t3 - t2 ) ;
     }
   if ( t3 - t2 > 0.0  && t2 - t1 > 0.0 ) {
     d2vdt2 = ( 2.0 * ( t3 * ( v2 - v1 ) + t2 * ( v1 - v3 ) + t1 * ( v3 - v2 ) ) ) / ( ( t1 - t2 ) * ( t1 - t3 ) * ( t2 - t3 ) ) ;
     }
   if ( v > vmin  && t > tmin ) {
     if ( dvdt > dvdtpeak ) {
       tdvdtpeak = t ;
       dvdtpeak = dvdt ;
       }
     if ( dvdt > 0.0  && d2vdt2 > d2vdt2peak ) {
       td2vdt2peak = t ;
       d2vdt2peak = d2vdt2 ;
       }
     }
    return 0; }
 
static void _hoc_check(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 check ( _p, _ppvar, _thread, _nt );
 hoc_retpushx(_r);
}

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
 {
   tpeak = 0.0 ;
   vpeak = - 100.0 ;
   v1 = 0.0 ;
   v2 = 0.0 ;
   v3 = 0.0 ;
   t1 = 0.0 ;
   t2 = 0.0 ;
   t3 = 0.0 ;
   initflag = 0.0 ;
   dvdt = 0.0 ;
   d2vdt2 = 0.0 ;
   tdvdtpeak = 0.0 ;
   dvdtpeak = 0.0 ;
   td2vdt2peak = 0.0 ;
   d2vdt2peak = 0.0 ;
   check ( _threadargs_ ) ;
   }
 
}
}

static void nrn_init(NrnThread* _nt, _Memb_list* _ml, int _type){
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
 initmodel(_p, _ppvar, _thread, _nt);
}
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _v){double _current=0.;v=_v;{
} return _current;
}

static void nrn_cur(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 
}
 
}

static void nrn_jacob(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}
 
}

static void nrn_state(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v=_v;
{
 {  { check(_p, _ppvar, _thread, _nt); }
  } {
   }
}}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/kurban/Documents/neuron_examples/alle_2009_135838/Alle_et_al_2009/peak.mod";
static const char* nmodl_file_text = 
  "TITLE peak.mod\n"
  "\n"
  "COMMENT\n"
  "\n"
  "pk: record peak time and peak value of membrane potential\n"
  "Arnd Roth 25.9.1997\n"
  "revised   10.9.2008\n"
  "\n"
  "ENDCOMMENT\n"
  "\n"
  "UNITS {\n"
  "	(mV) = (millivolt)\n"
  "}\n"
  "\n"
  "INDEPENDENT {t FROM 0 TO 1 WITH 1 (ms)}\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX pk\n"
  "	RANGE tmin, vmin\n"
  "	RANGE tpeak, vpeak\n"
  "	RANGE dvdt, d2vdt2, tdvdtpeak, dvdtpeak, td2vdt2peak, d2vdt2peak\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "	tmin	(ms)\n"
  "	vmin	(mV)\n"
  "	v	(mV)\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	tpeak	(ms)\n"
  "	vpeak	(mV)\n"
  "	v1	(mV)\n"
  "	v2	(mV)\n"
  "	v3	(mV)\n"
  "	t1	(ms)\n"
  "	t2	(ms)\n"
  "	t3	(ms)\n"
  "	initflag	(1)\n"
  "	dvdt	(mV/ms)\n"
  "	d2vdt2	(mV/ms2)\n"
  "	tdvdtpeak	(ms)\n"
  "	dvdtpeak	(mV/ms)\n"
  "	td2vdt2peak	(ms)\n"
  "	d2vdt2peak	(mV/ms2)\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	tpeak = 0	(ms)\n"
  "	vpeak = -100	(mV)\n"
  "	v1 = 0	(mV)\n"
  "	v2 = 0	(mV)\n"
  "	v3 = 0	(mV)\n"
  "	t1 = 0	(mV)\n"
  "	t2 = 0	(mV)\n"
  "	t3 = 0	(mV)\n"
  "	initflag = 0		(1)\n"
  "	dvdt = 0		(mV/ms)\n"
  "	d2vdt2 = 0		(mV/ms2)\n"
  "	tdvdtpeak = 0		(ms)\n"
  "	dvdtpeak = 0		(mV/ms)\n"
  "	td2vdt2peak = 0		(ms)\n"
  "	d2vdt2peak = 0		(mV/ms2)\n"
  "	check()\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE check METHOD after_cvode\n"
  "}\n"
  "\n"
  "PROCEDURE check() {\n"
  "	if (v > vpeak) {\n"
  "		tpeak = t\n"
  "		vpeak = v\n"
  "	}\n"
  "	v1 = v2\n"
  "	v2 = v3\n"
  "	v3 = v\n"
  "	t1 = t2\n"
  "	t2 = t3\n"
  "	t3 = t\n"
  "	if (t3 - t2 > 0) {\n"
  "		dvdt = (v3 - v2)/(t3 - t2)\n"
  "	}\n"
  "	if (t3 - t2 > 0 && t2 - t1 > 0) {\n"
  "		d2vdt2 = (2*(t3*(v2 - v1) + t2*(v1 - v3) + t1*(v3 - v2)))/((t1 - t2)*(t1 - t3)*(t2 - t3))\n"
  "	}\n"
  "	if (v > vmin && t > tmin) {\n"
  "		if (dvdt > dvdtpeak) {\n"
  "			tdvdtpeak = t\n"
  "			dvdtpeak = dvdt\n"
  "		}\n"
  "		if (dvdt > 0 && d2vdt2 > d2vdt2peak) {\n"
  "			td2vdt2peak = t\n"
  "			d2vdt2peak = d2vdt2\n"
  "		}\n"
  "	}\n"
  "}\n"
  ;
#endif
