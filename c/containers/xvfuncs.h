#ifndef XVFUNCS_H
#define XVFUNCS_H

// ================================================================
// Functions on extended values, namely, mlrvals/hashmaps.
// ================================================================

// xxx need memory-transfer semantics
// xxx make the xvfuncs API entirely in terms of boxed_xval_t's?

#include "../lib/mlrutil.h"
#include "../containers/mlhmmv.h"

// ----------------------------------------------------------------
typedef mlhmmv_xvalue_t xv_variadic_func_t(
	mlhmmv_xvalue_t* pxvals,
	int              nxvals);

typedef mlhmmv_xvalue_t xv_zary_func_t();

typedef mlhmmv_xvalue_t xv_unary_func_t(
	mlhmmv_xvalue_t* pxval1);

typedef mlhmmv_xvalue_t xv_binary_func_t(
	mlhmmv_xvalue_t* pxval1,
	mlhmmv_xvalue_t* pxval2);

// ----------------------------------------------------------------
static inline mlhmmv_xvalue_t b_x_ispresent_xfunc(mlhmmv_xvalue_t* pxval1) {
	return mlhmmv_xvalue_wrap_terminal(
		mv_from_bool(
			!pxval1->is_terminal || mv_is_present(&pxval1->terminal_mlrval)
		)
	);
}

static inline mlhmmv_xvalue_t b_x_isabsent_xfunc(mlhmmv_xvalue_t* pxval1) {
	return mlhmmv_xvalue_wrap_terminal(
		mv_from_bool(
			pxval1->is_terminal && mv_is_absent(&pxval1->terminal_mlrval)
		)
	);
}

static inline mlhmmv_xvalue_t b_x_ismap_xfunc(mlhmmv_xvalue_t* pxval1) {
	return mlhmmv_xvalue_wrap_terminal(
		mv_from_bool(
			!pxval1->is_terminal
		)
	);
}

static inline mlhmmv_xvalue_t b_x_isscalar_xfunc(mlhmmv_xvalue_t* pxval1) {
	return mlhmmv_xvalue_wrap_terminal(
		mv_from_bool(
			pxval1->is_terminal && mv_is_present(&pxval1->terminal_mlrval)
		)
	);
}

static inline mlhmmv_xvalue_t b_x_isnumeric_xfunc(mlhmmv_xvalue_t* pxval1) {
	return mlhmmv_xvalue_wrap_terminal(
		mv_from_bool(
			pxval1->is_terminal && mv_is_numeric(&pxval1->terminal_mlrval)
		)
	);
}

static inline mlhmmv_xvalue_t b_x_isint_xfunc(mlhmmv_xvalue_t* pxval1) {
	return mlhmmv_xvalue_wrap_terminal(
		mv_from_bool(
			pxval1->is_terminal && mv_is_int(&pxval1->terminal_mlrval)
		)
	);
}

static inline mlhmmv_xvalue_t b_x_isfloat_xfunc(mlhmmv_xvalue_t* pxval1) {
	return mlhmmv_xvalue_wrap_terminal(
		mv_from_bool(
			pxval1->is_terminal && mv_is_float(&pxval1->terminal_mlrval)
		)
	);
}

static inline mlhmmv_xvalue_t b_x_isboolean_xfunc(mlhmmv_xvalue_t* pxval1) {
	return mlhmmv_xvalue_wrap_terminal(
		mv_from_bool(
			pxval1->is_terminal && mv_is_boolean(&pxval1->terminal_mlrval)
		)
	);
}

static inline mlhmmv_xvalue_t b_x_isstring_xfunc(mlhmmv_xvalue_t* pxval1) {
	return mlhmmv_xvalue_wrap_terminal(
		mv_from_bool(
			pxval1->is_terminal && mv_is_string(&pxval1->terminal_mlrval)
		)
	);
}

static inline mlhmmv_xvalue_t b_x_isnull_xfunc(mlhmmv_xvalue_t* pxval1) {
	return mlhmmv_xvalue_wrap_terminal(
		mv_from_bool(
			pxval1->is_terminal && mv_is_null(&pxval1->terminal_mlrval)
		)
	);
}

static inline mlhmmv_xvalue_t b_x_isnotnull_xfunc(mlhmmv_xvalue_t* pxval1) {
	return mlhmmv_xvalue_wrap_terminal(
		mv_from_bool(
			!(pxval1->is_terminal && mv_is_null(&pxval1->terminal_mlrval))
		)
	);
}

static inline mlhmmv_xvalue_t b_x_isempty_xfunc(mlhmmv_xvalue_t* pxval1) {
	return mlhmmv_xvalue_wrap_terminal(
		mv_from_bool(
			pxval1->is_terminal && mv_is_empty(&pxval1->terminal_mlrval)
		)
	);
}

static inline mlhmmv_xvalue_t b_x_isnotempty_xfunc(mlhmmv_xvalue_t* pxval1) {
	return mlhmmv_xvalue_wrap_terminal(
		mv_from_bool(
			!(pxval1->is_terminal && mv_is_empty(&pxval1->terminal_mlrval))
		)
	);
}

static inline mlhmmv_xvalue_t b_x_isemptymap_xfunc(mlhmmv_xvalue_t* pxval1) {
	return mlhmmv_xvalue_wrap_terminal(
		mv_from_bool(
			!pxval1->is_terminal && pxval1->pnext_level->num_occupied == 0
		)
	);
}

static inline mlhmmv_xvalue_t b_x_isnotemptymap_xfunc(mlhmmv_xvalue_t* pxval1) {
	return mlhmmv_xvalue_wrap_terminal(
		mv_from_bool(
			pxval1->is_terminal || pxval1->pnext_level->num_occupied != 0
		)
	);
}

static inline mlhmmv_xvalue_t b_x_typeof_xfunc(mlhmmv_xvalue_t* pxval1) {
	return mlhmmv_xvalue_wrap_terminal(
	    mv_from_string(
			mlhmmv_xvalue_describe_type_simple(pxval1), NO_FREE
		)
	);
}

// ----------------------------------------------------------------
mlhmmv_xvalue_t b_x_haskey_xfunc(mlhmmv_xvalue_t* pmapval, mlhmmv_xvalue_t* pkeyval);

mlhmmv_xvalue_t b_x_length_xfunc(mlhmmv_xvalue_t* pxval1);

// xxx to do (non-inline):
//mlhmmv_xvalue_t i_m_depth_xfunc(mlhmmv_xvalue_t* pxval1);
//mlhmmv_xvalue_t i_m_deepcount_xfunc(mlhmmv_xvalue_t* pxval1);
//mlhmmv_xvalue_t m_mm_mapsum_xfunc(mlhmmv_xvalue_t* pxval1, mlhmmv_xvalue_t* pxval2);
//mlhmmv_xvalue_t m_mm_mapdiff_xfunc(mlhmmv_xvalue_t* pxval1, mlhmmv_xvalue_t* pxval2);
//mlhmmv_xvalue_t m_ss_split_xfunc(mlhmmv_xvalue_t* pxval1, mlhmmv_xvalue_t* pxval2);
//mlhmmv_xvalue_t s_ms_join_xfunc(mlhmmv_xvalue_t* pxval1, mlhmmv_xvalue_t* pxval2);

#endif // XVFUNCS_H
