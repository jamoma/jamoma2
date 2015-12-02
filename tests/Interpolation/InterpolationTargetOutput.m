% @file
% @ingroup 	jamoma2
% 
% @brief 		Generates the Expected Target Output for Interpolation using Octave
%
% @author		Nathan Wolek
% @copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
% @license		This project is released under the terms of the MIT License.

clear

% starting values
x0 = -1.0;
x1 =  2.0;
x2 =  1.0;
x3 =  4.0;
x = [x0,x1,x2,x3];

output_linear = double (1 : 64);
output_hermite = double (1 : 64);
output_spline = double (1 : 64);

for i = 1:64
	current_delta = 1.0 + i / 64;
	output_linear(i) = interp1(x,current_delta);
	output_hermite(i) = interp1(x,current_delta,"pchip");
	output_spline(i) = interp1(x,current_delta,"spline");
endfor

save expectedOutput.mat output_linear
save -append expectedOutput.mat output_hermite
save -append expectedOutput.mat output_spline
