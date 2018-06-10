/******************************************************************************
 *
 * Copyright (C) 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *****************************************************************************
 * Originally developed and contributed by Ittiam Systems Pvt. Ltd, Bangalore
*/

#ifndef IMPD_ERROR_HANDLER_H
#define IMPD_ERROR_HANDLER_H

/*****************************************************************************/
/* File includes                                                             */
/*****************************************************************************/

/* these definitions are used by error handling function         */
/* the error handler will work on a structure which identifies a */
/* particular error with a module, context and error_code        */
/* within error_code, MSB identifies FATAL (1), NONFATAL (0)     */
/* next 4 ms_bs identify a class of error                        */

/*****************************************************************************/
/* Constant hash defines                                                     */
/*****************************************************************************/
#define IA_ERROR_NON_FATAL_IDX 0x0
#define IA_ERROR_FATAL_IDX 0x1

#define IA_ERROR_CLASS_0 0x0
#define IA_ERROR_CLASS_1 0x1
#define IA_ERROR_CLASS_2 0x2
#define IA_ERROR_CLASS_3 0x3
#define IA_ERROR_CLASS_4 0x4
#define IA_ERROR_CLASS_5 0x5
#define IA_ERROR_CLASS_6 0x6
#define IA_ERROR_CLASS_7 0x7
#define IA_ERROR_CLASS_8 0x8
#define IA_ERROR_CLASS_9 0x9
#define IA_ERROR_CLASS_A 0xA
#define IA_ERROR_CLASS_B 0xB
#define IA_ERROR_CLASS_C 0xC
#define IA_ERROR_CLASS_D 0xD
#define IA_ERROR_CLASS_E 0xE
#define IA_ERROR_CLASS_F 0xF

/* each module, hence, needs to copy the following structure          */
/* the first index is for FATAL/NONFATAL                              */
/* the second index is for the classes                                */
/* then in a module specific initialization, fill in the following    */
/* structure with the pointers to the particular error message arrays */

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/
typedef struct {
  pWORD8 pb_module_name;
  pWORD8 ppb_class_names[16];
  WORD8 **ppppb_error_msg_pointers[2][16];
} ia_error_info_struct;

/*****************************************************************************/
/* Function prototypes                                                       */
/*****************************************************************************/
/* this error handler maps the code generated by a module to a error string */
/* pb_context is a string to specify where the module broke                 */
IA_ERRORCODE ia_error_handler(ia_error_info_struct *p_mod_err_info,
                              WORD8 *pb_context, IA_ERRORCODE code);

/*****************************************************************************/
/* Macro functions                                                           */
/*****************************************************************************/
/* the following macro does a line job of returning back to the parent */
/* in case a fatal error occurs after calling the errorhandler         */
#define _IA_HANDLE_ERROR(p_mod_err_info, context, e)    \
  if ((e) != IA_NO_ERROR) {                             \
    ia_error_handler((p_mod_err_info), (context), (e)); \
    if ((e)&IA_FATAL_ERROR) return (e);                 \
  }

#endif
