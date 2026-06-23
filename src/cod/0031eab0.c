/* ee-2.9-991111 matched TU. */

extern double func_0031DE78(void *);

typedef enum { CLASS_SNAN, CLASS_QNAN, CLASS_ZERO, CLASS_NUMBER, CLASS_INFINITY } fp_class_type;
typedef long long DItype;
typedef unsigned long long UDItype;
typedef int SItype;
typedef struct {
  fp_class_type class;
  unsigned int sign;
  int normal_exp;
  union { DItype ll; SItype l[2]; } fraction;
} fp_number_type;

__attribute__((section(".text.func_0031EAB0")))
double func_0031EAB0(fp_class_type class, unsigned int sign, int exp, UDItype frac)
{
  fp_number_type in;
  in.class = class;
  in.sign = sign;
  in.normal_exp = exp;
  in.fraction.ll = frac;
  return func_0031DE78(&in);
}
