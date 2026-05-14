#include "number.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include "mpdecimal.h"

int is_str_zero(const char* s) {
    if (!s || *s == '\0') return 1;
    
    // Ignora sinal
    if (*s == '-' || *s == '+') s++;
    
    int has_digits = 0;
    while (*s) {
        if (*s >= '1' && *s <= '9') return 0; // Tem número != 0
        if (*s >= '0' && *s <= '9') has_digits = 1;
        s++;
    }
    return has_digits; // Só é zero se tiver algum dígito e nenhum for 1-9
}

void setup_context(mpd_context_t *ctx, Number n1, Number n2, int force_low_prec) {
    mpd_maxcontext(ctx);
    
    if (force_low_prec) {
        ctx->prec = 1000;
    } else {

        size_t d1 = strlen(n1.number_str);
        size_t d2 = strlen(n2.number_str);
        ctx->prec = (d1 > d2 ? d1 : d2) + d2 + 2; 
        
        if (ctx->prec < 256) ctx->prec = 256;
        if (ctx->prec > MPD_MAX_PREC) ctx->prec = MPD_MAX_PREC;
    }
}

static Number finalize_number(mpd_t *result, mpd_context_t *ctx) {
    ctx->status &= ~MPD_Inexact;
    ctx->status &= ~MPD_Underflow;

    mpd_reduce(result, result, ctx);
    
    Number n;

    mpd_ssize_t exp = mpd_adjexp(result);

    if (exp <= 15 && exp >= -6) {
        n.number_str = mpd_to_sci(result, 0); 
    } else {
        n.number_str = mpd_to_sci(result, 1);
    }
    
    return n;
}


Number create_number(const char* value) {
    Number n;
    n.number_str = strdup(value); 
    
    if (n.number_str == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memória para o número.\n");
        exit(1);
    }
    
    return n;
}

Number nadd(Number num1, Number num2) {

    mpd_context_t ctx;
    setup_context(&ctx, num1, num2, 0);

    mpd_t *a = mpd_new(&ctx);
    mpd_t *b = mpd_new(&ctx);
    mpd_t *result = mpd_new(&ctx);

    mpd_set_string(a, num1.number_str, &ctx);
    mpd_set_string(b, num2.number_str, &ctx);

    mpd_add(result, a, b, &ctx);

    Number n = finalize_number(result, &ctx);

    mpd_del(a);
    mpd_del(b);
    mpd_del(result);

    return n;
}

Number nsub(Number num1, Number num2){
    mpd_context_t ctx;
    setup_context(&ctx, num1, num2, 0);

    mpd_t *a = mpd_new(&ctx);
    mpd_t *b = mpd_new(&ctx);
    mpd_t *result = mpd_new(&ctx);

    mpd_set_string(a, num1.number_str, &ctx);
    mpd_set_string(b, num2.number_str, &ctx);

    mpd_sub(result, a, b, &ctx);

    Number n = finalize_number(result, &ctx);

    mpd_del(a);
    mpd_del(b);
    mpd_del(result);

    return n;
}

Number nmult(Number num1, Number num2){
    mpd_context_t ctx;
    setup_context(&ctx, num1, num2, 0);

    mpd_t *a = mpd_new(&ctx);
    mpd_t *b = mpd_new(&ctx);
    mpd_t *result = mpd_new(&ctx);

    mpd_set_string(a, num1.number_str, &ctx);
    mpd_set_string(b, num2.number_str, &ctx);

    mpd_mul(result, a, b, &ctx);

    Number n = finalize_number(result, &ctx);

    mpd_del(a);
    mpd_del(b);
    mpd_del(result);

    return n;
}

Number ndiv(Number num1, Number num2){
    mpd_context_t ctx;
    setup_context(&ctx, num1, num2, 1);

    mpd_t *a = mpd_new(&ctx);
    mpd_t *b = mpd_new(&ctx);
    mpd_t *result = mpd_new(&ctx);

    mpd_set_string(a, num1.number_str, &ctx);
    mpd_set_string(b, num2.number_str, &ctx);

    mpd_div(result, a, b, &ctx);

    Number n = finalize_number(result, &ctx);

    mpd_del(a);
    mpd_del(b);
    mpd_del(result);

    return n;
}

Number nroot(Number num1, Number num2) {
    mpd_context_t ctx;
    setup_context(&ctx, num1, num2, 1);

    mpd_t *base = mpd_new(&ctx);
    mpd_t *indice = mpd_new(&ctx);
    mpd_t *result = mpd_new(&ctx);

    mpd_set_string(base, num2.number_str, &ctx);
    mpd_set_string(indice, num1.number_str, &ctx);

    if (mpd_iszero(indice)) {
        mpd_del(base); mpd_del(indice); mpd_del(result);
        return create_number("NaN");
    }
    
    if (mpd_isnegative(base)) {
        mpd_del(base); mpd_del(indice); mpd_del(result);
        return create_number("Error: Complex");
    }

    if (strcmp(num1.number_str, "2") == 0) {
        mpd_sqrt(result, base, &ctx);
    } else {
        mpd_t *one = mpd_new(&ctx);
        mpd_t *expoente = mpd_new(&ctx);
        mpd_set_string(one, "1", &ctx);

        mpd_div(expoente, one, indice, &ctx);
        mpd_pow(result, base, expoente, &ctx);

        mpd_del(one);
        mpd_del(expoente);
    }

    Number n = finalize_number(result, &ctx);

    mpd_del(base);
    mpd_del(indice);
    mpd_del(result);

    return n;
}

Number npow(Number num1, Number num2){
    mpd_context_t ctx;
    setup_context(&ctx, num1, num2, 1);

    mpd_t *a = mpd_new(&ctx);
    mpd_t *b = mpd_new(&ctx);
    mpd_t *result = mpd_new(&ctx);

    mpd_set_string(a, num1.number_str, &ctx);
    mpd_set_string(b, num2.number_str, &ctx);

    if (mpd_iszero(a) && mpd_iszero(b)) {
        mpd_del(a); mpd_del(b); mpd_del(result);
        return create_number("1");
    }

    mpd_pow(result, a, b, &ctx);

    Number n = finalize_number(result, &ctx);

    mpd_del(a);
    mpd_del(b);
    mpd_del(result);

    return n;
}

Number nexp(Number num1, Number num2) {
    mpd_context_t ctx;
    setup_context(&ctx, num1, num2, 0);
    ctx.traps = 0;
    ctx.status = 0;

    mpd_t *ten = mpd_new(&ctx);
    mpd_t *expoente = mpd_new(&ctx);
    mpd_t *num_original = mpd_new(&ctx);
    mpd_t *dez_elevado = mpd_new(&ctx);
    mpd_t *result = mpd_new(&ctx);

    mpd_set_string(ten, "10", &ctx);
    mpd_set_string(expoente, num2.number_str, &ctx);
    mpd_set_string(num_original, num1.number_str, &ctx);

    // 1. Faz 10 ^ num2
    mpd_pow(dez_elevado, ten, expoente, &ctx);
    
    // 2. Faz num1 * (10 ^ num2)
    mpd_mul(result, num_original, dez_elevado, &ctx);

    Number n = finalize_number(result, &ctx);

    mpd_del(ten); mpd_del(expoente); 
    mpd_del(num_original); mpd_del(dez_elevado); mpd_del(result);
    
    return n;
}
