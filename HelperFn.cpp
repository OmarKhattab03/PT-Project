
#include "HelperFn.h"

bool IsValue (string input)
{
	// checks if the input string is a double value
	// return true if it's double value, false otherwise

	// Double values can be: 12.5, -12.5, -23, -23. , -23.0 …etc.

	//TODO: complete this function
    if (input.empty())
        return false;


    int num_decimalpts = 0;
    int signs = 0;

   
    for (int i = 0; i < (int)input.length(); ++i) 
    {
        char thischar = input[i];

        if (!(thischar >= '0' && thischar <= '9')) {

            if (thischar == '.')
            {

                if (num_decimalpts == 0)
                {
                    ++num_decimalpts;
                    continue;
                }
                else
                    return false;
            }

            else if (thischar == '+' || thischar == '-')
            {
                if (i == 0 && signs == 0)
                {
                    ++signs;
                    continue;
                }
                else
                    return false;
            }
            else {
                return false;
            }
        }
    }
    return true;

}

bool IsVariable(string input)
{
	// checks if the input string is a variable name
	// return true if it can be a variable name, false otherwise

	// Variable names must start with an alphabetic letter (small or capital) or an underscore (_). 
    if (!((input[0] >= 'a' && input[0] <= 'z') || (input[0] >= 'A' && input[0] <= 'Z') || input[0] == '_'))
			return false;

	// After the first initial letter, variable names can contain letters, numbers and underscores.  
	// No spaces or special characters, however, are allowed.
	for (int i = 1; i < (int)input.length(); ++i) {
		char currentcharacter = input[i];
		if (!((currentcharacter >= 'a' && currentcharacter <= 'z') || (currentcharacter >= 'A' && currentcharacter <= 'Z') || (currentcharacter >= '0' && currentcharacter <= '9') || currentcharacter == '_')) 
			return false;
	}

	

	//TODO: complete this function

	return true;
}

OpType ValueOrVariable (string input)
{
	// checks if the input string is a double value or a variable name
	// chand returns enum "OpType" (the enum is declared in the .h)

	//TODO: complete this function
	if (IsValue(input))
		return VALUE_OP;

	else if (IsVariable(input))
		return VARIABLE_OP;

	else
		return INVALID_OP;

	return INVALID_OP;
}
