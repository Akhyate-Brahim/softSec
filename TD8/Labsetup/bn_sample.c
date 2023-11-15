#include <stdio.h>
#include <openssl/bn.h>

#define NBITS 256

void printBN(char *msg, BIGNUM * a)
{
   /* Use BN_bn2hex(a) for hex string
    * Use BN_bn2dec(a) for decimal string */
   char * number_str = BN_bn2hex(a);
   printf("%s %s\n", msg, number_str);
   OPENSSL_free(number_str);
}

int main ()
{
  BN_CTX *ctx = BN_CTX_new();

  BIGNUM *a = BN_new();
  BIGNUM *b = BN_new();
  BIGNUM *e = BN_new();
  BIGNUM *res = BN_new();


  // Initialize a, b, n
  BN_hex2bn(&a, "F7E75FDC469067FFDC4E847C51F452DF");
  BN_hex2bn(&b, "E85CED54AF57E53E092113E62F436F4F");
  BN_hex2bn(&e , "0D88C3");


  // calculate euler function of a and b
  BIGNUM *asub = BN_new();
  BIGNUM *bsub = BN_new();
  BIGNUM *phi = BN_new();
  BN_sub(asub, a, BN_value_one());
  BN_sub(bsub, b, BN_value_one());
  BN_mul(phi, asub, bsub, ctx);

  // Calculate d such that d*e ≡ 1 (mod phi)
  BIGNUM *d = BN_new();
  BN_mod_inverse(d, e, phi, ctx);

  printBN("the private key is ",d);

  return 0;
}

