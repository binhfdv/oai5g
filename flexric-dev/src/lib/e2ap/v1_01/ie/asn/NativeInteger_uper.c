/*
 * Copyright (c) 2017 Lev Walkin <vlm@lionet.info>.
 * All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#include <asn_internal.h>
#include <NativeInteger.h>

asn_dec_rval_t
NativeInteger_decode_uper_e2ap_v1_01(const asn_codec_ctx_t *opt_codec_ctx,
                          const asn_TYPE_descriptor_t *td,
                          const asn_per_constraints_t *constraints, void **sptr,
                          asn_per_data_t *pd) {
    const asn_INTEGER_specifics_t *specs =
        (const asn_INTEGER_specifics_t *)td->specifics;
    asn_dec_rval_t rval;
    long *native = (long *)*sptr;
    INTEGER_t tmpint;
    void *tmpintptr = &tmpint;

    (void)opt_codec_ctx;
    ASN_DEBUG("Decoding NativeInteger %s (UPER)", td->name);

    if(!native) {
        native = (long *)(*sptr = CALLOC(1, sizeof(*native)));
        if(!native) ASN__DECODE_FAILED;
    }

    memset(&tmpint, 0, sizeof tmpint);
    rval = INTEGER_decode_uper_e2ap_v1_01(opt_codec_ctx, td, constraints,
                               &tmpintptr, pd);
    if(rval.code == RC_OK) {
        if((specs&&specs->field_unsigned)
            ? asn_INTEGER2ulong_e2ap_v1_01(&tmpint, (unsigned long *)native)
            : asn_INTEGER2long_e2ap_v1_01(&tmpint, native))
            rval.code = RC_FAIL;
        else
            ASN_DEBUG("NativeInteger %s got value %ld",
                      td->name, *native);
    }
    ASN_STRUCT_FREE_CONTENTS_ONLY(asn_DEF_INTEGER_e2ap_v1_01, &tmpint);

    return rval;
}

asn_enc_rval_t
NativeInteger_encode_uper_e2ap_v1_01(const asn_TYPE_descriptor_t *td,
                          const asn_per_constraints_t *constraints,
                          const void *sptr, asn_per_outp_t *po) {
    const asn_INTEGER_specifics_t *specs =
        (const asn_INTEGER_specifics_t *)td->specifics;
    asn_enc_rval_t er = {0,0,0};
    long native;
    INTEGER_t tmpint;

    if(!sptr) ASN__ENCODE_FAILED;

    native = *(const long *)sptr;

    ASN_DEBUG("Encoding NativeInteger %s %ld (UPER)", td->name, native);

    memset(&tmpint, 0, sizeof(tmpint));
    if((specs&&specs->field_unsigned)
        ? asn_ulong2INTEGER_e2ap_v1_01(&tmpint, native)
        : asn_long2INTEGER_e2ap_v1_01(&tmpint, native))
        ASN__ENCODE_FAILED;
    er = INTEGER_encode_uper_e2ap_v1_01(td, constraints, &tmpint, po);
    ASN_STRUCT_FREE_CONTENTS_ONLY(asn_DEF_INTEGER_e2ap_v1_01, &tmpint);
    return er;
}
