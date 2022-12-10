/**
	norm_random_note
	tito scutari
*/
#define MAXAPI_USE_MSCRT

#include "ext.h"							// standard Max include, always required
#include "ext_obex.h"						// required for new style Max object
#include <math.h>
#include <stdlib.h>

////////////////////////// object struct
typedef struct _norm_random_note
{
	t_object ob;			// the object itself (must be first)
	double ft;
	double mu_1;
	double sigma_1;
	double mu_2;
	double sigma_2;
	void* m_outlet1;
} t_norm_random_note;

///////////////////////// function prototypes
void *norm_random_note_new();
void norm_random_note_free();

// inlets that call setters
void norm_random_note_ft1(t_norm_random_note* x, double f);
void norm_random_note_ft2(t_norm_random_note* x, double f);
void norm_random_note_ft3(t_norm_random_note* x, double f);
void norm_random_note_ft4(t_norm_random_note* x, double f);

// triggers
void norm_random_note_bang(t_norm_random_note* x);
void norm_random_note_float(t_norm_random_note* x, double f);

// setters
void set_mu_1(t_norm_random_note* x, double new_mu);
void set_sigma_1(t_norm_random_note* x, double new_sigma);
void set_mu_2(t_norm_random_note* x, double new_mu);
void set_sigma_2(t_norm_random_note* x, double new_sigma);

// utils
double randn(double mu, double sigma);
double random_note(t_norm_random_note* x);

//////////////////////// global class pointer variable
void *norm_random_note_class;

void ext_main(void *r)
{
	t_class *c;

	c = class_new("norm_random_note", (method)norm_random_note_new, (method)norm_random_note_free, (long)sizeof(t_norm_random_note),
				  0L /* leave NULL!! */, A_GIMME, 0);

	/* you CAN'T call this from the patcher */
	class_addmethod(c, (method)norm_random_note_bang, "bang", 0);
	class_addmethod(c, (method)norm_random_note_float, "float", A_FLOAT, 0);

	class_addmethod(c, (method)norm_random_note_ft1, "ft1", A_FLOAT, 0);
	class_addmethod(c, (method)norm_random_note_ft2, "ft2", A_FLOAT, 0);
	class_addmethod(c, (method)norm_random_note_ft3, "ft3", A_FLOAT, 0);
	class_addmethod(c, (method)norm_random_note_ft4, "ft4", A_FLOAT, 0);

	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	norm_random_note_class = c;
}

void norm_random_note_free(t_norm_random_note *x)
{
	;
}

void *norm_random_note_new()
{
	t_norm_random_note *x = (t_norm_random_note*)object_alloc(norm_random_note_class);
	x->m_outlet1 = floatout(x);
	floatin(x, 1);
	floatin(x, 2);
	floatin(x, 3);
	floatin(x, 4);

	x->ft = 1;
	x->mu_1 = 0;
	x->sigma_1 = 1;
	x->mu_2 = 0;
	x->sigma_2 = 1;
	return (x);
}

// inlets
void norm_random_note_ft1(t_norm_random_note* x, double f) {
	set_mu_1(x, f);
}
void norm_random_note_ft2(t_norm_random_note* x, double f) {
	set_sigma_1(x, f);
}
void norm_random_note_ft3(t_norm_random_note* x, double f) {
	set_mu_2(x, f);
}
void norm_random_note_ft4(t_norm_random_note* x, double f) {
	set_sigma_2(x, f);
}

// TRIGGERS
void norm_random_note_bang(t_norm_random_note* x) {
	outlet_float(x->m_outlet1, x->ft + random_note(x));
}

void norm_random_note_float(t_norm_random_note* x, double f) {
	x->ft = f;
	outlet_float(x->m_outlet1, x->ft + random_note(x));
}


// SETTERS
void set_mu_1(t_norm_random_note* x, double new_mu) {
	x->mu_1 = new_mu;
}
void set_sigma_1(t_norm_random_note* x, double new_sigma) {
	x->sigma_1 = new_sigma;
}
void set_mu_2(t_norm_random_note* x, double new_mu) {
	x->mu_2 = new_mu;
}
void set_sigma_2(t_norm_random_note* x, double new_sigma) {
	x->sigma_2 = new_sigma;
}


// lib tobe
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

double random_note(t_norm_random_note* x) {
	const double base = pow(2., (1. / 12.));
	
	double a = fmax(1.,ceil(randn(x->mu_1, x->sigma_1)));
	double b = fmax(1.,ceil(randn(x->mu_2, x->sigma_2)));

	double ratio = fabs(a / b);
	return round(log(ratio) / log(base));
}
