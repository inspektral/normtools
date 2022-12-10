/**
	norm_rhythm
	tito scutari
*/
#define MAXAPI_USE_MSCRT

#include "ext.h"							// standard Max include, always required
#include "ext_obex.h"						// required for new style Max object
#include <stdlib.h>

////////////////////////// object struct
typedef struct _norm_rhythm
{
	t_object ob;			// the object itself (must be first)
	double mu;
	double sigma;
	double count;
	void* m_outlet1;
} t_norm_rhythm;

///////////////////////// function prototypes
void *norm_rhythm_new();
void norm_rhythm_free();
void norm_rhythm_ft1(t_norm_rhythm* x, double f);
void norm_rhythm_bang(t_norm_rhythm* x);
void norm_rhythm_mu(t_norm_rhythm* x, double new_mu);
void norm_rhythm_sigma(t_norm_rhythm* x, double new_sigma);
double randn(double mu, double sigma);

//////////////////////// global class pointer variable
void *norm_rhythm_class;


void ext_main(void *r)
{
	t_class *c;

	c = class_new("norm_rhythm", (method)norm_rhythm_new, (method)norm_rhythm_free, (long)sizeof(t_norm_rhythm),
				  0L /* leave NULL!! */, A_GIMME, 0);

	/* you CAN'T call this from the patcher */
	class_addmethod(c, (method)norm_rhythm_bang, "bang", 0);
	class_addmethod(c, (method)norm_rhythm_mu, "float", A_FLOAT, 0);
	class_addmethod(c, (method)norm_rhythm_ft1, "ft1", A_FLOAT, 0);

	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	norm_rhythm_class = c;
}

void norm_rhythm_free(t_norm_rhythm *x)
{
	;
}

void *norm_rhythm_new()
{
	t_norm_rhythm *x = (t_norm_rhythm*)object_alloc(norm_rhythm_class);
	x->m_outlet1 = bangout(x);
	floatin(x, 1);
	x->mu = 0;
	x->sigma = 1;
	x->count = 0;
	return (x);
}

void norm_rhythm_ft1(t_norm_rhythm* x, double f) {
	norm_rhythm_sigma(x,f);
}

void norm_rhythm_bang(t_norm_rhythm* x) {
	if (x->count == 0.0) {
		// TODO bang
		x->count = round(randn(x->mu, x->sigma));
	}
	else {
		x->count--;
	}
}

void norm_rhythm_mu(t_norm_rhythm* x, double new_mu) {
	x->mu = new_mu;
}

void norm_rhythm_sigma(t_norm_rhythm* x, double new_sigma) {
	x->sigma = new_sigma;
}

// tobe lib

double randn(double mu, double sigma) {
	double U1, U2, W, mult;
	static double X1, X2;
	static int call = 0;

	if (call == 1)
	{
		call = !call;
		return (mu + sigma * (double)X2);
	}

	do
	{
		U1 = -1 + ((double)rand() / RAND_MAX) * 2;
		U2 = -1 + ((double)rand() / RAND_MAX) * 2;
		W = pow(U1, 2) + pow(U2, 2);
	} while (W >= 1 || W == 0);

	mult = sqrt((-2 * log(W)) / W);
	X1 = U1 * mult;
	X2 = U2 * mult;

	call = !call;

	return (mu + sigma * (double)X1);
}
