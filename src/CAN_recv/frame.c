/* Linux standard headers */
#include <assert.h>

/* Optionally installed headers */
#include <jansson.h>

/* User defined headers */
#include "frame.h"

#define JSON_BUF_SIZE 1000

// void encode_bin(dt_frame *input, int output_num, char *output, int *output_len){
//   int out_idx = 0;
//
//   *(output+out_idx) = 0x00; /* Write DataKind */
//   assert((++out_idx) < output_num); /* Check out-of-bound*/
//
//   *(output+out_idx) = input->spd; /* Write DataKind */
//   assert((++out_idx) < output_num);
//
//   *(output+out_idx) = input->eng; /* Write DataKind */
//   assert((++out_idx) < output_num);
//
//   *(output+out_idx) = input->fuel_consumpt; /* Write DataKind */
//   assert((++out_idx) < output_num);
// }


/**
 * encode_json
 */
int encode_json(const dt_frame *input, int output_len, char *output, int *write_len){
  assert(input != NULL);
  assert(output != NULL);
  assert(output_len != NULL);

  json_t *jsondt = json_object();
  assert(jsondt != NULL);

  /* Get ready json_object */
  json_object_set_new(jsondt,"spd",json_integer((json_int_t)((int)input->spd)));
  json_object_set_new(jsondt,"eng",json_integer((json_int_t)((int)input->eng)));
  json_object_set_new(jsondt,"fuel_consumpt",json_integer((json_int_t)((int)(input->fuel_consumpt))));

  /* Write json */
  int size = json_dumpb((const json_t *)jsondt, output, output_len, JSON_ENCODE_ANY | JSON_COMPACT);
  if (size == 0){
    fprintf(stderr,"[ERR] Generating Json string failed.¥n");
    return -1;
  }

  *write_len = size;
}

/**
* main function
*/
int main(void){
  dt_frame dtfrm;
  char buf[JSON_BUF_SIZE] = {0};
  int output_len = 0;


  dtfrm.spd = (char)10;
  dtfrm.eng = (char)20;
  dtfrm.fuel_consumpt = (char)30;

  encode_json(&dtfrm,JSON_BUF_SIZE,buf,&output_len);

  printf(buf);
}
