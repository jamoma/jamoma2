% @file
% @ingroup 	jamoma2
% 
% @brief 		Generates the Expected Target Output for Oscillators using Octave
%
% @author		Nathan Wolek
% @copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
% @license		This project is released under the terms of the MIT License.

clear

output_sine440 = double (1 : 64);

frequency = 440;
sample_rate = 96000;
step_size = frequency / sample_rate;
current_delta = 0.0;

for i = 1:64
	output_sine440(i) = sin (current_delta * 2.0 * pi);
	current_delta = current_delta + step_size;
endfor

save expectedOutput.mat output_sine440;
