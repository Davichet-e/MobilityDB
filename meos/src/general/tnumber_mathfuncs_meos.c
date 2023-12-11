/*****************************************************************************
 *
 * This MobilityDB code is provided under The PostgreSQL License.
 * Copyright (c) 2016-2023, Université libre de Bruxelles and MobilityDB
 * contributors
 *
 * MobilityDB includes portions of PostGIS version 3 source code released
 * under the GNU General Public License (GPLv2 or later).
 * Copyright (c) 2001-2023, PostGIS contributors
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without a written
 * agreement is hereby granted, provided that the above copyright notice and
 * this paragraph and the following two paragraphs appear in all copies.
 *
 * IN NO EVENT SHALL UNIVERSITE LIBRE DE BRUXELLES BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING
 * LOST PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
 * EVEN IF UNIVERSITE LIBRE DE BRUXELLES HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * UNIVERSITE LIBRE DE BRUXELLES SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE. THE SOFTWARE PROVIDED HEREUNDER IS ON
 * AN "AS IS" BASIS, AND UNIVERSITE LIBRE DE BRUXELLES HAS NO OBLIGATIONS TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 *
 *****************************************************************************/

/**
 * @file
 * @brief Mathematical operators (+, -, *, /) and functions (round, degrees, ...)
 * for temporal numbers.
 */

#include "general/tnumber_mathfuncs.h"

/* C */
#include <assert.h>
#include <math.h>
/* MEOS */
#include <meos.h>
#include "general/tnumber_mathfuncs.h"
#include "general/type_util.h"

/*****************************************************************************
 * Temporal addition
 *****************************************************************************/

/**
 * @ingroup libmeos_temporal_math
 * @brief Return the temporal addition of an integer and a temporal integer
 * @sql-cfn #Add_number_tnumber()
 */
Temporal *
add_int_tint(int i, const Temporal *temp)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) ||
      ! ensure_same_temporal_basetype(temp, T_INT4))
    return NULL;
  return arithop_tnumber_number(temp, Int32GetDatum(i), T_INT4, ADD,
    &datum_add, INVERT);
}

/**
 * @ingroup libmeos_temporal_math
 * @brief Return the temporal addition of a float and a temporal float
 * @sql-cfn #Add_number_tnumber()
 */
Temporal *
add_float_tfloat(double d, const Temporal *temp)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) ||
      ! ensure_same_temporal_basetype(temp, T_FLOAT8))
    return NULL;
  return arithop_tnumber_number(temp, Float8GetDatum(d), T_FLOAT8, ADD,
    &datum_add, INVERT);
}

/**
 * @ingroup libmeos_temporal_math
 * @brief Return the temporal addition of a temporal integer and an integer
 * @sql-cfn #Add_tnumber_number()
 */
Temporal *
add_tint_int(const Temporal *temp, int i)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) ||
      ! ensure_same_temporal_basetype(temp, T_INT4))
    return NULL;
  return arithop_tnumber_number(temp, Int32GetDatum(i), T_INT4, ADD,
    &datum_add, INVERT_NO);
}

/**
 * @ingroup libmeos_temporal_math
 * @brief Return the temporal addition of a temporal float and a float
 * @sql-cfn #Add_tnumber_number()
 */
Temporal *
add_tfloat_float(const Temporal *temp, double d)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) ||
      ! ensure_same_temporal_basetype(temp, T_FLOAT8))
    return NULL;
  return arithop_tnumber_number(temp, Float8GetDatum(d), T_FLOAT8, ADD,
    &datum_add, INVERT_NO);
}

/**
 * @ingroup libmeos_temporal_math
 * @brief Return the temporal addition of the temporal numbers
 * @sql-cfn #Add_tnumber_tnumber()
 */
Temporal *
add_tnumber_tnumber(const Temporal *temp1, const Temporal *temp2)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp1) || ! ensure_not_null((void *) temp2) ||
      ! ensure_tnumber_type(temp1->temptype) ||
      ! ensure_same_temporal_type(temp1, temp2))
    return NULL;
  return arithop_tnumber_tnumber(temp1, temp2, ADD, &datum_add, NULL);
}

/*****************************************************************************
 * Temporal subtraction
 *****************************************************************************/

/**
 * @ingroup libmeos_temporal_math
 * @brief Return the temporal subtraction of an integer and a temporal integer
 * @sql-cfn #Sub_number_tnumber()
 */
Temporal *
sub_int_tint(int i, const Temporal *temp)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) ||
      ! ensure_same_temporal_basetype(temp, T_INT4))
    return NULL;
  return arithop_tnumber_number(temp, Int32GetDatum(i), T_INT4, SUB,
    &datum_sub, INVERT);
}

/**
 * @ingroup libmeos_temporal_math
 * @brief Return the temporal subtraction of a float and a temporal float
 * @sql-cfn #Sub_number_tnumber()
 */
Temporal *
sub_float_tfloat(double d, const Temporal *temp)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) ||
      ! ensure_same_temporal_basetype(temp, T_FLOAT8))
    return NULL;
  return arithop_tnumber_number(temp, Float8GetDatum(d), T_FLOAT8, SUB,
    &datum_sub, INVERT);
}

/**
 * @ingroup libmeos_temporal_math
 * @brief Return the temporal subtraction of a temporal integer and an integer
 * @sql-cfn #Sub_tnumber_number()
 */
Temporal *
sub_tint_int(const Temporal *temp, int i)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) ||
      ! ensure_same_temporal_basetype(temp, T_INT4))
    return NULL;
  return arithop_tnumber_number(temp, Int32GetDatum(i), T_INT4, SUB,
    &datum_sub, INVERT_NO);
}

/**
 * @ingroup libmeos_temporal_math
 * @brief Return the temporal subtraction of a temporal float and a float
 * @sql-cfn #Sub_tnumber_number()
 */
Temporal *
sub_tfloat_float(const Temporal *temp, double d)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) ||
      ! ensure_same_temporal_basetype(temp, T_FLOAT8))
    return NULL;
  return arithop_tnumber_number(temp, Float8GetDatum(d), T_FLOAT8, SUB,
    &datum_sub, INVERT_NO);
}

/**
 * @ingroup libmeos_temporal_math
 * @brief Return the temporal subtraction of the temporal numbers
 * @sql-cfn #Sub_tnumber_tnumber()
 */
Temporal *
sub_tnumber_tnumber(const Temporal *temp1, const Temporal *temp2)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp1) || ! ensure_not_null((void *) temp2) ||
      ! ensure_tnumber_type(temp1->temptype) ||
      ! ensure_same_temporal_type(temp1, temp2))
    return NULL;
  return arithop_tnumber_tnumber(temp1, temp2, SUB, &datum_sub, NULL);
}

/*****************************************************************************
 * Temporal multiplication
 *****************************************************************************/

/**
 * @ingroup libmeos_temporal_math
 * @brief Return the temporal multiplication of an integer and a temporal integer
 * @sql-cfn #Mult_number_tnumber()
 */
Temporal *
mult_int_tint(int i, const Temporal *temp)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) ||
      ! ensure_same_temporal_basetype(temp, T_INT4))
    return NULL;
  return arithop_tnumber_number(temp, Int32GetDatum(i), T_INT4, MULT,
    &datum_mult, INVERT);
}

/**
 * @ingroup libmeos_temporal_math
 * @brief Return the temporal multiplication of a float and a temporal float
 * @sql-cfn #Mult_number_tnumber()
 */
Temporal *
mult_float_tfloat(double d, const Temporal *temp)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) ||
      ! ensure_same_temporal_basetype(temp, T_FLOAT8))
    return NULL;
  return arithop_tnumber_number(temp, Float8GetDatum(d), T_FLOAT8, MULT,
    &datum_mult, INVERT);
}

/**
 * @ingroup libmeos_temporal_math
 * @brief Return the temporal multiplication of a temporal integer and an integer
 * @sql-cfn #Mult_tnumber_number()
 */
Temporal *
mult_tint_int(const Temporal *temp, int i)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) ||
      ! ensure_same_temporal_basetype(temp, T_INT4))
    return NULL;
  return arithop_tnumber_number(temp, Int32GetDatum(i), T_INT4, MULT,
    &datum_mult, INVERT_NO);
}

/**
 * @ingroup libmeos_temporal_math
 * @brief Return the temporal multiplication of a temporal float and a float
 * @sql-cfn #Mult_tnumber_number()
 */
Temporal *
mult_tfloat_float(const Temporal *temp, double d)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) ||
      ! ensure_same_temporal_basetype(temp, T_FLOAT8))
    return NULL;
  return arithop_tnumber_number(temp, Float8GetDatum(d), T_FLOAT8, MULT,
    &datum_mult, INVERT_NO);
}

/**
 * @ingroup libmeos_temporal_math
 * @brief Return the temporal multiplication of the temporal numbers
 * @sql-cfn #Mult_tnumber_tnumber()
 */
Temporal *
mult_tnumber_tnumber(const Temporal *temp1, const Temporal *temp2)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp1) || ! ensure_not_null((void *) temp2) ||
      ! ensure_tnumber_type(temp1->temptype) ||
      ! ensure_same_temporal_type(temp1, temp2))
    return NULL;
  return arithop_tnumber_tnumber(temp1, temp2, MULT, &datum_mult,
    &tnumber_mult_tp_at_timestamptz);
}

/*****************************************************************************
 * Temporal division
 *****************************************************************************/

/**
 * @ingroup libmeos_temporal_math
 * @brief Return the temporal division of an integer and a temporal integer
 * @sql-cfn #Div_number_tnumber()
 */
Temporal *
div_int_tint(int i, const Temporal *temp)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) ||
      ! ensure_same_temporal_basetype(temp, T_INT4))
    return NULL;
  return arithop_tnumber_number(temp, Int32GetDatum(i), T_INT4, DIV,
    &datum_div, INVERT);
}

/**
 * @ingroup libmeos_temporal_math
 * @brief Return the temporal division of a float and a temporal float
 * @sql-cfn #Div_number_tnumber()
 */
Temporal *
div_float_tfloat(double d, const Temporal *temp)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) ||
      ! ensure_same_temporal_basetype(temp, T_FLOAT8))
    return NULL;
  return arithop_tnumber_number(temp, Float8GetDatum(d), T_FLOAT8, DIV,
    &datum_div, INVERT);
}

/**
 * @ingroup libmeos_temporal_math
 * @brief Return the temporal division of a temporal integer and an integer
 */
Temporal *
div_tint_int(const Temporal *temp, int i)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) ||
      ! ensure_same_temporal_basetype(temp, T_INT4))
    return NULL;
  return arithop_tnumber_number(temp, Int32GetDatum(i), T_INT4, DIV,
    &datum_div, INVERT_NO);
}

/**
 * @ingroup libmeos_temporal_math
 * @brief Return the temporal division of a temporal float and a float
 * @sql-cfn #Div_tnumber_number()
 */
Temporal *
div_tfloat_float(const Temporal *temp, double d)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp) ||
      ! ensure_same_temporal_basetype(temp, T_FLOAT8))
    return NULL;
  return arithop_tnumber_number(temp, Float8GetDatum(d), T_FLOAT8, DIV,
    &datum_div, INVERT_NO);
}

/**
 * @ingroup libmeos_temporal_math
 * @brief Return the temporal division of the temporal numbers
 * @sql-cfn #Div_tnumber_tnumber()
 */
Temporal *
div_tnumber_tnumber(const Temporal *temp1, const Temporal *temp2)
{
  /* Ensure validity of the arguments */
  if (! ensure_not_null((void *) temp1) || ! ensure_not_null((void *) temp2) ||
      ! ensure_tnumber_type(temp1->temptype) ||
      ! ensure_same_temporal_type(temp1, temp2))
    return NULL;
  return arithop_tnumber_tnumber(temp1, temp2, DIV, &datum_div,
    &tnumber_div_tp_at_timestamptz);
}

/*****************************************************************************/
