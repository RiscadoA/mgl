#include <mgl/string/conversion.h>

mgl_error_t MGL_API mgl_u8_to_str(mgl_u8_t * buffer, mgl_u64_t buffer_size, mgl_u8_t value, mgl_u8_t base, mgl_u64_t * out_size)
{
	MGL_DEBUG_ASSERT(buffer != NULL && base >= 2 && base <= 16);

	static const mgl_u8_t characters[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

	for (mgl_u64_t i = 0;; ++i)
	{
		// Buffer end reached
		if (i == buffer_size)
		{
			if (out_size != NULL)
				*out_size = i;
			return MGL_ERROR_EOF;
		}

		buffer[i] = characters[value % base];
		value /= base;

		// Finished
		if (value <= 0)
		{
			// Reverse string
			for (mgl_u64_t j = 0; j < i + 1; ++j)
			{
				if (j >= i - j)
					break;
				mgl_u8_t temp = buffer[j];
				buffer[j] = buffer[i - j];
				buffer[i - j] = temp;
			}

			if (out_size != NULL)
				*out_size = i + 1;
			return MGL_ERROR_NONE;
		}
	}
}

mgl_error_t MGL_API mgl_u16_to_str(mgl_u8_t * buffer, mgl_u64_t buffer_size, mgl_u16_t value, mgl_u8_t base, mgl_u64_t * out_size)
{
	MGL_DEBUG_ASSERT(buffer != NULL && base >= 2 && base <= 16);

	static const mgl_u8_t characters[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

	for (mgl_u64_t i = 0;; ++i)
	{
		// Buffer end reached
		if (i == buffer_size)
		{
			if (out_size != NULL)
				*out_size = i;
			return MGL_ERROR_EOF;
		}

		buffer[i] = characters[value % base];
		value /= base;

		// Finished
		if (value <= 0)
		{
			// Reverse string
			for (mgl_u64_t j = 0; j < i + 1; ++j)
			{
				if (j >= i - j)
					break;
				mgl_u8_t temp = buffer[j];
				buffer[j] = buffer[i - j];
				buffer[i - j] = temp;
			}

			if (out_size != NULL)
				*out_size = i + 1;
			return MGL_ERROR_NONE;
		}
	}
}

mgl_error_t MGL_API mgl_u32_to_str(mgl_u8_t * buffer, mgl_u64_t buffer_size, mgl_u32_t value, mgl_u8_t base, mgl_u64_t * out_size)
{
	MGL_DEBUG_ASSERT(buffer != NULL && base >= 2 && base <= 16);

	static const mgl_u8_t characters[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

	for (mgl_u64_t i = 0;; ++i)
	{
		// Buffer end reached
		if (i == buffer_size)
		{
			if (out_size != NULL)
				*out_size = i;
			return MGL_ERROR_EOF;
		}

		buffer[i] = characters[value % base];
		value /= base;

		// Finished
		if (value <= 0)
		{
			// Reverse string
			for (mgl_u64_t j = 0; j < i + 1; ++j)
			{
				if (j >= i - j)
					break;
				mgl_u8_t temp = buffer[j];
				buffer[j] = buffer[i - j];
				buffer[i - j] = temp;
			}

			if (out_size != NULL)
				*out_size = i + 1;
			return MGL_ERROR_NONE;
		}
	}
}

mgl_error_t MGL_API mgl_u64_to_str(mgl_u8_t * buffer, mgl_u64_t buffer_size, mgl_u64_t value, mgl_u8_t base, mgl_u64_t * out_size)
{
	MGL_DEBUG_ASSERT(buffer != NULL && base >= 2 && base <= 16);

	static const mgl_u8_t characters[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

	for (mgl_u64_t i = 0;; ++i)
	{
		// Buffer end reached
		if (i == buffer_size)
		{
			if (out_size != NULL)
				*out_size = i;
			return MGL_ERROR_EOF;
		}

		buffer[i] = characters[value % base];
		value /= base;

		// Finished
		if (value <= 0)
		{
			// Reverse string
			for (mgl_u64_t j = 0; j < i + 1; ++j)
			{
				if (j >= i - j)
					break;
				mgl_u8_t temp = buffer[j];
				buffer[j] = buffer[i - j];
				buffer[i - j] = temp;
			}

			if (out_size != NULL)
				*out_size = i + 1;
			return MGL_ERROR_NONE;
		}
	}
}

mgl_error_t MGL_API mgl_i8_to_str(mgl_u8_t * buffer, mgl_u64_t buffer_size, mgl_i8_t value, mgl_u8_t base, mgl_u64_t * out_size)
{
	MGL_DEBUG_ASSERT(buffer != NULL && base >= 2 && base <= 16);

	static const mgl_u8_t characters[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

	mgl_bool_t negative = (value < 0) ? MGL_TRUE : MGL_FALSE;

	for (mgl_u64_t i = 0;; ++i)
	{
		if (i == 0 && negative != MGL_FALSE)
		{
			buffer[0] = '-';
			value = -value;
			continue;
		}

		// Buffer end reached
		if (i == buffer_size)
		{
			if (out_size != NULL)
				*out_size = i;
			return MGL_ERROR_EOF;
		}

		buffer[i] = characters[value % base];
		value /= base;

		// Finished
		if (value <= 0)
		{
			// Reverse string
			if (negative == MGL_FALSE)
				for (mgl_u64_t j = 0; j < i + 1; ++j)
				{
					if (j >= i - j)
						break;
					mgl_u8_t temp = buffer[j];
					buffer[j] = buffer[i - j];
					buffer[i - j] = temp;
				}
			else
				for (mgl_u64_t j = 1; j < i + 2; ++j)
				{
					if (j >= i - j + 1)
						break;
					mgl_u8_t temp = buffer[j];
					buffer[j] = buffer[i - j + 1];
					buffer[i - j + 1] = temp;
				}

			if (out_size != NULL)
				*out_size = i + 1;
			return MGL_ERROR_NONE;
		}
	}
}

mgl_error_t MGL_API mgl_i16_to_str(mgl_u8_t * buffer, mgl_u64_t buffer_size, mgl_i16_t value, mgl_u8_t base, mgl_u64_t * out_size)
{
	MGL_DEBUG_ASSERT(buffer != NULL && base >= 2 && base <= 16);

	static const mgl_u8_t characters[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

	mgl_bool_t negative = (value < 0) ? MGL_TRUE : MGL_FALSE;

	for (mgl_u64_t i = 0;; ++i)
	{
		if (i == 0 && negative != MGL_FALSE)
		{
			buffer[0] = '-';
			value = -value;
			continue;
		}

		// Buffer end reached
		if (i == buffer_size)
		{
			if (out_size != NULL)
				*out_size = i;
			return MGL_ERROR_EOF;
		}

		buffer[i] = characters[value % base];
		value /= base;

		// Finished
		if (value <= 0)
		{
			// Reverse string
			if (negative == MGL_FALSE)
				for (mgl_u64_t j = 0; j < i + 1; ++j)
				{
					if (j >= i - j)
						break;
					mgl_u8_t temp = buffer[j];
					buffer[j] = buffer[i - j];
					buffer[i - j] = temp;
				}
			else
				for (mgl_u64_t j = 1; j < i + 2; ++j)
				{
					if (j >= i - j + 1)
						break;
					mgl_u8_t temp = buffer[j];
					buffer[j] = buffer[i - j + 1];
					buffer[i - j + 1] = temp;
				}

			if (out_size != NULL)
				*out_size = i + 1;
			return MGL_ERROR_NONE;
		}
	}
}

mgl_error_t MGL_API mgl_i32_to_str(mgl_u8_t * buffer, mgl_u64_t buffer_size, mgl_i32_t value, mgl_u8_t base, mgl_u64_t * out_size)
{
	MGL_DEBUG_ASSERT(buffer != NULL && base >= 2 && base <= 16);

	static const mgl_u8_t characters[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

	mgl_bool_t negative = (value < 0) ? MGL_TRUE : MGL_FALSE;

	for (mgl_u64_t i = 0;; ++i)
	{
		if (i == 0 && negative != MGL_FALSE)
		{
			buffer[0] = '-';
			value = -value;
			continue;
		}

		// Buffer end reached
		if (i == buffer_size)
		{
			if (out_size != NULL)
				*out_size = i;
			return MGL_ERROR_EOF;
		}

		buffer[i] = characters[value % base];
		value /= base;

		// Finished
		if (value <= 0)
		{
			// Reverse string
			if (negative == MGL_FALSE)
				for (mgl_u64_t j = 0; j < i + 1; ++j)
				{
					if (j >= i - j)
						break;
					mgl_u8_t temp = buffer[j];
					buffer[j] = buffer[i - j];
					buffer[i - j] = temp;
				}
			else
				for (mgl_u64_t j = 1; j < i + 2; ++j)
				{
					if (j >= i - j + 1)
						break;
					mgl_u8_t temp = buffer[j];
					buffer[j] = buffer[i - j + 1];
					buffer[i - j + 1] = temp;
				}

			if (out_size != NULL)
				*out_size = i + 1;
			return MGL_ERROR_NONE;
		}
	}
}

mgl_error_t MGL_API mgl_i64_to_str(mgl_u8_t * buffer, mgl_u64_t buffer_size, mgl_i64_t value, mgl_u8_t base, mgl_u64_t * out_size)
{
	MGL_DEBUG_ASSERT(buffer != NULL && base >= 2 && base <= 16);

	static const mgl_u8_t characters[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

	mgl_bool_t negative = (value < 0) ? MGL_TRUE : MGL_FALSE;

	for (mgl_u64_t i = 0;; ++i)
	{
		if (i == 0 && negative != MGL_FALSE)
		{
			buffer[0] = '-';
			value = -value;
			continue;
		}

		// Buffer end reached
		if (i == buffer_size)
		{
			if (out_size != NULL)
				*out_size = i;
			return MGL_ERROR_EOF;
		}

		buffer[i] = characters[value % base];
		value /= base;

		// Finished
		if (value <= 0)
		{
			// Reverse string
			if (negative == MGL_FALSE)
				for (mgl_u64_t j = 0; j < i + 1; ++j)
				{
					if (j >= i - j)
						break;
					mgl_u8_t temp = buffer[j];
					buffer[j] = buffer[i - j];
					buffer[i - j] = temp;
				}
			else
				for (mgl_u64_t j = 1; j < i + 2; ++j)
				{
					if (j >= i - j + 1)
						break;
					mgl_u8_t temp = buffer[j];
					buffer[j] = buffer[i - j + 1];
					buffer[i - j + 1] = temp;
				}

			if (out_size != NULL)
				*out_size = i + 1;
			return MGL_ERROR_NONE;
		}
	}
}

mgl_error_t MGL_API mgl_f32_to_str(mgl_u8_t * buffer, mgl_u64_t buffer_size, mgl_f32_t value, mgl_u8_t base, mgl_u64_t decimal_places, mgl_u64_t * out_size)
{
	MGL_DEBUG_ASSERT(buffer != NULL && base >= 2 && base <= 16);

	if (value == MGL_F32_INFINITY)
	{
		buffer[0] = 'I';

		if (buffer_size <= 1)
		{
			if (out_size != NULL)
				*out_size = 1;
			return MGL_ERROR_EOF;
		}
		buffer[1] = 'N';

		if (buffer_size <= 2)
		{
			if (out_size != NULL)
				*out_size = 2;
			return MGL_ERROR_EOF;
		}
		buffer[2] = 'F';
	}
	else if (value == -MGL_F32_INFINITY)
	{
		buffer[0] = '-';

		if (buffer_size <= 1)
		{
			if (out_size != NULL)
				*out_size = 1;
			return MGL_ERROR_EOF;
		}
		buffer[1] = 'I';

		if (buffer_size <= 2)
		{
			if (out_size != NULL)
				*out_size = 2;
			return MGL_ERROR_EOF;
		}
		buffer[2] = 'N';

		if (buffer_size <= 3)
		{
			if (out_size != NULL)
				*out_size = 3;
			return MGL_ERROR_EOF;
		}
		buffer[3] = 'F';
	}
	else if (value != value)
	{
		buffer[0] = 'N';

		if (buffer_size <= 1)
		{
			if (out_size != NULL)
				*out_size = 1;
			return MGL_ERROR_EOF;
		}
		buffer[1] = 'A';

		if (buffer_size <= 2)
		{
			if (out_size != NULL)
				*out_size = 2;
			return MGL_ERROR_EOF;
		}
		buffer[2] = 'N';
	}
	else if (value >= 0.0f && value <= 16777217.0f)
	{
		mgl_f32_t integerPartF = 0.0f;
		mgl_f32_t decimalPartF = modff(value, &integerPartF);
		mgl_u64_t integerPart = (mgl_u64_t)round(integerPartF);
		mgl_u64_t decimalPart = (mgl_u64_t)round(decimalPartF * pow(10, (double)decimal_places));

		mgl_error_t err;
		mgl_u64_t index = 0;
		mgl_u64_t size = 0;

		// Print integer part
		err = mgl_u64_to_str(buffer + index, buffer_size - index, integerPart, base, &size);
		index += size;
		if (err != MGL_ERROR_NONE)
		{
			if (out_size != NULL)
				*out_size = index;
			return err;
		}

		if (decimal_places > 0)
		{
			// Print dot
			if (buffer_size - index < 1)
			{
				if (out_size != NULL)
					*out_size = index;
				return MGL_ERROR_EOF;
			}
			buffer[index] = '.';
			++index;


			// Count leading zeroes of fractional part
			mgl_u32_t leadingZeroes = 0;
			{
				mgl_f32_t leadingZeroesProbe = decimalPartF;
				leadingZeroesProbe *= base;
				while (leadingZeroesProbe < 1.0f && leadingZeroesProbe != 0.0f)
				{
					leadingZeroesProbe *= base;
					++leadingZeroes;
				}
			}

			// Print leading zeros
			for (mgl_u32_t i = 0; i < leadingZeroes; ++i)
			{
				if (buffer_size - index < 1)
				{
					if (out_size != NULL)
						*out_size = index;
					return MGL_ERROR_EOF;
				}
				buffer[index] = '0';
				++index;
			}

			// Print fractional part
			err = mgl_u64_to_str(buffer + index, buffer_size - index, decimalPart, base, &size);
			index += size;
			size += leadingZeroes;
			if (err != MGL_ERROR_NONE)
			{
				if (out_size != NULL)
					*out_size = index;
				return err;
			}
			if (size < decimal_places)
			{
				while (size != decimal_places)
				{
					if (buffer_size - index < 1)
					{
						if (out_size != NULL)
							*out_size = index;
						return MGL_ERROR_EOF;
					}
					buffer[index] = '0';
					++index;
					++size;
				}
			}
		}

		if (out_size != NULL)
			*out_size = index;
	}
	else if (value < 0.0f && -value <= 16777217.0f)
	{
		mgl_f32_t integerPartF = 0.0f;
		mgl_f32_t decimalPartF = modff(-value, &integerPartF);
		mgl_u64_t integerPart = (mgl_u64_t)round(integerPartF);
		mgl_u64_t decimalPart = (mgl_u64_t)round(decimalPartF * pow(10, (double)decimal_places));

		mgl_error_t err;
		mgl_u64_t index = 0;
		mgl_u64_t size = 0;

		// Print dash
		if (buffer_size - index < 1)
		{
			if (out_size != NULL)
				*out_size = index;
			return MGL_ERROR_EOF;
		}
		buffer[index] = '-';
		++index;

		// Print integer part
		err = mgl_u64_to_str(buffer + index, buffer_size - index, integerPart, base, &size);
		index += size;
		if (err != MGL_ERROR_NONE)
		{
			if (out_size != NULL)
				*out_size = index;
			return err;
		}

		if (decimal_places > 0)
		{
			// Print dot
			if (buffer_size - index < 1)
			{
				if (out_size != NULL)
					*out_size = index;
				return MGL_ERROR_EOF;
			}
			buffer[index] = '.';
			++index;

			// Count leading zeroes of fractional part
			mgl_u32_t leadingZeroes = 0;
			{
				mgl_f32_t leadingZeroesProbe = decimalPartF;
				leadingZeroesProbe *= base;
				while (leadingZeroesProbe < 1.0f && leadingZeroesProbe != 0.0f)
				{
					leadingZeroesProbe *= base;
					++leadingZeroes;
				}
			}

			// Print leading zeros
			for (mgl_u32_t i = 0; i < leadingZeroes; ++i)
			{
				if (buffer_size - index < 1)
				{
					if (out_size != NULL)
						*out_size = index;
					return MGL_ERROR_EOF;
				}
				buffer[index] = '0';
				++index;
			}

			// Print fractional part
			err = mgl_u64_to_str(buffer + index, buffer_size - index, decimalPart, base, &size);
			index += size;
			size += leadingZeroes;
			if (err != MGL_ERROR_NONE)
			{
				if (out_size != NULL)
					*out_size = index;
				return err;
			}
			if (size < decimal_places)
			{
				while (size != decimal_places)
				{
					if (buffer_size - index < 1)
					{
						if (out_size != NULL)
							*out_size = index;
						return MGL_ERROR_EOF;
					}
					buffer[index] = '0';
					++index;
					++size;
				}
			}
		}

		if (out_size != NULL)
			*out_size = index;
	}
	else
	{
		// Print as exponent
		mgl_i32_t exp = (mgl_i32_t)floor(log10(fabs(value)));
		mgl_f32_t fractional = (mgl_f32_t)(value / pow(10, exp));

		if (fractional >= 10.0f)
		{
			++exp;
			fractional /= 10.0f;
		}
		else if (fractional <= 0.1f)
		{
			--exp;
			fractional *= 10.0f;
		}

		mgl_error_t err;
		mgl_u64_t index = 0;
		mgl_u64_t size = 0;

		// Print fractional part
		err = mgl_u64_to_str(buffer + index, buffer_size - index, (mgl_u64_t)fractional, base, &size);
		index += size;
		if (err != MGL_ERROR_NONE)
		{
			if (out_size != NULL)
				*out_size = index;
			return err;
		}

		// Print exponent
		if (buffer_size - index < 1)
		{
			if (out_size != NULL)
				*out_size = index;
			return MGL_ERROR_EOF;
		}
		buffer[index] = 'E';
		++index;

		if (exp > 0)
		{
			if (buffer_size - index < 1)
			{
				if (out_size != NULL)
					*out_size = index;
				return MGL_ERROR_EOF;
			}
			buffer[index] = '+';
			++index;
		}

		err = mgl_u64_to_str(buffer + index, buffer_size - index, exp, base, &size);
		index += size;
		if (err != MGL_ERROR_NONE)
		{
			if (out_size != NULL)
				*out_size = index;
			return err;
		}

		if (out_size != NULL)
			*out_size = index;
	}

	return MGL_ERROR_NONE;
}

mgl_error_t MGL_API mgl_f64_to_str(mgl_u8_t * buffer, mgl_u64_t buffer_size, mgl_f64_t value, mgl_u8_t base, mgl_u64_t decimal_places, mgl_u64_t * out_size)
{
	MGL_DEBUG_ASSERT(buffer != NULL && base >= 2 && base <= 16);

	if (value == MGL_F32_INFINITY)
	{
		buffer[0] = 'I';

		if (buffer_size <= 1)
		{
			if (out_size != NULL)
				*out_size = 1;
			return MGL_ERROR_EOF;
		}
		buffer[1] = 'N';

		if (buffer_size <= 2)
		{
			if (out_size != NULL)
				*out_size = 2;
			return MGL_ERROR_EOF;
		}
		buffer[2] = 'F';
	}
	else if (value == -MGL_F32_INFINITY)
	{
		buffer[0] = '-';

		if (buffer_size <= 1)
		{
			if (out_size != NULL)
				*out_size = 1;
			return MGL_ERROR_EOF;
		}
		buffer[1] = 'I';

		if (buffer_size <= 2)
		{
			if (out_size != NULL)
				*out_size = 2;
			return MGL_ERROR_EOF;
		}
		buffer[2] = 'N';

		if (buffer_size <= 3)
		{
			if (out_size != NULL)
				*out_size = 3;
			return MGL_ERROR_EOF;
		}
		buffer[3] = 'F';
	}
	else if (value != value)
	{
		buffer[0] = 'N';

		if (buffer_size <= 1)
		{
			if (out_size != NULL)
				*out_size = 1;
			return MGL_ERROR_EOF;
		}
		buffer[1] = 'A';

		if (buffer_size <= 2)
		{
			if (out_size != NULL)
				*out_size = 2;
			return MGL_ERROR_EOF;
		}
		buffer[2] = 'N';
	}
	else if (value >= 0.0f && value <= 16777217.0f)
	{
		mgl_f64_t integerPartF = 0.0f;
		mgl_f64_t decimalPartF = modf(value, &integerPartF);
		mgl_u64_t integerPart = (mgl_u64_t)round(integerPartF);
		mgl_u64_t decimalPart = (mgl_u64_t)round(decimalPartF * pow(10, (double)decimal_places));

		mgl_error_t err;
		mgl_u64_t index = 0;
		mgl_u64_t size = 0;

		// Print integer part
		err = mgl_u64_to_str(buffer + index, buffer_size - index, integerPart, base, &size);
		index += size;
		if (err != MGL_ERROR_NONE)
		{
			if (out_size != NULL)
				*out_size = index;
			return err;
		}

		if (decimal_places > 0)
		{
			// Print dot
			if (buffer_size - index < 1)
			{
				if (out_size != NULL)
					*out_size = index;
				return MGL_ERROR_EOF;
			}
			buffer[index] = '.';
			++index;


			// Count leading zeroes of fractional part
			mgl_u32_t leadingZeroes = 0;
			{
				mgl_f64_t leadingZeroesProbe = decimalPartF;
				leadingZeroesProbe *= base;
				while (leadingZeroesProbe < 1.0f && leadingZeroesProbe != 0.0f)
				{
					leadingZeroesProbe *= base;
					++leadingZeroes;
				}
			}

			// Print leading zeros
			for (mgl_u32_t i = 0; i < leadingZeroes; ++i)
			{
				if (buffer_size - index < 1)
				{
					if (out_size != NULL)
						*out_size = index;
					return MGL_ERROR_EOF;
				}
				buffer[index] = '0';
				++index;
			}

			// Print fractional part
			err = mgl_u64_to_str(buffer + index, buffer_size - index, decimalPart, base, &size);
			index += size;
			size += leadingZeroes;
			if (err != MGL_ERROR_NONE)
			{
				if (out_size != NULL)
					*out_size = index;
				return err;
			}
			if (size < decimal_places)
			{
				while (size != decimal_places)
				{
					if (buffer_size - index < 1)
					{
						if (out_size != NULL)
							*out_size = index;
						return MGL_ERROR_EOF;
					}
					buffer[index] = '0';
					++index;
					++size;
				}
			}
		}

		if (out_size != NULL)
			*out_size = index;
	}
	else if (value < 0.0f && -value <= 16777217.0f)
	{
		mgl_f64_t integerPartF = 0.0f;
		mgl_f64_t decimalPartF = modf(-value, &integerPartF);
		mgl_u64_t integerPart = (mgl_u64_t)round(integerPartF);
		mgl_u64_t decimalPart = (mgl_u64_t)round(decimalPartF * pow(10, (double)decimal_places));

		mgl_error_t err;
		mgl_u64_t index = 0;
		mgl_u64_t size = 0;

		// Print dash
		if (buffer_size - index < 1)
		{
			if (out_size != NULL)
				*out_size = index;
			return MGL_ERROR_EOF;
		}
		buffer[index] = '-';
		++index;

		// Print integer part
		err = mgl_u64_to_str(buffer + index, buffer_size - index, integerPart, base, &size);
		index += size;
		if (err != MGL_ERROR_NONE)
		{
			if (out_size != NULL)
				*out_size = index;
			return err;
		}

		if (decimal_places > 0)
		{
			// Print dot
			if (buffer_size - index < 1)
			{
				if (out_size != NULL)
					*out_size = index;
				return MGL_ERROR_EOF;
			}
			buffer[index] = '.';
			++index;

			// Count leading zeroes of fractional part
			mgl_u32_t leadingZeroes = 0;
			{
				mgl_f64_t leadingZeroesProbe = decimalPartF;
				leadingZeroesProbe *= base;
				while (leadingZeroesProbe < 1.0f && leadingZeroesProbe != 0.0f)
				{
					leadingZeroesProbe *= base;
					++leadingZeroes;
				}
			}

			// Print leading zeros
			for (mgl_u32_t i = 0; i < leadingZeroes; ++i)
			{
				if (buffer_size - index < 1)
				{
					if (out_size != NULL)
						*out_size = index;
					return MGL_ERROR_EOF;
				}
				buffer[index] = '0';
				++index;
			}

			// Print fractional part
			err = mgl_u64_to_str(buffer + index, buffer_size - index, decimalPart, base, &size);
			index += size;
			size += leadingZeroes;
			if (err != MGL_ERROR_NONE)
			{
				if (out_size != NULL)
					*out_size = index;
				return err;
			}
			if (size < decimal_places)
			{
				while (size != decimal_places)
				{
					if (buffer_size - index < 1)
					{
						if (out_size != NULL)
							*out_size = index;
						return MGL_ERROR_EOF;
					}
					buffer[index] = '0';
					++index;
					++size;
				}
			}
		}

		if (out_size != NULL)
			*out_size = index;
	}
	else
	{
		// Print as exponent
		mgl_i64_t exp = (mgl_i64_t)floor(log10(fabs(value)));
		mgl_f64_t fractional = value / pow(10, (double)exp);

		if (fractional >= 10.0f)
		{
			++exp;
			fractional /= 10.0f;
		}
		else if (fractional <= 0.1f)
		{
			--exp;
			fractional *= 10.0f;
		}

		mgl_error_t err;
		mgl_u64_t index = 0;
		mgl_u64_t size = 0;

		// Print fractional part
		err = mgl_u64_to_str(buffer + index, buffer_size - index, (mgl_u64_t)fractional, base, &size);
		index += size;
		if (err != MGL_ERROR_NONE)
		{
			if (out_size != NULL)
				*out_size = index;
			return err;
		}

		// Print exponent
		if (buffer_size - index < 1)
		{
			if (out_size != NULL)
				*out_size = index;
			return MGL_ERROR_EOF;
		}
		buffer[index] = 'E';
		++index;

		if (exp > 0)
		{
			if (buffer_size - index < 1)
			{
				if (out_size != NULL)
					*out_size = index;
				return MGL_ERROR_EOF;
			}
			buffer[index] = '+';
			++index;
		}

		err = mgl_u64_to_str(buffer + index, buffer_size - index, exp, base, &size);
		index += size;
		if (err != MGL_ERROR_NONE)
		{
			if (out_size != NULL)
				*out_size = index;
			return err;
		}

		if (out_size != NULL)
			*out_size = index;
	}

	return MGL_ERROR_NONE;
}
