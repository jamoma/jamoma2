% @file
% @ingroup 	jamoma2
% 
% @brief 		Generates the Expected Target Output for Generators using Octave
%
% @author		Nathan Wolek
% @copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
% @license		This project is released under the terms of the MIT License.

clear

output_ramp = double (1 : 64);
output_unipolarramp = double (1 : 64);
output_sine = double (1 : 64);
output_triangle = double (1 : 64);
output_unipolartriangle = double (1 : 64);

% the following function is adapted from the code in JamomaGenerators
function retval = generate_trangle(delta)
	retval = 0.0;
	if ( delta <= 0.25 )
		retval = delta / 0.25;
	elseif ( delta >= 0.75 )
		retval = -1.0 + (delta - 0.75) / 0.25;
	else
		retval = 1.0 - (delta - 0.25) / 0.25;
	endif
endfunction

function retval = generate_unipolartrangle(delta)
	retval = 0.0;
	if ( delta <= 0.25 )
		retval = delta / 0.5;
	elseif ( delta >= 0.75 )
		retval = 1.0 + (delta - 1.5) / 0.5;
	else
		retval = -2.0 - (delta - 1.5) / 0.5;
	endif
		retval = retval + 0.5;
endfunction

for i = 1:64
	current_delta = (i - 1) / 64;
	output_ramp(i) = ( current_delta * 2.0 ) - 1.0;
    output_unipolarramp(i) = current_delta;
	output_sine(i) = sin (current_delta * 2.0 * pi);
	output_triangle(i) = generate_trangle(current_delta);
	output_unipolartriangle(i) = generate_unipolartrangle(current_delta);
endfor

save expectedOutput.mat output_ramp
save -append expectedOutput.mat output_unipolarramp
save -append expectedOutput.mat output_sine
save -append expectedOutput.mat output_triangle
save -append expectedOutput.mat output_unipolartriangle
