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
x4 =  3.0;
x = [x0,x1,x2,x3,x4];

output_linear = double (1 : 64);
output_hermite = double (1 : 64);
output_hermitegen = double (1 : 64);
output_spline = double (1 : 64);

% the following function is adapted from gen~.interpolation example from Max 7.1
function retval = interp_hermitegen(v,delta)
	retval = 0.0;
	bias = 0.0;
	tension = 0.0;
	delta_int = fix(delta);
	a = delta - delta_int;
	w = v(delta_int-1);
	x = v(delta_int);
	y = v(delta_int+1);
	z = v(delta_int+2);
	aa = a*a;
	aaa = a*aa;
	bp = 1+bias;
	bm = 1-bias;
	mt = (1-tension)*0.5;
	m0  = ((x-w)*bp + (y-x)*bm) * mt;
	m1  = ((y-x)*bp + (z-y)*bm) * mt;
	a0 =  2*aaa - 3*aa + 1;
   	a1 =    aaa - 2*aa + a;
   	a2 =    aaa -   aa;
   	a3 = -2*aaa + 3*aa;
   	retval = a0*x + a1*m0 + a2*m1 + a3*y;
endfunction

for i = 1:64
	current_delta = 2.0 + i / 64;
	output_linear(i) = interp1(x,current_delta);
	output_hermite(i) = interp1(x,current_delta,"pchip");
	output_hermitegen(i) = interp_hermitegen(x,current_delta);
	output_spline(i) = interp1(x,current_delta,"spline");
endfor

save expectedOutput.mat output_linear
save -append expectedOutput.mat output_hermite
save -append expectedOutput.mat output_hermitegen
save -append expectedOutput.mat output_spline
