% @file
% @ingroup 	jamoma2
% 
% @brief 		Generates the Expected Target Output for Generators using Octave
%
% @author		Nathan Wolek
% @copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
% @license		This project is released under the terms of the MIT License.

clear

output_unipolarramp = double (1 : 64);

for i = 1:64
	current_delta = (i - 1) / 64;
    output_unipolarramp(i) = current_delta;
endfor

save expectedOutput.mat output_unipolarramp
%save -append expectedOutput.mat MORE OUTPUT